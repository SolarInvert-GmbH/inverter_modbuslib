#pragma once

// catta
#include <catta/json/Token.hpp>

// random
#include <catta/random/json/ParsingError.hpp>
#include <catta/random/json/TokenType.hpp>

template <>
class catta::random::Create<catta::json::Token>
{
  public:
    Create(Random& random) : _value(raw(random)) {}
    operator catta::json::Token() const { return _value; }

  private:
    catta::json::Token _value;
    static catta::json::Token raw(Random& random)
    {
        using Type = catta::json::TokenType;
        using Token = catta::json::Token;
        using Error = catta::json::ParsingError;
        switch (random.create<Type>())
        {
            case Type::openCurlyBracket():
                return Token::openCurlyBracket();
            case Type::closeCurlyBracket():
                return Token::closeCurlyBracket();
            case Type::openSquareBracket():
                return Token::openSquareBracket();
            case Type::closeSquareBracket():
                return Token::closeSquareBracket();
            case Type::colon():
                return Token::colon();
            case Type::comma():
                return Token::comma();
            case Type::nullObject():
                return Token::nullObject();
            case Type::boolTrue():
                return Token::boolTrue();
            case Type::boolFalse():
                return Token::boolFalse();
            case Type::integerNumber():
                return Token::integerNumber(random.create<std::int64_t>());
            case Type::floatNumber():
                return Token::floatNumber(random.interval(-1.0, 1.0));
            case Type::openString():
                return Token::openString();
            case Type::character():
                return Token::character(random.create<char32_t>());
            case Type::closeString():
                return Token::closeString();
            case Type::end():
                return Token::end();
            default:
                return Token::error(random.create<Error>());
        }
    }
};
