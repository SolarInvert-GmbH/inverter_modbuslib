#pragma once

// catta
#include <catta/modbus/si/response/Response.hpp>

// random
#include <catta/random/Random.hpp>
#include <catta/random/modbus/si/WriteRegister.hpp>
#include <catta/random/modbus/si/response/Exception.hpp>
#include <catta/random/modbus/si/response/FactoryValues.hpp>
#include <catta/random/modbus/si/response/ReadError.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/random/modbus/si/response/Type.hpp>
#include <catta/random/modbus/sunspec/String.hpp>

template <>
class catta::random::Create<catta::modbus::si::response::Response>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::response::Response() const { return _value; }

  private:
    catta::modbus::si::response::Response _value;
    static catta::modbus::si::response::Response create(Random& random)
    {
        using Type = catta::modbus::si::response::Type;
        switch (random.create<Type>())
        {
            case Type::exception():
                return catta::modbus::si::response::Response::exception(random.create<catta::modbus::si::response::Exception>());
            case Type::factoryValues():
                return catta::modbus::si::response::Response::factoryValues(random.create<catta::modbus::si::response::FactoryValues>());
            case Type::readError():
                return catta::modbus::si::response::Response::readError(random.create<catta::modbus::si::response::ReadError>());
            case Type::readOperatingData33():
                return catta::modbus::si::response::Response::readOperatingData33(random.create<catta::modbus::si::response::ReadOperatingData33>());
            case Type::readOperatingData3e():
                return catta::modbus::si::response::Response::readOperatingData3e(random.create<catta::modbus::si::response::ReadOperatingData3e>());
            case Type::switchOffInverter():
                return catta::modbus::si::response::Response::switchOffInverter();
            case Type::switchOnInverter():
                return catta::modbus::si::response::Response::switchOnInverter();
            case Type::forceIdle():
                return catta::modbus::si::response::Response::forceIdle();
            case Type::deactivateIdle():
                return catta::modbus::si::response::Response::deactivateIdle();
            case Type::startConstantVoltage():
                return catta::modbus::si::response::Response::startConstantVoltage();
            case Type::endConstantVoltage():
                return catta::modbus::si::response::Response::endConstantVoltage();
            case Type::setPowerFactor():
                return catta::modbus::si::response::Response::setPowerFactor();
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::Response::controlBatteryInvert();
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::Response::limitBatteryInvert();
            case Type::writeRegister():
                return catta::modbus::si::response::Response::writeRegister(random.create<catta::modbus::si::WriteRegister>());
            case Type::value16():
                return catta::modbus::si::response::Response::value16(random.create<std::uint16_t>());
            case Type::value32():
                return catta::modbus::si::response::Response::value32(random.create<std::uint32_t>());
            case Type::value64():
                return catta::modbus::si::response::Response::value64(random.interval(std::uint64_t(0), std::uint64_t(1) << 50));
            case Type::string():
                return catta::modbus::si::response::Response::string(random.create<catta::modbus::sunspec::String>());
            default:
                return catta::modbus::si::response::Response::empty();
        }
    }
};
