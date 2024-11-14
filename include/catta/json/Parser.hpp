#pragma once

// catta
#include <catta/Hexadecimal.hpp>
#include <catta/json/Token.hpp>
#include <catta/parser/SequenceParserConcept.hpp>

// std
#include <array>
#include <cmath>
#include <variant>

namespace catta
{
namespace json
{
/**
 * @brief Performes lexical analysis for json files according rfc 8259.
 *
 * Can only process utf8 strings.
 *
 * @author CattaTech - Maik Urbannek
 */
class Parser
{
  private:
    typedef std::tuple<catta::json::Token, catta::parser::InputHandled> Tuple;

  public:
    /**
     * Input type. char32_t
     */
    typedef char32_t Input;
    /**
     * Output Token type.
     */
    typedef catta::json::Token Token;
    /**
     * Constructor.
     */
    [[nodiscard]] constexpr Parser() noexcept : _state(START_STATE) {}
    /**
     * Processes the next character and returns the result token (with position in file/string). The end of the string has also to be parsed and will
     * produce an end token. After reading the end token an catta::json::Token::Error::jsonEnded() error is returned. The parsing stops on the end
     * token and on error token.
     *
     * Can only process utf8 strings. Uses rfc 8259.
     * @param[in] input The next character.
     * @return Returns the pair of result token and information whether input was handled or not. If the input was not handled the read methode has to
     * be called again with the same input. The read methode will never return not handled more than once in a row.
     */
    [[nodiscard]] constexpr std::tuple<Token, catta::parser::InputHandled> read(const Input input) noexcept
    {
        typedef catta::parser::InputHandled Handled;
        const auto stay = [] { return Tuple{Token{}, Handled::yes()}; };
        const auto next = [this](const std::uint8_t nextState, const Token token)
        {
            _state = nextState;
            return Tuple{token, Handled::yes()};
        };
        const auto error = [this, next](const catta::json::ParsingError message)
        {
            _data = message;
            return next(ERROR_STATE, catta::json::Token::error(message));
        };
        const auto tokenEnded = [input]()
        {
            return input == '"' || input == ' ' || input == '\t' || input == '\n' || input == '\r' || input == ':' || input == ',' || input == '{' ||
                   input == '}' || input == '[' || input == ']' || input == '\0';
        };
        const auto handleHubState = [this, input]()
        {
            const auto next = [this](const std::uint8_t nextState, const catta::json::Token token)
            {
                _state = nextState;
                return token;
            };
            if (input == 't') return next(TRUE_STATE, catta::json::Token{});
            if (input == 'f') return next(FALSE_STATE, catta::json::Token{});
            if (input == 'n') return next(NULL_STATE, catta::json::Token{});
            if (input == '0') return next(NUMBER_STATE + 0, catta::json::Token{});
            if (input == '-')
            {
                _data = Number{};
                return std::get<Number>(_data).readMinus(input, next(NUMBER_STATE + 1, catta::json::Token{}));
            }
            if (input >= '1' && input <= '9')
            {
                _data = Number{};
                return std::get<Number>(_data).readInteger(input, next(NUMBER_STATE + 2, catta::json::Token{}));
            }
            if (input == '"') return next(STRING_STATE, catta::json::Token::openString());
            if (input == ' ' || input == '\t' || input == '\n' || input == '\r') return next(BASE_STATE, catta::json::Token{});
            if (input == ':') return next(BASE_STATE, catta::json::Token::colon());
            if (input == ',') return next(BASE_STATE, catta::json::Token::comma());
            if (input == '{') return next(BASE_STATE, catta::json::Token::openCurlyBracket());
            if (input == '}') return next(BASE_STATE, catta::json::Token::closeCurlyBracket());
            if (input == '[') return next(BASE_STATE, catta::json::Token::openSquareBracket());
            if (input == ']') return next(BASE_STATE, catta::json::Token::closeSquareBracket());
            if (input == '\0') return next(END_STATE, catta::json::Token::end());
            _data = catta::json::ParsingError::unexpectedLiteral();
            return next(ERROR_STATE, catta::json::Token::error(std::get<catta::json::ParsingError>(_data)));
        };
        const auto finalState = [this](const catta::json::Token firstToken)
        {
            _state = BASE_STATE;
            return Tuple{firstToken, Handled::no()};
        };
        const auto finalNumberState = [this, finalState](const catta::json::Token numberToken)
        {
            _data = Number{};
            return finalState(numberToken);
        };
        const auto handleHex = [this, input, error](const std::uint8_t shift, std::uint16_t& u16, const auto result)
        {
            const auto hex = hexadecimalToHalfByte(input);
            if (!hex) return error(catta::json::ParsingError::badEscapeUnicodeSequence());
            u16 = uint16_t(u16 | (hex.value() << shift));
            const auto& _u16 = std::get<std::array<std::uint16_t, 2>>(_data);
            return result(_u16[0], _u16[1]);
        };
        const auto uNone = [this, stay](const std::uint16_t, const std::uint16_t)
        {
            _state++;
            return stay();
        };
        const auto isHighSurrogates = [](const char16_t c) { return (0xFC00 & c) == 0xD800; };
        const auto isLowSurrogates = [](const char16_t c) { return (0xFC00 & c) == 0xDC00; };
        const auto uFirst = [error, next, isLowSurrogates, isHighSurrogates](const std::uint16_t u160, const std::uint16_t)
        {
            if (isLowSurrogates(u160)) return error(catta::json::ParsingError::badEscapeUnicodeSequence());
            if (isHighSurrogates(u160)) return next(STRING_STATE + 6, Token{});
            return next(STRING_STATE + 0, catta::json::Token::character(u160));
        };
        const auto uSecond = [error, next, isLowSurrogates](const std::uint16_t u160, const std::uint16_t u161)
        {
            if (isLowSurrogates(u161))
            {
                const char32_t utf32 = static_cast<char32_t>(0x00010000 + (((u160 & 0x03FF) << 10) | (u161 & 0x03FF)));
                return next(STRING_STATE + 0, catta::json::Token::character(utf32));
            }
            return error(catta::json::ParsingError::badEscapeUnicodeSequence());
        };
        switch (_state)
        {
            case START_STATE:
            case BASE_STATE:
                return Tuple{handleHubState(), Handled::yes()};
            case TRUE_STATE + 0:
                if (input == 'r') return next(TRUE_STATE + 1, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case TRUE_STATE + 1:
                if (input == 'u') return next(TRUE_STATE + 2, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case TRUE_STATE + 2:
                if (input == 'e') return next(TRUE_STATE + 3, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case TRUE_STATE + 3:
                if (tokenEnded()) return finalState(catta::json::Token::boolTrue());
                return error(catta::json::ParsingError::unexpectedLiteral());
            case FALSE_STATE + 0:
                if (input == 'a') return next(FALSE_STATE + 1, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case FALSE_STATE + 1:
                if (input == 'l') return next(FALSE_STATE + 2, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case FALSE_STATE + 2:
                if (input == 's') return next(FALSE_STATE + 3, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case FALSE_STATE + 3:
                if (input == 'e') return next(FALSE_STATE + 4, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case FALSE_STATE + 4:
                if (tokenEnded()) return finalState(catta::json::Token::boolFalse());
                return error(catta::json::ParsingError::unexpectedLiteral());
            case NULL_STATE + 0:
                if (input == 'u') return next(NULL_STATE + 1, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case NULL_STATE + 1:
                if (input == 'l') return next(NULL_STATE + 2, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case NULL_STATE + 2:
                if (input == 'l') return next(NULL_STATE + 3, Token{});
                return error(catta::json::ParsingError::unexpectedLiteral());
            case NULL_STATE + 3:
                if (tokenEnded()) return finalState(catta::json::Token::nullObject());
                return error(catta::json::ParsingError::unexpectedLiteral());
            case NUMBER_STATE + 0:
                if (input == '.') return next(NUMBER_STATE + 3, Token{});
                if (tokenEnded()) return finalNumberState(catta::json::Token::integerNumber(0));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 1:
                if (input == '0') return next(NUMBER_STATE + 0, Token{});
                if (input >= '1' && input <= '9') return std::get<Number>(_data).readInteger(input, next(NUMBER_STATE + 2, Token{}));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 2:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readInteger(input, stay());
                if (input == '.') return next(NUMBER_STATE + 3, Token{});
                if (tokenEnded()) return finalNumberState(catta::json::Token::integerNumber(std::get<Number>(_data).getInteger()));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 3:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readFraction(input, next(NUMBER_STATE + 4, Token{}));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 4:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readFraction(input, stay());
                if (input == 'e' || input == 'E') return next(NUMBER_STATE + 5, Token{});
                if (tokenEnded()) return finalNumberState(catta::json::Token::floatNumber(std::get<Number>(_data).getFraction()));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 5:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readExponent(input, next(NUMBER_STATE + 7, Token{}));
                if (input == '+' || input == '-') return std::get<Number>(_data).readMinusExponent(input, next(NUMBER_STATE + 6, Token{}));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 6:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readExponent(input, next(NUMBER_STATE + 7, Token{}));
                return error(catta::json::ParsingError::badFormedNumber());
            case NUMBER_STATE + 7:
                if (input >= '0' && input <= '9') return std::get<Number>(_data).readExponent(input, stay());
                if (tokenEnded()) return finalNumberState(catta::json::Token::floatNumber(std::get<Number>(_data).getExponent()));
                return error(catta::json::ParsingError::badFormedNumber());
            case STRING_STATE + 0:
                if (input == '"') return next(BASE_STATE, catta::json::Token::closeString());
                if (input == '\\') return next(STRING_STATE + 1, Token{});
                if (input == '\0') return error(catta::json::ParsingError::stringNotClosed());
                if (input <= 0x1f) return error(catta::json::ParsingError::acsiiControlNotAllowed());
                return next(STRING_STATE + 0, catta::json::Token::character(input));
            case STRING_STATE + 1:
                switch (input)
                {
                    case '"':
                    case '\\':
                    case '/':
                        return next(STRING_STATE + 0, catta::json::Token::character(input));
                    case 'b':
                        return next(STRING_STATE + 0, catta::json::Token::character('\b'));
                    case 'f':
                        return next(STRING_STATE + 0, catta::json::Token::character('\f'));
                    case 'n':
                        return next(STRING_STATE + 0, catta::json::Token::character('\n'));
                    case 'r':
                        return next(STRING_STATE + 0, catta::json::Token::character('\r'));
                    case 't':
                        return next(STRING_STATE + 0, catta::json::Token::character('\t'));
                    case 'u':
                        _data = std::array<std::uint16_t, 2>{0, 0};
                        return next(STRING_STATE + 2, Token{});
                    default:
                        return error(catta::json::ParsingError::unknownEscapeSequence());
                }
            case STRING_STATE + 2:
                return handleHex(12, std::get<std::array<std::uint16_t, 2>>(_data)[0], uNone);
            case STRING_STATE + 3:
                return handleHex(8, std::get<std::array<std::uint16_t, 2>>(_data)[0], uNone);
            case STRING_STATE + 4:
                return handleHex(4, std::get<std::array<std::uint16_t, 2>>(_data)[0], uNone);
            case STRING_STATE + 5:
                return handleHex(0, std::get<std::array<std::uint16_t, 2>>(_data)[0], uFirst);
            case STRING_STATE + 6:
                if (input == '\\') return next(STRING_STATE + 7, Token{});
                return error(catta::json::ParsingError::badEscapeUnicodeSequence());
            case STRING_STATE + 7:
                if (input == 'u') return next(STRING_STATE + 8, Token{});
                return error(catta::json::ParsingError::badEscapeUnicodeSequence());
            case STRING_STATE + 8:
                return handleHex(12, std::get<std::array<std::uint16_t, 2>>(_data)[1], uNone);
            case STRING_STATE + 9:
                return handleHex(8, std::get<std::array<std::uint16_t, 2>>(_data)[1], uNone);
            case STRING_STATE + 10:
                return handleHex(4, std::get<std::array<std::uint16_t, 2>>(_data)[1], uNone);
            case STRING_STATE + 11:
                return handleHex(0, std::get<std::array<std::uint16_t, 2>>(_data)[1], uSecond);
            case END_STATE:
                return error(catta::json::ParsingError::jsonEnded());
            case ERROR_STATE:
                return error(std::get<catta::json::ParsingError>(_data));
            default:
                return error(catta::json::ParsingError::internalParserError());
        }
    }
    /**
     * @return Returns the state of the parser.
     */
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START_STATE:
                return catta::parser::State::start();
            case END_STATE:
                return catta::parser::State::done();
            default:
                return _state >= ERROR_STATE ? catta::parser::State::failed() : catta::parser::State::running();
        }
    }

  private:
    std::uint8_t _state;
    class Number
    {
      public:
        constexpr Number() noexcept : _minus(false), _minusExponent(false), _integer(0), _fraction(0), _fractionInverseFactor(1), _exponent(0) {}

        Tuple readInteger(const char32_t c, const Tuple& result) noexcept
        {
            readI(_integer, c);
            return result;
        }
        Token readInteger(const char32_t c, const Token& result) noexcept
        {
            readI(_integer, c);
            return result;
        }
        Tuple readExponent(const char32_t c, const Tuple& result) noexcept
        {
            readI(_exponent, c);
            return result;
        }
        Tuple readFraction(const char32_t c, const Tuple& result) noexcept
        {
            _fractionInverseFactor *= 10;
            readI(_fraction, c);
            return result;
        }
        Token readMinus(const char32_t c, const Token& result) noexcept
        {
            if (c == '-') _minus = true;
            return result;
        }
        Tuple readMinusExponent(const char32_t c, const Tuple& result) noexcept
        {
            if (c == '-') _minusExponent = true;
            return result;
        }
        constexpr std::int64_t getInteger() const noexcept
        {
            return _minus ? -static_cast<std::int64_t>(_integer) : static_cast<std::int64_t>(_integer);
        }
        constexpr double getFraction() const noexcept
        {
            const double inte = static_cast<double>(_integer);
            const double frac = static_cast<double>(_fraction) / static_cast<double>(_fractionInverseFactor);
            const double value = inte + frac;
            return _minus ? -value : value;
        }
        constexpr double getExponent() const noexcept
        {
            double exp = 0.0;
            if (std::is_constant_evaluated())
            {
                exp = 1.0;
                if (_minusExponent)
                    for (std::uint64_t i = 0; i < _exponent; i++) exp /= 10.0;
                else
                    for (std::uint64_t i = 0; i < _exponent; i++) exp *= 10.0;
                return exp;
            }
            else
            {
                exp = std::pow(10.0, _minusExponent ? -static_cast<int64_t>(_exponent) : static_cast<int64_t>(_exponent));
            }
            return getFraction() * exp;
        }

      private:
        constexpr static void readI(std::uint64_t& n, const char32_t c) noexcept { n = static_cast<std::uint64_t>(c - '0') + n * 10; }
        bool _minus;
        bool _minusExponent;
        std::uint64_t _integer;
        std::uint64_t _fraction;
        std::uint64_t _fractionInverseFactor;
        std::uint64_t _exponent;
    };
    typedef std::variant<Number, std::array<char, 3>, std::array<std::uint16_t, 2>, catta::json::ParsingError> Data;
    Data _data;
    constexpr static std::uint8_t START_STATE = 0;
    constexpr static std::uint8_t BASE_STATE = START_STATE + 1;
    constexpr static std::uint8_t TRUE_STATE = BASE_STATE + 1;
    constexpr static std::uint8_t FALSE_STATE = TRUE_STATE + 5;
    constexpr static std::uint8_t NULL_STATE = FALSE_STATE + 6;
    constexpr static std::uint8_t NUMBER_STATE = NULL_STATE + 5;
    constexpr static std::uint8_t STRING_STATE = NUMBER_STATE + 8;
    constexpr static std::uint8_t END_STATE = STRING_STATE + 12;
    constexpr static std::uint8_t ERROR_STATE = END_STATE + 1;
};

}  // namespace json
}  // namespace catta
