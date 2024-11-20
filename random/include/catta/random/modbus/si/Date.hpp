#pragma once

// catta
#include <catta/modbus/si/Date.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::Date>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::Date() const { return _value; }

  private:
    catta::modbus::si::Date _value;
    static catta::modbus::si::Date create(Random& random)
    {
        return catta::modbus::si::Date::create(random.create<catta::modbus::sunspec::ValueU8<1, 31>>(),
                                               random.create<catta::modbus::sunspec::ValueU8<1, 12>>(),
                                               random.create<catta::modbus::sunspec::ValueU8<0, 99>>());
    }
};
