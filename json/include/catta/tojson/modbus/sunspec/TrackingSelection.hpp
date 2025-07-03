#pragma once

// sunspec
#include <catta/modbus/sunspec/TrackingSelection.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::TrackingSelection>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::TrackingSelection;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _data = catta::json::Token::end();
            _state = DONE + 0;
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this](const catta::json::Token token)
        {
            _data = token;
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto next = [stay, this](const catta::json::Token token)
        {
            _state++;
            return stay(token);
        };
        const auto jump = [stay, this](const catta::json::Token token, const std::uint8_t state)
        {
            _state = state;
            return stay(token);
        };
        const auto start = [stay, this, input](const catta::json::Token token)
        {
            switch (input)
            {
                case 0:
                    _state = CHARGE_TO_U_SOLAR_BATTERY_ERROR + 0;
                    break;
                case 1:
                    _state = SWITCH_OFF + 0;
                    break;
                default:
                    _state = CHARGE_TO_U_MAX + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? jump(catta::json::Token::nullObject(), TAIL + 1) : start(catta::json::Token::openString());
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 0:
                return next(catta::json::Token::character('c'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 1:
                return next(catta::json::Token::character('h'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 2:
                return next(catta::json::Token::character('a'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 3:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 4:
                return next(catta::json::Token::character('g'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 5:
                return next(catta::json::Token::character('e'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 6:
                return next(catta::json::Token::character('T'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 7:
                return next(catta::json::Token::character('o'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 8:
                return next(catta::json::Token::character('U'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 9:
                return next(catta::json::Token::character('S'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 10:
                return next(catta::json::Token::character('o'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 11:
                return next(catta::json::Token::character('l'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 12:
                return next(catta::json::Token::character('a'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 13:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 14:
                return next(catta::json::Token::character('B'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 15:
                return next(catta::json::Token::character('a'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 16:
                return next(catta::json::Token::character('t'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 17:
                return next(catta::json::Token::character('t'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 18:
                return next(catta::json::Token::character('e'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 19:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 20:
                return next(catta::json::Token::character('y'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 21:
                return next(catta::json::Token::character('E'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 22:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 23:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 24:
                return next(catta::json::Token::character('o'));
            case CHARGE_TO_U_SOLAR_BATTERY_ERROR + 25:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case SWITCH_OFF + 0:
                return next(catta::json::Token::character('s'));
            case SWITCH_OFF + 1:
                return next(catta::json::Token::character('w'));
            case SWITCH_OFF + 2:
                return next(catta::json::Token::character('i'));
            case SWITCH_OFF + 3:
                return next(catta::json::Token::character('t'));
            case SWITCH_OFF + 4:
                return next(catta::json::Token::character('c'));
            case SWITCH_OFF + 5:
                return next(catta::json::Token::character('h'));
            case SWITCH_OFF + 6:
                return next(catta::json::Token::character('O'));
            case SWITCH_OFF + 7:
                return next(catta::json::Token::character('f'));
            case SWITCH_OFF + 8:
                return jump(catta::json::Token::character('f'), TAIL + 0);
            case CHARGE_TO_U_MAX + 0:
                return next(catta::json::Token::character('c'));
            case CHARGE_TO_U_MAX + 1:
                return next(catta::json::Token::character('h'));
            case CHARGE_TO_U_MAX + 2:
                return next(catta::json::Token::character('a'));
            case CHARGE_TO_U_MAX + 3:
                return next(catta::json::Token::character('r'));
            case CHARGE_TO_U_MAX + 4:
                return next(catta::json::Token::character('g'));
            case CHARGE_TO_U_MAX + 5:
                return next(catta::json::Token::character('e'));
            case CHARGE_TO_U_MAX + 6:
                return next(catta::json::Token::character('T'));
            case CHARGE_TO_U_MAX + 7:
                return next(catta::json::Token::character('o'));
            case CHARGE_TO_U_MAX + 8:
                return next(catta::json::Token::character('U'));
            case CHARGE_TO_U_MAX + 9:
                return next(catta::json::Token::character('M'));
            case CHARGE_TO_U_MAX + 10:
                return next(catta::json::Token::character('a'));
            case CHARGE_TO_U_MAX + 11:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case TAIL + 0:
                return next(catta::json::Token::closeString());
            case TAIL + 1:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _data(Output::empty()) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    catta::json::Token _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t CHARGE_TO_U_SOLAR_BATTERY_ERROR = START + 1;
    static constexpr std::uint8_t SWITCH_OFF = CHARGE_TO_U_SOLAR_BATTERY_ERROR + 26;
    static constexpr std::uint8_t CHARGE_TO_U_MAX = SWITCH_OFF + 9;
    static constexpr std::uint8_t TAIL = CHARGE_TO_U_MAX + 12;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
