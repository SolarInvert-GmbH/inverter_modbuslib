#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::RegisterAddress>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::RegisterAddress;
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
                    _state = COMMON_MANUFACTURER + 0;
                    break;
                case 1:
                    _state = COMMON_MODEL + 0;
                    break;
                case 2:
                    _state = COMMON_SERIAL_NUMBER + 0;
                    break;
                case 3:
                    _state = COMMON_DEVICE_ADDRESS + 0;
                    break;
                case 4:
                    _state = INVERTER_AMPS + 0;
                    break;
                case 5:
                    _state = INVERTER_AMPS_PHASE_A + 0;
                    break;
                case 6:
                    _state = INVERTER_AMPS_PHASE_B + 0;
                    break;
                case 7:
                    _state = INVERTER_AMPS_PHASE_C + 0;
                    break;
                case 8:
                    _state = INVERTER_AMPS_SCALE_FACTOR + 0;
                    break;
                case 9:
                    _state = INVERTER_PHASE_VOLTAGE_A + 0;
                    break;
                case 10:
                    _state = INVERTER_PHASE_VOLTAGE_B + 0;
                    break;
                case 11:
                    _state = INVERTER_PHASE_VOLTAGE_C + 0;
                    break;
                case 12:
                    _state = INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 0;
                    break;
                case 13:
                    _state = INVERTER_WATT + 0;
                    break;
                case 14:
                    _state = INVERTER_WATT_SCALE_FACTOR + 0;
                    break;
                case 15:
                    _state = INVERTER_HERTZ + 0;
                    break;
                case 16:
                    _state = INVERTER_HERTZ_SCALE_FACTOR + 0;
                    break;
                case 17:
                    _state = INVERTER_POWER_FACTOR + 0;
                    break;
                case 18:
                    _state = INVERTER_POWER_FACTOR_SCALE_FACTOR + 0;
                    break;
                case 19:
                    _state = INVERTER_WATT_HOURS + 0;
                    break;
                case 20:
                    _state = INVERTER_WATT_HOURS_SCALE_FACTOR + 0;
                    break;
                case 21:
                    _state = INVERTER_DC_VOLTAGE + 0;
                    break;
                case 22:
                    _state = INVERTER_DC_VOLTAGE_SCALE_FACTOR + 0;
                    break;
                case 23:
                    _state = INVERTER_TEMPERATURE + 0;
                    break;
                case 24:
                    _state = INVERTER_TEMPERATURE_SCALE_FACTOR + 0;
                    break;
                case 25:
                    _state = INVERTER_OPERATING_STATE + 0;
                    break;
                case 26:
                    _state = INVERTER_VENDOR_OPERATING_STATE + 0;
                    break;
                case 27:
                    _state = INVERTER_VENDOR_EVENT_BITFIELD + 0;
                    break;
                case 28:
                    _state = NAMEPLATE_DER_TYPE + 0;
                    break;
                case 29:
                    _state = BASIC_SETTINGS_W_MAX + 0;
                    break;
                case 30:
                    _state = BASIC_SETTINGS_V_MAX + 0;
                    break;
                case 31:
                    _state = BASIC_SETTINGS_V_MIN + 0;
                    break;
                case 32:
                    _state = BASIC_SETTINGS_ECP_NOM_HZ + 0;
                    break;
                case 33:
                    _state = BASIC_SETTINGS_CONN_PHASE + 0;
                    break;
                case 34:
                    _state = BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 0;
                    break;
                case 35:
                    _state = BASIC_SETTINGS_V_MIN_MAX + 0;
                    break;
                case 36:
                    _state = BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 0;
                    break;
                case 37:
                    _state = BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 0;
                    break;
                case 38:
                    _state = BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 0;
                    break;
                case 39:
                    _state = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 0;
                    break;
                case 40:
                    _state = IMMEDIATE_CONNECTION_TIMEOUT + 0;
                    break;
                case 41:
                    _state = IMMEDIATE_CONNECTION_CONTROL + 0;
                    break;
                case 42:
                    _state = IMMEDIATE_POWER_LIMIT + 0;
                    break;
                case 43:
                    _state = STORAGE_W_CHA_MAX + 0;
                    break;
                case 44:
                    _state = STORAGE_W_CHA_RATE + 0;
                    break;
                case 45:
                    _state = SI_CONTROL_PCD_DIV + 0;
                    break;
                case 46:
                    _state = SI_CONTROL_UDC_EXT + 0;
                    break;
                case 47:
                    _state = SI_CONTROL_P_SET_POINT + 0;
                    break;
                case 48:
                    _state = SI_CONTROL_U_MIN_EXT + 0;
                    break;
                default:
                    _state = SI_CONTROL_U_MAX_EXT + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return start(catta::json::Token::openString());
            case COMMON_MANUFACTURER + 0:
                return next(catta::json::Token::character('C'));
            case COMMON_MANUFACTURER + 1:
                return next(catta::json::Token::character('o'));
            case COMMON_MANUFACTURER + 2:
                return next(catta::json::Token::character('m'));
            case COMMON_MANUFACTURER + 3:
                return next(catta::json::Token::character('m'));
            case COMMON_MANUFACTURER + 4:
                return next(catta::json::Token::character('o'));
            case COMMON_MANUFACTURER + 5:
                return next(catta::json::Token::character('n'));
            case COMMON_MANUFACTURER + 6:
                return next(catta::json::Token::character('M'));
            case COMMON_MANUFACTURER + 7:
                return next(catta::json::Token::character('a'));
            case COMMON_MANUFACTURER + 8:
                return next(catta::json::Token::character('n'));
            case COMMON_MANUFACTURER + 9:
                return next(catta::json::Token::character('u'));
            case COMMON_MANUFACTURER + 10:
                return next(catta::json::Token::character('f'));
            case COMMON_MANUFACTURER + 11:
                return next(catta::json::Token::character('a'));
            case COMMON_MANUFACTURER + 12:
                return next(catta::json::Token::character('c'));
            case COMMON_MANUFACTURER + 13:
                return next(catta::json::Token::character('t'));
            case COMMON_MANUFACTURER + 14:
                return next(catta::json::Token::character('u'));
            case COMMON_MANUFACTURER + 15:
                return next(catta::json::Token::character('r'));
            case COMMON_MANUFACTURER + 16:
                return next(catta::json::Token::character('e'));
            case COMMON_MANUFACTURER + 17:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case COMMON_MODEL + 0:
                return next(catta::json::Token::character('C'));
            case COMMON_MODEL + 1:
                return next(catta::json::Token::character('o'));
            case COMMON_MODEL + 2:
                return next(catta::json::Token::character('m'));
            case COMMON_MODEL + 3:
                return next(catta::json::Token::character('m'));
            case COMMON_MODEL + 4:
                return next(catta::json::Token::character('o'));
            case COMMON_MODEL + 5:
                return next(catta::json::Token::character('n'));
            case COMMON_MODEL + 6:
                return next(catta::json::Token::character('M'));
            case COMMON_MODEL + 7:
                return next(catta::json::Token::character('o'));
            case COMMON_MODEL + 8:
                return next(catta::json::Token::character('d'));
            case COMMON_MODEL + 9:
                return next(catta::json::Token::character('e'));
            case COMMON_MODEL + 10:
                return jump(catta::json::Token::character('l'), TAIL + 0);
            case COMMON_SERIAL_NUMBER + 0:
                return next(catta::json::Token::character('C'));
            case COMMON_SERIAL_NUMBER + 1:
                return next(catta::json::Token::character('o'));
            case COMMON_SERIAL_NUMBER + 2:
                return next(catta::json::Token::character('m'));
            case COMMON_SERIAL_NUMBER + 3:
                return next(catta::json::Token::character('m'));
            case COMMON_SERIAL_NUMBER + 4:
                return next(catta::json::Token::character('o'));
            case COMMON_SERIAL_NUMBER + 5:
                return next(catta::json::Token::character('n'));
            case COMMON_SERIAL_NUMBER + 6:
                return next(catta::json::Token::character('S'));
            case COMMON_SERIAL_NUMBER + 7:
                return next(catta::json::Token::character('e'));
            case COMMON_SERIAL_NUMBER + 8:
                return next(catta::json::Token::character('r'));
            case COMMON_SERIAL_NUMBER + 9:
                return next(catta::json::Token::character('i'));
            case COMMON_SERIAL_NUMBER + 10:
                return next(catta::json::Token::character('a'));
            case COMMON_SERIAL_NUMBER + 11:
                return next(catta::json::Token::character('l'));
            case COMMON_SERIAL_NUMBER + 12:
                return next(catta::json::Token::character('N'));
            case COMMON_SERIAL_NUMBER + 13:
                return next(catta::json::Token::character('u'));
            case COMMON_SERIAL_NUMBER + 14:
                return next(catta::json::Token::character('m'));
            case COMMON_SERIAL_NUMBER + 15:
                return next(catta::json::Token::character('b'));
            case COMMON_SERIAL_NUMBER + 16:
                return next(catta::json::Token::character('e'));
            case COMMON_SERIAL_NUMBER + 17:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case COMMON_DEVICE_ADDRESS + 0:
                return next(catta::json::Token::character('C'));
            case COMMON_DEVICE_ADDRESS + 1:
                return next(catta::json::Token::character('o'));
            case COMMON_DEVICE_ADDRESS + 2:
                return next(catta::json::Token::character('m'));
            case COMMON_DEVICE_ADDRESS + 3:
                return next(catta::json::Token::character('m'));
            case COMMON_DEVICE_ADDRESS + 4:
                return next(catta::json::Token::character('o'));
            case COMMON_DEVICE_ADDRESS + 5:
                return next(catta::json::Token::character('n'));
            case COMMON_DEVICE_ADDRESS + 6:
                return next(catta::json::Token::character('D'));
            case COMMON_DEVICE_ADDRESS + 7:
                return next(catta::json::Token::character('e'));
            case COMMON_DEVICE_ADDRESS + 8:
                return next(catta::json::Token::character('v'));
            case COMMON_DEVICE_ADDRESS + 9:
                return next(catta::json::Token::character('i'));
            case COMMON_DEVICE_ADDRESS + 10:
                return next(catta::json::Token::character('c'));
            case COMMON_DEVICE_ADDRESS + 11:
                return next(catta::json::Token::character('e'));
            case COMMON_DEVICE_ADDRESS + 12:
                return next(catta::json::Token::character('A'));
            case COMMON_DEVICE_ADDRESS + 13:
                return next(catta::json::Token::character('d'));
            case COMMON_DEVICE_ADDRESS + 14:
                return next(catta::json::Token::character('d'));
            case COMMON_DEVICE_ADDRESS + 15:
                return next(catta::json::Token::character('r'));
            case COMMON_DEVICE_ADDRESS + 16:
                return next(catta::json::Token::character('e'));
            case COMMON_DEVICE_ADDRESS + 17:
                return next(catta::json::Token::character('s'));
            case COMMON_DEVICE_ADDRESS + 18:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case INVERTER_AMPS + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AMPS + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS + 9:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS + 10:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS + 11:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case INVERTER_AMPS_PHASE_A + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AMPS_PHASE_A + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS_PHASE_A + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS_PHASE_A + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_A + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_A + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_PHASE_A + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_A + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_A + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS_PHASE_A + 9:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS_PHASE_A + 10:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS_PHASE_A + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_A + 12:
                return next(catta::json::Token::character('P'));
            case INVERTER_AMPS_PHASE_A + 13:
                return next(catta::json::Token::character('h'));
            case INVERTER_AMPS_PHASE_A + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_PHASE_A + 15:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_A + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_A + 17:
                return jump(catta::json::Token::character('A'), TAIL + 0);
            case INVERTER_AMPS_PHASE_B + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AMPS_PHASE_B + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS_PHASE_B + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS_PHASE_B + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_B + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_B + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_PHASE_B + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_B + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_B + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS_PHASE_B + 9:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS_PHASE_B + 10:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS_PHASE_B + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_B + 12:
                return next(catta::json::Token::character('P'));
            case INVERTER_AMPS_PHASE_B + 13:
                return next(catta::json::Token::character('h'));
            case INVERTER_AMPS_PHASE_B + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_PHASE_B + 15:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_B + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_B + 17:
                return jump(catta::json::Token::character('B'), TAIL + 0);
            case INVERTER_AMPS_PHASE_C + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AMPS_PHASE_C + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS_PHASE_C + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS_PHASE_C + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_C + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_C + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_PHASE_C + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_C + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_PHASE_C + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS_PHASE_C + 9:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS_PHASE_C + 10:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS_PHASE_C + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_C + 12:
                return next(catta::json::Token::character('P'));
            case INVERTER_AMPS_PHASE_C + 13:
                return next(catta::json::Token::character('h'));
            case INVERTER_AMPS_PHASE_C + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_PHASE_C + 15:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_PHASE_C + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_PHASE_C + 17:
                return jump(catta::json::Token::character('C'), TAIL + 0);
            case INVERTER_AMPS_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AMPS_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('S'));
            case INVERTER_AMPS_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('c'));
            case INVERTER_AMPS_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_AMPS_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('F'));
            case INVERTER_AMPS_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('c'));
            case INVERTER_AMPS_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('o'));
            case INVERTER_AMPS_SCALE_FACTOR + 22:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_PHASE_VOLTAGE_A + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_PHASE_VOLTAGE_A + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_PHASE_VOLTAGE_A + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_PHASE_VOLTAGE_A + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_A + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_A + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_A + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_A + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_A + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_PHASE_VOLTAGE_A + 9:
                return next(catta::json::Token::character('h'));
            case INVERTER_PHASE_VOLTAGE_A + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_A + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_PHASE_VOLTAGE_A + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_A + 13:
                return next(catta::json::Token::character('V'));
            case INVERTER_PHASE_VOLTAGE_A + 14:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_A + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_A + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_A + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_A + 18:
                return next(catta::json::Token::character('g'));
            case INVERTER_PHASE_VOLTAGE_A + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_A + 20:
                return jump(catta::json::Token::character('A'), TAIL + 0);
            case INVERTER_PHASE_VOLTAGE_B + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_PHASE_VOLTAGE_B + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_PHASE_VOLTAGE_B + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_PHASE_VOLTAGE_B + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_B + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_B + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_B + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_B + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_B + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_PHASE_VOLTAGE_B + 9:
                return next(catta::json::Token::character('h'));
            case INVERTER_PHASE_VOLTAGE_B + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_B + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_PHASE_VOLTAGE_B + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_B + 13:
                return next(catta::json::Token::character('V'));
            case INVERTER_PHASE_VOLTAGE_B + 14:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_B + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_B + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_B + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_B + 18:
                return next(catta::json::Token::character('g'));
            case INVERTER_PHASE_VOLTAGE_B + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_B + 20:
                return jump(catta::json::Token::character('B'), TAIL + 0);
            case INVERTER_PHASE_VOLTAGE_C + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_PHASE_VOLTAGE_C + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_PHASE_VOLTAGE_C + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_PHASE_VOLTAGE_C + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_C + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_C + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_C + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_C + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_C + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_PHASE_VOLTAGE_C + 9:
                return next(catta::json::Token::character('h'));
            case INVERTER_PHASE_VOLTAGE_C + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_C + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_PHASE_VOLTAGE_C + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_C + 13:
                return next(catta::json::Token::character('V'));
            case INVERTER_PHASE_VOLTAGE_C + 14:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_C + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_C + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_C + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_C + 18:
                return next(catta::json::Token::character('g'));
            case INVERTER_PHASE_VOLTAGE_C + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_C + 20:
                return jump(catta::json::Token::character('C'), TAIL + 0);
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('h'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('s'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('V'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('g'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('S'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('c'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('F'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('c'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 30:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_WATT + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_WATT + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT + 8:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT + 9:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT + 10:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT + 11:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case INVERTER_WATT_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_WATT_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('S'));
            case INVERTER_WATT_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('l'));
            case INVERTER_WATT_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('F'));
            case INVERTER_WATT_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_SCALE_FACTOR + 22:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_HERTZ + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_HERTZ + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_HERTZ + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_HERTZ + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ + 8:
                return next(catta::json::Token::character('H'));
            case INVERTER_HERTZ + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ + 10:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ + 12:
                return jump(catta::json::Token::character('z'), TAIL + 0);
            case INVERTER_HERTZ_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_HERTZ_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_HERTZ_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_HERTZ_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('H'));
            case INVERTER_HERTZ_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('z'));
            case INVERTER_HERTZ_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('S'));
            case INVERTER_HERTZ_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('c'));
            case INVERTER_HERTZ_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_HERTZ_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('l'));
            case INVERTER_HERTZ_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('F'));
            case INVERTER_HERTZ_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_HERTZ_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case INVERTER_HERTZ_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('o'));
            case INVERTER_HERTZ_SCALE_FACTOR + 23:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_POWER_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_POWER_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_POWER_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_POWER_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_POWER_FACTOR + 9:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR + 10:
                return next(catta::json::Token::character('w'));
            case INVERTER_POWER_FACTOR + 11:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR + 12:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR + 13:
                return next(catta::json::Token::character('F'));
            case INVERTER_POWER_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR + 15:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR + 17:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR + 18:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('P'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('w'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('F'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('S'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('l'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('F'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 29:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_WATT_HOURS + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_WATT_HOURS + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT_HOURS + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT_HOURS + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS + 8:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT_HOURS + 9:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS + 10:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS + 12:
                return next(catta::json::Token::character('H'));
            case INVERTER_WATT_HOURS + 13:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_HOURS + 14:
                return next(catta::json::Token::character('u'));
            case INVERTER_WATT_HOURS + 15:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS + 16:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('H'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('u'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('s'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('S'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('l'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('F'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 27:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_DC_VOLTAGE + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_DC_VOLTAGE + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_DC_VOLTAGE + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_DC_VOLTAGE + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE + 8:
                return next(catta::json::Token::character('D'));
            case INVERTER_DC_VOLTAGE + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE + 10:
                return next(catta::json::Token::character('V'));
            case INVERTER_DC_VOLTAGE + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_VOLTAGE + 12:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_VOLTAGE + 13:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE + 15:
                return next(catta::json::Token::character('g'));
            case INVERTER_DC_VOLTAGE + 16:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('D'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('V'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('g'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('S'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('F'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 27:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_TEMPERATURE + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_TEMPERATURE + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_TEMPERATURE + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_TEMPERATURE + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE + 8:
                return next(catta::json::Token::character('T'));
            case INVERTER_TEMPERATURE + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE + 10:
                return next(catta::json::Token::character('m'));
            case INVERTER_TEMPERATURE + 11:
                return next(catta::json::Token::character('p'));
            case INVERTER_TEMPERATURE + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE + 15:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE + 16:
                return next(catta::json::Token::character('u'));
            case INVERTER_TEMPERATURE + 17:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE + 18:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('T'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('m'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('p'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('u'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('S'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('l'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('F'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('c'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('o'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 29:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_OPERATING_STATE + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_OPERATING_STATE + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_OPERATING_STATE + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_OPERATING_STATE + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_OPERATING_STATE + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_OPERATING_STATE + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_OPERATING_STATE + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_OPERATING_STATE + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_OPERATING_STATE + 8:
                return next(catta::json::Token::character('O'));
            case INVERTER_OPERATING_STATE + 9:
                return next(catta::json::Token::character('p'));
            case INVERTER_OPERATING_STATE + 10:
                return next(catta::json::Token::character('e'));
            case INVERTER_OPERATING_STATE + 11:
                return next(catta::json::Token::character('r'));
            case INVERTER_OPERATING_STATE + 12:
                return next(catta::json::Token::character('a'));
            case INVERTER_OPERATING_STATE + 13:
                return next(catta::json::Token::character('t'));
            case INVERTER_OPERATING_STATE + 14:
                return next(catta::json::Token::character('i'));
            case INVERTER_OPERATING_STATE + 15:
                return next(catta::json::Token::character('n'));
            case INVERTER_OPERATING_STATE + 16:
                return next(catta::json::Token::character('g'));
            case INVERTER_OPERATING_STATE + 17:
                return next(catta::json::Token::character('S'));
            case INVERTER_OPERATING_STATE + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_OPERATING_STATE + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_OPERATING_STATE + 20:
                return next(catta::json::Token::character('t'));
            case INVERTER_OPERATING_STATE + 21:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case INVERTER_VENDOR_OPERATING_STATE + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_OPERATING_STATE + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_OPERATING_STATE + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_OPERATING_STATE + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_OPERATING_STATE + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_OPERATING_STATE + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_OPERATING_STATE + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_OPERATING_STATE + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_OPERATING_STATE + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_OPERATING_STATE + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_OPERATING_STATE + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_OPERATING_STATE + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_OPERATING_STATE + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_OPERATING_STATE + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_OPERATING_STATE + 14:
                return next(catta::json::Token::character('O'));
            case INVERTER_VENDOR_OPERATING_STATE + 15:
                return next(catta::json::Token::character('p'));
            case INVERTER_VENDOR_OPERATING_STATE + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_OPERATING_STATE + 17:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_OPERATING_STATE + 18:
                return next(catta::json::Token::character('a'));
            case INVERTER_VENDOR_OPERATING_STATE + 19:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_OPERATING_STATE + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_OPERATING_STATE + 21:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_OPERATING_STATE + 22:
                return next(catta::json::Token::character('g'));
            case INVERTER_VENDOR_OPERATING_STATE + 23:
                return next(catta::json::Token::character('S'));
            case INVERTER_VENDOR_OPERATING_STATE + 24:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_OPERATING_STATE + 25:
                return next(catta::json::Token::character('a'));
            case INVERTER_VENDOR_OPERATING_STATE + 26:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_OPERATING_STATE + 27:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case INVERTER_VENDOR_EVENT_BITFIELD + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 14:
                return next(catta::json::Token::character('E'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 15:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 17:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 19:
                return next(catta::json::Token::character('B'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 22:
                return next(catta::json::Token::character('f'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 23:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 25:
                return next(catta::json::Token::character('l'));
            case INVERTER_VENDOR_EVENT_BITFIELD + 26:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case NAMEPLATE_DER_TYPE + 0:
                return next(catta::json::Token::character('N'));
            case NAMEPLATE_DER_TYPE + 1:
                return next(catta::json::Token::character('a'));
            case NAMEPLATE_DER_TYPE + 2:
                return next(catta::json::Token::character('m'));
            case NAMEPLATE_DER_TYPE + 3:
                return next(catta::json::Token::character('e'));
            case NAMEPLATE_DER_TYPE + 4:
                return next(catta::json::Token::character('p'));
            case NAMEPLATE_DER_TYPE + 5:
                return next(catta::json::Token::character('l'));
            case NAMEPLATE_DER_TYPE + 6:
                return next(catta::json::Token::character('a'));
            case NAMEPLATE_DER_TYPE + 7:
                return next(catta::json::Token::character('t'));
            case NAMEPLATE_DER_TYPE + 8:
                return next(catta::json::Token::character('e'));
            case NAMEPLATE_DER_TYPE + 9:
                return next(catta::json::Token::character('D'));
            case NAMEPLATE_DER_TYPE + 10:
                return next(catta::json::Token::character('e'));
            case NAMEPLATE_DER_TYPE + 11:
                return next(catta::json::Token::character('r'));
            case NAMEPLATE_DER_TYPE + 12:
                return next(catta::json::Token::character('T'));
            case NAMEPLATE_DER_TYPE + 13:
                return next(catta::json::Token::character('y'));
            case NAMEPLATE_DER_TYPE + 14:
                return next(catta::json::Token::character('p'));
            case NAMEPLATE_DER_TYPE + 15:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case BASIC_SETTINGS_W_MAX + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_W_MAX + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_W_MAX + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_W_MAX + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_W_MAX + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_W_MAX + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_W_MAX + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_W_MAX + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_W_MAX + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_W_MAX + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_W_MAX + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_W_MAX + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_W_MAX + 13:
                return next(catta::json::Token::character('W'));
            case BASIC_SETTINGS_W_MAX + 14:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_W_MAX + 15:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX + 16:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case BASIC_SETTINGS_V_MAX + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_V_MAX + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_V_MAX + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MAX + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MAX + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_V_MAX + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_V_MAX + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_V_MAX + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MAX + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MAX + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MAX + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_V_MAX + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_V_MAX + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MAX + 13:
                return next(catta::json::Token::character('V'));
            case BASIC_SETTINGS_V_MAX + 14:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_V_MAX + 15:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_V_MAX + 16:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case BASIC_SETTINGS_V_MIN + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_V_MIN + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_V_MIN + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MIN + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_V_MIN + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_V_MIN + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_V_MIN + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MIN + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MIN + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_V_MIN + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_V_MIN + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MIN + 13:
                return next(catta::json::Token::character('V'));
            case BASIC_SETTINGS_V_MIN + 14:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_V_MIN + 15:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN + 16:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case BASIC_SETTINGS_ECP_NOM_HZ + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 13:
                return next(catta::json::Token::character('E'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 14:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 15:
                return next(catta::json::Token::character('p'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 16:
                return next(catta::json::Token::character('N'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 17:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 18:
                return next(catta::json::Token::character('m'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 19:
                return next(catta::json::Token::character('H'));
            case BASIC_SETTINGS_ECP_NOM_HZ + 20:
                return jump(catta::json::Token::character('z'), TAIL + 0);
            case BASIC_SETTINGS_CONN_PHASE + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_CONN_PHASE + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_CONN_PHASE + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_CONN_PHASE + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_CONN_PHASE + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_CONN_PHASE + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_CONN_PHASE + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_CONN_PHASE + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_CONN_PHASE + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_CONN_PHASE + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_CONN_PHASE + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_CONN_PHASE + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_CONN_PHASE + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_CONN_PHASE + 13:
                return next(catta::json::Token::character('C'));
            case BASIC_SETTINGS_CONN_PHASE + 14:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_CONN_PHASE + 15:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_CONN_PHASE + 16:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_CONN_PHASE + 17:
                return next(catta::json::Token::character('P'));
            case BASIC_SETTINGS_CONN_PHASE + 18:
                return next(catta::json::Token::character('h'));
            case BASIC_SETTINGS_CONN_PHASE + 19:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_CONN_PHASE + 20:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_CONN_PHASE + 21:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('W'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('x'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('l'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('F'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 27:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case BASIC_SETTINGS_V_MIN_MAX + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_V_MIN_MAX + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_V_MIN_MAX + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MIN_MAX + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN_MAX + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_V_MIN_MAX + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_V_MIN_MAX + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_V_MIN_MAX + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MIN_MAX + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_V_MIN_MAX + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN_MAX + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_V_MIN_MAX + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_V_MIN_MAX + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_V_MIN_MAX + 13:
                return next(catta::json::Token::character('V'));
            case BASIC_SETTINGS_V_MIN_MAX + 14:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_V_MIN_MAX + 15:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_V_MIN_MAX + 16:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_V_MIN_MAX + 17:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_V_MIN_MAX + 18:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_V_MIN_MAX + 19:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('V'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('x'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('l'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('F'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 28:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('V'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('r'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('x'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('l'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('F'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 29:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('E'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('p'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('N'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('m'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('H'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('z'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('l'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('F'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 31:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 0:
                return next(catta::json::Token::character('E'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 1:
                return next(catta::json::Token::character('x'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 2:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 3:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 4:
                return next(catta::json::Token::character('n'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 5:
                return next(catta::json::Token::character('d'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 6:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 7:
                return next(catta::json::Token::character('d'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 8:
                return next(catta::json::Token::character('M'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 9:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 10:
                return next(catta::json::Token::character('s'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 11:
                return next(catta::json::Token::character('u'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 12:
                return next(catta::json::Token::character('r'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 13:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 14:
                return next(catta::json::Token::character('m'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 15:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 16:
                return next(catta::json::Token::character('n'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 17:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 18:
                return next(catta::json::Token::character('s'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 19:
                return next(catta::json::Token::character('A'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 20:
                return next(catta::json::Token::character('c'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 21:
                return next(catta::json::Token::character('W'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 22:
                return next(catta::json::Token::character('a'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 23:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 24:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 25:
                return next(catta::json::Token::character('H'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 26:
                return next(catta::json::Token::character('o'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 27:
                return next(catta::json::Token::character('u'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 28:
                return next(catta::json::Token::character('r'));
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS + 29:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case IMMEDIATE_CONNECTION_TIMEOUT + 0:
                return next(catta::json::Token::character('I'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 1:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 2:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 3:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 4:
                return next(catta::json::Token::character('d'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 5:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 6:
                return next(catta::json::Token::character('a'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 7:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 8:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 9:
                return next(catta::json::Token::character('C'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 10:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 11:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 12:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 13:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 14:
                return next(catta::json::Token::character('c'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 15:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 16:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 17:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 18:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 19:
                return next(catta::json::Token::character('T'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 20:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 21:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 22:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 23:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 24:
                return next(catta::json::Token::character('u'));
            case IMMEDIATE_CONNECTION_TIMEOUT + 25:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case IMMEDIATE_CONNECTION_CONTROL + 0:
                return next(catta::json::Token::character('I'));
            case IMMEDIATE_CONNECTION_CONTROL + 1:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_CONNECTION_CONTROL + 2:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_CONNECTION_CONTROL + 3:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_CONTROL + 4:
                return next(catta::json::Token::character('d'));
            case IMMEDIATE_CONNECTION_CONTROL + 5:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_CONNECTION_CONTROL + 6:
                return next(catta::json::Token::character('a'));
            case IMMEDIATE_CONNECTION_CONTROL + 7:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_CONNECTION_CONTROL + 8:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_CONTROL + 9:
                return next(catta::json::Token::character('C'));
            case IMMEDIATE_CONNECTION_CONTROL + 10:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_CONTROL + 11:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_CONTROL + 12:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_CONTROL + 13:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_CONNECTION_CONTROL + 14:
                return next(catta::json::Token::character('c'));
            case IMMEDIATE_CONNECTION_CONTROL + 15:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_CONNECTION_CONTROL + 16:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_CONNECTION_CONTROL + 17:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_CONTROL + 18:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_CONTROL + 19:
                return next(catta::json::Token::character('C'));
            case IMMEDIATE_CONNECTION_CONTROL + 20:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_CONTROL + 21:
                return next(catta::json::Token::character('n'));
            case IMMEDIATE_CONNECTION_CONTROL + 22:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_CONNECTION_CONTROL + 23:
                return next(catta::json::Token::character('r'));
            case IMMEDIATE_CONNECTION_CONTROL + 24:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_CONNECTION_CONTROL + 25:
                return jump(catta::json::Token::character('l'), TAIL + 0);
            case IMMEDIATE_POWER_LIMIT + 0:
                return next(catta::json::Token::character('I'));
            case IMMEDIATE_POWER_LIMIT + 1:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_POWER_LIMIT + 2:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_POWER_LIMIT + 3:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_POWER_LIMIT + 4:
                return next(catta::json::Token::character('d'));
            case IMMEDIATE_POWER_LIMIT + 5:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_POWER_LIMIT + 6:
                return next(catta::json::Token::character('a'));
            case IMMEDIATE_POWER_LIMIT + 7:
                return next(catta::json::Token::character('t'));
            case IMMEDIATE_POWER_LIMIT + 8:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_POWER_LIMIT + 9:
                return next(catta::json::Token::character('P'));
            case IMMEDIATE_POWER_LIMIT + 10:
                return next(catta::json::Token::character('o'));
            case IMMEDIATE_POWER_LIMIT + 11:
                return next(catta::json::Token::character('w'));
            case IMMEDIATE_POWER_LIMIT + 12:
                return next(catta::json::Token::character('e'));
            case IMMEDIATE_POWER_LIMIT + 13:
                return next(catta::json::Token::character('r'));
            case IMMEDIATE_POWER_LIMIT + 14:
                return next(catta::json::Token::character('L'));
            case IMMEDIATE_POWER_LIMIT + 15:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_POWER_LIMIT + 16:
                return next(catta::json::Token::character('m'));
            case IMMEDIATE_POWER_LIMIT + 17:
                return next(catta::json::Token::character('i'));
            case IMMEDIATE_POWER_LIMIT + 18:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case STORAGE_W_CHA_MAX + 0:
                return next(catta::json::Token::character('S'));
            case STORAGE_W_CHA_MAX + 1:
                return next(catta::json::Token::character('t'));
            case STORAGE_W_CHA_MAX + 2:
                return next(catta::json::Token::character('o'));
            case STORAGE_W_CHA_MAX + 3:
                return next(catta::json::Token::character('r'));
            case STORAGE_W_CHA_MAX + 4:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_MAX + 5:
                return next(catta::json::Token::character('g'));
            case STORAGE_W_CHA_MAX + 6:
                return next(catta::json::Token::character('e'));
            case STORAGE_W_CHA_MAX + 7:
                return next(catta::json::Token::character('W'));
            case STORAGE_W_CHA_MAX + 8:
                return next(catta::json::Token::character('C'));
            case STORAGE_W_CHA_MAX + 9:
                return next(catta::json::Token::character('h'));
            case STORAGE_W_CHA_MAX + 10:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_MAX + 11:
                return next(catta::json::Token::character('M'));
            case STORAGE_W_CHA_MAX + 12:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_MAX + 13:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case STORAGE_W_CHA_RATE + 0:
                return next(catta::json::Token::character('S'));
            case STORAGE_W_CHA_RATE + 1:
                return next(catta::json::Token::character('t'));
            case STORAGE_W_CHA_RATE + 2:
                return next(catta::json::Token::character('o'));
            case STORAGE_W_CHA_RATE + 3:
                return next(catta::json::Token::character('r'));
            case STORAGE_W_CHA_RATE + 4:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_RATE + 5:
                return next(catta::json::Token::character('g'));
            case STORAGE_W_CHA_RATE + 6:
                return next(catta::json::Token::character('e'));
            case STORAGE_W_CHA_RATE + 7:
                return next(catta::json::Token::character('W'));
            case STORAGE_W_CHA_RATE + 8:
                return next(catta::json::Token::character('C'));
            case STORAGE_W_CHA_RATE + 9:
                return next(catta::json::Token::character('h'));
            case STORAGE_W_CHA_RATE + 10:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_RATE + 11:
                return next(catta::json::Token::character('R'));
            case STORAGE_W_CHA_RATE + 12:
                return next(catta::json::Token::character('a'));
            case STORAGE_W_CHA_RATE + 13:
                return next(catta::json::Token::character('t'));
            case STORAGE_W_CHA_RATE + 14:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_PCD_DIV + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_PCD_DIV + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_PCD_DIV + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_PCD_DIV + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_PCD_DIV + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_PCD_DIV + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_PCD_DIV + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_PCD_DIV + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_PCD_DIV + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_PCD_DIV + 9:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_PCD_DIV + 10:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_PCD_DIV + 11:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_PCD_DIV + 12:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_PCD_DIV + 13:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_PCD_DIV + 14:
                return jump(catta::json::Token::character('v'), TAIL + 0);
            case SI_CONTROL_UDC_EXT + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UDC_EXT + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UDC_EXT + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UDC_EXT + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UDC_EXT + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UDC_EXT + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UDC_EXT + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UDC_EXT + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UDC_EXT + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UDC_EXT + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UDC_EXT + 10:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_UDC_EXT + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_UDC_EXT + 12:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_UDC_EXT + 13:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_UDC_EXT + 14:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case SI_CONTROL_P_SET_POINT + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_P_SET_POINT + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_P_SET_POINT + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_P_SET_POINT + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_P_SET_POINT + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_P_SET_POINT + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_P_SET_POINT + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_P_SET_POINT + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_P_SET_POINT + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_P_SET_POINT + 9:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_P_SET_POINT + 10:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_P_SET_POINT + 11:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_P_SET_POINT + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_P_SET_POINT + 13:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_P_SET_POINT + 14:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_P_SET_POINT + 15:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_P_SET_POINT + 16:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_P_SET_POINT + 17:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case SI_CONTROL_U_MIN_EXT + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_U_MIN_EXT + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_U_MIN_EXT + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_U_MIN_EXT + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_U_MIN_EXT + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_U_MIN_EXT + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_U_MIN_EXT + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_U_MIN_EXT + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_U_MIN_EXT + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_U_MIN_EXT + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_U_MIN_EXT + 10:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_U_MIN_EXT + 11:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_U_MIN_EXT + 12:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_U_MIN_EXT + 13:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_U_MIN_EXT + 14:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_U_MIN_EXT + 15:
                return jump(catta::json::Token::character('t'), TAIL + 0);
            case SI_CONTROL_U_MAX_EXT + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_U_MAX_EXT + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_U_MAX_EXT + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_U_MAX_EXT + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_U_MAX_EXT + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_U_MAX_EXT + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_U_MAX_EXT + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_U_MAX_EXT + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_U_MAX_EXT + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_U_MAX_EXT + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_U_MAX_EXT + 10:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_U_MAX_EXT + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_U_MAX_EXT + 12:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_U_MAX_EXT + 13:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_U_MAX_EXT + 14:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_U_MAX_EXT + 15:
                return jump(catta::json::Token::character('t'), TAIL + 0);
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
    static constexpr std::uint16_t COMMON_MANUFACTURER = START + 1;
    static constexpr std::uint16_t COMMON_MODEL = COMMON_MANUFACTURER + 18;
    static constexpr std::uint16_t COMMON_SERIAL_NUMBER = COMMON_MODEL + 11;
    static constexpr std::uint16_t COMMON_DEVICE_ADDRESS = COMMON_SERIAL_NUMBER + 18;
    static constexpr std::uint16_t INVERTER_AMPS = COMMON_DEVICE_ADDRESS + 19;
    static constexpr std::uint16_t INVERTER_AMPS_PHASE_A = INVERTER_AMPS + 12;
    static constexpr std::uint16_t INVERTER_AMPS_PHASE_B = INVERTER_AMPS_PHASE_A + 18;
    static constexpr std::uint16_t INVERTER_AMPS_PHASE_C = INVERTER_AMPS_PHASE_B + 18;
    static constexpr std::uint16_t INVERTER_AMPS_SCALE_FACTOR = INVERTER_AMPS_PHASE_C + 18;
    static constexpr std::uint16_t INVERTER_PHASE_VOLTAGE_A = INVERTER_AMPS_SCALE_FACTOR + 23;
    static constexpr std::uint16_t INVERTER_PHASE_VOLTAGE_B = INVERTER_PHASE_VOLTAGE_A + 21;
    static constexpr std::uint16_t INVERTER_PHASE_VOLTAGE_C = INVERTER_PHASE_VOLTAGE_B + 21;
    static constexpr std::uint16_t INVERTER_PHASE_VOLTAGE_SCALE_FACTOR = INVERTER_PHASE_VOLTAGE_C + 21;
    static constexpr std::uint16_t INVERTER_WATT = INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 31;
    static constexpr std::uint16_t INVERTER_WATT_SCALE_FACTOR = INVERTER_WATT + 12;
    static constexpr std::uint16_t INVERTER_HERTZ = INVERTER_WATT_SCALE_FACTOR + 23;
    static constexpr std::uint16_t INVERTER_HERTZ_SCALE_FACTOR = INVERTER_HERTZ + 13;
    static constexpr std::uint16_t INVERTER_POWER_FACTOR = INVERTER_HERTZ_SCALE_FACTOR + 24;
    static constexpr std::uint16_t INVERTER_POWER_FACTOR_SCALE_FACTOR = INVERTER_POWER_FACTOR + 19;
    static constexpr std::uint16_t INVERTER_WATT_HOURS = INVERTER_POWER_FACTOR_SCALE_FACTOR + 30;
    static constexpr std::uint16_t INVERTER_WATT_HOURS_SCALE_FACTOR = INVERTER_WATT_HOURS + 17;
    static constexpr std::uint16_t INVERTER_DC_VOLTAGE = INVERTER_WATT_HOURS_SCALE_FACTOR + 28;
    static constexpr std::uint16_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = INVERTER_DC_VOLTAGE + 17;
    static constexpr std::uint16_t INVERTER_TEMPERATURE = INVERTER_DC_VOLTAGE_SCALE_FACTOR + 28;
    static constexpr std::uint16_t INVERTER_TEMPERATURE_SCALE_FACTOR = INVERTER_TEMPERATURE + 19;
    static constexpr std::uint16_t INVERTER_OPERATING_STATE = INVERTER_TEMPERATURE_SCALE_FACTOR + 30;
    static constexpr std::uint16_t INVERTER_VENDOR_OPERATING_STATE = INVERTER_OPERATING_STATE + 22;
    static constexpr std::uint16_t INVERTER_VENDOR_EVENT_BITFIELD = INVERTER_VENDOR_OPERATING_STATE + 28;
    static constexpr std::uint16_t NAMEPLATE_DER_TYPE = INVERTER_VENDOR_EVENT_BITFIELD + 27;
    static constexpr std::uint16_t BASIC_SETTINGS_W_MAX = NAMEPLATE_DER_TYPE + 16;
    static constexpr std::uint16_t BASIC_SETTINGS_V_MAX = BASIC_SETTINGS_W_MAX + 17;
    static constexpr std::uint16_t BASIC_SETTINGS_V_MIN = BASIC_SETTINGS_V_MAX + 17;
    static constexpr std::uint16_t BASIC_SETTINGS_ECP_NOM_HZ = BASIC_SETTINGS_V_MIN + 17;
    static constexpr std::uint16_t BASIC_SETTINGS_CONN_PHASE = BASIC_SETTINGS_ECP_NOM_HZ + 21;
    static constexpr std::uint16_t BASIC_SETTINGS_W_MAX_SCALE_FACTOR = BASIC_SETTINGS_CONN_PHASE + 22;
    static constexpr std::uint16_t BASIC_SETTINGS_V_MIN_MAX = BASIC_SETTINGS_W_MAX_SCALE_FACTOR + 28;
    static constexpr std::uint16_t BASIC_SETTINGS_VA_MAX_SCALE_FACTOR = BASIC_SETTINGS_V_MIN_MAX + 20;
    static constexpr std::uint16_t BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR = BASIC_SETTINGS_VA_MAX_SCALE_FACTOR + 29;
    static constexpr std::uint16_t BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR = BASIC_SETTINGS_VAR_MAX_SCALE_FACTOR + 30;
    static constexpr std::uint16_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = BASIC_SETTINGS_ECP_NOM_HZ_SCALE_FACTOR + 32;
    static constexpr std::uint16_t IMMEDIATE_CONNECTION_TIMEOUT = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 30;
    static constexpr std::uint16_t IMMEDIATE_CONNECTION_CONTROL = IMMEDIATE_CONNECTION_TIMEOUT + 26;
    static constexpr std::uint16_t IMMEDIATE_POWER_LIMIT = IMMEDIATE_CONNECTION_CONTROL + 26;
    static constexpr std::uint16_t STORAGE_W_CHA_MAX = IMMEDIATE_POWER_LIMIT + 19;
    static constexpr std::uint16_t STORAGE_W_CHA_RATE = STORAGE_W_CHA_MAX + 14;
    static constexpr std::uint16_t SI_CONTROL_PCD_DIV = STORAGE_W_CHA_RATE + 15;
    static constexpr std::uint16_t SI_CONTROL_UDC_EXT = SI_CONTROL_PCD_DIV + 15;
    static constexpr std::uint16_t SI_CONTROL_P_SET_POINT = SI_CONTROL_UDC_EXT + 15;
    static constexpr std::uint16_t SI_CONTROL_U_MIN_EXT = SI_CONTROL_P_SET_POINT + 18;
    static constexpr std::uint16_t SI_CONTROL_U_MAX_EXT = SI_CONTROL_U_MIN_EXT + 16;
    static constexpr std::uint16_t TAIL = SI_CONTROL_U_MAX_EXT + 16;
    static constexpr std::uint16_t DONE = TAIL + 2;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
