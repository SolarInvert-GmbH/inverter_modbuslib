#pragma once

// catta
#include <catta/parser/TextPosition.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::parser::TextPosition>
{
  public:
    Create(Random& random)
        : _value(catta::parser::TextPosition(random.interval(std::size_t(1), std::size_t(1 << 15)),
                                             random.interval(std::size_t(1), std::size_t(1 << 15))))
    {
    }
    operator catta::parser::TextPosition() const { return _value; }

  private:
    catta::parser::TextPosition _value;
};
