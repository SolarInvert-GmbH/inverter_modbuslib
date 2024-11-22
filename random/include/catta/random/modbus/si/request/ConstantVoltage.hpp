#pragma once

// catta
#include <catta/modbus/si/request/ConstantVoltage.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::ConstantVoltage>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::ConstantVoltage() const { return _value; }

  private:
    catta::modbus::si::request::ConstantVoltage _value;
    static catta::modbus::si::request::ConstantVoltage create(Random& random)
    {
        return catta::modbus::si::request::ConstantVoltage::create(random.create<catta::modbus::sunspec::ValueU16>());
    }
};
