#pragma once

// catta
#include <catta/modbus/si/response/NiceResponse.hpp>

// random
#include <catta/random/Random.hpp>
#include <catta/random/modbus/si/RegisterAddress.hpp>
#include <catta/random/modbus/si/RegisterValue.hpp>
#include <catta/random/modbus/si/request/Type.hpp>
#include <catta/random/modbus/si/response/Exception.hpp>
#include <catta/random/modbus/si/response/FactoryValues.hpp>
#include <catta/random/modbus/si/response/NiceType.hpp>
#include <catta/random/modbus/si/response/ReadError.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData3e.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::NiceResponse>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::NiceResponse() const { return _value; }

  private:
    catta::modbus::si::response::NiceResponse _value;
    static catta::modbus::si::response::NiceResponse create(Random& random)
    {
        using Type = catta::modbus::si::response::NiceType;
        switch (random.create<Type>())
        {
            case Type::exception():
                return catta::modbus::si::response::NiceResponse::exception(random.create<catta::modbus::si::response::Exception>());
            case Type::factoryValues():
                return catta::modbus::si::response::NiceResponse::factoryValues(random.create<catta::modbus::si::response::FactoryValues>());
            case Type::readError():
                return catta::modbus::si::response::NiceResponse::readError(random.create<catta::modbus::si::response::ReadError>());
            case Type::readOperatingData33():
                return catta::modbus::si::response::NiceResponse::readOperatingData33(
                    random.create<catta::modbus::si::response::ReadOperatingData33>());
            case Type::readOperatingData3e():
                return catta::modbus::si::response::NiceResponse::readOperatingData3e(
                    random.create<catta::modbus::si::response::ReadOperatingData3e>());
            case Type::switchOffGridRelay():
                return catta::modbus::si::response::NiceResponse::switchOffGridRelay(random.create<bool>());
            case Type::switchOnGridRelay():
                return catta::modbus::si::response::NiceResponse::switchOnGridRelay(random.create<bool>());
            case Type::forceIdle():
                return catta::modbus::si::response::NiceResponse::forceIdle(random.create<bool>());
            case Type::deactivateIdle():
                return catta::modbus::si::response::NiceResponse::deactivateIdle(random.create<bool>());
            case Type::startConstantVoltage():
                return catta::modbus::si::response::NiceResponse::startConstantVoltage(random.create<bool>());
            case Type::endConstantVoltage():
                return catta::modbus::si::response::NiceResponse::endConstantVoltage(random.create<bool>());
            case Type::setPowerFactor():
                return catta::modbus::si::response::NiceResponse::setPowerFactor(random.create<bool>());
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::NiceResponse::controlBatteryInvert(random.create<bool>());
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::NiceResponse::limitBatteryInvert(random.create<bool>());
            case Type::writeRegister():
                return catta::modbus::si::response::NiceResponse::writeRegister(random.create<catta::modbus::si::RegisterAddress>());
            case Type::readRegister():
                return catta::modbus::si::response::NiceResponse::readRegister(random.create<catta::modbus::si::RegisterValue>());
            default:
                return catta::modbus::si::response::NiceResponse::empty();
        }
    }
};
