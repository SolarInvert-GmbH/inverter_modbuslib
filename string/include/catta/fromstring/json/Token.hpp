#pragma once

// catta
#include <catta/json/Token.hpp>

// fromstring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::json::Token>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = 7;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto end = [this]()
        {
            _state = 6;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error{}, catta::parser::InputHandled::yes()}; };
        const auto next = [this, stay](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto handle0 = [input, error, stay](auto& parser, const char c, const auto function)
        {
            if (parser.state().isDone()) return input == c ? function() : error();
            if (parser.state().isActive())
            {
                const auto [readError, handled] = parser.read(input);
                if (parser.state().isDone())
                {
                    if (!handled) return input == c ? function() : error();
                    return stay();
                }
                if (readError.isError()) return error();
                return Tuple{Error{}, handled};
            }
            return error();
        };
        const auto handle1 = [input, error](auto& parser, const char c, const auto function)
        {
            const auto [readError, handled] = parser.read(input == c ? '\0' : input);
            if (parser.state().isDone()) return input == c ? function() : error();
            if (parser.state().isFailed()) return error();
            return Tuple{Error{}, handled};
        };
        const auto f = [this, next]()
        {
            using Type = catta::json::TokenType;
            switch (_parser0.data())
            {
                case Type::integerNumber():
                    return next(2);
                case Type::floatNumber():
                    return next(2);
                case Type::character():
                    return next(3);
                case Type::error():
                    return next(4);
                default:
                    return next(1);
            }
        };
        const auto done = [this, error]()
        {
            using Type = catta::json::TokenType;
            using Token = catta::json::Token;
            switch (_parser0.data())
            {
                case Type::openCurlyBracket():
                    _data = Token::openCurlyBracket();
                    break;
                case Type::closeCurlyBracket():
                    _data = Token::closeCurlyBracket();
                    break;
                case Type::openSquareBracket():
                    _data = Token::openSquareBracket();
                    break;
                case Type::closeSquareBracket():
                    _data = Token::closeSquareBracket();
                    break;
                case Type::colon():
                    _data = Token::colon();
                    break;
                case Type::comma():
                    _data = Token::comma();
                    break;
                case Type::nullObject():
                    _data = Token::nullObject();
                    break;
                case Type::boolTrue():
                    _data = Token::boolTrue();
                    break;
                case Type::boolFalse():
                    _data = Token::boolFalse();
                    break;
                case Type::integerNumber():
                    _data = Token::integerNumber(std::int64_t(_parser2.data()));
                    break;
                case Type::floatNumber():
                    _data = Token::floatNumber(std::bit_cast<double>(std::int64_t(_parser2.data())));
                    break;
                case Type::openString():
                    _data = Token::openString();
                    break;
                case Type::character():
                    _data = Token::character(char32_t(std::uint32_t(_parser1.data())));
                    break;
                case Type::closeString():
                    _data = Token::closeString();
                    break;
                case Type::end():
                    _data = Token::end();
                    break;
                case Type::error():
                    _data = Token::error(_parser3.data());
                    break;
                default:
                    return error();
            }

            _state = 5;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        switch (_state)
        {
            case 0:
                return handle0(_parser0, '{', f);
            case 1:
                return input == '}' ? done() : error();
            case 2:
                return handle1(_parser2, '}', done);
            case 3:
                return handle1(_parser1, '}', done);
            case 4:
                return handle0(_parser3, '}', done);
            case 5:
                return input == '\0' ? end() : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(0) {}
    [[nodiscard]] constexpr catta::json::Token data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case 0:
                return _parser0.state();
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return catta::parser::State::running();
            case 6:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    catta::fromstring::Parser<catta::json::TokenType> _parser0;
    catta::fromstring::Parser<catta::Hexadecimal<std::uint32_t>> _parser1;
    catta::fromstring::Parser<catta::Hexadecimal<std::int64_t>> _parser2;
    catta::fromstring::Parser<catta::json::ParsingError> _parser3;
    std::uint8_t _state;
    catta::json::Token _data;
};

}  // namespace fromstring
}  // namespace catta
