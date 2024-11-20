#pragma once

// catta
#include <catta/modbus/sunspec/model/Nameplate.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::Nameplate>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::Nameplate() const { return _value; }

  private:
    catta::modbus::sunspec::model::Nameplate _value;
    static catta::modbus::sunspec::model::Nameplate create(Random& random)
    {
        return catta::modbus::sunspec::model::Nameplate::create(random.create<catta::modbus::sunspec::ValueU16>());
    }
};
