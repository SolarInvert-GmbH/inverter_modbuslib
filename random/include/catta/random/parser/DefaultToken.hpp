#pragma once

// catta
#include <catta/parser/DefaultToken.hpp>

// random
#include <catta/random/Random.hpp>

template <class Character, catta::parser::ErrorConcept Error>
class catta::random::Create<catta::parser::DefaultToken<Character, Error>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::parser::DefaultToken<Character, Error>() const { return _value; }

  private:
    catta::parser::DefaultToken<Character, Error> _value;
    static catta::parser::DefaultToken<Character, Error> create(Random& random)
    {
        switch (random.create<catta::parser::DefaultTokenType>())
        {
            case catta::parser::DefaultTokenType::end():
                return catta::parser::DefaultToken<Character, Error>::end();
            case catta::parser::DefaultTokenType::value():
                return catta::parser::DefaultToken<Character, Error>::character(random.create<Character>());
            default:
                return catta::parser::DefaultToken<Character, Error>::error(random.create<Error>());
        }
    }
};
