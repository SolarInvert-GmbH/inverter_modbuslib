// catta
#include <catta/modbus/MasterUart.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/MasterUartState.hpp>
#include <catta/tostring/modbus/Token.hpp>
#include <catta/tostring/parser/InputHandled.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkCases(catta::test::Test<OUTPUT>& test)
{
    using Byte = std::optional<std::uint8_t>;
    using State = catta::modbus::MasterUartState;
    using Token = catta::modbus::Token;
    using TokenVec = std::vector<Token>;
    using ByteVec = std::vector<std::uint8_t>;
    const TokenVec sendInput0 = {Token::start(), Token::function(0x31), Token::data(0x01), Token::data(0x01), Token::end()};
    const ByteVec sendOutput0 = {0x01, 0x31, 0x01, 0x01, 0x90, 0x47};
    const ByteVec receiveInput0 = {0x01, 0x31, 0x0c, 0x00, 0x01, 0x1E, 0x04, 0x0d, 0x22, 0x32, 0x28, 0x00, 0x00, 0x00, 0x00, 0x51, 0x51};
    const TokenVec receiveOutput0 = {Token::start(),    Token::function(0x31), Token::data(0x0c), Token::data(0x00),
                                     Token::data(0x01), Token::data(0x1E),     Token::data(0x04), Token::data(0x0D),
                                     Token::data(0x22), Token::data(0x32),     Token::data(0x28), Token::data(0x00),
                                     Token::data(0x00), Token::data(0x00),     Token::data(0x00), Token::end()};
    const TokenVec sendInput1 = {Token::start(),    Token::function(0x16), Token::data(0x9c), Token::data(0x40), Token::data(0x00),
                                 Token::data(0x00), Token::data(0xaf),     Token::data(0xfe), Token::end()};
    const ByteVec sendOutput1 = {0x01, 0x16, 0x9c, 0x40, 0x00, 0x00, 0xaf, 0xfe, 0x16, 0x25};
    const ByteVec receiveInput1 = sendOutput1;
    const TokenVec receiveOutput1 = sendInput1;

    std::chrono::microseconds now = {};
    static const auto printTime = [](const std::chrono::microseconds us)
    {
        return std::to_string(us.count() / 1000) + "." + std::to_string((us.count() / 100) % 10) + std::to_string((us.count() / 10) % 10) +
               std::to_string((us.count() / 1) % 10) + "ms";
    };
    static const auto printByte = [](const Byte b) { return b ? catta::tostring::toString(catta::Hexadecimal(b.value())) : std::string("{}"); };
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
    catta::modbus::MasterUart uart;
    const auto checkNormal = [&now, &uart, &test](const std::uint8_t address, const TokenVec& sendInput, const ByteVec& sendOutputExpected,
                                                  const ByteVec& receiveInput, const TokenVec& receiveOutputExpected,
                                                  const catta::modbus::MasterUartState error = catta::modbus::MasterUartState::empty())
    {
        ByteVec sendOutput;
        if (debug)
        {
            test.status(error.isEmpty() ? "Success case:" : catta::tostring::toString(error) + " case:");
            test.status("  send[token]: " + printTokenVec(sendInput));
        }
        const auto errorCase = [&test, &uart, &now, error, address](const Token inToken, const Byte inByte)
        {
            {
                const auto [state, token, send, handled] = uart.work(now, inByte, inToken, address);
                if (debug)
                    test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) +
                                "," + catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", " + printByte(inByte) + ", " +
                                catta::tostring::toString(inToken) + "," + catta::tostring::toString(catta::Hexadecimal(address)) + ")");
                if (state != error) return test.failedExpected(error, state, catta::tostring::toString(error) + " state");
                if (!token.isEmpty()) return test.failedExpected(Token::empty(), token, catta::tostring::toString(error) + " token");
                if (send)
                {
                    test.failed("Expected " + printByte(Byte()) + " as " + catta::tostring::toString(error) + " output,");
                    test.failed("but got  " + printByte(send) + ".");
                    return false;
                }
                if (handled != catta::parser::InputHandled::yes())
                    return test.failedExpected(catta::parser::InputHandled::yes(), handled, catta::tostring::toString(error) + " handled");
            }
            now = std::chrono::microseconds((now.count() / 1000000 + 6) * 1000000);
            const auto [state, token, send, handled] = uart.work(now, Byte(), Token::empty(), address);
            if (debug)
                test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) + "," +
                            catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", {}, " +
                            catta::tostring::toString(Token::empty()) + "," + catta::tostring::toString(catta::Hexadecimal(address)) + ")");
            if (!state.isIdle()) return test.failedExpected(State::idle(), state, "idle state");
            if (!token.isEmpty()) return test.failedExpected(Token::empty(), token, "idle token");
            if (send)
            {
                test.failed("Expected " + printByte(Byte()) + " as receive output,");
                test.failed("but got  " + printByte(send) + ".");
                return false;
            }
            return true;
        };
        if (error.isErrorSendInvalid()) return errorCase(Token::function(0x00), {});
        if (error.isErrorReceiveWithoutReuquest()) return errorCase(Token::empty(), Byte{0x00});
        for (const auto& s : sendInput)
        {
            const auto handle = [&now, &uart, &test, &s, &sendOutput, address](const catta::parser::InputHandled handledExpected)
            {
                const auto [state, token, send, handled] = uart.work(now, Byte{}, s, address);
                if (debug)
                    test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) +
                                "," + catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", {}, " +
                                catta::tostring::toString(s) + "," + catta::tostring::toString(catta::Hexadecimal(address)) + ")");
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
        if (debug) test.status("  send[bytes]: " + printByteVec(sendOutput));
        if (sendOutput != sendOutputExpected)
        {
            test.failed("Expected " + printByteVec(sendOutputExpected) + " as send output,");
            test.failed("but got  " + printByteVec(sendOutput) + ".");
            return false;
        }
        if (debug) test.status("  receive[bytes]: " + printByteVec(receiveInput));
        TokenVec receiveOutput;
        if (error.isErrorReceiveTimeoutNoResponse())
        {
            now += std::chrono::milliseconds{600};
            return errorCase(Token::empty(), {});
        }
        for (std::size_t i = 0; i < receiveInput.size(); i++)
        {
            if (error.isErrorReceiveLengthNotValid() && i == 2) return errorCase(Token::empty(), Byte{0xff});
            if (error.isErrorReceiveWrongCrc() && i + 2 == receiveInput.size()) return errorCase(Token::empty(), Byte{~receiveInput[i]});
            if (error.isErrorReceiveTimeoutPartialResponse() && i == 2)
            {
                now += std::chrono::microseconds{600};
                return errorCase(Token::empty(), {});
            }
            const auto [state, token, send, handled] = uart.work(now, receiveInput[i], Token::empty(), address);
            if (debug)
                test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) + "," +
                            catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", " + printByte(receiveInput[i]) + ", " +
                            catta::tostring::toString(Token::empty()) + "," + catta::tostring::toString(catta::Hexadecimal(address)) + ")");
            if (!state.isReceive()) return test.failedExpected(State::receive(), state, "receive state");
            if (!token.isEmpty()) receiveOutput.push_back(token);
            if (send)
            {
                test.failed("Expected " + printByte(Byte()) + " as receive output,");
                test.failed("but got  " + printByte(send) + ".");
                return false;
            }
            if (handled) return test.failedExpected(catta::parser::InputHandled::no(), handled, "receive handled");
            now += std::chrono::microseconds{200};
        }
        if (debug) test.status("  receive[token]: " + printTokenVec(receiveOutput));
        if (receiveOutput != receiveOutputExpected)
        {
            test.failed("Expected " + printTokenVec(receiveOutputExpected) + " as receive output,");
            test.failed("but got  " + printTokenVec(receiveOutput) + ".");
            return false;
        }

        now = std::chrono::microseconds((now.count() / 1000 + 2) * 1000);
        const auto [state, token, send, handled] = uart.work(now, Byte(), Token::empty(), address);
        if (debug)
            test.status("        [" + catta::tostring::toString(state) + "," + catta::tostring::toString(token) + "," + printByte(send) + "," +
                        catta::tostring::toString(handled) + "] = uart.work(" + printTime(now) + ", {}, " +
                        catta::tostring::toString(Token::empty()) + "," + catta::tostring::toString(catta::Hexadecimal(address)) + ")");
        if (!state.isIdle()) return test.failedExpected(State::idle(), state, "idle state");
        if (!token.isEmpty()) return test.failedExpected(Token::empty(), token, "idle token");
        if (send)
        {
            test.failed("Expected " + printByte(Byte()) + " as receive output,");
            test.failed("but got  " + printByte(send) + ".");
            return false;
        }
        return true;
    };
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0)) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorSendInvalid())) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorReceiveWithoutReuquest())) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorReceiveLengthNotValid())) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorReceiveWrongCrc())) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorReceiveTimeoutNoResponse())) return false;
    if (!checkNormal(0x01, sendInput0, sendOutput0, receiveInput0, receiveOutput0, State::errorReceiveTimeoutPartialResponse())) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1)) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1, State::errorSendInvalid())) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1, State::errorReceiveWithoutReuquest())) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1, State::errorReceiveWrongCrc())) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1, State::errorReceiveTimeoutNoResponse())) return false;
    if (!checkNormal(0x01, sendInput1, sendOutput1, receiveInput1, receiveOutput1, State::errorReceiveTimeoutPartialResponse())) return false;
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
