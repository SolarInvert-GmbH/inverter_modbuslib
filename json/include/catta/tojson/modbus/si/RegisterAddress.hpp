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
                    _state = COMMON_VERSION + 0;
                    break;
                case 3:
                    _state = COMMON_SERIAL_NUMBER + 0;
                    break;
                case 4:
                    _state = COMMON_DEVICE_ADDRESS + 0;
                    break;
                case 5:
                    _state = INVERTER_AMPS + 0;
                    break;
                case 6:
                    _state = INVERTER_AMPS_PHASE_A + 0;
                    break;
                case 7:
                    _state = INVERTER_AMPS_PHASE_B + 0;
                    break;
                case 8:
                    _state = INVERTER_AMPS_PHASE_C + 0;
                    break;
                case 9:
                    _state = INVERTER_AMPS_SCALE_FACTOR + 0;
                    break;
                case 10:
                    _state = INVERTER_PHASE_VOLTAGE_A + 0;
                    break;
                case 11:
                    _state = INVERTER_PHASE_VOLTAGE_B + 0;
                    break;
                case 12:
                    _state = INVERTER_PHASE_VOLTAGE_C + 0;
                    break;
                case 13:
                    _state = INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 0;
                    break;
                case 14:
                    _state = INVERTER_AC_POWER + 0;
                    break;
                case 15:
                    _state = INVERTER_AC_POWER_SCALE_FACTOR + 0;
                    break;
                case 16:
                    _state = INVERTER_HERTZ + 0;
                    break;
                case 17:
                    _state = INVERTER_HERTZ_SCALE_FACTOR + 0;
                    break;
                case 18:
                    _state = INVERTER_AC_APPARENT_POWER + 0;
                    break;
                case 19:
                    _state = INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 0;
                    break;
                case 20:
                    _state = INVERTER_AC_REACTIVE_POWER + 0;
                    break;
                case 21:
                    _state = INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 0;
                    break;
                case 22:
                    _state = INVERTER_POWER_FACTOR + 0;
                    break;
                case 23:
                    _state = INVERTER_POWER_FACTOR_SCALE_FACTOR + 0;
                    break;
                case 24:
                    _state = INVERTER_WATT_HOURS + 0;
                    break;
                case 25:
                    _state = INVERTER_WATT_HOURS_SCALE_FACTOR + 0;
                    break;
                case 26:
                    _state = INVERTER_DC_VOLTAGE + 0;
                    break;
                case 27:
                    _state = INVERTER_DC_VOLTAGE_SCALE_FACTOR + 0;
                    break;
                case 28:
                    _state = INVERTER_DC_POWER + 0;
                    break;
                case 29:
                    _state = INVERTER_DC_POWER_SCALE_FACTOR + 0;
                    break;
                case 30:
                    _state = INVERTER_TEMPERATURE + 0;
                    break;
                case 31:
                    _state = INVERTER_TEMPERATURE_SCALE_FACTOR + 0;
                    break;
                case 32:
                    _state = INVERTER_OPERATING_STATE + 0;
                    break;
                case 33:
                    _state = INVERTER_VENDOR_OPERATING_STATE + 0;
                    break;
                case 34:
                    _state = INVERTER_VENDOR_EVENT_BITFIELD1 + 0;
                    break;
                case 35:
                    _state = INVERTER_VENDOR_EVENT_BITFIELD2 + 0;
                    break;
                case 36:
                    _state = INVERTER_VENDOR_EVENT_BITFIELD3 + 0;
                    break;
                case 37:
                    _state = INVERTER_VENDOR_EVENT_BITFIELD4 + 0;
                    break;
                case 38:
                    _state = NAMEPLATE_DER_TYPE + 0;
                    break;
                case 39:
                    _state = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 0;
                    break;
                case 40:
                    _state = EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 0;
                    break;
                case 41:
                    _state = MPP_STEP_DAC0 + 0;
                    break;
                case 42:
                    _state = MPP_STEP_DAC1 + 0;
                    break;
                case 43:
                    _state = MPP_STEP_DAC2 + 0;
                    break;
                case 44:
                    _state = MPP_STEP_DAC3 + 0;
                    break;
                case 45:
                    _state = MPP_STEP_UDC0 + 0;
                    break;
                case 46:
                    _state = MPP_STEP_UDC1 + 0;
                    break;
                case 47:
                    _state = MPP_STEP_UDC2 + 0;
                    break;
                case 48:
                    _state = MPP_STEP_UDC3 + 0;
                    break;
                case 49:
                    _state = MPP_SAMPLE_DAC0 + 0;
                    break;
                case 50:
                    _state = MPP_SAMPLE_DAC1 + 0;
                    break;
                case 51:
                    _state = MPP_SAMPLE_DAC2 + 0;
                    break;
                case 52:
                    _state = MPP_SAMPLE_DAC3 + 0;
                    break;
                case 53:
                    _state = MPP_SAMPLE_UDC0 + 0;
                    break;
                case 54:
                    _state = MPP_SAMPLE_UDC1 + 0;
                    break;
                case 55:
                    _state = MPP_SAMPLE_UDC2 + 0;
                    break;
                default:
                    _state = MPP_SAMPLE_UDC3 + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? jump(catta::json::Token::nullObject(), TAIL + 1) : start(catta::json::Token::openString());
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
            case COMMON_VERSION + 0:
                return next(catta::json::Token::character('C'));
            case COMMON_VERSION + 1:
                return next(catta::json::Token::character('o'));
            case COMMON_VERSION + 2:
                return next(catta::json::Token::character('m'));
            case COMMON_VERSION + 3:
                return next(catta::json::Token::character('m'));
            case COMMON_VERSION + 4:
                return next(catta::json::Token::character('o'));
            case COMMON_VERSION + 5:
                return next(catta::json::Token::character('n'));
            case COMMON_VERSION + 6:
                return next(catta::json::Token::character('V'));
            case COMMON_VERSION + 7:
                return next(catta::json::Token::character('e'));
            case COMMON_VERSION + 8:
                return next(catta::json::Token::character('r'));
            case COMMON_VERSION + 9:
                return next(catta::json::Token::character('s'));
            case COMMON_VERSION + 10:
                return next(catta::json::Token::character('i'));
            case COMMON_VERSION + 11:
                return next(catta::json::Token::character('o'));
            case COMMON_VERSION + 12:
                return jump(catta::json::Token::character('n'), TAIL + 0);
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
            case INVERTER_AC_POWER + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_POWER + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_POWER + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_POWER + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_POWER + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_POWER + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_POWER + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_POWER + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_POWER + 10:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_POWER + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_POWER + 12:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_POWER + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER + 14:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_AC_POWER_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('S'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('l'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('F'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_POWER_SCALE_FACTOR + 25:
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
            case INVERTER_AC_APPARENT_POWER + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_APPARENT_POWER + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_APPARENT_POWER + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_APPARENT_POWER + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_APPARENT_POWER + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_APPARENT_POWER + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_APPARENT_POWER + 10:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_APPARENT_POWER + 11:
                return next(catta::json::Token::character('p'));
            case INVERTER_AC_APPARENT_POWER + 12:
                return next(catta::json::Token::character('p'));
            case INVERTER_AC_APPARENT_POWER + 13:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_APPARENT_POWER + 14:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER + 15:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER + 16:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_APPARENT_POWER + 17:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_APPARENT_POWER + 18:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_APPARENT_POWER + 19:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_APPARENT_POWER + 20:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_APPARENT_POWER + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER + 22:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('p'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('p'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('S'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('l'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('F'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 31:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 32:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 33:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_AC_REACTIVE_POWER + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_REACTIVE_POWER + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_REACTIVE_POWER + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_REACTIVE_POWER + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_REACTIVE_POWER + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_REACTIVE_POWER + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_REACTIVE_POWER + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_REACTIVE_POWER + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER + 10:
                return next(catta::json::Token::character('R'));
            case INVERTER_AC_REACTIVE_POWER + 11:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER + 12:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_REACTIVE_POWER + 13:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER + 14:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_REACTIVE_POWER + 15:
                return next(catta::json::Token::character('i'));
            case INVERTER_AC_REACTIVE_POWER + 16:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_REACTIVE_POWER + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER + 18:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_REACTIVE_POWER + 19:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_REACTIVE_POWER + 20:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_REACTIVE_POWER + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER + 22:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('A'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('R'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('i'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('v'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('P'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('w'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('r'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('S'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('l'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('e'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('F'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('a'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('c'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 31:
                return next(catta::json::Token::character('t'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 32:
                return next(catta::json::Token::character('o'));
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 33:
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
            case INVERTER_DC_POWER + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_DC_POWER + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_DC_POWER + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_DC_POWER + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_POWER + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_POWER + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_POWER + 8:
                return next(catta::json::Token::character('D'));
            case INVERTER_DC_POWER + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_POWER + 10:
                return next(catta::json::Token::character('P'));
            case INVERTER_DC_POWER + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_POWER + 12:
                return next(catta::json::Token::character('w'));
            case INVERTER_DC_POWER + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER + 14:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case INVERTER_DC_POWER_SCALE_FACTOR + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('D'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('P'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('w'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('S'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('F'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_POWER_SCALE_FACTOR + 25:
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
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 14:
                return next(catta::json::Token::character('E'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 15:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 17:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 19:
                return next(catta::json::Token::character('B'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 22:
                return next(catta::json::Token::character('f'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 23:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 25:
                return next(catta::json::Token::character('l'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 26:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD1 + 27:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 14:
                return next(catta::json::Token::character('E'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 15:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 17:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 19:
                return next(catta::json::Token::character('B'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 22:
                return next(catta::json::Token::character('f'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 23:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 25:
                return next(catta::json::Token::character('l'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 26:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD2 + 27:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 14:
                return next(catta::json::Token::character('E'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 15:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 17:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 19:
                return next(catta::json::Token::character('B'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 22:
                return next(catta::json::Token::character('f'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 23:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 25:
                return next(catta::json::Token::character('l'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 26:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD3 + 27:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 0:
                return next(catta::json::Token::character('I'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 1:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 2:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 3:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 4:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 5:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 6:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 7:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 8:
                return next(catta::json::Token::character('V'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 9:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 10:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 11:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 14:
                return next(catta::json::Token::character('E'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 15:
                return next(catta::json::Token::character('v'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 16:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 17:
                return next(catta::json::Token::character('n'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 18:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 19:
                return next(catta::json::Token::character('B'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 20:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 22:
                return next(catta::json::Token::character('f'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 23:
                return next(catta::json::Token::character('i'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 25:
                return next(catta::json::Token::character('l'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 26:
                return next(catta::json::Token::character('d'));
            case INVERTER_VENDOR_EVENT_BITFIELD4 + 27:
                return jump(catta::json::Token::character('4'), TAIL + 0);
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
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 0:
                return next(catta::json::Token::character('E'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 1:
                return next(catta::json::Token::character('x'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 2:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 3:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 4:
                return next(catta::json::Token::character('n'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 5:
                return next(catta::json::Token::character('d'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 6:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 7:
                return next(catta::json::Token::character('d'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 8:
                return next(catta::json::Token::character('M'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 9:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 10:
                return next(catta::json::Token::character('s'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 11:
                return next(catta::json::Token::character('u'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 12:
                return next(catta::json::Token::character('r'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 13:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 14:
                return next(catta::json::Token::character('m'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 15:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 16:
                return next(catta::json::Token::character('n'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 17:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 18:
                return next(catta::json::Token::character('s'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 19:
                return next(catta::json::Token::character('A'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 20:
                return next(catta::json::Token::character('c'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 21:
                return next(catta::json::Token::character('L'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 22:
                return next(catta::json::Token::character('i'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 23:
                return next(catta::json::Token::character('f'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 24:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 25:
                return next(catta::json::Token::character('t'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 26:
                return next(catta::json::Token::character('i'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 27:
                return next(catta::json::Token::character('m'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 28:
                return next(catta::json::Token::character('e'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 29:
                return next(catta::json::Token::character('C'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 30:
                return next(catta::json::Token::character('h'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 31:
                return next(catta::json::Token::character('a'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 32:
                return next(catta::json::Token::character('r'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 33:
                return next(catta::json::Token::character('g'));
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 34:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case MPP_STEP_DAC0 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_DAC0 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC0 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC0 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_DAC0 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_DAC0 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_DAC0 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC0 + 7:
                return next(catta::json::Token::character('D'));
            case MPP_STEP_DAC0 + 8:
                return next(catta::json::Token::character('a'));
            case MPP_STEP_DAC0 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_DAC0 + 10:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case MPP_STEP_DAC1 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_DAC1 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC1 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC1 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_DAC1 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_DAC1 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_DAC1 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC1 + 7:
                return next(catta::json::Token::character('D'));
            case MPP_STEP_DAC1 + 8:
                return next(catta::json::Token::character('a'));
            case MPP_STEP_DAC1 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_DAC1 + 10:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case MPP_STEP_DAC2 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_DAC2 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC2 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC2 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_DAC2 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_DAC2 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_DAC2 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC2 + 7:
                return next(catta::json::Token::character('D'));
            case MPP_STEP_DAC2 + 8:
                return next(catta::json::Token::character('a'));
            case MPP_STEP_DAC2 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_DAC2 + 10:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case MPP_STEP_DAC3 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_DAC3 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC3 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC3 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_DAC3 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_DAC3 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_DAC3 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_DAC3 + 7:
                return next(catta::json::Token::character('D'));
            case MPP_STEP_DAC3 + 8:
                return next(catta::json::Token::character('a'));
            case MPP_STEP_DAC3 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_DAC3 + 10:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case MPP_STEP_UDC0 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_UDC0 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC0 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC0 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_UDC0 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_UDC0 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_UDC0 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC0 + 7:
                return next(catta::json::Token::character('U'));
            case MPP_STEP_UDC0 + 8:
                return next(catta::json::Token::character('d'));
            case MPP_STEP_UDC0 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_UDC0 + 10:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case MPP_STEP_UDC1 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_UDC1 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC1 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC1 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_UDC1 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_UDC1 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_UDC1 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC1 + 7:
                return next(catta::json::Token::character('U'));
            case MPP_STEP_UDC1 + 8:
                return next(catta::json::Token::character('d'));
            case MPP_STEP_UDC1 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_UDC1 + 10:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case MPP_STEP_UDC2 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_UDC2 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC2 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC2 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_UDC2 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_UDC2 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_UDC2 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC2 + 7:
                return next(catta::json::Token::character('U'));
            case MPP_STEP_UDC2 + 8:
                return next(catta::json::Token::character('d'));
            case MPP_STEP_UDC2 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_UDC2 + 10:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case MPP_STEP_UDC3 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_STEP_UDC3 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC3 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC3 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_STEP_UDC3 + 4:
                return next(catta::json::Token::character('t'));
            case MPP_STEP_UDC3 + 5:
                return next(catta::json::Token::character('e'));
            case MPP_STEP_UDC3 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_STEP_UDC3 + 7:
                return next(catta::json::Token::character('U'));
            case MPP_STEP_UDC3 + 8:
                return next(catta::json::Token::character('d'));
            case MPP_STEP_UDC3 + 9:
                return next(catta::json::Token::character('c'));
            case MPP_STEP_UDC3 + 10:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case MPP_SAMPLE_DAC0 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_DAC0 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC0 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC0 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_DAC0 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC0 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_DAC0 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC0 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_DAC0 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_DAC0 + 9:
                return next(catta::json::Token::character('D'));
            case MPP_SAMPLE_DAC0 + 10:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC0 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_DAC0 + 12:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case MPP_SAMPLE_DAC1 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_DAC1 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC1 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC1 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_DAC1 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC1 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_DAC1 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC1 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_DAC1 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_DAC1 + 9:
                return next(catta::json::Token::character('D'));
            case MPP_SAMPLE_DAC1 + 10:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC1 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_DAC1 + 12:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case MPP_SAMPLE_DAC2 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_DAC2 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC2 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC2 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_DAC2 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC2 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_DAC2 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC2 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_DAC2 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_DAC2 + 9:
                return next(catta::json::Token::character('D'));
            case MPP_SAMPLE_DAC2 + 10:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC2 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_DAC2 + 12:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case MPP_SAMPLE_DAC3 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_DAC3 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC3 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC3 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_DAC3 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC3 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_DAC3 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_DAC3 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_DAC3 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_DAC3 + 9:
                return next(catta::json::Token::character('D'));
            case MPP_SAMPLE_DAC3 + 10:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_DAC3 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_DAC3 + 12:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case MPP_SAMPLE_UDC0 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_UDC0 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC0 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC0 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_UDC0 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_UDC0 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_UDC0 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC0 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_UDC0 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_UDC0 + 9:
                return next(catta::json::Token::character('U'));
            case MPP_SAMPLE_UDC0 + 10:
                return next(catta::json::Token::character('d'));
            case MPP_SAMPLE_UDC0 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_UDC0 + 12:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case MPP_SAMPLE_UDC1 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_UDC1 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC1 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC1 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_UDC1 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_UDC1 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_UDC1 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC1 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_UDC1 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_UDC1 + 9:
                return next(catta::json::Token::character('U'));
            case MPP_SAMPLE_UDC1 + 10:
                return next(catta::json::Token::character('d'));
            case MPP_SAMPLE_UDC1 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_UDC1 + 12:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case MPP_SAMPLE_UDC2 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_UDC2 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC2 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC2 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_UDC2 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_UDC2 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_UDC2 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC2 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_UDC2 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_UDC2 + 9:
                return next(catta::json::Token::character('U'));
            case MPP_SAMPLE_UDC2 + 10:
                return next(catta::json::Token::character('d'));
            case MPP_SAMPLE_UDC2 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_UDC2 + 12:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case MPP_SAMPLE_UDC3 + 0:
                return next(catta::json::Token::character('M'));
            case MPP_SAMPLE_UDC3 + 1:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC3 + 2:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC3 + 3:
                return next(catta::json::Token::character('S'));
            case MPP_SAMPLE_UDC3 + 4:
                return next(catta::json::Token::character('a'));
            case MPP_SAMPLE_UDC3 + 5:
                return next(catta::json::Token::character('m'));
            case MPP_SAMPLE_UDC3 + 6:
                return next(catta::json::Token::character('p'));
            case MPP_SAMPLE_UDC3 + 7:
                return next(catta::json::Token::character('l'));
            case MPP_SAMPLE_UDC3 + 8:
                return next(catta::json::Token::character('e'));
            case MPP_SAMPLE_UDC3 + 9:
                return next(catta::json::Token::character('U'));
            case MPP_SAMPLE_UDC3 + 10:
                return next(catta::json::Token::character('d'));
            case MPP_SAMPLE_UDC3 + 11:
                return next(catta::json::Token::character('c'));
            case MPP_SAMPLE_UDC3 + 12:
                return jump(catta::json::Token::character('3'), TAIL + 0);
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
    static constexpr std::uint16_t COMMON_VERSION = COMMON_MODEL + 11;
    static constexpr std::uint16_t COMMON_SERIAL_NUMBER = COMMON_VERSION + 13;
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
    static constexpr std::uint16_t INVERTER_AC_POWER = INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 31;
    static constexpr std::uint16_t INVERTER_AC_POWER_SCALE_FACTOR = INVERTER_AC_POWER + 15;
    static constexpr std::uint16_t INVERTER_HERTZ = INVERTER_AC_POWER_SCALE_FACTOR + 26;
    static constexpr std::uint16_t INVERTER_HERTZ_SCALE_FACTOR = INVERTER_HERTZ + 13;
    static constexpr std::uint16_t INVERTER_AC_APPARENT_POWER = INVERTER_HERTZ_SCALE_FACTOR + 24;
    static constexpr std::uint16_t INVERTER_AC_APPARENT_POWER_SCALE_FACTOR = INVERTER_AC_APPARENT_POWER + 23;
    static constexpr std::uint16_t INVERTER_AC_REACTIVE_POWER = INVERTER_AC_APPARENT_POWER_SCALE_FACTOR + 34;
    static constexpr std::uint16_t INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR = INVERTER_AC_REACTIVE_POWER + 23;
    static constexpr std::uint16_t INVERTER_POWER_FACTOR = INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR + 34;
    static constexpr std::uint16_t INVERTER_POWER_FACTOR_SCALE_FACTOR = INVERTER_POWER_FACTOR + 19;
    static constexpr std::uint16_t INVERTER_WATT_HOURS = INVERTER_POWER_FACTOR_SCALE_FACTOR + 30;
    static constexpr std::uint16_t INVERTER_WATT_HOURS_SCALE_FACTOR = INVERTER_WATT_HOURS + 17;
    static constexpr std::uint16_t INVERTER_DC_VOLTAGE = INVERTER_WATT_HOURS_SCALE_FACTOR + 28;
    static constexpr std::uint16_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = INVERTER_DC_VOLTAGE + 17;
    static constexpr std::uint16_t INVERTER_DC_POWER = INVERTER_DC_VOLTAGE_SCALE_FACTOR + 28;
    static constexpr std::uint16_t INVERTER_DC_POWER_SCALE_FACTOR = INVERTER_DC_POWER + 15;
    static constexpr std::uint16_t INVERTER_TEMPERATURE = INVERTER_DC_POWER_SCALE_FACTOR + 26;
    static constexpr std::uint16_t INVERTER_TEMPERATURE_SCALE_FACTOR = INVERTER_TEMPERATURE + 19;
    static constexpr std::uint16_t INVERTER_OPERATING_STATE = INVERTER_TEMPERATURE_SCALE_FACTOR + 30;
    static constexpr std::uint16_t INVERTER_VENDOR_OPERATING_STATE = INVERTER_OPERATING_STATE + 22;
    static constexpr std::uint16_t INVERTER_VENDOR_EVENT_BITFIELD1 = INVERTER_VENDOR_OPERATING_STATE + 28;
    static constexpr std::uint16_t INVERTER_VENDOR_EVENT_BITFIELD2 = INVERTER_VENDOR_EVENT_BITFIELD1 + 28;
    static constexpr std::uint16_t INVERTER_VENDOR_EVENT_BITFIELD3 = INVERTER_VENDOR_EVENT_BITFIELD2 + 28;
    static constexpr std::uint16_t INVERTER_VENDOR_EVENT_BITFIELD4 = INVERTER_VENDOR_EVENT_BITFIELD3 + 28;
    static constexpr std::uint16_t NAMEPLATE_DER_TYPE = INVERTER_VENDOR_EVENT_BITFIELD4 + 28;
    static constexpr std::uint16_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = NAMEPLATE_DER_TYPE + 16;
    static constexpr std::uint16_t EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 30;
    static constexpr std::uint16_t MPP_STEP_DAC0 = EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 35;
    static constexpr std::uint16_t MPP_STEP_DAC1 = MPP_STEP_DAC0 + 11;
    static constexpr std::uint16_t MPP_STEP_DAC2 = MPP_STEP_DAC1 + 11;
    static constexpr std::uint16_t MPP_STEP_DAC3 = MPP_STEP_DAC2 + 11;
    static constexpr std::uint16_t MPP_STEP_UDC0 = MPP_STEP_DAC3 + 11;
    static constexpr std::uint16_t MPP_STEP_UDC1 = MPP_STEP_UDC0 + 11;
    static constexpr std::uint16_t MPP_STEP_UDC2 = MPP_STEP_UDC1 + 11;
    static constexpr std::uint16_t MPP_STEP_UDC3 = MPP_STEP_UDC2 + 11;
    static constexpr std::uint16_t MPP_SAMPLE_DAC0 = MPP_STEP_UDC3 + 11;
    static constexpr std::uint16_t MPP_SAMPLE_DAC1 = MPP_SAMPLE_DAC0 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_DAC2 = MPP_SAMPLE_DAC1 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_DAC3 = MPP_SAMPLE_DAC2 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_UDC0 = MPP_SAMPLE_DAC3 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_UDC1 = MPP_SAMPLE_UDC0 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_UDC2 = MPP_SAMPLE_UDC1 + 13;
    static constexpr std::uint16_t MPP_SAMPLE_UDC3 = MPP_SAMPLE_UDC2 + 13;
    static constexpr std::uint16_t TAIL = MPP_SAMPLE_UDC3 + 13;
    static constexpr std::uint16_t DONE = TAIL + 2;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
