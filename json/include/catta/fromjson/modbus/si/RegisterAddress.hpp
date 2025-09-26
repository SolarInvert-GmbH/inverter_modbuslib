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
                return input == catta::json::Token::character('S')   ? jump(HUB + 424)
                       : input == catta::json::Token::character('N') ? jump(HUB + 408)
                       : input == catta::json::Token::character('I') ? jump(HUB + 120)
                       : input == catta::json::Token::character('E') ? jump(HUB + 76)
                       : input == catta::json::Token::character('C') ? jump(HUB + 22)
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
                return input == catta::json::Token::character('M') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('a') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('x') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('P') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('o') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('w') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('e') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('r') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::closeString() ? close(39) : error();
            case HUB + 22:
                return input == catta::json::Token::character('o') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('m') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('m') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('o') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('n') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('V')   ? jump(HUB + 69)
                       : input == catta::json::Token::character('S') ? jump(HUB + 57)
                       : input == catta::json::Token::character('M') ? jump(HUB + 41)
                       : input == catta::json::Token::character('D') ? jump(HUB + 28)
                                                                     : error();
            case HUB + 28:
                return input == catta::json::Token::character('e') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('v') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('i') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('c') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('e') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('A') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('d') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('d') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('r') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('e') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('s') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('s') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::closeString() ? close(4) : error();
            case HUB + 41:
                return input == catta::json::Token::character('o')   ? jump(HUB + 53)
                       : input == catta::json::Token::character('a') ? jump(HUB + 42)
                                                                     : error();
            case HUB + 42:
                return input == catta::json::Token::character('n') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('u') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('f') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('a') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('c') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('t') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('u') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('r') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('e') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('r') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::closeString() ? close(0) : error();
            case HUB + 53:
                return input == catta::json::Token::character('d') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::character('e') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('l') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::closeString() ? close(1) : error();
            case HUB + 57:
                return input == catta::json::Token::character('e') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('r') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('i') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('a') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('l') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('N') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('u') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('m') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('b') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('e') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('r') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::closeString() ? close(3) : error();
            case HUB + 69:
                return input == catta::json::Token::character('e') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('r') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('s') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('i') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('o') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::character('n') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::closeString() ? close(2) : error();
            case HUB + 76:
                return input == catta::json::Token::character('x') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('t') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('e') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('n') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('d') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('e') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('d') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('M') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('e') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('s') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('u') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('r') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('e') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('m') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::character('e') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('n') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('t') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('s') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('A') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::character('c') ? jump(HUB + 96) : error();
            case HUB + 96:
                return input == catta::json::Token::character('W')   ? jump(HUB + 111)
                       : input == catta::json::Token::character('L') ? jump(HUB + 97)
                                                                     : error();
            case HUB + 97:
                return input == catta::json::Token::character('i') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::character('f') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('e') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('t') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('i') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('m') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('e') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('C') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('h') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('a') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('r') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('g') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('e') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::closeString() ? close(41) : error();
            case HUB + 111:
                return input == catta::json::Token::character('a') ? jump(HUB + 112) : error();
            case HUB + 112:
                return input == catta::json::Token::character('t') ? jump(HUB + 113) : error();
            case HUB + 113:
                return input == catta::json::Token::character('t') ? jump(HUB + 114) : error();
            case HUB + 114:
                return input == catta::json::Token::character('H') ? jump(HUB + 115) : error();
            case HUB + 115:
                return input == catta::json::Token::character('o') ? jump(HUB + 116) : error();
            case HUB + 116:
                return input == catta::json::Token::character('u') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('r') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('s') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::closeString() ? close(40) : error();
            case HUB + 120:
                return input == catta::json::Token::character('n') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('v') ? jump(HUB + 122) : error();
            case HUB + 122:
                return input == catta::json::Token::character('e') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::character('r') ? jump(HUB + 124) : error();
            case HUB + 124:
                return input == catta::json::Token::character('t') ? jump(HUB + 125) : error();
            case HUB + 125:
                return input == catta::json::Token::character('e') ? jump(HUB + 126) : error();
            case HUB + 126:
                return input == catta::json::Token::character('r') ? jump(HUB + 127) : error();
            case HUB + 127:
                return input == catta::json::Token::character('W')   ? jump(HUB + 388)
                       : input == catta::json::Token::character('V') ? jump(HUB + 351)
                       : input == catta::json::Token::character('T') ? jump(HUB + 329)
                       : input == catta::json::Token::character('P') ? jump(HUB + 282)
                       : input == catta::json::Token::character('O') ? jump(HUB + 268)
                       : input == catta::json::Token::character('H') ? jump(HUB + 252)
                       : input == catta::json::Token::character('D') ? jump(HUB + 216)
                       : input == catta::json::Token::character('A') ? jump(HUB + 128)
                                                                     : error();
            case HUB + 128:
                return input == catta::json::Token::character('m')   ? jump(HUB + 194)
                       : input == catta::json::Token::character('c') ? jump(HUB + 129)
                                                                     : error();
            case HUB + 129:
                return input == catta::json::Token::character('R')   ? jump(HUB + 170)
                       : input == catta::json::Token::character('P') ? jump(HUB + 154)
                       : input == catta::json::Token::character('A') ? jump(HUB + 130)
                                                                     : error();
            case HUB + 130:
                return input == catta::json::Token::character('p') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('p') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::character('a') ? jump(HUB + 133) : error();
            case HUB + 133:
                return input == catta::json::Token::character('r') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('e') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('n') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::character('t') ? jump(HUB + 137) : error();
            case HUB + 137:
                return input == catta::json::Token::character('P') ? jump(HUB + 138) : error();
            case HUB + 138:
                return input == catta::json::Token::character('o') ? jump(HUB + 139) : error();
            case HUB + 139:
                return input == catta::json::Token::character('w') ? jump(HUB + 140) : error();
            case HUB + 140:
                return input == catta::json::Token::character('e') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('r') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::character('S')  ? jump(HUB + 143)
                       : input == catta::json::Token::closeString() ? close(18)
                                                                    : error();
            case HUB + 143:
                return input == catta::json::Token::character('c') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('a') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::character('l') ? jump(HUB + 146) : error();
            case HUB + 146:
                return input == catta::json::Token::character('e') ? jump(HUB + 147) : error();
            case HUB + 147:
                return input == catta::json::Token::character('F') ? jump(HUB + 148) : error();
            case HUB + 148:
                return input == catta::json::Token::character('a') ? jump(HUB + 149) : error();
            case HUB + 149:
                return input == catta::json::Token::character('c') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('t') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('o') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('r') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::closeString() ? close(19) : error();
            case HUB + 154:
                return input == catta::json::Token::character('o') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('w') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::character('e') ? jump(HUB + 157) : error();
            case HUB + 157:
                return input == catta::json::Token::character('r') ? jump(HUB + 158) : error();
            case HUB + 158:
                return input == catta::json::Token::character('S')  ? jump(HUB + 159)
                       : input == catta::json::Token::closeString() ? close(14)
                                                                    : error();
            case HUB + 159:
                return input == catta::json::Token::character('c') ? jump(HUB + 160) : error();
            case HUB + 160:
                return input == catta::json::Token::character('a') ? jump(HUB + 161) : error();
            case HUB + 161:
                return input == catta::json::Token::character('l') ? jump(HUB + 162) : error();
            case HUB + 162:
                return input == catta::json::Token::character('e') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('F') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('a') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('c') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('t') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('o') ? jump(HUB + 168) : error();
            case HUB + 168:
                return input == catta::json::Token::character('r') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::closeString() ? close(15) : error();
            case HUB + 170:
                return input == catta::json::Token::character('e') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::character('a') ? jump(HUB + 172) : error();
            case HUB + 172:
                return input == catta::json::Token::character('c') ? jump(HUB + 173) : error();
            case HUB + 173:
                return input == catta::json::Token::character('t') ? jump(HUB + 174) : error();
            case HUB + 174:
                return input == catta::json::Token::character('i') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('v') ? jump(HUB + 176) : error();
            case HUB + 176:
                return input == catta::json::Token::character('e') ? jump(HUB + 177) : error();
            case HUB + 177:
                return input == catta::json::Token::character('P') ? jump(HUB + 178) : error();
            case HUB + 178:
                return input == catta::json::Token::character('o') ? jump(HUB + 179) : error();
            case HUB + 179:
                return input == catta::json::Token::character('w') ? jump(HUB + 180) : error();
            case HUB + 180:
                return input == catta::json::Token::character('e') ? jump(HUB + 181) : error();
            case HUB + 181:
                return input == catta::json::Token::character('r') ? jump(HUB + 182) : error();
            case HUB + 182:
                return input == catta::json::Token::character('S')  ? jump(HUB + 183)
                       : input == catta::json::Token::closeString() ? close(20)
                                                                    : error();
            case HUB + 183:
                return input == catta::json::Token::character('c') ? jump(HUB + 184) : error();
            case HUB + 184:
                return input == catta::json::Token::character('a') ? jump(HUB + 185) : error();
            case HUB + 185:
                return input == catta::json::Token::character('l') ? jump(HUB + 186) : error();
            case HUB + 186:
                return input == catta::json::Token::character('e') ? jump(HUB + 187) : error();
            case HUB + 187:
                return input == catta::json::Token::character('F') ? jump(HUB + 188) : error();
            case HUB + 188:
                return input == catta::json::Token::character('a') ? jump(HUB + 189) : error();
            case HUB + 189:
                return input == catta::json::Token::character('c') ? jump(HUB + 190) : error();
            case HUB + 190:
                return input == catta::json::Token::character('t') ? jump(HUB + 191) : error();
            case HUB + 191:
                return input == catta::json::Token::character('o') ? jump(HUB + 192) : error();
            case HUB + 192:
                return input == catta::json::Token::character('r') ? jump(HUB + 193) : error();
            case HUB + 193:
                return input == catta::json::Token::closeString() ? close(21) : error();
            case HUB + 194:
                return input == catta::json::Token::character('p') ? jump(HUB + 195) : error();
            case HUB + 195:
                return input == catta::json::Token::character('s') ? jump(HUB + 196) : error();
            case HUB + 196:
                return input == catta::json::Token::character('S')   ? jump(HUB + 205)
                       : input == catta::json::Token::character('P') ? jump(HUB + 197)
                       : input == catta::json::Token::closeString()  ? close(5)
                                                                     : error();
            case HUB + 197:
                return input == catta::json::Token::character('h') ? jump(HUB + 198) : error();
            case HUB + 198:
                return input == catta::json::Token::character('a') ? jump(HUB + 199) : error();
            case HUB + 199:
                return input == catta::json::Token::character('s') ? jump(HUB + 200) : error();
            case HUB + 200:
                return input == catta::json::Token::character('e') ? jump(HUB + 201) : error();
            case HUB + 201:
                return input == catta::json::Token::character('C')   ? jump(HUB + 204)
                       : input == catta::json::Token::character('B') ? jump(HUB + 203)
                       : input == catta::json::Token::character('A') ? jump(HUB + 202)
                                                                     : error();
            case HUB + 202:
                return input == catta::json::Token::closeString() ? close(6) : error();
            case HUB + 203:
                return input == catta::json::Token::closeString() ? close(7) : error();
            case HUB + 204:
                return input == catta::json::Token::closeString() ? close(8) : error();
            case HUB + 205:
                return input == catta::json::Token::character('c') ? jump(HUB + 206) : error();
            case HUB + 206:
                return input == catta::json::Token::character('a') ? jump(HUB + 207) : error();
            case HUB + 207:
                return input == catta::json::Token::character('l') ? jump(HUB + 208) : error();
            case HUB + 208:
                return input == catta::json::Token::character('e') ? jump(HUB + 209) : error();
            case HUB + 209:
                return input == catta::json::Token::character('F') ? jump(HUB + 210) : error();
            case HUB + 210:
                return input == catta::json::Token::character('a') ? jump(HUB + 211) : error();
            case HUB + 211:
                return input == catta::json::Token::character('c') ? jump(HUB + 212) : error();
            case HUB + 212:
                return input == catta::json::Token::character('t') ? jump(HUB + 213) : error();
            case HUB + 213:
                return input == catta::json::Token::character('o') ? jump(HUB + 214) : error();
            case HUB + 214:
                return input == catta::json::Token::character('r') ? jump(HUB + 215) : error();
            case HUB + 215:
                return input == catta::json::Token::closeString() ? close(9) : error();
            case HUB + 216:
                return input == catta::json::Token::character('c') ? jump(HUB + 217) : error();
            case HUB + 217:
                return input == catta::json::Token::character('V')   ? jump(HUB + 234)
                       : input == catta::json::Token::character('P') ? jump(HUB + 218)
                                                                     : error();
            case HUB + 218:
                return input == catta::json::Token::character('o') ? jump(HUB + 219) : error();
            case HUB + 219:
                return input == catta::json::Token::character('w') ? jump(HUB + 220) : error();
            case HUB + 220:
                return input == catta::json::Token::character('e') ? jump(HUB + 221) : error();
            case HUB + 221:
                return input == catta::json::Token::character('r') ? jump(HUB + 222) : error();
            case HUB + 222:
                return input == catta::json::Token::character('S')  ? jump(HUB + 223)
                       : input == catta::json::Token::closeString() ? close(28)
                                                                    : error();
            case HUB + 223:
                return input == catta::json::Token::character('c') ? jump(HUB + 224) : error();
            case HUB + 224:
                return input == catta::json::Token::character('a') ? jump(HUB + 225) : error();
            case HUB + 225:
                return input == catta::json::Token::character('l') ? jump(HUB + 226) : error();
            case HUB + 226:
                return input == catta::json::Token::character('e') ? jump(HUB + 227) : error();
            case HUB + 227:
                return input == catta::json::Token::character('F') ? jump(HUB + 228) : error();
            case HUB + 228:
                return input == catta::json::Token::character('a') ? jump(HUB + 229) : error();
            case HUB + 229:
                return input == catta::json::Token::character('c') ? jump(HUB + 230) : error();
            case HUB + 230:
                return input == catta::json::Token::character('t') ? jump(HUB + 231) : error();
            case HUB + 231:
                return input == catta::json::Token::character('o') ? jump(HUB + 232) : error();
            case HUB + 232:
                return input == catta::json::Token::character('r') ? jump(HUB + 233) : error();
            case HUB + 233:
                return input == catta::json::Token::closeString() ? close(29) : error();
            case HUB + 234:
                return input == catta::json::Token::character('o') ? jump(HUB + 235) : error();
            case HUB + 235:
                return input == catta::json::Token::character('l') ? jump(HUB + 236) : error();
            case HUB + 236:
                return input == catta::json::Token::character('t') ? jump(HUB + 237) : error();
            case HUB + 237:
                return input == catta::json::Token::character('a') ? jump(HUB + 238) : error();
            case HUB + 238:
                return input == catta::json::Token::character('g') ? jump(HUB + 239) : error();
            case HUB + 239:
                return input == catta::json::Token::character('e') ? jump(HUB + 240) : error();
            case HUB + 240:
                return input == catta::json::Token::character('S')  ? jump(HUB + 241)
                       : input == catta::json::Token::closeString() ? close(26)
                                                                    : error();
            case HUB + 241:
                return input == catta::json::Token::character('c') ? jump(HUB + 242) : error();
            case HUB + 242:
                return input == catta::json::Token::character('a') ? jump(HUB + 243) : error();
            case HUB + 243:
                return input == catta::json::Token::character('l') ? jump(HUB + 244) : error();
            case HUB + 244:
                return input == catta::json::Token::character('e') ? jump(HUB + 245) : error();
            case HUB + 245:
                return input == catta::json::Token::character('F') ? jump(HUB + 246) : error();
            case HUB + 246:
                return input == catta::json::Token::character('a') ? jump(HUB + 247) : error();
            case HUB + 247:
                return input == catta::json::Token::character('c') ? jump(HUB + 248) : error();
            case HUB + 248:
                return input == catta::json::Token::character('t') ? jump(HUB + 249) : error();
            case HUB + 249:
                return input == catta::json::Token::character('o') ? jump(HUB + 250) : error();
            case HUB + 250:
                return input == catta::json::Token::character('r') ? jump(HUB + 251) : error();
            case HUB + 251:
                return input == catta::json::Token::closeString() ? close(27) : error();
            case HUB + 252:
                return input == catta::json::Token::character('e') ? jump(HUB + 253) : error();
            case HUB + 253:
                return input == catta::json::Token::character('r') ? jump(HUB + 254) : error();
            case HUB + 254:
                return input == catta::json::Token::character('t') ? jump(HUB + 255) : error();
            case HUB + 255:
                return input == catta::json::Token::character('z') ? jump(HUB + 256) : error();
            case HUB + 256:
                return input == catta::json::Token::character('S')  ? jump(HUB + 257)
                       : input == catta::json::Token::closeString() ? close(16)
                                                                    : error();
            case HUB + 257:
                return input == catta::json::Token::character('c') ? jump(HUB + 258) : error();
            case HUB + 258:
                return input == catta::json::Token::character('a') ? jump(HUB + 259) : error();
            case HUB + 259:
                return input == catta::json::Token::character('l') ? jump(HUB + 260) : error();
            case HUB + 260:
                return input == catta::json::Token::character('e') ? jump(HUB + 261) : error();
            case HUB + 261:
                return input == catta::json::Token::character('F') ? jump(HUB + 262) : error();
            case HUB + 262:
                return input == catta::json::Token::character('a') ? jump(HUB + 263) : error();
            case HUB + 263:
                return input == catta::json::Token::character('c') ? jump(HUB + 264) : error();
            case HUB + 264:
                return input == catta::json::Token::character('t') ? jump(HUB + 265) : error();
            case HUB + 265:
                return input == catta::json::Token::character('o') ? jump(HUB + 266) : error();
            case HUB + 266:
                return input == catta::json::Token::character('r') ? jump(HUB + 267) : error();
            case HUB + 267:
                return input == catta::json::Token::closeString() ? close(17) : error();
            case HUB + 268:
                return input == catta::json::Token::character('p') ? jump(HUB + 269) : error();
            case HUB + 269:
                return input == catta::json::Token::character('e') ? jump(HUB + 270) : error();
            case HUB + 270:
                return input == catta::json::Token::character('r') ? jump(HUB + 271) : error();
            case HUB + 271:
                return input == catta::json::Token::character('a') ? jump(HUB + 272) : error();
            case HUB + 272:
                return input == catta::json::Token::character('t') ? jump(HUB + 273) : error();
            case HUB + 273:
                return input == catta::json::Token::character('i') ? jump(HUB + 274) : error();
            case HUB + 274:
                return input == catta::json::Token::character('n') ? jump(HUB + 275) : error();
            case HUB + 275:
                return input == catta::json::Token::character('g') ? jump(HUB + 276) : error();
            case HUB + 276:
                return input == catta::json::Token::character('S') ? jump(HUB + 277) : error();
            case HUB + 277:
                return input == catta::json::Token::character('t') ? jump(HUB + 278) : error();
            case HUB + 278:
                return input == catta::json::Token::character('a') ? jump(HUB + 279) : error();
            case HUB + 279:
                return input == catta::json::Token::character('t') ? jump(HUB + 280) : error();
            case HUB + 280:
                return input == catta::json::Token::character('e') ? jump(HUB + 281) : error();
            case HUB + 281:
                return input == catta::json::Token::closeString() ? close(32) : error();
            case HUB + 282:
                return input == catta::json::Token::character('o')   ? jump(HUB + 308)
                       : input == catta::json::Token::character('h') ? jump(HUB + 283)
                                                                     : error();
            case HUB + 283:
                return input == catta::json::Token::character('a') ? jump(HUB + 284) : error();
            case HUB + 284:
                return input == catta::json::Token::character('s') ? jump(HUB + 285) : error();
            case HUB + 285:
                return input == catta::json::Token::character('e') ? jump(HUB + 286) : error();
            case HUB + 286:
                return input == catta::json::Token::character('V') ? jump(HUB + 287) : error();
            case HUB + 287:
                return input == catta::json::Token::character('o') ? jump(HUB + 288) : error();
            case HUB + 288:
                return input == catta::json::Token::character('l') ? jump(HUB + 289) : error();
            case HUB + 289:
                return input == catta::json::Token::character('t') ? jump(HUB + 290) : error();
            case HUB + 290:
                return input == catta::json::Token::character('a') ? jump(HUB + 291) : error();
            case HUB + 291:
                return input == catta::json::Token::character('g') ? jump(HUB + 292) : error();
            case HUB + 292:
                return input == catta::json::Token::character('e') ? jump(HUB + 293) : error();
            case HUB + 293:
                return input == catta::json::Token::character('S')   ? jump(HUB + 297)
                       : input == catta::json::Token::character('C') ? jump(HUB + 296)
                       : input == catta::json::Token::character('B') ? jump(HUB + 295)
                       : input == catta::json::Token::character('A') ? jump(HUB + 294)
                                                                     : error();
            case HUB + 294:
                return input == catta::json::Token::closeString() ? close(10) : error();
            case HUB + 295:
                return input == catta::json::Token::closeString() ? close(11) : error();
            case HUB + 296:
                return input == catta::json::Token::closeString() ? close(12) : error();
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
                return input == catta::json::Token::closeString() ? close(13) : error();
            case HUB + 308:
                return input == catta::json::Token::character('w') ? jump(HUB + 309) : error();
            case HUB + 309:
                return input == catta::json::Token::character('e') ? jump(HUB + 310) : error();
            case HUB + 310:
                return input == catta::json::Token::character('r') ? jump(HUB + 311) : error();
            case HUB + 311:
                return input == catta::json::Token::character('F') ? jump(HUB + 312) : error();
            case HUB + 312:
                return input == catta::json::Token::character('a') ? jump(HUB + 313) : error();
            case HUB + 313:
                return input == catta::json::Token::character('c') ? jump(HUB + 314) : error();
            case HUB + 314:
                return input == catta::json::Token::character('t') ? jump(HUB + 315) : error();
            case HUB + 315:
                return input == catta::json::Token::character('o') ? jump(HUB + 316) : error();
            case HUB + 316:
                return input == catta::json::Token::character('r') ? jump(HUB + 317) : error();
            case HUB + 317:
                return input == catta::json::Token::character('S')  ? jump(HUB + 318)
                       : input == catta::json::Token::closeString() ? close(22)
                                                                    : error();
            case HUB + 318:
                return input == catta::json::Token::character('c') ? jump(HUB + 319) : error();
            case HUB + 319:
                return input == catta::json::Token::character('a') ? jump(HUB + 320) : error();
            case HUB + 320:
                return input == catta::json::Token::character('l') ? jump(HUB + 321) : error();
            case HUB + 321:
                return input == catta::json::Token::character('e') ? jump(HUB + 322) : error();
            case HUB + 322:
                return input == catta::json::Token::character('F') ? jump(HUB + 323) : error();
            case HUB + 323:
                return input == catta::json::Token::character('a') ? jump(HUB + 324) : error();
            case HUB + 324:
                return input == catta::json::Token::character('c') ? jump(HUB + 325) : error();
            case HUB + 325:
                return input == catta::json::Token::character('t') ? jump(HUB + 326) : error();
            case HUB + 326:
                return input == catta::json::Token::character('o') ? jump(HUB + 327) : error();
            case HUB + 327:
                return input == catta::json::Token::character('r') ? jump(HUB + 328) : error();
            case HUB + 328:
                return input == catta::json::Token::closeString() ? close(23) : error();
            case HUB + 329:
                return input == catta::json::Token::character('e') ? jump(HUB + 330) : error();
            case HUB + 330:
                return input == catta::json::Token::character('m') ? jump(HUB + 331) : error();
            case HUB + 331:
                return input == catta::json::Token::character('p') ? jump(HUB + 332) : error();
            case HUB + 332:
                return input == catta::json::Token::character('e') ? jump(HUB + 333) : error();
            case HUB + 333:
                return input == catta::json::Token::character('r') ? jump(HUB + 334) : error();
            case HUB + 334:
                return input == catta::json::Token::character('a') ? jump(HUB + 335) : error();
            case HUB + 335:
                return input == catta::json::Token::character('t') ? jump(HUB + 336) : error();
            case HUB + 336:
                return input == catta::json::Token::character('u') ? jump(HUB + 337) : error();
            case HUB + 337:
                return input == catta::json::Token::character('r') ? jump(HUB + 338) : error();
            case HUB + 338:
                return input == catta::json::Token::character('e') ? jump(HUB + 339) : error();
            case HUB + 339:
                return input == catta::json::Token::character('S')  ? jump(HUB + 340)
                       : input == catta::json::Token::closeString() ? close(30)
                                                                    : error();
            case HUB + 340:
                return input == catta::json::Token::character('c') ? jump(HUB + 341) : error();
            case HUB + 341:
                return input == catta::json::Token::character('a') ? jump(HUB + 342) : error();
            case HUB + 342:
                return input == catta::json::Token::character('l') ? jump(HUB + 343) : error();
            case HUB + 343:
                return input == catta::json::Token::character('e') ? jump(HUB + 344) : error();
            case HUB + 344:
                return input == catta::json::Token::character('F') ? jump(HUB + 345) : error();
            case HUB + 345:
                return input == catta::json::Token::character('a') ? jump(HUB + 346) : error();
            case HUB + 346:
                return input == catta::json::Token::character('c') ? jump(HUB + 347) : error();
            case HUB + 347:
                return input == catta::json::Token::character('t') ? jump(HUB + 348) : error();
            case HUB + 348:
                return input == catta::json::Token::character('o') ? jump(HUB + 349) : error();
            case HUB + 349:
                return input == catta::json::Token::character('r') ? jump(HUB + 350) : error();
            case HUB + 350:
                return input == catta::json::Token::closeString() ? close(31) : error();
            case HUB + 351:
                return input == catta::json::Token::character('e') ? jump(HUB + 352) : error();
            case HUB + 352:
                return input == catta::json::Token::character('n') ? jump(HUB + 353) : error();
            case HUB + 353:
                return input == catta::json::Token::character('d') ? jump(HUB + 354) : error();
            case HUB + 354:
                return input == catta::json::Token::character('o') ? jump(HUB + 355) : error();
            case HUB + 355:
                return input == catta::json::Token::character('r') ? jump(HUB + 356) : error();
            case HUB + 356:
                return input == catta::json::Token::character('O')   ? jump(HUB + 374)
                       : input == catta::json::Token::character('E') ? jump(HUB + 357)
                                                                     : error();
            case HUB + 357:
                return input == catta::json::Token::character('v') ? jump(HUB + 358) : error();
            case HUB + 358:
                return input == catta::json::Token::character('e') ? jump(HUB + 359) : error();
            case HUB + 359:
                return input == catta::json::Token::character('n') ? jump(HUB + 360) : error();
            case HUB + 360:
                return input == catta::json::Token::character('t') ? jump(HUB + 361) : error();
            case HUB + 361:
                return input == catta::json::Token::character('B') ? jump(HUB + 362) : error();
            case HUB + 362:
                return input == catta::json::Token::character('i') ? jump(HUB + 363) : error();
            case HUB + 363:
                return input == catta::json::Token::character('t') ? jump(HUB + 364) : error();
            case HUB + 364:
                return input == catta::json::Token::character('f') ? jump(HUB + 365) : error();
            case HUB + 365:
                return input == catta::json::Token::character('i') ? jump(HUB + 366) : error();
            case HUB + 366:
                return input == catta::json::Token::character('e') ? jump(HUB + 367) : error();
            case HUB + 367:
                return input == catta::json::Token::character('l') ? jump(HUB + 368) : error();
            case HUB + 368:
                return input == catta::json::Token::character('d') ? jump(HUB + 369) : error();
            case HUB + 369:
                return input == catta::json::Token::character('4')   ? jump(HUB + 373)
                       : input == catta::json::Token::character('3') ? jump(HUB + 372)
                       : input == catta::json::Token::character('2') ? jump(HUB + 371)
                       : input == catta::json::Token::character('1') ? jump(HUB + 370)
                                                                     : error();
            case HUB + 370:
                return input == catta::json::Token::closeString() ? close(34) : error();
            case HUB + 371:
                return input == catta::json::Token::closeString() ? close(35) : error();
            case HUB + 372:
                return input == catta::json::Token::closeString() ? close(36) : error();
            case HUB + 373:
                return input == catta::json::Token::closeString() ? close(37) : error();
            case HUB + 374:
                return input == catta::json::Token::character('p') ? jump(HUB + 375) : error();
            case HUB + 375:
                return input == catta::json::Token::character('e') ? jump(HUB + 376) : error();
            case HUB + 376:
                return input == catta::json::Token::character('r') ? jump(HUB + 377) : error();
            case HUB + 377:
                return input == catta::json::Token::character('a') ? jump(HUB + 378) : error();
            case HUB + 378:
                return input == catta::json::Token::character('t') ? jump(HUB + 379) : error();
            case HUB + 379:
                return input == catta::json::Token::character('i') ? jump(HUB + 380) : error();
            case HUB + 380:
                return input == catta::json::Token::character('n') ? jump(HUB + 381) : error();
            case HUB + 381:
                return input == catta::json::Token::character('g') ? jump(HUB + 382) : error();
            case HUB + 382:
                return input == catta::json::Token::character('S') ? jump(HUB + 383) : error();
            case HUB + 383:
                return input == catta::json::Token::character('t') ? jump(HUB + 384) : error();
            case HUB + 384:
                return input == catta::json::Token::character('a') ? jump(HUB + 385) : error();
            case HUB + 385:
                return input == catta::json::Token::character('t') ? jump(HUB + 386) : error();
            case HUB + 386:
                return input == catta::json::Token::character('e') ? jump(HUB + 387) : error();
            case HUB + 387:
                return input == catta::json::Token::closeString() ? close(33) : error();
            case HUB + 388:
                return input == catta::json::Token::character('a') ? jump(HUB + 389) : error();
            case HUB + 389:
                return input == catta::json::Token::character('t') ? jump(HUB + 390) : error();
            case HUB + 390:
                return input == catta::json::Token::character('t') ? jump(HUB + 391) : error();
            case HUB + 391:
                return input == catta::json::Token::character('H') ? jump(HUB + 392) : error();
            case HUB + 392:
                return input == catta::json::Token::character('o') ? jump(HUB + 393) : error();
            case HUB + 393:
                return input == catta::json::Token::character('u') ? jump(HUB + 394) : error();
            case HUB + 394:
                return input == catta::json::Token::character('r') ? jump(HUB + 395) : error();
            case HUB + 395:
                return input == catta::json::Token::character('s') ? jump(HUB + 396) : error();
            case HUB + 396:
                return input == catta::json::Token::character('S')  ? jump(HUB + 397)
                       : input == catta::json::Token::closeString() ? close(24)
                                                                    : error();
            case HUB + 397:
                return input == catta::json::Token::character('c') ? jump(HUB + 398) : error();
            case HUB + 398:
                return input == catta::json::Token::character('a') ? jump(HUB + 399) : error();
            case HUB + 399:
                return input == catta::json::Token::character('l') ? jump(HUB + 400) : error();
            case HUB + 400:
                return input == catta::json::Token::character('e') ? jump(HUB + 401) : error();
            case HUB + 401:
                return input == catta::json::Token::character('F') ? jump(HUB + 402) : error();
            case HUB + 402:
                return input == catta::json::Token::character('a') ? jump(HUB + 403) : error();
            case HUB + 403:
                return input == catta::json::Token::character('c') ? jump(HUB + 404) : error();
            case HUB + 404:
                return input == catta::json::Token::character('t') ? jump(HUB + 405) : error();
            case HUB + 405:
                return input == catta::json::Token::character('o') ? jump(HUB + 406) : error();
            case HUB + 406:
                return input == catta::json::Token::character('r') ? jump(HUB + 407) : error();
            case HUB + 407:
                return input == catta::json::Token::closeString() ? close(25) : error();
            case HUB + 408:
                return input == catta::json::Token::character('a') ? jump(HUB + 409) : error();
            case HUB + 409:
                return input == catta::json::Token::character('m') ? jump(HUB + 410) : error();
            case HUB + 410:
                return input == catta::json::Token::character('e') ? jump(HUB + 411) : error();
            case HUB + 411:
                return input == catta::json::Token::character('p') ? jump(HUB + 412) : error();
            case HUB + 412:
                return input == catta::json::Token::character('l') ? jump(HUB + 413) : error();
            case HUB + 413:
                return input == catta::json::Token::character('a') ? jump(HUB + 414) : error();
            case HUB + 414:
                return input == catta::json::Token::character('t') ? jump(HUB + 415) : error();
            case HUB + 415:
                return input == catta::json::Token::character('e') ? jump(HUB + 416) : error();
            case HUB + 416:
                return input == catta::json::Token::character('D') ? jump(HUB + 417) : error();
            case HUB + 417:
                return input == catta::json::Token::character('e') ? jump(HUB + 418) : error();
            case HUB + 418:
                return input == catta::json::Token::character('r') ? jump(HUB + 419) : error();
            case HUB + 419:
                return input == catta::json::Token::character('T') ? jump(HUB + 420) : error();
            case HUB + 420:
                return input == catta::json::Token::character('y') ? jump(HUB + 421) : error();
            case HUB + 421:
                return input == catta::json::Token::character('p') ? jump(HUB + 422) : error();
            case HUB + 422:
                return input == catta::json::Token::character('e') ? jump(HUB + 423) : error();
            case HUB + 423:
                return input == catta::json::Token::closeString() ? close(38) : error();
            case HUB + 424:
                return input == catta::json::Token::character('t')   ? jump(HUB + 1290)
                       : input == catta::json::Token::character('i') ? jump(HUB + 425)
                                                                     : error();
            case HUB + 425:
                return input == catta::json::Token::character('C') ? jump(HUB + 426) : error();
            case HUB + 426:
                return input == catta::json::Token::character('o') ? jump(HUB + 427) : error();
            case HUB + 427:
                return input == catta::json::Token::character('n') ? jump(HUB + 428) : error();
            case HUB + 428:
                return input == catta::json::Token::character('t') ? jump(HUB + 429) : error();
            case HUB + 429:
                return input == catta::json::Token::character('r') ? jump(HUB + 430) : error();
            case HUB + 430:
                return input == catta::json::Token::character('o') ? jump(HUB + 431) : error();
            case HUB + 431:
                return input == catta::json::Token::character('l') ? jump(HUB + 432) : error();
            case HUB + 432:
                return input == catta::json::Token::character('W')   ? jump(HUB + 955)
                       : input == catta::json::Token::character('V') ? jump(HUB + 932)
                       : input == catta::json::Token::character('U') ? jump(HUB + 903)
                       : input == catta::json::Token::character('T') ? jump(HUB + 886)
                       : input == catta::json::Token::character('S') ? jump(HUB + 844)
                       : input == catta::json::Token::character('R') ? jump(HUB + 835)
                       : input == catta::json::Token::character('P') ? jump(HUB + 813)
                       : input == catta::json::Token::character('N') ? jump(HUB + 800)
                       : input == catta::json::Token::character('M') ? jump(HUB + 756)
                       : input == catta::json::Token::character('F') ? jump(HUB + 710)
                       : input == catta::json::Token::character('E') ? jump(HUB + 688)
                       : input == catta::json::Token::character('D') ? jump(HUB + 542)
                       : input == catta::json::Token::character('C') ? jump(HUB + 488)
                       : input == catta::json::Token::character('B') ? jump(HUB + 433)
                                                                     : error();
            case HUB + 433:
                return input == catta::json::Token::character('a') ? jump(HUB + 434) : error();
            case HUB + 434:
                return input == catta::json::Token::character('t') ? jump(HUB + 435) : error();
            case HUB + 435:
                return input == catta::json::Token::character('t') ? jump(HUB + 436) : error();
            case HUB + 436:
                return input == catta::json::Token::character('e') ? jump(HUB + 437) : error();
            case HUB + 437:
                return input == catta::json::Token::character('r') ? jump(HUB + 438) : error();
            case HUB + 438:
                return input == catta::json::Token::character('y') ? jump(HUB + 439) : error();
            case HUB + 439:
                return input == catta::json::Token::character('S')   ? jump(HUB + 470)
                       : input == catta::json::Token::character('C') ? jump(HUB + 455)
                       : input == catta::json::Token::character('B') ? jump(HUB + 440)
                                                                     : error();
            case HUB + 440:
                return input == catta::json::Token::character('i') ? jump(HUB + 441) : error();
            case HUB + 441:
                return input == catta::json::Token::character('M') ? jump(HUB + 442) : error();
            case HUB + 442:
                return input == catta::json::Token::character('o') ? jump(HUB + 443) : error();
            case HUB + 443:
                return input == catta::json::Token::character('d') ? jump(HUB + 444) : error();
            case HUB + 444:
                return input == catta::json::Token::character('e') ? jump(HUB + 445) : error();
            case HUB + 445:
                return input == catta::json::Token::character('W')   ? jump(HUB + 450)
                       : input == catta::json::Token::character('R') ? jump(HUB + 446)
                                                                     : error();
            case HUB + 446:
                return input == catta::json::Token::character('e') ? jump(HUB + 447) : error();
            case HUB + 447:
                return input == catta::json::Token::character('a') ? jump(HUB + 448) : error();
            case HUB + 448:
                return input == catta::json::Token::character('d') ? jump(HUB + 449) : error();
            case HUB + 449:
                return input == catta::json::Token::closeString() ? close(47) : error();
            case HUB + 450:
                return input == catta::json::Token::character('r') ? jump(HUB + 451) : error();
            case HUB + 451:
                return input == catta::json::Token::character('i') ? jump(HUB + 452) : error();
            case HUB + 452:
                return input == catta::json::Token::character('t') ? jump(HUB + 453) : error();
            case HUB + 453:
                return input == catta::json::Token::character('e') ? jump(HUB + 454) : error();
            case HUB + 454:
                return input == catta::json::Token::closeString() ? close(117) : error();
            case HUB + 455:
                return input == catta::json::Token::character('v') ? jump(HUB + 456) : error();
            case HUB + 456:
                return input == catta::json::Token::character('M') ? jump(HUB + 457) : error();
            case HUB + 457:
                return input == catta::json::Token::character('o') ? jump(HUB + 458) : error();
            case HUB + 458:
                return input == catta::json::Token::character('d') ? jump(HUB + 459) : error();
            case HUB + 459:
                return input == catta::json::Token::character('e') ? jump(HUB + 460) : error();
            case HUB + 460:
                return input == catta::json::Token::character('W')   ? jump(HUB + 465)
                       : input == catta::json::Token::character('R') ? jump(HUB + 461)
                                                                     : error();
            case HUB + 461:
                return input == catta::json::Token::character('e') ? jump(HUB + 462) : error();
            case HUB + 462:
                return input == catta::json::Token::character('a') ? jump(HUB + 463) : error();
            case HUB + 463:
                return input == catta::json::Token::character('d') ? jump(HUB + 464) : error();
            case HUB + 464:
                return input == catta::json::Token::closeString() ? close(49) : error();
            case HUB + 465:
                return input == catta::json::Token::character('r') ? jump(HUB + 466) : error();
            case HUB + 466:
                return input == catta::json::Token::character('i') ? jump(HUB + 467) : error();
            case HUB + 467:
                return input == catta::json::Token::character('t') ? jump(HUB + 468) : error();
            case HUB + 468:
                return input == catta::json::Token::character('e') ? jump(HUB + 469) : error();
            case HUB + 469:
                return input == catta::json::Token::closeString() ? close(119) : error();
            case HUB + 470:
                return input == catta::json::Token::character('a') ? jump(HUB + 471) : error();
            case HUB + 471:
                return input == catta::json::Token::character('f') ? jump(HUB + 472) : error();
            case HUB + 472:
                return input == catta::json::Token::character('t') ? jump(HUB + 473) : error();
            case HUB + 473:
                return input == catta::json::Token::character('y') ? jump(HUB + 474) : error();
            case HUB + 474:
                return input == catta::json::Token::character('M') ? jump(HUB + 475) : error();
            case HUB + 475:
                return input == catta::json::Token::character('o') ? jump(HUB + 476) : error();
            case HUB + 476:
                return input == catta::json::Token::character('d') ? jump(HUB + 477) : error();
            case HUB + 477:
                return input == catta::json::Token::character('e') ? jump(HUB + 478) : error();
            case HUB + 478:
                return input == catta::json::Token::character('W')   ? jump(HUB + 483)
                       : input == catta::json::Token::character('R') ? jump(HUB + 479)
                                                                     : error();
            case HUB + 479:
                return input == catta::json::Token::character('e') ? jump(HUB + 480) : error();
            case HUB + 480:
                return input == catta::json::Token::character('a') ? jump(HUB + 481) : error();
            case HUB + 481:
                return input == catta::json::Token::character('d') ? jump(HUB + 482) : error();
            case HUB + 482:
                return input == catta::json::Token::closeString() ? close(48) : error();
            case HUB + 483:
                return input == catta::json::Token::character('r') ? jump(HUB + 484) : error();
            case HUB + 484:
                return input == catta::json::Token::character('i') ? jump(HUB + 485) : error();
            case HUB + 485:
                return input == catta::json::Token::character('t') ? jump(HUB + 486) : error();
            case HUB + 486:
                return input == catta::json::Token::character('e') ? jump(HUB + 487) : error();
            case HUB + 487:
                return input == catta::json::Token::closeString() ? close(118) : error();
            case HUB + 488:
                return input == catta::json::Token::character('o') ? jump(HUB + 489) : error();
            case HUB + 489:
                return input == catta::json::Token::character('s')   ? jump(HUB + 538)
                       : input == catta::json::Token::character('n') ? jump(HUB + 490)
                                                                     : error();
            case HUB + 490:
                return input == catta::json::Token::character('s') ? jump(HUB + 491) : error();
            case HUB + 491:
                return input == catta::json::Token::character('t') ? jump(HUB + 492) : error();
            case HUB + 492:
                return input == catta::json::Token::character('a') ? jump(HUB + 493) : error();
            case HUB + 493:
                return input == catta::json::Token::character('n') ? jump(HUB + 494) : error();
            case HUB + 494:
                return input == catta::json::Token::character('t') ? jump(HUB + 495) : error();
            case HUB + 495:
                return input == catta::json::Token::character('V') ? jump(HUB + 496) : error();
            case HUB + 496:
                return input == catta::json::Token::character('o') ? jump(HUB + 497) : error();
            case HUB + 497:
                return input == catta::json::Token::character('l') ? jump(HUB + 498) : error();
            case HUB + 498:
                return input == catta::json::Token::character('t') ? jump(HUB + 499) : error();
            case HUB + 499:
                return input == catta::json::Token::character('a') ? jump(HUB + 500) : error();
            case HUB + 500:
                return input == catta::json::Token::character('g') ? jump(HUB + 501) : error();
            case HUB + 501:
                return input == catta::json::Token::character('e') ? jump(HUB + 502) : error();
            case HUB + 502:
                return input == catta::json::Token::character('Y')   ? jump(HUB + 507)
                       : input == catta::json::Token::character('X') ? jump(HUB + 503)
                                                                     : error();
            case HUB + 503:
                return input == catta::json::Token::character('2')   ? jump(HUB + 506)
                       : input == catta::json::Token::character('1') ? jump(HUB + 505)
                       : input == catta::json::Token::character('0') ? jump(HUB + 504)
                                                                     : error();
            case HUB + 504:
                return input == catta::json::Token::closeString() ? close(151) : error();
            case HUB + 505:
                return input == catta::json::Token::closeString() ? close(152) : error();
            case HUB + 506:
                return input == catta::json::Token::closeString() ? close(153) : error();
            case HUB + 507:
                return input == catta::json::Token::character('2')   ? jump(HUB + 528)
                       : input == catta::json::Token::character('1') ? jump(HUB + 518)
                       : input == catta::json::Token::character('0') ? jump(HUB + 508)
                                                                     : error();
            case HUB + 508:
                return input == catta::json::Token::character('W')   ? jump(HUB + 513)
                       : input == catta::json::Token::character('R') ? jump(HUB + 509)
                                                                     : error();
            case HUB + 509:
                return input == catta::json::Token::character('e') ? jump(HUB + 510) : error();
            case HUB + 510:
                return input == catta::json::Token::character('a') ? jump(HUB + 511) : error();
            case HUB + 511:
                return input == catta::json::Token::character('d') ? jump(HUB + 512) : error();
            case HUB + 512:
                return input == catta::json::Token::closeString() ? close(154) : error();
            case HUB + 513:
                return input == catta::json::Token::character('r') ? jump(HUB + 514) : error();
            case HUB + 514:
                return input == catta::json::Token::character('i') ? jump(HUB + 515) : error();
            case HUB + 515:
                return input == catta::json::Token::character('t') ? jump(HUB + 516) : error();
            case HUB + 516:
                return input == catta::json::Token::character('e') ? jump(HUB + 517) : error();
            case HUB + 517:
                return input == catta::json::Token::closeString() ? close(138) : error();
            case HUB + 518:
                return input == catta::json::Token::character('W')   ? jump(HUB + 523)
                       : input == catta::json::Token::character('R') ? jump(HUB + 519)
                                                                     : error();
            case HUB + 519:
                return input == catta::json::Token::character('e') ? jump(HUB + 520) : error();
            case HUB + 520:
                return input == catta::json::Token::character('a') ? jump(HUB + 521) : error();
            case HUB + 521:
                return input == catta::json::Token::character('d') ? jump(HUB + 522) : error();
            case HUB + 522:
                return input == catta::json::Token::closeString() ? close(155) : error();
            case HUB + 523:
                return input == catta::json::Token::character('r') ? jump(HUB + 524) : error();
            case HUB + 524:
                return input == catta::json::Token::character('i') ? jump(HUB + 525) : error();
            case HUB + 525:
                return input == catta::json::Token::character('t') ? jump(HUB + 526) : error();
            case HUB + 526:
                return input == catta::json::Token::character('e') ? jump(HUB + 527) : error();
            case HUB + 527:
                return input == catta::json::Token::closeString() ? close(139) : error();
            case HUB + 528:
                return input == catta::json::Token::character('W')   ? jump(HUB + 533)
                       : input == catta::json::Token::character('R') ? jump(HUB + 529)
                                                                     : error();
            case HUB + 529:
                return input == catta::json::Token::character('e') ? jump(HUB + 530) : error();
            case HUB + 530:
                return input == catta::json::Token::character('a') ? jump(HUB + 531) : error();
            case HUB + 531:
                return input == catta::json::Token::character('d') ? jump(HUB + 532) : error();
            case HUB + 532:
                return input == catta::json::Token::closeString() ? close(156) : error();
            case HUB + 533:
                return input == catta::json::Token::character('r') ? jump(HUB + 534) : error();
            case HUB + 534:
                return input == catta::json::Token::character('i') ? jump(HUB + 535) : error();
            case HUB + 535:
                return input == catta::json::Token::character('t') ? jump(HUB + 536) : error();
            case HUB + 536:
                return input == catta::json::Token::character('e') ? jump(HUB + 537) : error();
            case HUB + 537:
                return input == catta::json::Token::closeString() ? close(140) : error();
            case HUB + 538:
                return input == catta::json::Token::character('p') ? jump(HUB + 539) : error();
            case HUB + 539:
                return input == catta::json::Token::character('h') ? jump(HUB + 540) : error();
            case HUB + 540:
                return input == catta::json::Token::character('i') ? jump(HUB + 541) : error();
            case HUB + 541:
                return input == catta::json::Token::closeString() ? close(59) : error();
            case HUB + 542:
                return input == catta::json::Token::character('c')   ? jump(HUB + 662)
                       : input == catta::json::Token::character('a') ? jump(HUB + 543)
                                                                     : error();
            case HUB + 543:
                return input == catta::json::Token::character('c') ? jump(HUB + 544) : error();
            case HUB + 544:
                return input == catta::json::Token::character('C') ? jump(HUB + 545) : error();
            case HUB + 545:
                return input == catta::json::Token::character('u') ? jump(HUB + 546) : error();
            case HUB + 546:
                return input == catta::json::Token::character('r') ? jump(HUB + 547) : error();
            case HUB + 547:
                return input == catta::json::Token::character('v') ? jump(HUB + 548) : error();
            case HUB + 548:
                return input == catta::json::Token::character('e') ? jump(HUB + 549) : error();
            case HUB + 549:
                return input == catta::json::Token::character('Y')   ? jump(HUB + 561)
                       : input == catta::json::Token::character('X') ? jump(HUB + 550)
                                                                     : error();
            case HUB + 550:
                return input == catta::json::Token::character('9')   ? jump(HUB + 560)
                       : input == catta::json::Token::character('8') ? jump(HUB + 559)
                       : input == catta::json::Token::character('7') ? jump(HUB + 558)
                       : input == catta::json::Token::character('6') ? jump(HUB + 557)
                       : input == catta::json::Token::character('5') ? jump(HUB + 556)
                       : input == catta::json::Token::character('4') ? jump(HUB + 555)
                       : input == catta::json::Token::character('3') ? jump(HUB + 554)
                       : input == catta::json::Token::character('2') ? jump(HUB + 553)
                       : input == catta::json::Token::character('1') ? jump(HUB + 552)
                       : input == catta::json::Token::character('0') ? jump(HUB + 551)
                                                                     : error();
            case HUB + 551:
                return input == catta::json::Token::closeString() ? close(157) : error();
            case HUB + 552:
                return input == catta::json::Token::closeString() ? close(158) : error();
            case HUB + 553:
                return input == catta::json::Token::closeString() ? close(159) : error();
            case HUB + 554:
                return input == catta::json::Token::closeString() ? close(160) : error();
            case HUB + 555:
                return input == catta::json::Token::closeString() ? close(161) : error();
            case HUB + 556:
                return input == catta::json::Token::closeString() ? close(162) : error();
            case HUB + 557:
                return input == catta::json::Token::closeString() ? close(163) : error();
            case HUB + 558:
                return input == catta::json::Token::closeString() ? close(164) : error();
            case HUB + 559:
                return input == catta::json::Token::closeString() ? close(165) : error();
            case HUB + 560:
                return input == catta::json::Token::closeString() ? close(166) : error();
            case HUB + 561:
                return input == catta::json::Token::character('9')   ? jump(HUB + 652)
                       : input == catta::json::Token::character('8') ? jump(HUB + 642)
                       : input == catta::json::Token::character('7') ? jump(HUB + 632)
                       : input == catta::json::Token::character('6') ? jump(HUB + 622)
                       : input == catta::json::Token::character('5') ? jump(HUB + 612)
                       : input == catta::json::Token::character('4') ? jump(HUB + 602)
                       : input == catta::json::Token::character('3') ? jump(HUB + 592)
                       : input == catta::json::Token::character('2') ? jump(HUB + 582)
                       : input == catta::json::Token::character('1') ? jump(HUB + 572)
                       : input == catta::json::Token::character('0') ? jump(HUB + 562)
                                                                     : error();
            case HUB + 562:
                return input == catta::json::Token::character('W')   ? jump(HUB + 567)
                       : input == catta::json::Token::character('R') ? jump(HUB + 563)
                                                                     : error();
            case HUB + 563:
                return input == catta::json::Token::character('e') ? jump(HUB + 564) : error();
            case HUB + 564:
                return input == catta::json::Token::character('a') ? jump(HUB + 565) : error();
            case HUB + 565:
                return input == catta::json::Token::character('d') ? jump(HUB + 566) : error();
            case HUB + 566:
                return input == catta::json::Token::closeString() ? close(141) : error();
            case HUB + 567:
                return input == catta::json::Token::character('r') ? jump(HUB + 568) : error();
            case HUB + 568:
                return input == catta::json::Token::character('i') ? jump(HUB + 569) : error();
            case HUB + 569:
                return input == catta::json::Token::character('t') ? jump(HUB + 570) : error();
            case HUB + 570:
                return input == catta::json::Token::character('e') ? jump(HUB + 571) : error();
            case HUB + 571:
                return input == catta::json::Token::closeString() ? close(167) : error();
            case HUB + 572:
                return input == catta::json::Token::character('W')   ? jump(HUB + 577)
                       : input == catta::json::Token::character('R') ? jump(HUB + 573)
                                                                     : error();
            case HUB + 573:
                return input == catta::json::Token::character('e') ? jump(HUB + 574) : error();
            case HUB + 574:
                return input == catta::json::Token::character('a') ? jump(HUB + 575) : error();
            case HUB + 575:
                return input == catta::json::Token::character('d') ? jump(HUB + 576) : error();
            case HUB + 576:
                return input == catta::json::Token::closeString() ? close(142) : error();
            case HUB + 577:
                return input == catta::json::Token::character('r') ? jump(HUB + 578) : error();
            case HUB + 578:
                return input == catta::json::Token::character('i') ? jump(HUB + 579) : error();
            case HUB + 579:
                return input == catta::json::Token::character('t') ? jump(HUB + 580) : error();
            case HUB + 580:
                return input == catta::json::Token::character('e') ? jump(HUB + 581) : error();
            case HUB + 581:
                return input == catta::json::Token::closeString() ? close(168) : error();
            case HUB + 582:
                return input == catta::json::Token::character('W')   ? jump(HUB + 587)
                       : input == catta::json::Token::character('R') ? jump(HUB + 583)
                                                                     : error();
            case HUB + 583:
                return input == catta::json::Token::character('e') ? jump(HUB + 584) : error();
            case HUB + 584:
                return input == catta::json::Token::character('a') ? jump(HUB + 585) : error();
            case HUB + 585:
                return input == catta::json::Token::character('d') ? jump(HUB + 586) : error();
            case HUB + 586:
                return input == catta::json::Token::closeString() ? close(143) : error();
            case HUB + 587:
                return input == catta::json::Token::character('r') ? jump(HUB + 588) : error();
            case HUB + 588:
                return input == catta::json::Token::character('i') ? jump(HUB + 589) : error();
            case HUB + 589:
                return input == catta::json::Token::character('t') ? jump(HUB + 590) : error();
            case HUB + 590:
                return input == catta::json::Token::character('e') ? jump(HUB + 591) : error();
            case HUB + 591:
                return input == catta::json::Token::closeString() ? close(169) : error();
            case HUB + 592:
                return input == catta::json::Token::character('W')   ? jump(HUB + 597)
                       : input == catta::json::Token::character('R') ? jump(HUB + 593)
                                                                     : error();
            case HUB + 593:
                return input == catta::json::Token::character('e') ? jump(HUB + 594) : error();
            case HUB + 594:
                return input == catta::json::Token::character('a') ? jump(HUB + 595) : error();
            case HUB + 595:
                return input == catta::json::Token::character('d') ? jump(HUB + 596) : error();
            case HUB + 596:
                return input == catta::json::Token::closeString() ? close(144) : error();
            case HUB + 597:
                return input == catta::json::Token::character('r') ? jump(HUB + 598) : error();
            case HUB + 598:
                return input == catta::json::Token::character('i') ? jump(HUB + 599) : error();
            case HUB + 599:
                return input == catta::json::Token::character('t') ? jump(HUB + 600) : error();
            case HUB + 600:
                return input == catta::json::Token::character('e') ? jump(HUB + 601) : error();
            case HUB + 601:
                return input == catta::json::Token::closeString() ? close(170) : error();
            case HUB + 602:
                return input == catta::json::Token::character('W')   ? jump(HUB + 607)
                       : input == catta::json::Token::character('R') ? jump(HUB + 603)
                                                                     : error();
            case HUB + 603:
                return input == catta::json::Token::character('e') ? jump(HUB + 604) : error();
            case HUB + 604:
                return input == catta::json::Token::character('a') ? jump(HUB + 605) : error();
            case HUB + 605:
                return input == catta::json::Token::character('d') ? jump(HUB + 606) : error();
            case HUB + 606:
                return input == catta::json::Token::closeString() ? close(145) : error();
            case HUB + 607:
                return input == catta::json::Token::character('r') ? jump(HUB + 608) : error();
            case HUB + 608:
                return input == catta::json::Token::character('i') ? jump(HUB + 609) : error();
            case HUB + 609:
                return input == catta::json::Token::character('t') ? jump(HUB + 610) : error();
            case HUB + 610:
                return input == catta::json::Token::character('e') ? jump(HUB + 611) : error();
            case HUB + 611:
                return input == catta::json::Token::closeString() ? close(171) : error();
            case HUB + 612:
                return input == catta::json::Token::character('W')   ? jump(HUB + 617)
                       : input == catta::json::Token::character('R') ? jump(HUB + 613)
                                                                     : error();
            case HUB + 613:
                return input == catta::json::Token::character('e') ? jump(HUB + 614) : error();
            case HUB + 614:
                return input == catta::json::Token::character('a') ? jump(HUB + 615) : error();
            case HUB + 615:
                return input == catta::json::Token::character('d') ? jump(HUB + 616) : error();
            case HUB + 616:
                return input == catta::json::Token::closeString() ? close(146) : error();
            case HUB + 617:
                return input == catta::json::Token::character('r') ? jump(HUB + 618) : error();
            case HUB + 618:
                return input == catta::json::Token::character('i') ? jump(HUB + 619) : error();
            case HUB + 619:
                return input == catta::json::Token::character('t') ? jump(HUB + 620) : error();
            case HUB + 620:
                return input == catta::json::Token::character('e') ? jump(HUB + 621) : error();
            case HUB + 621:
                return input == catta::json::Token::closeString() ? close(172) : error();
            case HUB + 622:
                return input == catta::json::Token::character('W')   ? jump(HUB + 627)
                       : input == catta::json::Token::character('R') ? jump(HUB + 623)
                                                                     : error();
            case HUB + 623:
                return input == catta::json::Token::character('e') ? jump(HUB + 624) : error();
            case HUB + 624:
                return input == catta::json::Token::character('a') ? jump(HUB + 625) : error();
            case HUB + 625:
                return input == catta::json::Token::character('d') ? jump(HUB + 626) : error();
            case HUB + 626:
                return input == catta::json::Token::closeString() ? close(147) : error();
            case HUB + 627:
                return input == catta::json::Token::character('r') ? jump(HUB + 628) : error();
            case HUB + 628:
                return input == catta::json::Token::character('i') ? jump(HUB + 629) : error();
            case HUB + 629:
                return input == catta::json::Token::character('t') ? jump(HUB + 630) : error();
            case HUB + 630:
                return input == catta::json::Token::character('e') ? jump(HUB + 631) : error();
            case HUB + 631:
                return input == catta::json::Token::closeString() ? close(173) : error();
            case HUB + 632:
                return input == catta::json::Token::character('W')   ? jump(HUB + 637)
                       : input == catta::json::Token::character('R') ? jump(HUB + 633)
                                                                     : error();
            case HUB + 633:
                return input == catta::json::Token::character('e') ? jump(HUB + 634) : error();
            case HUB + 634:
                return input == catta::json::Token::character('a') ? jump(HUB + 635) : error();
            case HUB + 635:
                return input == catta::json::Token::character('d') ? jump(HUB + 636) : error();
            case HUB + 636:
                return input == catta::json::Token::closeString() ? close(148) : error();
            case HUB + 637:
                return input == catta::json::Token::character('r') ? jump(HUB + 638) : error();
            case HUB + 638:
                return input == catta::json::Token::character('i') ? jump(HUB + 639) : error();
            case HUB + 639:
                return input == catta::json::Token::character('t') ? jump(HUB + 640) : error();
            case HUB + 640:
                return input == catta::json::Token::character('e') ? jump(HUB + 641) : error();
            case HUB + 641:
                return input == catta::json::Token::closeString() ? close(174) : error();
            case HUB + 642:
                return input == catta::json::Token::character('W')   ? jump(HUB + 647)
                       : input == catta::json::Token::character('R') ? jump(HUB + 643)
                                                                     : error();
            case HUB + 643:
                return input == catta::json::Token::character('e') ? jump(HUB + 644) : error();
            case HUB + 644:
                return input == catta::json::Token::character('a') ? jump(HUB + 645) : error();
            case HUB + 645:
                return input == catta::json::Token::character('d') ? jump(HUB + 646) : error();
            case HUB + 646:
                return input == catta::json::Token::closeString() ? close(149) : error();
            case HUB + 647:
                return input == catta::json::Token::character('r') ? jump(HUB + 648) : error();
            case HUB + 648:
                return input == catta::json::Token::character('i') ? jump(HUB + 649) : error();
            case HUB + 649:
                return input == catta::json::Token::character('t') ? jump(HUB + 650) : error();
            case HUB + 650:
                return input == catta::json::Token::character('e') ? jump(HUB + 651) : error();
            case HUB + 651:
                return input == catta::json::Token::closeString() ? close(175) : error();
            case HUB + 652:
                return input == catta::json::Token::character('W')   ? jump(HUB + 657)
                       : input == catta::json::Token::character('R') ? jump(HUB + 653)
                                                                     : error();
            case HUB + 653:
                return input == catta::json::Token::character('e') ? jump(HUB + 654) : error();
            case HUB + 654:
                return input == catta::json::Token::character('a') ? jump(HUB + 655) : error();
            case HUB + 655:
                return input == catta::json::Token::character('d') ? jump(HUB + 656) : error();
            case HUB + 656:
                return input == catta::json::Token::closeString() ? close(150) : error();
            case HUB + 657:
                return input == catta::json::Token::character('r') ? jump(HUB + 658) : error();
            case HUB + 658:
                return input == catta::json::Token::character('i') ? jump(HUB + 659) : error();
            case HUB + 659:
                return input == catta::json::Token::character('t') ? jump(HUB + 660) : error();
            case HUB + 660:
                return input == catta::json::Token::character('e') ? jump(HUB + 661) : error();
            case HUB + 661:
                return input == catta::json::Token::closeString() ? close(176) : error();
            case HUB + 662:
                return input == catta::json::Token::character('L')   ? jump(HUB + 676)
                       : input == catta::json::Token::character('H') ? jump(HUB + 663)
                                                                     : error();
            case HUB + 663:
                return input == catta::json::Token::character('i') ? jump(HUB + 664) : error();
            case HUB + 664:
                return input == catta::json::Token::character('g') ? jump(HUB + 665) : error();
            case HUB + 665:
                return input == catta::json::Token::character('h') ? jump(HUB + 666) : error();
            case HUB + 666:
                return input == catta::json::Token::character('W')   ? jump(HUB + 671)
                       : input == catta::json::Token::character('R') ? jump(HUB + 667)
                                                                     : error();
            case HUB + 667:
                return input == catta::json::Token::character('e') ? jump(HUB + 668) : error();
            case HUB + 668:
                return input == catta::json::Token::character('a') ? jump(HUB + 669) : error();
            case HUB + 669:
                return input == catta::json::Token::character('d') ? jump(HUB + 670) : error();
            case HUB + 670:
                return input == catta::json::Token::closeString() ? close(51) : error();
            case HUB + 671:
                return input == catta::json::Token::character('r') ? jump(HUB + 672) : error();
            case HUB + 672:
                return input == catta::json::Token::character('i') ? jump(HUB + 673) : error();
            case HUB + 673:
                return input == catta::json::Token::character('t') ? jump(HUB + 674) : error();
            case HUB + 674:
                return input == catta::json::Token::character('e') ? jump(HUB + 675) : error();
            case HUB + 675:
                return input == catta::json::Token::closeString() ? close(121) : error();
            case HUB + 676:
                return input == catta::json::Token::character('o') ? jump(HUB + 677) : error();
            case HUB + 677:
                return input == catta::json::Token::character('w') ? jump(HUB + 678) : error();
            case HUB + 678:
                return input == catta::json::Token::character('W')   ? jump(HUB + 683)
                       : input == catta::json::Token::character('R') ? jump(HUB + 679)
                                                                     : error();
            case HUB + 679:
                return input == catta::json::Token::character('e') ? jump(HUB + 680) : error();
            case HUB + 680:
                return input == catta::json::Token::character('a') ? jump(HUB + 681) : error();
            case HUB + 681:
                return input == catta::json::Token::character('d') ? jump(HUB + 682) : error();
            case HUB + 682:
                return input == catta::json::Token::closeString() ? close(50) : error();
            case HUB + 683:
                return input == catta::json::Token::character('r') ? jump(HUB + 684) : error();
            case HUB + 684:
                return input == catta::json::Token::character('i') ? jump(HUB + 685) : error();
            case HUB + 685:
                return input == catta::json::Token::character('t') ? jump(HUB + 686) : error();
            case HUB + 686:
                return input == catta::json::Token::character('e') ? jump(HUB + 687) : error();
            case HUB + 687:
                return input == catta::json::Token::closeString() ? close(120) : error();
            case HUB + 688:
                return input == catta::json::Token::character('n') ? jump(HUB + 689) : error();
            case HUB + 689:
                return input == catta::json::Token::character('a') ? jump(HUB + 690) : error();
            case HUB + 690:
                return input == catta::json::Token::character('b') ? jump(HUB + 691) : error();
            case HUB + 691:
                return input == catta::json::Token::character('l') ? jump(HUB + 692) : error();
            case HUB + 692:
                return input == catta::json::Token::character('e') ? jump(HUB + 693) : error();
            case HUB + 693:
                return input == catta::json::Token::character('W') ? jump(HUB + 694) : error();
            case HUB + 694:
                return input == catta::json::Token::character('r') ? jump(HUB + 695) : error();
            case HUB + 695:
                return input == catta::json::Token::character('i') ? jump(HUB + 696) : error();
            case HUB + 696:
                return input == catta::json::Token::character('t') ? jump(HUB + 697) : error();
            case HUB + 697:
                return input == catta::json::Token::character('e') ? jump(HUB + 698) : error();
            case HUB + 698:
                return input == catta::json::Token::character('P')   ? jump(HUB + 703)
                       : input == catta::json::Token::character('O') ? jump(HUB + 699)
                                                                     : error();
            case HUB + 699:
                return input == catta::json::Token::character('n') ? jump(HUB + 700) : error();
            case HUB + 700:
                return input == catta::json::Token::character('c') ? jump(HUB + 701) : error();
            case HUB + 701:
                return input == catta::json::Token::character('e') ? jump(HUB + 702) : error();
            case HUB + 702:
                return input == catta::json::Token::closeString() ? close(193) : error();
            case HUB + 703:
                return input == catta::json::Token::character('e') ? jump(HUB + 704) : error();
            case HUB + 704:
                return input == catta::json::Token::character('r') ? jump(HUB + 705) : error();
            case HUB + 705:
                return input == catta::json::Token::character('m') ? jump(HUB + 706) : error();
            case HUB + 706:
                return input == catta::json::Token::character('a') ? jump(HUB + 707) : error();
            case HUB + 707:
                return input == catta::json::Token::character('n') ? jump(HUB + 708) : error();
            case HUB + 708:
                return input == catta::json::Token::character('t') ? jump(HUB + 709) : error();
            case HUB + 709:
                return input == catta::json::Token::closeString() ? close(194) : error();
            case HUB + 710:
                return input == catta::json::Token::character('u')   ? jump(HUB + 725)
                       : input == catta::json::Token::character('i') ? jump(HUB + 711)
                                                                     : error();
            case HUB + 711:
                return input == catta::json::Token::character('l') ? jump(HUB + 712) : error();
            case HUB + 712:
                return input == catta::json::Token::character('t') ? jump(HUB + 713) : error();
            case HUB + 713:
                return input == catta::json::Token::character('e') ? jump(HUB + 714) : error();
            case HUB + 714:
                return input == catta::json::Token::character('r') ? jump(HUB + 715) : error();
            case HUB + 715:
                return input == catta::json::Token::character('W') ? jump(HUB + 716) : error();
            case HUB + 716:
                return input == catta::json::Token::character('i') ? jump(HUB + 717) : error();
            case HUB + 717:
                return input == catta::json::Token::character('n') ? jump(HUB + 718) : error();
            case HUB + 718:
                return input == catta::json::Token::character('d') ? jump(HUB + 719) : error();
            case HUB + 719:
                return input == catta::json::Token::character('C') ? jump(HUB + 720) : error();
            case HUB + 720:
                return input == catta::json::Token::character('u') ? jump(HUB + 721) : error();
            case HUB + 721:
                return input == catta::json::Token::character('r') ? jump(HUB + 722) : error();
            case HUB + 722:
                return input == catta::json::Token::character('v') ? jump(HUB + 723) : error();
            case HUB + 723:
                return input == catta::json::Token::character('e') ? jump(HUB + 724) : error();
            case HUB + 724:
                return input == catta::json::Token::closeString() ? close(79) : error();
            case HUB + 725:
                return input == catta::json::Token::character('n') ? jump(HUB + 726) : error();
            case HUB + 726:
                return input == catta::json::Token::character('c') ? jump(HUB + 727) : error();
            case HUB + 727:
                return input == catta::json::Token::character('t') ? jump(HUB + 728) : error();
            case HUB + 728:
                return input == catta::json::Token::character('i') ? jump(HUB + 729) : error();
            case HUB + 729:
                return input == catta::json::Token::character('o') ? jump(HUB + 730) : error();
            case HUB + 730:
                return input == catta::json::Token::character('n') ? jump(HUB + 731) : error();
            case HUB + 731:
                return input == catta::json::Token::character('W')   ? jump(HUB + 745)
                       : input == catta::json::Token::character('R') ? jump(HUB + 740)
                       : input == catta::json::Token::character('A') ? jump(HUB + 732)
                                                                     : error();
            case HUB + 732:
                return input == catta::json::Token::character('c') ? jump(HUB + 733) : error();
            case HUB + 733:
                return input == catta::json::Token::character('t') ? jump(HUB + 734) : error();
            case HUB + 734:
                return input == catta::json::Token::character('i') ? jump(HUB + 735) : error();
            case HUB + 735:
                return input == catta::json::Token::character('v') ? jump(HUB + 736) : error();
            case HUB + 736:
                return input == catta::json::Token::character('a') ? jump(HUB + 737) : error();
            case HUB + 737:
                return input == catta::json::Token::character('t') ? jump(HUB + 738) : error();
            case HUB + 738:
                return input == catta::json::Token::character('e') ? jump(HUB + 739) : error();
            case HUB + 739:
                return input == catta::json::Token::closeString() ? close(53) : error();
            case HUB + 740:
                return input == catta::json::Token::character('e') ? jump(HUB + 741) : error();
            case HUB + 741:
                return input == catta::json::Token::character('s') ? jump(HUB + 742) : error();
            case HUB + 742:
                return input == catta::json::Token::character('e') ? jump(HUB + 743) : error();
            case HUB + 743:
                return input == catta::json::Token::character('t') ? jump(HUB + 744) : error();
            case HUB + 744:
                return input == catta::json::Token::closeString() ? close(55) : error();
            case HUB + 745:
                return input == catta::json::Token::character('r') ? jump(HUB + 746) : error();
            case HUB + 746:
                return input == catta::json::Token::character('i') ? jump(HUB + 747) : error();
            case HUB + 747:
                return input == catta::json::Token::character('t') ? jump(HUB + 748) : error();
            case HUB + 748:
                return input == catta::json::Token::character('e') ? jump(HUB + 749) : error();
            case HUB + 749:
                return input == catta::json::Token::character('E') ? jump(HUB + 750) : error();
            case HUB + 750:
                return input == catta::json::Token::character('e') ? jump(HUB + 751) : error();
            case HUB + 751:
                return input == catta::json::Token::character('p') ? jump(HUB + 752) : error();
            case HUB + 752:
                return input == catta::json::Token::character('r') ? jump(HUB + 753) : error();
            case HUB + 753:
                return input == catta::json::Token::character('o') ? jump(HUB + 754) : error();
            case HUB + 754:
                return input == catta::json::Token::character('m') ? jump(HUB + 755) : error();
            case HUB + 755:
                return input == catta::json::Token::closeString() ? close(54) : error();
            case HUB + 756:
                return input == catta::json::Token::character('p')   ? jump(HUB + 761)
                       : input == catta::json::Token::character('o') ? jump(HUB + 757)
                                                                     : error();
            case HUB + 757:
                return input == catta::json::Token::character('d') ? jump(HUB + 758) : error();
            case HUB + 758:
                return input == catta::json::Token::character('u') ? jump(HUB + 759) : error();
            case HUB + 759:
                return input == catta::json::Token::character('s') ? jump(HUB + 760) : error();
            case HUB + 760:
                return input == catta::json::Token::closeString() ? close(43) : error();
            case HUB + 761:
                return input == catta::json::Token::character('p') ? jump(HUB + 762) : error();
            case HUB + 762:
                return input == catta::json::Token::character('S') ? jump(HUB + 763) : error();
            case HUB + 763:
                return input == catta::json::Token::character('t')   ? jump(HUB + 783)
                       : input == catta::json::Token::character('a') ? jump(HUB + 764)
                                                                     : error();
            case HUB + 764:
                return input == catta::json::Token::character('m') ? jump(HUB + 765) : error();
            case HUB + 765:
                return input == catta::json::Token::character('p') ? jump(HUB + 766) : error();
            case HUB + 766:
                return input == catta::json::Token::character('l') ? jump(HUB + 767) : error();
            case HUB + 767:
                return input == catta::json::Token::character('e') ? jump(HUB + 768) : error();
            case HUB + 768:
                return input == catta::json::Token::character('U')   ? jump(HUB + 776)
                       : input == catta::json::Token::character('D') ? jump(HUB + 769)
                                                                     : error();
            case HUB + 769:
                return input == catta::json::Token::character('a') ? jump(HUB + 770) : error();
            case HUB + 770:
                return input == catta::json::Token::character('c') ? jump(HUB + 771) : error();
            case HUB + 771:
                return input == catta::json::Token::character('3')   ? jump(HUB + 775)
                       : input == catta::json::Token::character('2') ? jump(HUB + 774)
                       : input == catta::json::Token::character('1') ? jump(HUB + 773)
                       : input == catta::json::Token::character('0') ? jump(HUB + 772)
                                                                     : error();
            case HUB + 772:
                return input == catta::json::Token::closeString() ? close(69) : error();
            case HUB + 773:
                return input == catta::json::Token::closeString() ? close(70) : error();
            case HUB + 774:
                return input == catta::json::Token::closeString() ? close(71) : error();
            case HUB + 775:
                return input == catta::json::Token::closeString() ? close(72) : error();
            case HUB + 776:
                return input == catta::json::Token::character('d') ? jump(HUB + 777) : error();
            case HUB + 777:
                return input == catta::json::Token::character('c') ? jump(HUB + 778) : error();
            case HUB + 778:
                return input == catta::json::Token::character('3')   ? jump(HUB + 782)
                       : input == catta::json::Token::character('2') ? jump(HUB + 781)
                       : input == catta::json::Token::character('1') ? jump(HUB + 780)
                       : input == catta::json::Token::character('0') ? jump(HUB + 779)
                                                                     : error();
            case HUB + 779:
                return input == catta::json::Token::closeString() ? close(73) : error();
            case HUB + 780:
                return input == catta::json::Token::closeString() ? close(74) : error();
            case HUB + 781:
                return input == catta::json::Token::closeString() ? close(75) : error();
            case HUB + 782:
                return input == catta::json::Token::closeString() ? close(76) : error();
            case HUB + 783:
                return input == catta::json::Token::character('e') ? jump(HUB + 784) : error();
            case HUB + 784:
                return input == catta::json::Token::character('p') ? jump(HUB + 785) : error();
            case HUB + 785:
                return input == catta::json::Token::character('U')   ? jump(HUB + 793)
                       : input == catta::json::Token::character('D') ? jump(HUB + 786)
                                                                     : error();
            case HUB + 786:
                return input == catta::json::Token::character('a') ? jump(HUB + 787) : error();
            case HUB + 787:
                return input == catta::json::Token::character('c') ? jump(HUB + 788) : error();
            case HUB + 788:
                return input == catta::json::Token::character('3')   ? jump(HUB + 792)
                       : input == catta::json::Token::character('2') ? jump(HUB + 791)
                       : input == catta::json::Token::character('1') ? jump(HUB + 790)
                       : input == catta::json::Token::character('0') ? jump(HUB + 789)
                                                                     : error();
            case HUB + 789:
                return input == catta::json::Token::closeString() ? close(61) : error();
            case HUB + 790:
                return input == catta::json::Token::closeString() ? close(62) : error();
            case HUB + 791:
                return input == catta::json::Token::closeString() ? close(63) : error();
            case HUB + 792:
                return input == catta::json::Token::closeString() ? close(64) : error();
            case HUB + 793:
                return input == catta::json::Token::character('d') ? jump(HUB + 794) : error();
            case HUB + 794:
                return input == catta::json::Token::character('c') ? jump(HUB + 795) : error();
            case HUB + 795:
                return input == catta::json::Token::character('3')   ? jump(HUB + 799)
                       : input == catta::json::Token::character('2') ? jump(HUB + 798)
                       : input == catta::json::Token::character('1') ? jump(HUB + 797)
                       : input == catta::json::Token::character('0') ? jump(HUB + 796)
                                                                     : error();
            case HUB + 796:
                return input == catta::json::Token::closeString() ? close(65) : error();
            case HUB + 797:
                return input == catta::json::Token::closeString() ? close(66) : error();
            case HUB + 798:
                return input == catta::json::Token::closeString() ? close(67) : error();
            case HUB + 799:
                return input == catta::json::Token::closeString() ? close(68) : error();
            case HUB + 800:
                return input == catta::json::Token::character('i') ? jump(HUB + 801) : error();
            case HUB + 801:
                return input == catta::json::Token::character('g') ? jump(HUB + 802) : error();
            case HUB + 802:
                return input == catta::json::Token::character('h') ? jump(HUB + 803) : error();
            case HUB + 803:
                return input == catta::json::Token::character('t') ? jump(HUB + 804) : error();
            case HUB + 804:
                return input == catta::json::Token::character('S') ? jump(HUB + 805) : error();
            case HUB + 805:
                return input == catta::json::Token::character('h') ? jump(HUB + 806) : error();
            case HUB + 806:
                return input == catta::json::Token::character('u') ? jump(HUB + 807) : error();
            case HUB + 807:
                return input == catta::json::Token::character('t') ? jump(HUB + 808) : error();
            case HUB + 808:
                return input == catta::json::Token::character('d') ? jump(HUB + 809) : error();
            case HUB + 809:
                return input == catta::json::Token::character('o') ? jump(HUB + 810) : error();
            case HUB + 810:
                return input == catta::json::Token::character('w') ? jump(HUB + 811) : error();
            case HUB + 811:
                return input == catta::json::Token::character('n') ? jump(HUB + 812) : error();
            case HUB + 812:
                return input == catta::json::Token::closeString() ? close(57) : error();
            case HUB + 813:
                return input == catta::json::Token::character('o')   ? jump(HUB + 817)
                       : input == catta::json::Token::character('m') ? jump(HUB + 814)
                                                                     : error();
            case HUB + 814:
                return input == catta::json::Token::character('a') ? jump(HUB + 815) : error();
            case HUB + 815:
                return input == catta::json::Token::character('x') ? jump(HUB + 816) : error();
            case HUB + 816:
                return input == catta::json::Token::closeString() ? close(58) : error();
            case HUB + 817:
                return input == catta::json::Token::character('w') ? jump(HUB + 818) : error();
            case HUB + 818:
                return input == catta::json::Token::character('e') ? jump(HUB + 819) : error();
            case HUB + 819:
                return input == catta::json::Token::character('r') ? jump(HUB + 820) : error();
            case HUB + 820:
                return input == catta::json::Token::character('L') ? jump(HUB + 821) : error();
            case HUB + 821:
                return input == catta::json::Token::character('i') ? jump(HUB + 822) : error();
            case HUB + 822:
                return input == catta::json::Token::character('m') ? jump(HUB + 823) : error();
            case HUB + 823:
                return input == catta::json::Token::character('i') ? jump(HUB + 824) : error();
            case HUB + 824:
                return input == catta::json::Token::character('t') ? jump(HUB + 825) : error();
            case HUB + 825:
                return input == catta::json::Token::character('S') ? jump(HUB + 826) : error();
            case HUB + 826:
                return input == catta::json::Token::character('a') ? jump(HUB + 827) : error();
            case HUB + 827:
                return input == catta::json::Token::character('f') ? jump(HUB + 828) : error();
            case HUB + 828:
                return input == catta::json::Token::character('t') ? jump(HUB + 829) : error();
            case HUB + 829:
                return input == catta::json::Token::character('y') ? jump(HUB + 830) : error();
            case HUB + 830:
                return input == catta::json::Token::character('M') ? jump(HUB + 831) : error();
            case HUB + 831:
                return input == catta::json::Token::character('o') ? jump(HUB + 832) : error();
            case HUB + 832:
                return input == catta::json::Token::character('d') ? jump(HUB + 833) : error();
            case HUB + 833:
                return input == catta::json::Token::character('e') ? jump(HUB + 834) : error();
            case HUB + 834:
                return input == catta::json::Token::closeString() ? close(113) : error();
            case HUB + 835:
                return input == catta::json::Token::character('e') ? jump(HUB + 836) : error();
            case HUB + 836:
                return input == catta::json::Token::character('d') ? jump(HUB + 837) : error();
            case HUB + 837:
                return input == catta::json::Token::character('u') ? jump(HUB + 838) : error();
            case HUB + 838:
                return input == catta::json::Token::character('c') ? jump(HUB + 839) : error();
            case HUB + 839:
                return input == catta::json::Token::character('t') ? jump(HUB + 840) : error();
            case HUB + 840:
                return input == catta::json::Token::character('i') ? jump(HUB + 841) : error();
            case HUB + 841:
                return input == catta::json::Token::character('o') ? jump(HUB + 842) : error();
            case HUB + 842:
                return input == catta::json::Token::character('n') ? jump(HUB + 843) : error();
            case HUB + 843:
                return input == catta::json::Token::closeString() ? close(77) : error();
            case HUB + 844:
                return input == catta::json::Token::character('t')   ? jump(HUB + 873)
                       : input == catta::json::Token::character('o') ? jump(HUB + 852)
                       : input == catta::json::Token::character('i') ? jump(HUB + 845)
                                                                     : error();
            case HUB + 845:
                return input == catta::json::Token::character('n') ? jump(HUB + 846) : error();
            case HUB + 846:
                return input == catta::json::Token::character('e') ? jump(HUB + 847) : error();
            case HUB + 847:
                return input == catta::json::Token::character('d') ? jump(HUB + 848) : error();
            case HUB + 848:
                return input == catta::json::Token::character('u') ? jump(HUB + 849) : error();
            case HUB + 849:
                return input == catta::json::Token::character('t') ? jump(HUB + 850) : error();
            case HUB + 850:
                return input == catta::json::Token::character('y') ? jump(HUB + 851) : error();
            case HUB + 851:
                return input == catta::json::Token::closeString() ? close(78) : error();
            case HUB + 852:
                return input == catta::json::Token::character('l') ? jump(HUB + 853) : error();
            case HUB + 853:
                return input == catta::json::Token::character('a') ? jump(HUB + 854) : error();
            case HUB + 854:
                return input == catta::json::Token::character('r') ? jump(HUB + 855) : error();
            case HUB + 855:
                return input == catta::json::Token::character('B') ? jump(HUB + 856) : error();
            case HUB + 856:
                return input == catta::json::Token::character('a') ? jump(HUB + 857) : error();
            case HUB + 857:
                return input == catta::json::Token::character('t') ? jump(HUB + 858) : error();
            case HUB + 858:
                return input == catta::json::Token::character('t') ? jump(HUB + 859) : error();
            case HUB + 859:
                return input == catta::json::Token::character('e') ? jump(HUB + 860) : error();
            case HUB + 860:
                return input == catta::json::Token::character('r') ? jump(HUB + 861) : error();
            case HUB + 861:
                return input == catta::json::Token::character('y') ? jump(HUB + 862) : error();
            case HUB + 862:
                return input == catta::json::Token::character('F') ? jump(HUB + 863) : error();
            case HUB + 863:
                return input == catta::json::Token::character('i') ? jump(HUB + 864) : error();
            case HUB + 864:
                return input == catta::json::Token::character('l') ? jump(HUB + 865) : error();
            case HUB + 865:
                return input == catta::json::Token::character('t') ? jump(HUB + 866) : error();
            case HUB + 866:
                return input == catta::json::Token::character('e') ? jump(HUB + 867) : error();
            case HUB + 867:
                return input == catta::json::Token::character('r') ? jump(HUB + 868) : error();
            case HUB + 868:
                return input == catta::json::Token::character('S') ? jump(HUB + 869) : error();
            case HUB + 869:
                return input == catta::json::Token::character('t') ? jump(HUB + 870) : error();
            case HUB + 870:
                return input == catta::json::Token::character('e') ? jump(HUB + 871) : error();
            case HUB + 871:
                return input == catta::json::Token::character('p') ? jump(HUB + 872) : error();
            case HUB + 872:
                return input == catta::json::Token::closeString() ? close(112) : error();
            case HUB + 873:
                return input == catta::json::Token::character('a') ? jump(HUB + 874) : error();
            case HUB + 874:
                return input == catta::json::Token::character('r') ? jump(HUB + 875) : error();
            case HUB + 875:
                return input == catta::json::Token::character('t') ? jump(HUB + 876) : error();
            case HUB + 876:
                return input == catta::json::Token::character('C') ? jump(HUB + 877) : error();
            case HUB + 877:
                return input == catta::json::Token::character('o') ? jump(HUB + 878) : error();
            case HUB + 878:
                return input == catta::json::Token::character('u') ? jump(HUB + 879) : error();
            case HUB + 879:
                return input == catta::json::Token::character('n') ? jump(HUB + 880) : error();
            case HUB + 880:
                return input == catta::json::Token::character('t') ? jump(HUB + 881) : error();
            case HUB + 881:
                return input == catta::json::Token::character('d') ? jump(HUB + 882) : error();
            case HUB + 882:
                return input == catta::json::Token::character('o') ? jump(HUB + 883) : error();
            case HUB + 883:
                return input == catta::json::Token::character('w') ? jump(HUB + 884) : error();
            case HUB + 884:
                return input == catta::json::Token::character('n') ? jump(HUB + 885) : error();
            case HUB + 885:
                return input == catta::json::Token::closeString() ? close(56) : error();
            case HUB + 886:
                return input == catta::json::Token::character('r') ? jump(HUB + 887) : error();
            case HUB + 887:
                return input == catta::json::Token::character('a') ? jump(HUB + 888) : error();
            case HUB + 888:
                return input == catta::json::Token::character('c') ? jump(HUB + 889) : error();
            case HUB + 889:
                return input == catta::json::Token::character('k') ? jump(HUB + 890) : error();
            case HUB + 890:
                return input == catta::json::Token::character('i') ? jump(HUB + 891) : error();
            case HUB + 891:
                return input == catta::json::Token::character('n') ? jump(HUB + 892) : error();
            case HUB + 892:
                return input == catta::json::Token::character('g') ? jump(HUB + 893) : error();
            case HUB + 893:
                return input == catta::json::Token::character('S') ? jump(HUB + 894) : error();
            case HUB + 894:
                return input == catta::json::Token::character('e') ? jump(HUB + 895) : error();
            case HUB + 895:
                return input == catta::json::Token::character('l') ? jump(HUB + 896) : error();
            case HUB + 896:
                return input == catta::json::Token::character('e') ? jump(HUB + 897) : error();
            case HUB + 897:
                return input == catta::json::Token::character('c') ? jump(HUB + 898) : error();
            case HUB + 898:
                return input == catta::json::Token::character('t') ? jump(HUB + 899) : error();
            case HUB + 899:
                return input == catta::json::Token::character('i') ? jump(HUB + 900) : error();
            case HUB + 900:
                return input == catta::json::Token::character('o') ? jump(HUB + 901) : error();
            case HUB + 901:
                return input == catta::json::Token::character('n') ? jump(HUB + 902) : error();
            case HUB + 902:
                return input == catta::json::Token::closeString() ? close(52) : error();
            case HUB + 903:
                return input == catta::json::Token::character('p')   ? jump(HUB + 927)
                       : input == catta::json::Token::character('m') ? jump(HUB + 904)
                                                                     : error();
            case HUB + 904:
                return input == catta::json::Token::character('i')   ? jump(HUB + 916)
                       : input == catta::json::Token::character('a') ? jump(HUB + 905)
                                                                     : error();
            case HUB + 905:
                return input == catta::json::Token::character('x') ? jump(HUB + 906) : error();
            case HUB + 906:
                return input == catta::json::Token::character('W')   ? jump(HUB + 911)
                       : input == catta::json::Token::character('R') ? jump(HUB + 907)
                                                                     : error();
            case HUB + 907:
                return input == catta::json::Token::character('e') ? jump(HUB + 908) : error();
            case HUB + 908:
                return input == catta::json::Token::character('a') ? jump(HUB + 909) : error();
            case HUB + 909:
                return input == catta::json::Token::character('d') ? jump(HUB + 910) : error();
            case HUB + 910:
                return input == catta::json::Token::closeString() ? close(45) : error();
            case HUB + 911:
                return input == catta::json::Token::character('r') ? jump(HUB + 912) : error();
            case HUB + 912:
                return input == catta::json::Token::character('i') ? jump(HUB + 913) : error();
            case HUB + 913:
                return input == catta::json::Token::character('t') ? jump(HUB + 914) : error();
            case HUB + 914:
                return input == catta::json::Token::character('e') ? jump(HUB + 915) : error();
            case HUB + 915:
                return input == catta::json::Token::closeString() ? close(115) : error();
            case HUB + 916:
                return input == catta::json::Token::character('n') ? jump(HUB + 917) : error();
            case HUB + 917:
                return input == catta::json::Token::character('W')   ? jump(HUB + 922)
                       : input == catta::json::Token::character('R') ? jump(HUB + 918)
                                                                     : error();
            case HUB + 918:
                return input == catta::json::Token::character('e') ? jump(HUB + 919) : error();
            case HUB + 919:
                return input == catta::json::Token::character('a') ? jump(HUB + 920) : error();
            case HUB + 920:
                return input == catta::json::Token::character('d') ? jump(HUB + 921) : error();
            case HUB + 921:
                return input == catta::json::Token::closeString() ? close(44) : error();
            case HUB + 922:
                return input == catta::json::Token::character('r') ? jump(HUB + 923) : error();
            case HUB + 923:
                return input == catta::json::Token::character('i') ? jump(HUB + 924) : error();
            case HUB + 924:
                return input == catta::json::Token::character('t') ? jump(HUB + 925) : error();
            case HUB + 925:
                return input == catta::json::Token::character('e') ? jump(HUB + 926) : error();
            case HUB + 926:
                return input == catta::json::Token::closeString() ? close(114) : error();
            case HUB + 927:
                return input == catta::json::Token::character('t') ? jump(HUB + 928) : error();
            case HUB + 928:
                return input == catta::json::Token::character('i') ? jump(HUB + 929) : error();
            case HUB + 929:
                return input == catta::json::Token::character('m') ? jump(HUB + 930) : error();
            case HUB + 930:
                return input == catta::json::Token::character('e') ? jump(HUB + 931) : error();
            case HUB + 931:
                return input == catta::json::Token::closeString() ? close(60) : error();
            case HUB + 932:
                return input == catta::json::Token::character('o') ? jump(HUB + 933) : error();
            case HUB + 933:
                return input == catta::json::Token::character('l') ? jump(HUB + 934) : error();
            case HUB + 934:
                return input == catta::json::Token::character('t') ? jump(HUB + 935) : error();
            case HUB + 935:
                return input == catta::json::Token::character('a') ? jump(HUB + 936) : error();
            case HUB + 936:
                return input == catta::json::Token::character('g') ? jump(HUB + 937) : error();
            case HUB + 937:
                return input == catta::json::Token::character('e') ? jump(HUB + 938) : error();
            case HUB + 938:
                return input == catta::json::Token::character('D') ? jump(HUB + 939) : error();
            case HUB + 939:
                return input == catta::json::Token::character('c') ? jump(HUB + 940) : error();
            case HUB + 940:
                return input == catta::json::Token::character('S') ? jump(HUB + 941) : error();
            case HUB + 941:
                return input == catta::json::Token::character('t') ? jump(HUB + 942) : error();
            case HUB + 942:
                return input == catta::json::Token::character('a') ? jump(HUB + 943) : error();
            case HUB + 943:
                return input == catta::json::Token::character('r') ? jump(HUB + 944) : error();
            case HUB + 944:
                return input == catta::json::Token::character('t') ? jump(HUB + 945) : error();
            case HUB + 945:
                return input == catta::json::Token::character('W')   ? jump(HUB + 950)
                       : input == catta::json::Token::character('R') ? jump(HUB + 946)
                                                                     : error();
            case HUB + 946:
                return input == catta::json::Token::character('e') ? jump(HUB + 947) : error();
            case HUB + 947:
                return input == catta::json::Token::character('a') ? jump(HUB + 948) : error();
            case HUB + 948:
                return input == catta::json::Token::character('d') ? jump(HUB + 949) : error();
            case HUB + 949:
                return input == catta::json::Token::closeString() ? close(46) : error();
            case HUB + 950:
                return input == catta::json::Token::character('r') ? jump(HUB + 951) : error();
            case HUB + 951:
                return input == catta::json::Token::character('i') ? jump(HUB + 952) : error();
            case HUB + 952:
                return input == catta::json::Token::character('t') ? jump(HUB + 953) : error();
            case HUB + 953:
                return input == catta::json::Token::character('e') ? jump(HUB + 954) : error();
            case HUB + 954:
                return input == catta::json::Token::closeString() ? close(116) : error();
            case HUB + 955:
                return input == catta::json::Token::character('i') ? jump(HUB + 956) : error();
            case HUB + 956:
                return input == catta::json::Token::character('n') ? jump(HUB + 957) : error();
            case HUB + 957:
                return input == catta::json::Token::character('d') ? jump(HUB + 958) : error();
            case HUB + 958:
                return input == catta::json::Token::character('C') ? jump(HUB + 959) : error();
            case HUB + 959:
                return input == catta::json::Token::character('u') ? jump(HUB + 960) : error();
            case HUB + 960:
                return input == catta::json::Token::character('r') ? jump(HUB + 961) : error();
            case HUB + 961:
                return input == catta::json::Token::character('v') ? jump(HUB + 962) : error();
            case HUB + 962:
                return input == catta::json::Token::character('e') ? jump(HUB + 963) : error();
            case HUB + 963:
                return input == catta::json::Token::character('Y')   ? jump(HUB + 1127)
                       : input == catta::json::Token::character('X') ? jump(HUB + 964)
                                                                     : error();
            case HUB + 964:
                return input == catta::json::Token::character('1')   ? jump(HUB + 1066)
                       : input == catta::json::Token::character('0') ? jump(HUB + 965)
                                                                     : error();
            case HUB + 965:
                return input == catta::json::Token::character('9')   ? jump(HUB + 1056)
                       : input == catta::json::Token::character('8') ? jump(HUB + 1046)
                       : input == catta::json::Token::character('7') ? jump(HUB + 1036)
                       : input == catta::json::Token::character('6') ? jump(HUB + 1026)
                       : input == catta::json::Token::character('5') ? jump(HUB + 1016)
                       : input == catta::json::Token::character('4') ? jump(HUB + 1006)
                       : input == catta::json::Token::character('3') ? jump(HUB + 996)
                       : input == catta::json::Token::character('2') ? jump(HUB + 986)
                       : input == catta::json::Token::character('1') ? jump(HUB + 976)
                       : input == catta::json::Token::character('0') ? jump(HUB + 966)
                                                                     : error();
            case HUB + 966:
                return input == catta::json::Token::character('w')   ? jump(HUB + 971)
                       : input == catta::json::Token::character('r') ? jump(HUB + 967)
                                                                     : error();
            case HUB + 967:
                return input == catta::json::Token::character('e') ? jump(HUB + 968) : error();
            case HUB + 968:
                return input == catta::json::Token::character('a') ? jump(HUB + 969) : error();
            case HUB + 969:
                return input == catta::json::Token::character('d') ? jump(HUB + 970) : error();
            case HUB + 970:
                return input == catta::json::Token::closeString() ? close(80) : error();
            case HUB + 971:
                return input == catta::json::Token::character('r') ? jump(HUB + 972) : error();
            case HUB + 972:
                return input == catta::json::Token::character('i') ? jump(HUB + 973) : error();
            case HUB + 973:
                return input == catta::json::Token::character('t') ? jump(HUB + 974) : error();
            case HUB + 974:
                return input == catta::json::Token::character('e') ? jump(HUB + 975) : error();
            case HUB + 975:
                return input == catta::json::Token::closeString() ? close(177) : error();
            case HUB + 976:
                return input == catta::json::Token::character('w')   ? jump(HUB + 981)
                       : input == catta::json::Token::character('r') ? jump(HUB + 977)
                                                                     : error();
            case HUB + 977:
                return input == catta::json::Token::character('e') ? jump(HUB + 978) : error();
            case HUB + 978:
                return input == catta::json::Token::character('a') ? jump(HUB + 979) : error();
            case HUB + 979:
                return input == catta::json::Token::character('d') ? jump(HUB + 980) : error();
            case HUB + 980:
                return input == catta::json::Token::closeString() ? close(81) : error();
            case HUB + 981:
                return input == catta::json::Token::character('r') ? jump(HUB + 982) : error();
            case HUB + 982:
                return input == catta::json::Token::character('i') ? jump(HUB + 983) : error();
            case HUB + 983:
                return input == catta::json::Token::character('t') ? jump(HUB + 984) : error();
            case HUB + 984:
                return input == catta::json::Token::character('e') ? jump(HUB + 985) : error();
            case HUB + 985:
                return input == catta::json::Token::closeString() ? close(178) : error();
            case HUB + 986:
                return input == catta::json::Token::character('w')   ? jump(HUB + 991)
                       : input == catta::json::Token::character('r') ? jump(HUB + 987)
                                                                     : error();
            case HUB + 987:
                return input == catta::json::Token::character('e') ? jump(HUB + 988) : error();
            case HUB + 988:
                return input == catta::json::Token::character('a') ? jump(HUB + 989) : error();
            case HUB + 989:
                return input == catta::json::Token::character('d') ? jump(HUB + 990) : error();
            case HUB + 990:
                return input == catta::json::Token::closeString() ? close(82) : error();
            case HUB + 991:
                return input == catta::json::Token::character('r') ? jump(HUB + 992) : error();
            case HUB + 992:
                return input == catta::json::Token::character('i') ? jump(HUB + 993) : error();
            case HUB + 993:
                return input == catta::json::Token::character('t') ? jump(HUB + 994) : error();
            case HUB + 994:
                return input == catta::json::Token::character('e') ? jump(HUB + 995) : error();
            case HUB + 995:
                return input == catta::json::Token::closeString() ? close(179) : error();
            case HUB + 996:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1001)
                       : input == catta::json::Token::character('r') ? jump(HUB + 997)
                                                                     : error();
            case HUB + 997:
                return input == catta::json::Token::character('e') ? jump(HUB + 998) : error();
            case HUB + 998:
                return input == catta::json::Token::character('a') ? jump(HUB + 999) : error();
            case HUB + 999:
                return input == catta::json::Token::character('d') ? jump(HUB + 1000) : error();
            case HUB + 1000:
                return input == catta::json::Token::closeString() ? close(83) : error();
            case HUB + 1001:
                return input == catta::json::Token::character('r') ? jump(HUB + 1002) : error();
            case HUB + 1002:
                return input == catta::json::Token::character('i') ? jump(HUB + 1003) : error();
            case HUB + 1003:
                return input == catta::json::Token::character('t') ? jump(HUB + 1004) : error();
            case HUB + 1004:
                return input == catta::json::Token::character('e') ? jump(HUB + 1005) : error();
            case HUB + 1005:
                return input == catta::json::Token::closeString() ? close(180) : error();
            case HUB + 1006:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1011)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1007)
                                                                     : error();
            case HUB + 1007:
                return input == catta::json::Token::character('e') ? jump(HUB + 1008) : error();
            case HUB + 1008:
                return input == catta::json::Token::character('a') ? jump(HUB + 1009) : error();
            case HUB + 1009:
                return input == catta::json::Token::character('d') ? jump(HUB + 1010) : error();
            case HUB + 1010:
                return input == catta::json::Token::closeString() ? close(84) : error();
            case HUB + 1011:
                return input == catta::json::Token::character('r') ? jump(HUB + 1012) : error();
            case HUB + 1012:
                return input == catta::json::Token::character('i') ? jump(HUB + 1013) : error();
            case HUB + 1013:
                return input == catta::json::Token::character('t') ? jump(HUB + 1014) : error();
            case HUB + 1014:
                return input == catta::json::Token::character('e') ? jump(HUB + 1015) : error();
            case HUB + 1015:
                return input == catta::json::Token::closeString() ? close(181) : error();
            case HUB + 1016:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1021)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1017)
                                                                     : error();
            case HUB + 1017:
                return input == catta::json::Token::character('e') ? jump(HUB + 1018) : error();
            case HUB + 1018:
                return input == catta::json::Token::character('a') ? jump(HUB + 1019) : error();
            case HUB + 1019:
                return input == catta::json::Token::character('d') ? jump(HUB + 1020) : error();
            case HUB + 1020:
                return input == catta::json::Token::closeString() ? close(85) : error();
            case HUB + 1021:
                return input == catta::json::Token::character('r') ? jump(HUB + 1022) : error();
            case HUB + 1022:
                return input == catta::json::Token::character('i') ? jump(HUB + 1023) : error();
            case HUB + 1023:
                return input == catta::json::Token::character('t') ? jump(HUB + 1024) : error();
            case HUB + 1024:
                return input == catta::json::Token::character('e') ? jump(HUB + 1025) : error();
            case HUB + 1025:
                return input == catta::json::Token::closeString() ? close(182) : error();
            case HUB + 1026:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1031)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1027)
                                                                     : error();
            case HUB + 1027:
                return input == catta::json::Token::character('e') ? jump(HUB + 1028) : error();
            case HUB + 1028:
                return input == catta::json::Token::character('a') ? jump(HUB + 1029) : error();
            case HUB + 1029:
                return input == catta::json::Token::character('d') ? jump(HUB + 1030) : error();
            case HUB + 1030:
                return input == catta::json::Token::closeString() ? close(86) : error();
            case HUB + 1031:
                return input == catta::json::Token::character('r') ? jump(HUB + 1032) : error();
            case HUB + 1032:
                return input == catta::json::Token::character('i') ? jump(HUB + 1033) : error();
            case HUB + 1033:
                return input == catta::json::Token::character('t') ? jump(HUB + 1034) : error();
            case HUB + 1034:
                return input == catta::json::Token::character('e') ? jump(HUB + 1035) : error();
            case HUB + 1035:
                return input == catta::json::Token::closeString() ? close(183) : error();
            case HUB + 1036:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1041)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1037)
                                                                     : error();
            case HUB + 1037:
                return input == catta::json::Token::character('e') ? jump(HUB + 1038) : error();
            case HUB + 1038:
                return input == catta::json::Token::character('a') ? jump(HUB + 1039) : error();
            case HUB + 1039:
                return input == catta::json::Token::character('d') ? jump(HUB + 1040) : error();
            case HUB + 1040:
                return input == catta::json::Token::closeString() ? close(87) : error();
            case HUB + 1041:
                return input == catta::json::Token::character('r') ? jump(HUB + 1042) : error();
            case HUB + 1042:
                return input == catta::json::Token::character('i') ? jump(HUB + 1043) : error();
            case HUB + 1043:
                return input == catta::json::Token::character('t') ? jump(HUB + 1044) : error();
            case HUB + 1044:
                return input == catta::json::Token::character('e') ? jump(HUB + 1045) : error();
            case HUB + 1045:
                return input == catta::json::Token::closeString() ? close(184) : error();
            case HUB + 1046:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1051)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1047)
                                                                     : error();
            case HUB + 1047:
                return input == catta::json::Token::character('e') ? jump(HUB + 1048) : error();
            case HUB + 1048:
                return input == catta::json::Token::character('a') ? jump(HUB + 1049) : error();
            case HUB + 1049:
                return input == catta::json::Token::character('d') ? jump(HUB + 1050) : error();
            case HUB + 1050:
                return input == catta::json::Token::closeString() ? close(88) : error();
            case HUB + 1051:
                return input == catta::json::Token::character('r') ? jump(HUB + 1052) : error();
            case HUB + 1052:
                return input == catta::json::Token::character('i') ? jump(HUB + 1053) : error();
            case HUB + 1053:
                return input == catta::json::Token::character('t') ? jump(HUB + 1054) : error();
            case HUB + 1054:
                return input == catta::json::Token::character('e') ? jump(HUB + 1055) : error();
            case HUB + 1055:
                return input == catta::json::Token::closeString() ? close(185) : error();
            case HUB + 1056:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1061)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1057)
                                                                     : error();
            case HUB + 1057:
                return input == catta::json::Token::character('e') ? jump(HUB + 1058) : error();
            case HUB + 1058:
                return input == catta::json::Token::character('a') ? jump(HUB + 1059) : error();
            case HUB + 1059:
                return input == catta::json::Token::character('d') ? jump(HUB + 1060) : error();
            case HUB + 1060:
                return input == catta::json::Token::closeString() ? close(89) : error();
            case HUB + 1061:
                return input == catta::json::Token::character('r') ? jump(HUB + 1062) : error();
            case HUB + 1062:
                return input == catta::json::Token::character('i') ? jump(HUB + 1063) : error();
            case HUB + 1063:
                return input == catta::json::Token::character('t') ? jump(HUB + 1064) : error();
            case HUB + 1064:
                return input == catta::json::Token::character('e') ? jump(HUB + 1065) : error();
            case HUB + 1065:
                return input == catta::json::Token::closeString() ? close(186) : error();
            case HUB + 1066:
                return input == catta::json::Token::character('5')   ? jump(HUB + 1117)
                       : input == catta::json::Token::character('4') ? jump(HUB + 1107)
                       : input == catta::json::Token::character('3') ? jump(HUB + 1097)
                       : input == catta::json::Token::character('2') ? jump(HUB + 1087)
                       : input == catta::json::Token::character('1') ? jump(HUB + 1077)
                       : input == catta::json::Token::character('0') ? jump(HUB + 1067)
                                                                     : error();
            case HUB + 1067:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1072)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1068)
                                                                     : error();
            case HUB + 1068:
                return input == catta::json::Token::character('e') ? jump(HUB + 1069) : error();
            case HUB + 1069:
                return input == catta::json::Token::character('a') ? jump(HUB + 1070) : error();
            case HUB + 1070:
                return input == catta::json::Token::character('d') ? jump(HUB + 1071) : error();
            case HUB + 1071:
                return input == catta::json::Token::closeString() ? close(90) : error();
            case HUB + 1072:
                return input == catta::json::Token::character('r') ? jump(HUB + 1073) : error();
            case HUB + 1073:
                return input == catta::json::Token::character('i') ? jump(HUB + 1074) : error();
            case HUB + 1074:
                return input == catta::json::Token::character('t') ? jump(HUB + 1075) : error();
            case HUB + 1075:
                return input == catta::json::Token::character('e') ? jump(HUB + 1076) : error();
            case HUB + 1076:
                return input == catta::json::Token::closeString() ? close(187) : error();
            case HUB + 1077:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1082)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1078)
                                                                     : error();
            case HUB + 1078:
                return input == catta::json::Token::character('e') ? jump(HUB + 1079) : error();
            case HUB + 1079:
                return input == catta::json::Token::character('a') ? jump(HUB + 1080) : error();
            case HUB + 1080:
                return input == catta::json::Token::character('d') ? jump(HUB + 1081) : error();
            case HUB + 1081:
                return input == catta::json::Token::closeString() ? close(91) : error();
            case HUB + 1082:
                return input == catta::json::Token::character('r') ? jump(HUB + 1083) : error();
            case HUB + 1083:
                return input == catta::json::Token::character('i') ? jump(HUB + 1084) : error();
            case HUB + 1084:
                return input == catta::json::Token::character('t') ? jump(HUB + 1085) : error();
            case HUB + 1085:
                return input == catta::json::Token::character('e') ? jump(HUB + 1086) : error();
            case HUB + 1086:
                return input == catta::json::Token::closeString() ? close(188) : error();
            case HUB + 1087:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1092)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1088)
                                                                     : error();
            case HUB + 1088:
                return input == catta::json::Token::character('e') ? jump(HUB + 1089) : error();
            case HUB + 1089:
                return input == catta::json::Token::character('a') ? jump(HUB + 1090) : error();
            case HUB + 1090:
                return input == catta::json::Token::character('d') ? jump(HUB + 1091) : error();
            case HUB + 1091:
                return input == catta::json::Token::closeString() ? close(92) : error();
            case HUB + 1092:
                return input == catta::json::Token::character('r') ? jump(HUB + 1093) : error();
            case HUB + 1093:
                return input == catta::json::Token::character('i') ? jump(HUB + 1094) : error();
            case HUB + 1094:
                return input == catta::json::Token::character('t') ? jump(HUB + 1095) : error();
            case HUB + 1095:
                return input == catta::json::Token::character('e') ? jump(HUB + 1096) : error();
            case HUB + 1096:
                return input == catta::json::Token::closeString() ? close(189) : error();
            case HUB + 1097:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1102)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1098)
                                                                     : error();
            case HUB + 1098:
                return input == catta::json::Token::character('e') ? jump(HUB + 1099) : error();
            case HUB + 1099:
                return input == catta::json::Token::character('a') ? jump(HUB + 1100) : error();
            case HUB + 1100:
                return input == catta::json::Token::character('d') ? jump(HUB + 1101) : error();
            case HUB + 1101:
                return input == catta::json::Token::closeString() ? close(93) : error();
            case HUB + 1102:
                return input == catta::json::Token::character('r') ? jump(HUB + 1103) : error();
            case HUB + 1103:
                return input == catta::json::Token::character('i') ? jump(HUB + 1104) : error();
            case HUB + 1104:
                return input == catta::json::Token::character('t') ? jump(HUB + 1105) : error();
            case HUB + 1105:
                return input == catta::json::Token::character('e') ? jump(HUB + 1106) : error();
            case HUB + 1106:
                return input == catta::json::Token::closeString() ? close(190) : error();
            case HUB + 1107:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1112)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1108)
                                                                     : error();
            case HUB + 1108:
                return input == catta::json::Token::character('e') ? jump(HUB + 1109) : error();
            case HUB + 1109:
                return input == catta::json::Token::character('a') ? jump(HUB + 1110) : error();
            case HUB + 1110:
                return input == catta::json::Token::character('d') ? jump(HUB + 1111) : error();
            case HUB + 1111:
                return input == catta::json::Token::closeString() ? close(94) : error();
            case HUB + 1112:
                return input == catta::json::Token::character('r') ? jump(HUB + 1113) : error();
            case HUB + 1113:
                return input == catta::json::Token::character('i') ? jump(HUB + 1114) : error();
            case HUB + 1114:
                return input == catta::json::Token::character('t') ? jump(HUB + 1115) : error();
            case HUB + 1115:
                return input == catta::json::Token::character('e') ? jump(HUB + 1116) : error();
            case HUB + 1116:
                return input == catta::json::Token::closeString() ? close(191) : error();
            case HUB + 1117:
                return input == catta::json::Token::character('w')   ? jump(HUB + 1122)
                       : input == catta::json::Token::character('r') ? jump(HUB + 1118)
                                                                     : error();
            case HUB + 1118:
                return input == catta::json::Token::character('e') ? jump(HUB + 1119) : error();
            case HUB + 1119:
                return input == catta::json::Token::character('a') ? jump(HUB + 1120) : error();
            case HUB + 1120:
                return input == catta::json::Token::character('d') ? jump(HUB + 1121) : error();
            case HUB + 1121:
                return input == catta::json::Token::closeString() ? close(95) : error();
            case HUB + 1122:
                return input == catta::json::Token::character('r') ? jump(HUB + 1123) : error();
            case HUB + 1123:
                return input == catta::json::Token::character('i') ? jump(HUB + 1124) : error();
            case HUB + 1124:
                return input == catta::json::Token::character('t') ? jump(HUB + 1125) : error();
            case HUB + 1125:
                return input == catta::json::Token::character('e') ? jump(HUB + 1126) : error();
            case HUB + 1126:
                return input == catta::json::Token::closeString() ? close(192) : error();
            case HUB + 1127:
                return input == catta::json::Token::character('1')   ? jump(HUB + 1229)
                       : input == catta::json::Token::character('0') ? jump(HUB + 1128)
                                                                     : error();
            case HUB + 1128:
                return input == catta::json::Token::character('9')   ? jump(HUB + 1219)
                       : input == catta::json::Token::character('8') ? jump(HUB + 1209)
                       : input == catta::json::Token::character('7') ? jump(HUB + 1199)
                       : input == catta::json::Token::character('6') ? jump(HUB + 1189)
                       : input == catta::json::Token::character('5') ? jump(HUB + 1179)
                       : input == catta::json::Token::character('4') ? jump(HUB + 1169)
                       : input == catta::json::Token::character('3') ? jump(HUB + 1159)
                       : input == catta::json::Token::character('2') ? jump(HUB + 1149)
                       : input == catta::json::Token::character('1') ? jump(HUB + 1139)
                       : input == catta::json::Token::character('0') ? jump(HUB + 1129)
                                                                     : error();
            case HUB + 1129:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1134)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1130)
                                                                     : error();
            case HUB + 1130:
                return input == catta::json::Token::character('e') ? jump(HUB + 1131) : error();
            case HUB + 1131:
                return input == catta::json::Token::character('a') ? jump(HUB + 1132) : error();
            case HUB + 1132:
                return input == catta::json::Token::character('d') ? jump(HUB + 1133) : error();
            case HUB + 1133:
                return input == catta::json::Token::closeString() ? close(96) : error();
            case HUB + 1134:
                return input == catta::json::Token::character('r') ? jump(HUB + 1135) : error();
            case HUB + 1135:
                return input == catta::json::Token::character('i') ? jump(HUB + 1136) : error();
            case HUB + 1136:
                return input == catta::json::Token::character('t') ? jump(HUB + 1137) : error();
            case HUB + 1137:
                return input == catta::json::Token::character('e') ? jump(HUB + 1138) : error();
            case HUB + 1138:
                return input == catta::json::Token::closeString() ? close(122) : error();
            case HUB + 1139:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1144)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1140)
                                                                     : error();
            case HUB + 1140:
                return input == catta::json::Token::character('e') ? jump(HUB + 1141) : error();
            case HUB + 1141:
                return input == catta::json::Token::character('a') ? jump(HUB + 1142) : error();
            case HUB + 1142:
                return input == catta::json::Token::character('d') ? jump(HUB + 1143) : error();
            case HUB + 1143:
                return input == catta::json::Token::closeString() ? close(97) : error();
            case HUB + 1144:
                return input == catta::json::Token::character('r') ? jump(HUB + 1145) : error();
            case HUB + 1145:
                return input == catta::json::Token::character('i') ? jump(HUB + 1146) : error();
            case HUB + 1146:
                return input == catta::json::Token::character('t') ? jump(HUB + 1147) : error();
            case HUB + 1147:
                return input == catta::json::Token::character('e') ? jump(HUB + 1148) : error();
            case HUB + 1148:
                return input == catta::json::Token::closeString() ? close(123) : error();
            case HUB + 1149:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1154)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1150)
                                                                     : error();
            case HUB + 1150:
                return input == catta::json::Token::character('e') ? jump(HUB + 1151) : error();
            case HUB + 1151:
                return input == catta::json::Token::character('a') ? jump(HUB + 1152) : error();
            case HUB + 1152:
                return input == catta::json::Token::character('d') ? jump(HUB + 1153) : error();
            case HUB + 1153:
                return input == catta::json::Token::closeString() ? close(98) : error();
            case HUB + 1154:
                return input == catta::json::Token::character('r') ? jump(HUB + 1155) : error();
            case HUB + 1155:
                return input == catta::json::Token::character('i') ? jump(HUB + 1156) : error();
            case HUB + 1156:
                return input == catta::json::Token::character('t') ? jump(HUB + 1157) : error();
            case HUB + 1157:
                return input == catta::json::Token::character('e') ? jump(HUB + 1158) : error();
            case HUB + 1158:
                return input == catta::json::Token::closeString() ? close(124) : error();
            case HUB + 1159:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1164)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1160)
                                                                     : error();
            case HUB + 1160:
                return input == catta::json::Token::character('e') ? jump(HUB + 1161) : error();
            case HUB + 1161:
                return input == catta::json::Token::character('a') ? jump(HUB + 1162) : error();
            case HUB + 1162:
                return input == catta::json::Token::character('d') ? jump(HUB + 1163) : error();
            case HUB + 1163:
                return input == catta::json::Token::closeString() ? close(99) : error();
            case HUB + 1164:
                return input == catta::json::Token::character('r') ? jump(HUB + 1165) : error();
            case HUB + 1165:
                return input == catta::json::Token::character('i') ? jump(HUB + 1166) : error();
            case HUB + 1166:
                return input == catta::json::Token::character('t') ? jump(HUB + 1167) : error();
            case HUB + 1167:
                return input == catta::json::Token::character('e') ? jump(HUB + 1168) : error();
            case HUB + 1168:
                return input == catta::json::Token::closeString() ? close(125) : error();
            case HUB + 1169:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1174)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1170)
                                                                     : error();
            case HUB + 1170:
                return input == catta::json::Token::character('e') ? jump(HUB + 1171) : error();
            case HUB + 1171:
                return input == catta::json::Token::character('a') ? jump(HUB + 1172) : error();
            case HUB + 1172:
                return input == catta::json::Token::character('d') ? jump(HUB + 1173) : error();
            case HUB + 1173:
                return input == catta::json::Token::closeString() ? close(100) : error();
            case HUB + 1174:
                return input == catta::json::Token::character('r') ? jump(HUB + 1175) : error();
            case HUB + 1175:
                return input == catta::json::Token::character('i') ? jump(HUB + 1176) : error();
            case HUB + 1176:
                return input == catta::json::Token::character('t') ? jump(HUB + 1177) : error();
            case HUB + 1177:
                return input == catta::json::Token::character('e') ? jump(HUB + 1178) : error();
            case HUB + 1178:
                return input == catta::json::Token::closeString() ? close(126) : error();
            case HUB + 1179:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1184)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1180)
                                                                     : error();
            case HUB + 1180:
                return input == catta::json::Token::character('e') ? jump(HUB + 1181) : error();
            case HUB + 1181:
                return input == catta::json::Token::character('a') ? jump(HUB + 1182) : error();
            case HUB + 1182:
                return input == catta::json::Token::character('d') ? jump(HUB + 1183) : error();
            case HUB + 1183:
                return input == catta::json::Token::closeString() ? close(101) : error();
            case HUB + 1184:
                return input == catta::json::Token::character('r') ? jump(HUB + 1185) : error();
            case HUB + 1185:
                return input == catta::json::Token::character('i') ? jump(HUB + 1186) : error();
            case HUB + 1186:
                return input == catta::json::Token::character('t') ? jump(HUB + 1187) : error();
            case HUB + 1187:
                return input == catta::json::Token::character('e') ? jump(HUB + 1188) : error();
            case HUB + 1188:
                return input == catta::json::Token::closeString() ? close(127) : error();
            case HUB + 1189:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1194)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1190)
                                                                     : error();
            case HUB + 1190:
                return input == catta::json::Token::character('e') ? jump(HUB + 1191) : error();
            case HUB + 1191:
                return input == catta::json::Token::character('a') ? jump(HUB + 1192) : error();
            case HUB + 1192:
                return input == catta::json::Token::character('d') ? jump(HUB + 1193) : error();
            case HUB + 1193:
                return input == catta::json::Token::closeString() ? close(102) : error();
            case HUB + 1194:
                return input == catta::json::Token::character('r') ? jump(HUB + 1195) : error();
            case HUB + 1195:
                return input == catta::json::Token::character('i') ? jump(HUB + 1196) : error();
            case HUB + 1196:
                return input == catta::json::Token::character('t') ? jump(HUB + 1197) : error();
            case HUB + 1197:
                return input == catta::json::Token::character('e') ? jump(HUB + 1198) : error();
            case HUB + 1198:
                return input == catta::json::Token::closeString() ? close(128) : error();
            case HUB + 1199:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1204)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1200)
                                                                     : error();
            case HUB + 1200:
                return input == catta::json::Token::character('e') ? jump(HUB + 1201) : error();
            case HUB + 1201:
                return input == catta::json::Token::character('a') ? jump(HUB + 1202) : error();
            case HUB + 1202:
                return input == catta::json::Token::character('d') ? jump(HUB + 1203) : error();
            case HUB + 1203:
                return input == catta::json::Token::closeString() ? close(103) : error();
            case HUB + 1204:
                return input == catta::json::Token::character('r') ? jump(HUB + 1205) : error();
            case HUB + 1205:
                return input == catta::json::Token::character('i') ? jump(HUB + 1206) : error();
            case HUB + 1206:
                return input == catta::json::Token::character('t') ? jump(HUB + 1207) : error();
            case HUB + 1207:
                return input == catta::json::Token::character('e') ? jump(HUB + 1208) : error();
            case HUB + 1208:
                return input == catta::json::Token::closeString() ? close(129) : error();
            case HUB + 1209:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1214)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1210)
                                                                     : error();
            case HUB + 1210:
                return input == catta::json::Token::character('e') ? jump(HUB + 1211) : error();
            case HUB + 1211:
                return input == catta::json::Token::character('a') ? jump(HUB + 1212) : error();
            case HUB + 1212:
                return input == catta::json::Token::character('d') ? jump(HUB + 1213) : error();
            case HUB + 1213:
                return input == catta::json::Token::closeString() ? close(104) : error();
            case HUB + 1214:
                return input == catta::json::Token::character('r') ? jump(HUB + 1215) : error();
            case HUB + 1215:
                return input == catta::json::Token::character('i') ? jump(HUB + 1216) : error();
            case HUB + 1216:
                return input == catta::json::Token::character('t') ? jump(HUB + 1217) : error();
            case HUB + 1217:
                return input == catta::json::Token::character('e') ? jump(HUB + 1218) : error();
            case HUB + 1218:
                return input == catta::json::Token::closeString() ? close(130) : error();
            case HUB + 1219:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1224)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1220)
                                                                     : error();
            case HUB + 1220:
                return input == catta::json::Token::character('e') ? jump(HUB + 1221) : error();
            case HUB + 1221:
                return input == catta::json::Token::character('a') ? jump(HUB + 1222) : error();
            case HUB + 1222:
                return input == catta::json::Token::character('d') ? jump(HUB + 1223) : error();
            case HUB + 1223:
                return input == catta::json::Token::closeString() ? close(105) : error();
            case HUB + 1224:
                return input == catta::json::Token::character('r') ? jump(HUB + 1225) : error();
            case HUB + 1225:
                return input == catta::json::Token::character('i') ? jump(HUB + 1226) : error();
            case HUB + 1226:
                return input == catta::json::Token::character('t') ? jump(HUB + 1227) : error();
            case HUB + 1227:
                return input == catta::json::Token::character('e') ? jump(HUB + 1228) : error();
            case HUB + 1228:
                return input == catta::json::Token::closeString() ? close(131) : error();
            case HUB + 1229:
                return input == catta::json::Token::character('5')   ? jump(HUB + 1280)
                       : input == catta::json::Token::character('4') ? jump(HUB + 1270)
                       : input == catta::json::Token::character('3') ? jump(HUB + 1260)
                       : input == catta::json::Token::character('2') ? jump(HUB + 1250)
                       : input == catta::json::Token::character('1') ? jump(HUB + 1240)
                       : input == catta::json::Token::character('0') ? jump(HUB + 1230)
                                                                     : error();
            case HUB + 1230:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1235)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1231)
                                                                     : error();
            case HUB + 1231:
                return input == catta::json::Token::character('e') ? jump(HUB + 1232) : error();
            case HUB + 1232:
                return input == catta::json::Token::character('a') ? jump(HUB + 1233) : error();
            case HUB + 1233:
                return input == catta::json::Token::character('d') ? jump(HUB + 1234) : error();
            case HUB + 1234:
                return input == catta::json::Token::closeString() ? close(106) : error();
            case HUB + 1235:
                return input == catta::json::Token::character('r') ? jump(HUB + 1236) : error();
            case HUB + 1236:
                return input == catta::json::Token::character('i') ? jump(HUB + 1237) : error();
            case HUB + 1237:
                return input == catta::json::Token::character('t') ? jump(HUB + 1238) : error();
            case HUB + 1238:
                return input == catta::json::Token::character('e') ? jump(HUB + 1239) : error();
            case HUB + 1239:
                return input == catta::json::Token::closeString() ? close(132) : error();
            case HUB + 1240:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1245)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1241)
                                                                     : error();
            case HUB + 1241:
                return input == catta::json::Token::character('e') ? jump(HUB + 1242) : error();
            case HUB + 1242:
                return input == catta::json::Token::character('a') ? jump(HUB + 1243) : error();
            case HUB + 1243:
                return input == catta::json::Token::character('d') ? jump(HUB + 1244) : error();
            case HUB + 1244:
                return input == catta::json::Token::closeString() ? close(107) : error();
            case HUB + 1245:
                return input == catta::json::Token::character('r') ? jump(HUB + 1246) : error();
            case HUB + 1246:
                return input == catta::json::Token::character('i') ? jump(HUB + 1247) : error();
            case HUB + 1247:
                return input == catta::json::Token::character('t') ? jump(HUB + 1248) : error();
            case HUB + 1248:
                return input == catta::json::Token::character('e') ? jump(HUB + 1249) : error();
            case HUB + 1249:
                return input == catta::json::Token::closeString() ? close(133) : error();
            case HUB + 1250:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1255)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1251)
                                                                     : error();
            case HUB + 1251:
                return input == catta::json::Token::character('e') ? jump(HUB + 1252) : error();
            case HUB + 1252:
                return input == catta::json::Token::character('a') ? jump(HUB + 1253) : error();
            case HUB + 1253:
                return input == catta::json::Token::character('d') ? jump(HUB + 1254) : error();
            case HUB + 1254:
                return input == catta::json::Token::closeString() ? close(108) : error();
            case HUB + 1255:
                return input == catta::json::Token::character('r') ? jump(HUB + 1256) : error();
            case HUB + 1256:
                return input == catta::json::Token::character('i') ? jump(HUB + 1257) : error();
            case HUB + 1257:
                return input == catta::json::Token::character('t') ? jump(HUB + 1258) : error();
            case HUB + 1258:
                return input == catta::json::Token::character('e') ? jump(HUB + 1259) : error();
            case HUB + 1259:
                return input == catta::json::Token::closeString() ? close(134) : error();
            case HUB + 1260:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1265)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1261)
                                                                     : error();
            case HUB + 1261:
                return input == catta::json::Token::character('e') ? jump(HUB + 1262) : error();
            case HUB + 1262:
                return input == catta::json::Token::character('a') ? jump(HUB + 1263) : error();
            case HUB + 1263:
                return input == catta::json::Token::character('d') ? jump(HUB + 1264) : error();
            case HUB + 1264:
                return input == catta::json::Token::closeString() ? close(109) : error();
            case HUB + 1265:
                return input == catta::json::Token::character('r') ? jump(HUB + 1266) : error();
            case HUB + 1266:
                return input == catta::json::Token::character('i') ? jump(HUB + 1267) : error();
            case HUB + 1267:
                return input == catta::json::Token::character('t') ? jump(HUB + 1268) : error();
            case HUB + 1268:
                return input == catta::json::Token::character('e') ? jump(HUB + 1269) : error();
            case HUB + 1269:
                return input == catta::json::Token::closeString() ? close(135) : error();
            case HUB + 1270:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1275)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1271)
                                                                     : error();
            case HUB + 1271:
                return input == catta::json::Token::character('e') ? jump(HUB + 1272) : error();
            case HUB + 1272:
                return input == catta::json::Token::character('a') ? jump(HUB + 1273) : error();
            case HUB + 1273:
                return input == catta::json::Token::character('d') ? jump(HUB + 1274) : error();
            case HUB + 1274:
                return input == catta::json::Token::closeString() ? close(110) : error();
            case HUB + 1275:
                return input == catta::json::Token::character('r') ? jump(HUB + 1276) : error();
            case HUB + 1276:
                return input == catta::json::Token::character('i') ? jump(HUB + 1277) : error();
            case HUB + 1277:
                return input == catta::json::Token::character('t') ? jump(HUB + 1278) : error();
            case HUB + 1278:
                return input == catta::json::Token::character('e') ? jump(HUB + 1279) : error();
            case HUB + 1279:
                return input == catta::json::Token::closeString() ? close(136) : error();
            case HUB + 1280:
                return input == catta::json::Token::character('W')   ? jump(HUB + 1285)
                       : input == catta::json::Token::character('R') ? jump(HUB + 1281)
                                                                     : error();
            case HUB + 1281:
                return input == catta::json::Token::character('e') ? jump(HUB + 1282) : error();
            case HUB + 1282:
                return input == catta::json::Token::character('a') ? jump(HUB + 1283) : error();
            case HUB + 1283:
                return input == catta::json::Token::character('d') ? jump(HUB + 1284) : error();
            case HUB + 1284:
                return input == catta::json::Token::closeString() ? close(111) : error();
            case HUB + 1285:
                return input == catta::json::Token::character('r') ? jump(HUB + 1286) : error();
            case HUB + 1286:
                return input == catta::json::Token::character('i') ? jump(HUB + 1287) : error();
            case HUB + 1287:
                return input == catta::json::Token::character('t') ? jump(HUB + 1288) : error();
            case HUB + 1288:
                return input == catta::json::Token::character('e') ? jump(HUB + 1289) : error();
            case HUB + 1289:
                return input == catta::json::Token::closeString() ? close(137) : error();
            case HUB + 1290:
                return input == catta::json::Token::character('o') ? jump(HUB + 1291) : error();
            case HUB + 1291:
                return input == catta::json::Token::character('r') ? jump(HUB + 1292) : error();
            case HUB + 1292:
                return input == catta::json::Token::character('a') ? jump(HUB + 1293) : error();
            case HUB + 1293:
                return input == catta::json::Token::character('g') ? jump(HUB + 1294) : error();
            case HUB + 1294:
                return input == catta::json::Token::character('e') ? jump(HUB + 1295) : error();
            case HUB + 1295:
                return input == catta::json::Token::character('N') ? jump(HUB + 1296) : error();
            case HUB + 1296:
                return input == catta::json::Token::character('o') ? jump(HUB + 1297) : error();
            case HUB + 1297:
                return input == catta::json::Token::character('m') ? jump(HUB + 1298) : error();
            case HUB + 1298:
                return input == catta::json::Token::character('i') ? jump(HUB + 1299) : error();
            case HUB + 1299:
                return input == catta::json::Token::character('n') ? jump(HUB + 1300) : error();
            case HUB + 1300:
                return input == catta::json::Token::character('a') ? jump(HUB + 1301) : error();
            case HUB + 1301:
                return input == catta::json::Token::character('l') ? jump(HUB + 1302) : error();
            case HUB + 1302:
                return input == catta::json::Token::character('C') ? jump(HUB + 1303) : error();
            case HUB + 1303:
                return input == catta::json::Token::character('h') ? jump(HUB + 1304) : error();
            case HUB + 1304:
                return input == catta::json::Token::character('a') ? jump(HUB + 1305) : error();
            case HUB + 1305:
                return input == catta::json::Token::character('r') ? jump(HUB + 1306) : error();
            case HUB + 1306:
                return input == catta::json::Token::character('g') ? jump(HUB + 1307) : error();
            case HUB + 1307:
                return input == catta::json::Token::character('e') ? jump(HUB + 1308) : error();
            case HUB + 1308:
                return input == catta::json::Token::character('P') ? jump(HUB + 1309) : error();
            case HUB + 1309:
                return input == catta::json::Token::character('o') ? jump(HUB + 1310) : error();
            case HUB + 1310:
                return input == catta::json::Token::character('w') ? jump(HUB + 1311) : error();
            case HUB + 1311:
                return input == catta::json::Token::character('e') ? jump(HUB + 1312) : error();
            case HUB + 1312:
                return input == catta::json::Token::character('r') ? jump(HUB + 1313) : error();
            case HUB + 1313:
                return input == catta::json::Token::closeString() ? close(42) : error();
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
    static constexpr std::uint16_t TAIL = HUB + 1314;
    static constexpr std::uint16_t DONE = TAIL + 1;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
