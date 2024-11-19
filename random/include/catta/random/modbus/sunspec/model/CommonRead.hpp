#pragma once

// catta
#include <catta/modbus/sunspec/model/CommonRead.hpp>

// random
#include <catta/random/modbus/sunspec/String.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::CommonRead>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::CommonRead() const { return _value; }

  private:
    catta::modbus::sunspec::model::CommonRead _value;
    static catta::modbus::sunspec::model::CommonRead create(Random& random)
    {
        return catta::modbus::sunspec::model::CommonRead::create(
            random.create<catta::modbus::sunspec::String>(), random.create<catta::modbus::sunspec::String>(),
            random.create<catta::modbus::sunspec::String>(), random.create<catta::modbus::sunspec::ValueU16>());
    }
};
