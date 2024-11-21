#pragma once

// catta
#include <catta/modbus/si/response/ReadOperatingData33.hpp>

// random
#include <catta/random/modbus/si/State.hpp>
#include <catta/random/modbus/sunspec/ValueS16.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::ReadOperatingData33>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::ReadOperatingData33() const { return _value; }

  private:
    catta::modbus::si::response::ReadOperatingData33 _value;
    static catta::modbus::si::response::ReadOperatingData33 create(Random& random)
    {
        return catta::modbus::si::response::ReadOperatingData33::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU8<0, 255>>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueS16>(),
            random.create<catta::modbus::si::State>());
    }
};
