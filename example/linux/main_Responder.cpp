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
#include <catta/random/modbus/sunspec/String.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// system
#include <signal.h>

// std
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
    std::cout << program << " --uart /dev/ttyUSB0 [--debug [--verbose]] \n";
    std::cout << " --uart     : uart device.\n";
    std::cout << "[--debug]   : print debug messages.\n";
    std::cout << "[--verbose] : vebose debug messages. Needs '--verbose'.\n";
}

static void logAndExit(const std::string &message)
{
    std::cout << message << std::endl;
    exit(EXIT_FAILURE);
}

static std::tuple<std::string, LogLevel> checkFlags(int argc, char *argv[])
{
    std::string uart;
    bool debug = false;
    bool verbose = false;

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
    return std::tuple<std::string, LogLevel>{uart, logLevel};
}

static bool end = false;

static void signalHandler(const int signal)
{
    if (signal == SIGTERM || signal == SIGINT) end = true;
}

static void handleRequest(const catta::modbus::si::request::Request &request, catta::modbus::si::response::Response &response,
                          catta::random::Random &random)
{
    using Type = catta::modbus::si::request::Type;
    using Response = catta::modbus::si::response::Response;
    switch (request.type())
    {
        case Type::readRegister():

            switch (request.readRegisterValue().registerAddress().type().size())
            {
                case 2:
                    response = Response::value16(random.create<std::uint16_t>());
                    break;
                case 4:
                    response = Response::value32(random.create<std::uint32_t>());
                    break;
                case 8:
                    response = Response::value64(random.interval(std::uint64_t(0), std::uint64_t(1) << 50));
                    break;
                case 32:
                    response = Response::string(random.create<catta::modbus::sunspec::String>());
                    break;

                default:
                    break;
            }
            break;
        case Type::writeRegister():
            response = Response::writeRegister(request.writeRegisterValue());
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
    const auto [uartDevice, logLevel] = checkFlags(argc, argv);

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

    std::optional<std::uint8_t> receivedByte = {};
    std::optional<std::uint8_t> sendByte = {};
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
            receivedByte = {};
            sendByte = sendByteLocal;

            receiveToken = recevieTokenLocal;
            if (sendByte || !receiveToken.isEmpty()) somethingHappend = true;
        }
        if (sendByte)
            if (uart.write(static_cast<char>(sendByte.value())))
            {
                if (isVerbose) debugLog("send: " + catta::tostring::toString(catta::Hexadecimal(sendByte.value())) + '\n');
                sendByte = {};
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
                handleRequest(request, response, random);
                if (isDebug)
                {
                    debugLog("Received Bytes: " + printLine(receiveLine) + '\n');
                    receiveLine = {};
                    debugLog("Received: ");
                }
                std::cout << catta::tostring::toString(request) << '\n';
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
                if (isDebug) debugLog("Send: " + catta::tostring::toString(response) + '\n');
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
