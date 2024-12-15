#pragma once

// response
#include <catta/modbus/si/response/FactoryValues.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/Date.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::FactoryValues>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::FactoryValues;
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
                return input == catta::json::Token::character('s')   ? jump(HUB + 71)
                       : input == catta::json::Token::character('p') ? jump(HUB + 55)
                       : input == catta::json::Token::character('h') ? jump(HUB + 38)
                       : input == catta::json::Token::character('f') ? jump(HUB + 21)
                       : input == catta::json::Token::character('b') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('o') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('o') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('t') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('s') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('t') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('r') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('a') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('p') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('p') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('V') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('e') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('r') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('s') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('i') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::character('o') ? jump(HUB + 17) : error();
            case HUB + 17:
                return input == catta::json::Token::character('n') ? jump(HUB + 18) : error();
            case HUB + 18:
                return input == catta::json::Token::closeString() ? jump(HUB + 19) : error();
            case HUB + 19:
                return !_bootstrappVersionParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 20:
                return handle(_bootstrappVersionParser);
            case HUB + 21:
                return input == catta::json::Token::character('i') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('r') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('m') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('w') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('a') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('r') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('e') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::character('V') ? jump(HUB + 29) : error();
            case HUB + 29:
                return input == catta::json::Token::character('e') ? jump(HUB + 30) : error();
            case HUB + 30:
                return input == catta::json::Token::character('r') ? jump(HUB + 31) : error();
            case HUB + 31:
                return input == catta::json::Token::character('s') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('i') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('o') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::character('n') ? jump(HUB + 35) : error();
            case HUB + 35:
                return input == catta::json::Token::closeString() ? jump(HUB + 36) : error();
            case HUB + 36:
                return !_firmwareVersionParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 37:
                return handle(_firmwareVersionParser);
            case HUB + 38:
                return input == catta::json::Token::character('a') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('r') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('d') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('w') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('a') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('r') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('e') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('V') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('e') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('r') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::character('s') ? jump(HUB + 49) : error();
            case HUB + 49:
                return input == catta::json::Token::character('i') ? jump(HUB + 50) : error();
            case HUB + 50:
                return input == catta::json::Token::character('o') ? jump(HUB + 51) : error();
            case HUB + 51:
                return input == catta::json::Token::character('n') ? jump(HUB + 52) : error();
            case HUB + 52:
                return input == catta::json::Token::closeString() ? jump(HUB + 53) : error();
            case HUB + 53:
                return !_hardwareVersionParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 54:
                return handle(_hardwareVersionParser);
            case HUB + 55:
                return input == catta::json::Token::character('r') ? jump(HUB + 56) : error();
            case HUB + 56:
                return input == catta::json::Token::character('o') ? jump(HUB + 57) : error();
            case HUB + 57:
                return input == catta::json::Token::character('d') ? jump(HUB + 58) : error();
            case HUB + 58:
                return input == catta::json::Token::character('u') ? jump(HUB + 59) : error();
            case HUB + 59:
                return input == catta::json::Token::character('c') ? jump(HUB + 60) : error();
            case HUB + 60:
                return input == catta::json::Token::character('t') ? jump(HUB + 61) : error();
            case HUB + 61:
                return input == catta::json::Token::character('i') ? jump(HUB + 62) : error();
            case HUB + 62:
                return input == catta::json::Token::character('o') ? jump(HUB + 63) : error();
            case HUB + 63:
                return input == catta::json::Token::character('n') ? jump(HUB + 64) : error();
            case HUB + 64:
                return input == catta::json::Token::character('D') ? jump(HUB + 65) : error();
            case HUB + 65:
                return input == catta::json::Token::character('a') ? jump(HUB + 66) : error();
            case HUB + 66:
                return input == catta::json::Token::character('t') ? jump(HUB + 67) : error();
            case HUB + 67:
                return input == catta::json::Token::character('e') ? jump(HUB + 68) : error();
            case HUB + 68:
                return input == catta::json::Token::closeString() ? jump(HUB + 69) : error();
            case HUB + 69:
                return !_productionDateParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 70:
                return handle(_productionDateParser);
            case HUB + 71:
                return input == catta::json::Token::character('e') ? jump(HUB + 72) : error();
            case HUB + 72:
                return input == catta::json::Token::character('r') ? jump(HUB + 73) : error();
            case HUB + 73:
                return input == catta::json::Token::character('i') ? jump(HUB + 74) : error();
            case HUB + 74:
                return input == catta::json::Token::character('a') ? jump(HUB + 75) : error();
            case HUB + 75:
                return input == catta::json::Token::character('l') ? jump(HUB + 76) : error();
            case HUB + 76:
                return input == catta::json::Token::character('n') ? jump(HUB + 77) : error();
            case HUB + 77:
                return input == catta::json::Token::character('u') ? jump(HUB + 78) : error();
            case HUB + 78:
                return input == catta::json::Token::character('m') ? jump(HUB + 79) : error();
            case HUB + 79:
                return input == catta::json::Token::character('b') ? jump(HUB + 80) : error();
            case HUB + 80:
                return input == catta::json::Token::character('e') ? jump(HUB + 81) : error();
            case HUB + 81:
                return input == catta::json::Token::character('r') ? jump(HUB + 82) : error();
            case HUB + 82:
                return input == catta::json::Token::closeString() ? jump(HUB + 83) : error();
            case HUB + 83:
                return !_serialnumberParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 84:
                return handle(_serialnumberParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(_serialnumberParser.data(), _productionDateParser.data(), _hardwareVersionParser.data(),
                                               _firmwareVersionParser.data(), _bootstrappVersionParser.data())
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
    Parser<catta::modbus::sunspec::ValueU8<0, 255>> _bootstrappVersionParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 255>> _firmwareVersionParser;
    Parser<catta::modbus::sunspec::ValueU8<0, 255>> _hardwareVersionParser;
    Parser<catta::modbus::si::Date> _productionDateParser;
    Parser<catta::modbus::sunspec::ValueU16> _serialnumberParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 85;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
