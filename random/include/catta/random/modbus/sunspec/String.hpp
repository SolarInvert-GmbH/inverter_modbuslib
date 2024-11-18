#pragma once

// catta
#include <catta/modbus/sunspec/String.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::String>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::String() const { return _value; }

  private:
    catta::modbus::sunspec::String _value;
    static catta::modbus::sunspec::String create(Random& random)
    {
        const auto s = random.interval(std::size_t(1), catta::modbus::sunspec::String::size - 1);
        catta::modbus::sunspec::String::Raw raw = {};
        for (std::size_t i = 0; i < s; i++) raw[i] = random.ascii();
        return catta::modbus::sunspec::String::create(raw.data());
    }
};
