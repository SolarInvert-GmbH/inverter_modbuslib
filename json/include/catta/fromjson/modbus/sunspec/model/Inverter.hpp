#pragma once

// model
#include <catta/modbus/sunspec/model/Inverter.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/sunspec/ScaledValue3U16.hpp>
#include <catta/fromjson/modbus/sunspec/ScaledValue4U16.hpp>
#include <catta/fromjson/modbus/sunspec/ScaledValueS16.hpp>
#include <catta/fromjson/modbus/sunspec/ScaledValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ScaledValueU32.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU32.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::model::Inverter>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::model::Inverter;
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
                return input == catta::json::Token::character('w')   ? jump(HUB + 122)
                       : input == catta::json::Token::character('v') ? jump(HUB + 77)
                       : input == catta::json::Token::character('p') ? jump(HUB + 64)
                       : input == catta::json::Token::character('o') ? jump(HUB + 48)
                       : input == catta::json::Token::character('h') ? jump(HUB + 41)
                       : input == catta::json::Token::character('d') ? jump(HUB + 30)
                       : input == catta::json::Token::character('c') ? jump(HUB + 10)
                       : input == catta::json::Token::character('a') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('m') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('p') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('e') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('r') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('e') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::closeString() ? jump(HUB + 8) : error();
            case HUB + 8:
                return !_ampereParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 9:
                return handle(_ampereParser);
            case HUB + 10:
                return input == catta::json::Token::character('a') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('b') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('i') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('n') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('e') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('t') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('T') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('e') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('m') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('p') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('e') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('r') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('a') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('t') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('u') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('r') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('e') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::closeString() ? jump(HUB + 28) : error();
            case HUB + 28:
                return !_cabinetTemperatureParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 29:
                return handle(_cabinetTemperatureParser);
            case HUB + 30:
                return input == catta::json::Token::character('c') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('V') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('o') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('l') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('t') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('a') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('g') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::character('e') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::closeString() ? jump(HUB + 39) : error();
            case HUB + 39:
                return !_dcVoltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 40:
                return handle(_dcVoltageParser);
            case HUB + 41:
                return input == catta::json::Token::character('e') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('r') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('t') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('z') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::closeString() ? jump(HUB + 46) : error();
            case HUB + 46:
                return !_hertzParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 47:
                return handle(_hertzParser);
            case HUB + 48:
                return input == catta::json::Token::character('p') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('e') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('r') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('a') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::character('t') ? jump(HUB + 53) : error();
            case HUB + 53:
                return input == catta::json::Token::character('i') ? jump(HUB + 54) : error();
            case HUB + 54:
                return input == catta::json::Token::character('n') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('g') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('S') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('t') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('a') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('t') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('e') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::closeString() ? jump(HUB + 62) : error();
            case HUB + 62:
                return !_operatingStateParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 63:
                return handle(_operatingStateParser);
            case HUB + 64:
                return input == catta::json::Token::character('o') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('w') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('e') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('r') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::character('F') ? jump(HUB + 69) : error();
            case HUB + 69:
                return input == catta::json::Token::character('a') ? jump(HUB + 70) : error();
            case HUB + 70:
                return input == catta::json::Token::character('c') ? jump(HUB + 71) : error();
            case HUB + 71:
                return input == catta::json::Token::character('t') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('o') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('r') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::closeString() ? jump(HUB + 75) : error();
            case HUB + 75:
                return !_powerFactorParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 76:
                return handle(_powerFactorParser);
            case HUB + 77:
                return input == catta::json::Token::character('o')   ? jump(HUB + 114)
                       : input == catta::json::Token::character('e') ? jump(HUB + 78)
                                                                     : error();
            case HUB + 78:
                return input == catta::json::Token::character('n') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('d') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('o') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('r') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('O')   ? jump(HUB + 98)
                       : input == catta::json::Token::character('E') ? jump(HUB + 83)
                                                                     : error();
            case HUB + 83:
                return input == catta::json::Token::character('v') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('e') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('n') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('t') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('B') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('i') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('t') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::character('f') ? jump(HUB + 91) : error();
            case HUB + 91:
                return input == catta::json::Token::character('i') ? jump(HUB + 92) : error();
            case HUB + 92:
                return input == catta::json::Token::character('e') ? jump(HUB + 93) : error();
            case HUB + 93:
                return input == catta::json::Token::character('l') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('d') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::closeString() ? jump(HUB + 96) : error();
            case HUB + 96:
                return !_vendorEventBitfieldParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 97:
                return handle(_vendorEventBitfieldParser);
            case HUB + 98:
                return input == catta::json::Token::character('p') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('e') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('r') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('a') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('t') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('i') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::character('n') ? jump(HUB + 105) : error();
            case HUB + 105:
                return input == catta::json::Token::character('g') ? jump(HUB + 106) : error();
            case HUB + 106:
                return input == catta::json::Token::character('S') ? jump(HUB + 107) : error();
            case HUB + 107:
                return input == catta::json::Token::character('t') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('a') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('t') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::character('e') ? jump(HUB + 111) : error();
            case HUB + 111:
                return input == catta::json::Token::closeString() ? jump(HUB + 112) : error();
            case HUB + 112:
                return !_vendorOperatingStateParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 113:
                return handle(_vendorOperatingStateParser);
            case HUB + 114:
                return input == catta::json::Token::character('l') ? jump(HUB + 115) : error();
            case HUB + 115:
                return input == catta::json::Token::character('t') ? jump(HUB + 116) : error();
            case HUB + 116:
                return input == catta::json::Token::character('a') ? jump(HUB + 117) : error();
            case HUB + 117:
                return input == catta::json::Token::character('g') ? jump(HUB + 118) : error();
            case HUB + 118:
                return input == catta::json::Token::character('e') ? jump(HUB + 119) : error();
            case HUB + 119:
                return input == catta::json::Token::closeString() ? jump(HUB + 120) : error();
            case HUB + 120:
                return !_voltageParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 121:
                return handle(_voltageParser);
            case HUB + 122:
                return input == catta::json::Token::character('a') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::character('t') ? jump(HUB + 124) : error();
            case HUB + 124:
                return input == catta::json::Token::character('t') ? jump(HUB + 125) : error();
            case HUB + 125:
                return input == catta::json::Token::character('H')  ? jump(HUB + 128)
                       : input == catta::json::Token::closeString() ? jump(HUB + 126)
                                                                    : error();
            case HUB + 126:
                return !_wattParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 127:
                return handle(_wattParser);
            case HUB + 128:
                return input == catta::json::Token::character('o') ? jump(HUB + 129) : error();
            case HUB + 129:
                return input == catta::json::Token::character('u') ? jump(HUB + 130) : error();
            case HUB + 130:
                return input == catta::json::Token::character('r') ? jump(HUB + 131) : error();
            case HUB + 131:
                return input == catta::json::Token::character('s') ? jump(HUB + 132) : error();
            case HUB + 132:
                return input == catta::json::Token::closeString() ? jump(HUB + 133) : error();
            case HUB + 133:
                return !_wattHoursParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 134:
                return handle(_wattHoursParser);
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
                   ? Output::create(_ampereParser.data(), _voltageParser.data(), _wattParser.data(), _hertzParser.data(), _powerFactorParser.data(),
                                    _wattHoursParser.data(), _dcVoltageParser.data(), _cabinetTemperatureParser.data(), _operatingStateParser.data(),
                                    _vendorOperatingStateParser.data(), _vendorEventBitfieldParser.data())
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
    Parser<catta::modbus::sunspec::ScaledValue4U16> _ampereParser;
    Parser<catta::modbus::sunspec::ScaledValueS16> _cabinetTemperatureParser;
    Parser<catta::modbus::sunspec::ScaledValueU16> _dcVoltageParser;
    Parser<catta::modbus::sunspec::ScaledValueU16> _hertzParser;
    Parser<catta::modbus::sunspec::ValueU16> _operatingStateParser;
    Parser<catta::modbus::sunspec::ScaledValueS16> _powerFactorParser;
    Parser<catta::modbus::sunspec::ValueU32> _vendorEventBitfieldParser;
    Parser<catta::modbus::sunspec::ValueU16> _vendorOperatingStateParser;
    Parser<catta::modbus::sunspec::ScaledValue3U16> _voltageParser;
    Parser<catta::modbus::sunspec::ScaledValueS16> _wattParser;
    Parser<catta::modbus::sunspec::ScaledValueU32> _wattHoursParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 135;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
