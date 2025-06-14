#pragma once

// response
#include <catta/modbus/si/response/Type.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::Type>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::Type;
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
        const auto jump = [stay, this](const catta::json::Token token, const std::uint16_t state)
        {
            _state = state;
            return stay(token);
        };
        const auto start = [stay, this, input](const catta::json::Token token)
        {
            switch (input)
            {
                case 0:
                    _state = EXCEPTION + 0;
                    break;
                case 1:
                    _state = FACTORY_VALUES + 0;
                    break;
                case 2:
                    _state = READ_ERROR + 0;
                    break;
                case 3:
                    _state = READ_OPERATING_DATA33 + 0;
                    break;
                case 4:
                    _state = READ_OPERATING_DATA3E + 0;
                    break;
                case 5:
                    _state = SWITCH_OFF_GRID_RELAY + 0;
                    break;
                case 6:
                    _state = SWITCH_ON_GRID_RELAY + 0;
                    break;
                case 7:
                    _state = FORCE_IDLE + 0;
                    break;
                case 8:
                    _state = DEACTIVATE_IDLE + 0;
                    break;
                case 9:
                    _state = START_CONSTANT_VOLTAGE + 0;
                    break;
                case 10:
                    _state = END_CONSTANT_VOLTAGE + 0;
                    break;
                case 11:
                    _state = SET_POWER_FACTOR + 0;
                    break;
                case 12:
                    _state = CONTROL_BATTERY_INVERT + 0;
                    break;
                case 13:
                    _state = LIMIT_BATTERY_INVERT + 0;
                    break;
                case 14:
                    _state = WRITE_REGISTER + 0;
                    break;
                case 15:
                    _state = VALUE16 + 0;
                    break;
                case 16:
                    _state = VALUE32 + 0;
                    break;
                case 17:
                    _state = VALUE64 + 0;
                    break;
                default:
                    _state = STRING + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? jump(catta::json::Token::nullObject(), TAIL + 1) : start(catta::json::Token::openString());
            case EXCEPTION + 0:
                return next(catta::json::Token::character('e'));
            case EXCEPTION + 1:
                return next(catta::json::Token::character('x'));
            case EXCEPTION + 2:
                return next(catta::json::Token::character('c'));
            case EXCEPTION + 3:
                return next(catta::json::Token::character('e'));
            case EXCEPTION + 4:
                return next(catta::json::Token::character('p'));
            case EXCEPTION + 5:
                return next(catta::json::Token::character('t'));
            case EXCEPTION + 6:
                return next(catta::json::Token::character('i'));
            case EXCEPTION + 7:
                return next(catta::json::Token::character('o'));
            case EXCEPTION + 8:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case FACTORY_VALUES + 0:
                return next(catta::json::Token::character('f'));
            case FACTORY_VALUES + 1:
                return next(catta::json::Token::character('a'));
            case FACTORY_VALUES + 2:
                return next(catta::json::Token::character('c'));
            case FACTORY_VALUES + 3:
                return next(catta::json::Token::character('t'));
            case FACTORY_VALUES + 4:
                return next(catta::json::Token::character('o'));
            case FACTORY_VALUES + 5:
                return next(catta::json::Token::character('r'));
            case FACTORY_VALUES + 6:
                return next(catta::json::Token::character('y'));
            case FACTORY_VALUES + 7:
                return next(catta::json::Token::character('V'));
            case FACTORY_VALUES + 8:
                return next(catta::json::Token::character('a'));
            case FACTORY_VALUES + 9:
                return next(catta::json::Token::character('l'));
            case FACTORY_VALUES + 10:
                return next(catta::json::Token::character('u'));
            case FACTORY_VALUES + 11:
                return next(catta::json::Token::character('e'));
            case FACTORY_VALUES + 12:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case READ_ERROR + 0:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 1:
                return next(catta::json::Token::character('e'));
            case READ_ERROR + 2:
                return next(catta::json::Token::character('a'));
            case READ_ERROR + 3:
                return next(catta::json::Token::character('d'));
            case READ_ERROR + 4:
                return next(catta::json::Token::character('E'));
            case READ_ERROR + 5:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 6:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 7:
                return next(catta::json::Token::character('o'));
            case READ_ERROR + 8:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case READ_OPERATING_DATA33 + 0:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA33 + 1:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA33 + 2:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 3:
                return next(catta::json::Token::character('d'));
            case READ_OPERATING_DATA33 + 4:
                return next(catta::json::Token::character('O'));
            case READ_OPERATING_DATA33 + 5:
                return next(catta::json::Token::character('p'));
            case READ_OPERATING_DATA33 + 6:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA33 + 7:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA33 + 8:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 9:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA33 + 10:
                return next(catta::json::Token::character('i'));
            case READ_OPERATING_DATA33 + 11:
                return next(catta::json::Token::character('n'));
            case READ_OPERATING_DATA33 + 12:
                return next(catta::json::Token::character('g'));
            case READ_OPERATING_DATA33 + 13:
                return next(catta::json::Token::character('D'));
            case READ_OPERATING_DATA33 + 14:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 15:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA33 + 16:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 17:
                return next(catta::json::Token::character('3'));
            case READ_OPERATING_DATA33 + 18:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case READ_OPERATING_DATA3E + 0:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA3E + 1:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA3E + 2:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 3:
                return next(catta::json::Token::character('d'));
            case READ_OPERATING_DATA3E + 4:
                return next(catta::json::Token::character('O'));
            case READ_OPERATING_DATA3E + 5:
                return next(catta::json::Token::character('p'));
            case READ_OPERATING_DATA3E + 6:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA3E + 7:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA3E + 8:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 9:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA3E + 10:
                return next(catta::json::Token::character('i'));
            case READ_OPERATING_DATA3E + 11:
                return next(catta::json::Token::character('n'));
            case READ_OPERATING_DATA3E + 12:
                return next(catta::json::Token::character('g'));
            case READ_OPERATING_DATA3E + 13:
                return next(catta::json::Token::character('D'));
            case READ_OPERATING_DATA3E + 14:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 15:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA3E + 16:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 17:
                return next(catta::json::Token::character('3'));
            case READ_OPERATING_DATA3E + 18:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SWITCH_OFF_GRID_RELAY + 0:
                return next(catta::json::Token::character('s'));
            case SWITCH_OFF_GRID_RELAY + 1:
                return next(catta::json::Token::character('w'));
            case SWITCH_OFF_GRID_RELAY + 2:
                return next(catta::json::Token::character('i'));
            case SWITCH_OFF_GRID_RELAY + 3:
                return next(catta::json::Token::character('t'));
            case SWITCH_OFF_GRID_RELAY + 4:
                return next(catta::json::Token::character('c'));
            case SWITCH_OFF_GRID_RELAY + 5:
                return next(catta::json::Token::character('h'));
            case SWITCH_OFF_GRID_RELAY + 6:
                return next(catta::json::Token::character('O'));
            case SWITCH_OFF_GRID_RELAY + 7:
                return next(catta::json::Token::character('f'));
            case SWITCH_OFF_GRID_RELAY + 8:
                return next(catta::json::Token::character('f'));
            case SWITCH_OFF_GRID_RELAY + 9:
                return next(catta::json::Token::character('G'));
            case SWITCH_OFF_GRID_RELAY + 10:
                return next(catta::json::Token::character('r'));
            case SWITCH_OFF_GRID_RELAY + 11:
                return next(catta::json::Token::character('i'));
            case SWITCH_OFF_GRID_RELAY + 12:
                return next(catta::json::Token::character('d'));
            case SWITCH_OFF_GRID_RELAY + 13:
                return next(catta::json::Token::character('R'));
            case SWITCH_OFF_GRID_RELAY + 14:
                return next(catta::json::Token::character('e'));
            case SWITCH_OFF_GRID_RELAY + 15:
                return next(catta::json::Token::character('l'));
            case SWITCH_OFF_GRID_RELAY + 16:
                return next(catta::json::Token::character('a'));
            case SWITCH_OFF_GRID_RELAY + 17:
                return jump(catta::json::Token::character('y'), TAIL + 0);
            case SWITCH_ON_GRID_RELAY + 0:
                return next(catta::json::Token::character('s'));
            case SWITCH_ON_GRID_RELAY + 1:
                return next(catta::json::Token::character('w'));
            case SWITCH_ON_GRID_RELAY + 2:
                return next(catta::json::Token::character('i'));
            case SWITCH_ON_GRID_RELAY + 3:
                return next(catta::json::Token::character('t'));
            case SWITCH_ON_GRID_RELAY + 4:
                return next(catta::json::Token::character('c'));
            case SWITCH_ON_GRID_RELAY + 5:
                return next(catta::json::Token::character('h'));
            case SWITCH_ON_GRID_RELAY + 6:
                return next(catta::json::Token::character('O'));
            case SWITCH_ON_GRID_RELAY + 7:
                return next(catta::json::Token::character('n'));
            case SWITCH_ON_GRID_RELAY + 8:
                return next(catta::json::Token::character('G'));
            case SWITCH_ON_GRID_RELAY + 9:
                return next(catta::json::Token::character('r'));
            case SWITCH_ON_GRID_RELAY + 10:
                return next(catta::json::Token::character('i'));
            case SWITCH_ON_GRID_RELAY + 11:
                return next(catta::json::Token::character('d'));
            case SWITCH_ON_GRID_RELAY + 12:
                return next(catta::json::Token::character('R'));
            case SWITCH_ON_GRID_RELAY + 13:
                return next(catta::json::Token::character('e'));
            case SWITCH_ON_GRID_RELAY + 14:
                return next(catta::json::Token::character('l'));
            case SWITCH_ON_GRID_RELAY + 15:
                return next(catta::json::Token::character('a'));
            case SWITCH_ON_GRID_RELAY + 16:
                return jump(catta::json::Token::character('y'), TAIL + 0);
            case FORCE_IDLE + 0:
                return next(catta::json::Token::character('f'));
            case FORCE_IDLE + 1:
                return next(catta::json::Token::character('o'));
            case FORCE_IDLE + 2:
                return next(catta::json::Token::character('r'));
            case FORCE_IDLE + 3:
                return next(catta::json::Token::character('c'));
            case FORCE_IDLE + 4:
                return next(catta::json::Token::character('e'));
            case FORCE_IDLE + 5:
                return next(catta::json::Token::character('I'));
            case FORCE_IDLE + 6:
                return next(catta::json::Token::character('d'));
            case FORCE_IDLE + 7:
                return next(catta::json::Token::character('l'));
            case FORCE_IDLE + 8:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case DEACTIVATE_IDLE + 0:
                return next(catta::json::Token::character('d'));
            case DEACTIVATE_IDLE + 1:
                return next(catta::json::Token::character('e'));
            case DEACTIVATE_IDLE + 2:
                return next(catta::json::Token::character('a'));
            case DEACTIVATE_IDLE + 3:
                return next(catta::json::Token::character('c'));
            case DEACTIVATE_IDLE + 4:
                return next(catta::json::Token::character('t'));
            case DEACTIVATE_IDLE + 5:
                return next(catta::json::Token::character('i'));
            case DEACTIVATE_IDLE + 6:
                return next(catta::json::Token::character('v'));
            case DEACTIVATE_IDLE + 7:
                return next(catta::json::Token::character('a'));
            case DEACTIVATE_IDLE + 8:
                return next(catta::json::Token::character('t'));
            case DEACTIVATE_IDLE + 9:
                return next(catta::json::Token::character('e'));
            case DEACTIVATE_IDLE + 10:
                return next(catta::json::Token::character('I'));
            case DEACTIVATE_IDLE + 11:
                return next(catta::json::Token::character('d'));
            case DEACTIVATE_IDLE + 12:
                return next(catta::json::Token::character('l'));
            case DEACTIVATE_IDLE + 13:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case START_CONSTANT_VOLTAGE + 0:
                return next(catta::json::Token::character('s'));
            case START_CONSTANT_VOLTAGE + 1:
                return next(catta::json::Token::character('t'));
            case START_CONSTANT_VOLTAGE + 2:
                return next(catta::json::Token::character('a'));
            case START_CONSTANT_VOLTAGE + 3:
                return next(catta::json::Token::character('r'));
            case START_CONSTANT_VOLTAGE + 4:
                return next(catta::json::Token::character('t'));
            case START_CONSTANT_VOLTAGE + 5:
                return next(catta::json::Token::character('C'));
            case START_CONSTANT_VOLTAGE + 6:
                return next(catta::json::Token::character('o'));
            case START_CONSTANT_VOLTAGE + 7:
                return next(catta::json::Token::character('n'));
            case START_CONSTANT_VOLTAGE + 8:
                return next(catta::json::Token::character('s'));
            case START_CONSTANT_VOLTAGE + 9:
                return next(catta::json::Token::character('t'));
            case START_CONSTANT_VOLTAGE + 10:
                return next(catta::json::Token::character('a'));
            case START_CONSTANT_VOLTAGE + 11:
                return next(catta::json::Token::character('n'));
            case START_CONSTANT_VOLTAGE + 12:
                return next(catta::json::Token::character('t'));
            case START_CONSTANT_VOLTAGE + 13:
                return next(catta::json::Token::character('V'));
            case START_CONSTANT_VOLTAGE + 14:
                return next(catta::json::Token::character('o'));
            case START_CONSTANT_VOLTAGE + 15:
                return next(catta::json::Token::character('l'));
            case START_CONSTANT_VOLTAGE + 16:
                return next(catta::json::Token::character('t'));
            case START_CONSTANT_VOLTAGE + 17:
                return next(catta::json::Token::character('a'));
            case START_CONSTANT_VOLTAGE + 18:
                return next(catta::json::Token::character('g'));
            case START_CONSTANT_VOLTAGE + 19:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case END_CONSTANT_VOLTAGE + 0:
                return next(catta::json::Token::character('e'));
            case END_CONSTANT_VOLTAGE + 1:
                return next(catta::json::Token::character('n'));
            case END_CONSTANT_VOLTAGE + 2:
                return next(catta::json::Token::character('d'));
            case END_CONSTANT_VOLTAGE + 3:
                return next(catta::json::Token::character('C'));
            case END_CONSTANT_VOLTAGE + 4:
                return next(catta::json::Token::character('o'));
            case END_CONSTANT_VOLTAGE + 5:
                return next(catta::json::Token::character('n'));
            case END_CONSTANT_VOLTAGE + 6:
                return next(catta::json::Token::character('s'));
            case END_CONSTANT_VOLTAGE + 7:
                return next(catta::json::Token::character('t'));
            case END_CONSTANT_VOLTAGE + 8:
                return next(catta::json::Token::character('a'));
            case END_CONSTANT_VOLTAGE + 9:
                return next(catta::json::Token::character('n'));
            case END_CONSTANT_VOLTAGE + 10:
                return next(catta::json::Token::character('t'));
            case END_CONSTANT_VOLTAGE + 11:
                return next(catta::json::Token::character('V'));
            case END_CONSTANT_VOLTAGE + 12:
                return next(catta::json::Token::character('o'));
            case END_CONSTANT_VOLTAGE + 13:
                return next(catta::json::Token::character('l'));
            case END_CONSTANT_VOLTAGE + 14:
                return next(catta::json::Token::character('t'));
            case END_CONSTANT_VOLTAGE + 15:
                return next(catta::json::Token::character('a'));
            case END_CONSTANT_VOLTAGE + 16:
                return next(catta::json::Token::character('g'));
            case END_CONSTANT_VOLTAGE + 17:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SET_POWER_FACTOR + 0:
                return next(catta::json::Token::character('s'));
            case SET_POWER_FACTOR + 1:
                return next(catta::json::Token::character('e'));
            case SET_POWER_FACTOR + 2:
                return next(catta::json::Token::character('t'));
            case SET_POWER_FACTOR + 3:
                return next(catta::json::Token::character('P'));
            case SET_POWER_FACTOR + 4:
                return next(catta::json::Token::character('o'));
            case SET_POWER_FACTOR + 5:
                return next(catta::json::Token::character('w'));
            case SET_POWER_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case SET_POWER_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case SET_POWER_FACTOR + 8:
                return next(catta::json::Token::character('F'));
            case SET_POWER_FACTOR + 9:
                return next(catta::json::Token::character('a'));
            case SET_POWER_FACTOR + 10:
                return next(catta::json::Token::character('c'));
            case SET_POWER_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case SET_POWER_FACTOR + 12:
                return next(catta::json::Token::character('o'));
            case SET_POWER_FACTOR + 13:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case CONTROL_BATTERY_INVERT + 0:
                return next(catta::json::Token::character('c'));
            case CONTROL_BATTERY_INVERT + 1:
                return next(catta::json::Token::character('o'));
            case CONTROL_BATTERY_INVERT + 2:
                return next(catta::json::Token::character('n'));
            case CONTROL_BATTERY_INVERT + 3:
                return next(catta::json::Token::character('t'));
            case CONTROL_BATTERY_INVERT + 4:
                return next(catta::json::Token::character('r'));
            case CONTROL_BATTERY_INVERT + 5:
                return next(catta::json::Token::character('o'));
            case CONTROL_BATTERY_INVERT + 6:
                return next(catta::json::Token::character('l'));
            case CONTROL_BATTERY_INVERT + 7:
                return next(catta::json::Token::character('B'));
            case CONTROL_BATTERY_INVERT + 8:
                return next(catta::json::Token::character('a'));
            case CONTROL_BATTERY_INVERT + 9:
                return next(catta::json::Token::character('t'));
            case CONTROL_BATTERY_INVERT + 10:
                return next(catta::json::Token::character('t'));
            case CONTROL_BATTERY_INVERT + 11:
                return next(catta::json::Token::character('e'));
            case CONTROL_BATTERY_INVERT + 12:
                return next(catta::json::Token::character('r'));
            case CONTROL_BATTERY_INVERT + 13:
                return next(catta::json::Token::character('y'));
            case CONTROL_BATTERY_INVERT + 14:
                return next(catta::json::Token::character('I'));
            case CONTROL_BATTERY_INVERT + 15:
                return next(catta::json::Token::character('n'));
            case CONTROL_BATTERY_INVERT + 16:
                return next(catta::json::Token::character('v'));
            case CONTROL_BATTERY_INVERT + 17:
                return next(catta::json::Token::character('e'));
            case CONTROL_BATTERY_INVERT + 18:
                return next(catta::json::Token::character('r'));
            case CONTROL_BATTERY_INVERT + 19:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case LIMIT_BATTERY_INVERT + 0:
                return next(catta::json::Token::character('l'));
            case LIMIT_BATTERY_INVERT + 1:
                return next(catta::json::Token::character('i'));
            case LIMIT_BATTERY_INVERT + 2:
                return next(catta::json::Token::character('m'));
            case LIMIT_BATTERY_INVERT + 3:
                return next(catta::json::Token::character('i'));
            case LIMIT_BATTERY_INVERT + 4:
                return next(catta::json::Token::character('t'));
            case LIMIT_BATTERY_INVERT + 5:
                return next(catta::json::Token::character('B'));
            case LIMIT_BATTERY_INVERT + 6:
                return next(catta::json::Token::character('a'));
            case LIMIT_BATTERY_INVERT + 7:
                return next(catta::json::Token::character('t'));
            case LIMIT_BATTERY_INVERT + 8:
                return next(catta::json::Token::character('t'));
            case LIMIT_BATTERY_INVERT + 9:
                return next(catta::json::Token::character('e'));
            case LIMIT_BATTERY_INVERT + 10:
                return next(catta::json::Token::character('r'));
            case LIMIT_BATTERY_INVERT + 11:
                return next(catta::json::Token::character('y'));
            case LIMIT_BATTERY_INVERT + 12:
                return next(catta::json::Token::character('I'));
            case LIMIT_BATTERY_INVERT + 13:
                return next(catta::json::Token::character('n'));
            case LIMIT_BATTERY_INVERT + 14:
                return next(catta::json::Token::character('v'));
            case LIMIT_BATTERY_INVERT + 15:
                return next(catta::json::Token::character('e'));
            case LIMIT_BATTERY_INVERT + 16:
                return next(catta::json::Token::character('r'));
            case LIMIT_BATTERY_INVERT + 17:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case WRITE_REGISTER + 0:
                return next(catta::json::Token::character('w'));
            case WRITE_REGISTER + 1:
                return next(catta::json::Token::character('r'));
            case WRITE_REGISTER + 2:
                return next(catta::json::Token::character('i'));
            case WRITE_REGISTER + 3:
                return next(catta::json::Token::character('t'));
            case WRITE_REGISTER + 4:
                return next(catta::json::Token::character('e'));
            case WRITE_REGISTER + 5:
                return next(catta::json::Token::character('R'));
            case WRITE_REGISTER + 6:
                return next(catta::json::Token::character('e'));
            case WRITE_REGISTER + 7:
                return next(catta::json::Token::character('g'));
            case WRITE_REGISTER + 8:
                return next(catta::json::Token::character('i'));
            case WRITE_REGISTER + 9:
                return next(catta::json::Token::character('s'));
            case WRITE_REGISTER + 10:
                return next(catta::json::Token::character('t'));
            case WRITE_REGISTER + 11:
                return next(catta::json::Token::character('e'));
            case WRITE_REGISTER + 12:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case VALUE16 + 0:
                return next(catta::json::Token::character('v'));
            case VALUE16 + 1:
                return next(catta::json::Token::character('a'));
            case VALUE16 + 2:
                return next(catta::json::Token::character('l'));
            case VALUE16 + 3:
                return next(catta::json::Token::character('u'));
            case VALUE16 + 4:
                return next(catta::json::Token::character('e'));
            case VALUE16 + 5:
                return next(catta::json::Token::character('1'));
            case VALUE16 + 6:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case VALUE32 + 0:
                return next(catta::json::Token::character('v'));
            case VALUE32 + 1:
                return next(catta::json::Token::character('a'));
            case VALUE32 + 2:
                return next(catta::json::Token::character('l'));
            case VALUE32 + 3:
                return next(catta::json::Token::character('u'));
            case VALUE32 + 4:
                return next(catta::json::Token::character('e'));
            case VALUE32 + 5:
                return next(catta::json::Token::character('3'));
            case VALUE32 + 6:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case VALUE64 + 0:
                return next(catta::json::Token::character('v'));
            case VALUE64 + 1:
                return next(catta::json::Token::character('a'));
            case VALUE64 + 2:
                return next(catta::json::Token::character('l'));
            case VALUE64 + 3:
                return next(catta::json::Token::character('u'));
            case VALUE64 + 4:
                return next(catta::json::Token::character('e'));
            case VALUE64 + 5:
                return next(catta::json::Token::character('6'));
            case VALUE64 + 6:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case STRING + 0:
                return next(catta::json::Token::character('s'));
            case STRING + 1:
                return next(catta::json::Token::character('t'));
            case STRING + 2:
                return next(catta::json::Token::character('r'));
            case STRING + 3:
                return next(catta::json::Token::character('i'));
            case STRING + 4:
                return next(catta::json::Token::character('n'));
            case STRING + 5:
                return jump(catta::json::Token::character('g'), TAIL + 0);
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
    std::uint16_t _state;
    catta::json::Token _data;
    static constexpr std::uint16_t START = 0;
    static constexpr std::uint16_t EXCEPTION = START + 1;
    static constexpr std::uint16_t FACTORY_VALUES = EXCEPTION + 9;
    static constexpr std::uint16_t READ_ERROR = FACTORY_VALUES + 13;
    static constexpr std::uint16_t READ_OPERATING_DATA33 = READ_ERROR + 9;
    static constexpr std::uint16_t READ_OPERATING_DATA3E = READ_OPERATING_DATA33 + 19;
    static constexpr std::uint16_t SWITCH_OFF_GRID_RELAY = READ_OPERATING_DATA3E + 19;
    static constexpr std::uint16_t SWITCH_ON_GRID_RELAY = SWITCH_OFF_GRID_RELAY + 18;
    static constexpr std::uint16_t FORCE_IDLE = SWITCH_ON_GRID_RELAY + 17;
    static constexpr std::uint16_t DEACTIVATE_IDLE = FORCE_IDLE + 9;
    static constexpr std::uint16_t START_CONSTANT_VOLTAGE = DEACTIVATE_IDLE + 14;
    static constexpr std::uint16_t END_CONSTANT_VOLTAGE = START_CONSTANT_VOLTAGE + 20;
    static constexpr std::uint16_t SET_POWER_FACTOR = END_CONSTANT_VOLTAGE + 18;
    static constexpr std::uint16_t CONTROL_BATTERY_INVERT = SET_POWER_FACTOR + 14;
    static constexpr std::uint16_t LIMIT_BATTERY_INVERT = CONTROL_BATTERY_INVERT + 20;
    static constexpr std::uint16_t WRITE_REGISTER = LIMIT_BATTERY_INVERT + 18;
    static constexpr std::uint16_t VALUE16 = WRITE_REGISTER + 13;
    static constexpr std::uint16_t VALUE32 = VALUE16 + 7;
    static constexpr std::uint16_t VALUE64 = VALUE32 + 7;
    static constexpr std::uint16_t STRING = VALUE64 + 7;
    static constexpr std::uint16_t TAIL = STRING + 6;
    static constexpr std::uint16_t DONE = TAIL + 2;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
