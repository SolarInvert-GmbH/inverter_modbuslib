// catta
#include <catta/modbus/Uart.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/Token.hpp>
#include <catta/tostring/modbus/UartState.hpp>
#include <catta/tostring/parser/InputHandled.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromJson.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = true;

template <catta::test::Output OUTPUT>
static bool checkCases(catta::test::Test<OUTPUT>& test)
{
    using State = catta::modbus::UartState;
    using Token = catta::modbus::Token;
    using TokenVec = std::vector<Token>;
    using ByteVec = std::vector<std::uint8_t>;
    const TokenVec sendInput = {Token::address(0x01), Token::function(0x31), Token::length(0x01), Token::data(0x01), Token::end()};
    const ByteVec sendOutput = {0x01, 0x31, 0x01, 0x01, 0x90, 0x47};
    const ByteVec receiveInput = {0x01, 0x31, 0x0c, 0x00, 0x01, 0x1E, 0x04, 0x0d, 0x22, 0x32, 0x28, 0x00, 0x00, 0x00, 0x00, 0x51, 0x51};
    const TokenVec receiveOutput = {Token::address(0x01), Token::function(0x31), Token::length(0x0c), Token::data(0x00),
                                    Token::data(0x01),    Token::data(0x1E),     Token::data(0x04),   Token::data(0x0D),
                                    Token::data(0x22),    Token::data(0x32),     Token::data(0x28),   Token::data(0x00),
                                    Token::data(0x00),    Token::data(0x00),     Token::data(0x00),   Token::end()};

    std::chrono::microseconds now = {};
    static const auto printTime = [](const std::chrono::microseconds us)
    {
        return std::to_string(us.count() / 1000) + "." + std::to_string((us.count() / 100) % 10) + std::to_string((us.count() / 10) % 10) +
               std::to_string((us.count() / 1) % 10) + "ms";
    };
    static const auto printByte = [](const std::optional<std::uint8_t> b)
    { return b ? catta::tostring::toString(catta::Hexadecimal(b.value())) : std::string("{}"); };
    static const auto printTokenVec = [](const TokenVec& v)
    {
        std::string s = "[";
        for (std::size_t i = 0; i < v.size(); i++) s += catta::tostring::toString(v[i]) + (i + 1 < v.size() ? std::string(",") : std::string());
        return s + "]";
    };
    static const auto printByteVec = [](const ByteVec& v)
    {
        std::string s = "[";
        for (std::size_t i = 0; i < v.size(); i++)
            s += catta::tostring::toString(catta::Hexadecimal(v[i])) + (i + 1 < v.size() ? std::string(",") : std::string());
        return s + "]";
    };
    catta::modbus::Uart uart;
    const auto check = [&now, &uart, &test](const TokenVec& sendInput, const ByteVec& sendOutputExpected, const ByteVec& receiveInput,
                                            const TokenVec& receiveOutputExpected)
    {
        ByteVec sendOutput;
        if (debug) test.status("send[token]: " + printTokenVec(sendInput));
        for (const auto& s : sendInput)
        {
            const auto handle = [&now, &uart, &test, &s, &sendOutput](const catta::parser::InputHandled handledExpected)
            {
                const auto [state, token, send, handled] = uart.work(now, std::optional<std::uint8_t>{}, s);
                if (debug)
                    test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) +
                                "," + catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", {}, " +
                                catta::tostring::toString(s) + ")");
                if (!state.isSend()) return test.failedExpected(State::send(), state, "send state");
                if (!token.isEmpty()) return test.failedExpected(Token::empty(), token, "send token");
                if (send) sendOutput.push_back(send.value());
                if (handled != handledExpected) return test.failedExpected(handledExpected, handled, "send handled");
                now += std::chrono::microseconds{200};
                return true;
            };
            if (s.type().isEnd() && !handle(catta::parser::InputHandled::no())) return false;
            if (!handle(catta::parser::InputHandled::yes())) return false;
        }
        if (debug) test.status("send[bytes]: " + printByteVec(sendOutput));
        if (sendOutput != sendOutputExpected)
        {
            test.failed("Expected " + printByteVec(sendOutputExpected) + " as send output,");
            test.failed("but got  " + printByteVec(sendOutput) + ".");
            return false;
        }
        if (debug) test.status("receive[bytes]: " + printByteVec(receiveInput));
        TokenVec receiveOutput;
        for (const auto& r : receiveInput)
        {
            const auto [state, token, send, handled] = uart.work(now, r, Token::empty());
            if (debug)
                test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) + "," +
                            catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", " + printByte(r) + ", " +
                            catta::tostring::toString(Token::empty()) + ")");
            if (!state.isReceive()) return test.failedExpected(State::receive(), state, "receive state");
            if (!token.isEmpty()) receiveOutput.push_back(token);
            if (send)
            {
                test.failed("Expected " + printByte(std::optional<std::uint8_t>()) + " as receive output,");
                test.failed("but got  " + printByte(send) + ".");
                return false;
            }
            if (handled) return test.failedExpected(catta::parser::InputHandled::no(), handled, "receive handled");
            now += std::chrono::microseconds{200};
        }
        if (debug) test.status("receive[token]: " + printTokenVec(receiveOutput));
        if (receiveOutput != receiveOutputExpected)
        {
            test.failed("Expected " + printTokenVec(receiveOutputExpected) + " as receive output,");
            test.failed("but got  " + printTokenVec(receiveOutput) + ".");
            return false;
        }

        now = std::chrono::microseconds((now.count() / 1000 + 2) * 1000);
        const auto [state, token, send, handled] = uart.work(now, std::optional<std::uint8_t>(), Token::empty());
        if (debug)
            test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) + "," +
                        catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", {}, " +
                        catta::tostring::toString(Token::empty()) + ")");
        if (!state.isIdle()) return test.failedExpected(State::idle(), state, "idle state");
        if (!token.isEmpty()) return test.failedExpected(Token::empty(), token, "idle token");
        if (send)
        {
            test.failed("Expected " + printByte(std::optional<std::uint8_t>()) + " as receive output,");
            test.failed("but got  " + printByte(send) + ".");
            return false;
        }
        return true;
    };
    if (!check(sendInput, sendOutput, receiveInput, receiveOutput)) return false;
    return true;
}

int main()
{
    using Output = catta::test::ConsoleOutput;
    Output output("catta::modbus::Uart");
    const auto test_error_cases = checkCases<Output>;
    int error = 0;
    if (!catta::test::execute<Output>(test_error_cases, "error_cases", output)) error++;
    return error;
}
