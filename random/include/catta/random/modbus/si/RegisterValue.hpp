#pragma once

// catta
#include <catta/modbus/si/RegisterValue.hpp>

// random
#include <catta/random/modbus/si/RegisterAddress.hpp>
#include <catta/random/modbus/sunspec/String.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>
#include <catta/random/modbus/sunspec/ValueU32.hpp>
#include <catta/random/modbus/sunspec/ValueU64.hpp>

template <>
class catta::random::Create<catta::modbus::si::RegisterValue>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::RegisterValue() const { return _value; }

  private:
    catta::modbus::si::RegisterValue _value;
    static catta::modbus::si::RegisterValue create(Random& random)
    {
        using Type = catta::modbus::si::RegisterType;
        const catta::modbus::si::RegisterAddress registerAddress = random.create<catta::modbus::si::RegisterAddress>();
        switch (registerAddress.type())
        {
            default:
                return catta::modbus::si::RegisterValue::value16(registerAddress, random.create<catta::modbus::sunspec::ValueU16>());
            case Type::uint32():
                return catta::modbus::si::RegisterValue::value32(registerAddress, random.create<catta::modbus::sunspec::ValueU32>());
            case Type::uint64():
                return catta::modbus::si::RegisterValue::value64(registerAddress, random.create<catta::modbus::sunspec::ValueU64>());
            case Type::string32():
                return catta::modbus::si::RegisterValue::string(registerAddress, random.create<catta::modbus::sunspec::String>());
        }
    }
};
