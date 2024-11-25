#pragma once

// catta
#include <catta/modbus/sunspec/model/Inverter.hpp>

// random
#include <catta/random/modbus/sunspec/ScaledValue3U16.hpp>
#include <catta/random/modbus/sunspec/ScaledValue4U16.hpp>
#include <catta/random/modbus/sunspec/ScaledValueS16.hpp>
#include <catta/random/modbus/sunspec/ScaledValueU16.hpp>
#include <catta/random/modbus/sunspec/ScaledValueU32.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::Inverter>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::Inverter() const { return _value; }

  private:
    catta::modbus::sunspec::model::Inverter _value;
    static catta::modbus::sunspec::model::Inverter create(Random& random)
    {
        return catta::modbus::sunspec::model::Inverter::create(
            random.create<catta::modbus::sunspec::ScaledValue4U16>(), random.create<catta::modbus::sunspec::ScaledValue3U16>(),
            random.create<catta::modbus::sunspec::ScaledValueS16>(), random.create<catta::modbus::sunspec::ScaledValueU16>(),
            random.create<catta::modbus::sunspec::ScaledValueS16>(), random.create<catta::modbus::sunspec::ScaledValueU32>(),
            random.create<catta::modbus::sunspec::ScaledValueU16>(), random.create<catta::modbus::sunspec::ScaledValueS16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU32>());
    }
};
