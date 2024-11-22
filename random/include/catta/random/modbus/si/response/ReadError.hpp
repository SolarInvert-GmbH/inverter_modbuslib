#pragma once

// catta
#include <catta/modbus/si/response/ReadError.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::ReadError>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::ReadError() const { return _value; }

  private:
    catta::modbus::si::response::ReadError _value;
    static catta::modbus::si::response::ReadError create(Random& random)
    {
        return catta::modbus::si::response::ReadError::create(
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>(),
            random.create<catta::modbus::sunspec::ValueU16>(), random.create<catta::modbus::sunspec::ValueU16>());
    }
};
