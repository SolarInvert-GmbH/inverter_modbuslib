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
            _state = ERROR_STATE;
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
                return input == catta::json::Token::nullObject()   ? jump(TAIL + 0)
                       : input == catta::json::Token::openString() ? jump(HUB + 0)
                                                                   : error();
            case HUB + 0:
                return input == catta::json::Token::character('N')   ? jump(HUB + 427)
                       : input == catta::json::Token::character('M') ? jump(HUB + 387)
                       : input == catta::json::Token::character('I') ? jump(HUB + 99)
                       : input == catta::json::Token::character('E') ? jump(HUB + 55)
                       : input == catta::json::Token::character('C') ? jump(HUB + 1)
                                                                     : error();
            case HUB + 1:
                return input == catta::json::Token::character('o') ? jump(HUB + 2) : error();
            case HUB + 2:
                return input == catta::json::Token::character('m') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('m') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('o') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('n') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('V')   ? jump(HUB + 48)
                       : input == catta::json::Token::character('S') ? jump(HUB + 36)
                       : input == catta::json::Token::character('M') ? jump(HUB + 20)
                       : input == catta::json::Token::character('D') ? jump(HUB + 7)
                                                                     : error();
            case HUB + 7:
                return input == catta::json::Token::character('e') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('v') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('i') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('c') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('e') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('A') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('d') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('d') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('r') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('e') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('s') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('s') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::closeString() ? close(4) : error();
            case HUB + 20:
                return input == catta::json::Token::character('o')   ? jump(HUB + 32)
                       : input == catta::json::Token::character('a') ? jump(HUB + 21)
                                                                     : error();
            case HUB + 21:
                return input == catta::json::Token::character('n') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('u') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('f') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('a') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('c') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('t') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('u') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::character('r') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('e') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('r') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::closeString() ? close(0) : error();
            case HUB + 32:
                return input == catta::json::Token::character('d') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('e') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('l') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::closeString() ? close(1) : error();
            case HUB + 36:
                return input == catta::json::Token::character('e') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('r') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('i') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('a') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('l') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('N') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('u') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('m') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('b') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('e') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('r') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::closeString() ? close(3) : error();
            case HUB + 48:
                return input == catta::json::Token::character('e') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('r') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('s') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('i') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::character('o') ? jump(HUB + 53) : error();
            case HUB + 53:
                return input == catta::json::Token::character('n') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::closeString() ? close(2) : error();
            case HUB + 55:
                return input == catta::json::Token::character('x') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('t') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('e') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('n') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('d') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('e') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('d') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('M') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('e') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('s') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('u') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('r') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('e') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::character('m') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('e') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('n') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('t') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('s') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('A') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::character('c') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('W')   ? jump(HUB + 90)
                       : input == catta::json::Token::character('L') ? jump(HUB + 76)
                                                                     : error();
            case HUB + 76:
                return input == catta::json::Token::character('i') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('f') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('e') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('t') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('i') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('m') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('e') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('C') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('h') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('a') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('r') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('g') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('e') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::closeString() ? close(40) : error();
            case HUB + 90:
                return input == catta::json::Token::character('a') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('t') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('t') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('H') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('o') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::character('u') ? jump(HUB + 96) : error();
            case HUB + 96:
                return input == catta::json::Token::character('r') ? jump(HUB + 97) : error();
            case HUB + 97:
                return input == catta::json::Token::character('s') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::closeString() ? close(39) : error();
            case HUB + 99:
                return input == catta::json::Token::character('n') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('v') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('e') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('r') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('t') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('e') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('r') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('W')   ? jump(HUB + 367)
                       : input == catta::json::Token::character('V') ? jump(HUB + 330)
                       : input == catta::json::Token::character('T') ? jump(HUB + 308)
                       : input == catta::json::Token::character('P') ? jump(HUB + 261)
                       : input == catta::json::Token::character('O') ? jump(HUB + 247)
                       : input == catta::json::Token::character('H') ? jump(HUB + 231)
                       : input == catta::json::Token::character('D') ? jump(HUB + 195)
                       : input == catta::json::Token::character('A') ? jump(HUB + 107)
                                                                     : error();
            case HUB + 107:
                return input == catta::json::Token::character('m')   ? jump(HUB + 173)
                       : input == catta::json::Token::character('c') ? jump(HUB + 108)
                                                                     : error();
            case HUB + 108:
                return input == catta::json::Token::character('R')   ? jump(HUB + 149)
                       : input == catta::json::Token::character('P') ? jump(HUB + 133)
                       : input == catta::json::Token::character('A') ? jump(HUB + 109)
                                                                     : error();
            case HUB + 109:
                return input == catta::json::Token::character('p') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('p') ? jump(HUB + 111) : error();
            case HUB + 111:
                return input == catta::json::Token::character('a') ? jump(HUB + 112) : error();
            case HUB + 112:
                return input == catta::json::Token::character('r') ? jump(HUB + 113) : error();
            case HUB + 113:
                return input == catta::json::Token::character('e') ? jump(HUB + 114) : error();
            case HUB + 114:
                return input == catta::json::Token::character('n') ? jump(HUB + 115) : error();
            case HUB + 115:
                return input == catta::json::Token::character('t') ? jump(HUB + 116) : error();
            case HUB + 116:
                return input == catta::json::Token::character('P') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('o') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('w') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::character('e') ? jump(HUB + 120) : error();
            case HUB + 120:
                return input == catta::json::Token::character('r') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('S')  ? jump(HUB + 122)
                       : input == catta::json::Token::closeString() ? close(18)
                                                                    : error();
            case HUB + 122:
                return input == catta::json::Token::character('c') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::character('a') ? jump(HUB + 124) : error();
            case HUB + 124:
                return input == catta::json::Token::character('l') ? jump(HUB + 125) : error();
            case HUB + 125:
                return input == catta::json::Token::character('e') ? jump(HUB + 126) : error();
            case HUB + 126:
                return input == catta::json::Token::character('F') ? jump(HUB + 127) : error();
            case HUB + 127:
                return input == catta::json::Token::character('a') ? jump(HUB + 128) : error();
            case HUB + 128:
                return input == catta::json::Token::character('c') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('t') ? jump(HUB + 130) : error();
            case HUB + 130:
                return input == catta::json::Token::character('o') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('r') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::closeString() ? close(19) : error();
            case HUB + 133:
                return input == catta::json::Token::character('o') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('w') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('e') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::character('r') ? jump(HUB + 137) : error();
            case HUB + 137:
                return input == catta::json::Token::character('S')  ? jump(HUB + 138)
                       : input == catta::json::Token::closeString() ? close(14)
                                                                    : error();
            case HUB + 138:
                return input == catta::json::Token::character('c') ? jump(HUB + 139) : error();
            case HUB + 139:
                return input == catta::json::Token::character('a') ? jump(HUB + 140) : error();
            case HUB + 140:
                return input == catta::json::Token::character('l') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('e') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::character('F') ? jump(HUB + 143) : error();
            case HUB + 143:
                return input == catta::json::Token::character('a') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('c') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::character('t') ? jump(HUB + 146) : error();
            case HUB + 146:
                return input == catta::json::Token::character('o') ? jump(HUB + 147) : error();
            case HUB + 147:
                return input == catta::json::Token::character('r') ? jump(HUB + 148) : error();
            case HUB + 148:
                return input == catta::json::Token::closeString() ? close(15) : error();
            case HUB + 149:
                return input == catta::json::Token::character('e') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('a') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('c') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('t') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::character('i') ? jump(HUB + 154) : error();
            case HUB + 154:
                return input == catta::json::Token::character('v') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('e') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::character('P') ? jump(HUB + 157) : error();
            case HUB + 157:
                return input == catta::json::Token::character('o') ? jump(HUB + 158) : error();
            case HUB + 158:
                return input == catta::json::Token::character('w') ? jump(HUB + 159) : error();
            case HUB + 159:
                return input == catta::json::Token::character('e') ? jump(HUB + 160) : error();
            case HUB + 160:
                return input == catta::json::Token::character('r') ? jump(HUB + 161) : error();
            case HUB + 161:
                return input == catta::json::Token::character('S')  ? jump(HUB + 162)
                       : input == catta::json::Token::closeString() ? close(20)
                                                                    : error();
            case HUB + 162:
                return input == catta::json::Token::character('c') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('a') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('l') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('e') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('F') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('a') ? jump(HUB + 168) : error();
            case HUB + 168:
                return input == catta::json::Token::character('c') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::character('t') ? jump(HUB + 170) : error();
            case HUB + 170:
                return input == catta::json::Token::character('o') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::character('r') ? jump(HUB + 172) : error();
            case HUB + 172:
                return input == catta::json::Token::closeString() ? close(21) : error();
            case HUB + 173:
                return input == catta::json::Token::character('p') ? jump(HUB + 174) : error();
            case HUB + 174:
                return input == catta::json::Token::character('s') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('S')   ? jump(HUB + 184)
                       : input == catta::json::Token::character('P') ? jump(HUB + 176)
                       : input == catta::json::Token::closeString()  ? close(5)
                                                                     : error();
            case HUB + 176:
                return input == catta::json::Token::character('h') ? jump(HUB + 177) : error();
            case HUB + 177:
                return input == catta::json::Token::character('a') ? jump(HUB + 178) : error();
            case HUB + 178:
                return input == catta::json::Token::character('s') ? jump(HUB + 179) : error();
            case HUB + 179:
                return input == catta::json::Token::character('e') ? jump(HUB + 180) : error();
            case HUB + 180:
                return input == catta::json::Token::character('C')   ? jump(HUB + 183)
                       : input == catta::json::Token::character('B') ? jump(HUB + 182)
                       : input == catta::json::Token::character('A') ? jump(HUB + 181)
                                                                     : error();
            case HUB + 181:
                return input == catta::json::Token::closeString() ? close(6) : error();
            case HUB + 182:
                return input == catta::json::Token::closeString() ? close(7) : error();
            case HUB + 183:
                return input == catta::json::Token::closeString() ? close(8) : error();
            case HUB + 184:
                return input == catta::json::Token::character('c') ? jump(HUB + 185) : error();
            case HUB + 185:
                return input == catta::json::Token::character('a') ? jump(HUB + 186) : error();
            case HUB + 186:
                return input == catta::json::Token::character('l') ? jump(HUB + 187) : error();
            case HUB + 187:
                return input == catta::json::Token::character('e') ? jump(HUB + 188) : error();
            case HUB + 188:
                return input == catta::json::Token::character('F') ? jump(HUB + 189) : error();
            case HUB + 189:
                return input == catta::json::Token::character('a') ? jump(HUB + 190) : error();
            case HUB + 190:
                return input == catta::json::Token::character('c') ? jump(HUB + 191) : error();
            case HUB + 191:
                return input == catta::json::Token::character('t') ? jump(HUB + 192) : error();
            case HUB + 192:
                return input == catta::json::Token::character('o') ? jump(HUB + 193) : error();
            case HUB + 193:
                return input == catta::json::Token::character('r') ? jump(HUB + 194) : error();
            case HUB + 194:
                return input == catta::json::Token::closeString() ? close(9) : error();
            case HUB + 195:
                return input == catta::json::Token::character('c') ? jump(HUB + 196) : error();
            case HUB + 196:
                return input == catta::json::Token::character('V')   ? jump(HUB + 213)
                       : input == catta::json::Token::character('P') ? jump(HUB + 197)
                                                                     : error();
            case HUB + 197:
                return input == catta::json::Token::character('o') ? jump(HUB + 198) : error();
            case HUB + 198:
                return input == catta::json::Token::character('w') ? jump(HUB + 199) : error();
            case HUB + 199:
                return input == catta::json::Token::character('e') ? jump(HUB + 200) : error();
            case HUB + 200:
                return input == catta::json::Token::character('r') ? jump(HUB + 201) : error();
            case HUB + 201:
                return input == catta::json::Token::character('S')  ? jump(HUB + 202)
                       : input == catta::json::Token::closeString() ? close(28)
                                                                    : error();
            case HUB + 202:
                return input == catta::json::Token::character('c') ? jump(HUB + 203) : error();
            case HUB + 203:
                return input == catta::json::Token::character('a') ? jump(HUB + 204) : error();
            case HUB + 204:
                return input == catta::json::Token::character('l') ? jump(HUB + 205) : error();
            case HUB + 205:
                return input == catta::json::Token::character('e') ? jump(HUB + 206) : error();
            case HUB + 206:
                return input == catta::json::Token::character('F') ? jump(HUB + 207) : error();
            case HUB + 207:
                return input == catta::json::Token::character('a') ? jump(HUB + 208) : error();
            case HUB + 208:
                return input == catta::json::Token::character('c') ? jump(HUB + 209) : error();
            case HUB + 209:
                return input == catta::json::Token::character('t') ? jump(HUB + 210) : error();
            case HUB + 210:
                return input == catta::json::Token::character('o') ? jump(HUB + 211) : error();
            case HUB + 211:
                return input == catta::json::Token::character('r') ? jump(HUB + 212) : error();
            case HUB + 212:
                return input == catta::json::Token::closeString() ? close(29) : error();
            case HUB + 213:
                return input == catta::json::Token::character('o') ? jump(HUB + 214) : error();
            case HUB + 214:
                return input == catta::json::Token::character('l') ? jump(HUB + 215) : error();
            case HUB + 215:
                return input == catta::json::Token::character('t') ? jump(HUB + 216) : error();
            case HUB + 216:
                return input == catta::json::Token::character('a') ? jump(HUB + 217) : error();
            case HUB + 217:
                return input == catta::json::Token::character('g') ? jump(HUB + 218) : error();
            case HUB + 218:
                return input == catta::json::Token::character('e') ? jump(HUB + 219) : error();
            case HUB + 219:
                return input == catta::json::Token::character('S')  ? jump(HUB + 220)
                       : input == catta::json::Token::closeString() ? close(26)
                                                                    : error();
            case HUB + 220:
                return input == catta::json::Token::character('c') ? jump(HUB + 221) : error();
            case HUB + 221:
                return input == catta::json::Token::character('a') ? jump(HUB + 222) : error();
            case HUB + 222:
                return input == catta::json::Token::character('l') ? jump(HUB + 223) : error();
            case HUB + 223:
                return input == catta::json::Token::character('e') ? jump(HUB + 224) : error();
            case HUB + 224:
                return input == catta::json::Token::character('F') ? jump(HUB + 225) : error();
            case HUB + 225:
                return input == catta::json::Token::character('a') ? jump(HUB + 226) : error();
            case HUB + 226:
                return input == catta::json::Token::character('c') ? jump(HUB + 227) : error();
            case HUB + 227:
                return input == catta::json::Token::character('t') ? jump(HUB + 228) : error();
            case HUB + 228:
                return input == catta::json::Token::character('o') ? jump(HUB + 229) : error();
            case HUB + 229:
                return input == catta::json::Token::character('r') ? jump(HUB + 230) : error();
            case HUB + 230:
                return input == catta::json::Token::closeString() ? close(27) : error();
            case HUB + 231:
                return input == catta::json::Token::character('e') ? jump(HUB + 232) : error();
            case HUB + 232:
                return input == catta::json::Token::character('r') ? jump(HUB + 233) : error();
            case HUB + 233:
                return input == catta::json::Token::character('t') ? jump(HUB + 234) : error();
            case HUB + 234:
                return input == catta::json::Token::character('z') ? jump(HUB + 235) : error();
            case HUB + 235:
                return input == catta::json::Token::character('S')  ? jump(HUB + 236)
                       : input == catta::json::Token::closeString() ? close(16)
                                                                    : error();
            case HUB + 236:
                return input == catta::json::Token::character('c') ? jump(HUB + 237) : error();
            case HUB + 237:
                return input == catta::json::Token::character('a') ? jump(HUB + 238) : error();
            case HUB + 238:
                return input == catta::json::Token::character('l') ? jump(HUB + 239) : error();
            case HUB + 239:
                return input == catta::json::Token::character('e') ? jump(HUB + 240) : error();
            case HUB + 240:
                return input == catta::json::Token::character('F') ? jump(HUB + 241) : error();
            case HUB + 241:
                return input == catta::json::Token::character('a') ? jump(HUB + 242) : error();
            case HUB + 242:
                return input == catta::json::Token::character('c') ? jump(HUB + 243) : error();
            case HUB + 243:
                return input == catta::json::Token::character('t') ? jump(HUB + 244) : error();
            case HUB + 244:
                return input == catta::json::Token::character('o') ? jump(HUB + 245) : error();
            case HUB + 245:
                return input == catta::json::Token::character('r') ? jump(HUB + 246) : error();
            case HUB + 246:
                return input == catta::json::Token::closeString() ? close(17) : error();
            case HUB + 247:
                return input == catta::json::Token::character('p') ? jump(HUB + 248) : error();
            case HUB + 248:
                return input == catta::json::Token::character('e') ? jump(HUB + 249) : error();
            case HUB + 249:
                return input == catta::json::Token::character('r') ? jump(HUB + 250) : error();
            case HUB + 250:
                return input == catta::json::Token::character('a') ? jump(HUB + 251) : error();
            case HUB + 251:
                return input == catta::json::Token::character('t') ? jump(HUB + 252) : error();
            case HUB + 252:
                return input == catta::json::Token::character('i') ? jump(HUB + 253) : error();
            case HUB + 253:
                return input == catta::json::Token::character('n') ? jump(HUB + 254) : error();
            case HUB + 254:
                return input == catta::json::Token::character('g') ? jump(HUB + 255) : error();
            case HUB + 255:
                return input == catta::json::Token::character('S') ? jump(HUB + 256) : error();
            case HUB + 256:
                return input == catta::json::Token::character('t') ? jump(HUB + 257) : error();
            case HUB + 257:
                return input == catta::json::Token::character('a') ? jump(HUB + 258) : error();
            case HUB + 258:
                return input == catta::json::Token::character('t') ? jump(HUB + 259) : error();
            case HUB + 259:
                return input == catta::json::Token::character('e') ? jump(HUB + 260) : error();
            case HUB + 260:
                return input == catta::json::Token::closeString() ? close(32) : error();
            case HUB + 261:
                return input == catta::json::Token::character('o')   ? jump(HUB + 287)
                       : input == catta::json::Token::character('h') ? jump(HUB + 262)
                                                                     : error();
            case HUB + 262:
                return input == catta::json::Token::character('a') ? jump(HUB + 263) : error();
            case HUB + 263:
                return input == catta::json::Token::character('s') ? jump(HUB + 264) : error();
            case HUB + 264:
                return input == catta::json::Token::character('e') ? jump(HUB + 265) : error();
            case HUB + 265:
                return input == catta::json::Token::character('V') ? jump(HUB + 266) : error();
            case HUB + 266:
                return input == catta::json::Token::character('o') ? jump(HUB + 267) : error();
            case HUB + 267:
                return input == catta::json::Token::character('l') ? jump(HUB + 268) : error();
            case HUB + 268:
                return input == catta::json::Token::character('t') ? jump(HUB + 269) : error();
            case HUB + 269:
                return input == catta::json::Token::character('a') ? jump(HUB + 270) : error();
            case HUB + 270:
                return input == catta::json::Token::character('g') ? jump(HUB + 271) : error();
            case HUB + 271:
                return input == catta::json::Token::character('e') ? jump(HUB + 272) : error();
            case HUB + 272:
                return input == catta::json::Token::character('S')   ? jump(HUB + 276)
                       : input == catta::json::Token::character('C') ? jump(HUB + 275)
                       : input == catta::json::Token::character('B') ? jump(HUB + 274)
                       : input == catta::json::Token::character('A') ? jump(HUB + 273)
                                                                     : error();
            case HUB + 273:
                return input == catta::json::Token::closeString() ? close(10) : error();
            case HUB + 274:
                return input == catta::json::Token::closeString() ? close(11) : error();
            case HUB + 275:
                return input == catta::json::Token::closeString() ? close(12) : error();
            case HUB + 276:
                return input == catta::json::Token::character('c') ? jump(HUB + 277) : error();
            case HUB + 277:
                return input == catta::json::Token::character('a') ? jump(HUB + 278) : error();
            case HUB + 278:
                return input == catta::json::Token::character('l') ? jump(HUB + 279) : error();
            case HUB + 279:
                return input == catta::json::Token::character('e') ? jump(HUB + 280) : error();
            case HUB + 280:
                return input == catta::json::Token::character('F') ? jump(HUB + 281) : error();
            case HUB + 281:
                return input == catta::json::Token::character('a') ? jump(HUB + 282) : error();
            case HUB + 282:
                return input == catta::json::Token::character('c') ? jump(HUB + 283) : error();
            case HUB + 283:
                return input == catta::json::Token::character('t') ? jump(HUB + 284) : error();
            case HUB + 284:
                return input == catta::json::Token::character('o') ? jump(HUB + 285) : error();
            case HUB + 285:
                return input == catta::json::Token::character('r') ? jump(HUB + 286) : error();
            case HUB + 286:
                return input == catta::json::Token::closeString() ? close(13) : error();
            case HUB + 287:
                return input == catta::json::Token::character('w') ? jump(HUB + 288) : error();
            case HUB + 288:
                return input == catta::json::Token::character('e') ? jump(HUB + 289) : error();
            case HUB + 289:
                return input == catta::json::Token::character('r') ? jump(HUB + 290) : error();
            case HUB + 290:
                return input == catta::json::Token::character('F') ? jump(HUB + 291) : error();
            case HUB + 291:
                return input == catta::json::Token::character('a') ? jump(HUB + 292) : error();
            case HUB + 292:
                return input == catta::json::Token::character('c') ? jump(HUB + 293) : error();
            case HUB + 293:
                return input == catta::json::Token::character('t') ? jump(HUB + 294) : error();
            case HUB + 294:
                return input == catta::json::Token::character('o') ? jump(HUB + 295) : error();
            case HUB + 295:
                return input == catta::json::Token::character('r') ? jump(HUB + 296) : error();
            case HUB + 296:
                return input == catta::json::Token::character('S')  ? jump(HUB + 297)
                       : input == catta::json::Token::closeString() ? close(22)
                                                                    : error();
            case HUB + 297:
                return input == catta::json::Token::character('c') ? jump(HUB + 298) : error();
            case HUB + 298:
                return input == catta::json::Token::character('a') ? jump(HUB + 299) : error();
            case HUB + 299:
                return input == catta::json::Token::character('l') ? jump(HUB + 300) : error();
            case HUB + 300:
                return input == catta::json::Token::character('e') ? jump(HUB + 301) : error();
            case HUB + 301:
                return input == catta::json::Token::character('F') ? jump(HUB + 302) : error();
            case HUB + 302:
                return input == catta::json::Token::character('a') ? jump(HUB + 303) : error();
            case HUB + 303:
                return input == catta::json::Token::character('c') ? jump(HUB + 304) : error();
            case HUB + 304:
                return input == catta::json::Token::character('t') ? jump(HUB + 305) : error();
            case HUB + 305:
                return input == catta::json::Token::character('o') ? jump(HUB + 306) : error();
            case HUB + 306:
                return input == catta::json::Token::character('r') ? jump(HUB + 307) : error();
            case HUB + 307:
                return input == catta::json::Token::closeString() ? close(23) : error();
            case HUB + 308:
                return input == catta::json::Token::character('e') ? jump(HUB + 309) : error();
            case HUB + 309:
                return input == catta::json::Token::character('m') ? jump(HUB + 310) : error();
            case HUB + 310:
                return input == catta::json::Token::character('p') ? jump(HUB + 311) : error();
            case HUB + 311:
                return input == catta::json::Token::character('e') ? jump(HUB + 312) : error();
            case HUB + 312:
                return input == catta::json::Token::character('r') ? jump(HUB + 313) : error();
            case HUB + 313:
                return input == catta::json::Token::character('a') ? jump(HUB + 314) : error();
            case HUB + 314:
                return input == catta::json::Token::character('t') ? jump(HUB + 315) : error();
            case HUB + 315:
                return input == catta::json::Token::character('u') ? jump(HUB + 316) : error();
            case HUB + 316:
                return input == catta::json::Token::character('r') ? jump(HUB + 317) : error();
            case HUB + 317:
                return input == catta::json::Token::character('e') ? jump(HUB + 318) : error();
            case HUB + 318:
                return input == catta::json::Token::character('S')  ? jump(HUB + 319)
                       : input == catta::json::Token::closeString() ? close(30)
                                                                    : error();
            case HUB + 319:
                return input == catta::json::Token::character('c') ? jump(HUB + 320) : error();
            case HUB + 320:
                return input == catta::json::Token::character('a') ? jump(HUB + 321) : error();
            case HUB + 321:
                return input == catta::json::Token::character('l') ? jump(HUB + 322) : error();
            case HUB + 322:
                return input == catta::json::Token::character('e') ? jump(HUB + 323) : error();
            case HUB + 323:
                return input == catta::json::Token::character('F') ? jump(HUB + 324) : error();
            case HUB + 324:
                return input == catta::json::Token::character('a') ? jump(HUB + 325) : error();
            case HUB + 325:
                return input == catta::json::Token::character('c') ? jump(HUB + 326) : error();
            case HUB + 326:
                return input == catta::json::Token::character('t') ? jump(HUB + 327) : error();
            case HUB + 327:
                return input == catta::json::Token::character('o') ? jump(HUB + 328) : error();
            case HUB + 328:
                return input == catta::json::Token::character('r') ? jump(HUB + 329) : error();
            case HUB + 329:
                return input == catta::json::Token::closeString() ? close(31) : error();
            case HUB + 330:
                return input == catta::json::Token::character('e') ? jump(HUB + 331) : error();
            case HUB + 331:
                return input == catta::json::Token::character('n') ? jump(HUB + 332) : error();
            case HUB + 332:
                return input == catta::json::Token::character('d') ? jump(HUB + 333) : error();
            case HUB + 333:
                return input == catta::json::Token::character('o') ? jump(HUB + 334) : error();
            case HUB + 334:
                return input == catta::json::Token::character('r') ? jump(HUB + 335) : error();
            case HUB + 335:
                return input == catta::json::Token::character('O')   ? jump(HUB + 353)
                       : input == catta::json::Token::character('E') ? jump(HUB + 336)
                                                                     : error();
            case HUB + 336:
                return input == catta::json::Token::character('v') ? jump(HUB + 337) : error();
            case HUB + 337:
                return input == catta::json::Token::character('e') ? jump(HUB + 338) : error();
            case HUB + 338:
                return input == catta::json::Token::character('n') ? jump(HUB + 339) : error();
            case HUB + 339:
                return input == catta::json::Token::character('t') ? jump(HUB + 340) : error();
            case HUB + 340:
                return input == catta::json::Token::character('B') ? jump(HUB + 341) : error();
            case HUB + 341:
                return input == catta::json::Token::character('i') ? jump(HUB + 342) : error();
            case HUB + 342:
                return input == catta::json::Token::character('t') ? jump(HUB + 343) : error();
            case HUB + 343:
                return input == catta::json::Token::character('f') ? jump(HUB + 344) : error();
            case HUB + 344:
                return input == catta::json::Token::character('i') ? jump(HUB + 345) : error();
            case HUB + 345:
                return input == catta::json::Token::character('e') ? jump(HUB + 346) : error();
            case HUB + 346:
                return input == catta::json::Token::character('l') ? jump(HUB + 347) : error();
            case HUB + 347:
                return input == catta::json::Token::character('d') ? jump(HUB + 348) : error();
            case HUB + 348:
                return input == catta::json::Token::character('4')   ? jump(HUB + 352)
                       : input == catta::json::Token::character('3') ? jump(HUB + 351)
                       : input == catta::json::Token::character('2') ? jump(HUB + 350)
                       : input == catta::json::Token::character('1') ? jump(HUB + 349)
                                                                     : error();
            case HUB + 349:
                return input == catta::json::Token::closeString() ? close(34) : error();
            case HUB + 350:
                return input == catta::json::Token::closeString() ? close(35) : error();
            case HUB + 351:
                return input == catta::json::Token::closeString() ? close(36) : error();
            case HUB + 352:
                return input == catta::json::Token::closeString() ? close(37) : error();
            case HUB + 353:
                return input == catta::json::Token::character('p') ? jump(HUB + 354) : error();
            case HUB + 354:
                return input == catta::json::Token::character('e') ? jump(HUB + 355) : error();
            case HUB + 355:
                return input == catta::json::Token::character('r') ? jump(HUB + 356) : error();
            case HUB + 356:
                return input == catta::json::Token::character('a') ? jump(HUB + 357) : error();
            case HUB + 357:
                return input == catta::json::Token::character('t') ? jump(HUB + 358) : error();
            case HUB + 358:
                return input == catta::json::Token::character('i') ? jump(HUB + 359) : error();
            case HUB + 359:
                return input == catta::json::Token::character('n') ? jump(HUB + 360) : error();
            case HUB + 360:
                return input == catta::json::Token::character('g') ? jump(HUB + 361) : error();
            case HUB + 361:
                return input == catta::json::Token::character('S') ? jump(HUB + 362) : error();
            case HUB + 362:
                return input == catta::json::Token::character('t') ? jump(HUB + 363) : error();
            case HUB + 363:
                return input == catta::json::Token::character('a') ? jump(HUB + 364) : error();
            case HUB + 364:
                return input == catta::json::Token::character('t') ? jump(HUB + 365) : error();
            case HUB + 365:
                return input == catta::json::Token::character('e') ? jump(HUB + 366) : error();
            case HUB + 366:
                return input == catta::json::Token::closeString() ? close(33) : error();
            case HUB + 367:
                return input == catta::json::Token::character('a') ? jump(HUB + 368) : error();
            case HUB + 368:
                return input == catta::json::Token::character('t') ? jump(HUB + 369) : error();
            case HUB + 369:
                return input == catta::json::Token::character('t') ? jump(HUB + 370) : error();
            case HUB + 370:
                return input == catta::json::Token::character('H') ? jump(HUB + 371) : error();
            case HUB + 371:
                return input == catta::json::Token::character('o') ? jump(HUB + 372) : error();
            case HUB + 372:
                return input == catta::json::Token::character('u') ? jump(HUB + 373) : error();
            case HUB + 373:
                return input == catta::json::Token::character('r') ? jump(HUB + 374) : error();
            case HUB + 374:
                return input == catta::json::Token::character('s') ? jump(HUB + 375) : error();
            case HUB + 375:
                return input == catta::json::Token::character('S')  ? jump(HUB + 376)
                       : input == catta::json::Token::closeString() ? close(24)
                                                                    : error();
            case HUB + 376:
                return input == catta::json::Token::character('c') ? jump(HUB + 377) : error();
            case HUB + 377:
                return input == catta::json::Token::character('a') ? jump(HUB + 378) : error();
            case HUB + 378:
                return input == catta::json::Token::character('l') ? jump(HUB + 379) : error();
            case HUB + 379:
                return input == catta::json::Token::character('e') ? jump(HUB + 380) : error();
            case HUB + 380:
                return input == catta::json::Token::character('F') ? jump(HUB + 381) : error();
            case HUB + 381:
                return input == catta::json::Token::character('a') ? jump(HUB + 382) : error();
            case HUB + 382:
                return input == catta::json::Token::character('c') ? jump(HUB + 383) : error();
            case HUB + 383:
                return input == catta::json::Token::character('t') ? jump(HUB + 384) : error();
            case HUB + 384:
                return input == catta::json::Token::character('o') ? jump(HUB + 385) : error();
            case HUB + 385:
                return input == catta::json::Token::character('r') ? jump(HUB + 386) : error();
            case HUB + 386:
                return input == catta::json::Token::closeString() ? close(25) : error();
            case HUB + 387:
                return input == catta::json::Token::character('p') ? jump(HUB + 388) : error();
            case HUB + 388:
                return input == catta::json::Token::character('p') ? jump(HUB + 389) : error();
            case HUB + 389:
                return input == catta::json::Token::character('S') ? jump(HUB + 390) : error();
            case HUB + 390:
                return input == catta::json::Token::character('t')   ? jump(HUB + 410)
                       : input == catta::json::Token::character('a') ? jump(HUB + 391)
                                                                     : error();
            case HUB + 391:
                return input == catta::json::Token::character('m') ? jump(HUB + 392) : error();
            case HUB + 392:
                return input == catta::json::Token::character('p') ? jump(HUB + 393) : error();
            case HUB + 393:
                return input == catta::json::Token::character('l') ? jump(HUB + 394) : error();
            case HUB + 394:
                return input == catta::json::Token::character('e') ? jump(HUB + 395) : error();
            case HUB + 395:
                return input == catta::json::Token::character('U')   ? jump(HUB + 403)
                       : input == catta::json::Token::character('D') ? jump(HUB + 396)
                                                                     : error();
            case HUB + 396:
                return input == catta::json::Token::character('a') ? jump(HUB + 397) : error();
            case HUB + 397:
                return input == catta::json::Token::character('c') ? jump(HUB + 398) : error();
            case HUB + 398:
                return input == catta::json::Token::character('3')   ? jump(HUB + 402)
                       : input == catta::json::Token::character('2') ? jump(HUB + 401)
                       : input == catta::json::Token::character('1') ? jump(HUB + 400)
                       : input == catta::json::Token::character('0') ? jump(HUB + 399)
                                                                     : error();
            case HUB + 399:
                return input == catta::json::Token::closeString() ? close(49) : error();
            case HUB + 400:
                return input == catta::json::Token::closeString() ? close(50) : error();
            case HUB + 401:
                return input == catta::json::Token::closeString() ? close(51) : error();
            case HUB + 402:
                return input == catta::json::Token::closeString() ? close(52) : error();
            case HUB + 403:
                return input == catta::json::Token::character('d') ? jump(HUB + 404) : error();
            case HUB + 404:
                return input == catta::json::Token::character('c') ? jump(HUB + 405) : error();
            case HUB + 405:
                return input == catta::json::Token::character('3')   ? jump(HUB + 409)
                       : input == catta::json::Token::character('2') ? jump(HUB + 408)
                       : input == catta::json::Token::character('1') ? jump(HUB + 407)
                       : input == catta::json::Token::character('0') ? jump(HUB + 406)
                                                                     : error();
            case HUB + 406:
                return input == catta::json::Token::closeString() ? close(53) : error();
            case HUB + 407:
                return input == catta::json::Token::closeString() ? close(54) : error();
            case HUB + 408:
                return input == catta::json::Token::closeString() ? close(55) : error();
            case HUB + 409:
                return input == catta::json::Token::closeString() ? close(56) : error();
            case HUB + 410:
                return input == catta::json::Token::character('e') ? jump(HUB + 411) : error();
            case HUB + 411:
                return input == catta::json::Token::character('p') ? jump(HUB + 412) : error();
            case HUB + 412:
                return input == catta::json::Token::character('U')   ? jump(HUB + 420)
                       : input == catta::json::Token::character('D') ? jump(HUB + 413)
                                                                     : error();
            case HUB + 413:
                return input == catta::json::Token::character('a') ? jump(HUB + 414) : error();
            case HUB + 414:
                return input == catta::json::Token::character('c') ? jump(HUB + 415) : error();
            case HUB + 415:
                return input == catta::json::Token::character('3')   ? jump(HUB + 419)
                       : input == catta::json::Token::character('2') ? jump(HUB + 418)
                       : input == catta::json::Token::character('1') ? jump(HUB + 417)
                       : input == catta::json::Token::character('0') ? jump(HUB + 416)
                                                                     : error();
            case HUB + 416:
                return input == catta::json::Token::closeString() ? close(41) : error();
            case HUB + 417:
                return input == catta::json::Token::closeString() ? close(42) : error();
            case HUB + 418:
                return input == catta::json::Token::closeString() ? close(43) : error();
            case HUB + 419:
                return input == catta::json::Token::closeString() ? close(44) : error();
            case HUB + 420:
                return input == catta::json::Token::character('d') ? jump(HUB + 421) : error();
            case HUB + 421:
                return input == catta::json::Token::character('c') ? jump(HUB + 422) : error();
            case HUB + 422:
                return input == catta::json::Token::character('3')   ? jump(HUB + 426)
                       : input == catta::json::Token::character('2') ? jump(HUB + 425)
                       : input == catta::json::Token::character('1') ? jump(HUB + 424)
                       : input == catta::json::Token::character('0') ? jump(HUB + 423)
                                                                     : error();
            case HUB + 423:
                return input == catta::json::Token::closeString() ? close(45) : error();
            case HUB + 424:
                return input == catta::json::Token::closeString() ? close(46) : error();
            case HUB + 425:
                return input == catta::json::Token::closeString() ? close(47) : error();
            case HUB + 426:
                return input == catta::json::Token::closeString() ? close(48) : error();
            case HUB + 427:
                return input == catta::json::Token::character('a') ? jump(HUB + 428) : error();
            case HUB + 428:
                return input == catta::json::Token::character('m') ? jump(HUB + 429) : error();
            case HUB + 429:
                return input == catta::json::Token::character('e') ? jump(HUB + 430) : error();
            case HUB + 430:
                return input == catta::json::Token::character('p') ? jump(HUB + 431) : error();
            case HUB + 431:
                return input == catta::json::Token::character('l') ? jump(HUB + 432) : error();
            case HUB + 432:
                return input == catta::json::Token::character('a') ? jump(HUB + 433) : error();
            case HUB + 433:
                return input == catta::json::Token::character('t') ? jump(HUB + 434) : error();
            case HUB + 434:
                return input == catta::json::Token::character('e') ? jump(HUB + 435) : error();
            case HUB + 435:
                return input == catta::json::Token::character('D') ? jump(HUB + 436) : error();
            case HUB + 436:
                return input == catta::json::Token::character('e') ? jump(HUB + 437) : error();
            case HUB + 437:
                return input == catta::json::Token::character('r') ? jump(HUB + 438) : error();
            case HUB + 438:
                return input == catta::json::Token::character('T') ? jump(HUB + 439) : error();
            case HUB + 439:
                return input == catta::json::Token::character('y') ? jump(HUB + 440) : error();
            case HUB + 440:
                return input == catta::json::Token::character('p') ? jump(HUB + 441) : error();
            case HUB + 441:
                return input == catta::json::Token::character('e') ? jump(HUB + 442) : error();
            case HUB + 442:
                return input == catta::json::Token::closeString() ? close(38) : error();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _data(Output::empty()) {}
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
    static constexpr std::uint16_t TAIL = HUB + 443;
    static constexpr std::uint16_t DONE = TAIL + 1;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
