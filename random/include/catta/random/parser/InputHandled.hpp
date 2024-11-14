#pragma once

// catta
#include <catta/parser/InputHandled.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::parser::InputHandled>
{
  public:
    Create(Random& random) : _value(random.create<bool>() ? catta::parser::InputHandled::yes() : catta::parser::InputHandled::no()) {}
    operator catta::parser::InputHandled() const { return _value; }

  private:
    catta::parser::InputHandled _value;
};
