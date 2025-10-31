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
                    _state = SI_CONTROL_UMIN_READ + 0;
                    break;
                case 45:
                    _state = SI_CONTROL_UMAX_READ + 0;
                    break;
                case 46:
                    _state = SI_CONTROL_VOLTAGE_DC_START_READ + 0;
                    break;
                case 47:
                    _state = SI_CONTROL_BATTERY_BI_MODE_READ + 0;
                    break;
                case 48:
                    _state = SI_CONTROL_BATTERY_SAFTY_MODE_READ + 0;
                    break;
                case 49:
                    _state = SI_CONTROL_BATTERY_CV_MODE_READ + 0;
                    break;
                case 50:
                    _state = SI_CONTROL_DC_LOW_READ + 0;
                    break;
                case 51:
                    _state = SI_CONTROL_DC_HIGH_READ + 0;
                    break;
                case 52:
                    _state = SI_CONTROL_TRACKING_SELECTION + 0;
                    break;
                case 53:
                    _state = SI_CONTROL_FUNCTION_ACTIVATE + 0;
                    break;
                case 54:
                    _state = SI_CONTROL_FUNCTION_WRITE_EEPROM + 0;
                    break;
                case 55:
                    _state = SI_CONTROL_FUNCTION_RESET + 0;
                    break;
                case 56:
                    _state = SI_CONTROL_START_COUNTDOWN + 0;
                    break;
                case 57:
                    _state = SI_CONTROL_NIGHT_SHUTDOWN + 0;
                    break;
                case 58:
                    _state = SI_CONTROL_PMAX + 0;
                    break;
                case 59:
                    _state = SI_CONTROL_COSPHI + 0;
                    break;
                case 60:
                    _state = SI_CONTROL_UPTIME + 0;
                    break;
                case 61:
                    _state = SI_CONTROL_MPP_STEP_DAC0 + 0;
                    break;
                case 62:
                    _state = SI_CONTROL_MPP_STEP_DAC1 + 0;
                    break;
                case 63:
                    _state = SI_CONTROL_MPP_STEP_DAC2 + 0;
                    break;
                case 64:
                    _state = SI_CONTROL_MPP_STEP_DAC3 + 0;
                    break;
                case 65:
                    _state = SI_CONTROL_MPP_STEP_UDC0 + 0;
                    break;
                case 66:
                    _state = SI_CONTROL_MPP_STEP_UDC1 + 0;
                    break;
                case 67:
                    _state = SI_CONTROL_MPP_STEP_UDC2 + 0;
                    break;
                case 68:
                    _state = SI_CONTROL_MPP_STEP_UDC3 + 0;
                    break;
                case 69:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC0 + 0;
                    break;
                case 70:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC1 + 0;
                    break;
                case 71:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC2 + 0;
                    break;
                case 72:
                    _state = SI_CONTROL_MPP_SAMPLE_DAC3 + 0;
                    break;
                case 73:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC0 + 0;
                    break;
                case 74:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC1 + 0;
                    break;
                case 75:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC2 + 0;
                    break;
                case 76:
                    _state = SI_CONTROL_MPP_SAMPLE_UDC3 + 0;
                    break;
                case 77:
                    _state = SI_CONTROL_REDUCTION + 0;
                    break;
                case 78:
                    _state = SI_CONTROL_SINEDUTY + 0;
                    break;
                case 79:
                    _state = SI_CONTROL_FILTER_WIND_CURVE + 0;
                    break;
                case 80:
                    _state = SI_CONTROL_WIND_CURVE_X00READ + 0;
                    break;
                case 81:
                    _state = SI_CONTROL_WIND_CURVE_X01READ + 0;
                    break;
                case 82:
                    _state = SI_CONTROL_WIND_CURVE_X02READ + 0;
                    break;
                case 83:
                    _state = SI_CONTROL_WIND_CURVE_X03READ + 0;
                    break;
                case 84:
                    _state = SI_CONTROL_WIND_CURVE_X04READ + 0;
                    break;
                case 85:
                    _state = SI_CONTROL_WIND_CURVE_X05READ + 0;
                    break;
                case 86:
                    _state = SI_CONTROL_WIND_CURVE_X06READ + 0;
                    break;
                case 87:
                    _state = SI_CONTROL_WIND_CURVE_X07READ + 0;
                    break;
                case 88:
                    _state = SI_CONTROL_WIND_CURVE_X08READ + 0;
                    break;
                case 89:
                    _state = SI_CONTROL_WIND_CURVE_X09READ + 0;
                    break;
                case 90:
                    _state = SI_CONTROL_WIND_CURVE_X10READ + 0;
                    break;
                case 91:
                    _state = SI_CONTROL_WIND_CURVE_X11READ + 0;
                    break;
                case 92:
                    _state = SI_CONTROL_WIND_CURVE_X12READ + 0;
                    break;
                case 93:
                    _state = SI_CONTROL_WIND_CURVE_X13READ + 0;
                    break;
                case 94:
                    _state = SI_CONTROL_WIND_CURVE_X14READ + 0;
                    break;
                case 95:
                    _state = SI_CONTROL_WIND_CURVE_X15READ + 0;
                    break;
                case 96:
                    _state = SI_CONTROL_WIND_CURVE_Y00_READ + 0;
                    break;
                case 97:
                    _state = SI_CONTROL_WIND_CURVE_Y01_READ + 0;
                    break;
                case 98:
                    _state = SI_CONTROL_WIND_CURVE_Y02_READ + 0;
                    break;
                case 99:
                    _state = SI_CONTROL_WIND_CURVE_Y03_READ + 0;
                    break;
                case 100:
                    _state = SI_CONTROL_WIND_CURVE_Y04_READ + 0;
                    break;
                case 101:
                    _state = SI_CONTROL_WIND_CURVE_Y05_READ + 0;
                    break;
                case 102:
                    _state = SI_CONTROL_WIND_CURVE_Y06_READ + 0;
                    break;
                case 103:
                    _state = SI_CONTROL_WIND_CURVE_Y07_READ + 0;
                    break;
                case 104:
                    _state = SI_CONTROL_WIND_CURVE_Y08_READ + 0;
                    break;
                case 105:
                    _state = SI_CONTROL_WIND_CURVE_Y09_READ + 0;
                    break;
                case 106:
                    _state = SI_CONTROL_WIND_CURVE_Y10_READ + 0;
                    break;
                case 107:
                    _state = SI_CONTROL_WIND_CURVE_Y11_READ + 0;
                    break;
                case 108:
                    _state = SI_CONTROL_WIND_CURVE_Y12_READ + 0;
                    break;
                case 109:
                    _state = SI_CONTROL_WIND_CURVE_Y13_READ + 0;
                    break;
                case 110:
                    _state = SI_CONTROL_WIND_CURVE_Y14_READ + 0;
                    break;
                case 111:
                    _state = SI_CONTROL_WIND_CURVE_Y15_READ + 0;
                    break;
                case 112:
                    _state = SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 0;
                    break;
                case 113:
                    _state = SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 0;
                    break;
                case 114:
                    _state = SI_CONTROL_UMIN_WRITE + 0;
                    break;
                case 115:
                    _state = SI_CONTROL_UMAX_WRITE + 0;
                    break;
                case 116:
                    _state = SI_CONTROL_VOLTAGE_DC_START_WRITE + 0;
                    break;
                case 117:
                    _state = SI_CONTROL_BATTERY_BI_MODE_WRITE + 0;
                    break;
                case 118:
                    _state = SI_CONTROL_BATTERY_SAFTY_MODE_WRITE + 0;
                    break;
                case 119:
                    _state = SI_CONTROL_BATTERY_CV_MODE_WRITE + 0;
                    break;
                case 120:
                    _state = SI_CONTROL_DC_LOW_WRITE + 0;
                    break;
                case 121:
                    _state = SI_CONTROL_DC_HIGH_WRITE + 0;
                    break;
                case 122:
                    _state = SI_CONTROL_WIND_CURVE_Y00_WRITE + 0;
                    break;
                case 123:
                    _state = SI_CONTROL_WIND_CURVE_Y01_WRITE + 0;
                    break;
                case 124:
                    _state = SI_CONTROL_WIND_CURVE_Y02_WRITE + 0;
                    break;
                case 125:
                    _state = SI_CONTROL_WIND_CURVE_Y03_WRITE + 0;
                    break;
                case 126:
                    _state = SI_CONTROL_WIND_CURVE_Y04_WRITE + 0;
                    break;
                case 127:
                    _state = SI_CONTROL_WIND_CURVE_Y05_WRITE + 0;
                    break;
                case 128:
                    _state = SI_CONTROL_WIND_CURVE_Y06_WRITE + 0;
                    break;
                case 129:
                    _state = SI_CONTROL_WIND_CURVE_Y07_WRITE + 0;
                    break;
                case 130:
                    _state = SI_CONTROL_WIND_CURVE_Y08_WRITE + 0;
                    break;
                case 131:
                    _state = SI_CONTROL_WIND_CURVE_Y09_WRITE + 0;
                    break;
                case 132:
                    _state = SI_CONTROL_WIND_CURVE_Y10_WRITE + 0;
                    break;
                case 133:
                    _state = SI_CONTROL_WIND_CURVE_Y11_WRITE + 0;
                    break;
                case 134:
                    _state = SI_CONTROL_WIND_CURVE_Y12_WRITE + 0;
                    break;
                case 135:
                    _state = SI_CONTROL_WIND_CURVE_Y13_WRITE + 0;
                    break;
                case 136:
                    _state = SI_CONTROL_WIND_CURVE_Y14_WRITE + 0;
                    break;
                case 137:
                    _state = SI_CONTROL_WIND_CURVE_Y15_WRITE + 0;
                    break;
                case 138:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y0_WRITE + 0;
                    break;
                case 139:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y1_WRITE + 0;
                    break;
                case 140:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 0;
                    break;
                case 141:
                    _state = SI_CONTROL_DAC_CURVE_Y0 + 0;
                    break;
                case 142:
                    _state = SI_CONTROL_DAC_CURVE_Y1 + 0;
                    break;
                case 143:
                    _state = SI_CONTROL_DAC_CURVE_Y2 + 0;
                    break;
                case 144:
                    _state = SI_CONTROL_DAC_CURVE_Y3 + 0;
                    break;
                case 145:
                    _state = SI_CONTROL_DAC_CURVE_Y4 + 0;
                    break;
                case 146:
                    _state = SI_CONTROL_DAC_CURVE_Y5 + 0;
                    break;
                case 147:
                    _state = SI_CONTROL_DAC_CURVE_Y6 + 0;
                    break;
                case 148:
                    _state = SI_CONTROL_DAC_CURVE_Y7 + 0;
                    break;
                case 149:
                    _state = SI_CONTROL_DAC_CURVE_Y8 + 0;
                    break;
                case 150:
                    _state = SI_CONTROL_DAC_CURVE_Y9 + 0;
                    break;
                case 151:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X0 + 0;
                    break;
                case 152:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X1 + 0;
                    break;
                case 153:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_X2 + 0;
                    break;
                case 154:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y0_READ + 0;
                    break;
                case 155:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y1_READ + 0;
                    break;
                case 156:
                    _state = SI_CONTROL_CONSTANT_VOLTAGE_Y2_READ + 0;
                    break;
                case 157:
                    _state = SI_CONTROL_DAC_CURVE_X0 + 0;
                    break;
                case 158:
                    _state = SI_CONTROL_DAC_CURVE_X1 + 0;
                    break;
                case 159:
                    _state = SI_CONTROL_DAC_CURVE_X2 + 0;
                    break;
                case 160:
                    _state = SI_CONTROL_DAC_CURVE_X3 + 0;
                    break;
                case 161:
                    _state = SI_CONTROL_DAC_CURVE_X4 + 0;
                    break;
                case 162:
                    _state = SI_CONTROL_DAC_CURVE_X5 + 0;
                    break;
                case 163:
                    _state = SI_CONTROL_DAC_CURVE_X6 + 0;
                    break;
                case 164:
                    _state = SI_CONTROL_DAC_CURVE_X7 + 0;
                    break;
                case 165:
                    _state = SI_CONTROL_DAC_CURVE_X8 + 0;
                    break;
                case 166:
                    _state = SI_CONTROL_DAC_CURVE_X9 + 0;
                    break;
                case 167:
                    _state = SI_CONTROL_WIND_CURVE_X00WRITE + 0;
                    break;
                case 168:
                    _state = SI_CONTROL_WIND_CURVE_X01WRITE + 0;
                    break;
                case 169:
                    _state = SI_CONTROL_WIND_CURVE_X02WRITE + 0;
                    break;
                case 170:
                    _state = SI_CONTROL_WIND_CURVE_X03WRITE + 0;
                    break;
                case 171:
                    _state = SI_CONTROL_WIND_CURVE_X04WRITE + 0;
                    break;
                case 172:
                    _state = SI_CONTROL_WIND_CURVE_X05WRITE + 0;
                    break;
                case 173:
                    _state = SI_CONTROL_WIND_CURVE_X06WRITE + 0;
                    break;
                case 174:
                    _state = SI_CONTROL_WIND_CURVE_X07WRITE + 0;
                    break;
                case 175:
                    _state = SI_CONTROL_WIND_CURVE_X08WRITE + 0;
                    break;
                case 176:
                    _state = SI_CONTROL_WIND_CURVE_X09WRITE + 0;
                    break;
                case 177:
                    _state = SI_CONTROL_WIND_CURVE_X10WRITE + 0;
                    break;
                case 178:
                    _state = SI_CONTROL_WIND_CURVE_X11WRITE + 0;
                    break;
                case 179:
                    _state = SI_CONTROL_WIND_CURVE_X12WRITE + 0;
                    break;
                case 180:
                    _state = SI_CONTROL_WIND_CURVE_X13WRITE + 0;
                    break;
                case 181:
                    _state = SI_CONTROL_WIND_CURVE_X14WRITE + 0;
                    break;
                case 182:
                    _state = SI_CONTROL_WIND_CURVE_X15WRITE + 0;
                    break;
                case 183:
                    _state = SI_CONTROL_ENABLE_WRITE_ONCE + 0;
                    break;
                default:
                    _state = SI_CONTROL_ENABLE_WRITE_PERMANT + 0;
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
            case SI_CONTROL_UMIN_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UMIN_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMIN_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UMIN_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMIN_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMIN_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMIN_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMIN_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMIN_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UMIN_READ + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UMIN_READ + 10:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_UMIN_READ + 11:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMIN_READ + 12:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMIN_READ + 13:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_UMIN_READ + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_UMIN_READ + 15:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_UMIN_READ + 16:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_UMAX_READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UMAX_READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMAX_READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UMAX_READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMAX_READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMAX_READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMAX_READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMAX_READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMAX_READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UMAX_READ + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UMAX_READ + 10:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_UMAX_READ + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_UMAX_READ + 12:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_UMAX_READ + 13:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_UMAX_READ + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_UMAX_READ + 15:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_UMAX_READ + 16:
                return jump(catta::json::Token::character('d'), TAIL + 0);
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
            case SI_CONTROL_FUNCTION_ACTIVATE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 9:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 10:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 12:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 14:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 15:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 16:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 17:
                return next(catta::json::Token::character('A'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 18:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 19:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 20:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 21:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 22:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 23:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_ACTIVATE + 24:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 9:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 10:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 12:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 14:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 15:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 16:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 17:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 18:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 19:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 20:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 22:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 23:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 24:
                return next(catta::json::Token::character('p'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 25:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 26:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_WRITE_EEPROM + 27:
                return jump(catta::json::Token::character('m'), TAIL + 0);
            case SI_CONTROL_FUNCTION_RESET + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_FUNCTION_RESET + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_RESET + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_FUNCTION_RESET + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_RESET + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_RESET + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_RESET + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_FUNCTION_RESET + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_RESET + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_FUNCTION_RESET + 9:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_FUNCTION_RESET + 10:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_FUNCTION_RESET + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_RESET + 12:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_FUNCTION_RESET + 13:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_FUNCTION_RESET + 14:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_FUNCTION_RESET + 15:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_FUNCTION_RESET + 16:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_FUNCTION_RESET + 17:
                return next(catta::json::Token::character('R'));
            case SI_CONTROL_FUNCTION_RESET + 18:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_FUNCTION_RESET + 19:
                return next(catta::json::Token::character('s'));
            case SI_CONTROL_FUNCTION_RESET + 20:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_FUNCTION_RESET + 21:
                return jump(catta::json::Token::character('t'), TAIL + 0);
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
            case SI_CONTROL_WIND_CURVE_X00READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X00READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X00READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X00READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X00READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X00READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X00READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X00READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X00READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X00READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X00READ + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X00READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X00READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X00READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X01READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X01READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X01READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X01READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X01READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X01READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X01READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X01READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X01READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X01READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X01READ + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X01READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X01READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X01READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X02READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X02READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X02READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X02READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X02READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X02READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X02READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X02READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X02READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X02READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X02READ + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_X02READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X02READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X02READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X03READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X03READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X03READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X03READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X03READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X03READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X03READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X03READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X03READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X03READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X03READ + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_X03READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X03READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X03READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X04READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X04READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X04READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X04READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X04READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X04READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X04READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X04READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X04READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X04READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X04READ + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_X04READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X04READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X04READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X05READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X05READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X05READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X05READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X05READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X05READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X05READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X05READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X05READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X05READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X05READ + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_X05READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X05READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X05READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X06READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X06READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X06READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X06READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X06READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X06READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X06READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X06READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X06READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X06READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X06READ + 20:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_WIND_CURVE_X06READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X06READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X06READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X07READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X07READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X07READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X07READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X07READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X07READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X07READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X07READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X07READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X07READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X07READ + 20:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_WIND_CURVE_X07READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X07READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X07READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X08READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X08READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X08READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X08READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X08READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X08READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X08READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X08READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X08READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X08READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X08READ + 20:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_WIND_CURVE_X08READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X08READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X08READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X09READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X09READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X09READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X09READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X09READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X09READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X09READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X09READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X09READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X09READ + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X09READ + 20:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_WIND_CURVE_X09READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X09READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X09READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X10READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X10READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X10READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X10READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X10READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X10READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X10READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X10READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X10READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X10READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X10READ + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X10READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X10READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X10READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X11READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X11READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X11READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X11READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X11READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X11READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X11READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X11READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X11READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X11READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X11READ + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X11READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X11READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X11READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X12READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X12READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X12READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X12READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X12READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X12READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X12READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X12READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X12READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X12READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X12READ + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_X12READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X12READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X12READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X13READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X13READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X13READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X13READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X13READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X13READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X13READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X13READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X13READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X13READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X13READ + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_X13READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X13READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X13READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X14READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X14READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X14READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X14READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X14READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X14READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X14READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X14READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X14READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X14READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X14READ + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_X14READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X14READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X14READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X15READ + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X15READ + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15READ + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15READ + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15READ + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15READ + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X15READ + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15READ + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15READ + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X15READ + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X15READ + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15READ + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15READ + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X15READ + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15READ + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X15READ + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15READ + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X15READ + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X15READ + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X15READ + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X15READ + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_X15READ + 21:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15READ + 22:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X15READ + 23:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_WIND_CURVE_X15READ + 24:
                return jump(catta::json::Token::character('d'), TAIL + 0);
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
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 9:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 10:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 11:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 12:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 13:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 14:
                return next(catta::json::Token::character('B'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 15:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 17:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 18:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 19:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 20:
                return next(catta::json::Token::character('y'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 21:
                return next(catta::json::Token::character('F'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 22:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 23:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 25:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 26:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 27:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 28:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 29:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 30:
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
            case SI_CONTROL_UMIN_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UMIN_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMIN_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UMIN_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMIN_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMIN_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMIN_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMIN_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMIN_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UMIN_WRITE + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UMIN_WRITE + 10:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_UMIN_WRITE + 11:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMIN_WRITE + 12:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMIN_WRITE + 13:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_UMIN_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMIN_WRITE + 15:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMIN_WRITE + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMIN_WRITE + 17:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_UMAX_WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_UMAX_WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMAX_WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_UMAX_WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMAX_WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_UMAX_WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMAX_WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMAX_WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_UMAX_WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_UMAX_WRITE + 9:
                return next(catta::json::Token::character('U'));
            case SI_CONTROL_UMAX_WRITE + 10:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_UMAX_WRITE + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_UMAX_WRITE + 12:
                return next(catta::json::Token::character('x'));
            case SI_CONTROL_UMAX_WRITE + 13:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_UMAX_WRITE + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_UMAX_WRITE + 15:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_UMAX_WRITE + 16:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_UMAX_WRITE + 17:
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
            case SI_CONTROL_DAC_CURVE_Y0 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y0 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y0 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y0 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y0 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y0 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y0 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y0 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y0 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y0 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y0 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y0 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y0 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y0 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y0 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y0 + 18:
                return jump(catta::json::Token::character('0'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y1 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y1 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y1 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y1 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y1 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y1 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y1 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y1 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y1 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y1 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y1 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y1 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y1 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y1 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y1 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y1 + 18:
                return jump(catta::json::Token::character('1'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y2 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y2 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y2 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y2 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y2 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y2 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y2 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y2 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y2 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y2 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y2 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y2 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y2 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y2 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y2 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y2 + 18:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y3 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y3 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y3 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y3 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y3 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y3 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y3 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y3 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y3 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y3 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y3 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y3 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y3 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y3 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y3 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y3 + 18:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y4 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y4 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y4 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y4 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y4 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y4 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y4 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y4 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y4 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y4 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y4 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y4 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y4 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y4 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y4 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y4 + 18:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y5 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y5 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y5 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y5 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y5 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y5 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y5 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y5 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y5 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y5 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y5 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y5 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y5 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y5 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y5 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y5 + 18:
                return jump(catta::json::Token::character('5'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y6 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y6 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y6 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y6 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y6 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y6 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y6 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y6 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y6 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y6 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y6 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y6 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y6 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y6 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y6 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y6 + 18:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y7 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y7 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y7 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y7 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y7 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y7 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y7 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y7 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y7 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y7 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y7 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y7 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y7 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y7 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y7 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y7 + 18:
                return jump(catta::json::Token::character('7'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y8 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y8 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y8 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y8 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y8 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y8 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y8 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y8 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y8 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y8 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y8 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y8 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y8 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y8 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y8 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y8 + 18:
                return jump(catta::json::Token::character('8'), TAIL + 0);
            case SI_CONTROL_DAC_CURVE_Y9 + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_DAC_CURVE_Y9 + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_DAC_CURVE_Y9 + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9 + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9 + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_DAC_CURVE_Y9 + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_DAC_CURVE_Y9 + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9 + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_DAC_CURVE_Y9 + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_DAC_CURVE_Y9 + 9:
                return next(catta::json::Token::character('D'));
            case SI_CONTROL_DAC_CURVE_Y9 + 10:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_DAC_CURVE_Y9 + 11:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_DAC_CURVE_Y9 + 12:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_DAC_CURVE_Y9 + 13:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_DAC_CURVE_Y9 + 14:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_DAC_CURVE_Y9 + 15:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_DAC_CURVE_Y9 + 16:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_DAC_CURVE_Y9 + 17:
                return next(catta::json::Token::character('Y'));
            case SI_CONTROL_DAC_CURVE_Y9 + 18:
                return jump(catta::json::Token::character('9'), TAIL + 0);
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
            case SI_CONTROL_WIND_CURVE_X00WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X00WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X01WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X01WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X02WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X02WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X03WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X03WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X04WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X04WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X05WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X05WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X06WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 20:
                return next(catta::json::Token::character('6'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X06WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X07WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 20:
                return next(catta::json::Token::character('7'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X07WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X08WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 20:
                return next(catta::json::Token::character('8'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X08WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X09WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 19:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 20:
                return next(catta::json::Token::character('9'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X09WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X10WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 20:
                return next(catta::json::Token::character('0'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X10WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X11WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 20:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X11WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X12WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 20:
                return next(catta::json::Token::character('2'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X12WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X13WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 20:
                return next(catta::json::Token::character('3'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X13WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X14WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 20:
                return next(catta::json::Token::character('4'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X14WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_WIND_CURVE_X15WRITE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 9:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 10:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 11:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 12:
                return next(catta::json::Token::character('d'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 13:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 14:
                return next(catta::json::Token::character('u'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 15:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 16:
                return next(catta::json::Token::character('v'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 17:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 18:
                return next(catta::json::Token::character('X'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 19:
                return next(catta::json::Token::character('1'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 20:
                return next(catta::json::Token::character('5'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 21:
                return next(catta::json::Token::character('w'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 23:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 24:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_WIND_CURVE_X15WRITE + 25:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_ENABLE_WRITE_ONCE + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 9:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 10:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 12:
                return next(catta::json::Token::character('b'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 13:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 15:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 16:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 18:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 19:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 20:
                return next(catta::json::Token::character('O'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 21:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 22:
                return next(catta::json::Token::character('c'));
            case SI_CONTROL_ENABLE_WRITE_ONCE + 23:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 0:
                return next(catta::json::Token::character('S'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 1:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 2:
                return next(catta::json::Token::character('C'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 3:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 4:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 5:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 6:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 7:
                return next(catta::json::Token::character('o'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 8:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 9:
                return next(catta::json::Token::character('E'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 10:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 11:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 12:
                return next(catta::json::Token::character('b'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 13:
                return next(catta::json::Token::character('l'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 14:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 15:
                return next(catta::json::Token::character('W'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 16:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 17:
                return next(catta::json::Token::character('i'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 18:
                return next(catta::json::Token::character('t'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 19:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 20:
                return next(catta::json::Token::character('P'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 21:
                return next(catta::json::Token::character('e'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 22:
                return next(catta::json::Token::character('r'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 23:
                return next(catta::json::Token::character('m'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 24:
                return next(catta::json::Token::character('a'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 25:
                return next(catta::json::Token::character('n'));
            case SI_CONTROL_ENABLE_WRITE_PERMANT + 26:
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
    static constexpr std::uint16_t SI_CONTROL_UMIN_READ = SI_CONTROL_MODUS + 14;
    static constexpr std::uint16_t SI_CONTROL_UMAX_READ = SI_CONTROL_UMIN_READ + 17;
    static constexpr std::uint16_t SI_CONTROL_VOLTAGE_DC_START_READ = SI_CONTROL_UMAX_READ + 17;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_BI_MODE_READ = SI_CONTROL_VOLTAGE_DC_START_READ + 27;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_SAFTY_MODE_READ = SI_CONTROL_BATTERY_BI_MODE_READ + 26;
    static constexpr std::uint16_t SI_CONTROL_BATTERY_CV_MODE_READ = SI_CONTROL_BATTERY_SAFTY_MODE_READ + 29;
    static constexpr std::uint16_t SI_CONTROL_DC_LOW_READ = SI_CONTROL_BATTERY_CV_MODE_READ + 26;
    static constexpr std::uint16_t SI_CONTROL_DC_HIGH_READ = SI_CONTROL_DC_LOW_READ + 18;
    static constexpr std::uint16_t SI_CONTROL_TRACKING_SELECTION = SI_CONTROL_DC_HIGH_READ + 19;
    static constexpr std::uint16_t SI_CONTROL_FUNCTION_ACTIVATE = SI_CONTROL_TRACKING_SELECTION + 26;
    static constexpr std::uint16_t SI_CONTROL_FUNCTION_WRITE_EEPROM = SI_CONTROL_FUNCTION_ACTIVATE + 25;
    static constexpr std::uint16_t SI_CONTROL_FUNCTION_RESET = SI_CONTROL_FUNCTION_WRITE_EEPROM + 28;
    static constexpr std::uint16_t SI_CONTROL_START_COUNTDOWN = SI_CONTROL_FUNCTION_RESET + 22;
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
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X00READ = SI_CONTROL_FILTER_WIND_CURVE + 24;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X01READ = SI_CONTROL_WIND_CURVE_X00READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X02READ = SI_CONTROL_WIND_CURVE_X01READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X03READ = SI_CONTROL_WIND_CURVE_X02READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X04READ = SI_CONTROL_WIND_CURVE_X03READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X05READ = SI_CONTROL_WIND_CURVE_X04READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X06READ = SI_CONTROL_WIND_CURVE_X05READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X07READ = SI_CONTROL_WIND_CURVE_X06READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X08READ = SI_CONTROL_WIND_CURVE_X07READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X09READ = SI_CONTROL_WIND_CURVE_X08READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X10READ = SI_CONTROL_WIND_CURVE_X09READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X11READ = SI_CONTROL_WIND_CURVE_X10READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X12READ = SI_CONTROL_WIND_CURVE_X11READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X13READ = SI_CONTROL_WIND_CURVE_X12READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X14READ = SI_CONTROL_WIND_CURVE_X13READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X15READ = SI_CONTROL_WIND_CURVE_X14READ + 25;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_Y00_READ = SI_CONTROL_WIND_CURVE_X15READ + 25;
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
    static constexpr std::uint16_t SI_CONTROL_SOLAR_BATTERY_FILTER_STEP = SI_CONTROL_WIND_CURVE_Y15_READ + 25;
    static constexpr std::uint16_t SI_CONTROL_POWER_LIMIT_SAFTY_MODE = SI_CONTROL_SOLAR_BATTERY_FILTER_STEP + 31;
    static constexpr std::uint16_t SI_CONTROL_UMIN_WRITE = SI_CONTROL_POWER_LIMIT_SAFTY_MODE + 28;
    static constexpr std::uint16_t SI_CONTROL_UMAX_WRITE = SI_CONTROL_UMIN_WRITE + 18;
    static constexpr std::uint16_t SI_CONTROL_VOLTAGE_DC_START_WRITE = SI_CONTROL_UMAX_WRITE + 18;
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
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y0 = SI_CONTROL_CONSTANT_VOLTAGE_Y2_WRITE + 31;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y1 = SI_CONTROL_DAC_CURVE_Y0 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y2 = SI_CONTROL_DAC_CURVE_Y1 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y3 = SI_CONTROL_DAC_CURVE_Y2 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y4 = SI_CONTROL_DAC_CURVE_Y3 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y5 = SI_CONTROL_DAC_CURVE_Y4 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y6 = SI_CONTROL_DAC_CURVE_Y5 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y7 = SI_CONTROL_DAC_CURVE_Y6 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y8 = SI_CONTROL_DAC_CURVE_Y7 + 19;
    static constexpr std::uint16_t SI_CONTROL_DAC_CURVE_Y9 = SI_CONTROL_DAC_CURVE_Y8 + 19;
    static constexpr std::uint16_t SI_CONTROL_CONSTANT_VOLTAGE_X0 = SI_CONTROL_DAC_CURVE_Y9 + 19;
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
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X00WRITE = SI_CONTROL_DAC_CURVE_X9 + 19;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X01WRITE = SI_CONTROL_WIND_CURVE_X00WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X02WRITE = SI_CONTROL_WIND_CURVE_X01WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X03WRITE = SI_CONTROL_WIND_CURVE_X02WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X04WRITE = SI_CONTROL_WIND_CURVE_X03WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X05WRITE = SI_CONTROL_WIND_CURVE_X04WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X06WRITE = SI_CONTROL_WIND_CURVE_X05WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X07WRITE = SI_CONTROL_WIND_CURVE_X06WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X08WRITE = SI_CONTROL_WIND_CURVE_X07WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X09WRITE = SI_CONTROL_WIND_CURVE_X08WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X10WRITE = SI_CONTROL_WIND_CURVE_X09WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X11WRITE = SI_CONTROL_WIND_CURVE_X10WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X12WRITE = SI_CONTROL_WIND_CURVE_X11WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X13WRITE = SI_CONTROL_WIND_CURVE_X12WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X14WRITE = SI_CONTROL_WIND_CURVE_X13WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_WIND_CURVE_X15WRITE = SI_CONTROL_WIND_CURVE_X14WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_ENABLE_WRITE_ONCE = SI_CONTROL_WIND_CURVE_X15WRITE + 26;
    static constexpr std::uint16_t SI_CONTROL_ENABLE_WRITE_PERMANT = SI_CONTROL_ENABLE_WRITE_ONCE + 24;
    static constexpr std::uint16_t TAIL = SI_CONTROL_ENABLE_WRITE_PERMANT + 27;
    static constexpr std::uint16_t DONE = TAIL + 2;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
