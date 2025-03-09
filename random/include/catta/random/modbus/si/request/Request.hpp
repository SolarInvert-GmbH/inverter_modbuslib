#pragma once

// catta
#include <catta/modbus/si/request/Request.hpp>

// random
#include <catta/random/Random.hpp>
#include <catta/random/modbus/si/ReadRegister.hpp>
#include <catta/random/modbus/si/WriteRegister.hpp>
#include <catta/random/modbus/si/request/ConstantVoltage.hpp>
#include <catta/random/modbus/si/request/ControlBatteryInvert.hpp>
#include <catta/random/modbus/si/request/LimitBatteryInvert.hpp>
#include <catta/random/modbus/si/request/PowerFactor.hpp>
#include <catta/random/modbus/si/request/Type.hpp>

template <>
class catta::random::Create<catta::modbus::si::request::Request>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::request::Request() const { return _value; }

  private:
    catta::modbus::si::request::Request _value;
    static catta::modbus::si::request::Request create(Random& random)
    {
        using Type = catta::modbus::si::request::Type;
        switch (random.create<Type>())
        {
            case Type::readRegister():
                return catta::modbus::si::request::Request::readRegister(random.create<catta::modbus::si::ReadRegister>());
            case Type::writeRegister():
                return catta::modbus::si::request::Request::writeRegister(random.create<catta::modbus::si::WriteRegister>());
            case Type::factoryValues():
                return catta::modbus::si::request::Request::factoryValues();
            case Type::readOperatingData33():
                return catta::modbus::si::request::Request::readOperatingData33();
            case Type::readOperatingData3e():
                return catta::modbus::si::request::Request::readOperatingData3e();
            case Type::switchOffGridRelay():
                return catta::modbus::si::request::Request::switchOffGridRelay();
            case Type::switchOnGridRelay():
                return catta::modbus::si::request::Request::switchOnGridRelay();
            case Type::forceIdle():
                return catta::modbus::si::request::Request::forceIdle();
            case Type::deactivateIdle():
                return catta::modbus::si::request::Request::deactivateIdle();
            case Type::startConstantVoltage():
                return catta::modbus::si::request::Request::startConstantVoltage(random.create<catta::modbus::si::request::ConstantVoltage>());
            case Type::endConstantVoltage():
                return catta::modbus::si::request::Request::endConstantVoltage();
            case Type::setPowerFactor():
                return catta::modbus::si::request::Request::setPowerFactor(random.create<catta::modbus::si::request::PowerFactor>());
            case Type::controlBatteryInvert():
                return catta::modbus::si::request::Request::controlBatteryInvert(random.create<catta::modbus::si::request::ControlBatteryInvert>());
            case Type::limitBatteryInvert():
                return catta::modbus::si::request::Request::limitBatteryInvert(random.create<catta::modbus::si::request::LimitBatteryInvert>());
            case Type::readError():
                return catta::modbus::si::request::Request::readError();
            default:
                return catta::modbus::si::request::Request::empty();
        }
    }
};
