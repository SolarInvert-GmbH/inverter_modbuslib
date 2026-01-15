// linux
#include <catta/linux/Time.hpp>
#include <catta/linux/Uart.hpp>

// modbus
#include <catta/modbus/SlaveUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/request/Request.hpp>
#include <catta/tomodbus/modbus/si/response/Response.hpp>

// random
#include <catta/random/modbus/si/response/FactoryValues.hpp>
#include <catta/random/modbus/si/response/ReadError.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/random/modbus/sunspec/String16.hpp>
#include <catta/random/modbus/sunspec/String32.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// fromstring
#include <catta/fromstring/Hexadecimal.hpp>

// system
#include <signal.h>

// std
#include <cmath>
#include <fstream>
#include <vector>

enum LogLevel
{
    NOTHING,
    DEBUG,
    VERBOSE
};

static std::string printTimestamp(const std::chrono::microseconds t)
{
    std::string r = "00.00.0000-00:00:00-000:000";
    using namespace std::chrono;
    std::chrono::time_point<system_clock, microseconds> tp = std::chrono::time_point<system_clock, microseconds>(t);
    auto dp = floor<days>(tp);
    year_month_day ymd{dp};
    hh_mm_ss time{floor<microseconds>(tp - dp)};
    auto y = ymd.year();
    auto m = static_cast<unsigned>(ymd.month());
    auto d = static_cast<unsigned>(ymd.day());
    auto h = time.hours().count();
    auto M = time.minutes().count();
    auto s = time.seconds().count();
    auto ss = time.subseconds().count();
    const auto set = [&r](const auto source, const auto factor, const std::size_t index)
    { r[index] = static_cast<char>((static_cast<int>(source) / factor) % 10 + '0'); };
    set(d, 10, 0);
    set(d, 1, 1);
    set(m, 10, 3);
    set(m, 1, 4);
    set(y, 1000, 6);
    set(y, 100, 7);
    set(y, 10, 8);
    set(y, 1, 9);
    set(h, 10, 11);
    set(h, 1, 12);
    set(M, 10, 14);
    set(M, 1, 15);
    set(s, 10, 17);
    set(s, 1, 18);
    set(ss, 100 * 1000, 20);
    set(ss, 10 * 1000, 21);
    set(ss, 1 * 1000, 22);
    set(ss, 100, 24);
    set(ss, 10, 25);
    set(ss, 1, 26);
    return r;
}

static void printHelp(const std::string_view program)
{
    std::cout << program << " --uart /dev/ttyUSB0 [--debug [--verbose]] [ [--switch] | [--id ID] ] \n";
    std::cout << " --uart     : uart device.\n";
    std::cout << "[--debug]   : print debug messages.\n";
    std::cout << "[--verbose] : vebose debug messages. Needs '--verbose'.\n";
    std::cout
        << "[--switch]  : path to a file. The file is read on every response. The first five character of the file have to be '0' or '1'. If the "
           "request is for id 0…4 and the the n-th byte is '0' there will be no response. All other ids will be ignored when switch file is set. "
           "Can't be used with '--id'.\n";
    std::cout << "[--id]      : Only answer for one id. ID two hexadecimal digets. Can't be used with '--switch'.\n";
}

static void logAndExit(const std::string &message)
{
    std::cout << message << std::endl;
    exit(EXIT_FAILURE);
}

static std::tuple<std::string, LogLevel, std::string, std::optional<std::uint8_t>> checkFlags(int argc, char *argv[])
{
    std::string uart;
    bool debug = false;
    bool verbose = false;
    std::string switchFile;
    std::optional<std::uint8_t> id = std::nullopt;

    static const auto checkArg = [](const std::string &arg, const std::string &name)
    {
        if (arg.empty()) logAndExit("'--" + name + "' not set.");
    };

    static const auto setArg = [argc, argv](std::string &arg, const std::string &name, int &i)
    {
        if (i + 1 >= argc) logAndExit("Add " + name + " after '--" + name + "'.");
        i++;
        arg = argv[i];
    };

    static const auto setArgByte = [argc, argv](std::optional<std::uint8_t> &arg, const std::string &name, int &i)
    {
        if (i + 1 >= argc) logAndExit("Add " + name + " after '--" + name + "'.");
        i++;
        const std::uint8_t v = std::uint8_t(catta::fromstring::fromString<catta::Hexadecimal<std::uint8_t>>(argv[i]));
        if (v == 0 && std::string(argv[i]) != "00") logAndExit("Add valid (two hex digets) " + name + " after '--" + name + "'.");
        arg = v;
    };

    static const auto setBool = [](bool &arg, const std::string &name)
    {
        if (arg) logAndExit("'--" + name + "' used more than once");
        arg = true;
    };

    for (int i = 1; i < argc; i++)
    {
        const std::string flag = argv[i];
        if (flag == "--uart")
            setArg(uart, "uart", i);
        else if (flag == "--debug")
            setBool(debug, "debug");
        else if (flag == "--verbose")
            setBool(verbose, "verbose");
        else if (flag == "--switch")
            setArg(switchFile, "switch", i);
        else if (flag == "--id")
            setArgByte(id, "id", i);
        else if (flag == "help" || flag == "-h" || flag == "--help")
        {
            printHelp(argv[0]);
            exit(EXIT_FAILURE);
        }
        else
            logAndExit("Could not understand '" + flag + "'");
    }
    LogLevel logLevel = NOTHING;
    checkArg(uart, "uart");
    if (debug)
        logLevel = verbose ? VERBOSE : DEBUG;
    else if (verbose)
        logAndExit("Used '--verbose' without '--debug'");
    if (!switchFile.empty() && id) logAndExit("Used '--switch' and '--id'. You can only use one at once.");
    return std::tuple<std::string, LogLevel, std::string, std::optional<std::uint8_t>>{uart, logLevel, switchFile, id};
}

static bool end = false;

static void signalHandler(const int signal)
{
    if (signal == SIGTERM || signal == SIGINT) end = true;
}

template <class T>
static T sinus(const double min, const double max, const std::uint8_t id, const double length)
{
    const double p = 3.141592654;
    const double offset = static_cast<double>(id % 4) / 4.0;
    const double t = ((static_cast<double>(catta::linux::Time::get().count()) / 1'000'000.0) / length + offset) * 2.0 * p;
    const double s = std::sin(t) * 0.5 + 0.5;
    const double v = s * (max - min) + min;
    return static_cast<T>(v);
}

static std::uint32_t saw(const std::uint32_t max, const std::uint8_t id)
{
    const std::int64_t m = static_cast<std::uint32_t>(max);
    const std::int64_t offset = static_cast<int32_t>(id % 4) * (m / 4);
    const std::uint32_t t = static_cast<uint32_t>((catta::linux::Time::get().count() / 1'000'000 + offset) % m);
    return t;
}

static std::uint16_t state()
{
    const std::uint16_t max = catta::modbus::si::State::empty();
    const std::uint16_t v = static_cast<std::uint16_t>(((catta::linux::Time::get().count() / 1'000'000) / 30) % max);
    return v;
}

static bool ignoreRequest(const std::string &switchFile, const std::uint8_t id, const std::optional<std::uint8_t> onlyId)
{
    if (onlyId) return id != onlyId.value();
    if (id >= 5) return !switchFile.empty();
    std::ifstream f(switchFile.c_str());
    for (std::uint8_t i = 0; i < 5; i++)
    {
        char c = '1';
        f.get(c);
        if (id == i) return c == '0';
    }
    return false;
}

static void handleRequest(const catta::modbus::si::request::Request &request, catta::modbus::si::response::Response &response,
                          catta::random::Random &random, const std::uint8_t id, const std::string &switchFile,
                          const std::optional<std::uint8_t> onlyId)
{
    if (ignoreRequest(switchFile, id, onlyId)) return;
    using Type = catta::modbus::si::request::Type;
    using Response = catta::modbus::si::response::Response;
    switch (request.type())
    {
        case Type::readRegister():

            using Address = catta::modbus::si::RegisterAddress;
            switch (request.readRegisterValue().registerAddress())
            {
                case Address::inverterDcVoltage():
                    response = Response::value16(sinus<std::uint16_t>(240.0, 480.0, id, 300.0));
                    return;
                case Address::siControlUptime():
                    response = Response::value32(saw(500, id));
                    return;
                case Address::inverterAcPower():
                    response = Response::value16(sinus<std::uint16_t>(5000.0, 10000.0, id, 400.0));
                    return;
                case Address::inverterVendorOperatingState():
                    response = Response::value16(id == 0x00 ? 0 : state());
                    return;
                case Address::inverterTemperature():
                    response = Response::value16(
                        sinus<std::uint16_t>(88.0, 208.0, id, 200.0));  // temperature=124-register/2 => [(124-20°C)*2, (124-80°C)*2]
                    return;
                case Address::inverterPhaseVoltageA():
                    response = Response::value16(sinus<std::uint16_t>(200.0, 250.0, id, 800.0));
                    return;
                case Address::inverterWattHours():
                    response = Response::value32(sinus<std::uint32_t>(0.0, 1000.0, id, 800.0));
                    return;
                default:
                    break;
            }

            switch (request.readRegisterValue().registerAddress().type())
            {
                case catta::modbus::si::RegisterType::uint16():
                case catta::modbus::si::RegisterType::sint16():
                    response = Response::value16(random.create<std::uint16_t>());
                    break;
                case catta::modbus::si::RegisterType::connectedPhase():
                    response = Response::value16(random.interval(std::uint16_t(1), std::uint16_t(3)));
                    break;
                case catta::modbus::si::RegisterType::scaleFactor():
                    response = Response::value16(static_cast<std::uint16_t>(random.interval(std::int16_t(-10), std::int16_t(+10))));
                    break;
                case catta::modbus::si::RegisterType::sint32():
                case catta::modbus::si::RegisterType::uint32():
                    response = Response::value32(random.create<std::uint32_t>());
                    break;
                case catta::modbus::si::RegisterType::uint64():
                    response = Response::value64(random.interval(std::uint64_t(0), std::uint64_t(1) << 50));
                    break;
                case catta::modbus::si::RegisterType::string16():
                    response = Response::string16(random.create<catta::modbus::sunspec::String16>());
                    break;
                case catta::modbus::si::RegisterType::string32():
                {
                    const std::array<char, 10> s = std::array<char, 10>{'d',
                                                                        'u',
                                                                        'm',
                                                                        'm',
                                                                        'y',
                                                                        '-',
                                                                        static_cast<char>('0' + (id / 100) % 10),
                                                                        static_cast<char>('0' + (id / 10) % 10),
                                                                        static_cast<char>('0' + (id / 1) % 10),
                                                                        '\0'};
                    response = Response::string32(catta::modbus::sunspec::String32::create(s.data()));
                    break;
                }

                default:
                    break;
            }
            break;
        case Type::writeRegister():
            response = Response::writeRegister(request.writeRegisterValue().registerAddress());
            break;
        case Type::factoryValues():
            response = Response::factoryValues(random.create<catta::modbus::si::response::FactoryValues>());
            break;
        case Type::readOperatingData33():
            response = Response::readOperatingData33(random.create<catta::modbus::si::response::ReadOperatingData33>());
            break;
        case Type::readOperatingData3e():
            response = Response::readOperatingData3e(random.create<catta::modbus::si::response::ReadOperatingData3e>());
            break;
        case Type::switchOffGridRelay():
            response = Response::switchOffGridRelay(random.create<bool>());
            break;
        case Type::switchOnGridRelay():
            response = Response::switchOnGridRelay(random.create<bool>());
            break;
        case Type::forceIdle():
            response = Response::forceIdle(random.create<bool>());
            break;
        case Type::deactivateIdle():
            response = Response::deactivateIdle(random.create<bool>());
            break;
        case Type::startConstantVoltage():
            response = Response::startConstantVoltage(random.create<bool>());
            break;
        case Type::endConstantVoltage():
            response = Response::endConstantVoltage(random.create<bool>());
            break;
        case Type::setPowerFactor():
            response = Response::setPowerFactor(random.create<bool>());
            break;
        case Type::controlBatteryInvert():
            response = Response::controlBatteryInvert(random.create<bool>());
            break;
        case Type::limitBatteryInvert():
            response = Response::limitBatteryInvert(random.create<bool>());
            break;
        case Type::readError():
            response = Response::readError(random.create<catta::modbus::si::response::ReadError>());
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
    const auto [uartDevice, logLevel, switchFile, onlyId] = checkFlags(argc, argv);

    const bool isDebug = logLevel == DEBUG || logLevel == VERBOSE;
    const bool isVerbose = logLevel == VERBOSE;

    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    // Baud Rate 57600, 1 Startbit, 1 Stopbit, 8 Databits, No Parity
    static constexpr auto baudrate = catta::hardware::uart::Baudrate::baudrate57600();
    static constexpr auto parity = catta::hardware::uart::Parity::empty();
    static constexpr auto dataBits = catta::hardware::uart::DataBits::eight();
    static constexpr auto stopBits = catta::hardware::uart::StopBits::one();

    auto uart = catta::linux::Uart::create(uartDevice, baudrate, parity, dataBits, stopBits);
    auto modbus = catta::modbus::SlaveUart();

    bool uartConnection = false;

    const auto logConnection = [isVerbose](catta::linux::Uart &uart, bool &boolean, const char *name, const std::chrono::microseconds now)
    {
        const bool c = uart.error().isEmpty();
        if (c != boolean)
        {
            if (c)
            {
                if (isVerbose) std::cout << printTimestamp(now) << ' ';
                std::cout << name << ": Connect\n";
                boolean = true;
            }
            else
            {
                if (isVerbose) std::cout << printTimestamp(now) << ' ';
                std::cout << name << ": Disconnect" << catta::tostring::toString(uart.error()) << "\n";
                boolean = false;
            }
        }
    };
    catta::frommodbus::Parser<catta::modbus::si::request::Request> parser;
    catta::tomodbus::Serializer<catta::modbus::si::response::Response> serializer;

    catta::modbus::SlaveUartState state;

    std::optional<std::uint8_t> receivedByte = std::nullopt;
    std::optional<std::uint8_t> sendByte = std::nullopt;
    catta::modbus::Token sendToken = {};
    catta::modbus::Token receiveToken = {};

    std::vector<std::uint8_t> sendLine;
    std::vector<std::uint8_t> receiveLine;

    catta::random::Random random = catta::random::Random::create(static_cast<std::uint64_t>(catta::linux::Time::get().count()));

    const auto printLine = [](const std::vector<std::uint8_t> &vec)
    {
        std::string s;
        for (std::size_t i = 0; i < vec.size(); i++)
        {
            s += catta::tostring::toString(catta::Hexadecimal(vec[i]));
            if (i + 1 < vec.size()) s += ':';
        }
        return s;
    };

    catta::modbus::si::response::Response response = {};

    while (!end)
    {
        const auto now = catta::linux::Time::get();
        bool somethingHappend = false;

        const auto debugLog = [now, isVerbose](const std::string s)
        {
            if (isVerbose) std::cout << printTimestamp(now) << ' ';
            std::cout << s;
        };

        logConnection(uart, uartConnection, "Uart", now);

        if (!sendByte && receiveToken.isEmpty())
        {
            const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = modbus.work(now, receivedByte, sendToken);
            if (isVerbose && state != modbusState)
            {
                debugLog("[Modbus::Uart::State] " + catta::tostring::toString(modbusState) + '\n');
                state = modbusState;
            }
            if (isDebug && sendByteLocal) sendLine.push_back(sendByteLocal.value());
            if (isDebug && sendHandled && sendToken.type().isEnd())
            {
                debugLog("Send: " + printLine(sendLine) + '\n');
                sendLine = {};
            }
            if (sendHandled) sendToken = {};
            receivedByte = std::nullopt;
            sendByte = sendByteLocal;

            receiveToken = recevieTokenLocal;
            if (sendByte || !receiveToken.isEmpty()) somethingHappend = true;
        }
        if (sendByte)
            if (uart.write(static_cast<char>(sendByte.value())))
            {
                if (isVerbose) debugLog("send: " + catta::tostring::toString(catta::Hexadecimal(sendByte.value())) + '\n');
                sendByte = std::nullopt;
                somethingHappend = true;
            }
        if (uart.error().isEmpty())
        {
            if (!receivedByte)
            {
                const auto result = uart.read();
                if (result)
                {
                    receiveLine.push_back(static_cast<std::uint8_t>(result.value()));
                    receivedByte = result;
                    somethingHappend = true;
                    if (isVerbose) debugLog("receive: " + catta::tostring::toString(catta::Hexadecimal(result.value())) + '\n');
                }
            }
        }
        else
            uart = catta::linux::Uart::create(uartDevice, baudrate, parity, dataBits, stopBits);

        if (!receiveToken.isEmpty())
        {
            const auto [error, handled] = parser.read(receiveToken);
            if (handled) receiveToken = {};
            if (parser.state().isDone())
            {
                const auto request = parser.data();
                handleRequest(request, response, random, modbus.modbusId(), switchFile, onlyId);
                if (isDebug)
                {
                    debugLog("Received Bytes: " + printLine(receiveLine) + '\n');
                    receiveLine = {};
                    debugLog("Received: ");
                }
                std::cout << catta::tostring::toString(request) << '\n';
                if (response.isEmpty())
                {
                    debugLog("Response: ");
                    std::cout << "EMPTY\n";
                    modbus = {};
                }
                parser = {};
            }
            if (parser.state().isFailed())
            {
                if (isDebug)
                {
                    debugLog("Parsing error: " + printLine(receiveLine) + '\n');
                    receiveLine = {};
                }
                parser = {};
            }
            somethingHappend = true;
        }

        if (!response.isEmpty() && sendToken.isEmpty())
        {
            somethingHappend = true;
            [[maybe_unused]] const auto ignore = serializer.read(response);
            sendToken = serializer.data();
            if (serializer.state().isDone())
            {
                serializer = {};
                if (isDebug) debugLog("Send: ");
                std::cout << catta::tostring::toString(response) << '\n';
                response = {};
            }
            if (serializer.state().isFailed())
            {
                if (isDebug)
                {
                    debugLog("Serializing error: " + printLine(sendLine) + '\n');
                    debugLog(catta::tostring::toString(response) + '\n');
                    sendLine = {};
                }
                serializer = {};
            }
        }

        if (!somethingHappend) catta::linux::Time::sleep(1us);
    }

    std::cout << "Exit.\n";
    return 0;
}
