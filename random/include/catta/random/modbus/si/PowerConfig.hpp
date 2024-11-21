#pragma once

// catta
#include <catta/modbus/si/PowerConfig.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::modbus::si::PowerConfig>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::PowerConfig() const { return _value; }

  private:
    catta::modbus::si::PowerConfig _value;
    static catta::modbus::si::PowerConfig create(Random& random)
    {
        return catta::modbus::si::PowerConfig::create(random.interval(std::uint16_t(0), std::uint16_t(3200)), random.create<bool>());
    }
};
