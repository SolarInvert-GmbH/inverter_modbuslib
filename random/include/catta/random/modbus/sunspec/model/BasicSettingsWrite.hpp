#pragma once

// catta
#include <catta/modbus/sunspec/model/BasicSettingsWrite.hpp>

// random
#include <catta/random/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::BasicSettingsWrite>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::BasicSettingsWrite() const { return _value; }

  private:
    catta::modbus::sunspec::model::BasicSettingsWrite _value;
    static catta::modbus::sunspec::model::BasicSettingsWrite create(Random& random)
    {
        return catta::modbus::sunspec::model::BasicSettingsWrite::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ConnectedPhase>());
    }
};
