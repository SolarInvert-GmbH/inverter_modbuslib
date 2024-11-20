#pragma once

// si
#include <catta/modbus/si/Date.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::Date>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::Date;
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
                return input == catta::json::Token::character('y')   ? jump(HUB + 14)
                       : input == catta::json::Token::character('m') ? jump(HUB + 7)
                       : input == catta::json::Token::character('d') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('a') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('y') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::closeString() ? jump(HUB + 5) : error();
            case HUB + 5:
                return !_dayParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 6:
                return handle(_dayParser);
            case HUB + 7:
                return input == catta::json::Token::character('o') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('n') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('t') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('h') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::closeString() ? jump(HUB + 12) : error();
            case HUB + 12:
                return !_monthParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 13:
                return handle(_monthParser);
            case HUB + 14:
                return input == catta::json::Token::character('e') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('a') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('r') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::closeString() ? jump(HUB + 18) : error();
            case HUB + 18:
                return !_yearParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 19:
                return handle(_yearParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_dayParser.data(), _monthParser.data(), _yearParser.data()) : Output::empty();
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
    Parser<catta::modbus::sunspec::ValueU8<1, 31>> _dayParser;
    Parser<catta::modbus::sunspec::ValueU8<1, 12>> _monthParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 99>> _yearParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 20;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
