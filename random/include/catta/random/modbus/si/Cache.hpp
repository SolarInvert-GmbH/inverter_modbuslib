#pragma once

// catta
#include <catta/modbus/si/Cache.hpp>

// random
#include <catta/random/modbus/si/Type.hpp>
#include <catta/random/modbus/sunspec/ScaleFactor.hpp>

template <>
class catta::random::Create<catta::modbus::si::Cache>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::Cache() const { return _value; }

  private:
    catta::modbus::si::Cache _value;
    static catta::modbus::si::Cache create(Random& random)
    {
        return catta::modbus::si::Cache::create(
            catta::modbus::si::Type(random.interval(std::uint8_t(0), std::uint8_t(catta::modbus::si::Type::empty()))),

            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),

            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))),
            catta::modbus::sunspec::ScaleFactor::create(random.interval(std::int8_t(-10), std::int8_t(+11))));
    }
};
