#pragma once

// catta
#include <catta/modbus/sunspec/ValueU32.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ValueU32>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueU32() const { return _value; }

  private:
    catta::modbus::sunspec::ValueU32 _value;
    static catta::modbus::sunspec::ValueU32 create(Random& random)
    {
        return catta::modbus::sunspec::ValueU32::create(random.create<std::uint32_t>());
    }
};
