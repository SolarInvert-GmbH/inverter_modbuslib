#pragma once

// catta
#include <catta/modbus/Token.hpp>

// random
#include <catta/random/modbus/TokenType.hpp>

template <>
class catta::random::Create<catta::modbus::Token>
{
  public:
    Create(Random& random) : _value(raw(random)) {}
    operator catta::modbus::Token() const { return _value; }

  private:
    catta::modbus::Token _value;
    static catta::modbus::Token raw(Random& random)
    {
        using Type = catta::modbus::TokenType;
        using Token = catta::modbus::Token;
        switch (random.create<Type>())
        {
            case Type::address():
                return Token::address(random.create<std::uint8_t>());
            case Type::function():
                return Token::function(random.create<std::uint8_t>());
            case Type::length():
                return Token::length(random.create<std::uint8_t>());
            case Type::data():
                return Token::data(random.create<std::uint8_t>());
            default:
                return Token::end();
        }
    }
};
