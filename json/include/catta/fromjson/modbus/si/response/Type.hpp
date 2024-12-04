#pragma once

// response
#include <catta/modbus/si/response/Type.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::Type>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::Type;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
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
                return input == catta::json::Token::character('w')   ? jump(HUB + 198)
                       : input == catta::json::Token::character('v') ? jump(HUB + 187)
                       : input == catta::json::Token::character('s') ? jump(HUB + 125)
                       : input == catta::json::Token::character('r') ? jump(HUB + 100)
                       : input == catta::json::Token::character('l') ? jump(HUB + 82)
                       : input == catta::json::Token::character('f') ? jump(HUB + 61)
                       : input == catta::json::Token::character('e') ? jump(HUB + 35)
                       : input == catta::json::Token::character('d') ? jump(HUB + 21)
                       : input == catta::json::Token::character('c') ? jump(HUB + 1)
                                                                     : error();
            case HUB + 1:
                return input == catta::json::Token::character('o') ? jump(HUB + 2) : error();
            case HUB + 2:
                return input == catta::json::Token::character('n') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('t') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('r') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('o') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('l') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('B') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('a') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('t') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('t') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('e') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('r') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('y') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('I') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('n') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('v') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('e') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('r') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('t') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::closeString() ? close(12) : error();
            case HUB + 21:
                return input == catta::json::Token::character('e') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('a') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('c') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('t') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('i') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('v') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('a') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::character('t') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('e') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('I') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('d') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('l') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('e') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::closeString() ? close(8) : error();
            case HUB + 35:
                return input == catta::json::Token::character('x')   ? jump(HUB + 53)
                       : input == catta::json::Token::character('n') ? jump(HUB + 36)
                                                                     : error();
            case HUB + 36:
                return input == catta::json::Token::character('d') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('C') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('o') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('n') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('s') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('t') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('a') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('n') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('t') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('V') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('o') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('l') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('t') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('a') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('g') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('e') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::closeString() ? close(10) : error();
            case HUB + 53:
                return input == catta::json::Token::character('c') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::character('e') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('p') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('t') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('i') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('o') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('n') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::closeString() ? close(0) : error();
            case HUB + 61:
                return input == catta::json::Token::character('o')   ? jump(HUB + 74)
                       : input == catta::json::Token::character('a') ? jump(HUB + 62)
                                                                     : error();
            case HUB + 62:
                return input == catta::json::Token::character('c') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('t') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('o') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('r') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('y') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('V') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::character('a') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('l') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('u') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('e') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('s') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::closeString() ? close(1) : error();
            case HUB + 74:
                return input == catta::json::Token::character('r') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('c') ? jump(HUB + 76) : error();
            case HUB + 76:
                return input == catta::json::Token::character('e') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('I') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('d') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('l') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('e') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::closeString() ? close(7) : error();
            case HUB + 82:
                return input == catta::json::Token::character('i') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('m') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('i') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('t') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('B') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('a') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('t') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('t') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::character('e') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('r') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('y') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('I') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('n') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::character('v') ? jump(HUB + 96) : error();
            case HUB + 96:
                return input == catta::json::Token::character('e') ? jump(HUB + 97) : error();
            case HUB + 97:
                return input == catta::json::Token::character('r') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::character('t') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::closeString() ? close(13) : error();
            case HUB + 100:
                return input == catta::json::Token::character('e') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('a') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('d') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('O')   ? jump(HUB + 109)
                       : input == catta::json::Token::character('E') ? jump(HUB + 104)
                                                                     : error();
            case HUB + 104:
                return input == catta::json::Token::character('r') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('r') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('o') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('r') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::closeString() ? close(2) : error();
            case HUB + 109:
                return input == catta::json::Token::character('p') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('e') ? jump(HUB + 111) : error();
            case HUB + 111:
                return input == catta::json::Token::character('r') ? jump(HUB + 112) : error();
            case HUB + 112:
                return input == catta::json::Token::character('a') ? jump(HUB + 113) : error();
            case HUB + 113:
                return input == catta::json::Token::character('t') ? jump(HUB + 114) : error();
            case HUB + 114:
                return input == catta::json::Token::character('i') ? jump(HUB + 115) : error();
            case HUB + 115:
                return input == catta::json::Token::character('n') ? jump(HUB + 116) : error();
            case HUB + 116:
                return input == catta::json::Token::character('g') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('D') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('a') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::character('t') ? jump(HUB + 120) : error();
            case HUB + 120:
                return input == catta::json::Token::character('a') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('3') ? jump(HUB + 122) : error();
            case HUB + 122:
                return input == catta::json::Token::character('e')   ? jump(HUB + 124)
                       : input == catta::json::Token::character('3') ? jump(HUB + 123)
                                                                     : error();
            case HUB + 123:
                return input == catta::json::Token::closeString() ? close(3) : error();
            case HUB + 124:
                return input == catta::json::Token::closeString() ? close(4) : error();
            case HUB + 125:
                return input == catta::json::Token::character('w')   ? jump(HUB + 162)
                       : input == catta::json::Token::character('t') ? jump(HUB + 139)
                       : input == catta::json::Token::character('e') ? jump(HUB + 126)
                                                                     : error();
            case HUB + 126:
                return input == catta::json::Token::character('t') ? jump(HUB + 127) : error();
            case HUB + 127:
                return input == catta::json::Token::character('P') ? jump(HUB + 128) : error();
            case HUB + 128:
                return input == catta::json::Token::character('o') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('w') ? jump(HUB + 130) : error();
            case HUB + 130:
                return input == catta::json::Token::character('e') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('r') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::character('F') ? jump(HUB + 133) : error();
            case HUB + 133:
                return input == catta::json::Token::character('a') ? jump(HUB + 134) : error();
            case HUB + 134:
                return input == catta::json::Token::character('c') ? jump(HUB + 135) : error();
            case HUB + 135:
                return input == catta::json::Token::character('t') ? jump(HUB + 136) : error();
            case HUB + 136:
                return input == catta::json::Token::character('o') ? jump(HUB + 137) : error();
            case HUB + 137:
                return input == catta::json::Token::character('r') ? jump(HUB + 138) : error();
            case HUB + 138:
                return input == catta::json::Token::closeString() ? close(11) : error();
            case HUB + 139:
                return input == catta::json::Token::character('r')   ? jump(HUB + 158)
                       : input == catta::json::Token::character('a') ? jump(HUB + 140)
                                                                     : error();
            case HUB + 140:
                return input == catta::json::Token::character('r') ? jump(HUB + 141) : error();
            case HUB + 141:
                return input == catta::json::Token::character('t') ? jump(HUB + 142) : error();
            case HUB + 142:
                return input == catta::json::Token::character('C') ? jump(HUB + 143) : error();
            case HUB + 143:
                return input == catta::json::Token::character('o') ? jump(HUB + 144) : error();
            case HUB + 144:
                return input == catta::json::Token::character('n') ? jump(HUB + 145) : error();
            case HUB + 145:
                return input == catta::json::Token::character('s') ? jump(HUB + 146) : error();
            case HUB + 146:
                return input == catta::json::Token::character('t') ? jump(HUB + 147) : error();
            case HUB + 147:
                return input == catta::json::Token::character('a') ? jump(HUB + 148) : error();
            case HUB + 148:
                return input == catta::json::Token::character('n') ? jump(HUB + 149) : error();
            case HUB + 149:
                return input == catta::json::Token::character('t') ? jump(HUB + 150) : error();
            case HUB + 150:
                return input == catta::json::Token::character('V') ? jump(HUB + 151) : error();
            case HUB + 151:
                return input == catta::json::Token::character('o') ? jump(HUB + 152) : error();
            case HUB + 152:
                return input == catta::json::Token::character('l') ? jump(HUB + 153) : error();
            case HUB + 153:
                return input == catta::json::Token::character('t') ? jump(HUB + 154) : error();
            case HUB + 154:
                return input == catta::json::Token::character('a') ? jump(HUB + 155) : error();
            case HUB + 155:
                return input == catta::json::Token::character('g') ? jump(HUB + 156) : error();
            case HUB + 156:
                return input == catta::json::Token::character('e') ? jump(HUB + 157) : error();
            case HUB + 157:
                return input == catta::json::Token::closeString() ? close(9) : error();
            case HUB + 158:
                return input == catta::json::Token::character('i') ? jump(HUB + 159) : error();
            case HUB + 159:
                return input == catta::json::Token::character('n') ? jump(HUB + 160) : error();
            case HUB + 160:
                return input == catta::json::Token::character('g') ? jump(HUB + 161) : error();
            case HUB + 161:
                return input == catta::json::Token::closeString() ? close(18) : error();
            case HUB + 162:
                return input == catta::json::Token::character('i') ? jump(HUB + 163) : error();
            case HUB + 163:
                return input == catta::json::Token::character('t') ? jump(HUB + 164) : error();
            case HUB + 164:
                return input == catta::json::Token::character('c') ? jump(HUB + 165) : error();
            case HUB + 165:
                return input == catta::json::Token::character('h') ? jump(HUB + 166) : error();
            case HUB + 166:
                return input == catta::json::Token::character('O') ? jump(HUB + 167) : error();
            case HUB + 167:
                return input == catta::json::Token::character('n')   ? jump(HUB + 178)
                       : input == catta::json::Token::character('f') ? jump(HUB + 168)
                                                                     : error();
            case HUB + 168:
                return input == catta::json::Token::character('f') ? jump(HUB + 169) : error();
            case HUB + 169:
                return input == catta::json::Token::character('I') ? jump(HUB + 170) : error();
            case HUB + 170:
                return input == catta::json::Token::character('n') ? jump(HUB + 171) : error();
            case HUB + 171:
                return input == catta::json::Token::character('v') ? jump(HUB + 172) : error();
            case HUB + 172:
                return input == catta::json::Token::character('e') ? jump(HUB + 173) : error();
            case HUB + 173:
                return input == catta::json::Token::character('r') ? jump(HUB + 174) : error();
            case HUB + 174:
                return input == catta::json::Token::character('t') ? jump(HUB + 175) : error();
            case HUB + 175:
                return input == catta::json::Token::character('e') ? jump(HUB + 176) : error();
            case HUB + 176:
                return input == catta::json::Token::character('r') ? jump(HUB + 177) : error();
            case HUB + 177:
                return input == catta::json::Token::closeString() ? close(5) : error();
            case HUB + 178:
                return input == catta::json::Token::character('I') ? jump(HUB + 179) : error();
            case HUB + 179:
                return input == catta::json::Token::character('n') ? jump(HUB + 180) : error();
            case HUB + 180:
                return input == catta::json::Token::character('v') ? jump(HUB + 181) : error();
            case HUB + 181:
                return input == catta::json::Token::character('e') ? jump(HUB + 182) : error();
            case HUB + 182:
                return input == catta::json::Token::character('r') ? jump(HUB + 183) : error();
            case HUB + 183:
                return input == catta::json::Token::character('t') ? jump(HUB + 184) : error();
            case HUB + 184:
                return input == catta::json::Token::character('e') ? jump(HUB + 185) : error();
            case HUB + 185:
                return input == catta::json::Token::character('r') ? jump(HUB + 186) : error();
            case HUB + 186:
                return input == catta::json::Token::closeString() ? close(6) : error();
            case HUB + 187:
                return input == catta::json::Token::character('a') ? jump(HUB + 188) : error();
            case HUB + 188:
                return input == catta::json::Token::character('l') ? jump(HUB + 189) : error();
            case HUB + 189:
                return input == catta::json::Token::character('u') ? jump(HUB + 190) : error();
            case HUB + 190:
                return input == catta::json::Token::character('e') ? jump(HUB + 191) : error();
            case HUB + 191:
                return input == catta::json::Token::character('6')   ? jump(HUB + 196)
                       : input == catta::json::Token::character('3') ? jump(HUB + 194)
                       : input == catta::json::Token::character('1') ? jump(HUB + 192)
                                                                     : error();
            case HUB + 192:
                return input == catta::json::Token::character('6') ? jump(HUB + 193) : error();
            case HUB + 193:
                return input == catta::json::Token::closeString() ? close(15) : error();
            case HUB + 194:
                return input == catta::json::Token::character('2') ? jump(HUB + 195) : error();
            case HUB + 195:
                return input == catta::json::Token::closeString() ? close(16) : error();
            case HUB + 196:
                return input == catta::json::Token::character('4') ? jump(HUB + 197) : error();
            case HUB + 197:
                return input == catta::json::Token::closeString() ? close(17) : error();
            case HUB + 198:
                return input == catta::json::Token::character('r') ? jump(HUB + 199) : error();
            case HUB + 199:
                return input == catta::json::Token::character('i') ? jump(HUB + 200) : error();
            case HUB + 200:
                return input == catta::json::Token::character('t') ? jump(HUB + 201) : error();
            case HUB + 201:
                return input == catta::json::Token::character('e') ? jump(HUB + 202) : error();
            case HUB + 202:
                return input == catta::json::Token::character('R') ? jump(HUB + 203) : error();
            case HUB + 203:
                return input == catta::json::Token::character('e') ? jump(HUB + 204) : error();
            case HUB + 204:
                return input == catta::json::Token::character('g') ? jump(HUB + 205) : error();
            case HUB + 205:
                return input == catta::json::Token::character('i') ? jump(HUB + 206) : error();
            case HUB + 206:
                return input == catta::json::Token::character('s') ? jump(HUB + 207) : error();
            case HUB + 207:
                return input == catta::json::Token::character('t') ? jump(HUB + 208) : error();
            case HUB + 208:
                return input == catta::json::Token::character('e') ? jump(HUB + 209) : error();
            case HUB + 209:
                return input == catta::json::Token::character('r') ? jump(HUB + 210) : error();
            case HUB + 210:
                return input == catta::json::Token::closeString() ? close(14) : error();
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
    std::uint8_t _state;
    std::uint8_t _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 211;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
