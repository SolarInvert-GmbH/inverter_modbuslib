#pragma once

// json
#include <catta/json/Token.hpp>

// parser
#include <catta/parser/DefaultToken.hpp>

// state
#include <catta/state/DefaultError.hpp>

// tostring
#include <catta/tostring/Decimal.hpp>
#include <catta/tostring/FixedPointNumber.hpp>

// catta
#include <catta/Hexadecimal.hpp>

namespace catta
{
namespace json
{
/**
 * @brief Serializes json files according rfc 8259.
 *
 * Can only process utf32_t strings.
 *
 * @author CattaTech - Maik Urbannek
 */
class Serializer
{
  public:
    /**
     * Error type.
     */
    using Error = catta::state::DefaultError;
    /**
     * Input type. char32_t
     */
    using Input = catta::json::Token;
    /**
     * Output Token type.
     */
    using Token = catta::parser::DefaultToken<char32_t, Error>;
    /**
     * Constructor.
     */
    [[nodiscard]] constexpr Serializer() noexcept : _state(STATE_START) {}
    /**
     * Can only process utf8 strings. Uses rfc 8259.
     * @param[in] input The json token.
     * @return Returns the pair of result token and information whether input was handled or not. If the input was not handled the read methode has to
     * be called again with the same input.
     */
    [[nodiscard]] constexpr std::tuple<Token, catta::parser::InputHandled> read(const Input input) noexcept
    {
        using Handled = catta::parser::InputHandled;
        using Tuple = std::tuple<Token, Handled>;
        const auto error = [this]()
        {
            _state = STATE_ERROR;
            return Tuple{Token::error(Error::error()), Handled::yes()};
        };
        const auto result = [this](const Handled handled, const std::uint8_t state, const char32_t c)
        {
            _state = state;
            return Tuple{Token::character(c), handled};
        };
        const auto done = [this]()
        {
            _state = STATE_DONE;
            return Tuple{Token::end(), Handled::yes()};
        };
        const auto isInEndState = [](auto serializer, const auto value)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            return serializer.state().isDone();
        };
        const auto character = [result](const char c, const std::uint8_t state)
        {
            const Handled handled = state == STATE_READY + 0 ? Handled::yes() : Handled::no();
            const char32_t c32 = static_cast<char32_t>(c);
            return result(handled, state, c32);
        };
        const auto handleInteger = [this, input, result, isInEndState]()
        {
            const auto value = catta::Decimal(input.integerValue());
            [[maybe_unused]] auto ignore = _serializerInteger.read(value);
            const char32_t data = static_cast<char32_t>(_serializerInteger.data());
            if (isInEndState(_serializerInteger, value)) return result(Handled::yes(), STATE_READY + 0, data);
            return result(Handled::no(), STATE_INTEGER + 0, data);
        };
        const auto handleFloat = [this, input, result, isInEndState]()
        {
            const auto value = catta::FixedPointNumber<8>::create(static_cast<int64_t>(input.floatValue() * 100'000'000.0));
            [[maybe_unused]] auto ignore = _serializerFloat.read(value);
            const char32_t data = static_cast<char32_t>(_serializerFloat.data());
            if (isInEndState(_serializerFloat, value)) return result(Handled::yes(), STATE_READY + 0, data);
            return result(Handled::no(), STATE_FLOAT + 0, data);
        };
        const auto handleHex = [input, character](const std::uint8_t state, const std::uint8_t i)
        {
            const std::uint8_t h = static_cast<std::uint8_t>(input.unicodeCharacterValue() >> ((3 - i) * 4));
            const char c = catta::halfByteToHexadecimal(h);
            return character(c, state);
        };

        const auto handleCharacter = [input, character, result]()
        {
            switch (input.unicodeCharacterValue())
            {
                case '"':
                    return character('\\', STATE_ESCAPE_QUOTES + 0);
                case '\\':
                    return character('\\', STATE_ESCAPE_BACKSLASH + 0);
                case '\b':
                    return character('\\', STATE_ESCAPE_B + 0);
                case '\f':
                    return character('\\', STATE_ESCAPE_F + 0);
                case '\n':
                    return character('\\', STATE_ESCAPE_N + 0);
                case '\r':
                    return character('\\', STATE_ESCAPE_R + 0);
                case '\t':
                    return character('\\', STATE_ESCAPE_T + 0);
                default:
                    return input.unicodeCharacterValue() < ' ' ? character('\\', STATE_ESCAPE_HEX + 0)
                                                               : result(Handled::yes(), STATE_READY + 0, input.unicodeCharacterValue());
            }
        };

        const auto handleToken = [input, character, handleInteger, handleFloat, error, done, handleCharacter, this]()
        {
            using Type = catta::json::TokenType;
            switch (input.type())
            {
                case Type::openCurlyBracket():
                    return character('{', STATE_READY + 0);
                case Type::closeCurlyBracket():
                    return character('}', STATE_READY + 0);
                case Type::openSquareBracket():
                    return character('[', STATE_READY + 0);
                case Type::closeSquareBracket():
                    return character(']', STATE_READY + 0);
                case Type::colon():
                    return character(':', STATE_READY + 0);
                case Type::comma():
                    return character(',', STATE_READY + 0);
                case Type::nullObject():
                    return character('n', STATE_NULL + 0);
                case Type::boolTrue():
                    return character('t', STATE_TRUE + 0);
                case Type::boolFalse():
                    return character('f', STATE_FALSE + 0);
                case Type::integerNumber():
                    _serializerInteger = {};
                    return handleInteger();
                case Type::floatNumber():
                    _serializerFloat = {};
                    return handleFloat();
                case Type::openString():
                case Type::closeString():
                    return character('"', STATE_READY + 0);
                case Type::character():
                    return handleCharacter();
                case Type::end():
                    return done();
                default:
                    return error();
            }
        };
        switch (_state)
        {
            case STATE_START + 0:
            case STATE_READY + 0:
                return handleToken();
            case STATE_NULL + 0:
                return character('u', STATE_NULL + 1);
            case STATE_NULL + 1:
                return character('l', STATE_NULL + 2);
            case STATE_NULL + 2:
                return character('l', STATE_READY + 0);
            case STATE_TRUE + 0:
                return character('r', STATE_TRUE + 1);
            case STATE_TRUE + 1:
                return character('u', STATE_TRUE + 2);
            case STATE_TRUE + 2:
                return character('e', STATE_READY + 0);
            case STATE_FALSE + 0:
                return character('a', STATE_FALSE + 1);
            case STATE_FALSE + 1:
                return character('l', STATE_FALSE + 2);
            case STATE_FALSE + 2:
                return character('s', STATE_FALSE + 3);
            case STATE_FALSE + 3:
                return character('e', STATE_READY + 0);
            case STATE_INTEGER + 0:
                return handleInteger();
            case STATE_FLOAT + 0:
                return handleFloat();
            case STATE_ESCAPE_QUOTES + 0:
                return character('"', STATE_READY + 0);
            case STATE_ESCAPE_BACKSLASH + 0:
                return character('\\', STATE_READY + 0);
            case STATE_ESCAPE_B + 0:
                return character('b', STATE_READY + 0);
            case STATE_ESCAPE_F + 0:
                return character('f', STATE_READY + 0);
            case STATE_ESCAPE_N + 0:
                return character('n', STATE_READY + 0);
            case STATE_ESCAPE_R + 0:
                return character('r', STATE_READY + 0);
            case STATE_ESCAPE_T + 0:
                return character('t', STATE_READY + 0);
            case STATE_ESCAPE_HEX + 0:
                return character('u', STATE_READY + 0);
            case STATE_ESCAPE_HEX + 1:
                return handleHex(STATE_ESCAPE_HEX + 2, 0);
            case STATE_ESCAPE_HEX + 2:
                return handleHex(STATE_ESCAPE_HEX + 3, 1);
            case STATE_ESCAPE_HEX + 3:
                return handleHex(STATE_ESCAPE_HEX + 4, 2);
            case STATE_ESCAPE_HEX + 4:
                return handleHex(STATE_READY + 0, 3);
            default:
                return error();
        }
    }
    /**
     * @return Returns the state of the parser.
     */
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case STATE_START:
                return catta::parser::State::start();
            case STATE_DONE:
                return catta::parser::State::done();
            default:
                return _state >= STATE_ERROR ? catta::parser::State::failed() : catta::parser::State::running();
        }
    }

  private:
    std::uint8_t _state;
    catta::tostring::Serializer<catta::Decimal<std::int64_t>> _serializerInteger;
    catta::tostring::Serializer<catta::FixedPointNumber<8>> _serializerFloat;

    static constexpr std::uint8_t STATE_START = 0;
    static constexpr std::uint8_t STATE_READY = STATE_START + 1;
    static constexpr std::uint8_t STATE_NULL = STATE_READY + 1;
    static constexpr std::uint8_t STATE_TRUE = STATE_NULL + 3;
    static constexpr std::uint8_t STATE_FALSE = STATE_TRUE + 3;
    static constexpr std::uint8_t STATE_INTEGER = STATE_FALSE + 4;
    static constexpr std::uint8_t STATE_FLOAT = STATE_INTEGER + 1;
    static constexpr std::uint8_t STATE_ESCAPE_QUOTES = STATE_FLOAT + 1;
    static constexpr std::uint8_t STATE_ESCAPE_BACKSLASH = STATE_ESCAPE_QUOTES + 1;
    static constexpr std::uint8_t STATE_ESCAPE_B = STATE_ESCAPE_BACKSLASH + 1;
    static constexpr std::uint8_t STATE_ESCAPE_F = STATE_ESCAPE_B + 1;
    static constexpr std::uint8_t STATE_ESCAPE_N = STATE_ESCAPE_F + 1;
    static constexpr std::uint8_t STATE_ESCAPE_R = STATE_ESCAPE_N + 1;
    static constexpr std::uint8_t STATE_ESCAPE_T = STATE_ESCAPE_R + 1;
    static constexpr std::uint8_t STATE_ESCAPE_HEX = STATE_ESCAPE_T + 1;
    static constexpr std::uint8_t STATE_DONE = STATE_ESCAPE_HEX + 5;
    static constexpr std::uint8_t STATE_ERROR = STATE_DONE + 1;
};

}  // namespace json
}  // namespace catta
