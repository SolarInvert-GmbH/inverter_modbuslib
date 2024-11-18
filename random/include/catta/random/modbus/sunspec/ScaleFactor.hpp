#pragma once

// catta
#include <catta/modbus/sunspec/ScaleFactor.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ScaleFactor>
{
  public:
    Create(Random& random) : _value(catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+10)))) {}
    operator catta::modbus::sunspec::ScaleFactor() const { return _value; }

  private:
    catta::modbus::sunspec::ScaleFactor _value;
};
