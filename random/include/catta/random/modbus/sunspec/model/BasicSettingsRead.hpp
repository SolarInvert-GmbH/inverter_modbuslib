#pragma once

// catta
#include <catta/modbus/sunspec/model/BasicSettingsRead.hpp>

// random
#include <catta/random/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/random/modbus/sunspec/ScaledValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::BasicSettingsRead>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::BasicSettingsRead() const { return _value; }

  private:
    catta::modbus::sunspec::model::BasicSettingsRead _value;
    static catta::modbus::sunspec::model::BasicSettingsRead create(Random& random)
    {
        return catta::modbus::sunspec::model::BasicSettingsRead::create(
            random.create<catta::modbus::sunspec::ScaledValueU16>(), random.create<catta::modbus::sunspec::ScaledValueU16>(),
            random.create<catta::modbus::sunspec::ScaledValueU16>(), random.create<catta::modbus::sunspec::ScaledValueU16>(),
            random.create<catta::modbus::sunspec::ConnectedPhase>());
    }
};
