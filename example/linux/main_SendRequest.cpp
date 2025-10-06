// linux
#include <catta/linux/Time.hpp>
#include <catta/linux/Uart.hpp>

// modbus
#include <catta/modbus/MasterUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/response/Response.hpp>
#include <catta/tomodbus/modbus/si/request/Request.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/NiceResponse.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// fromstring
#include <catta/fromstring/Decimal.hpp>
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/fromstring/modbus/si/request/Request.hpp>

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
    std::cout << program
              << " --uart /dev/ttyUSB0 --modbusid 01 --request '{\"type\":\"readError\",\"value\":null}' [--timeout 5000] [--debug [--verbose]]\n";
    std::cout << " --uart     : uart device.\n";
    std::cout << " --modbusid : modbusid in hex (two digets).\n";
    std::cout << " --request  : the request as json.\n";
    std::cout << "[--timeout] : timeout in milliseconds. 1…60000 is allowed. Default is no timeout.\n";
    std::cout << "[--debug]   : print debug messages.\n";
    std::cout << "[--verbose] : vebose debug messages. Needs '--verbose'.\n";
}

static void logAndExit(const std::string &message)
{
    std::cout << message << std::endl;
    exit(EXIT_FAILURE);
}

static std::tuple<std::string, LogLevel, std::uint8_t, catta::modbus::si::request::Request, std::uint16_t> checkFlags(int argc, char *argv[])
{
    std::string uart;
    bool debug = false;
    bool verbose = false;
    std::optional<std::uint8_t> modbusid = {};
    catta::modbus::si::request::Request request;
    std::uint16_t timeout = 0;

    static const auto checkArg = [](const std::string &name, const bool b)
    {
        if (b) logAndExit("'--" + name + "' not set.");
    };

    static const auto setArgString = [argc, argv](std::string &arg, const std::string &name, int &i)
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

    static const auto setArgTimeout = [argc, argv](std::uint16_t &arg, const std::string &name, int &i)
    {
        if (i + 1 >= argc) logAndExit("Add " + name + " after '--" + name + "'.");
        i++;
        const std::uint16_t v = std::uint16_t(catta::fromstring::fromString<catta::Decimal<std::uint16_t>>(argv[i]));
        if (v < 1 || v > 60'000) logAndExit("Add valid timeout 1 … 60000 " + name + " after '--" + name + "'.");
        arg = v;
    };

    static const auto setArgRequest = [argc, argv](catta::modbus::si::request::Request &arg, const std::string &name, int &i)
    {
        if (i + 1 >= argc) logAndExit("Add " + name + " after '--" + name + "'.");
        i++;
        arg = catta::fromstring::fromString<catta::modbus::si::request::Request>(argv[i]);
        if (arg.isEmpty()) logAndExit("Add valid json " + name + " after '--" + name + "'.");
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
            setArgString(uart, "uart", i);
        else if (flag == "--modbusid")
            setArgByte(modbusid, "modbusid", i);
        else if (flag == "--request")
            setArgRequest(request, "request", i);
        else if (flag == "--timeout")
            setArgTimeout(timeout, "timeout", i);
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
    checkArg("uart", uart.empty());
    if (debug)
        logLevel = verbose ? VERBOSE : DEBUG;
    else if (verbose)
        logAndExit("Used '--verbose' without '--debug'");
    checkArg("modbusid", !modbusid);
    checkArg("request", request.isEmpty());

    return std::tuple<std::string, LogLevel, std::uint8_t, catta::modbus::si::request::Request, std::uint16_t>{uart, logLevel, modbusid.value(),
                                                                                                               request, timeout};
}

static bool end = false;

static void signalHandler(const int signal)
{
    if (signal == SIGTERM || signal == SIGINT) end = true;
}

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
    const auto [uartDevice, logLevel, modbusId, requestInput, timeout] = checkFlags(argc, argv);

    const bool isDebug = logLevel == DEBUG || logLevel == VERBOSE;
    const bool isVerbose = logLevel == VERBOSE;

    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    const auto errorExit = [](const std::string value)
    {
        std::cout << "{\"type\":\"error\",\"value\":\"" + value + "\"}";
        return 1;
    };

    // Baud Rate 57600, 1 Startbit, 1 Stopbit, 8 Databits, No Parity
    static constexpr auto baudrate = catta::hardware::uart::Baudrate::baudrate57600();
    static constexpr auto parity = catta::hardware::uart::Parity::empty();
    static constexpr auto dataBits = catta::hardware::uart::DataBits::eight();
    static constexpr auto stopBits = catta::hardware::uart::StopBits::one();

    static constexpr std::chrono::microseconds requestTimeout = std::chrono::milliseconds{500};
    static constexpr std::chrono::microseconds dataTimeout = std::chrono::milliseconds{500};  // should b mush smaller
    static constexpr std::chrono::microseconds stayInError = std::chrono::seconds{5};
    static constexpr std::chrono::microseconds waitForIdle = std::chrono::microseconds{1};

    const std::chrono::microseconds waitUntil =
        timeout == 0 ? std::chrono::microseconds{0} : catta::linux::Time::get() + std::chrono::milliseconds(timeout);

    auto uart = catta::linux::Uart::create(uartDevice, baudrate, parity, dataBits, stopBits);
    auto modbus = catta::modbus::MasterUart(requestTimeout, dataTimeout, stayInError, waitForIdle);

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

    catta::tomodbus::Serializer<catta::modbus::si::request::Request> serializer;
    catta::frommodbus::Parser<catta::modbus::si::response::Response> parser;

    catta::modbus::MasterUartState state;
    catta::modbus::MasterUartState error;

    std::optional<std::uint8_t> receivedByte = {};
    std::optional<std::uint8_t> sendByte = {};
    catta::modbus::Token sendToken = {};
    catta::modbus::Token receiveToken = {};

    std::vector<std::uint8_t> sendLine;
    std::vector<std::uint8_t> receiveLine;

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

    catta::modbus::si::request::Request request = requestInput;

    std::size_t count0 = 0;
    std::size_t count1 = 0;

    while (!end)
    {
        const auto now = catta::linux::Time::get();

        if (waitUntil.count() && now > waitUntil) return errorExit("Timeout");

        bool somethingHappend = false;

        const auto debugLog = [now, isVerbose](const std::string s)
        {
            if (isVerbose) std::cout << printTimestamp(now) << ' ';
            std::cout << s;
        };

        if (isVerbose) logConnection(uart, uartConnection, "Uart", now);

        if (!sendByte && receiveToken.isEmpty())
        {
            const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = modbus.work(now, receivedByte, sendToken, modbusId);
            if (isVerbose && state != modbusState)
            {
                std::cout << printTimestamp(now) << " [Modbus::Uart::State] " << catta::tostring::toString(modbusState) << '\n';
                state = modbusState;
            }
            if (modbusState > catta::modbus::MasterUartState::receive() && error.isEmpty())
            {
                if (isDebug)
                {
                    debugLog("Send bytes: " + printLine(sendLine) + '\n');
                    sendLine = {};
                    debugLog("Received Bytes: " + printLine(receiveLine) + '\n');
                    receiveLine = {};
                }
                error = modbusState;
            }
            if (modbusState.isIdle() && !error.isEmpty())
            {
                debugLog("Modbus uart had error: " + catta::tostring::toString(error) + '\n');
                return 1;
            }
            if (isDebug && sendByteLocal) sendLine.push_back(sendByteLocal.value());
            if (isDebug && sendHandled && sendToken.type().isEnd())
            {
                debugLog("Send bytes: " + printLine(sendLine) + '\n');
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
                count0++;
                const auto result = uart.read();
                if (result)
                {
                    receiveLine.push_back(static_cast<std::uint8_t>(result.value()));
                    receivedByte = result;
                    somethingHappend = true;
                    if (isVerbose)
                        debugLog("receive: " + catta::tostring::toString(catta::Hexadecimal(result.value())) + ' ' + std::to_string(count0) + ' ' +
                                 std::to_string(count1) + '\n');
                    count0 = 0;
                    count1 = 0;
                }
            }
            else
                count1++;
        }
        else
            return errorExit("Uart error: " + catta::tostring::toString(uart.error()));

        if (!receiveToken.isEmpty())
        {
            const auto [error, handled] = parser.read(receiveToken);
            if (handled) receiveToken = {};
            if (parser.state().isDone())
            {
                const auto response = parser.data();
                if (isDebug)
                {
                    debugLog("Received Bytes: " + printLine(receiveLine) + '\n');
                    receiveLine = {};
                    debugLog("Received: ");
                    debugLog("   " + catta::tostring::toString(response));
                }
                parser = {};
                const auto niceResponse = catta::modbus::si::response::NiceResponse::fromUgly(response, requestInput);
                if (niceResponse.isEmpty()) return errorExit("Could not build nice response");
                std::cout << catta::tostring::toString(niceResponse) << '\n';
                return 0;
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

        if (!request.isEmpty() && sendToken.isEmpty())
        {
            somethingHappend = true;
            [[maybe_unused]] const auto ignore = serializer.read(request);
            sendToken = serializer.data();
            if (serializer.state().isDone())
            {
                serializer = {};
                if (isDebug) debugLog("Send: " + catta::tostring::toString(request) + '\n');
                request = {};
            }
            if (serializer.state().isFailed())
            {
                if (isDebug)
                {
                    debugLog("Serializing error: " + printLine(sendLine) + '\n');
                    debugLog(catta::tostring::toString(request) + '\n');
                    sendLine = {};
                }
                serializer = {};
                return errorExit("Corrupted response.");
            }
        }
        if (!somethingHappend) catta::linux::Time::sleep(1us);
    }

    return errorExit("Abort");
}
