// catta
#include <catta/modbus/ValueCache.hpp>

// tostring
#include <catta/tostring/Decimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

// std
#include <optional>

static constexpr bool debug = false;

namespace catta
{
namespace tostring
{
template <>
class Serializer<std::optional<catta::modbus::si::response::Response>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = std::optional<catta::modbus::si::response::Response>;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const Tuple result = Tuple{Error::empty(), catta::parser::InputHandled::no()};
        const auto runing = [this, input]()
        {
            _state = RUNNING;
            return _serializer.read(input.value());
        };
        const auto character = [this, result](const char c, const std::uint8_t state)
        {
            _state = state;
            _data = c;
            return result;
        };
        const auto tail = [this]()
        {
            _state = DONE;
            _data = '\0';
            return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
        };
        switch (_state)
        {
            case START:
                return input ? runing() : character('V', VOID + 0);
            case RUNNING:
                return runing();
            case VOID + 0:
                return character('O', VOID + 1);
            case VOID + 1:
                return character('I', VOID + 2);
            case VOID + 2:
                return character('D', TAIL);
            case TAIL:
                return tail();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _data('\0'), _state(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == RUNNING ? _serializer.data() : _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return catta::parser::State::start();
            case RUNNING:
                return _serializer.state();
            case VOID + 0:
            case VOID + 1:
            case VOID + 2:
            case TAIL:
                return catta::parser::State::running();
            case DONE:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    char _data;
    Serializer<catta::modbus::si::response::Response> _serializer;
    std::uint8_t _state;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t RUNNING = START + 1;
    static constexpr std::uint8_t VOID = RUNNING + 1;
    static constexpr std::uint8_t TAIL = VOID + 3;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tostring
}  // namespace catta

template <catta::test::Output OUTPUT>
static bool checkWork(catta::test::Test<OUTPUT>& test)
{
    catta::modbus::ValueCache<3> valueCache;

    using Response = catta::modbus::si::response::Response;
    using Request = catta::modbus::si::request::Request;
    using ReadRegister = catta::modbus::si::ReadRegister;
    using RegisterAddress = catta::modbus::si::RegisterAddress;

    static constexpr Request RequestEmp = Request::empty();
    static constexpr Request RequestSca = Request::readRegister(ReadRegister::create(RegisterAddress::inverterAmpsScaleFactor()));
    static constexpr Request RequestPhA = Request::readRegister(ReadRegister::create(RegisterAddress::inverterAmpsPhaseA()));
    static constexpr Request RequestPhB = Request::readRegister(ReadRegister::create(RegisterAddress::inverterAmpsPhaseB()));

    static constexpr bool T = true;
    static constexpr bool N = false;

    static constexpr std::optional<Response> ResponseVoi = std::optional<Response>{};
    static constexpr Response ResponseEmp = Response::empty();
    static constexpr Response ResponseSca = Response::value16(0xfffe);
    static constexpr Response ResponsePA0 = Response::value16(0x00aa);
    static constexpr Response ResponsePA1 = Response::value16(0x0aaa);
    static constexpr Response ResponsePB0 = Response::value16(0x00bb);
    static constexpr Response ResponsePB1 = Response::value16(0x0bbb);

    std::optional<Response> response0;
    std::optional<Response> response1;
    std::optional<Response> response2;

    valueCache.setRequest(0, RequestSca);
    valueCache.setRequest(1, RequestPhA);
    valueCache.setRequest(2, RequestPhB);

    const auto callback0 = [&response0, &test](const Response& response)
    {
        if (debug) test.status("callback0(" + catta::tostring::toString(response) + ")");
        response0 = response;
    };
    const auto callback1 = [&response1, &test](const Response& response)
    {
        if (debug) test.status("callback1(" + catta::tostring::toString(response) + ")");
        response1 = response;
    };
    const auto callback2 = [&response2, &test](const Response& response)
    {
        if (debug) test.status("callback2(" + catta::tostring::toString(response) + ")");
        response2 = response;
    };

    valueCache.setCallback(0, callback0);
    valueCache.setCallback(1, callback1);
    valueCache.setCallback(2, callback2);

    valueCache.setValidTime(1, std::chrono::seconds{1});
    valueCache.setValidTime(2, std::chrono::seconds{1});

    const auto check = [&valueCache, &response0, &response1, &response2, &test](
                           const bool canTakeRequest, const Response& response, const Request& request, const Request& expectedResult,
                           const std::optional<Response>& expectedResponse0, const std::optional<Response>& expectedResponse1,
                           const std::optional<Response>& expectedResponse2, const std::int64_t now)
    {
        response0 = {};
        response1 = {};
        response2 = {};
        if (debug)
            test.status(std::string("work(") + (canTakeRequest ? "0" : "1") + ", " + catta::tostring::toString(response) + ", " +
                        catta::tostring::toString(request) + ", " + std::to_string(now) + " ms)");
        const auto result = valueCache.work(canTakeRequest, response, request, std::chrono::microseconds{now * 1000});
        if (expectedResult != result) return test.failedExpected(expectedResult, result, "work result");
        if (expectedResponse0 != response0) return test.failedExpected(expectedResponse0, response0, "callback result0");
        if (expectedResponse1 != response1) return test.failedExpected(expectedResponse1, response1, "callback result1");
        if (expectedResponse2 != response2) return test.failedExpected(expectedResponse2, response2, "callback result2");
        if (debug) test.status(std::string("  => ") + catta::tostring::toString(result));
        return true;
    };

    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 0)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestSca, ResponseVoi, ResponseVoi, ResponseVoi, 10)) return false;
    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 20)) return false;
    if (!check(T, ResponseSca, RequestSca, RequestPhA, ResponseSca, ResponseVoi, ResponseVoi, 30)) return false;
    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 40)) return false;
    if (!check(T, ResponsePA0, RequestPhA, RequestPhB, ResponseVoi, ResponsePA0, ResponseVoi, 50)) return false;
    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 60)) return false;
    if (!check(T, ResponsePB0, RequestPhB, RequestEmp, ResponseVoi, ResponseVoi, ResponsePB0, 70)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 300)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestPhA, ResponseVoi, ResponseVoi, ResponseVoi, 301)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestPhB, ResponseVoi, ResponseVoi, ResponseVoi, 321)) return false;
    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseVoi, ResponseVoi, 1050)) return false;
    if (!check(N, ResponseEmp, RequestEmp, RequestEmp, ResponseVoi, ResponseEmp, ResponseVoi, 1051)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestPhA, ResponseVoi, ResponseVoi, ResponseVoi, 1052)) return false;
    if (!check(N, ResponsePA1, RequestPhA, RequestEmp, ResponseVoi, ResponsePA1, ResponseVoi, 1053)) return false;
    if (!check(T, ResponseEmp, RequestEmp, RequestPhB, ResponseVoi, ResponseVoi, ResponseVoi, 1054)) return false;
    if (!check(N, ResponsePB1, RequestPhB, RequestEmp, ResponseVoi, ResponseVoi, ResponsePB1, 1053)) return false;

    return true;
}

int main()
{
    using Output = catta::test::ConsoleOutput;
    Output output("catta::modbus::ValueCache");
    const auto test_work = checkWork<Output>;
    int error = 0;
    if (!catta::test::execute<Output>(test_work, "work", output)) error++;
    return error;
}
