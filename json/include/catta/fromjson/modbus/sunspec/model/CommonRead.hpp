#pragma once

// model
#include <catta/modbus/sunspec/model/CommonRead.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/sunspec/String.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::model::CommonRead>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::model::CommonRead;
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
                return input == catta::json::Token::character('s')   ? jump(HUB + 37)
                       : input == catta::json::Token::character('m') ? jump(HUB + 17)
                       : input == catta::json::Token::character('d') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('e') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('v') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('i') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('c') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('e') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('A') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('d') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('d') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('r') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('e') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('s') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('s') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::closeString() ? jump(HUB + 15) : error();
            case HUB + 15:
                return !_deviceAddressParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 16:
                return handle(_deviceAddressParser);
            case HUB + 17:
                return input == catta::json::Token::character('o')   ? jump(HUB + 31)
                       : input == catta::json::Token::character('a') ? jump(HUB + 18)
                                                                     : error();
            case HUB + 18:
                return input == catta::json::Token::character('n') ? jump(HUB + 19) : error();
            case HUB + 19:
                return input == catta::json::Token::character('u') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('f') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('a') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('c') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::character('t') ? jump(HUB + 24) : error();
            case HUB + 24:
                return input == catta::json::Token::character('u') ? jump(HUB + 25) : error();
            case HUB + 25:
                return input == catta::json::Token::character('r') ? jump(HUB + 26) : error();
            case HUB + 26:
                return input == catta::json::Token::character('e') ? jump(HUB + 27) : error();
            case HUB + 27:
                return input == catta::json::Token::character('r') ? jump(HUB + 28) : error();
            case HUB + 28:
                return input == catta::json::Token::closeString() ? jump(HUB + 29) : error();
            case HUB + 29:
                return !_manufacturerParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 30:
                return handle(_manufacturerParser);
            case HUB + 31:
                return input == catta::json::Token::character('d') ? jump(HUB + 32) : error();
            case HUB + 32:
                return input == catta::json::Token::character('e') ? jump(HUB + 33) : error();
            case HUB + 33:
                return input == catta::json::Token::character('l') ? jump(HUB + 34) : error();
            case HUB + 34:
                return input == catta::json::Token::closeString() ? jump(HUB + 35) : error();
            case HUB + 35:
                return !_modelParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 36:
                return handle(_modelParser);
            case HUB + 37:
                return input == catta::json::Token::character('e') ? jump(HUB + 38) : error();
            case HUB + 38:
                return input == catta::json::Token::character('r') ? jump(HUB + 39) : error();
            case HUB + 39:
                return input == catta::json::Token::character('i') ? jump(HUB + 40) : error();
            case HUB + 40:
                return input == catta::json::Token::character('a') ? jump(HUB + 41) : error();
            case HUB + 41:
                return input == catta::json::Token::character('l') ? jump(HUB + 42) : error();
            case HUB + 42:
                return input == catta::json::Token::character('N') ? jump(HUB + 43) : error();
            case HUB + 43:
                return input == catta::json::Token::character('u') ? jump(HUB + 44) : error();
            case HUB + 44:
                return input == catta::json::Token::character('m') ? jump(HUB + 45) : error();
            case HUB + 45:
                return input == catta::json::Token::character('b') ? jump(HUB + 46) : error();
            case HUB + 46:
                return input == catta::json::Token::character('e') ? jump(HUB + 47) : error();
            case HUB + 47:
                return input == catta::json::Token::character('r') ? jump(HUB + 48) : error();
            case HUB + 48:
                return input == catta::json::Token::closeString() ? jump(HUB + 49) : error();
            case HUB + 49:
                return !_serialNumberParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 50:
                return handle(_serialNumberParser);
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
                   ? Output::create(_manufacturerParser.data(), _modelParser.data(), _serialNumberParser.data(), _deviceAddressParser.data())
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
    Parser<catta::modbus::sunspec::ValueU16> _deviceAddressParser;
    Parser<catta::modbus::sunspec::String> _manufacturerParser;
    Parser<catta::modbus::sunspec::String> _modelParser;
    Parser<catta::modbus::sunspec::String> _serialNumberParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 51;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
