#pragma once

// catta
#include <catta/modbus/sunspec/model/Storage.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::Storage>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::Storage() const { return _value; }

  private:
    catta::modbus::sunspec::model::Storage _value;
    static catta::modbus::sunspec::model::Storage create(Random& random)
    {
        return catta::modbus::sunspec::model::Storage::create(random.create<catta::modbus::sunspec::ValueU16>(),
                                                              random.create<catta::modbus::sunspec::ValueU16>());
    }
};
