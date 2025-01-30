#pragma once

// catta
#include <catta/modbus/si/response/Exception.hpp>

// random
#include <catta/random/modbus/si/request/Type.hpp>
#include <catta/random/modbus/si/response/ExceptionValue.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::Exception>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::Exception() const { return _value; }

  private:
    catta::modbus::si::response::Exception _value;
    static catta::modbus::si::response::Exception create(Random& random)
    {
        return catta::modbus::si::response::Exception::create(random.create<catta::modbus::si::response::ExceptionValue>(),
                                                              random.create<catta::modbus::si::request::Type>());
    }
};
