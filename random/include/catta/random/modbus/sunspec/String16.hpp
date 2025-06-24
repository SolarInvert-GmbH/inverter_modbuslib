#pragma once

// catta
#include <catta/modbus/sunspec/String16.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::String16>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::String16() const { return _value; }

  private:
    catta::modbus::sunspec::String16 _value;
    static catta::modbus::sunspec::String16 create(Random& random)
    {
        const auto s = random.interval(std::size_t(1), catta::modbus::sunspec::String16::size - 1);
        catta::modbus::sunspec::String16::Raw raw = {};
        for (std::size_t i = 0; i < s; i++) raw[i] = random.ascii();
        return catta::modbus::sunspec::String16::create(raw.data());
    }
};
