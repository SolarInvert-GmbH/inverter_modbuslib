// esp32
#include <catta/esp32/SinglePwm.hpp>
#include <catta/esp32/Time.hpp>
#include <catta/esp32/Uart.hpp>
#include <catta/esp32/WatchDog.hpp>

// modbus
#include <catta/modbus/SlaveUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/request/Request.hpp>
#include <catta/tomodbus/modbus/si/response/Response.hpp>

// catta
#include <catta/Approximation.hpp>

// std
#include <iostream>

static constexpr std::uint32_t getTimeVariable(const std::chrono::microseconds now)
{
    const std::int64_t nearlySeconds = now.count() >> 20;
    const std::uint64_t u64 = static_cast<std::uint64_t>(nearlySeconds);
    const std::uint32_t u32 = static_cast<std::uint32_t>(u64);
    return u32;
}

static constexpr catta::modbus::si::response::Response handleRequest(const catta::modbus::si::request::Request &request, const std::uint8_t id,
                                                                     const std::chrono::microseconds now)
{
    using Response = catta::modbus::si::response::Response;
    using Address = catta::modbus::si::RegisterAddress;
    if (id != 9 || !request.type().isReadRegister()) return Response();

    switch (request.readRegisterValue().registerAddress())
    {
        case Address::inverterDcVoltage():
            return Response::value16(static_cast<std::uint16_t>(catta::sinusWindow<240, 480, 255>(getTimeVariable(now))));
        case Address::siControlUptime():
            return Response::value32(catta::saw<512>(getTimeVariable(now)));
        case Address::inverterAcPower():
            return Response::value16(static_cast<std::uint16_t>(catta::sinusWindow<5000, 10000, 512>(getTimeVariable(now))));
        case Address::inverterVendorOperatingState():
            return Response::value16(static_cast<std::uint16_t>(catta::step<8, 16>(getTimeVariable(now))));
            ;
        case Address::inverterTemperature():
            // temperature=124-register/2 => [(124-20°C)*2, (124-80°C)*2]
            return Response::value16(static_cast<std::uint16_t>(catta::sinusWindow<88, 208, 256>(getTimeVariable(now))));
        case Address::inverterPhaseVoltageA():
            return Response::value16(static_cast<std::uint16_t>(catta::sinusWindow<200, 250, 1024>(getTimeVariable(now))));
        case Address::inverterWattHours():
            return Response::value32(catta::sinusWindow<0, 1000, 1024>(getTimeVariable(now)));
        case Address::commonSerialNumber():
            return Response::string32(catta::modbus::sunspec::String32::create("dummy-009"));
        default:
            return Response();
    }
}

static constexpr catta::physics::Hertz32 getPwmFrequency(const std::chrono::microseconds now)
{
    return catta::physics::Hertz32(static_cast<std::int32_t>(catta::sinusWindow<20, 100, 512>(getTimeVariable(now))));
}

extern "C" void app_main(void);
extern "C" void app_main(void)
{
    using namespace std::chrono_literals;

    static constexpr std::size_t SIZE = 2;

    static constexpr std::array<catta::esp32::Pin, SIZE> txPin = {catta::esp32::Pin::gp22(), catta::esp32::Pin::gp12()};
    static constexpr std::array<catta::esp32::Pin, SIZE> rxPin = {catta::esp32::Pin::gp23(), catta::esp32::Pin::gp14()};

    static constexpr std::array<catta::esp32::Pin, SIZE> pwmPin = {catta::esp32::Pin::gp05(), catta::esp32::Pin::gp04()};

    static constexpr auto baudrate = catta::hardware::uart::Baudrate::baudrate57600();
    static constexpr auto parity = catta::hardware::uart::Parity::empty();
    static constexpr auto dataBits = catta::hardware::uart::DataBits::eight();
    static constexpr auto stopBits = catta::hardware::uart::StopBits::one();

    static catta::esp32::WatchDog watchDog(10s);

    static std::array<catta::esp32::Uart, SIZE> uart = {catta::esp32::Uart::device1(txPin[0], rxPin[0], baudrate, parity, dataBits, stopBits),
                                                        catta::esp32::Uart::device2(txPin[1], rxPin[1], baudrate, parity, dataBits, stopBits)};

    static constexpr std::uint8_t PwmResolution = 12;

    static constexpr catta::physics::Hertz32 pwmInitialFrequency = getPwmFrequency(std::chrono::microseconds::zero());
    static constexpr std::uint32_t pwmDuty = 1 << (PwmResolution - 2);  // ~25% high 75% low

    static std::array<catta::esp32::SinglePwm<PwmResolution>, SIZE> pwm = {
        catta::esp32::SinglePwm<PwmResolution>::createChannel0(pwmPin[0], pwmInitialFrequency, pwmDuty),
        catta::esp32::SinglePwm<PwmResolution>::createChannel1(pwmPin[1], pwmInitialFrequency, pwmDuty)};

    static std::array<catta::modbus::SlaveUart, SIZE> modbus = {catta::modbus::SlaveUart(), catta::modbus::SlaveUart()};

    using Parser = catta::frommodbus::Parser<catta::modbus::si::request::Request>;
    using Serializer = catta::tomodbus::Serializer<catta::modbus::si::response::Response>;

    static std::array<Parser, SIZE> parser = {};
    static std::array<Serializer, SIZE> serializer = {};

    using Byte = std::optional<std::uint8_t>;
    using Token = catta::modbus::Token;

    static std::array<Byte, SIZE> receivedByte = {std::nullopt, std::nullopt};
    static std::array<Byte, SIZE> sendByte = {std::nullopt, std::nullopt};
    static std::array<Token, SIZE> sendToken = {};
    static std::array<Token, SIZE> receiveToken = {};

    using Response = catta::modbus::si::response::Response;

    static std::array<Response, SIZE> response = {};

    static std::chrono::microseconds nextPwm = std::chrono::microseconds::zero();

    while (true)
    {
        const auto now = catta::esp32::Time::get();
        if (now > nextPwm)
        {
            const catta::physics::Hertz32 frequency = getPwmFrequency(now);
            pwm[0].set(frequency, pwmDuty);
            pwm[1].set(frequency, pwmDuty);
            nextPwm = now + 1s;
        }

        for (std::size_t i = 0; i < SIZE; i++)
        {
            if (!sendByte[i] && receiveToken[i].isEmpty())
            {
                const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = modbus[i].work(now, receivedByte[i], sendToken[i]);
                if (sendHandled) sendToken[i] = {};
                receivedByte[i] = std::nullopt;
                sendByte[i] = sendByteLocal;
                receiveToken[i] = recevieTokenLocal;
            }
            if (sendByte[i])
                if (uart[i].write(static_cast<char>(sendByte[i].value()))) sendByte[i] = std::nullopt;

            if (!receivedByte[i]) receivedByte[i] = uart[i].read();

            if (!receiveToken[i].isEmpty())
            {
                const auto [error, handled] = parser[i].read(receiveToken[i]);
                if (handled) receiveToken[i] = {};
                if (parser[i].state().isDone())
                {
                    const auto request = parser[i].data();
                    response[i] = handleRequest(request, modbus[i].modbusId(), now);
                    if (response[i].isEmpty()) modbus[i] = {};
                    parser[i] = {};
                }
                if (parser[i].state().isFailed()) parser[i] = {};
            }

            if (!response[i].isEmpty() && sendToken[i].isEmpty())
            {
                [[maybe_unused]] const auto ignore = serializer[i].read(response[i]);
                sendToken[i] = serializer[i].data();
                if (serializer[i].state().isDone())
                {
                    serializer[i] = {};
                    response[i] = {};
                }
                if (serializer[i].state().isFailed()) serializer[i] = {};
            }
        }
        watchDog.feed();
    }
}
