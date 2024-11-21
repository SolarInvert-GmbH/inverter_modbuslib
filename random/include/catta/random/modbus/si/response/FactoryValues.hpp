#pragma once

// catta
#include <catta/modbus/si/response/FactoryValues.hpp>

// random
#include <catta/random/modbus/si/Date.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::FactoryValues>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::FactoryValues() const { return _value; }

  private:
    catta::modbus::si::response::FactoryValues _value;
    static catta::modbus::si::response::FactoryValues create(Random& random)
    {
        return catta::modbus::si::response::FactoryValues::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::si::Date>(),
            random.create<catta::modbus::sunspec::ValueU8<0, 255>>(), random.create<catta::modbus::sunspec::ValueU8<0, 255>>(),
            random.create<catta::modbus::sunspec::ValueU8<0, 255>>());
    }
};
