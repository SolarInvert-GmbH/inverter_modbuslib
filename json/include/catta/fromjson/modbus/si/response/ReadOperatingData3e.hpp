#pragma once

// response
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/Type.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU32.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::ReadOperatingData3e>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::ReadOperatingData3e;
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
                return input == catta::json::Token::character('v')   ? jump(HUB + 113)
                       : input == catta::json::Token::character('t') ? jump(HUB + 107)
                       : input == catta::json::Token::character('s') ? jump(HUB + 93)
                       : input == catta::json::Token::character('p') ? jump(HUB + 70)
                       : input == catta::json::Token::character('o') ? jump(HUB + 54)
                       : input == catta::json::Token::character('n') ? jump(HUB + 40)
                       : input == catta::json::Token::character('m') ? jump(HUB + 30)
                       : input == catta::json::Token::character('g') ? jump(HUB + 10)
                       : input == catta::json::Token::character('c') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('o') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('s') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('p') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('h') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('i') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::closeString() ? jump(HUB + 8) : error();
            case HUB + 8:
                return !_cosphiParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 9:
                return handle(_cosphiParser);
            case HUB + 10:
                return input == catta::json::Token::character('r') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('i') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('d') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('S') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('u') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('p') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('p') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('l') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::character('y') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('D') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('a') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('i') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('l') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('y') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('S') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('u') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('m') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::closeString() ? jump(HUB + 28) : error();
            case HUB + 28:
                return !_gridSupplyDailySumParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 29:
                return handle(_gridSupplyDailySumParser);
            case HUB + 30:
                return input == catta::json::Token::character('o') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('d') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('b') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('u') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('s') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::character('I') ? jump(HUB + 36) : error();
            case HUB + 36:
                return input == catta::json::Token::character('d') ? jump(HUB + 37) : error();
            case HUB + 37:
                return input == catta::json::Token::closeString() ? jump(HUB + 38) : error();
            case HUB + 38:
                return !_modbusIdParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 39:
                return handle(_modbusIdParser);
            case HUB + 40:
                return input == catta::json::Token::character('o') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('m') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('i') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('n') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('a') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('l') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('P') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('o') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('w') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('e') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('r') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::closeString() ? jump(HUB + 52) : error();
            case HUB + 52:
                return !_nominalPowerParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 53:
                return handle(_nominalPowerParser);
            case HUB + 54:
                return input == catta::json::Token::character('p') ? jump(HUB + 55) : error();
            case HUB + 55:
                return input == catta::json::Token::character('e') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('r') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('a') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('t') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('i') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('n') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('g') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('H') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('o') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('u') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('r') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('s') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::closeString() ? jump(HUB + 68) : error();
            case HUB + 68:
                return !_operatingHoursParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 69:
                return handle(_operatingHoursParser);
            case HUB + 70:
                return input == catta::json::Token::character('o')   ? jump(HUB + 77)
                       : input == catta::json::Token::character('h') ? jump(HUB + 71)
                                                                     : error();
            case HUB + 71:
                return input == catta::json::Token::character('a') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('s') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('e') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::closeString() ? jump(HUB + 75) : error();
            case HUB + 75:
                return !_phaseParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 76:
                return handle(_phaseParser);
            case HUB + 77:
                return input == catta::json::Token::character('w') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('e') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('r') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('L') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('i') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::character('m') ? jump(HUB + 83) : error();
            case HUB + 83:
                return input == catta::json::Token::character('i') ? jump(HUB + 84) : error();
            case HUB + 84:
                return input == catta::json::Token::character('t') ? jump(HUB + 85) : error();
            case HUB + 85:
                return input == catta::json::Token::character('a') ? jump(HUB + 86) : error();
            case HUB + 86:
                return input == catta::json::Token::character('t') ? jump(HUB + 87) : error();
            case HUB + 87:
                return input == catta::json::Token::character('i') ? jump(HUB + 88) : error();
            case HUB + 88:
                return input == catta::json::Token::character('o') ? jump(HUB + 89) : error();
            case HUB + 89:
                return input == catta::json::Token::character('n') ? jump(HUB + 90) : error();
            case HUB + 90:
                return input == catta::json::Token::closeString() ? jump(HUB + 91) : error();
            case HUB + 91:
                return !_powerLimitationParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 92:
                return handle(_powerLimitationParser);
            case HUB + 93:
                return input == catta::json::Token::character('e') ? jump(HUB + 94) : error();
            case HUB + 94:
                return input == catta::json::Token::character('r') ? jump(HUB + 95) : error();
            case HUB + 95:
                return input == catta::json::Token::character('i') ? jump(HUB + 96) : error();
            case HUB + 96:
                return input == catta::json::Token::character('a') ? jump(HUB + 97) : error();
            case HUB + 97:
                return input == catta::json::Token::character('l') ? jump(HUB + 98) : error();
            case HUB + 98:
                return input == catta::json::Token::character('N') ? jump(HUB + 99) : error();
            case HUB + 99:
                return input == catta::json::Token::character('u') ? jump(HUB + 100) : error();
            case HUB + 100:
                return input == catta::json::Token::character('m') ? jump(HUB + 101) : error();
            case HUB + 101:
                return input == catta::json::Token::character('b') ? jump(HUB + 102) : error();
            case HUB + 102:
                return input == catta::json::Token::character('e') ? jump(HUB + 103) : error();
            case HUB + 103:
                return input == catta::json::Token::character('r') ? jump(HUB + 104) : error();
            case HUB + 104:
                return input == catta::json::Token::closeString() ? jump(HUB + 105) : error();
            case HUB + 105:
                return !_serialNumberParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 106:
                return handle(_serialNumberParser);
            case HUB + 107:
                return input == catta::json::Token::character('y') ? jump(HUB + 108) : error();
            case HUB + 108:
                return input == catta::json::Token::character('p') ? jump(HUB + 109) : error();
            case HUB + 109:
                return input == catta::json::Token::character('e') ? jump(HUB + 110) : error();
            case HUB + 110:
                return input == catta::json::Token::closeString() ? jump(HUB + 111) : error();
            case HUB + 111:
                return !_typeParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 112:
                return handle(_typeParser);
            case HUB + 113:
                return input == catta::json::Token::character('o') ? jump(HUB + 114) : error();
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
                return input == catta::json::Token::character('T') ? jump(HUB + 120) : error();
            case HUB + 120:
                return input == catta::json::Token::character('y') ? jump(HUB + 121) : error();
            case HUB + 121:
                return input == catta::json::Token::character('p') ? jump(HUB + 122) : error();
            case HUB + 122:
                return input == catta::json::Token::character('e') ? jump(HUB + 123) : error();
            case HUB + 123:
                return input == catta::json::Token::closeString() ? jump(HUB + 124) : error();
            case HUB + 124:
                return !_voltageTypeParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 125:
                return handle(_voltageTypeParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_serialNumberParser.data(), _typeParser.data(), _voltageTypeParser.data(), _nominalPowerParser.data(),
                                               _cosphiParser.data(), _gridSupplyDailySumParser.data(), _powerLimitationParser.data(),
                                               _operatingHoursParser.data(), _phaseParser.data(), _modbusIdParser.data())
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
    Parser<catta::modbus::sunspec::ValueU16> _cosphiParser;
    Parser<catta::modbus::sunspec::ValueU32> _gridSupplyDailySumParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 15>> _modbusIdParser;
    Parser<catta::modbus::sunspec::ValueU8<1, 32>> _nominalPowerParser;
    Parser<catta::modbus::sunspec::ValueU32> _operatingHoursParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 3>> _phaseParser;
    Parser<catta::modbus::sunspec::ValueU16> _powerLimitationParser;
    Parser<catta::modbus::sunspec::ValueU16> _serialNumberParser;
    Parser<catta::modbus::si::Type> _typeParser;
    Parser<catta::modbus::sunspec::ValueU8<1, 10>> _voltageTypeParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 126;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
