#pragma once

// catta
#include <catta/modbus/sunspec/ValueU16.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ValueU16>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueU16() const { return _value; }

  private:
    catta::modbus::sunspec::ValueU16 _value;
    static catta::modbus::sunspec::ValueU16 create(Random& random)
    {
        return catta::modbus::sunspec::ValueU16::create(random.create<std::uint16_t>());
    }
};
