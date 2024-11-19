#pragma once

// catta
#include <catta/modbus/sunspec/ScaledValueS16.hpp>

// random
#include <catta/random/modbus/sunspec/ScaleFactor.hpp>
#include <catta/random/modbus/sunspec/ValueS16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ScaledValueS16>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ScaledValueS16() const { return _value; }

  private:
    catta::modbus::sunspec::ScaledValueS16 _value;
    static catta::modbus::sunspec::ScaledValueS16 create(Random& random)
    {
        return catta::modbus::sunspec::ScaledValueS16::create(random.create<catta::modbus::sunspec::ValueS16>(),
                                                              random.create<catta::modbus::sunspec::ScaleFactor>());
    }
};
