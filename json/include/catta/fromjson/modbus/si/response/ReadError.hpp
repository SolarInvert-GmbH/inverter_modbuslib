#pragma once

// response
#include <catta/modbus/si/response/ReadError.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::ReadError>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::ReadError;
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
                return input == catta::json::Token::character('u')   ? jump(HUB + 205)
                       : input == catta::json::Token::character('o') ? jump(HUB + 126)
                       : input == catta::json::Token::character('l') ? jump(HUB + 98)
                       : input == catta::json::Token::character('i') ? jump(HUB + 86)
                       : input == catta::json::Token::character('e') ? jump(HUB + 54)
                       : input == catta::json::Token::character('d') ? jump(HUB + 31)
                       : input == catta::json::Token::character('c') ? jump(HUB + 26)
                       : input == catta::json::Token::character('a') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('v') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('e') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('r') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('a') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('g') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('e') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('G') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('r') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('i') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('d') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('O') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('v') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('e') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('r') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('V') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('o') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('l') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('t') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('a') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('g') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('e') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::closeString() ? jump(HUB + 24) : error();
            case HUB + 24:
                return !_averageGridOverVoltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 25:
                return handle(_averageGridOverVoltageParser);
            case HUB + 26:
                return input == catta::json::Token::character('o') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('m') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::closeString() ? jump(HUB + 29) : error();
            case HUB + 29:
                return !_comParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 30:
                return handle(_comParser);
            case HUB + 31:
                return input == catta::json::Token::character('i') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('f') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('f') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('e') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('r') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('e') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('n') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('c') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('e') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('G') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('r') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('i') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('d') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('V') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('o') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('l') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('t') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('a') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('g') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('e') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::closeString() ? jump(HUB + 52) : error();
            case HUB + 52:
                return !_differenceGridVoltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 53:
                return handle(_differenceGridVoltageParser);
            case HUB + 54:
                return input == catta::json::Token::character('r') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('r') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('o') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('r') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('G')   ? jump(HUB + 74)
                       : input == catta::json::Token::character('C') ? jump(HUB + 59)
                                                                     : error();
            case HUB + 59:
                return input == catta::json::Token::character('u') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('r') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('r') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('e') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('n') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('t') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('S') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('e') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('n') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::character('s') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('o') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('r') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::closeString() ? jump(HUB + 72) : error();
            case HUB + 72:
                return !_errorCurrentSensorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 73:
                return handle(_errorCurrentSensorParser);
            case HUB + 74:
                return input == catta::json::Token::character('r') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('i') ? jump(HUB + 76) : error();
            case HUB + 76:
                return input == catta::json::Token::character('d') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('R') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('e') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('l') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('a') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('i') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('s') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::closeString() ? jump(HUB + 84) : error();
            case HUB + 84:
                return !_errorGridRelaisParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 85:
                return handle(_errorGridRelaisParser);
            case HUB + 86:
                return input == catta::json::Token::character('s') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('l') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('a') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('n') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::character('d') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('G') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('r') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('i') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('d') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::closeString() ? jump(HUB + 96) : error();
            case HUB + 96:
                return !_islandGridParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 97:
                return handle(_islandGridParser);
            case HUB + 98:
                return input == catta::json::Token::character('i') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('m') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('i') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('t') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('e') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('d') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('P') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('o') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('w') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('e') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('r') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('T') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('5')   ? jump(HUB + 123)
                       : input == catta::json::Token::character('4') ? jump(HUB + 120)
                       : input == catta::json::Token::character('3') ? jump(HUB + 117)
                       : input == catta::json::Token::character('2') ? jump(HUB + 114)
                       : input == catta::json::Token::character('1') ? jump(HUB + 111)
                                                                     : error();
            case HUB + 111:
                return input == catta::json::Token::closeString() ? jump(HUB + 112) : error();
            case HUB + 112:
                return !_limitedPowerT1Parser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 113:
                return handle(_limitedPowerT1Parser);
            case HUB + 114:
                return input == catta::json::Token::closeString() ? jump(HUB + 115) : error();
            case HUB + 115:
                return !_limitedPowerT2Parser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 116:
                return handle(_limitedPowerT2Parser);
            case HUB + 117:
                return input == catta::json::Token::closeString() ? jump(HUB + 118) : error();
            case HUB + 118:
                return !_limitedPowerT3Parser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 119:
                return handle(_limitedPowerT3Parser);
            case HUB + 120:
                return input == catta::json::Token::closeString() ? jump(HUB + 121) : error();
            case HUB + 121:
                return !_limitedPowerT4Parser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 122:
                return handle(_limitedPowerT4Parser);
            case HUB + 123:
                return input == catta::json::Token::closeString() ? jump(HUB + 124) : error();
            case HUB + 124:
                return !_limitedPowerT5Parser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 125:
                return handle(_limitedPowerT5Parser);
            case HUB + 126:
                return input == catta::json::Token::character('v') ? jump(HUB + 127) : error();
            case HUB + 127:
                return input == catta::json::Token::character('e') ? jump(HUB + 128) : error();
            case HUB + 128:
                return input == catta::json::Token::character('r') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('V')   ? jump(HUB + 179)
                       : input == catta::json::Token::character('T') ? jump(HUB + 159)
                       : input == catta::json::Token::character('F') ? jump(HUB + 148)
                       : input == catta::json::Token::character('C') ? jump(HUB + 130)
                                                                     : error();
            case HUB + 130:
                return input == catta::json::Token::character('u') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('r') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::character('r') ? jump(HUB + 133) : error();
            case HUB + 133:
                return input == catta::json::Token::character('e') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('n') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('t') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::character('I') ? jump(HUB + 137) : error();
            case HUB + 137:
                return input == catta::json::Token::character('n') ? jump(HUB + 138) : error();
            case HUB + 138:
                return input == catta::json::Token::character('t') ? jump(HUB + 139) : error();
            case HUB + 139:
                return input == catta::json::Token::character('e') ? jump(HUB + 140) : error();
            case HUB + 140:
                return input == catta::json::Token::character('r') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('r') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::character('u') ? jump(HUB + 143) : error();
            case HUB + 143:
                return input == catta::json::Token::character('p') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('t') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::closeString() ? jump(HUB + 146) : error();
            case HUB + 146:
                return !_overCurrentInterruptParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 147:
                return handle(_overCurrentInterruptParser);
            case HUB + 148:
                return input == catta::json::Token::character('r') ? jump(HUB + 149) : error();
            case HUB + 149:
                return input == catta::json::Token::character('e') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('q') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('u') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('e') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::character('n') ? jump(HUB + 154) : error();
            case HUB + 154:
                return input == catta::json::Token::character('c') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('y') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::closeString() ? jump(HUB + 157) : error();
            case HUB + 157:
                return !_overFrequencyParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 158:
                return handle(_overFrequencyParser);
            case HUB + 159:
                return input == catta::json::Token::character('e') ? jump(HUB + 160) : error();
            case HUB + 160:
                return input == catta::json::Token::character('m') ? jump(HUB + 161) : error();
            case HUB + 161:
                return input == catta::json::Token::character('p') ? jump(HUB + 162) : error();
            case HUB + 162:
                return input == catta::json::Token::character('r') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('a') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('t') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('u') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('r') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('e') ? jump(HUB + 168) : error();
            case HUB + 168:
                return input == catta::json::Token::character('S') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::character('h') ? jump(HUB + 170) : error();
            case HUB + 170:
                return input == catta::json::Token::character('u') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::character('t') ? jump(HUB + 172) : error();
            case HUB + 172:
                return input == catta::json::Token::character('d') ? jump(HUB + 173) : error();
            case HUB + 173:
                return input == catta::json::Token::character('o') ? jump(HUB + 174) : error();
            case HUB + 174:
                return input == catta::json::Token::character('w') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('n') ? jump(HUB + 176) : error();
            case HUB + 176:
                return input == catta::json::Token::closeString() ? jump(HUB + 177) : error();
            case HUB + 177:
                return !_overTempratureShutdownParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 178:
                return handle(_overTempratureShutdownParser);
            case HUB + 179:
                return input == catta::json::Token::character('o') ? jump(HUB + 180) : error();
            case HUB + 180:
                return input == catta::json::Token::character('l') ? jump(HUB + 181) : error();
            case HUB + 181:
                return input == catta::json::Token::character('t') ? jump(HUB + 182) : error();
            case HUB + 182:
                return input == catta::json::Token::character('a') ? jump(HUB + 183) : error();
            case HUB + 183:
                return input == catta::json::Token::character('g') ? jump(HUB + 184) : error();
            case HUB + 184:
                return input == catta::json::Token::character('e') ? jump(HUB + 185) : error();
            case HUB + 185:
                return input == catta::json::Token::character('I')   ? jump(HUB + 194)
                       : input == catta::json::Token::character('D') ? jump(HUB + 190)
                       : input == catta::json::Token::character('A') ? jump(HUB + 186)
                                                                     : error();
            case HUB + 186:
                return input == catta::json::Token::character('C') ? jump(HUB + 187) : error();
            case HUB + 187:
                return input == catta::json::Token::closeString() ? jump(HUB + 188) : error();
            case HUB + 188:
                return !_overVoltageACParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 189:
                return handle(_overVoltageACParser);
            case HUB + 190:
                return input == catta::json::Token::character('C') ? jump(HUB + 191) : error();
            case HUB + 191:
                return input == catta::json::Token::closeString() ? jump(HUB + 192) : error();
            case HUB + 192:
                return !_overVoltageDCParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 193:
                return handle(_overVoltageDCParser);
            case HUB + 194:
                return input == catta::json::Token::character('n') ? jump(HUB + 195) : error();
            case HUB + 195:
                return input == catta::json::Token::character('t') ? jump(HUB + 196) : error();
            case HUB + 196:
                return input == catta::json::Token::character('e') ? jump(HUB + 197) : error();
            case HUB + 197:
                return input == catta::json::Token::character('r') ? jump(HUB + 198) : error();
            case HUB + 198:
                return input == catta::json::Token::character('r') ? jump(HUB + 199) : error();
            case HUB + 199:
                return input == catta::json::Token::character('u') ? jump(HUB + 200) : error();
            case HUB + 200:
                return input == catta::json::Token::character('p') ? jump(HUB + 201) : error();
            case HUB + 201:
                return input == catta::json::Token::character('t') ? jump(HUB + 202) : error();
            case HUB + 202:
                return input == catta::json::Token::closeString() ? jump(HUB + 203) : error();
            case HUB + 203:
                return !_overVoltageInterruptParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 204:
                return handle(_overVoltageInterruptParser);
            case HUB + 205:
                return input == catta::json::Token::character('n') ? jump(HUB + 206) : error();
            case HUB + 206:
                return input == catta::json::Token::character('d') ? jump(HUB + 207) : error();
            case HUB + 207:
                return input == catta::json::Token::character('e') ? jump(HUB + 208) : error();
            case HUB + 208:
                return input == catta::json::Token::character('r') ? jump(HUB + 209) : error();
            case HUB + 209:
                return input == catta::json::Token::character('V')   ? jump(HUB + 221)
                       : input == catta::json::Token::character('F') ? jump(HUB + 210)
                                                                     : error();
            case HUB + 210:
                return input == catta::json::Token::character('r') ? jump(HUB + 211) : error();
            case HUB + 211:
                return input == catta::json::Token::character('e') ? jump(HUB + 212) : error();
            case HUB + 212:
                return input == catta::json::Token::character('q') ? jump(HUB + 213) : error();
            case HUB + 213:
                return input == catta::json::Token::character('u') ? jump(HUB + 214) : error();
            case HUB + 214:
                return input == catta::json::Token::character('e') ? jump(HUB + 215) : error();
            case HUB + 215:
                return input == catta::json::Token::character('n') ? jump(HUB + 216) : error();
            case HUB + 216:
                return input == catta::json::Token::character('c') ? jump(HUB + 217) : error();
            case HUB + 217:
                return input == catta::json::Token::character('y') ? jump(HUB + 218) : error();
            case HUB + 218:
                return input == catta::json::Token::closeString() ? jump(HUB + 219) : error();
            case HUB + 219:
                return !_underFrequencyParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 220:
                return handle(_underFrequencyParser);
            case HUB + 221:
                return input == catta::json::Token::character('o') ? jump(HUB + 222) : error();
            case HUB + 222:
                return input == catta::json::Token::character('l') ? jump(HUB + 223) : error();
            case HUB + 223:
                return input == catta::json::Token::character('t') ? jump(HUB + 224) : error();
            case HUB + 224:
                return input == catta::json::Token::character('a') ? jump(HUB + 225) : error();
            case HUB + 225:
                return input == catta::json::Token::character('g') ? jump(HUB + 226) : error();
            case HUB + 226:
                return input == catta::json::Token::character('e') ? jump(HUB + 227) : error();
            case HUB + 227:
                return input == catta::json::Token::character('D')   ? jump(HUB + 232)
                       : input == catta::json::Token::character('A') ? jump(HUB + 228)
                                                                     : error();
            case HUB + 228:
                return input == catta::json::Token::character('C') ? jump(HUB + 229) : error();
            case HUB + 229:
                return input == catta::json::Token::closeString() ? jump(HUB + 230) : error();
            case HUB + 230:
                return !_underVoltageACParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 231:
                return handle(_underVoltageACParser);
            case HUB + 232:
                return input == catta::json::Token::character('C') ? jump(HUB + 233) : error();
            case HUB + 233:
                return input == catta::json::Token::closeString() ? jump(HUB + 234) : error();
            case HUB + 234:
                return !_underVoltageDCParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 235:
                return handle(_underVoltageDCParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_overVoltageACParser.data(), _underVoltageACParser.data(), _overVoltageDCParser.data(),
                                               _underVoltageDCParser.data(), _overFrequencyParser.data(), _underFrequencyParser.data(),
                                               _limitedPowerT1Parser.data(), _limitedPowerT2Parser.data(), _limitedPowerT3Parser.data(),
                                               _limitedPowerT4Parser.data(), _limitedPowerT5Parser.data(), _comParser.data(),
                                               _islandGridParser.data(), _overCurrentInterruptParser.data(), _overVoltageInterruptParser.data(),
                                               _averageGridOverVoltageParser.data(), _overTempratureShutdownParser.data(),
                                               _differenceGridVoltageParser.data(), _errorGridRelaisParser.data(), _errorCurrentSensorParser.data())
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
    Parser<catta::modbus::sunspec::ValueU16> _averageGridOverVoltageParser;
    Parser<catta::modbus::sunspec::ValueU16> _comParser;
    Parser<catta::modbus::sunspec::ValueU16> _differenceGridVoltageParser;
    Parser<catta::modbus::sunspec::ValueU16> _errorCurrentSensorParser;
    Parser<catta::modbus::sunspec::ValueU16> _errorGridRelaisParser;
    Parser<catta::modbus::sunspec::ValueU16> _islandGridParser;
    Parser<catta::modbus::sunspec::ValueU16> _limitedPowerT1Parser;
    Parser<catta::modbus::sunspec::ValueU16> _limitedPowerT2Parser;
    Parser<catta::modbus::sunspec::ValueU16> _limitedPowerT3Parser;
    Parser<catta::modbus::sunspec::ValueU16> _limitedPowerT4Parser;
    Parser<catta::modbus::sunspec::ValueU16> _limitedPowerT5Parser;
    Parser<catta::modbus::sunspec::ValueU16> _overCurrentInterruptParser;
    Parser<catta::modbus::sunspec::ValueU16> _overFrequencyParser;
    Parser<catta::modbus::sunspec::ValueU16> _overTempratureShutdownParser;
    Parser<catta::modbus::sunspec::ValueU16> _overVoltageACParser;
    Parser<catta::modbus::sunspec::ValueU16> _overVoltageDCParser;
    Parser<catta::modbus::sunspec::ValueU16> _overVoltageInterruptParser;
    Parser<catta::modbus::sunspec::ValueU16> _underFrequencyParser;
    Parser<catta::modbus::sunspec::ValueU16> _underVoltageACParser;
    Parser<catta::modbus::sunspec::ValueU16> _underVoltageDCParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 236;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
