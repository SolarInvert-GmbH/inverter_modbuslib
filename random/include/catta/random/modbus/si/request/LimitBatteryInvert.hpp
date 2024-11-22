#pragma once

// catta
#include <catta/modbus/si/request/LimitBatteryInvert.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::LimitBatteryInvert>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::LimitBatteryInvert() const { return _value; }

  private:
    catta::modbus::si::request::LimitBatteryInvert _value;
    static catta::modbus::si::request::LimitBatteryInvert create(Random& random)
    {
        return catta::modbus::si::request::LimitBatteryInvert::create(random.create<catta::modbus::sunspec::ValueU8<0, 100>>());
    }
};
