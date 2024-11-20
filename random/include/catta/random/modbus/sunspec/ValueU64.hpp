#pragma once

// catta
#include <catta/modbus/sunspec/ValueU64.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ValueU64>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ValueU64() const { return _value; }

  private:
    catta::modbus::sunspec::ValueU64 _value;
    static catta::modbus::sunspec::ValueU64 create(Random& random)
    {
        return catta::modbus::sunspec::ValueU64::create(random.interval(std::uint64_t(0ll), std::uint64_t(9223372036854775807ll)));
    }
};
