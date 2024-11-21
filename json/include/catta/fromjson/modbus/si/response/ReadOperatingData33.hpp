#pragma once

// response
#include <catta/modbus/si/response/ReadOperatingData33.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/State.hpp>
#include <catta/fromjson/modbus/sunspec/ValueS16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::ReadOperatingData33>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::ReadOperatingData33;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto isInEndState = [](auto parser)
        {
            [[maybe_unused]] auto ignore = parser.read(catta::json::Token::end());
            return parser.state().isDone();
        };
        const auto handle = [stay, jump, error, input, isInEndState](auto& parser)
        {
            const auto close = catta::json::Token::closeCurlyBracket();
            const auto again = catta::json::Token::comma();
            const auto token = (input == close || input == again) && isInEndState(parser) ? catta::json::Token::end() : input;
            [[maybe_unused]] auto ignore = parser.read(token);
            if (parser.state().isFailed()) return error();
            if (parser.state().isDone()) return jump(input == close ? TAIL + 0 : HUB + 0);
            return stay();
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('s')   ? jump(HUB + 46)
                       : input == catta::json::Token::character('g') ? jump(HUB + 31)
                       : input == catta::json::Token::character('d') ? jump(HUB + 20)
                       : input == catta::json::Token::character('a') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('c') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('V')   ? jump(HUB + 11)
                       : input == catta::json::Token::character('P') ? jump(HUB + 4)
                                                                     : error();
            case HUB + 4:
                return input == catta::json::Token::character('o') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('w') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('e') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('r') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::closeString() ? jump(HUB + 9) : error();
            case HUB + 9:
                return !_acPowerParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 10:
                return handle(_acPowerParser);
            case HUB + 11:
                return input == catta::json::Token::character('o') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('l') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('t') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('a') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('g') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('e') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::closeString() ? jump(HUB + 18) : error();
            case HUB + 18:
                return !_acVoltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 19:
                return handle(_acVoltageParser);
            case HUB + 20:
                return input == catta::json::Token::character('c') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('V') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('o') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('l') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('t') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('a') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('g') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('e') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::closeString() ? jump(HUB + 29) : error();
            case HUB + 29:
                return !_dcVoltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 30:
                return handle(_dcVoltageParser);
            case HUB + 31:
                return input == catta::json::Token::character('r') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('i') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('d') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('F') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('r') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('e') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('q') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('u') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('e') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('n') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('c') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('y') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::closeString() ? jump(HUB + 44) : error();
            case HUB + 44:
                return !_gridFrequencyParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 45:
                return handle(_gridFrequencyParser);
            case HUB + 46:
                return input == catta::json::Token::character('t') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('a') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('t') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('e') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::closeString() ? jump(HUB + 51) : error();
            case HUB + 51:
                return !_stateParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 52:
                return handle(_stateParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_dcVoltageParser.data(), _acVoltageParser.data(), _gridFrequencyParser.data(), _acPowerParser.data(),
                                               _stateParser.data())
                              : Output::empty();
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    Parser<catta::modbus::sunspec::ValueS16> _acPowerParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 255>> _acVoltageParser;
    Parser<catta::modbus::sunspec::ValueU16> _dcVoltageParser;
    Parser<catta::modbus::sunspec::ValueU16> _gridFrequencyParser;
    Parser<catta::modbus::si::State> _stateParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 53;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
