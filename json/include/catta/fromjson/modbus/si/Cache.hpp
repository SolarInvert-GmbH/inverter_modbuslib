#pragma once

// si
#include <catta/modbus/si/Cache.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/Type.hpp>
#include <catta/fromjson/modbus/sunspec/ScaleFactor.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::Cache>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::Cache;
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
                return input == catta::json::Token::character('t')   ? jump(HUB + 174)
                       : input == catta::json::Token::character('i') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('n') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('v') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('e') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('r') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('t') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('e') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('r') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('W')   ? jump(HUB + 139)
                       : input == catta::json::Token::character('T') ? jump(HUB + 115)
                       : input == catta::json::Token::character('P') ? jump(HUB + 67)
                       : input == catta::json::Token::character('H') ? jump(HUB + 49)
                       : input == catta::json::Token::character('D') ? jump(HUB + 27)
                       : input == catta::json::Token::character('A') ? jump(HUB + 10)
                                                                     : error();
            case HUB + 10:
                return input == catta::json::Token::character('m') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('p') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('s') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('S') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('c') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('a') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('l') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('e') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('F') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('a') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('c') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('t') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('o') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('r') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::closeString() ? jump(HUB + 25) : error();
            case HUB + 25:
                return !_inverterAmpsScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 26:
                return handle(_inverterAmpsScaleFactorParser);
            case HUB + 27:
                return input == catta::json::Token::character('c') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::character('V') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('o') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('l') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('t') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('a') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('g') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('e') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('S') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('c') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('a') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('l') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('e') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('F') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('a') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('c') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('t') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('o') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('r') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::closeString() ? jump(HUB + 47) : error();
            case HUB + 47:
                return !_inverterDcVoltageScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 48:
                return handle(_inverterDcVoltageScaleFactorParser);
            case HUB + 49:
                return input == catta::json::Token::character('e') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('r') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('t') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::character('z') ? jump(HUB + 53) : error();
            case HUB + 53:
                return input == catta::json::Token::character('S') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::character('c') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('a') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('l') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('e') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('F') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('a') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('c') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('t') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('o') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('r') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::closeString() ? jump(HUB + 65) : error();
            case HUB + 65:
                return !_inverterHertzScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 66:
                return handle(_inverterHertzScaleFactorParser);
            case HUB + 67:
                return input == catta::json::Token::character('o')   ? jump(HUB + 92)
                       : input == catta::json::Token::character('h') ? jump(HUB + 68)
                                                                     : error();
            case HUB + 68:
                return input == catta::json::Token::character('a') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('s') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('e') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('V') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('o') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('l') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::character('t') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('a') ? jump(HUB + 76) : error();
            case HUB + 76:
                return input == catta::json::Token::character('g') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('e') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('S') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('c') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('a') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('l') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('e') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('F') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('a') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('c') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('t') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('o') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('r') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::closeString() ? jump(HUB + 90) : error();
            case HUB + 90:
                return !_inverterPhaseVoltageScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 91:
                return handle(_inverterPhaseVoltageScaleFactorParser);
            case HUB + 92:
                return input == catta::json::Token::character('w') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('e') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('r') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::character('F') ? jump(HUB + 96) : error();
            case HUB + 96:
                return input == catta::json::Token::character('a') ? jump(HUB + 97) : error();
            case HUB + 97:
                return input == catta::json::Token::character('c') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::character('t') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('o') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('r') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('S') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('c') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('a') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('l') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('e') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('F') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('a') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('c') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('t') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('o') ? jump(HUB + 111) : error();
            case HUB + 111:
                return input == catta::json::Token::character('r') ? jump(HUB + 112) : error();
            case HUB + 112:
                return input == catta::json::Token::closeString() ? jump(HUB + 113) : error();
            case HUB + 113:
                return !_inverterPowerFactorScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 114:
                return handle(_inverterPowerFactorScaleFactorParser);
            case HUB + 115:
                return input == catta::json::Token::character('e') ? jump(HUB + 116) : error();
            case HUB + 116:
                return input == catta::json::Token::character('m') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('p') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('e') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::character('r') ? jump(HUB + 120) : error();
            case HUB + 120:
                return input == catta::json::Token::character('a') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('t') ? jump(HUB + 122) : error();
            case HUB + 122:
                return input == catta::json::Token::character('u') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::character('r') ? jump(HUB + 124) : error();
            case HUB + 124:
                return input == catta::json::Token::character('e') ? jump(HUB + 125) : error();
            case HUB + 125:
                return input == catta::json::Token::character('S') ? jump(HUB + 126) : error();
            case HUB + 126:
                return input == catta::json::Token::character('c') ? jump(HUB + 127) : error();
            case HUB + 127:
                return input == catta::json::Token::character('a') ? jump(HUB + 128) : error();
            case HUB + 128:
                return input == catta::json::Token::character('l') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('e') ? jump(HUB + 130) : error();
            case HUB + 130:
                return input == catta::json::Token::character('F') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('a') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::character('c') ? jump(HUB + 133) : error();
            case HUB + 133:
                return input == catta::json::Token::character('t') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('o') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('r') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::closeString() ? jump(HUB + 137) : error();
            case HUB + 137:
                return !_inverterTemperatureScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 138:
                return handle(_inverterTemperatureScaleFactorParser);
            case HUB + 139:
                return input == catta::json::Token::character('a') ? jump(HUB + 140) : error();
            case HUB + 140:
                return input == catta::json::Token::character('t') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('t') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::character('S')   ? jump(HUB + 161)
                       : input == catta::json::Token::character('H') ? jump(HUB + 143)
                                                                     : error();
            case HUB + 143:
                return input == catta::json::Token::character('o') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('u') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::character('r') ? jump(HUB + 146) : error();
            case HUB + 146:
                return input == catta::json::Token::character('s') ? jump(HUB + 147) : error();
            case HUB + 147:
                return input == catta::json::Token::character('S') ? jump(HUB + 148) : error();
            case HUB + 148:
                return input == catta::json::Token::character('c') ? jump(HUB + 149) : error();
            case HUB + 149:
                return input == catta::json::Token::character('a') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('l') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('e') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('F') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::character('a') ? jump(HUB + 154) : error();
            case HUB + 154:
                return input == catta::json::Token::character('c') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('t') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::character('o') ? jump(HUB + 157) : error();
            case HUB + 157:
                return input == catta::json::Token::character('r') ? jump(HUB + 158) : error();
            case HUB + 158:
                return input == catta::json::Token::closeString() ? jump(HUB + 159) : error();
            case HUB + 159:
                return !_inverterWattHoursScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 160:
                return handle(_inverterWattHoursScaleFactorParser);
            case HUB + 161:
                return input == catta::json::Token::character('c') ? jump(HUB + 162) : error();
            case HUB + 162:
                return input == catta::json::Token::character('a') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('l') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('e') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('F') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('a') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('c') ? jump(HUB + 168) : error();
            case HUB + 168:
                return input == catta::json::Token::character('t') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::character('o') ? jump(HUB + 170) : error();
            case HUB + 170:
                return input == catta::json::Token::character('r') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::closeString() ? jump(HUB + 172) : error();
            case HUB + 172:
                return !_inverterWattScaleFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 173:
                return handle(_inverterWattScaleFactorParser);
            case HUB + 174:
                return input == catta::json::Token::character('y') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('p') ? jump(HUB + 176) : error();
            case HUB + 176:
                return input == catta::json::Token::character('e') ? jump(HUB + 177) : error();
            case HUB + 177:
                return input == catta::json::Token::closeString() ? jump(HUB + 178) : error();
            case HUB + 178:
                return !_typeParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 179:
                return handle(_typeParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE
                   ? Output::create(_typeParser.data(), _inverterAmpsScaleFactorParser.data(), _inverterPhaseVoltageScaleFactorParser.data(),
                                    _inverterWattScaleFactorParser.data(), _inverterHertzScaleFactorParser.data(),
                                    _inverterPowerFactorScaleFactorParser.data(), _inverterWattHoursScaleFactorParser.data(),
                                    _inverterDcVoltageScaleFactorParser.data(), _inverterTemperatureScaleFactorParser.data())
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
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterAmpsScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterDcVoltageScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterHertzScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterPhaseVoltageScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterPowerFactorScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterTemperatureScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterWattHoursScaleFactorParser;
    Parser<catta::modbus::sunspec::ScaleFactor> _inverterWattScaleFactorParser;
    Parser<catta::modbus::si::Type> _typeParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 180;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
