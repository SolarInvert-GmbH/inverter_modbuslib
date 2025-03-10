#pragma once

// si
#include <catta/modbus/si/RegisterValue.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/RegisterAddress.hpp>
#include <catta/fromjson/modbus/sunspec/String.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU32.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU64.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::RegisterValue>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::RegisterValue;
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
        const auto handleNumber = [this, jump, input]()
        {
            _token = input;
            return jump(HUB + 27);
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('v')   ? jump(HUB + 19)
                       : input == catta::json::Token::character('r') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('e') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('g') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('i') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('s') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('t') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('e') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('r') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('A') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('d') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('d') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('r') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('e') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('s') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('s') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::closeString() ? jump(HUB + 17) : error();
            case HUB + 17:
                return !_registerAddressParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 18:
                return handle(_registerAddressParser);
            case HUB + 19:
                return input == catta::json::Token::character('a') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('l') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('u') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('e') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::closeString() ? jump(HUB + 24) : error();
            case HUB + 24:
                return _index != 0 || !_token.isEmpty() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 25:
                return input == catta::json::Token::openString() ? next() : input.type().isIntegerNumber() ? handleNumber() : error();
            case HUB + 26:
                switch (input.type())
                {
                    case catta::json::TokenType::character():
                        if (_index > 31) return error();
                        _string[_index] = static_cast<char>(input.unicodeCharacterValue());
                        _index++;
                        return stay();
                    case catta::json::TokenType::closeString():
                        if (_index == 0) return error();
                        return next();
                    default:
                        return error();
                }
            case HUB + 27:
                return input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                       : input == catta::json::Token::comma()           ? jump(HUB + 0)
                                                                        : error();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _string{}, _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE) return Output::empty();
        using Type = catta::modbus::si::RegisterType;
        switch (_registerAddressParser.data().type())
        {
            case Type::uint16():
            case Type::sint16():
            case Type::scaleFactor():
            case Type::connectedPhase():
                if (!_token.type().isIntegerNumber() || _token.integerValue() < MINU16 || _token.integerValue() > MAXU16) return Output::empty();
                return Output::value16(_registerAddressParser.data(),
                                       catta::modbus::sunspec::ValueU16::create(static_cast<std::uint16_t>(_token.integerValue())));
            case Type::uint32():
                if (!_token.type().isIntegerNumber() || _token.integerValue() < MINU32 || _token.integerValue() > MAXU32) return Output::empty();
                return Output::value32(_registerAddressParser.data(),
                                       catta::modbus::sunspec::ValueU32::create(static_cast<std::uint32_t>(_token.integerValue())));
            case Type::uint64():
                if (!_token.type().isIntegerNumber()) return Output::empty();
                return Output::value64(_registerAddressParser.data(),
                                       catta::modbus::sunspec::ValueU64::create(static_cast<std::uint64_t>(_token.integerValue())));
            case Type::string32():
                return Output::string(_registerAddressParser.data(), catta::modbus::sunspec::String::create(_string.data()));
            default:
                return Output::empty();
        }
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
    Parser<catta::modbus::si::RegisterAddress> _registerAddressParser;
    Parser<catta::modbus::sunspec::ValueU16> _valueU16Parser;
    Parser<catta::modbus::sunspec::ValueU32> _valueU32Parser;
    Parser<catta::modbus::sunspec::ValueU64> _valueU64Parser;
    Parser<catta::modbus::sunspec::String> _valueStringParser;
    Input _token;
    std::array<char, 33> _string;
    std::uint8_t _index;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 28;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
    static constexpr std::uint16_t MINU16 = 0;
    static constexpr std::uint32_t MINU32 = 0;
    static constexpr std::uint16_t MAXU16 = 0xffff;
    static constexpr std::uint32_t MAXU32 = 0xffffffff;
};
}  // namespace fromjson
}  // namespace catta
