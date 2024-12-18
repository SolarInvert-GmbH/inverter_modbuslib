// rp2040
#include <catta/rp2040/Time.hpp>
#include <catta/rp2040/Uart.hpp>

// modbus
#include <catta/modbus/MasterUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/response/Response.hpp>
#include <catta/tomodbus/modbus/si/request/Request.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// fromstring
#include <catta/fromstring/modbus/si/request/Request.hpp>

// container
#include <catta/container/RingBuffer.hpp>

// std
#include <type_traits>

enum LogLevel
{
    NOTHING,
    DEBUG,
    VERBOSE
};

static std::array<char, 17> printTimestamp(const std::chrono::microseconds t)
{
    std::array<char, 17> r = {'0', '0', ':', '0', '0', ':', '0', '0', '-', '0', '0', '0', ':', '0', '0', '0', '\0'};
    auto h = (t.count() / (1000 * 1000 * 60 * std::int64_t(60))) % 24;
    auto M = (t.count() / (1000 * 1000 * 60)) % 60;
    auto s = (t.count() / (1000 * 1000)) % 60;
    auto milli = (t.count() / 1000) % 1000;
    auto micro = (t.count() / 1) % 1000;
    const auto set = [&r](const auto source, const auto factor, const std::size_t index)
    { r[index] = static_cast<char>((static_cast<int>(source) / factor) % 10 + '0'); };
    set(h, 10, 0);
    set(h, 1, 1);
    set(M, 10, 3);
    set(M, 1, 4);
    set(s, 10, 6);
    set(s, 1, 7);
    set(milli, 100, 9);
    set(milli, 10, 10);
    set(milli, 1, 11);
    set(micro, 100, 13);
    set(micro, 10, 14);
    set(micro, 1, 15);
    return r;
}

int main()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    using namespace std::chrono_literals;

    static constexpr bool isDebug = false;
    static constexpr bool isVerbose = false;

    static constexpr auto tx0 = catta::rp2040::Pin::gp00();
    static constexpr auto rx0 = catta::rp2040::Pin::gp01();

    static constexpr auto tx1 = catta::rp2040::Pin::gp04();
    static constexpr auto rx1 = catta::rp2040::Pin::gp05();

    static constexpr auto baudrate0 = catta::hardware::uart::Baudrate::baudrate115200();
    static constexpr auto parity0 = catta::hardware::uart::Parity::empty();
    static constexpr auto dataBits0 = catta::hardware::uart::DataBits::eight();
    static constexpr auto stopBits0 = catta::hardware::uart::StopBits::one();

    static constexpr auto baudrate1 = catta::hardware::uart::Baudrate::baudrate57600();
    static constexpr auto parity1 = catta::hardware::uart::Parity::empty();
    static constexpr auto dataBits1 = catta::hardware::uart::DataBits::eight();
    static constexpr auto stopBits1 = catta::hardware::uart::StopBits::one();

    static constexpr std::chrono::microseconds requestTimeout = std::chrono::milliseconds{500};
    static constexpr std::chrono::microseconds dataTimeout = std::chrono::milliseconds{100};  // should be much smaller
    static constexpr std::chrono::microseconds stayInError = std::chrono::seconds{5};
    static constexpr std::chrono::microseconds waitForIdle = std::chrono::microseconds{1};

    static constexpr std::uint8_t address = 0x0d;

    catta::rp2040::Uart uartJson = catta::rp2040::Uart::device0(tx0, rx0, baudrate0, parity0, dataBits0, stopBits0);
    catta::rp2040::Uart uartModbus = catta::rp2040::Uart::device1(tx1, rx1, baudrate1, parity1, dataBits1, stopBits1);
    auto modbus = catta::modbus::MasterUart(requestTimeout, dataTimeout, stayInError, waitForIdle);

    catta::tomodbus::Serializer<catta::modbus::si::request::Request> serializer;
    catta::frommodbus::Parser<catta::modbus::si::response::Response> parser;

    catta::modbus::MasterUartState state;
    catta::modbus::MasterUartState error;

    std::optional<std::uint8_t> receivedByte = {};
    std::optional<std::uint8_t> sendByte = {};
    catta::modbus::Token sendToken = {};
    catta::modbus::Token receiveToken = {};

    std::optional<char> receivedCharacter = {};
    catta::fromstring::Parser<catta::modbus::si::request::Request> jsonParser = {};
    catta::modbus::si::request::Request request = {};

    static constexpr std::size_t SIZE = 400;
    static catta::container::RingBuffer<char, SIZE * 2> out;
    using LineBuffer = catta::container::RingBuffer<std::uint8_t, SIZE>;
    LineBuffer sendLine;
    LineBuffer receiveLine;

    static const auto print = [](const char* in)
    {
        for (const char* c = in; *c != '\0'; c++) out.push(*c);
    };

    static const auto printFrom = [](auto in)
    {
        using Type = std::remove_cvref<decltype(in)>::type;
        catta::tostring::Serializer<Type> serializer;
        while (true)
        {
            const auto [error, inputHandled] = serializer.read(in);
            if (!error.isEmpty()) return;
            const char data = serializer.data();
            if (data == '\0') return;
            out.push(data);
        }
    };
    static const auto printLine = [](LineBuffer& vec)
    {
        for (; vec.size() > 0; vec.pop())
        {
            printFrom(catta::Hexadecimal(vec.front()));
            if (vec.size() > 1) out.push(':');
        }
    };
    static const auto printEndline = []()
    {
        out.push('\r');
        out.push('\n');
    };

    bool led = false;

    auto next = catta::rp2040::Time::get() + std::chrono::seconds{1};
    print("Modbus demo\r\n");
    while (true)
    {
        const auto now = catta::rp2040::Time::get();

        if (now > next)
        {
            led = !led;
            next = catta::rp2040::Time::get() + std::chrono::seconds{1};
        }
        gpio_put(PICO_DEFAULT_LED_PIN, led);
        const auto debugLog = [now](const char* s)
        {
            if (isVerbose)
            {
                print(printTimestamp(now).data());
                print(" ");
            }
            print(s);
        };

        if (!sendByte && receiveToken.isEmpty())
        {
            const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = modbus.work(now, receivedByte, sendToken, address);
            if (isVerbose && state != modbusState)
            {
                print(printTimestamp(now).data());
                print(" [Modbus::Uart::State] ");
                printFrom(modbusState);
                printEndline();
                state = modbusState;
            }
            if (modbusState > catta::modbus::MasterUartState::receive() && error.isEmpty())
            {
                if (isDebug)
                {
                    debugLog("Send bytes: ");
                    printLine(sendLine);
                    printEndline();
                    sendLine = {};
                    debugLog("Received Bytes: ");
                    printLine(receiveLine);
                    printEndline();
                    receiveLine = {};
                }
                error = modbusState;
            }
            if (modbusState.isIdle() && !error.isEmpty())
            {
                debugLog("Modbus uart had error: ");
                printFrom(error);
                printEndline();
                error = {};
            }
            if (isDebug && sendByteLocal) sendLine.push(sendByteLocal.value());
            if (isDebug && sendHandled && sendToken.type().isEnd())
            {
                debugLog("Send Bytes: ");
                printLine(sendLine);
                printEndline();
                sendLine = {};
            }
            if (sendHandled) sendToken = {};
            receivedByte = {};
            sendByte = sendByteLocal;
            receiveToken = recevieTokenLocal;
        }

        if (sendByte)
            if (uartModbus.write(static_cast<char>(sendByte.value())))
            {
                if (isVerbose)
                {
                    debugLog("send: ");
                    printFrom(catta::Hexadecimal(sendByte.value()));
                    printEndline();
                }
                sendByte = {};
            }
        if (!receivedByte)
        {
            const auto result = uartModbus.read();
            if (result)
            {
                receiveLine.push(static_cast<std::uint8_t>(result.value()));
                receivedByte = result;
                if (isVerbose)
                {
                    debugLog("receive: ");
                    printFrom(catta::Hexadecimal(result.value()));
                    printEndline();
                }
            }
        }

        if (!receiveToken.isEmpty())
        {
            const auto [error, handled] = parser.read(receiveToken);
            if (handled) receiveToken = {};
            if (parser.state().isDone())
            {
                const auto response = parser.data();
                if (isDebug)
                {
                    debugLog("Received Bytes: ");
                    printLine(receiveLine);
                    printEndline();
                    receiveLine = {};
                    debugLog("Received: ");
                }
                parser = {};
                printFrom(response);
                printEndline();
                request = {};
            }
            if (parser.state().isFailed())
            {
                if (isDebug)
                {
                    debugLog("Parsing error: ");
                    printLine(receiveLine);
                    printEndline();
                    receiveLine = {};
                }
                parser = {};
                request = {};
            }
        }

        if (!request.isEmpty() && sendToken.isEmpty())
        {
            [[maybe_unused]] const auto ignore = serializer.read(request);
            sendToken = serializer.data();
            if (serializer.state().isDone())
            {
                serializer = {};
                if (isDebug)
                {
                    debugLog("Send: ");
                    printFrom(request);
                    printEndline();
                }
                request = {};
            }
            if (serializer.state().isFailed())
            {
                if (isDebug)
                {
                    debugLog("Serializing error: ");
                    printLine(sendLine);
                    printEndline();
                    debugLog("");
                    printFrom(request);
                    printEndline();
                    sendLine = {};
                }
                serializer = {};
                request = {};
            }
        }

        if (!receivedCharacter) receivedCharacter = uartJson.read();

        if (request.isEmpty() && receivedCharacter)
        {
            const char in = receivedCharacter.value() == '\r' || receivedCharacter.value() == '\n' ? '\0' : receivedCharacter.value();
            if (in != '\0' || !jsonParser.state().isStart())
            {
                const auto [error, inputHandled] = jsonParser.read(in);

                if (jsonParser.state().isFailed())
                {
                    jsonParser = {};
                    debugLog("Json parser error\r\n");
                    receivedCharacter = {};
                }

                if (inputHandled)
                {
                    receivedCharacter = {};
                }
                if (jsonParser.state().isDone())
                {
                    request = jsonParser.data();
                    if (isDebug)
                    {
                        debugLog("Receive json request: ");
                        printFrom(request);
                        printEndline();
                    }
                    jsonParser = {};
                }
            }
            else
                receivedCharacter = {};
        }

        if (out.size() && uartJson.write(out.front())) out.pop();
    }

    return 1;
}
