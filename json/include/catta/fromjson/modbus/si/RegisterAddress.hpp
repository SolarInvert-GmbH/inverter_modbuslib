#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::RegisterAddress>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::RegisterAddress;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint16_t state)
        {
            _state = state;
            return stay();
        };
        const auto close = [jump, this](std::uint8_t data)
        {
            _data = data;
            return jump(TAIL + 0);
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openString() ? jump(HUB + 0) : error();
            case HUB + 0:
                return input == catta::json::Token::character('S')   ? jump(HUB + 445)
                       : input == catta::json::Token::character('N') ? jump(HUB + 429)
                       : input == catta::json::Token::character('I') ? jump(HUB + 173)
                       : input == catta::json::Token::character('E') ? jump(HUB + 143)
                       : input == catta::json::Token::character('C') ? jump(HUB + 96)
                       : input == catta::json::Token::character('B') ? jump(HUB + 1)
                                                                     : error();
            case HUB + 1:
                return input == catta::json::Token::character('a') ? jump(HUB + 2) : error();
            case HUB + 2:
                return input == catta::json::Token::character('s') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('i') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('c') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('S') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('e') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('t') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('t') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('i') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('n') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('g') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('s') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('W')   ? jump(HUB + 81)
                       : input == catta::json::Token::character('V') ? jump(HUB + 42)
                       : input == catta::json::Token::character('E') ? jump(HUB + 23)
                       : input == catta::json::Token::character('C') ? jump(HUB + 14)
                                                                     : error();
            case HUB + 14:
                return input == catta::json::Token::character('o') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('n') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('n') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('P') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('h') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('a') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('s') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('e') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::closeString() ? close(33) : error();
            case HUB + 23:
                return input == catta::json::Token::character('c') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('p') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('N') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('o') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('m') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::character('H') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('z') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('S')  ? jump(HUB + 31)
                       : input == catta::json::Token::closeString() ? close(32)
                                                                    : error();
            case HUB + 31:
                return input == catta::json::Token::character('c') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('a') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('l') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('e') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('F') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('a') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('c') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('t') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('o') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('r') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::closeString() ? close(38) : error();
            case HUB + 42:
                return input == catta::json::Token::character('a')   ? jump(HUB + 51)
                       : input == catta::json::Token::character('M') ? jump(HUB + 43)
                                                                     : error();
            case HUB + 43:
                return input == catta::json::Token::character('i')   ? jump(HUB + 46)
                       : input == catta::json::Token::character('a') ? jump(HUB + 44)
                                                                     : error();
            case HUB + 44:
                return input == catta::json::Token::character('x') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::closeString() ? close(30) : error();
            case HUB + 46:
                return input == catta::json::Token::character('n') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('M')  ? jump(HUB + 48)
                       : input == catta::json::Token::closeString() ? close(31)
                                                                    : error();
            case HUB + 48:
                return input == catta::json::Token::character('a') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('x') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::closeString() ? close(35) : error();
            case HUB + 51:
                return input == catta::json::Token::character('r')   ? jump(HUB + 66)
                       : input == catta::json::Token::character('M') ? jump(HUB + 52)
                                                                     : error();
            case HUB + 52:
                return input == catta::json::Token::character('a') ? jump(HUB + 53) : error();
            case HUB + 53:
                return input == catta::json::Token::character('x') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::character('S') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('c') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('a') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('l') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('e') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('F') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('a') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('c') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('t') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('o') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('r') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::closeString() ? close(36) : error();
            case HUB + 66:
                return input == catta::json::Token::character('M') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('a') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::character('x') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('S') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('c') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('a') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('l') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('e') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::character('F') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('a') ? jump(HUB + 76) : error();
            case HUB + 76:
                return input == catta::json::Token::character('c') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('t') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('o') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('r') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::closeString() ? close(37) : error();
            case HUB + 81:
                return input == catta::json::Token::character('M') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('a') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('x') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('S')  ? jump(HUB + 85)
                       : input == catta::json::Token::closeString() ? close(29)
                                                                    : error();
            case HUB + 85:
                return input == catta::json::Token::character('c') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('a') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('l') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('e') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('F') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::character('a') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('c') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('t') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('o') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('r') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::closeString() ? close(34) : error();
            case HUB + 96:
                return input == catta::json::Token::character('o') ? jump(HUB + 97) : error();
            case HUB + 97:
                return input == catta::json::Token::character('m') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::character('m') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('o') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('n') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('S')   ? jump(HUB + 131)
                       : input == catta::json::Token::character('M') ? jump(HUB + 115)
                       : input == catta::json::Token::character('D') ? jump(HUB + 102)
                                                                     : error();
            case HUB + 102:
                return input == catta::json::Token::character('e') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('v') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('i') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('c') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('e') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('A') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('d') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('d') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('r') ? jump(HUB + 111) : error();
            case HUB + 111:
                return input == catta::json::Token::character('e') ? jump(HUB + 112) : error();
            case HUB + 112:
                return input == catta::json::Token::character('s') ? jump(HUB + 113) : error();
            case HUB + 113:
                return input == catta::json::Token::character('s') ? jump(HUB + 114) : error();
            case HUB + 114:
                return input == catta::json::Token::closeString() ? close(3) : error();
            case HUB + 115:
                return input == catta::json::Token::character('o')   ? jump(HUB + 127)
                       : input == catta::json::Token::character('a') ? jump(HUB + 116)
                                                                     : error();
            case HUB + 116:
                return input == catta::json::Token::character('n') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('u') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('f') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::character('a') ? jump(HUB + 120) : error();
            case HUB + 120:
                return input == catta::json::Token::character('c') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('t') ? jump(HUB + 122) : error();
            case HUB + 122:
                return input == catta::json::Token::character('u') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::character('r') ? jump(HUB + 124) : error();
            case HUB + 124:
                return input == catta::json::Token::character('e') ? jump(HUB + 125) : error();
            case HUB + 125:
                return input == catta::json::Token::character('r') ? jump(HUB + 126) : error();
            case HUB + 126:
                return input == catta::json::Token::closeString() ? close(0) : error();
            case HUB + 127:
                return input == catta::json::Token::character('d') ? jump(HUB + 128) : error();
            case HUB + 128:
                return input == catta::json::Token::character('e') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('l') ? jump(HUB + 130) : error();
            case HUB + 130:
                return input == catta::json::Token::closeString() ? close(1) : error();
            case HUB + 131:
                return input == catta::json::Token::character('e') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::character('r') ? jump(HUB + 133) : error();
            case HUB + 133:
                return input == catta::json::Token::character('i') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('a') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('l') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::character('N') ? jump(HUB + 137) : error();
            case HUB + 137:
                return input == catta::json::Token::character('u') ? jump(HUB + 138) : error();
            case HUB + 138:
                return input == catta::json::Token::character('m') ? jump(HUB + 139) : error();
            case HUB + 139:
                return input == catta::json::Token::character('b') ? jump(HUB + 140) : error();
            case HUB + 140:
                return input == catta::json::Token::character('e') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('r') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::closeString() ? close(2) : error();
            case HUB + 143:
                return input == catta::json::Token::character('x') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('t') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::character('e') ? jump(HUB + 146) : error();
            case HUB + 146:
                return input == catta::json::Token::character('n') ? jump(HUB + 147) : error();
            case HUB + 147:
                return input == catta::json::Token::character('d') ? jump(HUB + 148) : error();
            case HUB + 148:
                return input == catta::json::Token::character('e') ? jump(HUB + 149) : error();
            case HUB + 149:
                return input == catta::json::Token::character('d') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('M') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('e') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('s') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::character('u') ? jump(HUB + 154) : error();
            case HUB + 154:
                return input == catta::json::Token::character('r') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('e') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::character('m') ? jump(HUB + 157) : error();
            case HUB + 157:
                return input == catta::json::Token::character('e') ? jump(HUB + 158) : error();
            case HUB + 158:
                return input == catta::json::Token::character('n') ? jump(HUB + 159) : error();
            case HUB + 159:
                return input == catta::json::Token::character('t') ? jump(HUB + 160) : error();
            case HUB + 160:
                return input == catta::json::Token::character('s') ? jump(HUB + 161) : error();
            case HUB + 161:
                return input == catta::json::Token::character('A') ? jump(HUB + 162) : error();
            case HUB + 162:
                return input == catta::json::Token::character('c') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('W') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('a') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('t') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('t') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('H') ? jump(HUB + 168) : error();
            case HUB + 168:
                return input == catta::json::Token::character('o') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::character('u') ? jump(HUB + 170) : error();
            case HUB + 170:
                return input == catta::json::Token::character('r') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::character('s') ? jump(HUB + 172) : error();
            case HUB + 172:
                return input == catta::json::Token::closeString() ? close(39) : error();
            case HUB + 173:
                return input == catta::json::Token::character('n')   ? jump(HUB + 216)
                       : input == catta::json::Token::character('m') ? jump(HUB + 174)
                                                                     : error();
            case HUB + 174:
                return input == catta::json::Token::character('m') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('e') ? jump(HUB + 176) : error();
            case HUB + 176:
                return input == catta::json::Token::character('d') ? jump(HUB + 177) : error();
            case HUB + 177:
                return input == catta::json::Token::character('i') ? jump(HUB + 178) : error();
            case HUB + 178:
                return input == catta::json::Token::character('a') ? jump(HUB + 179) : error();
            case HUB + 179:
                return input == catta::json::Token::character('t') ? jump(HUB + 180) : error();
            case HUB + 180:
                return input == catta::json::Token::character('e') ? jump(HUB + 181) : error();
            case HUB + 181:
                return input == catta::json::Token::character('P')   ? jump(HUB + 206)
                       : input == catta::json::Token::character('C') ? jump(HUB + 182)
                                                                     : error();
            case HUB + 182:
                return input == catta::json::Token::character('o') ? jump(HUB + 183) : error();
            case HUB + 183:
                return input == catta::json::Token::character('n') ? jump(HUB + 184) : error();
            case HUB + 184:
                return input == catta::json::Token::character('n') ? jump(HUB + 185) : error();
            case HUB + 185:
                return input == catta::json::Token::character('e') ? jump(HUB + 186) : error();
            case HUB + 186:
                return input == catta::json::Token::character('c') ? jump(HUB + 187) : error();
            case HUB + 187:
                return input == catta::json::Token::character('t') ? jump(HUB + 188) : error();
            case HUB + 188:
                return input == catta::json::Token::character('i') ? jump(HUB + 189) : error();
            case HUB + 189:
                return input == catta::json::Token::character('o') ? jump(HUB + 190) : error();
            case HUB + 190:
                return input == catta::json::Token::character('n') ? jump(HUB + 191) : error();
            case HUB + 191:
                return input == catta::json::Token::character('T')   ? jump(HUB + 199)
                       : input == catta::json::Token::character('C') ? jump(HUB + 192)
                                                                     : error();
            case HUB + 192:
                return input == catta::json::Token::character('o') ? jump(HUB + 193) : error();
            case HUB + 193:
                return input == catta::json::Token::character('n') ? jump(HUB + 194) : error();
            case HUB + 194:
                return input == catta::json::Token::character('t') ? jump(HUB + 195) : error();
            case HUB + 195:
                return input == catta::json::Token::character('r') ? jump(HUB + 196) : error();
            case HUB + 196:
                return input == catta::json::Token::character('o') ? jump(HUB + 197) : error();
            case HUB + 197:
                return input == catta::json::Token::character('l') ? jump(HUB + 198) : error();
            case HUB + 198:
                return input == catta::json::Token::closeString() ? close(41) : error();
            case HUB + 199:
                return input == catta::json::Token::character('i') ? jump(HUB + 200) : error();
            case HUB + 200:
                return input == catta::json::Token::character('m') ? jump(HUB + 201) : error();
            case HUB + 201:
                return input == catta::json::Token::character('e') ? jump(HUB + 202) : error();
            case HUB + 202:
                return input == catta::json::Token::character('o') ? jump(HUB + 203) : error();
            case HUB + 203:
                return input == catta::json::Token::character('u') ? jump(HUB + 204) : error();
            case HUB + 204:
                return input == catta::json::Token::character('t') ? jump(HUB + 205) : error();
            case HUB + 205:
                return input == catta::json::Token::closeString() ? close(40) : error();
            case HUB + 206:
                return input == catta::json::Token::character('o') ? jump(HUB + 207) : error();
            case HUB + 207:
                return input == catta::json::Token::character('w') ? jump(HUB + 208) : error();
            case HUB + 208:
                return input == catta::json::Token::character('e') ? jump(HUB + 209) : error();
            case HUB + 209:
                return input == catta::json::Token::character('r') ? jump(HUB + 210) : error();
            case HUB + 210:
                return input == catta::json::Token::character('L') ? jump(HUB + 211) : error();
            case HUB + 211:
                return input == catta::json::Token::character('i') ? jump(HUB + 212) : error();
            case HUB + 212:
                return input == catta::json::Token::character('m') ? jump(HUB + 213) : error();
            case HUB + 213:
                return input == catta::json::Token::character('i') ? jump(HUB + 214) : error();
            case HUB + 214:
                return input == catta::json::Token::character('t') ? jump(HUB + 215) : error();
            case HUB + 215:
                return input == catta::json::Token::closeString() ? close(42) : error();
            case HUB + 216:
                return input == catta::json::Token::character('v') ? jump(HUB + 217) : error();
            case HUB + 217:
                return input == catta::json::Token::character('e') ? jump(HUB + 218) : error();
            case HUB + 218:
                return input == catta::json::Token::character('r') ? jump(HUB + 219) : error();
            case HUB + 219:
                return input == catta::json::Token::character('t') ? jump(HUB + 220) : error();
            case HUB + 220:
                return input == catta::json::Token::character('e') ? jump(HUB + 221) : error();
            case HUB + 221:
                return input == catta::json::Token::character('r') ? jump(HUB + 222) : error();
            case HUB + 222:
                return input == catta::json::Token::character('W')   ? jump(HUB + 398)
                       : input == catta::json::Token::character('V') ? jump(HUB + 365)
                       : input == catta::json::Token::character('T') ? jump(HUB + 343)
                       : input == catta::json::Token::character('P') ? jump(HUB + 296)
                       : input == catta::json::Token::character('O') ? jump(HUB + 282)
                       : input == catta::json::Token::character('H') ? jump(HUB + 266)
                       : input == catta::json::Token::character('D') ? jump(HUB + 246)
                       : input == catta::json::Token::character('A') ? jump(HUB + 223)
                                                                     : error();
            case HUB + 223:
                return input == catta::json::Token::character('m') ? jump(HUB + 224) : error();
            case HUB + 224:
                return input == catta::json::Token::character('p') ? jump(HUB + 225) : error();
            case HUB + 225:
                return input == catta::json::Token::character('s') ? jump(HUB + 226) : error();
            case HUB + 226:
                return input == catta::json::Token::character('S')   ? jump(HUB + 235)
                       : input == catta::json::Token::character('P') ? jump(HUB + 227)
                       : input == catta::json::Token::closeString()  ? close(4)
                                                                     : error();
            case HUB + 227:
                return input == catta::json::Token::character('h') ? jump(HUB + 228) : error();
            case HUB + 228:
                return input == catta::json::Token::character('a') ? jump(HUB + 229) : error();
            case HUB + 229:
                return input == catta::json::Token::character('s') ? jump(HUB + 230) : error();
            case HUB + 230:
                return input == catta::json::Token::character('e') ? jump(HUB + 231) : error();
            case HUB + 231:
                return input == catta::json::Token::character('C')   ? jump(HUB + 234)
                       : input == catta::json::Token::character('B') ? jump(HUB + 233)
                       : input == catta::json::Token::character('A') ? jump(HUB + 232)
                                                                     : error();
            case HUB + 232:
                return input == catta::json::Token::closeString() ? close(5) : error();
            case HUB + 233:
                return input == catta::json::Token::closeString() ? close(6) : error();
            case HUB + 234:
                return input == catta::json::Token::closeString() ? close(7) : error();
            case HUB + 235:
                return input == catta::json::Token::character('c') ? jump(HUB + 236) : error();
            case HUB + 236:
                return input == catta::json::Token::character('a') ? jump(HUB + 237) : error();
            case HUB + 237:
                return input == catta::json::Token::character('l') ? jump(HUB + 238) : error();
            case HUB + 238:
                return input == catta::json::Token::character('e') ? jump(HUB + 239) : error();
            case HUB + 239:
                return input == catta::json::Token::character('F') ? jump(HUB + 240) : error();
            case HUB + 240:
                return input == catta::json::Token::character('a') ? jump(HUB + 241) : error();
            case HUB + 241:
                return input == catta::json::Token::character('c') ? jump(HUB + 242) : error();
            case HUB + 242:
                return input == catta::json::Token::character('t') ? jump(HUB + 243) : error();
            case HUB + 243:
                return input == catta::json::Token::character('o') ? jump(HUB + 244) : error();
            case HUB + 244:
                return input == catta::json::Token::character('r') ? jump(HUB + 245) : error();
            case HUB + 245:
                return input == catta::json::Token::closeString() ? close(8) : error();
            case HUB + 246:
                return input == catta::json::Token::character('c') ? jump(HUB + 247) : error();
            case HUB + 247:
                return input == catta::json::Token::character('V') ? jump(HUB + 248) : error();
            case HUB + 248:
                return input == catta::json::Token::character('o') ? jump(HUB + 249) : error();
            case HUB + 249:
                return input == catta::json::Token::character('l') ? jump(HUB + 250) : error();
            case HUB + 250:
                return input == catta::json::Token::character('t') ? jump(HUB + 251) : error();
            case HUB + 251:
                return input == catta::json::Token::character('a') ? jump(HUB + 252) : error();
            case HUB + 252:
                return input == catta::json::Token::character('g') ? jump(HUB + 253) : error();
            case HUB + 253:
                return input == catta::json::Token::character('e') ? jump(HUB + 254) : error();
            case HUB + 254:
                return input == catta::json::Token::character('S')  ? jump(HUB + 255)
                       : input == catta::json::Token::closeString() ? close(21)
                                                                    : error();
            case HUB + 255:
                return input == catta::json::Token::character('c') ? jump(HUB + 256) : error();
            case HUB + 256:
                return input == catta::json::Token::character('a') ? jump(HUB + 257) : error();
            case HUB + 257:
                return input == catta::json::Token::character('l') ? jump(HUB + 258) : error();
            case HUB + 258:
                return input == catta::json::Token::character('e') ? jump(HUB + 259) : error();
            case HUB + 259:
                return input == catta::json::Token::character('F') ? jump(HUB + 260) : error();
            case HUB + 260:
                return input == catta::json::Token::character('a') ? jump(HUB + 261) : error();
            case HUB + 261:
                return input == catta::json::Token::character('c') ? jump(HUB + 262) : error();
            case HUB + 262:
                return input == catta::json::Token::character('t') ? jump(HUB + 263) : error();
            case HUB + 263:
                return input == catta::json::Token::character('o') ? jump(HUB + 264) : error();
            case HUB + 264:
                return input == catta::json::Token::character('r') ? jump(HUB + 265) : error();
            case HUB + 265:
                return input == catta::json::Token::closeString() ? close(22) : error();
            case HUB + 266:
                return input == catta::json::Token::character('e') ? jump(HUB + 267) : error();
            case HUB + 267:
                return input == catta::json::Token::character('r') ? jump(HUB + 268) : error();
            case HUB + 268:
                return input == catta::json::Token::character('t') ? jump(HUB + 269) : error();
            case HUB + 269:
                return input == catta::json::Token::character('z') ? jump(HUB + 270) : error();
            case HUB + 270:
                return input == catta::json::Token::character('S')  ? jump(HUB + 271)
                       : input == catta::json::Token::closeString() ? close(15)
                                                                    : error();
            case HUB + 271:
                return input == catta::json::Token::character('c') ? jump(HUB + 272) : error();
            case HUB + 272:
                return input == catta::json::Token::character('a') ? jump(HUB + 273) : error();
            case HUB + 273:
                return input == catta::json::Token::character('l') ? jump(HUB + 274) : error();
            case HUB + 274:
                return input == catta::json::Token::character('e') ? jump(HUB + 275) : error();
            case HUB + 275:
                return input == catta::json::Token::character('F') ? jump(HUB + 276) : error();
            case HUB + 276:
                return input == catta::json::Token::character('a') ? jump(HUB + 277) : error();
            case HUB + 277:
                return input == catta::json::Token::character('c') ? jump(HUB + 278) : error();
            case HUB + 278:
                return input == catta::json::Token::character('t') ? jump(HUB + 279) : error();
            case HUB + 279:
                return input == catta::json::Token::character('o') ? jump(HUB + 280) : error();
            case HUB + 280:
                return input == catta::json::Token::character('r') ? jump(HUB + 281) : error();
            case HUB + 281:
                return input == catta::json::Token::closeString() ? close(16) : error();
            case HUB + 282:
                return input == catta::json::Token::character('p') ? jump(HUB + 283) : error();
            case HUB + 283:
                return input == catta::json::Token::character('e') ? jump(HUB + 284) : error();
            case HUB + 284:
                return input == catta::json::Token::character('r') ? jump(HUB + 285) : error();
            case HUB + 285:
                return input == catta::json::Token::character('a') ? jump(HUB + 286) : error();
            case HUB + 286:
                return input == catta::json::Token::character('t') ? jump(HUB + 287) : error();
            case HUB + 287:
                return input == catta::json::Token::character('i') ? jump(HUB + 288) : error();
            case HUB + 288:
                return input == catta::json::Token::character('n') ? jump(HUB + 289) : error();
            case HUB + 289:
                return input == catta::json::Token::character('g') ? jump(HUB + 290) : error();
            case HUB + 290:
                return input == catta::json::Token::character('S') ? jump(HUB + 291) : error();
            case HUB + 291:
                return input == catta::json::Token::character('t') ? jump(HUB + 292) : error();
            case HUB + 292:
                return input == catta::json::Token::character('a') ? jump(HUB + 293) : error();
            case HUB + 293:
                return input == catta::json::Token::character('t') ? jump(HUB + 294) : error();
            case HUB + 294:
                return input == catta::json::Token::character('e') ? jump(HUB + 295) : error();
            case HUB + 295:
                return input == catta::json::Token::closeString() ? close(25) : error();
            case HUB + 296:
                return input == catta::json::Token::character('o')   ? jump(HUB + 322)
                       : input == catta::json::Token::character('h') ? jump(HUB + 297)
                                                                     : error();
            case HUB + 297:
                return input == catta::json::Token::character('a') ? jump(HUB + 298) : error();
            case HUB + 298:
                return input == catta::json::Token::character('s') ? jump(HUB + 299) : error();
            case HUB + 299:
                return input == catta::json::Token::character('e') ? jump(HUB + 300) : error();
            case HUB + 300:
                return input == catta::json::Token::character('V') ? jump(HUB + 301) : error();
            case HUB + 301:
                return input == catta::json::Token::character('o') ? jump(HUB + 302) : error();
            case HUB + 302:
                return input == catta::json::Token::character('l') ? jump(HUB + 303) : error();
            case HUB + 303:
                return input == catta::json::Token::character('t') ? jump(HUB + 304) : error();
            case HUB + 304:
                return input == catta::json::Token::character('a') ? jump(HUB + 305) : error();
            case HUB + 305:
                return input == catta::json::Token::character('g') ? jump(HUB + 306) : error();
            case HUB + 306:
                return input == catta::json::Token::character('e') ? jump(HUB + 307) : error();
            case HUB + 307:
                return input == catta::json::Token::character('S')   ? jump(HUB + 311)
                       : input == catta::json::Token::character('C') ? jump(HUB + 310)
                       : input == catta::json::Token::character('B') ? jump(HUB + 309)
                       : input == catta::json::Token::character('A') ? jump(HUB + 308)
                                                                     : error();
            case HUB + 308:
                return input == catta::json::Token::closeString() ? close(9) : error();
            case HUB + 309:
                return input == catta::json::Token::closeString() ? close(10) : error();
            case HUB + 310:
                return input == catta::json::Token::closeString() ? close(11) : error();
            case HUB + 311:
                return input == catta::json::Token::character('c') ? jump(HUB + 312) : error();
            case HUB + 312:
                return input == catta::json::Token::character('a') ? jump(HUB + 313) : error();
            case HUB + 313:
                return input == catta::json::Token::character('l') ? jump(HUB + 314) : error();
            case HUB + 314:
                return input == catta::json::Token::character('e') ? jump(HUB + 315) : error();
            case HUB + 315:
                return input == catta::json::Token::character('F') ? jump(HUB + 316) : error();
            case HUB + 316:
                return input == catta::json::Token::character('a') ? jump(HUB + 317) : error();
            case HUB + 317:
                return input == catta::json::Token::character('c') ? jump(HUB + 318) : error();
            case HUB + 318:
                return input == catta::json::Token::character('t') ? jump(HUB + 319) : error();
            case HUB + 319:
                return input == catta::json::Token::character('o') ? jump(HUB + 320) : error();
            case HUB + 320:
                return input == catta::json::Token::character('r') ? jump(HUB + 321) : error();
            case HUB + 321:
                return input == catta::json::Token::closeString() ? close(12) : error();
            case HUB + 322:
                return input == catta::json::Token::character('w') ? jump(HUB + 323) : error();
            case HUB + 323:
                return input == catta::json::Token::character('e') ? jump(HUB + 324) : error();
            case HUB + 324:
                return input == catta::json::Token::character('r') ? jump(HUB + 325) : error();
            case HUB + 325:
                return input == catta::json::Token::character('F') ? jump(HUB + 326) : error();
            case HUB + 326:
                return input == catta::json::Token::character('a') ? jump(HUB + 327) : error();
            case HUB + 327:
                return input == catta::json::Token::character('c') ? jump(HUB + 328) : error();
            case HUB + 328:
                return input == catta::json::Token::character('t') ? jump(HUB + 329) : error();
            case HUB + 329:
                return input == catta::json::Token::character('o') ? jump(HUB + 330) : error();
            case HUB + 330:
                return input == catta::json::Token::character('r') ? jump(HUB + 331) : error();
            case HUB + 331:
                return input == catta::json::Token::character('S')  ? jump(HUB + 332)
                       : input == catta::json::Token::closeString() ? close(17)
                                                                    : error();
            case HUB + 332:
                return input == catta::json::Token::character('c') ? jump(HUB + 333) : error();
            case HUB + 333:
                return input == catta::json::Token::character('a') ? jump(HUB + 334) : error();
            case HUB + 334:
                return input == catta::json::Token::character('l') ? jump(HUB + 335) : error();
            case HUB + 335:
                return input == catta::json::Token::character('e') ? jump(HUB + 336) : error();
            case HUB + 336:
                return input == catta::json::Token::character('F') ? jump(HUB + 337) : error();
            case HUB + 337:
                return input == catta::json::Token::character('a') ? jump(HUB + 338) : error();
            case HUB + 338:
                return input == catta::json::Token::character('c') ? jump(HUB + 339) : error();
            case HUB + 339:
                return input == catta::json::Token::character('t') ? jump(HUB + 340) : error();
            case HUB + 340:
                return input == catta::json::Token::character('o') ? jump(HUB + 341) : error();
            case HUB + 341:
                return input == catta::json::Token::character('r') ? jump(HUB + 342) : error();
            case HUB + 342:
                return input == catta::json::Token::closeString() ? close(18) : error();
            case HUB + 343:
                return input == catta::json::Token::character('e') ? jump(HUB + 344) : error();
            case HUB + 344:
                return input == catta::json::Token::character('m') ? jump(HUB + 345) : error();
            case HUB + 345:
                return input == catta::json::Token::character('p') ? jump(HUB + 346) : error();
            case HUB + 346:
                return input == catta::json::Token::character('e') ? jump(HUB + 347) : error();
            case HUB + 347:
                return input == catta::json::Token::character('r') ? jump(HUB + 348) : error();
            case HUB + 348:
                return input == catta::json::Token::character('a') ? jump(HUB + 349) : error();
            case HUB + 349:
                return input == catta::json::Token::character('t') ? jump(HUB + 350) : error();
            case HUB + 350:
                return input == catta::json::Token::character('u') ? jump(HUB + 351) : error();
            case HUB + 351:
                return input == catta::json::Token::character('r') ? jump(HUB + 352) : error();
            case HUB + 352:
                return input == catta::json::Token::character('e') ? jump(HUB + 353) : error();
            case HUB + 353:
                return input == catta::json::Token::character('S')  ? jump(HUB + 354)
                       : input == catta::json::Token::closeString() ? close(23)
                                                                    : error();
            case HUB + 354:
                return input == catta::json::Token::character('c') ? jump(HUB + 355) : error();
            case HUB + 355:
                return input == catta::json::Token::character('a') ? jump(HUB + 356) : error();
            case HUB + 356:
                return input == catta::json::Token::character('l') ? jump(HUB + 357) : error();
            case HUB + 357:
                return input == catta::json::Token::character('e') ? jump(HUB + 358) : error();
            case HUB + 358:
                return input == catta::json::Token::character('F') ? jump(HUB + 359) : error();
            case HUB + 359:
                return input == catta::json::Token::character('a') ? jump(HUB + 360) : error();
            case HUB + 360:
                return input == catta::json::Token::character('c') ? jump(HUB + 361) : error();
            case HUB + 361:
                return input == catta::json::Token::character('t') ? jump(HUB + 362) : error();
            case HUB + 362:
                return input == catta::json::Token::character('o') ? jump(HUB + 363) : error();
            case HUB + 363:
                return input == catta::json::Token::character('r') ? jump(HUB + 364) : error();
            case HUB + 364:
                return input == catta::json::Token::closeString() ? close(24) : error();
            case HUB + 365:
                return input == catta::json::Token::character('e') ? jump(HUB + 366) : error();
            case HUB + 366:
                return input == catta::json::Token::character('n') ? jump(HUB + 367) : error();
            case HUB + 367:
                return input == catta::json::Token::character('d') ? jump(HUB + 368) : error();
            case HUB + 368:
                return input == catta::json::Token::character('o') ? jump(HUB + 369) : error();
            case HUB + 369:
                return input == catta::json::Token::character('r') ? jump(HUB + 370) : error();
            case HUB + 370:
                return input == catta::json::Token::character('O')   ? jump(HUB + 384)
                       : input == catta::json::Token::character('E') ? jump(HUB + 371)
                                                                     : error();
            case HUB + 371:
                return input == catta::json::Token::character('v') ? jump(HUB + 372) : error();
            case HUB + 372:
                return input == catta::json::Token::character('e') ? jump(HUB + 373) : error();
            case HUB + 373:
                return input == catta::json::Token::character('n') ? jump(HUB + 374) : error();
            case HUB + 374:
                return input == catta::json::Token::character('t') ? jump(HUB + 375) : error();
            case HUB + 375:
                return input == catta::json::Token::character('B') ? jump(HUB + 376) : error();
            case HUB + 376:
                return input == catta::json::Token::character('i') ? jump(HUB + 377) : error();
            case HUB + 377:
                return input == catta::json::Token::character('t') ? jump(HUB + 378) : error();
            case HUB + 378:
                return input == catta::json::Token::character('f') ? jump(HUB + 379) : error();
            case HUB + 379:
                return input == catta::json::Token::character('i') ? jump(HUB + 380) : error();
            case HUB + 380:
                return input == catta::json::Token::character('e') ? jump(HUB + 381) : error();
            case HUB + 381:
                return input == catta::json::Token::character('l') ? jump(HUB + 382) : error();
            case HUB + 382:
                return input == catta::json::Token::character('d') ? jump(HUB + 383) : error();
            case HUB + 383:
                return input == catta::json::Token::closeString() ? close(27) : error();
            case HUB + 384:
                return input == catta::json::Token::character('p') ? jump(HUB + 385) : error();
            case HUB + 385:
                return input == catta::json::Token::character('e') ? jump(HUB + 386) : error();
            case HUB + 386:
                return input == catta::json::Token::character('r') ? jump(HUB + 387) : error();
            case HUB + 387:
                return input == catta::json::Token::character('a') ? jump(HUB + 388) : error();
            case HUB + 388:
                return input == catta::json::Token::character('t') ? jump(HUB + 389) : error();
            case HUB + 389:
                return input == catta::json::Token::character('i') ? jump(HUB + 390) : error();
            case HUB + 390:
                return input == catta::json::Token::character('n') ? jump(HUB + 391) : error();
            case HUB + 391:
                return input == catta::json::Token::character('g') ? jump(HUB + 392) : error();
            case HUB + 392:
                return input == catta::json::Token::character('S') ? jump(HUB + 393) : error();
            case HUB + 393:
                return input == catta::json::Token::character('t') ? jump(HUB + 394) : error();
            case HUB + 394:
                return input == catta::json::Token::character('a') ? jump(HUB + 395) : error();
            case HUB + 395:
                return input == catta::json::Token::character('t') ? jump(HUB + 396) : error();
            case HUB + 396:
                return input == catta::json::Token::character('e') ? jump(HUB + 397) : error();
            case HUB + 397:
                return input == catta::json::Token::closeString() ? close(26) : error();
            case HUB + 398:
                return input == catta::json::Token::character('a') ? jump(HUB + 399) : error();
            case HUB + 399:
                return input == catta::json::Token::character('t') ? jump(HUB + 400) : error();
            case HUB + 400:
                return input == catta::json::Token::character('t') ? jump(HUB + 401) : error();
            case HUB + 401:
                return input == catta::json::Token::character('S')   ? jump(HUB + 418)
                       : input == catta::json::Token::character('H') ? jump(HUB + 402)
                       : input == catta::json::Token::closeString()  ? close(13)
                                                                     : error();
            case HUB + 402:
                return input == catta::json::Token::character('o') ? jump(HUB + 403) : error();
            case HUB + 403:
                return input == catta::json::Token::character('u') ? jump(HUB + 404) : error();
            case HUB + 404:
                return input == catta::json::Token::character('r') ? jump(HUB + 405) : error();
            case HUB + 405:
                return input == catta::json::Token::character('s') ? jump(HUB + 406) : error();
            case HUB + 406:
                return input == catta::json::Token::character('S')  ? jump(HUB + 407)
                       : input == catta::json::Token::closeString() ? close(19)
                                                                    : error();
            case HUB + 407:
                return input == catta::json::Token::character('c') ? jump(HUB + 408) : error();
            case HUB + 408:
                return input == catta::json::Token::character('a') ? jump(HUB + 409) : error();
            case HUB + 409:
                return input == catta::json::Token::character('l') ? jump(HUB + 410) : error();
            case HUB + 410:
                return input == catta::json::Token::character('e') ? jump(HUB + 411) : error();
            case HUB + 411:
                return input == catta::json::Token::character('F') ? jump(HUB + 412) : error();
            case HUB + 412:
                return input == catta::json::Token::character('a') ? jump(HUB + 413) : error();
            case HUB + 413:
                return input == catta::json::Token::character('c') ? jump(HUB + 414) : error();
            case HUB + 414:
                return input == catta::json::Token::character('t') ? jump(HUB + 415) : error();
            case HUB + 415:
                return input == catta::json::Token::character('o') ? jump(HUB + 416) : error();
            case HUB + 416:
                return input == catta::json::Token::character('r') ? jump(HUB + 417) : error();
            case HUB + 417:
                return input == catta::json::Token::closeString() ? close(20) : error();
            case HUB + 418:
                return input == catta::json::Token::character('c') ? jump(HUB + 419) : error();
            case HUB + 419:
                return input == catta::json::Token::character('a') ? jump(HUB + 420) : error();
            case HUB + 420:
                return input == catta::json::Token::character('l') ? jump(HUB + 421) : error();
            case HUB + 421:
                return input == catta::json::Token::character('e') ? jump(HUB + 422) : error();
            case HUB + 422:
                return input == catta::json::Token::character('F') ? jump(HUB + 423) : error();
            case HUB + 423:
                return input == catta::json::Token::character('a') ? jump(HUB + 424) : error();
            case HUB + 424:
                return input == catta::json::Token::character('c') ? jump(HUB + 425) : error();
            case HUB + 425:
                return input == catta::json::Token::character('t') ? jump(HUB + 426) : error();
            case HUB + 426:
                return input == catta::json::Token::character('o') ? jump(HUB + 427) : error();
            case HUB + 427:
                return input == catta::json::Token::character('r') ? jump(HUB + 428) : error();
            case HUB + 428:
                return input == catta::json::Token::closeString() ? close(14) : error();
            case HUB + 429:
                return input == catta::json::Token::character('a') ? jump(HUB + 430) : error();
            case HUB + 430:
                return input == catta::json::Token::character('m') ? jump(HUB + 431) : error();
            case HUB + 431:
                return input == catta::json::Token::character('e') ? jump(HUB + 432) : error();
            case HUB + 432:
                return input == catta::json::Token::character('p') ? jump(HUB + 433) : error();
            case HUB + 433:
                return input == catta::json::Token::character('l') ? jump(HUB + 434) : error();
            case HUB + 434:
                return input == catta::json::Token::character('a') ? jump(HUB + 435) : error();
            case HUB + 435:
                return input == catta::json::Token::character('t') ? jump(HUB + 436) : error();
            case HUB + 436:
                return input == catta::json::Token::character('e') ? jump(HUB + 437) : error();
            case HUB + 437:
                return input == catta::json::Token::character('D') ? jump(HUB + 438) : error();
            case HUB + 438:
                return input == catta::json::Token::character('e') ? jump(HUB + 439) : error();
            case HUB + 439:
                return input == catta::json::Token::character('r') ? jump(HUB + 440) : error();
            case HUB + 440:
                return input == catta::json::Token::character('T') ? jump(HUB + 441) : error();
            case HUB + 441:
                return input == catta::json::Token::character('y') ? jump(HUB + 442) : error();
            case HUB + 442:
                return input == catta::json::Token::character('p') ? jump(HUB + 443) : error();
            case HUB + 443:
                return input == catta::json::Token::character('e') ? jump(HUB + 444) : error();
            case HUB + 444:
                return input == catta::json::Token::closeString() ? close(28) : error();
            case HUB + 445:
                return input == catta::json::Token::character('t')   ? jump(HUB + 485)
                       : input == catta::json::Token::character('i') ? jump(HUB + 446)
                                                                     : error();
            case HUB + 446:
                return input == catta::json::Token::character('C') ? jump(HUB + 447) : error();
            case HUB + 447:
                return input == catta::json::Token::character('o') ? jump(HUB + 448) : error();
            case HUB + 448:
                return input == catta::json::Token::character('n') ? jump(HUB + 449) : error();
            case HUB + 449:
                return input == catta::json::Token::character('t') ? jump(HUB + 450) : error();
            case HUB + 450:
                return input == catta::json::Token::character('r') ? jump(HUB + 451) : error();
            case HUB + 451:
                return input == catta::json::Token::character('o') ? jump(HUB + 452) : error();
            case HUB + 452:
                return input == catta::json::Token::character('l') ? jump(HUB + 453) : error();
            case HUB + 453:
                return input == catta::json::Token::character('U')   ? jump(HUB + 468)
                       : input == catta::json::Token::character('P') ? jump(HUB + 454)
                                                                     : error();
            case HUB + 454:
                return input == catta::json::Token::character('c')   ? jump(HUB + 463)
                       : input == catta::json::Token::character('S') ? jump(HUB + 455)
                                                                     : error();
            case HUB + 455:
                return input == catta::json::Token::character('e') ? jump(HUB + 456) : error();
            case HUB + 456:
                return input == catta::json::Token::character('t') ? jump(HUB + 457) : error();
            case HUB + 457:
                return input == catta::json::Token::character('P') ? jump(HUB + 458) : error();
            case HUB + 458:
                return input == catta::json::Token::character('o') ? jump(HUB + 459) : error();
            case HUB + 459:
                return input == catta::json::Token::character('i') ? jump(HUB + 460) : error();
            case HUB + 460:
                return input == catta::json::Token::character('n') ? jump(HUB + 461) : error();
            case HUB + 461:
                return input == catta::json::Token::character('t') ? jump(HUB + 462) : error();
            case HUB + 462:
                return input == catta::json::Token::closeString() ? close(47) : error();
            case HUB + 463:
                return input == catta::json::Token::character('d') ? jump(HUB + 464) : error();
            case HUB + 464:
                return input == catta::json::Token::character('D') ? jump(HUB + 465) : error();
            case HUB + 465:
                return input == catta::json::Token::character('i') ? jump(HUB + 466) : error();
            case HUB + 466:
                return input == catta::json::Token::character('v') ? jump(HUB + 467) : error();
            case HUB + 467:
                return input == catta::json::Token::closeString() ? close(45) : error();
            case HUB + 468:
                return input == catta::json::Token::character('d')   ? jump(HUB + 480)
                       : input == catta::json::Token::character('M') ? jump(HUB + 469)
                                                                     : error();
            case HUB + 469:
                return input == catta::json::Token::character('i')   ? jump(HUB + 475)
                       : input == catta::json::Token::character('a') ? jump(HUB + 470)
                                                                     : error();
            case HUB + 470:
                return input == catta::json::Token::character('x') ? jump(HUB + 471) : error();
            case HUB + 471:
                return input == catta::json::Token::character('E') ? jump(HUB + 472) : error();
            case HUB + 472:
                return input == catta::json::Token::character('x') ? jump(HUB + 473) : error();
            case HUB + 473:
                return input == catta::json::Token::character('t') ? jump(HUB + 474) : error();
            case HUB + 474:
                return input == catta::json::Token::closeString() ? close(49) : error();
            case HUB + 475:
                return input == catta::json::Token::character('n') ? jump(HUB + 476) : error();
            case HUB + 476:
                return input == catta::json::Token::character('E') ? jump(HUB + 477) : error();
            case HUB + 477:
                return input == catta::json::Token::character('x') ? jump(HUB + 478) : error();
            case HUB + 478:
                return input == catta::json::Token::character('t') ? jump(HUB + 479) : error();
            case HUB + 479:
                return input == catta::json::Token::closeString() ? close(48) : error();
            case HUB + 480:
                return input == catta::json::Token::character('c') ? jump(HUB + 481) : error();
            case HUB + 481:
                return input == catta::json::Token::character('E') ? jump(HUB + 482) : error();
            case HUB + 482:
                return input == catta::json::Token::character('x') ? jump(HUB + 483) : error();
            case HUB + 483:
                return input == catta::json::Token::character('t') ? jump(HUB + 484) : error();
            case HUB + 484:
                return input == catta::json::Token::closeString() ? close(46) : error();
            case HUB + 485:
                return input == catta::json::Token::character('o') ? jump(HUB + 486) : error();
            case HUB + 486:
                return input == catta::json::Token::character('r') ? jump(HUB + 487) : error();
            case HUB + 487:
                return input == catta::json::Token::character('a') ? jump(HUB + 488) : error();
            case HUB + 488:
                return input == catta::json::Token::character('g') ? jump(HUB + 489) : error();
            case HUB + 489:
                return input == catta::json::Token::character('e') ? jump(HUB + 490) : error();
            case HUB + 490:
                return input == catta::json::Token::character('W') ? jump(HUB + 491) : error();
            case HUB + 491:
                return input == catta::json::Token::character('C') ? jump(HUB + 492) : error();
            case HUB + 492:
                return input == catta::json::Token::character('h') ? jump(HUB + 493) : error();
            case HUB + 493:
                return input == catta::json::Token::character('a') ? jump(HUB + 494) : error();
            case HUB + 494:
                return input == catta::json::Token::character('R')   ? jump(HUB + 498)
                       : input == catta::json::Token::character('M') ? jump(HUB + 495)
                                                                     : error();
            case HUB + 495:
                return input == catta::json::Token::character('a') ? jump(HUB + 496) : error();
            case HUB + 496:
                return input == catta::json::Token::character('x') ? jump(HUB + 497) : error();
            case HUB + 497:
                return input == catta::json::Token::closeString() ? close(43) : error();
            case HUB + 498:
                return input == catta::json::Token::character('a') ? jump(HUB + 499) : error();
            case HUB + 499:
                return input == catta::json::Token::character('t') ? jump(HUB + 500) : error();
            case HUB + 500:
                return input == catta::json::Token::character('e') ? jump(HUB + 501) : error();
            case HUB + 501:
                return input == catta::json::Token::closeString() ? close(44) : error();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE + 0 ? Output(_data) : Output(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint16_t _state;
    std::uint8_t _data;
    static constexpr std::uint16_t START = 0;
    static constexpr std::uint16_t HUB = START + 1;
    static constexpr std::uint16_t TAIL = HUB + 502;
    static constexpr std::uint16_t DONE = TAIL + 1;
    static constexpr std::uint16_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
