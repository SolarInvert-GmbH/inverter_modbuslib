#pragma once

// catta
#include <catta/modbus/si/ReadRegister.hpp>

// random
#include <catta/random/modbus/si/RegisterAddress.hpp>

template <>
class catta::random::Create<catta::modbus::si::ReadRegister>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::ReadRegister() const { return _value; }

  private:
    catta::modbus::si::ReadRegister _value;
    static catta::modbus::si::ReadRegister create(Random& random)
    {
        return catta::modbus::si::ReadRegister::create(random.create<catta::modbus::si::RegisterAddress>());
    }
};
