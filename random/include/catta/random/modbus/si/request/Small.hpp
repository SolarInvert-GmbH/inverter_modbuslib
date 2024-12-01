#pragma once

// catta
#include <catta/modbus/si/request/Small.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::Small>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::Small() const { return _value; }

  private:
    catta::modbus::si::request::Small _value;
    static catta::modbus::si::request::Small create(Random& random)
    {
        return catta::modbus::si::request::Small::create(random.interval(std::uint8_t(1), std::uint8_t(255)));
    }
};
