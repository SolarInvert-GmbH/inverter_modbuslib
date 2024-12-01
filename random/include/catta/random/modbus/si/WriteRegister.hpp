#pragma once

// catta
#include <catta/modbus/si/WriteRegister.hpp>

// random
#include <catta/random/modbus/si/RegisterAddress.hpp>
#include <catta/random/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/random/modbus/sunspec/ValueS16.hpp>
#include <catta/random/modbus/sunspec/ValueU16.hpp>

template <>
class catta::random::Create<catta::modbus::si::WriteRegister>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::WriteRegister() const { return _value; }

  private:
    catta::modbus::si::WriteRegister _value;
    static catta::modbus::si::WriteRegister create(Random& random)
    {
        using A = catta::modbus::si::RegisterAddress;
        using T = catta::modbus::si::RegisterType;
        static constexpr std::array<A, 16> a = {A::commonDeviceAddress(),
                                                A::basicSettingsWMax(),
                                                A::basicSettingsVMax(),
                                                A::basicSettingsVMin(),
                                                A::basicSettingsEcpNomHz(),
                                                A::basicSettingsConnPhase(),
                                                A::immediateConnectionTimeout(),
                                                A::immediateConnectionControl(),
                                                A::immediatePowerLimit(),
                                                A::storageWChaMax(),
                                                A::storageWChaRate(),
                                                A::siControlPcdDiv(),
                                                A::siControlUdcExt(),
                                                A::siControlPSetPoint(),
                                                A::siControlUMinExt(),
                                                A::siControlUMaxExt()};
        const auto address = a[random.interval(std::size_t(0), a.size() - 1)];
        switch (address.type())
        {
            case T::uint16():
                return catta::modbus::si::WriteRegister::create(address, random.create<catta::modbus::sunspec::ValueU16>());
            case T::sint16():
                return catta::modbus::si::WriteRegister::create(address, random.create<catta::modbus::sunspec::ValueS16>());
            case T::connectedPhase():
                return catta::modbus::si::WriteRegister::create(address, random.create<catta::modbus::sunspec::ConnectedPhase>());
            default:
                return catta::modbus::si::WriteRegister::empty();
        }
    }
};
