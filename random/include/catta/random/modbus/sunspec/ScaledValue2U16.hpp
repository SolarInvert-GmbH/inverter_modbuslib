#pragma once

// catta
#include <catta/modbus/sunspec/ScaledValue2U16.hpp>

// random
#include <catta/random/modbus/sunspec/ScaleFactor.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ScaledValue2U16>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ScaledValue2U16() const { return _value; }

  private:
    catta::modbus::sunspec::ScaledValue2U16 _value;
    static catta::modbus::sunspec::ScaledValue2U16 create(Random& random)
    {
        return catta::modbus::sunspec::ScaledValue2U16::create(random.create<catta::modbus::sunspec::ValueU16>(),
                                                               random.create<catta::modbus::sunspec::ValueU16>(),
                                                               random.create<catta::modbus::sunspec::ScaleFactor>());
    }
};
