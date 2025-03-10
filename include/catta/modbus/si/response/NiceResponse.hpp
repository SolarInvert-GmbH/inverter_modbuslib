#pragma once

// std
#include <array>

// sunspec
#include <catta/modbus/sunspec/String.hpp>

// si
#include <catta/modbus/si/RegisterValue.hpp>
#include <catta/modbus/si/WriteRegister.hpp>

// response
#include <catta/modbus/si/response/Exception.hpp>
#include <catta/modbus/si/response/FactoryValues.hpp>
#include <catta/modbus/si/response/NiceType.hpp>
#include <catta/modbus/si/response/ReadError.hpp>
#include <catta/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>

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
 * @brief Class for representing a response with nicer reprensentation.
 *
 * @author CattaTech - Maik Urbannek
 */
class NiceResponse
{
  public:
    /**
     * Default constructor. Creates invalid nice response.
     */
    constexpr NiceResponse() noexcept : NiceResponse(Raw{}, catta::modbus::si::response::NiceType::empty()) {}
    /**
     * @return Returns invalid nice response.
     */
    constexpr static NiceResponse empty() noexcept { return NiceResponse{}; }
    /**
     *  @return Returns @b true if nice response is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _type.isEmpty(); }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns switch off grid relay response.
     */
    static constexpr NiceResponse switchOffGridRelay(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::switchOffGridRelay());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns switch on grid relay response.
     */
    static constexpr NiceResponse switchOnGridRelay(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::switchOnGridRelay());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns force idle response.
     */
    static constexpr NiceResponse forceIdle(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::forceIdle());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns deactivate idle response.
     */
    static constexpr NiceResponse deactivateIdle(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::deactivateIdle());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns start constant voltage response.
     */
    static constexpr NiceResponse startConstantVoltage(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::startConstantVoltage());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns end constant voltage response.
     */
    static constexpr NiceResponse endConstantVoltage(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::endConstantVoltage());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns set power factor response.
     */
    static constexpr NiceResponse setPowerFactor(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::setPowerFactor());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns control battery invert response.
     */
    static constexpr NiceResponse controlBatteryInvert(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::controlBatteryInvert());
    }
    /**
     * @param[in] success Whether the request was successfull.
     * @return Returns limit battery invert response.
     */
    static constexpr NiceResponse limitBatteryInvert(const bool success)
    {
        return NiceResponse(Raw{success}, catta::modbus::si::response::NiceType::limitBatteryInvert());
    }
    /**
     * @param[in] exception The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns exception response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse exception(const catta::modbus::si::response::Exception exception)
    {
        return exception.isEmpty() ? NiceResponse::empty()
                                   : NiceResponse(Raw{exception.value(), exception.request()}, catta::modbus::si::response::NiceType::exception());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns factory values response.
     */
    static constexpr NiceResponse factoryValues(const catta::modbus::si::response::FactoryValues value)
    {
        return value.isEmpty()
                   ? NiceResponse::empty()
                   : NiceResponse(Raw{value.serialnumber().value(), value.productionDate().day().value(), value.productionDate().month().value(),
                                      value.productionDate().year().value(), value.hardwareVersion().value(), value.firmwareVersion().value(),
                                      value.bootstrappVersion().value()},
                                  catta::modbus::si::response::NiceType::factoryValues());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data33 response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse readError(const catta::modbus::si::response::ReadError& value)
    {
        return value.isEmpty() ? NiceResponse::empty()
                               : NiceResponse(Raw{value.overVoltageAC().value(),
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
                                              catta::modbus::si::response::NiceType::readError());
    }
    /**
     * @param[in] value The read operating data 33. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data33 response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse readOperatingData33(const catta::modbus::si::response::ReadOperatingData33& value)
    {
        return value.isEmpty() ? NiceResponse::empty()
                               : NiceResponse(Raw{value.dcVoltage().value(), value.acVoltage().value(), value.gridFrequency().value(),
                                                  static_cast<std::uint16_t>(value.acPower().value()), value.state()},
                                              catta::modbus::si::response::NiceType::readOperatingData33());
    }
    /**
     * @param[in] value The read operating data 3e. Has to be not empty, otherwise empty is returned.
     * @return Returns read operating data3e response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse readOperatingData3e(const catta::modbus::si::response::ReadOperatingData3e& value)
    {
        return value.isEmpty() ? NiceResponse::empty()
                               : NiceResponse(Raw{value.serialNumber().value(), value.type(), value.voltageType().value(),
                                                  value.nominalPower().value(), value.cosphi().value(), pack(value.gridSupplyDailySum().value(), 1),
                                                  pack(value.gridSupplyDailySum().value(), 0), value.powerLimitation().value(),
                                                  pack(value.operatingHours().value(), 1), pack(value.operatingHours().value(), 0),
                                                  value.phase().value(), value.modbusId().value()},
                                              catta::modbus::si::response::NiceType::readOperatingData3e());
    }
    /**
     * @param[in] value The exception. Has to be not empty, otherwise empty is returned.
     * @return Returns exception response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse writeRegister(const catta::modbus::si::WriteRegister value)
    {
        return value.isEmpty() ? NiceResponse::empty()
                               : NiceResponse(Raw{value.registerAddress(), value.raw()}, catta::modbus::si::response::NiceType::writeRegister());
    }
    /**
     * @param[in] registerValue The registerValue. Has to be valid, otherwise empty is returned.
     * @return Returns read register response if input is valid, otherwise empty.
     */
    static constexpr NiceResponse readRegister(const catta::modbus::si::RegisterValue registerValue)
    {
        const auto p = [&registerValue](const std::size_t i) { return registerValue.raw()[i]; };
        return registerValue.isEmpty()
                   ? NiceResponse::empty()
                   : NiceResponse(Raw{registerValue.registerAddress(), p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), p(10), p(11)},
                                  catta::modbus::si::response::NiceType::readRegister());
    }
    /**
     * @return Returns write register value. Is only valid if type is write register.
     */
    constexpr catta::modbus::si::WriteRegister writeRegisterValue() const noexcept
    {
        return catta::modbus::si::WriteRegister::fromRaw(catta::modbus::si::RegisterAddress(static_cast<std::uint8_t>(_data[0])), _data[1]);
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
     * @return Returns the register value. Only valid if type is read register.
     */
    constexpr catta::modbus::si::RegisterValue registerValue() const noexcept
    {
        return catta::modbus::si::RegisterValue(
            std::array<std::uint16_t, 16>{_data[1], _data[2], _data[3], _data[4], _data[5], _data[6], _data[7], _data[8], _data[9], _data[10],
                                          _data[11], _data[12], _data[13], _data[14], _data[15], _data[16]},
            catta::modbus::si::RegisterAddress(static_cast<std::uint8_t>(_data[0])));
    }
    /**
     * @return Returns the raw data.
     */
    constexpr const std::array<std::uint16_t, 20>& raw() const noexcept { return _data; }
    /**
     * @param[in] other The other NiceResponse.
     * @return Returns @b true if the two NiceResponse objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const NiceResponse& other) const noexcept = default;
    /**
     * @return Returns the type of the response.
     */
    constexpr catta::modbus::si::response::NiceType type() const noexcept { return _type; }

  private:
    using Raw = std::array<std::uint16_t, 20>;
    constexpr NiceResponse(const Raw data, const catta::modbus::si::response::NiceType type) : _data(data), _type(type) {}
    Raw _data;
    catta::modbus::si::response::NiceType _type;
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
