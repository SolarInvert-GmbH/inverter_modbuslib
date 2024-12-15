#pragma once

// request
#include <catta/modbus/si/request/ControlBatteryInvert.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/PowerConfig.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::request::ControlBatteryInvert>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::request::ControlBatteryInvert;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
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
                return input == catta::json::Token::character('u')   ? jump(HUB + 17)
                       : input == catta::json::Token::character('t') ? jump(HUB + 8)
                       : input == catta::json::Token::character('p') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('M') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('a') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('x') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::closeString() ? jump(HUB + 6) : error();
            case HUB + 6:
                return !_pMaxParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 7:
                return handle(_pMaxParser);
            case HUB + 8:
                return input == catta::json::Token::character('i') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('m') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('e') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('o') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('u') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('t') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::closeString() ? jump(HUB + 15) : error();
            case HUB + 15:
                return !_timeoutParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 16:
                return handle(_timeoutParser);
            case HUB + 17:
                return input == catta::json::Token::character('M') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('i')   ? jump(HUB + 23)
                       : input == catta::json::Token::character('a') ? jump(HUB + 19)
                                                                     : error();
            case HUB + 19:
                return input == catta::json::Token::character('x') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::closeString() ? jump(HUB + 21) : error();
            case HUB + 21:
                return !_uMaxParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 22:
                return handle(_uMaxParser);
            case HUB + 23:
                return input == catta::json::Token::character('n') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::closeString() ? jump(HUB + 25) : error();
            case HUB + 25:
                return !_uMinParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 26:
                return handle(_uMinParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_pMaxParser.data(), _uMinParser.data(), _uMaxParser.data(), _timeoutParser.data()) : Output::empty();
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
    Parser<catta::modbus::si::PowerConfig> _pMaxParser;
    Parser<catta::modbus::sunspec::ValueU16> _timeoutParser;
    Parser<catta::modbus::sunspec::ValueU16> _uMaxParser;
    Parser<catta::modbus::sunspec::ValueU16> _uMinParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 27;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
