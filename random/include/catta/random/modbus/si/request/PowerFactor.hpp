#pragma once

// catta
#include <catta/modbus/si/request/PowerFactor.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::PowerFactor>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::PowerFactor() const { return _value; }

  private:
    catta::modbus::si::request::PowerFactor _value;
    static catta::modbus::si::request::PowerFactor create(Random& random)
    {
        return catta::modbus::si::request::PowerFactor::create(random.create<catta::modbus::sunspec::ValueU8<0, 255>>());
    }
};
