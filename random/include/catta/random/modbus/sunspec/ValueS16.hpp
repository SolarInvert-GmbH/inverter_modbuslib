#pragma once

// catta
#include <catta/modbus/sunspec/ValueS16.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ValueS16>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueS16() const { return _value; }

  private:
    catta::modbus::sunspec::ValueS16 _value;
    static catta::modbus::sunspec::ValueS16 create(Random& random) { return catta::modbus::sunspec::ValueS16::create(random.create<std::int16_t>()); }
};
