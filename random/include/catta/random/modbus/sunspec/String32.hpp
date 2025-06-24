#pragma once

// catta
#include <catta/modbus/sunspec/String32.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::String32>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::String32() const { return _value; }

  private:
    catta::modbus::sunspec::String32 _value;
    static catta::modbus::sunspec::String32 create(Random& random)
    {
        const auto s = random.interval(std::size_t(1), catta::modbus::sunspec::String32::size - 1);
        catta::modbus::sunspec::String32::Raw raw = {};
        for (std::size_t i = 0; i < s; i++) raw[i] = random.ascii();
        return catta::modbus::sunspec::String32::create(raw.data());
    }
};
