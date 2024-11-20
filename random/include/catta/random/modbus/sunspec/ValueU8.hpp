#pragma once

// catta
#include <catta/modbus/sunspec/ValueU8.hpp>

// random
#include <catta/random/Random.hpp>

template <std::uint8_t MIN, std::uint8_t MAX>
class catta::random::Create<catta::modbus::sunspec::ValueU8<MIN, MAX>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueU8<MIN, MAX>() const { return _value; }

  private:
    catta::modbus::sunspec::ValueU8<MIN, MAX> _value;
    static catta::modbus::sunspec::ValueU8<MIN, MAX> create(Random& random)
    {
        return catta::modbus::sunspec::ValueU8<MIN, MAX>::create(random.interval(MIN, MAX));
    }
};
