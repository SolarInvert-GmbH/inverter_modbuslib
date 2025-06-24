#pragma once

// std
#include <array>

// sunspec
#include <catta/modbus/sunspec/String16.hpp>
#include <catta/modbus/sunspec/String32.hpp>

// si
#include <catta/modbus/si/RegisterAddress.hpp>

// response
#include <catta/modbus/si/response/Exception.hpp>
#include <catta/modbus/si/response/FactoryValues.hpp>
#include <catta/modbus/si/response/ReadError.hpp>
#include <catta/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/modbus/si/response/Type.hpp>

// request
#include <catta/modbus/si/request/Type.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Class for representing a response.
 *
 * @author CattaTech - Maik Urbannek
 */
class Response
{
  public:
    /**
     * Default constructor. Creates invalid response.
     */
    constexpr Response() noexcept : Response(Raw{}, catta::modbus::si::response::Type::empty()) {}
    /**
     * @return Returns invalid response.
     */
    constexpr static Response empty() noexcept { return Response{}; }
    /**
     *  @return Returns @b true if response is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _type.isEmpty(); }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns switch off grid relay response.
     */
    static constexpr Response switchOffGridRelay(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::switchOffGridRelay());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns switch on grid relay response.
     */
    static constexpr Response switchOnGridRelay(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::switchOnGridRelay());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns force idle response.
     */
    static constexpr Response forceIdle(const bool success) { return Response(Raw{success}, catta::modbus::si::response::Type::forceIdle()); }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns deactivate idle response.
     */
    static constexpr Response deactivateIdle(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::deactivateIdle());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns start constant voltage response.
     */
    static constexpr Response startConstantVoltage(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::startConstantVoltage());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns end constant voltage response.
     */
    static constexpr Response endConstantVoltage(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::endConstantVoltage());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns set power factor response.
     */
    static constexpr Response setPowerFactor(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::setPowerFactor());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns control battery invert response.
     */
    static constexpr Response controlBatteryInvert(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::controlBatteryInvert());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns limit battery invert response.
     */
    static constexpr Response limitBatteryInvert(const bool success)
    {
        return Response(Raw{success}, catta::modbus::si::response::Type::limitBatteryInvert());
    }
    /**
     * @param[in] exception The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns exception response if input is valid, otherwise empty.
     */
    static constexpr Response exception(const catta::modbus::si::response::Exception exception)
    {
        return exception.isEmpty() ? Response::empty()
                                   : Response(Raw{exception.value(), exception.request()}, catta::modbus::si::response::Type::exception());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns factory values response.
     */
    static constexpr Response factoryValues(const catta::modbus::si::response::FactoryValues value)
    {
        return value.isEmpty() ? Response::empty()
                               : Response(Raw{value.serialnumber().value(), value.productionDate().day().value(),
                                              value.productionDate().month().value(), value.productionDate().year().value(),
                                              value.hardwareVersion().value(), value.firmwareVersion().value(), value.bootstrappVersion().value()},
                                          catta::modbus::si::response::Type::factoryValues());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data33 response if input is valid, otherwise empty.
     */
    static constexpr Response readError(const catta::modbus::si::response::ReadError& value)
    {
        return value.isEmpty() ? Response::empty()
                               : Response(Raw{value.overVoltageAC().value(),
                                              value.underVoltageAC().value(),
                                              value.overVoltageDC().value(),
                                              value.underVoltageDC().value(),
                                              value.overFrequency().value(),
                                              value.underFrequency().value(),
                                              value.limitedPowerT1().value(),
                                              value.limitedPowerT2().value(),
                                              value.limitedPowerT3().value(),
                                              value.limitedPowerT4().value(),
                                              value.limitedPowerT5().value(),
                                              value.com().value(),
                                              value.islandGrid().value(),
                                              value.overCurrentInterrupt().value(),
                                              value.overVoltageInterrupt().value(),
                                              value.averageGridOverVoltage().value(),
                                              value.overTempratureShutdown().value(),
                                              value.differenceGridVoltage().value(),
                                              value.errorGridRelais().value(),
                                              value.errorCurrentSensor().value()},
                                          catta::modbus::si::response::Type::readError());
    }
    /**
     * @param[in] value The read operating data 33. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data33 response if input is valid, otherwise empty.
     */
    static constexpr Response readOperatingData33(const catta::modbus::si::response::ReadOperatingData33& value)
    {
        return value.isEmpty() ? Response::empty()
                               : Response(Raw{value.dcVoltage().value(), value.acVoltage().value(), value.gridFrequency().value(),
                                              static_cast<std::uint16_t>(value.acPower().value()), value.state()},
                                          catta::modbus::si::response::Type::readOperatingData33());
    }
    /**
     * @param[in] value The read operating data 3e. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data3e response if input is valid, otherwise empty.
     */
    static constexpr Response readOperatingData3e(const catta::modbus::si::response::ReadOperatingData3e& value)
    {
        return value.isEmpty()
                   ? Response::empty()
                   : Response(Raw{value.serialNumber().value(), value.type(), value.voltageType().value(), value.nominalPower().value(),
                                  value.cosphi().value(), pack(value.gridSupplyDailySum().value(), 1), pack(value.gridSupplyDailySum().value(), 0),
                                  value.powerLimitation().value(), pack(value.operatingHours().value(), 1), pack(value.operatingHours().value(), 0),
                                  value.phase().value(), value.modbusId().value()},
                              catta::modbus::si::response::Type::readOperatingData3e());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns exception response if input is valid, otherwise empty.
     */
    static constexpr Response writeRegister(const catta::modbus::si::RegisterAddress value)
    {
        return value.isEmpty() ? Response::empty() : Response(Raw{value}, catta::modbus::si::response::Type::writeRegister());
    }
    /**
     * @param[in] value The value16.
     * @return Returns value16 response if input is valid, otherwise empty.
     */
    static constexpr Response value16(const std::uint16_t value) { return Response(Raw{value}, catta::modbus::si::response::Type::value16()); }
    /**
     * @param[in] value The value32.
     * @return Returns value32 response if input is valid, otherwise empty.
     */
    static constexpr Response value32(const std::uint32_t value)
    {
        return Response(Raw{pack(value, 1), pack(value, 0)}, catta::modbus::si::response::Type::value32());
    }
    /**
     * @param[in] value The value64.
     * @return Returns valueU64 response if input is valid, otherwise empty.
     */
    static constexpr Response value64(const std::uint64_t value)
    {
        return Response(Raw{pack(value, 3), pack(value, 2), pack(value, 1), pack(value, 0)}, catta::modbus::si::response::Type::value64());
    }
    /**
     * @param[in] value The string16. Has to be not empty, otherwise empty is returned.
     * @return Returns string response if input is valid, otherwise empty.
     */
    static constexpr Response string16(const catta::modbus::sunspec::String16& value)
    {
        const auto pack = [&value]()
        {
            Raw r = {};
            for (std::size_t i = 0; i < catta::modbus::sunspec::String16::size / 2; i++)
                r[i] = static_cast<std::uint16_t>((value.data()[(i * 2) + 0] << 8) | value.data()[(i * 2) + 1]);
            return r;
        };
        return value.isEmpty() ? Response::empty() : Response(pack(), catta::modbus::si::response::Type::string16());
    }
    /**
     * @param[in] value The string32. Has to be not empty, otherwise empty is returned.
     * @return Returns string response if input is valid, otherwise empty.
     */
    static constexpr Response string32(const catta::modbus::sunspec::String32& value)
    {
        const auto pack = [&value]()
        {
            Raw r = {};
            for (std::size_t i = 0; i < catta::modbus::sunspec::String32::size / 2; i++)
                r[i] = static_cast<std::uint16_t>((value.data()[(i * 2) + 0] << 8) | value.data()[(i * 2) + 1]);
            return r;
        };
        return value.isEmpty() ? Response::empty() : Response(pack(), catta::modbus::si::response::Type::string32());
    }
    /**
     * @return Returns write register value. Is only valid if type is write register.
     */
    constexpr catta::modbus::si::RegisterAddress writeRegisterValue() const noexcept
    {
        return catta::modbus::si::RegisterAddress(static_cast<std::uint8_t>(_data[0]));
    }
    /**
     * @return Returns exception value. Is only valid if type is exception.
     */
    constexpr catta::modbus::si::response::Exception exceptionValue() const noexcept
    {
        return catta::modbus::si::response::Exception::create(catta::modbus::si::response::ExceptionValue(static_cast<std::uint8_t>(_data[0])),
                                                              catta::modbus::si::request::Type(static_cast<std::uint8_t>(_data[1])));
    }
    /**
     * @return Returns factory values value. Is only valid if type is factory values.
     */
    constexpr catta::modbus::si::response::FactoryValues factoryValuesValue() const noexcept
    {
        const auto serialnumber = catta::modbus::sunspec::ValueU16::create(_data[0]);
        const auto day = catta::modbus::sunspec::ValueU8<1, 31>::create(static_cast<std::uint8_t>(_data[1]));
        const auto month = catta::modbus::sunspec::ValueU8<1, 12>::create(static_cast<std::uint8_t>(_data[2]));
        const auto year = catta::modbus::sunspec::ValueU8<0, 99>::create(static_cast<std::uint8_t>(_data[3]));
        const auto date = catta::modbus::si::Date::create(day, month, year);
        const auto hardwareVersion = catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[4]));
        const auto firmwareVersion = catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[5]));
        const auto bootstrappVersion = catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[6]));
        return catta::modbus::si::response::FactoryValues::create(serialnumber, date, hardwareVersion, firmwareVersion, bootstrappVersion);
    }
    /**
     * @return Returns read error value. Is only valid if type is read error.
     */
    constexpr catta::modbus::si::response::ReadError readErrorValue() const noexcept
    {
        const auto v = [this](const std::size_t i) { return catta::modbus::sunspec::ValueU16::create(_data[i]); };
        return catta::modbus::si::response::ReadError::create(v(0), v(1), v(2), v(3), v(4), v(5), v(6), v(7), v(8), v(9), v(10), v(11), v(12), v(13),
                                                              v(14), v(15), v(16), v(17), v(18), v(19));
    }
    /**
     * @return Returns read operating data 33 value. Is only valid if type is read operating data 33.
     */
    constexpr catta::modbus::si::response::ReadOperatingData33 readOperatingData33Value() const noexcept
    {
        const auto dcVoltage = catta::modbus::sunspec::ValueU16::create(_data[0]);
        const auto acVoltage = catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[1]));
        const auto gridFrequency = catta::modbus::sunspec::ValueU16::create(_data[2]);
        const auto acPower = catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(_data[3]));
        const auto state = catta::modbus::si::State(static_cast<std::uint8_t>(_data[4]));
        return catta::modbus::si::response::ReadOperatingData33::create(dcVoltage, acVoltage, gridFrequency, acPower, state);
    }
    /**
     * @return Returns read operating data 3e value. Is only valid if type is read operating data 3e.
     */
    constexpr catta::modbus::si::response::ReadOperatingData3e readOperatingData3eValue() const noexcept
    {
        const auto serialNumber = catta::modbus::sunspec::ValueU16::create(_data[0]);
        const auto type = catta::modbus::si::Type(static_cast<std::uint8_t>(_data[1]));
        const auto voltageType = catta::modbus::sunspec::ValueU8<1, 10>::create(static_cast<std::uint8_t>(_data[2]));
        const auto nominalPower = catta::modbus::sunspec::ValueU8<1, 32>::create(static_cast<std::uint8_t>(_data[3]));
        const auto cosphi = catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[4]));
        const auto gridSupplyDailySum = catta::modbus::sunspec::ValueU32::create(unpack(_data[5], _data[6]));
        const auto powerLimitation = catta::modbus::sunspec::ValueU16::create(_data[7]);
        const auto operatingHours = catta::modbus::sunspec::ValueU32::create(unpack(_data[8], _data[9]));
        const auto phase = catta::modbus::sunspec::ValueU8<0, 3>::create(static_cast<std::uint8_t>(_data[10]));
        const auto modbusId = catta::modbus::sunspec::ValueU8<0, 15>::create(static_cast<std::uint8_t>(_data[11]));
        return catta::modbus::si::response::ReadOperatingData3e::create(serialNumber, type, voltageType, nominalPower, cosphi, gridSupplyDailySum,
                                                                        powerLimitation, operatingHours, phase, modbusId);
    }
    /**
     * @return Returns whether the request was successfull. Is only valid if type is switchOffGridRelay, switchOnGridRelay, forceIdle, deactivateIdle,
     * startConstantVoltage, endConstantVoltage, setPowerFactor, controlBatteryInvert or limitBatteryInvert.
     */
    constexpr std::uint16_t successValue() const noexcept { return static_cast<bool>(_data[0]); }
    /**
     * @return Returns value16 value. Is only valid if type is value16.
     */
    constexpr std::uint16_t value16Value() const noexcept { return _data[0]; }
    /**
     * @return Returns value32 value. Is only valid if type is value32.
     */
    constexpr std::uint32_t value32Value() const noexcept { return unpack(_data[0], _data[1]); }
    /**
     * @return Returns value64 value. Is only valid if type is value64.
     */
    constexpr std::uint64_t value64Value() const noexcept { return unpack(_data[0], _data[1], _data[2], _data[3]); }
    /**
     * @return Returns string16 value. Is only valid if type is string16.
     */
    constexpr catta::modbus::sunspec::String16 string16Value() const noexcept
    {
        catta::modbus::sunspec::String16::Raw r = {};
        for (std::size_t i = 0; i < catta::modbus::sunspec::String16::size / 2; i++)
        {
            r[i * 2 + 0] = static_cast<char>(_data[i] >> 8);
            r[i * 2 + 1] = static_cast<char>(_data[i] >> 0);
        }
        return catta::modbus::sunspec::String16::create(r.data());
    }
    /**
     * @return Returns string32 value. Is only valid if type is string32.
     */
    constexpr catta::modbus::sunspec::String32 string32Value() const noexcept
    {
        catta::modbus::sunspec::String32::Raw r = {};
        for (std::size_t i = 0; i < catta::modbus::sunspec::String32::size / 2; i++)
        {
            r[i * 2 + 0] = static_cast<char>(_data[i] >> 8);
            r[i * 2 + 1] = static_cast<char>(_data[i] >> 0);
        }
        return catta::modbus::sunspec::String32::create(r.data());
    }
    /**
     * @return Returns the raw data.
     */
    constexpr const std::array<std::uint16_t, 20>& raw() const noexcept { return _data; }
    /**
     * @param[in] other The other Response.
     * @return Returns @b true if the two Response objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Response& other) const noexcept = default;
    /**
     * @return Returns the type of the response.
     */
    constexpr catta::modbus::si::response::Type type() const noexcept { return _type; }

  private:
    using Raw = std::array<std::uint16_t, 20>;
    constexpr Response(const Raw data, const catta::modbus::si::response::Type type) : _data(data), _type(type) {}
    Raw _data;
    catta::modbus::si::response::Type _type;
    constexpr static std::uint16_t pack(const auto v, const auto i) { return static_cast<std::uint16_t>(v >> (i * 16)); }
    constexpr static std::uint32_t unpack(const std::uint16_t v1, const std::uint16_t v0) { return static_cast<std::uint32_t>((v1 << (16)) | v0); }
    constexpr static std::uint64_t unpack(const std::uint16_t v3, const std::uint16_t v2, const std::uint16_t v1, const std::uint16_t v0)
    {
        return (static_cast<std::uint64_t>(v3) << 48) | (static_cast<std::uint64_t>(v2) << 32) | (static_cast<std::uint64_t>(v1) << 16) |
               (static_cast<std::uint64_t>(v0) << 0);
    }
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
