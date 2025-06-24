#pragma once

// catta
#include <catta/modbus/si/response/Response.hpp>

// random
#include <catta/random/Random.hpp>
#include <catta/random/modbus/si/RegisterAddress.hpp>
#include <catta/random/modbus/si/request/Type.hpp>
#include <catta/random/modbus/si/response/Exception.hpp>
#include <catta/random/modbus/si/response/FactoryValues.hpp>
#include <catta/random/modbus/si/response/ReadError.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/random/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/random/modbus/si/response/Type.hpp>
#include <catta/random/modbus/sunspec/String16.hpp>
#include <catta/random/modbus/sunspec/String32.hpp>

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
            case Type::switchOffGridRelay():
                return catta::modbus::si::response::Response::switchOffGridRelay(random.create<bool>());
            case Type::switchOnGridRelay():
                return catta::modbus::si::response::Response::switchOnGridRelay(random.create<bool>());
            case Type::forceIdle():
                return catta::modbus::si::response::Response::forceIdle(random.create<bool>());
            case Type::deactivateIdle():
                return catta::modbus::si::response::Response::deactivateIdle(random.create<bool>());
            case Type::startConstantVoltage():
                return catta::modbus::si::response::Response::startConstantVoltage(random.create<bool>());
            case Type::endConstantVoltage():
                return catta::modbus::si::response::Response::endConstantVoltage(random.create<bool>());
            case Type::setPowerFactor():
                return catta::modbus::si::response::Response::setPowerFactor(random.create<bool>());
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::Response::controlBatteryInvert(random.create<bool>());
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::Response::limitBatteryInvert(random.create<bool>());
            case Type::writeRegister():
                return catta::modbus::si::response::Response::writeRegister(random.create<catta::modbus::si::RegisterAddress>());
            case Type::value16():
                return catta::modbus::si::response::Response::value16(random.create<std::uint16_t>());
            case Type::value32():
                return catta::modbus::si::response::Response::value32(random.create<std::uint32_t>());
            case Type::value64():
                return catta::modbus::si::response::Response::value64(random.interval(std::uint64_t(0), std::uint64_t(1) << 50));
            case Type::string16():
                return catta::modbus::si::response::Response::string16(random.create<catta::modbus::sunspec::String16>());
            case Type::string32():
                return catta::modbus::si::response::Response::string32(random.create<catta::modbus::sunspec::String32>());
            default:
                return catta::modbus::si::response::Response::empty();
        }
    }
};
