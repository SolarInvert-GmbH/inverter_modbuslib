#pragma once

// catta
#include <catta/modbus/sunspec/ValueS32.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ValueS32>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueS32() const { return _value; }

  private:
    catta::modbus::sunspec::ValueS32 _value;
    static catta::modbus::sunspec::ValueS32 create(Random& random) { return catta::modbus::sunspec::ValueS32::create(random.create<std::int32_t>()); }
};
