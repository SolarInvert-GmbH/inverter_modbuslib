#pragma once

// catta
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>

// random
#include <catta/random/modbus/si/Type.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>
#include <catta/random/modbus/sunspec/ValueU32.hpp>
#include <catta/random/modbus/sunspec/ValueU8.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::ReadOperatingData3e>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::ReadOperatingData3e() const { return _value; }

  private:
    catta::modbus::si::response::ReadOperatingData3e _value;
    static catta::modbus::si::response::ReadOperatingData3e create(Random& random)
    {
        return catta::modbus::si::response::ReadOperatingData3e::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::si::Type>(),
            random.create<catta::modbus::sunspec::ValueU8<1, 10>>(), random.create<catta::modbus::sunspec::ValueU8<1, 32>>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU32>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU32>(),
            random.create<catta::modbus::sunspec::ValueU8<0, 3>>(), random.create<catta::modbus::sunspec::ValueU8<0, 15>>());
    }
};
