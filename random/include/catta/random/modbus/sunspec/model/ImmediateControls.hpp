#pragma once

// catta
#include <catta/modbus/sunspec/model/ImmediateControls.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::ImmediateControls>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::ImmediateControls() const { return _value; }

  private:
    catta::modbus::sunspec::model::ImmediateControls _value;
    static catta::modbus::sunspec::model::ImmediateControls create(Random& random)
    {
        return catta::modbus::sunspec::model::ImmediateControls::create(random.create<catta::modbus::sunspec::ValueU16>(),
                                                                        random.create<catta::modbus::sunspec::ValueU16>(),
                                                                        random.create<catta::modbus::sunspec::ValueU16>());
    }
};
