#pragma once

// catta
#include <catta/modbus/si/request/ControlBatteryInvert.hpp>

// random
#include <catta/random/modbus/si/PowerConfig.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::ControlBatteryInvert>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::ControlBatteryInvert() const { return _value; }

  private:
    catta::modbus::si::request::ControlBatteryInvert _value;
    static catta::modbus::si::request::ControlBatteryInvert create(Random& random)
    {
        return catta::modbus::si::request::ControlBatteryInvert::create(
            random.create<catta::modbus::si::PowerConfig>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>());
    }
};
