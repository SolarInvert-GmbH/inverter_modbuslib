#pragma once

// si
#include <catta/modbus/si/State.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::State>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::State;
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
                    _state = INITLEVEL1 + 0;
                    break;
                case 1:
                    _state = INITLEVEL2 + 0;
                    break;
                case 2:
                    _state = INITLEVEL3 + 0;
                    break;
                case 3:
                    _state = MPPT + 0;
                    break;
                case 4:
                    _state = RESET + 0;
                    break;
                case 5:
                    _state = CONSTANTVOLTAGE + 0;
                    break;
                case 6:
                    _state = LOWERPOWERMODE + 0;
                    break;
                case 7:
                    _state = WIND + 0;
                    break;
                case 8:
                    _state = FACTORYMODE + 0;
                    break;
                case 9:
                    _state = BATTERY + 0;
                    break;
                default:
                    _state = BATTERYSAFETY + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return start(catta::json::Token::openString());
            case INITLEVEL1 + 0:
                return next(catta::json::Token::character('i'));
            case INITLEVEL1 + 1:
                return next(catta::json::Token::character('n'));
            case INITLEVEL1 + 2:
                return next(catta::json::Token::character('i'));
            case INITLEVEL1 + 3:
                return next(catta::json::Token::character('t'));
            case INITLEVEL1 + 4:
                return next(catta::json::Token::character(' '));
            case INITLEVEL1 + 5:
                return next(catta::json::Token::character('l'));
            case INITLEVEL1 + 6:
                return next(catta::json::Token::character('e'));
            case INITLEVEL1 + 7:
                return next(catta::json::Token::character('v'));
            case INITLEVEL1 + 8:
                return next(catta::json::Token::character('e'));
            case INITLEVEL1 + 9:
                return next(catta::json::Token::character('l'));
            case INITLEVEL1 + 10:
                return next(catta::json::Token::character(' '));
            case INITLEVEL1 + 11:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case INITLEVEL2 + 0:
                return next(catta::json::Token::character('i'));
            case INITLEVEL2 + 1:
                return next(catta::json::Token::character('n'));
            case INITLEVEL2 + 2:
                return next(catta::json::Token::character('i'));
            case INITLEVEL2 + 3:
                return next(catta::json::Token::character('t'));
            case INITLEVEL2 + 4:
                return next(catta::json::Token::character(' '));
            case INITLEVEL2 + 5:
                return next(catta::json::Token::character('l'));
            case INITLEVEL2 + 6:
                return next(catta::json::Token::character('e'));
            case INITLEVEL2 + 7:
                return next(catta::json::Token::character('v'));
            case INITLEVEL2 + 8:
                return next(catta::json::Token::character('e'));
            case INITLEVEL2 + 9:
                return next(catta::json::Token::character('l'));
            case INITLEVEL2 + 10:
                return next(catta::json::Token::character(' '));
            case INITLEVEL2 + 11:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case INITLEVEL3 + 0:
                return next(catta::json::Token::character('i'));
            case INITLEVEL3 + 1:
                return next(catta::json::Token::character('n'));
            case INITLEVEL3 + 2:
                return next(catta::json::Token::character('i'));
            case INITLEVEL3 + 3:
                return next(catta::json::Token::character('t'));
            case INITLEVEL3 + 4:
                return next(catta::json::Token::character(' '));
            case INITLEVEL3 + 5:
                return next(catta::json::Token::character('l'));
            case INITLEVEL3 + 6:
                return next(catta::json::Token::character('e'));
            case INITLEVEL3 + 7:
                return next(catta::json::Token::character('v'));
            case INITLEVEL3 + 8:
                return next(catta::json::Token::character('e'));
            case INITLEVEL3 + 9:
                return next(catta::json::Token::character('l'));
            case INITLEVEL3 + 10:
                return next(catta::json::Token::character(' '));
            case INITLEVEL3 + 11:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case MPPT + 0:
                return next(catta::json::Token::character('m'));
            case MPPT + 1:
                return next(catta::json::Token::character('p'));
            case MPPT + 2:
                return next(catta::json::Token::character('p'));
            case MPPT + 3:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case RESET + 0:
                return next(catta::json::Token::character('r'));
            case RESET + 1:
                return next(catta::json::Token::character('e'));
            case RESET + 2:
                return next(catta::json::Token::character('s'));
            case RESET + 3:
                return next(catta::json::Token::character('e'));
            case RESET + 4:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case CONSTANTVOLTAGE + 0:
                return next(catta::json::Token::character('c'));
            case CONSTANTVOLTAGE + 1:
                return next(catta::json::Token::character('o'));
            case CONSTANTVOLTAGE + 2:
                return next(catta::json::Token::character('n'));
            case CONSTANTVOLTAGE + 3:
                return next(catta::json::Token::character('s'));
            case CONSTANTVOLTAGE + 4:
                return next(catta::json::Token::character('t'));
            case CONSTANTVOLTAGE + 5:
                return next(catta::json::Token::character('a'));
            case CONSTANTVOLTAGE + 6:
                return next(catta::json::Token::character('n'));
            case CONSTANTVOLTAGE + 7:
                return next(catta::json::Token::character('t'));
            case CONSTANTVOLTAGE + 8:
                return next(catta::json::Token::character(' '));
            case CONSTANTVOLTAGE + 9:
                return next(catta::json::Token::character('v'));
            case CONSTANTVOLTAGE + 10:
                return next(catta::json::Token::character('o'));
            case CONSTANTVOLTAGE + 11:
                return next(catta::json::Token::character('l'));
            case CONSTANTVOLTAGE + 12:
                return next(catta::json::Token::character('t'));
            case CONSTANTVOLTAGE + 13:
                return next(catta::json::Token::character('a'));
            case CONSTANTVOLTAGE + 14:
                return next(catta::json::Token::character('g'));
            case CONSTANTVOLTAGE + 15:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case LOWERPOWERMODE + 0:
                return next(catta::json::Token::character('l'));
            case LOWERPOWERMODE + 1:
                return next(catta::json::Token::character('o'));
            case LOWERPOWERMODE + 2:
                return next(catta::json::Token::character('w'));
            case LOWERPOWERMODE + 3:
                return next(catta::json::Token::character('e'));
            case LOWERPOWERMODE + 4:
                return next(catta::json::Token::character('r'));
            case LOWERPOWERMODE + 5:
                return next(catta::json::Token::character(' '));
            case LOWERPOWERMODE + 6:
                return next(catta::json::Token::character('p'));
            case LOWERPOWERMODE + 7:
                return next(catta::json::Token::character('o'));
            case LOWERPOWERMODE + 8:
                return next(catta::json::Token::character('w'));
            case LOWERPOWERMODE + 9:
                return next(catta::json::Token::character('e'));
            case LOWERPOWERMODE + 10:
                return next(catta::json::Token::character('r'));
            case LOWERPOWERMODE + 11:
                return next(catta::json::Token::character(' '));
            case LOWERPOWERMODE + 12:
                return next(catta::json::Token::character('m'));
            case LOWERPOWERMODE + 13:
                return next(catta::json::Token::character('o'));
            case LOWERPOWERMODE + 14:
                return next(catta::json::Token::character('d'));
            case LOWERPOWERMODE + 15:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case WIND + 0:
                return next(catta::json::Token::character('w'));
            case WIND + 1:
                return next(catta::json::Token::character('i'));
            case WIND + 2:
                return next(catta::json::Token::character('n'));
            case WIND + 3:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case FACTORYMODE + 0:
                return next(catta::json::Token::character('f'));
            case FACTORYMODE + 1:
                return next(catta::json::Token::character('a'));
            case FACTORYMODE + 2:
                return next(catta::json::Token::character('c'));
            case FACTORYMODE + 3:
                return next(catta::json::Token::character('t'));
            case FACTORYMODE + 4:
                return next(catta::json::Token::character('o'));
            case FACTORYMODE + 5:
                return next(catta::json::Token::character('r'));
            case FACTORYMODE + 6:
                return next(catta::json::Token::character('y'));
            case FACTORYMODE + 7:
                return next(catta::json::Token::character(' '));
            case FACTORYMODE + 8:
                return next(catta::json::Token::character('m'));
            case FACTORYMODE + 9:
                return next(catta::json::Token::character('o'));
            case FACTORYMODE + 10:
                return next(catta::json::Token::character('d'));
            case FACTORYMODE + 11:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case BATTERY + 0:
                return next(catta::json::Token::character('b'));
            case BATTERY + 1:
                return next(catta::json::Token::character('a'));
            case BATTERY + 2:
                return next(catta::json::Token::character('t'));
            case BATTERY + 3:
                return next(catta::json::Token::character('t'));
            case BATTERY + 4:
                return next(catta::json::Token::character('e'));
            case BATTERY + 5:
                return next(catta::json::Token::character('r'));
            case BATTERY + 6:
                return jump(catta::json::Token::character('y'), TAIL + 0);
            case BATTERYSAFETY + 0:
                return next(catta::json::Token::character('b'));
            case BATTERYSAFETY + 1:
                return next(catta::json::Token::character('a'));
            case BATTERYSAFETY + 2:
                return next(catta::json::Token::character('t'));
            case BATTERYSAFETY + 3:
                return next(catta::json::Token::character('t'));
            case BATTERYSAFETY + 4:
                return next(catta::json::Token::character('e'));
            case BATTERYSAFETY + 5:
                return next(catta::json::Token::character('r'));
            case BATTERYSAFETY + 6:
                return next(catta::json::Token::character('y'));
            case BATTERYSAFETY + 7:
                return next(catta::json::Token::character(' '));
            case BATTERYSAFETY + 8:
                return next(catta::json::Token::character('s'));
            case BATTERYSAFETY + 9:
                return next(catta::json::Token::character('a'));
            case BATTERYSAFETY + 10:
                return next(catta::json::Token::character('f'));
            case BATTERYSAFETY + 11:
                return next(catta::json::Token::character('e'));
            case BATTERYSAFETY + 12:
                return next(catta::json::Token::character('t'));
            case BATTERYSAFETY + 13:
                return jump(catta::json::Token::character('y'), TAIL + 0);
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
    static constexpr std::uint8_t INITLEVEL1 = START + 1;
    static constexpr std::uint8_t INITLEVEL2 = INITLEVEL1 + 12;
    static constexpr std::uint8_t INITLEVEL3 = INITLEVEL2 + 12;
    static constexpr std::uint8_t MPPT = INITLEVEL3 + 12;
    static constexpr std::uint8_t RESET = MPPT + 4;
    static constexpr std::uint8_t CONSTANTVOLTAGE = RESET + 5;
    static constexpr std::uint8_t LOWERPOWERMODE = CONSTANTVOLTAGE + 16;
    static constexpr std::uint8_t WIND = LOWERPOWERMODE + 16;
    static constexpr std::uint8_t FACTORYMODE = WIND + 4;
    static constexpr std::uint8_t BATTERY = FACTORYMODE + 12;
    static constexpr std::uint8_t BATTERYSAFETY = BATTERY + 7;
    static constexpr std::uint8_t TAIL = BATTERYSAFETY + 14;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
