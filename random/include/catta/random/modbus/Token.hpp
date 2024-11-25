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
            case Type::start():
                return Token::start();
            case Type::function():
                return Token::function(random.create<std::uint8_t>());
            case Type::data():
                return Token::data(random.create<std::uint8_t>());
            case Type::exeception():
                return Token::exeception();
            case Type::code():
                return Token::code(random.interval(std::uint8_t(1), std::uint8_t(4)));
            default:
                return Token::end();
        }
    }
};
