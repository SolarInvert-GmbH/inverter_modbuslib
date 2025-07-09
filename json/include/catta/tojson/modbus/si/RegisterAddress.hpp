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
                    _state = BASIC_SETTINGS_MAX_POWER + 0;
                    break;
                case 40:
                    _state = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 0;
                    break;
                case 41:
                    _state = EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 0;
                    break;
                case 42:
                    _state = STORAGE_NOMINAL_CHARGE_POWER + 0;
                    break;
                case 43:
                    _state = SI_CONTROL_MODUS + 0;
                    break;
                case 44:
                    _state = SI_CONTROL_VOLTAGE_DC_START_READ + 0;
                    break;
                case 45:
                    _state = SI_CONTROL_BATTERY_BI_MODE_READ + 0;
                    break;
                case 46:
                    _state = SI_CONTROL_BATTERY_SAFTY_MODE_READ + 0;
                    break;
                case 47:
                    _state = SI_CONTROL_BATTERY_CV_MODE_READ + 0;
                    break;
                case 48:
                    _state = SI_CONTROL_DC_LOW_READ + 0;
                    break;
                case 49:
                    _state = SI_CONTROL_DC_HIGH_READ + 0;
                    break;
                case 50:
                    _state = SI_CONTROL_TRACKING_SELECTION + 0;
                    break;
                case 51:
                    _state = SI_CONTROL_START_COUNTDOWN + 0;
                    break;
                case 52:
                    _state = SI_CONTROL_NIGHT_SHUTDOWN + 0;
                    break;
                case 53:
                    _state = SI_CONTROL_PMAX + 0;
                    break;
                case 54:
                    _state = SI_CONTROL_COSPHI + 0;
                    break;
                case 55:
                    _state = SI_CONTROL_UPTIME + 0;
                    break;
                case 56:
                    _state = SI_CONTROL_MPP_STEP_DAC0 + 0;
                    break;
                case 57:
                    _state = SI_CONTROL_MPP_STEP_DAC1 + 0;
                    break;
                case 58:
                    _state = SI_CONTROL_MPP_STEP_DAC2 + 0;
                    break;
                case 59:
                    _state = SI_CONTROL_MPP_STEP_DAC3 + 0;
                    break;
                case 60:
                    _state = SI_CONTROL_MPP_STEP_UDC0 + 0;
                    break;
                case 61:
                    _state = SI_CONTROL_MPP_STEP_UDC1 + 0;
                    break;
                case 62:
                    _state = SI_CONTROL_MPP_STEP_UDC2 + 0;
                    break;
                case 63:
                    _state = SI_CONTROL_MPP_STEP_UDC3 + 0;
                    break;
                case 64:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC0 + 0;
                    break;
                case 65:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC1 + 0;
                    break;
                case 66:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC2 + 0;
                    break;
                case 67:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC3 + 0;
                    break;
                case 68:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC0 + 0;
                    break;
                case 69:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC1 + 0;
                    break;
                case 70:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC2 + 0;
                    break;
                case 71:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC3 + 0;
                    break;
                case 72:
                    _state = SI_CONTROL_REDUCTION + 0;
                    break;
                case 73:
                    _state = SI_CONTROL_SINEDUTY + 0;
                    break;
                case 74:
                    _state = SI_CONTROL_FILTER_WIND_CURVE + 0;
                    break;
                case 75:
                    _state = SI_CONTROL_WIND_CURVE_X00 + 0;
                    break;
                case 76:
                    _state = SI_CONTROL_WIND_CURVE_X01 + 0;
                    break;
                case 77:
                    _state = SI_CONTROL_WIND_CURVE_X02 + 0;
                    break;
                case 78:
                    _state = SI_CONTROL_WIND_CURVE_X03 + 0;
                    break;
                case 79:
                    _state = SI_CONTROL_WIND_CURVE_X04 + 0;
                    break;
                case 80:
                    _state = SI_CONTROL_WIND_CURVE_X05 + 0;
                    break;
                case 81:
                    _state = SI_CONTROL_WIND_CURVE_X06 + 0;
                    break;
                case 82:
                    _state = SI_CONTROL_WIND_CURVE_X07 + 0;
                    break;
                case 83:
                    _state = SI_CONTROL_WIND_CURVE_X08 + 0;
                    break;
                case 84:
                    _state = SI_CONTROL_WIND_CURVE_X09 + 0;
                    break;
                case 85:
                    _state = SI_CONTROL_WIND_CURVE_X10 + 0;
                    break;
                case 86:
                    _state = SI_CONTROL_WIND_CURVE_X11 + 0;
                    break;
                case 87:
                    _state = SI_CONTROL_WIND_CURVE_X12 + 0;
                    break;
                case 88:
                    _state = SI_CONTROL_WIND_CURVE_X13 + 0;
                    break;
                case 89:
                    _state = SI_CONTROL_WIND_CURVE_X14 + 0;
                    break;
                case 90:
                    _state = SI_CONTROL_WIND_CURVE_X15 + 0;
                    break;
                case 91:
                    _state = SI_CONTROL_WIND_CURVE_Y00_READ + 0;
                    break;
                case 92:
                    _state = SI_CONTROL_WIND_CURVE_Y01_READ + 0;
                    break;
                case 93:
                    _state = SI_CONTROL_WIND_CURVE_Y02_READ + 0;
                    break;
                case 94:
                    _state = SI_CONTROL_WIND_CURVE_Y03_READ + 0;
                    break;
                case 95:
                    _state = SI_CONTROL_WIND_CURVE_Y04_READ + 0;
                    break;
                case 96:
                    _state = SI_CONTROL_WIND_CURVE_Y05_READ + 0;
                    break;
                case 97:
                    _state = SI_CONTROL_WIND_CURVE_Y06_READ + 0;
                    break;
                case 98:
                    _state = SI_CONTROL_WIND_CURVE_Y07_READ + 0;
                    break;
                case 99:
                    _state = SI_CONTROL_WIND_CURVE_Y08_READ + 0;
                    break;
                case 100:
                    _state = SI_CONTROL_WIND_CURVE_Y09_READ + 0;
                    break;
                case 101:
                    _state = SI_CONTROL_WIND_CURVE_Y10_READ + 0;
                    break;
                case 102:
                    _state = SI_CONTROL_WIND_CURVE_Y11_READ + 0;
                    break;
                case 103:
                    _state = SI_CONTROL_WIND_CURVE_Y12_READ + 0;
                    break;
                case 104:
                    _state = SI_CONTROL_WIND_CURVE_Y13_READ + 0;
                    break;
                case 105:
                    _state = SI_CONTROL_WIND_CURVE_Y14_READ + 0;
                    break;
                case 106:
                    _state = SI_CONTROL_WIND_CURVE_Y15_READ + 0;
                    break;
                case 107:
                    _state = SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 0;
                    break;
                case 108:
                    _state = SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 0;
                    break;
                case 109:
                    _state = SI_CONTROL_VOLTAGE_DC_START_WRITE + 0;
                    break;
                case 110:
                    _state = SI_CONTROL_BATTERY_BI_MODE_WRITE + 0;
                    break;
                case 111:
                    _state = SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 0;
                    break;
                case 112:
                    _state = SI_CONTROL_BATTERY_CV_MODE_WRITE + 0;
                    break;
                case 113:
                    _state = SI_CONTROL_DC_LOW_WRITE + 0;
                    break;
                case 114:
                    _state = SI_CONTROL_DC_HIGH_WRITE + 0;
                    break;
                case 115:
                    _state = SI_CONTROL_WIND_CURVE_Y00_WRITE + 0;
                    break;
                case 116:
                    _state = SI_CONTROL_WIND_CURVE_Y01_WRITE + 0;
                    break;
                case 117:
                    _state = SI_CONTROL_WIND_CURVE_Y02_WRITE + 0;
                    break;
                case 118:
                    _state = SI_CONTROL_WIND_CURVE_Y03_WRITE + 0;
                    break;
                case 119:
                    _state = SI_CONTROL_WIND_CURVE_Y04_WRITE + 0;
                    break;
                case 120:
                    _state = SI_CONTROL_WIND_CURVE_Y05_WRITE + 0;
                    break;
                case 121:
                    _state = SI_CONTROL_WIND_CURVE_Y06_WRITE + 0;
                    break;
                case 122:
                    _state = SI_CONTROL_WIND_CURVE_Y07_WRITE + 0;
                    break;
                case 123:
                    _state = SI_CONTROL_WIND_CURVE_Y08_WRITE + 0;
                    break;
                case 124:
                    _state = SI_CONTROL_WIND_CURVE_Y09_WRITE + 0;
                    break;
                case 125:
                    _state = SI_CONTROL_WIND_CURVE_Y10_WRITE + 0;
                    break;
                case 126:
                    _state = SI_CONTROL_WIND_CURVE_Y11_WRITE + 0;
                    break;
                case 127:
                    _state = SI_CONTROL_WIND_CURVE_Y12_WRITE + 0;
                    break;
                case 128:
                    _state = SI_CONTROL_WIND_CURVE_Y13_WRITE + 0;
                    break;
                case 129:
                    _state = SI_CONTROL_WIND_CURVE_Y14_WRITE + 0;
                    break;
                case 130:
                    _state = SI_CONTROL_WIND_CURVE_Y15_WRITE + 0;
                    break;
                case 131:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 0;
                    break;
                case 132:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 0;
                    break;
                case 133:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 0;
                    break;
                case 134:
                    _state = SI_CONTROL_DAC_CURVE_Y0_READ + 0;
                    break;
                case 135:
                    _state = SI_CONTROL_DAC_CURVE_Y1_READ + 0;
                    break;
                case 136:
                    _state = SI_CONTROL_DAC_CURVE_Y2_READ + 0;
                    break;
                case 137:
                    _state = SI_CONTROL_DAC_CURVE_Y3_READ + 0;
                    break;
                case 138:
                    _state = SI_CONTROL_DAC_CURVE_Y4_READ + 0;
                    break;
                case 139:
                    _state = SI_CONTROL_DAC_CURVE_Y5_READ + 0;
                    break;
                case 140:
                    _state = SI_CONTROL_DAC_CURVE_Y6_READ + 0;
                    break;
                case 141:
                    _state = SI_CONTROL_DAC_CURVE_Y7_READ + 0;
                    break;
                case 142:
                    _state = SI_CONTROL_DAC_CURVE_Y8_READ + 0;
                    break;
                case 143:
                    _state = SI_CONTROL_DAC_CURVE_Y9_READ + 0;
                    break;
                case 144:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X0 + 0;
                    break;
                case 145:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X1 + 0;
                    break;
                case 146:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X2 + 0;
                    break;
                case 147:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 0;
                    break;
                case 148:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 0;
                    break;
                case 149:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 0;
                    break;
                case 150:
                    _state = SI_CONTROL_DAC_CURVE_X0 + 0;
                    break;
                case 151:
                    _state = SI_CONTROL_DAC_CURVE_X1 + 0;
                    break;
                case 152:
                    _state = SI_CONTROL_DAC_CURVE_X2 + 0;
                    break;
                case 153:
                    _state = SI_CONTROL_DAC_CURVE_X3 + 0;
                    break;
                case 154:
                    _state = SI_CONTROL_DAC_CURVE_X4 + 0;
                    break;
                case 155:
                    _state = SI_CONTROL_DAC_CURVE_X5 + 0;
                    break;
                case 156:
                    _state = SI_CONTROL_DAC_CURVE_X6 + 0;
                    break;
                case 157:
                    _state = SI_CONTROL_DAC_CURVE_X7 + 0;
                    break;
                case 158:
                    _state = SI_CONTROL_DAC_CURVE_X8 + 0;
                    break;
                case 159:
                    _state = SI_CONTROL_DAC_CURVE_X9 + 0;
                    break;
                case 160:
                    _state = SI_CONTROL_DAC_CURVE_Y0_WRITE + 0;
                    break;
                case 161:
                    _state = SI_CONTROL_DAC_CURVE_Y1_WRITE + 0;
                    break;
                case 162:
                    _state = SI_CONTROL_DAC_CURVE_Y2_WRITE + 0;
                    break;
                case 163:
                    _state = SI_CONTROL_DAC_CURVE_Y3_WRITE + 0;
                    break;
                case 164:
                    _state = SI_CONTROL_DAC_CURVE_Y4_WRITE + 0;
                    break;
                case 165:
                    _state = SI_CONTROL_DAC_CURVE_Y5_WRITE + 0;
                    break;
                case 166:
                    _state = SI_CONTROL_DAC_CURVE_Y6_WRITE + 0;
                    break;
                case 167:
                    _state = SI_CONTROL_DAC_CURVE_Y7_WRITE + 0;
                    break;
                case 168:
                    _state = SI_CONTROL_DAC_CURVE_Y8_WRITE + 0;
                    break;
                default:
                    _state = SI_CONTROL_DAC_CURVE_Y9_WRITE + 0;
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
            case BASIC_SETTINGS_MAX_POWER + 0:
                return next(catta::json::Token::character('B'));
            case BASIC_SETTINGS_MAX_POWER + 1:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_MAX_POWER + 2:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_MAX_POWER + 3:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_MAX_POWER + 4:
                return next(catta::json::Token::character('c'));
            case BASIC_SETTINGS_MAX_POWER + 5:
                return next(catta::json::Token::character('S'));
            case BASIC_SETTINGS_MAX_POWER + 6:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_MAX_POWER + 7:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_MAX_POWER + 8:
                return next(catta::json::Token::character('t'));
            case BASIC_SETTINGS_MAX_POWER + 9:
                return next(catta::json::Token::character('i'));
            case BASIC_SETTINGS_MAX_POWER + 10:
                return next(catta::json::Token::character('n'));
            case BASIC_SETTINGS_MAX_POWER + 11:
                return next(catta::json::Token::character('g'));
            case BASIC_SETTINGS_MAX_POWER + 12:
                return next(catta::json::Token::character('s'));
            case BASIC_SETTINGS_MAX_POWER + 13:
                return next(catta::json::Token::character('M'));
            case BASIC_SETTINGS_MAX_POWER + 14:
                return next(catta::json::Token::character('a'));
            case BASIC_SETTINGS_MAX_POWER + 15:
                return next(catta::json::Token::character('x'));
            case BASIC_SETTINGS_MAX_POWER + 16:
                return next(catta::json::Token::character('P'));
            case BASIC_SETTINGS_MAX_POWER + 17:
                return next(catta::json::Token::character('o'));
            case BASIC_SETTINGS_MAX_POWER + 18:
                return next(catta::json::Token::character('w'));
            case BASIC_SETTINGS_MAX_POWER + 19:
                return next(catta::json::Token::character('e'));
            case BASIC_SETTINGS_MAX_POWER + 20:
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
            case STORAGE_NOMINAL_CHARGE_POWER + 0:
                return next(catta::json::Token::character('S'));
            case STORAGE_NOMINAL_CHARGE_POWER + 1:
                return next(catta::json::Token::character('t'));
            case STORAGE_NOMINAL_CHARGE_POWER + 2:
                return next(catta::json::Token::character('o'));
            case STORAGE_NOMINAL_CHARGE_POWER + 3:
                return next(catta::json::Token::character('r'));
            case STORAGE_NOMINAL_CHARGE_POWER + 4:
                return next(catta::json::Token::character('a'));
            case STORAGE_NOMINAL_CHARGE_POWER + 5:
                return next(catta::json::Token::character('g'));
            case STORAGE_NOMINAL_CHARGE_POWER + 6:
                return next(catta::json::Token::character('e'));
            case STORAGE_NOMINAL_CHARGE_POWER + 7:
                return next(catta::json::Token::character('N'));
            case STORAGE_NOMINAL_CHARGE_POWER + 8:
                return next(catta::json::Token::character('o'));
            case STORAGE_NOMINAL_CHARGE_POWER + 9:
                return next(catta::json::Token::character('m'));
            case STORAGE_NOMINAL_CHARGE_POWER + 10:
                return next(catta::json::Token::character('i'));
            case STORAGE_NOMINAL_CHARGE_POWER + 11:
                return next(catta::json::Token::character('n'));
            case STORAGE_NOMINAL_CHARGE_POWER + 12:
                return next(catta::json::Token::character('a'));
            case STORAGE_NOMINAL_CHARGE_POWER + 13:
                return next(catta::json::Token::character('l'));
            case STORAGE_NOMINAL_CHARGE_POWER + 14:
                return next(catta::json::Token::character('C'));
            case STORAGE_NOMINAL_CHARGE_POWER + 15:
                return next(catta::json::Token::character('h'));
            case STORAGE_NOMINAL_CHARGE_POWER + 16:
                return next(catta::json::Token::character('a'));
            case STORAGE_NOMINAL_CHARGE_POWER + 17:
                return next(catta::json::Token::character('r'));
            case STORAGE_NOMINAL_CHARGE_POWER + 18:
                return next(catta::json::Token::character('g'));
            case STORAGE_NOMINAL_CHARGE_POWER + 19:
                return next(catta::json::Token::character('e'));
            case STORAGE_NOMINAL_CHARGE_POWER + 20:
                return next(catta::json::Token::character('P'));
            case STORAGE_NOMINAL_CHARGE_POWER + 21:
                return next(catta::json::Token::character('o'));
            case STORAGE_NOMINAL_CHARGE_POWER + 22:
                return next(catta::json::Token::character('w'));
            case STORAGE_NOMINAL_CHARGE_POWER + 23:
                return next(catta::json::Token::character('e'));
            case STORAGE_NOMINAL_CHARGE_POWER + 24:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case SI_CONTROL_MODUS + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MODUS + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MODUS + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MODUS + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MODUS + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MODUS + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MODUS + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MODUS + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MODUS + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MODUS + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MODUS + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MODUS + 11:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MODUS + 12:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_MODUS + 13:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case SI_CONTROL_VOLTAGE_DC_START_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 9:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 11:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 14:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 15:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 17:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 18:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 19:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 20:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 23:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 24:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 25:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_VOLTAGE_DC_START_READ + 26:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_BATTERY_BI_MODE_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 16:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 18:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 19:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 20:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 22:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 24:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_BI_MODE_READ + 25:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 16:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 18:
                return next(catta::json::Token::character('f'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 19:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 20:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 21:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 22:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 23:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 24:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 25:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 26:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 27:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_READ + 28:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_BATTERY_CV_MODE_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 16:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 17:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 18:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 19:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 20:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 22:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 24:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_CV_MODE_READ + 25:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DC_LOW_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DC_LOW_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_LOW_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DC_LOW_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DC_LOW_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_LOW_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_LOW_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DC_LOW_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DC_LOW_READ + 10:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DC_LOW_READ + 11:
                return next(catta::json::Token::character('L'));
            case SI_CONTROL_DC_LOW_READ + 12:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_READ + 13:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_DC_LOW_READ + 14:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DC_LOW_READ + 15:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DC_LOW_READ + 16:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DC_LOW_READ + 17:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DC_HIGH_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DC_HIGH_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_HIGH_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DC_HIGH_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_HIGH_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DC_HIGH_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_HIGH_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_HIGH_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_HIGH_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DC_HIGH_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DC_HIGH_READ + 10:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DC_HIGH_READ + 11:
                return next(catta::json::Token::character('H'));
            case SI_CONTROL_DC_HIGH_READ + 12:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_HIGH_READ + 13:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_DC_HIGH_READ + 14:
                return next(catta::json::Token::character('h'));
            case SI_CONTROL_DC_HIGH_READ + 15:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DC_HIGH_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DC_HIGH_READ + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DC_HIGH_READ + 18:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_TRACKING_SELECTION + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_TRACKING_SELECTION + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_TRACKING_SELECTION + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_TRACKING_SELECTION + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_TRACKING_SELECTION + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_TRACKING_SELECTION + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_TRACKING_SELECTION + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_TRACKING_SELECTION + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_TRACKING_SELECTION + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_TRACKING_SELECTION + 9:
                return next(catta::json::Token::character('T'));
            case SI_CONTROL_TRACKING_SELECTION + 10:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_TRACKING_SELECTION + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_TRACKING_SELECTION + 12:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_TRACKING_SELECTION + 13:
                return next(catta::json::Token::character('k'));
            case SI_CONTROL_TRACKING_SELECTION + 14:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_TRACKING_SELECTION + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_TRACKING_SELECTION + 16:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_TRACKING_SELECTION + 17:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_TRACKING_SELECTION + 18:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_TRACKING_SELECTION + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_TRACKING_SELECTION + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_TRACKING_SELECTION + 21:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_TRACKING_SELECTION + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_TRACKING_SELECTION + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_TRACKING_SELECTION + 24:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_TRACKING_SELECTION + 25:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case SI_CONTROL_START_COUNTDOWN + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_START_COUNTDOWN + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_START_COUNTDOWN + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_START_COUNTDOWN + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_START_COUNTDOWN + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_START_COUNTDOWN + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_START_COUNTDOWN + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_START_COUNTDOWN + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_START_COUNTDOWN + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_START_COUNTDOWN + 9:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_START_COUNTDOWN + 10:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_START_COUNTDOWN + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_START_COUNTDOWN + 12:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_START_COUNTDOWN + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_START_COUNTDOWN + 14:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_START_COUNTDOWN + 15:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_START_COUNTDOWN + 16:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_START_COUNTDOWN + 17:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_START_COUNTDOWN + 18:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_START_COUNTDOWN + 19:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_START_COUNTDOWN + 20:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_START_COUNTDOWN + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_START_COUNTDOWN + 22:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case SI_CONTROL_NIGHT_SHUTDOWN + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 9:
                return next(catta::json::Token::character('N'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 11:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 12:
                return next(catta::json::Token::character('h'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 14:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 15:
                return next(catta::json::Token::character('h'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 16:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 17:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 18:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 19:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 20:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_NIGHT_SHUTDOWN + 21:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case SI_CONTROL_PMAX + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_PMAX + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_PMAX + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_PMAX + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_PMAX + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_PMAX + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_PMAX + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_PMAX + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_PMAX + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_PMAX + 9:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_PMAX + 10:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_PMAX + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_PMAX + 12:
                return jump(catta::json::Token::character('x'), TAIL + 0);
            case SI_CONTROL_COSPHI + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_COSPHI + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_COSPHI + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_COSPHI + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_COSPHI + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_COSPHI + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_COSPHI + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_COSPHI + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_COSPHI + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_COSPHI + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_COSPHI + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_COSPHI + 11:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_COSPHI + 12:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_COSPHI + 13:
                return next(catta::json::Token::character('h'));
            case SI_CONTROL_COSPHI + 14:
                return jump(catta::json::Token::character('i'), TAIL + 0);
            case SI_CONTROL_UPTIME + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UPTIME + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UPTIME + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UPTIME + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UPTIME + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UPTIME + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UPTIME + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UPTIME + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UPTIME + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UPTIME + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UPTIME + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_UPTIME + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UPTIME + 12:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UPTIME + 13:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_UPTIME + 14:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_DAC0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_DAC0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_DAC0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_DAC0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_DAC0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_DAC0 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_DAC0 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC0 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC0 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC0 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC0 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_DAC0 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC0 + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_STEP_DAC0 + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_STEP_DAC0 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_DAC0 + 19:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_DAC1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_DAC1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_DAC1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_DAC1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_DAC1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_DAC1 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_DAC1 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC1 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC1 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC1 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC1 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_DAC1 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC1 + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_STEP_DAC1 + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_STEP_DAC1 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_DAC1 + 19:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_DAC2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_DAC2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_DAC2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_DAC2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_DAC2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_DAC2 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_DAC2 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC2 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC2 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC2 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC2 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_DAC2 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC2 + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_STEP_DAC2 + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_STEP_DAC2 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_DAC2 + 19:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_DAC3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_DAC3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_DAC3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_DAC3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_DAC3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_DAC3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_DAC3 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_DAC3 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC3 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC3 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_DAC3 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_DAC3 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_DAC3 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_DAC3 + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_STEP_DAC3 + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_STEP_DAC3 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_DAC3 + 19:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_UDC0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_UDC0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_UDC0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_UDC0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_UDC0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_UDC0 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_UDC0 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC0 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC0 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC0 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC0 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_UDC0 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC0 + 16:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_STEP_UDC0 + 17:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_STEP_UDC0 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_UDC0 + 19:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_UDC1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_UDC1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_UDC1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_UDC1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_UDC1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_UDC1 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_UDC1 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC1 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC1 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC1 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC1 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_UDC1 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC1 + 16:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_STEP_UDC1 + 17:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_STEP_UDC1 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_UDC1 + 19:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_UDC2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_UDC2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_UDC2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_UDC2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_UDC2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_UDC2 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_UDC2 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC2 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC2 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC2 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC2 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_UDC2 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC2 + 16:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_STEP_UDC2 + 17:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_STEP_UDC2 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_UDC2 + 19:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_MPP_STEP_UDC3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_STEP_UDC3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_STEP_UDC3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_STEP_UDC3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_STEP_UDC3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_STEP_UDC3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_STEP_UDC3 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_STEP_UDC3 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC3 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC3 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_STEP_UDC3 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_STEP_UDC3 + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_STEP_UDC3 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_STEP_UDC3 + 16:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_STEP_UDC3 + 17:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_STEP_UDC3 + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_STEP_UDC3 + 19:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 18:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 19:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_DAC0 + 21:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 18:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 19:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_DAC1 + 21:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 18:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 19:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_DAC2 + 21:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 18:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 19:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_DAC3 + 21:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 18:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 19:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_UDC0 + 21:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 18:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 19:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_UDC1 + 21:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 18:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 19:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_UDC2 + 21:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 9:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 10:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 11:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 12:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 14:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 15:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 16:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 18:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 19:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 20:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_MPP_SAMPLE_UDC3 + 21:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_REDUCTION + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_REDUCTION + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_REDUCTION + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_REDUCTION + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_REDUCTION + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_REDUCTION + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_REDUCTION + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_REDUCTION + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_REDUCTION + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_REDUCTION + 9:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_REDUCTION + 10:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_REDUCTION + 11:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_REDUCTION + 12:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_REDUCTION + 13:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_REDUCTION + 14:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_REDUCTION + 15:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_REDUCTION + 16:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_REDUCTION + 17:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case SI_CONTROL_SINEDUTY + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SINEDUTY + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SINEDUTY + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_SINEDUTY + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SINEDUTY + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_SINEDUTY + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SINEDUTY + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SINEDUTY + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SINEDUTY + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SINEDUTY + 9:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SINEDUTY + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SINEDUTY + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_SINEDUTY + 12:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SINEDUTY + 13:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_SINEDUTY + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_SINEDUTY + 15:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SINEDUTY + 16:
                return jump(catta::json::Token::character('y'), TAIL + 0);
            case SI_CONTROL_FILTER_WIND_CURVE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_FILTER_WIND_CURVE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FILTER_WIND_CURVE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_FILTER_WIND_CURVE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FILTER_WIND_CURVE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FILTER_WIND_CURVE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FILTER_WIND_CURVE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FILTER_WIND_CURVE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FILTER_WIND_CURVE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_FILTER_WIND_CURVE + 9:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_FILTER_WIND_CURVE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FILTER_WIND_CURVE + 11:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_FILTER_WIND_CURVE + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FILTER_WIND_CURVE + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_FILTER_WIND_CURVE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FILTER_WIND_CURVE + 15:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_FILTER_WIND_CURVE + 16:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FILTER_WIND_CURVE + 17:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FILTER_WIND_CURVE + 18:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_FILTER_WIND_CURVE + 19:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_FILTER_WIND_CURVE + 20:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_FILTER_WIND_CURVE + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FILTER_WIND_CURVE + 22:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_FILTER_WIND_CURVE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X00 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X00 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X00 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X00 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X00 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X00 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X00 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X00 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X00 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X00 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X00 + 20:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X01 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X01 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X01 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X01 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X01 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X01 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X01 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X01 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X01 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X01 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X01 + 20:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X02 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X02 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X02 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X02 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X02 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X02 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X02 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X02 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X02 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X02 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X02 + 20:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X03 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X03 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X03 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X03 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X03 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X03 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X03 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X03 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X03 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X03 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X03 + 20:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X04 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X04 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X04 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X04 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X04 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X04 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X04 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X04 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X04 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X04 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X04 + 20:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X05 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X05 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X05 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X05 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X05 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X05 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X05 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X05 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X05 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X05 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X05 + 20:
                return jump(catta::json::Token::character('5'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X06 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X06 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X06 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X06 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X06 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X06 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X06 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X06 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X06 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X06 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X06 + 20:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X07 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X07 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X07 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X07 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X07 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X07 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X07 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X07 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X07 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X07 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X07 + 20:
                return jump(catta::json::Token::character('7'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X08 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X08 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X08 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X08 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X08 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X08 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X08 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X08 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X08 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X08 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X08 + 20:
                return jump(catta::json::Token::character('8'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X09 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X09 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X09 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X09 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X09 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X09 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X09 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X09 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X09 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X09 + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X09 + 20:
                return jump(catta::json::Token::character('9'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X10 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X10 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X10 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X10 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X10 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X10 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X10 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X10 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X10 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X10 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X10 + 20:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X11 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X11 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X11 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X11 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X11 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X11 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X11 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X11 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X11 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X11 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X11 + 20:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X12 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X12 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X12 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X12 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X12 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X12 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X12 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X12 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X12 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X12 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X12 + 20:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X13 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X13 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X13 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X13 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X13 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X13 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X13 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X13 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X13 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X13 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X13 + 20:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X14 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X14 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X14 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X14 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X14 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X14 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X14 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X14 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X14 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X14 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X14 + 20:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X15 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X15 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X15 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X15 + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X15 + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15 + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X15 + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15 + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X15 + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15 + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X15 + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X15 + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X15 + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X15 + 20:
                return jump(catta::json::Token::character('5'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y00_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y00_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y01_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y01_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y02_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y02_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y03_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y03_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y04_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y04_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y05_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y05_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y06_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 20:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y06_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y07_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 20:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y07_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y08_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 20:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y08_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y09_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 20:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y09_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y10_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y10_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y11_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y11_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y12_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y12_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y13_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y13_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y14_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y14_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y15_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 21:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_Y15_READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 9:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 11:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 12:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 13:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 14:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 15:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 17:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 18:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 19:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 20:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 21:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 22:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 23:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 25:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 26:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 27:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 28:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 29:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 30:
                return jump(catta::json::Token::character('p'), TAIL + 0);
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 9:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 11:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 12:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 13:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 14:
                return next(catta::json::Token::character('L'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 15:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 16:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 18:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 19:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 20:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 21:
                return next(catta::json::Token::character('f'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 23:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 24:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 25:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 26:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 27:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 9:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 11:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 13:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 14:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 15:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 16:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 17:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 18:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 19:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 20:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 23:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 24:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 25:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 26:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_VOLTAGE_DC_START_WRITE + 27:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 16:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 18:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 19:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 20:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 22:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 23:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 24:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 25:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_BI_MODE_WRITE + 26:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 16:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 17:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 18:
                return next(catta::json::Token::character('f'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 19:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 20:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 21:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 22:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 23:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 24:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 25:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 26:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 27:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 28:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 29:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 9:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 11:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 12:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 13:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 15:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 16:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 17:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 18:
                return next(catta::json::Token::character('M'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 19:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 20:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 22:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 23:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 24:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 25:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_BATTERY_CV_MODE_WRITE + 26:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DC_LOW_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DC_LOW_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_LOW_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DC_LOW_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DC_LOW_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_LOW_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_LOW_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DC_LOW_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DC_LOW_WRITE + 10:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DC_LOW_WRITE + 11:
                return next(catta::json::Token::character('L'));
            case SI_CONTROL_DC_LOW_WRITE + 12:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_LOW_WRITE + 13:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_DC_LOW_WRITE + 14:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DC_LOW_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_LOW_WRITE + 16:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_LOW_WRITE + 17:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_LOW_WRITE + 18:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DC_HIGH_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DC_HIGH_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_HIGH_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DC_HIGH_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_HIGH_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DC_HIGH_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_HIGH_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_HIGH_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DC_HIGH_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DC_HIGH_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DC_HIGH_WRITE + 10:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DC_HIGH_WRITE + 11:
                return next(catta::json::Token::character('H'));
            case SI_CONTROL_DC_HIGH_WRITE + 12:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_HIGH_WRITE + 13:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_DC_HIGH_WRITE + 14:
                return next(catta::json::Token::character('h'));
            case SI_CONTROL_DC_HIGH_WRITE + 15:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DC_HIGH_WRITE + 16:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DC_HIGH_WRITE + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DC_HIGH_WRITE + 18:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DC_HIGH_WRITE + 19:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y00_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y01_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y02_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y03_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y04_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y05_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 20:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y06_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 20:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y07_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 20:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y08_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 20:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y09_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y10_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y11_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y12_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y13_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y14_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 18:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 21:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_Y15_WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 25:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 26:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 27:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 28:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 29:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 30:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 25:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 26:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 27:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 28:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 29:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 30:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 25:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 26:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 27:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 28:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 29:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 30:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y0_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 18:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y0_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y1_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 18:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y1_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y2_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 18:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y2_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y3_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 18:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y3_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y4_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 18:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y4_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y5_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 18:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y5_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y6_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 18:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y6_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y7_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 18:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y7_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y8_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 18:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y8_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y9_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 18:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 19:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y9_READ + 22:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 24:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X0 + 25:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 24:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X1 + 25:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 24:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_CONSTANT_VOLTAGE_X2 + 25:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 25:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 26:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 27:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 28:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 29:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 25:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 26:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 27:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 28:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 29:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 9:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 12:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 14:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 15:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 17:
                return next(catta::json::Token::character('V'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 18:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 19:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 21:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 22:
                return next(catta::json::Token::character('g'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 24:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 25:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 26:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 27:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 28:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 29:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X0 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X0 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X0 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X0 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X0 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X0 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X0 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X0 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X0 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X0 + 18:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X1 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X1 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X1 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X1 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X1 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X1 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X1 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X1 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X1 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X1 + 18:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X2 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X2 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X2 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X2 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X2 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X2 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X2 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X2 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X2 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X2 + 18:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X3 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X3 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X3 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X3 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X3 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X3 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X3 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X3 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X3 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X3 + 18:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X4 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X4 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X4 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X4 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X4 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X4 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X4 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X4 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X4 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X4 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X4 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X4 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X4 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X4 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X4 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X4 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X4 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X4 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X4 + 18:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X5 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X5 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X5 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X5 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X5 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X5 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X5 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X5 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X5 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X5 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X5 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X5 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X5 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X5 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X5 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X5 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X5 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X5 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X5 + 18:
                return jump(catta::json::Token::character('5'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X6 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X6 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X6 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X6 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X6 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X6 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X6 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X6 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X6 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X6 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X6 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X6 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X6 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X6 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X6 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X6 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X6 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X6 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X6 + 18:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X7 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X7 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X7 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X7 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X7 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X7 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X7 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X7 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X7 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X7 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X7 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X7 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X7 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X7 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X7 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X7 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X7 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X7 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X7 + 18:
                return jump(catta::json::Token::character('7'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X8 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X8 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X8 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X8 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X8 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X8 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X8 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X8 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X8 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X8 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X8 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X8 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X8 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X8 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X8 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X8 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X8 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X8 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X8 + 18:
                return jump(catta::json::Token::character('8'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_X9 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_X9 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_X9 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X9 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X9 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_X9 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_X9 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X9 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_X9 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_X9 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_X9 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_X9 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_X9 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_X9 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_X9 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_X9 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_X9 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_X9 + 17:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_DAC_CURVE_X9 + 18:
                return jump(catta::json::Token::character('9'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 18:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y0_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 18:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y1_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 18:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y2_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 18:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y3_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 18:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y4_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 18:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y5_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 18:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y6_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 18:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y7_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 18:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y8_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 18:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 19:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 20:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 21:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 22:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y9_WRITE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
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
    static constexpr std::uint16_t BASIC_SETTINGS_MAX_POWER = NAMEPLATE_DER_TYPE + 16;
    static constexpr std::uint16_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = BASIC_SETTINGS_MAX_POWER + 21;
    static constexpr std::uint16_t EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE = EXTENDED_MESUREMENTS_AC_WATT_HOURS + 30;
    static constexpr std::uint16_t STORAGE_NOMINAL_CHARGE_POWER = EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE + 35;
    static constexpr std::uint16_t SI_CONTROL_MODUS = STORAGE_NOMINAL_CHARGE_POWER + 25;
    static constexpr std::uint16_t SI_CONTROL_VOLTAGE_DC_START_READ = SI_CONTROL_MODUS + 14;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_BI_MODE_READ = SI_CONTROL_VOLTAGE_DC_START_READ + 27;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_SAFTY_MODE_READ = SI_CONTROL_BATTERY_BI_MODE_READ + 26;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_CV_MODE_READ = SI_CONTROL_BATTERY_SAFTY_MODE_READ + 29;
    static constexpr std::uint16_t SI_CONTROL_DC_LOW_READ = SI_CONTROL_BATTERY_CV_MODE_READ + 26;
    static constexpr std::uint16_t SI_CONTROL_DC_HIGH_READ = SI_CONTROL_DC_LOW_READ + 18;
    static constexpr std::uint16_t SI_CONTROL_TRACKING_SELECTION = SI_CONTROL_DC_HIGH_READ + 19;
    static constexpr std::uint16_t SI_CONTROL_START_COUNTDOWN = SI_CONTROL_TRACKING_SELECTION + 26;
    static constexpr std::uint16_t SI_CONTROL_NIGHT_SHUTDOWN = SI_CONTROL_START_COUNTDOWN + 23;
    static constexpr std::uint16_t SI_CONTROL_PMAX = SI_CONTROL_NIGHT_SHUTDOWN + 22;
    static constexpr std::uint16_t SI_CONTROL_COSPHI = SI_CONTROL_PMAX + 13;
    static constexpr std::uint16_t SI_CONTROL_UPTIME = SI_CONTROL_COSPHI + 15;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_DAC0 = SI_CONTROL_UPTIME + 15;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_DAC1 = SI_CONTROL_MPP_STEP_DAC0 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_DAC2 = SI_CONTROL_MPP_STEP_DAC1 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_DAC3 = SI_CONTROL_MPP_STEP_DAC2 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_UDC0 = SI_CONTROL_MPP_STEP_DAC3 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_UDC1 = SI_CONTROL_MPP_STEP_UDC0 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_UDC2 = SI_CONTROL_MPP_STEP_UDC1 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_STEP_UDC3 = SI_CONTROL_MPP_STEP_UDC2 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_DAC0 = SI_CONTROL_MPP_STEP_UDC3 + 20;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_DAC1 = SI_CONTROL_MPP_SAMPLE_DAC0 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_DAC2 = SI_CONTROL_MPP_SAMPLE_DAC1 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_DAC3 = SI_CONTROL_MPP_SAMPLE_DAC2 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_UDC0 = SI_CONTROL_MPP_SAMPLE_DAC3 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_UDC1 = SI_CONTROL_MPP_SAMPLE_UDC0 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_UDC2 = SI_CONTROL_MPP_SAMPLE_UDC1 + 22;
    static constexpr std::uint16_t SI_CONTROL_MPP_SAMPLE_UDC3 = SI_CONTROL_MPP_SAMPLE_UDC2 + 22;
    static constexpr std::uint16_t SI_CONTROL_REDUCTION = SI_CONTROL_MPP_SAMPLE_UDC3 + 22;
    static constexpr std::uint16_t SI_CONTROL_SINEDUTY = SI_CONTROL_REDUCTION + 18;
    static constexpr std::uint16_t SI_CONTROL_FILTER_WIND_CURVE = SI_CONTROL_SINEDUTY + 17;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X00 = SI_CONTROL_FILTER_WIND_CURVE + 24;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X01 = SI_CONTROL_WIND_CURVE_X00 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X02 = SI_CONTROL_WIND_CURVE_X01 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X03 = SI_CONTROL_WIND_CURVE_X02 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X04 = SI_CONTROL_WIND_CURVE_X03 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X05 = SI_CONTROL_WIND_CURVE_X04 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X06 = SI_CONTROL_WIND_CURVE_X05 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X07 = SI_CONTROL_WIND_CURVE_X06 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X08 = SI_CONTROL_WIND_CURVE_X07 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X09 = SI_CONTROL_WIND_CURVE_X08 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X10 = SI_CONTROL_WIND_CURVE_X09 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X11 = SI_CONTROL_WIND_CURVE_X10 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X12 = SI_CONTROL_WIND_CURVE_X11 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X13 = SI_CONTROL_WIND_CURVE_X12 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X14 = SI_CONTROL_WIND_CURVE_X13 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X15 = SI_CONTROL_WIND_CURVE_X14 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y00_READ = SI_CONTROL_WIND_CURVE_X15 + 21;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y01_READ = SI_CONTROL_WIND_CURVE_Y00_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y02_READ = SI_CONTROL_WIND_CURVE_Y01_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y03_READ = SI_CONTROL_WIND_CURVE_Y02_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y04_READ = SI_CONTROL_WIND_CURVE_Y03_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y05_READ = SI_CONTROL_WIND_CURVE_Y04_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y06_READ = SI_CONTROL_WIND_CURVE_Y05_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y07_READ = SI_CONTROL_WIND_CURVE_Y06_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y08_READ = SI_CONTROL_WIND_CURVE_Y07_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y09_READ = SI_CONTROL_WIND_CURVE_Y08_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y10_READ = SI_CONTROL_WIND_CURVE_Y09_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y11_READ = SI_CONTROL_WIND_CURVE_Y10_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y12_READ = SI_CONTROL_WIND_CURVE_Y11_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y13_READ = SI_CONTROL_WIND_CURVE_Y12_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y14_READ = SI_CONTROL_WIND_CURVE_Y13_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y15_READ = SI_CONTROL_WIND_CURVE_Y14_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_SOLAR_BATTARY_FILTER_STEP = SI_CONTROL_WIND_CURVE_Y15_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_POWER_LIMIT_SAFTY_MODE = SI_CONTROL_SOLAR_BATTARY_FILTER_STEP + 31;
    static constexpr std::uint16_t SI_CONTROL_VOLTAGE_DC_START_WRITE = SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 28;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_BI_MODE_WRITE = SI_CONTROL_VOLTAGE_DC_START_WRITE + 28;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_SAFTY_MODE_WRITE = SI_CONTROL_BATTERY_BI_MODE_WRITE + 27;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_CV_MODE_WRITE = SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 30;
    static constexpr std::uint16_t SI_CONTROL_DC_LOW_WRITE = SI_CONTROL_BATTERY_CV_MODE_WRITE + 27;
    static constexpr std::uint16_t SI_CONTROL_DC_HIGH_WRITE = SI_CONTROL_DC_LOW_WRITE + 19;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y00_WRITE = SI_CONTROL_DC_HIGH_WRITE + 20;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y01_WRITE = SI_CONTROL_WIND_CURVE_Y00_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y02_WRITE = SI_CONTROL_WIND_CURVE_Y01_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y03_WRITE = SI_CONTROL_WIND_CURVE_Y02_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y04_WRITE = SI_CONTROL_WIND_CURVE_Y03_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y05_WRITE = SI_CONTROL_WIND_CURVE_Y04_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y06_WRITE = SI_CONTROL_WIND_CURVE_Y05_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y07_WRITE = SI_CONTROL_WIND_CURVE_Y06_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y08_WRITE = SI_CONTROL_WIND_CURVE_Y07_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y09_WRITE = SI_CONTROL_WIND_CURVE_Y08_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y10_WRITE = SI_CONTROL_WIND_CURVE_Y09_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y11_WRITE = SI_CONTROL_WIND_CURVE_Y10_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y12_WRITE = SI_CONTROL_WIND_CURVE_Y11_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y13_WRITE = SI_CONTROL_WIND_CURVE_Y12_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y14_WRITE = SI_CONTROL_WIND_CURVE_Y13_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y15_WRITE = SI_CONTROL_WIND_CURVE_Y14_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE = SI_CONTROL_WIND_CURVE_Y15_WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE = SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 31;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE = SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 31;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y0_READ = SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 31;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y1_READ = SI_CONTROL_DAC_CURVE_Y0_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y2_READ = SI_CONTROL_DAC_CURVE_Y1_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y3_READ = SI_CONTROL_DAC_CURVE_Y2_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y4_READ = SI_CONTROL_DAC_CURVE_Y3_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y5_READ = SI_CONTROL_DAC_CURVE_Y4_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y6_READ = SI_CONTROL_DAC_CURVE_Y5_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y7_READ = SI_CONTROL_DAC_CURVE_Y6_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y8_READ = SI_CONTROL_DAC_CURVE_Y7_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y9_READ = SI_CONTROL_DAC_CURVE_Y8_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_X0 = SI_CONTROL_DAC_CURVE_Y9_READ + 23;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_X1 = SI_CONTROL_CONSTANT_VOLTAGE_X0 + 26;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_X2 = SI_CONTROL_CONSTANT_VOLTAGE_X1 + 26;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ = SI_CONTROL_CONSTANT_VOLTAGE_X2 + 26;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ = SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 30;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ = SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 30;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X0 = SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 30;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X1 = SI_CONTROL_DAC_CURVE_X0 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X2 = SI_CONTROL_DAC_CURVE_X1 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X3 = SI_CONTROL_DAC_CURVE_X2 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X4 = SI_CONTROL_DAC_CURVE_X3 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X5 = SI_CONTROL_DAC_CURVE_X4 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X6 = SI_CONTROL_DAC_CURVE_X5 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X7 = SI_CONTROL_DAC_CURVE_X6 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X8 = SI_CONTROL_DAC_CURVE_X7 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_X9 = SI_CONTROL_DAC_CURVE_X8 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y0_WRITE = SI_CONTROL_DAC_CURVE_X9 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y1_WRITE = SI_CONTROL_DAC_CURVE_Y0_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y2_WRITE = SI_CONTROL_DAC_CURVE_Y1_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y3_WRITE = SI_CONTROL_DAC_CURVE_Y2_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y4_WRITE = SI_CONTROL_DAC_CURVE_Y3_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y5_WRITE = SI_CONTROL_DAC_CURVE_Y4_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y6_WRITE = SI_CONTROL_DAC_CURVE_Y5_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y7_WRITE = SI_CONTROL_DAC_CURVE_Y6_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y8_WRITE = SI_CONTROL_DAC_CURVE_Y7_WRITE + 24;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y9_WRITE = SI_CONTROL_DAC_CURVE_Y8_WRITE + 24;
    static constexpr std::uint16_t TAIL = SI_CONTROL_DAC_CURVE_Y9_WRITE + 24;
    static constexpr std::uint16_t DONE = TAIL + 2;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
