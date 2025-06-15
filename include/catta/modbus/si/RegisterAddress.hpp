#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

// si
#include <catta/modbus/si/RegisterType.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Represents the si register address.
 * @author CattaTech - Maik Urbannek
 */
class RegisterAddress
{
  private:
    constexpr static std::uint8_t COMMON_MANUFACTURER = 0;
    constexpr static std::uint8_t COMMON_MODEL = 1;
    constexpr static std::uint8_t COMMON_SERIAL_NUMBER = 2;
    constexpr static std::uint8_t COMMON_DEVICE_ADDRESS = 3;
    constexpr static std::uint8_t INVERTER_AMPS = 4;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_A = 5;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_B = 6;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_C = 7;
    constexpr static std::uint8_t INVERTER_AMPS_SCALE_FACTOR = 8;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_A = 9;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_B = 10;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_C = 11;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_SCALE_FACTOR = 12;
    constexpr static std::uint8_t INVERTER_AC_POWER = 13;
    constexpr static std::uint8_t INVERTER_AC_POWER_SCALE_FACTOR = 14;
    constexpr static std::uint8_t INVERTER_HERTZ = 15;
    constexpr static std::uint8_t INVERTER_HERTZ_SCALE_FACTOR = 16;
    constexpr static std::uint8_t INVERTER_AC_APPARENT_POWER = 17;
    constexpr static std::uint8_t INVERTER_AC_APPARENT_POWER_SCALE_FACTOR = 18;
    constexpr static std::uint8_t INVERTER_AC_REACTIVE_POWER = 19;
    constexpr static std::uint8_t INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR = 20;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR = 21;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR_SCALE_FACTOR = 22;
    constexpr static std::uint8_t INVERTER_WATT_HOURS = 23;
    constexpr static std::uint8_t INVERTER_WATT_HOURS_SCALE_FACTOR = 24;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE = 25;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = 26;
    constexpr static std::uint8_t INVERTER_DC_POWER = 27;
    constexpr static std::uint8_t INVERTER_DC_POWER_SCALE_FACTOR = 28;
    constexpr static std::uint8_t INVERTER_TEMPERATURE = 29;
    constexpr static std::uint8_t INVERTER_TEMPERATURE_SCALE_FACTOR = 30;
    constexpr static std::uint8_t INVERTER_OPERATING_STATE = 31;
    constexpr static std::uint8_t INVERTER_VENDOR_OPERATING_STATE = 32;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_1 = 33;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_2 = 34;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_3 = 35;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_4 = 36;
    constexpr static std::uint8_t NAMEPLATE_DER_TYPE = 37;
    constexpr static std::uint8_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = 38;
    constexpr static std::uint8_t EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE = 39;
    constexpr static std::uint8_t EMPTY = 40;

  public:
    /**
     * @param[in] value The enum value of the register.
     * @warning This constructor should not be used. Use commonManufacturer(), commonModel(), commonSerialNumber(), commonDeviceAddress(),
     * inverterAmps(), inverterAmpsPhaseA(), inverterAmpsPhaseB(), inverterAmpsPhaseC(), inverterAmpsScaleFactor(), inverterPhaseVoltageA(),
     * inverterPhaseVoltageB(), inverterPhaseVoltageC(), inverterPhaseVoltageScaleFactor(), inverterAcPower(), inverterAcPowerScaleFactor(),
     * inverterHertz(), inverterHertzScaleFactor(), inverterAcApparentPower(), inverterAcApparentPowerScaleFactor(), inverterAcReactivePower(),
     * inverterAcReactivePowerScaleFactor(), inverterPowerFactor(), inverterPowerFactorScaleFactor(), inverterWattHours(),
     * inverterWattHoursScaleFactor(), inverterDcVoltage(), inverterDcVoltageScaleFactor(), inverterDcPower(), inverterDcPowerScaleFactor(),
     * inverterTemperature(), inverterTemperatureScaleFactor(), inverterOperatingState(), inverterVendorOperatingState(),
     * inverterVendorEventBitfield1(), inverterVendorEventBitfield2(), inverterVendorEventBitfield3(), inverterVendorEventBitfield4(),
     * nameplateDerType(), extendedMesurementsAcWattHours(), extendedMesurementsAcLifetimeCharge() or empty(). Explicit constructor. Converts uint8 to
     * register.
     */
    [[nodiscard]] constexpr explicit RegisterAddress(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid register.
     */
    [[nodiscard]] constexpr RegisterAddress() noexcept : RegisterAddress(EMPTY) {}
    /**
     * @return Returns the name of the manufacturer from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonManufacturer() noexcept { return RegisterAddress{COMMON_MANUFACTURER}; }
    /**
     * @return Returns the model name from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonModel() noexcept { return RegisterAddress{COMMON_MODEL}; }
    /**
     * @return Returns the serial number from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonSerialNumber() noexcept { return RegisterAddress{COMMON_SERIAL_NUMBER}; }
    /**
     * @return Returns the device address from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonDeviceAddress() noexcept { return RegisterAddress{COMMON_DEVICE_ADDRESS}; }
    /**
     * @return Returns the device AC current on all phases from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmps() noexcept { return RegisterAddress{INVERTER_AMPS}; }
    /**
     * @return Returns the device AC current on phases a from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseA() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_A}; }
    /**
     * @return Returns the device AC current on phases b from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseB() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_B}; }
    /**
     * @return Returns the device AC current on phases c from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseC() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_C}; }
    /**
     * @return Returns the device AC current scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsScaleFactor() noexcept { return RegisterAddress{INVERTER_AMPS_SCALE_FACTOR}; }
    /**
     * @return Returns the device AC Voltage on phase a from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageA() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_A}; }
    /**
     * @return Returns the device AC Voltage on phase b from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageB() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_B}; }
    /**
     * @return Returns the device AC Voltage on phase c from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageC() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_C}; }
    /**
     * @return Returns the device AC Voltage scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_PHASE_VOLTAGE_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcPower() noexcept { return RegisterAddress{INVERTER_AC_POWER}; }
    /**
     * @return Returns the device AC power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcPowerScaleFactor() noexcept { return RegisterAddress{INVERTER_AC_POWER_SCALE_FACTOR}; }
    /**
     * @return Returns the device line frequency from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertz() noexcept { return RegisterAddress{INVERTER_HERTZ}; }
    /**
     * @return Returns the device line frequency scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertzScaleFactor() noexcept { return RegisterAddress{INVERTER_HERTZ_SCALE_FACTOR}; }
    /**
     * @return Returns the device AC apparent power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcApparentPower() noexcept { return RegisterAddress{INVERTER_AC_APPARENT_POWER}; }
    /**
     * @return Returns the device AC apparent power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcApparentPowerScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_AC_APPARENT_POWER_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC reactive power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcReactivePower() noexcept { return RegisterAddress{INVERTER_AC_REACTIVE_POWER}; }
    /**
     * @return Returns the device AC reactive power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcReactivePowerScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC power factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPowerFactor() noexcept { return RegisterAddress{INVERTER_POWER_FACTOR}; }
    /**
     * @return Returns the device AC power factor scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPowerFactorScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_POWER_FACTOR_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC energy from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterWattHours() noexcept { return RegisterAddress{INVERTER_WATT_HOURS}; }
    /**
     * @return Returns the device AC energy scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterWattHoursScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_WATT_HOURS_SCALE_FACTOR};
    }
    /**
     * @return Returns the device DC voltage from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcVoltage() noexcept { return RegisterAddress{INVERTER_DC_VOLTAGE}; }
    /**
     * @return Returns the device DC voltage scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcVoltageScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_DC_VOLTAGE_SCALE_FACTOR};
    }
    /**
     * @return Returns the device DC power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcPower() noexcept { return RegisterAddress{INVERTER_DC_POWER}; }
    /**
     * @return Returns the device DC power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcPowerScaleFactor() noexcept { return RegisterAddress{INVERTER_DC_POWER_SCALE_FACTOR}; }
    /**
     * @return Returns the device cabinet temperature from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterTemperature() noexcept { return RegisterAddress{INVERTER_TEMPERATURE}; }
    /**
     * @return Returns the device cabinet temperature scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterTemperatureScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_TEMPERATURE_SCALE_FACTOR};
    }
    /**
     * @return Returns the operating state from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterOperatingState() noexcept { return RegisterAddress{INVERTER_OPERATING_STATE}; }
    /**
     * @return Returns the vendor operating state from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorOperatingState() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_OPERATING_STATE};
    }
    /**
     * @return Returns the vendor event bitfield 1 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield1() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_1};
    }
    /**
     * @return Returns the vendor event bitfield 2 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield2() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_2};
    }
    /**
     * @return Returns the vendor event bitfield 3 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield3() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_3};
    }
    /**
     * @return Returns the vendor event bitfield 4 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield4() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_4};
    }
    /**
     * @return Returns the der type from the nameplate model.
     */
    [[nodiscard]] constexpr static RegisterAddress nameplateDerType() noexcept { return RegisterAddress{NAMEPLATE_DER_TYPE}; }
    /**
     * @return Returns the AC lifetime active (real) energy output from the extended mesurements model.
     */
    [[nodiscard]] constexpr static RegisterAddress extendedMesurementsAcWattHours() noexcept
    {
        return RegisterAddress{EXTENDED_MESUREMENTS_AC_WATT_HOURS};
    }
    /**
     * @return Returns the AC lifetime active (real) energy charge from the extended mesurements model.
     */
    [[nodiscard]] constexpr static RegisterAddress extendedMesurementsAcLifetimeCharge() noexcept
    {
        return RegisterAddress{EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE};
    }
    /**
     * @return Returns the invalid register.
     */
    [[nodiscard]] constexpr static RegisterAddress empty() noexcept { return RegisterAddress{EMPTY}; }
    /**
     * @param[in] other The other RegisterAddress.
     * @return Returns @b true if the two RegisterAddress objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const RegisterAddress& other) const = default;
    /**
     * @return Returns register as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if name of the manufacturer from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonManufacturer() const noexcept { return _value == COMMON_MANUFACTURER; }
    /**
     * @return Returns @b true if model name from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonModel() const noexcept { return _value == COMMON_MODEL; }
    /**
     * @return Returns @b true if serial number from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonSerialNumber() const noexcept { return _value == COMMON_SERIAL_NUMBER; }
    /**
     * @return Returns @b true if device address from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonDeviceAddress() const noexcept { return _value == COMMON_DEVICE_ADDRESS; }
    /**
     * @return Returns @b true if device AC current on all phases from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmps() const noexcept { return _value == INVERTER_AMPS; }
    /**
     * @return Returns @b true if device AC current on phases a from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseA() const noexcept { return _value == INVERTER_AMPS_PHASE_A; }
    /**
     * @return Returns @b true if device AC current on phases b from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseB() const noexcept { return _value == INVERTER_AMPS_PHASE_B; }
    /**
     * @return Returns @b true if device AC current on phases c from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseC() const noexcept { return _value == INVERTER_AMPS_PHASE_C; }
    /**
     * @return Returns @b true if device AC current scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsScaleFactor() const noexcept { return _value == INVERTER_AMPS_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC Voltage on phase a from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageA() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_A; }
    /**
     * @return Returns @b true if device AC Voltage on phase b from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageB() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_B; }
    /**
     * @return Returns @b true if device AC Voltage on phase c from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageC() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_C; }
    /**
     * @return Returns @b true if device AC Voltage scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageScaleFactor() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcPower() const noexcept { return _value == INVERTER_AC_POWER; }
    /**
     * @return Returns @b true if device AC power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcPowerScaleFactor() const noexcept { return _value == INVERTER_AC_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device line frequency from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertz() const noexcept { return _value == INVERTER_HERTZ; }
    /**
     * @return Returns @b true if device line frequency scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertzScaleFactor() const noexcept { return _value == INVERTER_HERTZ_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC apparent power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcApparentPower() const noexcept { return _value == INVERTER_AC_APPARENT_POWER; }
    /**
     * @return Returns @b true if device AC apparent power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcApparentPowerScaleFactor() const noexcept { return _value == INVERTER_AC_APPARENT_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC reactive power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcReactivePower() const noexcept { return _value == INVERTER_AC_REACTIVE_POWER; }
    /**
     * @return Returns @b true if device AC reactive power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcReactivePowerScaleFactor() const noexcept { return _value == INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC power factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPowerFactor() const noexcept { return _value == INVERTER_POWER_FACTOR; }
    /**
     * @return Returns @b true if device AC power factor scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPowerFactorScaleFactor() const noexcept { return _value == INVERTER_POWER_FACTOR_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC energy from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterWattHours() const noexcept { return _value == INVERTER_WATT_HOURS; }
    /**
     * @return Returns @b true if device AC energy scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterWattHoursScaleFactor() const noexcept { return _value == INVERTER_WATT_HOURS_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device DC voltage from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcVoltage() const noexcept { return _value == INVERTER_DC_VOLTAGE; }
    /**
     * @return Returns @b true if device DC voltage scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcVoltageScaleFactor() const noexcept { return _value == INVERTER_DC_VOLTAGE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device DC power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcPower() const noexcept { return _value == INVERTER_DC_POWER; }
    /**
     * @return Returns @b true if device DC power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcPowerScaleFactor() const noexcept { return _value == INVERTER_DC_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device cabinet temperature from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterTemperature() const noexcept { return _value == INVERTER_TEMPERATURE; }
    /**
     * @return Returns @b true if device cabinet temperature scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterTemperatureScaleFactor() const noexcept { return _value == INVERTER_TEMPERATURE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if operating state from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterOperatingState() const noexcept { return _value == INVERTER_OPERATING_STATE; }
    /**
     * @return Returns @b true if vendor operating state from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorOperatingState() const noexcept { return _value == INVERTER_VENDOR_OPERATING_STATE; }
    /**
     * @return Returns @b true if vendor event bitfield 1 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield1() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_1; }
    /**
     * @return Returns @b true if vendor event bitfield 2 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield2() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_2; }
    /**
     * @return Returns @b true if vendor event bitfield 3 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield3() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_3; }
    /**
     * @return Returns @b true if vendor event bitfield 4 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield4() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_4; }
    /**
     * @return Returns @b true if der type from the nameplate model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isNameplateDerType() const noexcept { return _value == NAMEPLATE_DER_TYPE; }
    /**
     * @return Returns @b true if AC lifetime active (real) energy output from the extended mesurements model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isExtendedMesurementsAcWattHours() const noexcept { return _value == EXTENDED_MESUREMENTS_AC_WATT_HOURS; }
    /**
     * @return Returns @b true if AC lifetime active (real) energy charge from the extended mesurements model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isExtendedMesurementsAcLifetimeCharge() const noexcept { return _value == EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE; }
    /**
     * @return Returns @b true if invalid register is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Register in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"COMMON_MANUFACTURER",
                                                                      "COMMON_MODEL",
                                                                      "COMMON_SERIAL_NUMBER",
                                                                      "COMMON_DEVICE_ADDRESS",
                                                                      "INVERTER_AMPS",
                                                                      "INVERTER_AMPS_PHASE_A",
                                                                      "INVERTER_AMPS_PHASE_B",
                                                                      "INVERTER_AMPS_PHASE_C",
                                                                      "INVERTER_AMPS_SCALE_FACTOR",
                                                                      "INVERTER_PHASE_VOLTAGE_A",
                                                                      "INVERTER_PHASE_VOLTAGE_B",
                                                                      "INVERTER_PHASE_VOLTAGE_C",
                                                                      "INVERTER_PHASE_VOLTAGE_SCALE_FACTOR",
                                                                      "INVERTER_AC_POWER",
                                                                      "INVERTER_AC_POWER_SCALE_FACTOR",
                                                                      "INVERTER_HERTZ",
                                                                      "INVERTER_HERTZ_SCALE_FACTOR",
                                                                      "INVERTER_AC_APPARENT_POWER",
                                                                      "INVERTER_AC_APPARENT_POWER_SCALE_FACTOR",
                                                                      "INVERTER_AC_REACTIVE_POWER",
                                                                      "INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR",
                                                                      "INVERTER_POWER_FACTOR",
                                                                      "INVERTER_POWER_FACTOR_SCALE_FACTOR",
                                                                      "INVERTER_WATT_HOURS",
                                                                      "INVERTER_WATT_HOURS_SCALE_FACTOR",
                                                                      "INVERTER_DC_VOLTAGE",
                                                                      "INVERTER_DC_VOLTAGE_SCALE_FACTOR",
                                                                      "INVERTER_DC_POWER",
                                                                      "INVERTER_DC_POWER_SCALE_FACTOR",
                                                                      "INVERTER_TEMPERATURE",
                                                                      "INVERTER_TEMPERATURE_SCALE_FACTOR",
                                                                      "INVERTER_OPERATING_STATE",
                                                                      "INVERTER_VENDOR_OPERATING_STATE",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_1",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_2",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_3",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_4",
                                                                      "NAMEPLATE_DER_TYPE",
                                                                      "EXTENDED_MESUREMENTS_AC_WATT_HOURS",
                                                                      "EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE"};

    /**
     *@return Returns the address of the register.
     */
    constexpr std::uint16_t raw() const noexcept
    {
        switch (_value)
        {
            case COMMON_MANUFACTURER:
                return std::uint16_t(40004);
            case COMMON_MODEL:
                return std::uint16_t(40020);
            case COMMON_SERIAL_NUMBER:
                return std::uint16_t(40052);
            case COMMON_DEVICE_ADDRESS:
                return std::uint16_t(40068);
            case INVERTER_AMPS:
                return std::uint16_t(40072);
            case INVERTER_AMPS_PHASE_A:
                return std::uint16_t(40073);
            case INVERTER_AMPS_PHASE_B:
                return std::uint16_t(40074);
            case INVERTER_AMPS_PHASE_C:
                return std::uint16_t(40075);
            case INVERTER_AMPS_SCALE_FACTOR:
                return std::uint16_t(40076);
            case INVERTER_PHASE_VOLTAGE_A:
                return std::uint16_t(40080);
            case INVERTER_PHASE_VOLTAGE_B:
                return std::uint16_t(40081);
            case INVERTER_PHASE_VOLTAGE_C:
                return std::uint16_t(40082);
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR:
                return std::uint16_t(40083);
            case INVERTER_AC_POWER:
                return std::uint16_t(40084);
            case INVERTER_AC_POWER_SCALE_FACTOR:
                return std::uint16_t(40085);
            case INVERTER_HERTZ:
                return std::uint16_t(40086);
            case INVERTER_HERTZ_SCALE_FACTOR:
                return std::uint16_t(40087);
            case INVERTER_AC_APPARENT_POWER:
                return std::uint16_t(40088);
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR:
                return std::uint16_t(40089);
            case INVERTER_AC_REACTIVE_POWER:
                return std::uint16_t(40090);
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR:
                return std::uint16_t(40091);
            case INVERTER_POWER_FACTOR:
                return std::uint16_t(40092);
            case INVERTER_POWER_FACTOR_SCALE_FACTOR:
                return std::uint16_t(40093);
            case INVERTER_WATT_HOURS:
                return std::uint16_t(40094);
            case INVERTER_WATT_HOURS_SCALE_FACTOR:
                return std::uint16_t(40096);
            case INVERTER_DC_VOLTAGE:
                return std::uint16_t(40099);
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR:
                return std::uint16_t(40100);
            case INVERTER_DC_POWER:
                return std::uint16_t(40101);
            case INVERTER_DC_POWER_SCALE_FACTOR:
                return std::uint16_t(40102);
            case INVERTER_TEMPERATURE:
                return std::uint16_t(40103);
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return std::uint16_t(40107);
            case INVERTER_OPERATING_STATE:
                return std::uint16_t(40108);
            case INVERTER_VENDOR_OPERATING_STATE:
                return std::uint16_t(40109);
            case INVERTER_VENDOR_EVENT_BITFIELD_1:
                return std::uint16_t(40110);
            case INVERTER_VENDOR_EVENT_BITFIELD_2:
                return std::uint16_t(40112);
            case INVERTER_VENDOR_EVENT_BITFIELD_3:
                return std::uint16_t(40114);
            case INVERTER_VENDOR_EVENT_BITFIELD_4:
                return std::uint16_t(40116);
            case NAMEPLATE_DER_TYPE:
                return std::uint16_t(40124);
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
                return std::uint16_t(40187);
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE:
                return std::uint16_t(40203);
            default:
                return std::uint16_t(0);
        }
    }

    /**
     * @return Returns the type of the register.
     */
    constexpr catta::modbus::si::RegisterType type() const noexcept
    {
        using Type = catta::modbus::si::RegisterType;
        switch (_value)
        {
            case COMMON_MANUFACTURER:
                return Type::string32();
            case COMMON_MODEL:
                return Type::string32();
            case COMMON_SERIAL_NUMBER:
                return Type::string32();
            case COMMON_DEVICE_ADDRESS:
                return Type::uint16();
            case INVERTER_AMPS:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_A:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_B:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_C:
                return Type::uint16();
            case INVERTER_AMPS_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_PHASE_VOLTAGE_A:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_B:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_C:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_POWER:
                return Type::sint16();
            case INVERTER_AC_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_HERTZ:
                return Type::uint16();
            case INVERTER_HERTZ_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_APPARENT_POWER:
                return Type::uint16();
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_REACTIVE_POWER:
                return Type::uint16();
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_POWER_FACTOR:
                return Type::sint16();
            case INVERTER_POWER_FACTOR_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_WATT_HOURS:
                return Type::uint32();
            case INVERTER_WATT_HOURS_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_DC_VOLTAGE:
                return Type::uint16();
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_DC_POWER:
                return Type::uint16();
            case INVERTER_DC_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_TEMPERATURE:
                return Type::sint16();
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_OPERATING_STATE:
                return Type::uint16();
            case INVERTER_VENDOR_OPERATING_STATE:
                return Type::uint16();
            case INVERTER_VENDOR_EVENT_BITFIELD_1:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_2:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_3:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_4:
                return Type::uint32();
            case NAMEPLATE_DER_TYPE:
                return Type::uint16();
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
                return Type::uint32();
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE:
                return Type::uint32();
            default:
                return Type::empty();
        }
    }

    /**
     * @param[in] value The address as uint16. Has to be exact an address coresponding to and address, otherwise empty is returned.
     * @return Returns the registe address if input is valid, otherwise empty.
     */
    constexpr static catta::modbus::si::RegisterAddress fromRaw(const std::uint16_t value) noexcept
    {
        using Address = catta::modbus::si::RegisterAddress;
        switch (value)
        {
            case 40004:
                return Address(COMMON_MANUFACTURER);
            case 40020:
                return Address(COMMON_MODEL);
            case 40052:
                return Address(COMMON_SERIAL_NUMBER);
            case 40068:
                return Address(COMMON_DEVICE_ADDRESS);
            case 40072:
                return Address(INVERTER_AMPS);
            case 40073:
                return Address(INVERTER_AMPS_PHASE_A);
            case 40074:
                return Address(INVERTER_AMPS_PHASE_B);
            case 40075:
                return Address(INVERTER_AMPS_PHASE_C);
            case 40076:
                return Address(INVERTER_AMPS_SCALE_FACTOR);
            case 40080:
                return Address(INVERTER_PHASE_VOLTAGE_A);
            case 40081:
                return Address(INVERTER_PHASE_VOLTAGE_B);
            case 40082:
                return Address(INVERTER_PHASE_VOLTAGE_C);
            case 40083:
                return Address(INVERTER_PHASE_VOLTAGE_SCALE_FACTOR);
            case 40084:
                return Address(INVERTER_AC_POWER);
            case 40085:
                return Address(INVERTER_AC_POWER_SCALE_FACTOR);
            case 40086:
                return Address(INVERTER_HERTZ);
            case 40087:
                return Address(INVERTER_HERTZ_SCALE_FACTOR);
            case 40088:
                return Address(INVERTER_AC_APPARENT_POWER);
            case 40089:
                return Address(INVERTER_AC_APPARENT_POWER_SCALE_FACTOR);
            case 40090:
                return Address(INVERTER_AC_REACTIVE_POWER);
            case 40091:
                return Address(INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR);
            case 40092:
                return Address(INVERTER_POWER_FACTOR);
            case 40093:
                return Address(INVERTER_POWER_FACTOR_SCALE_FACTOR);
            case 40094:
                return Address(INVERTER_WATT_HOURS);
            case 40096:
                return Address(INVERTER_WATT_HOURS_SCALE_FACTOR);
            case 40099:
                return Address(INVERTER_DC_VOLTAGE);
            case 40100:
                return Address(INVERTER_DC_VOLTAGE_SCALE_FACTOR);
            case 40101:
                return Address(INVERTER_DC_POWER);
            case 40102:
                return Address(INVERTER_DC_POWER_SCALE_FACTOR);
            case 40103:
                return Address(INVERTER_TEMPERATURE);
            case 40107:
                return Address(INVERTER_TEMPERATURE_SCALE_FACTOR);
            case 40108:
                return Address(INVERTER_OPERATING_STATE);
            case 40109:
                return Address(INVERTER_VENDOR_OPERATING_STATE);
            case 40110:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_1);
            case 40112:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_2);
            case 40114:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_3);
            case 40116:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_4);
            case 40124:
                return Address(NAMEPLATE_DER_TYPE);
            case 40187:
                return Address(EXTENDED_MESUREMENTS_AC_WATT_HOURS);
            case 40203:
                return Address(EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE);
            default:
                return Address();
        }
    }

    /**
     * @return Returns @b true if register is readable, otherwise @b false.
     */
    constexpr bool isReadable() const noexcept { return true; }

    /**
     * @return Returns @b true if register is writable, otherwise @b false.
     */
    constexpr bool isWritable() const noexcept
    {
        switch (_value)
        {
            case COMMON_DEVICE_ADDRESS:
                return true;
            default:
                return false;
        }
    }

  private:
    std::uint8_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
