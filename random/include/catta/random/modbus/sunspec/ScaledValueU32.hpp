#pragma once

// catta
#include <catta/modbus/sunspec/ScaledValueU32.hpp>

// random
#include <catta/random/modbus/sunspec/ScaleFactor.hpp>
#include <catta/random/modbus/sunspec/ValueU32.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::ScaledValueU32>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::ScaledValueU32() const { return _value; }

  private:
    catta::modbus::sunspec::ScaledValueU32 _value;
    static catta::modbus::sunspec::ScaledValueU32 create(Random& random)
    {
        return catta::modbus::sunspec::ScaledValueU32::create(random.create<catta::modbus::sunspec::ValueU32>(),
                                                              random.create<catta::modbus::sunspec::ScaleFactor>());
    }
};
