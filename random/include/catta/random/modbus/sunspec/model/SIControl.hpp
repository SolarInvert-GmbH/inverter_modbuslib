#pragma once

// catta
#include <catta/modbus/sunspec/model/SIControl.hpp>

// random
#include <catta/random/modbus/sunspec/ValueS16.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::SIControl>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::SIControl() const { return _value; }

  private:
    catta::modbus::sunspec::model::SIControl _value;
    static catta::modbus::sunspec::model::SIControl create(Random& random)
    {
        return catta::modbus::sunspec::model::SIControl::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueS16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>());
    }
};
