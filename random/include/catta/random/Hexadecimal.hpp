#pragma once

// catta
#include <catta/Hexadecimal.hpp>

// random
#include <catta/random/Random.hpp>

template <std::integral INTEGRAL>
class catta::random::Create<catta::Hexadecimal<INTEGRAL>>
{
  public:
    Create(Random& random) : _value(catta::Hexadecimal<INTEGRAL>(Create<INTEGRAL>(random))) {}
    operator catta::Hexadecimal<INTEGRAL>() const { return _value; }

  private:
    catta::Hexadecimal<INTEGRAL> _value;
};
