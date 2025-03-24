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
    constexpr static std::uint8_t INVERTER_WATT = 13;
    constexpr static std::uint8_t INVERTER_WATT_SCALE_FACTOR = 14;
    constexpr static std::uint8_t INVERTER_HERTZ = 15;
    constexpr static std::uint8_t INVERTER_HERTZ_SCALE_FACTOR = 16;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR = 17;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR_SCALE_FACTOR = 18;
    constexpr static std::uint8_t INVERTER_WATT_HOURS = 19;
    constexpr static std::uint8_t INVERTER_WATT_HOURS_SCALE_FACTOR = 20;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE = 21;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = 22;
    constexpr static std::uint8_t INVERTER_TEMPERATURE = 23;
    constexpr static std::uint8_t INVERTER_TEMPERATURE_SCALE_FACTOR = 24;
    constexpr static std::uint8_t INVERTER_OPERATING_STATE = 25;
    constexpr static std::uint8_t NAMEPLATE_DER_TYPE = 26;
    constexpr static std::uint8_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = 27;
    constexpr static std::uint8_t EMPTY = 28;

  public:
    /**
     * @param[in] value The enum value of the register.
     * @warning This constructor should not be used. Use commonManufacturer(), commonModel(), commonSerialNumber(), commonDeviceAddress(),
     * inverterAmps(), inverterAmpsPhaseA(), inverterAmpsPhaseB(), inverterAmpsPhaseC(), inverterAmpsScaleFactor(), inverterPhaseVoltageA(),
     * inverterPhaseVoltageB(), inverterPhaseVoltageC(), inverterPhaseVoltageScaleFactor(), inverterWatt(), inverterWattScaleFactor(),
     * inverterHertz(), inverterHertzScaleFactor(), inverterPowerFactor(), inverterPowerFactorScaleFactor(), inverterWattHours(),
     * inverterWattHoursScaleFactor(), inverterDcVoltage(), inverterDcVoltageScaleFactor(), inverterTemperature(), inverterTemperatureScaleFactor(),
     * inverterOperatingState(), nameplateDerType(), extendedMesurementsAcWattHours() or empty(). Explicit constructor. Converts uint8 to register.
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
    [[nodiscard]] constexpr static RegisterAddress inverterWatt() noexcept { return RegisterAddress{INVERTER_WATT}; }
    /**
     * @return Returns the device AC power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterWattScaleFactor() noexcept { return RegisterAddress{INVERTER_WATT_SCALE_FACTOR}; }
    /**
     * @return Returns the device line frequency from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertz() noexcept { return RegisterAddress{INVERTER_HERTZ}; }
    /**
     * @return Returns the device line frequency scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertzScaleFactor() noexcept { return RegisterAddress{INVERTER_HERTZ_SCALE_FACTOR}; }
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
    [[nodiscard]] constexpr bool isInverterWatt() const noexcept { return _value == INVERTER_WATT; }
    /**
     * @return Returns @b true if device AC power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterWattScaleFactor() const noexcept { return _value == INVERTER_WATT_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device line frequency from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertz() const noexcept { return _value == INVERTER_HERTZ; }
    /**
     * @return Returns @b true if device line frequency scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertzScaleFactor() const noexcept { return _value == INVERTER_HERTZ_SCALE_FACTOR; }
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
     * @return Returns @b true if der type from the nameplate model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isNameplateDerType() const noexcept { return _value == NAMEPLATE_DER_TYPE; }
    /**
     * @return Returns @b true if AC lifetime active (real) energy output from the extended mesurements model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isExtendedMesurementsAcWattHours() const noexcept { return _value == EXTENDED_MESUREMENTS_AC_WATT_HOURS; }
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
                                                                      "INVERTER_WATT",
                                                                      "INVERTER_WATT_SCALE_FACTOR",
                                                                      "INVERTER_HERTZ",
                                                                      "INVERTER_HERTZ_SCALE_FACTOR",
                                                                      "INVERTER_POWER_FACTOR",
                                                                      "INVERTER_POWER_FACTOR_SCALE_FACTOR",
                                                                      "INVERTER_WATT_HOURS",
                                                                      "INVERTER_WATT_HOURS_SCALE_FACTOR",
                                                                      "INVERTER_DC_VOLTAGE",
                                                                      "INVERTER_DC_VOLTAGE_SCALE_FACTOR",
                                                                      "INVERTER_TEMPERATURE",
                                                                      "INVERTER_TEMPERATURE_SCALE_FACTOR",
                                                                      "INVERTER_OPERATING_STATE",
                                                                      "NAMEPLATE_DER_TYPE",
                                                                      "EXTENDED_MESUREMENTS_AC_WATT_HOURS"};

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
            case INVERTER_WATT:
                return std::uint16_t(40084);
            case INVERTER_WATT_SCALE_FACTOR:
                return std::uint16_t(40085);
            case INVERTER_HERTZ:
                return std::uint16_t(40086);
            case INVERTER_HERTZ_SCALE_FACTOR:
                return std::uint16_t(40087);
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
            case INVERTER_TEMPERATURE:
                return std::uint16_t(40103);
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return std::uint16_t(40107);
            case INVERTER_OPERATING_STATE:
                return std::uint16_t(40108);
            case NAMEPLATE_DER_TYPE:
                return std::uint16_t(40124);
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
                return std::uint16_t(40187);
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
            case INVERTER_WATT:
                return Type::sint16();
            case INVERTER_WATT_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_HERTZ:
                return Type::uint16();
            case INVERTER_HERTZ_SCALE_FACTOR:
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
            case INVERTER_TEMPERATURE:
                return Type::sint16();
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_OPERATING_STATE:
                return Type::uint16();
            case NAMEPLATE_DER_TYPE:
                return Type::uint16();
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
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
                return Address(INVERTER_WATT);
            case 40085:
                return Address(INVERTER_WATT_SCALE_FACTOR);
            case 40086:
                return Address(INVERTER_HERTZ);
            case 40087:
                return Address(INVERTER_HERTZ_SCALE_FACTOR);
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
            case 40103:
                return Address(INVERTER_TEMPERATURE);
            case 40107:
                return Address(INVERTER_TEMPERATURE_SCALE_FACTOR);
            case 40108:
                return Address(INVERTER_OPERATING_STATE);
            case 40124:
                return Address(NAMEPLATE_DER_TYPE);
            case 40187:
                return Address(EXTENDED_MESUREMENTS_AC_WATT_HOURS);
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
