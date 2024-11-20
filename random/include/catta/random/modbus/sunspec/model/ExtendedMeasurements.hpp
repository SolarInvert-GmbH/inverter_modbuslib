#pragma once

// catta
#include <catta/modbus/sunspec/model/ExtendedMeasurements.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU64.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::ExtendedMeasurements>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::ExtendedMeasurements() const { return _value; }

  private:
    catta::modbus::sunspec::model::ExtendedMeasurements _value;
    static catta::modbus::sunspec::model::ExtendedMeasurements create(Random& random)
    {
        return catta::modbus::sunspec::model::ExtendedMeasurements::create(random.create<catta::modbus::sunspec::ValueU64>());
    }
};
