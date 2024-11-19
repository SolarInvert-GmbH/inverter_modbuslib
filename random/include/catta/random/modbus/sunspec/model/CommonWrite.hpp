#pragma once

// catta
#include <catta/modbus/sunspec/model/CommonWrite.hpp>

// random
#include <catta/random/modbus/sunspec/String.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::sunspec::model::CommonWrite>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::sunspec::model::CommonWrite() const { return _value; }

  private:
    catta::modbus::sunspec::model::CommonWrite _value;
    static catta::modbus::sunspec::model::CommonWrite create(Random& random)
    {
        return catta::modbus::sunspec::model::CommonWrite::create(random.create<catta::modbus::sunspec::ValueU16>());
    }
};
