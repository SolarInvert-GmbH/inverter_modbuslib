#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Represents the si response nice type.
 * @author CattaTech - Maik Urbannek
 */
class NiceType
{
  private:
    constexpr static std::uint8_t EXCEPTION = 0;
    constexpr static std::uint8_t FACTORY_VALUES = 1;
    constexpr static std::uint8_t READ_ERROR = 2;
    constexpr static std::uint8_t READ_OPERATING_DATA_33 = 3;
    constexpr static std::uint8_t READ_OPERATING_DATA_3E = 4;
    constexpr static std::uint8_t SWITCH_OFF_GRID_RELAY = 5;
    constexpr static std::uint8_t SWITCH_ON_GRID_RELAY = 6;
    constexpr static std::uint8_t FORCE_IDLE = 7;
    constexpr static std::uint8_t DEACTIVATE_IDLE = 8;
    constexpr static std::uint8_t START_CONSTANT_VOLTAGE = 9;
    constexpr static std::uint8_t END_CONSTANT_VOLTAGE = 10;
    constexpr static std::uint8_t SET_POWER_FACTOR = 11;
    constexpr static std::uint8_t CONTROL_BATTERY_INVERT = 12;
    constexpr static std::uint8_t LIMIT_BATTERY_INVERT = 13;
    constexpr static std::uint8_t WRITE_REGISTER = 14;
    constexpr static std::uint8_t READ_REGISTER = 15;
    constexpr static std::uint8_t EMPTY = 16;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use exception(), factoryValues(), readError(), readOperatingData33(), readOperatingData3e(),
     * switchOffGridRelay(), switchOnGridRelay(), forceIdle(), deactivateIdle(), startConstantVoltage(), endConstantVoltage(), setPowerFactor(),
     * controlBatteryInvert(), limitBatteryInvert(), writeRegister(), readRegister() or empty(). Explicit constructor. Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit NiceType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr NiceType() noexcept : NiceType(EMPTY) {}
    /**
     * @return Returns the exception response.
     */
    [[nodiscard]] constexpr static NiceType exception() noexcept { return NiceType{EXCEPTION}; }
    /**
     * @return Returns the factory values 0x31 response.
     */
    [[nodiscard]] constexpr static NiceType factoryValues() noexcept { return NiceType{FACTORY_VALUES}; }
    /**
     * @return Returns the read error 0x40 response.
     */
    [[nodiscard]] constexpr static NiceType readError() noexcept { return NiceType{READ_ERROR}; }
    /**
     * @return Returns the read operating data 0x33 response.
     */
    [[nodiscard]] constexpr static NiceType readOperatingData33() noexcept { return NiceType{READ_OPERATING_DATA_33}; }
    /**
     * @return Returns the read operating data 0x3e response.
     */
    [[nodiscard]] constexpr static NiceType readOperatingData3e() noexcept { return NiceType{READ_OPERATING_DATA_3E}; }
    /**
     * @return Returns the switch off grid relay 0x34.
     */
    [[nodiscard]] constexpr static NiceType switchOffGridRelay() noexcept { return NiceType{SWITCH_OFF_GRID_RELAY}; }
    /**
     * @return Returns the switch on grid relay 0x35.
     */
    [[nodiscard]] constexpr static NiceType switchOnGridRelay() noexcept { return NiceType{SWITCH_ON_GRID_RELAY}; }
    /**
     * @return Returns the force idle 0x36.
     */
    [[nodiscard]] constexpr static NiceType forceIdle() noexcept { return NiceType{FORCE_IDLE}; }
    /**
     * @return Returns the deactivate idle 0x37.
     */
    [[nodiscard]] constexpr static NiceType deactivateIdle() noexcept { return NiceType{DEACTIVATE_IDLE}; }
    /**
     * @return Returns the start constant voltage 0x38.
     */
    [[nodiscard]] constexpr static NiceType startConstantVoltage() noexcept { return NiceType{START_CONSTANT_VOLTAGE}; }
    /**
     * @return Returns the end constant voltage 0x39.
     */
    [[nodiscard]] constexpr static NiceType endConstantVoltage() noexcept { return NiceType{END_CONSTANT_VOLTAGE}; }
    /**
     * @return Returns the set power factor 0x3b.
     */
    [[nodiscard]] constexpr static NiceType setPowerFactor() noexcept { return NiceType{SET_POWER_FACTOR}; }
    /**
     * @return Returns the constrol battery invert 0x3f.
     */
    [[nodiscard]] constexpr static NiceType controlBatteryInvert() noexcept { return NiceType{CONTROL_BATTERY_INVERT}; }
    /**
     * @return Returns the constrol battery invert 0x44.
     */
    [[nodiscard]] constexpr static NiceType limitBatteryInvert() noexcept { return NiceType{LIMIT_BATTERY_INVERT}; }
    /**
     * @return Returns the write register.
     */
    [[nodiscard]] constexpr static NiceType writeRegister() noexcept { return NiceType{WRITE_REGISTER}; }
    /**
     * @return Returns the read register.
     */
    [[nodiscard]] constexpr static NiceType readRegister() noexcept { return NiceType{READ_REGISTER}; }
    /**
     * @return Returns the invalid type.
     */
    [[nodiscard]] constexpr static NiceType empty() noexcept { return NiceType{EMPTY}; }
    /**
     * @param[in] other The other NiceType.
     * @return Returns @b true if the two NiceType objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const NiceType& other) const = default;
    /**
     * @return Returns type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if exception response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isException() const noexcept { return _value == EXCEPTION; }
    /**
     * @return Returns @b true if factory values 0x31 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFactoryValues() const noexcept { return _value == FACTORY_VALUES; }
    /**
     * @return Returns @b true if read error 0x40 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadError() const noexcept { return _value == READ_ERROR; }
    /**
     * @return Returns @b true if read operating data 0x33 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadOperatingData33() const noexcept { return _value == READ_OPERATING_DATA_33; }
    /**
     * @return Returns @b true if read operating data 0x3e response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadOperatingData3e() const noexcept { return _value == READ_OPERATING_DATA_3E; }
    /**
     * @return Returns @b true if switch off grid relay 0x34 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSwitchOffGridRelay() const noexcept { return _value == SWITCH_OFF_GRID_RELAY; }
    /**
     * @return Returns @b true if switch on grid relay 0x35 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSwitchOnGridRelay() const noexcept { return _value == SWITCH_ON_GRID_RELAY; }
    /**
     * @return Returns @b true if force idle 0x36 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isForceIdle() const noexcept { return _value == FORCE_IDLE; }
    /**
     * @return Returns @b true if deactivate idle 0x37 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isDeactivateIdle() const noexcept { return _value == DEACTIVATE_IDLE; }
    /**
     * @return Returns @b true if start constant voltage 0x38 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isStartConstantVoltage() const noexcept { return _value == START_CONSTANT_VOLTAGE; }
    /**
     * @return Returns @b true if end constant voltage 0x39 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEndConstantVoltage() const noexcept { return _value == END_CONSTANT_VOLTAGE; }
    /**
     * @return Returns @b true if set power factor 0x3b is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSetPowerFactor() const noexcept { return _value == SET_POWER_FACTOR; }
    /**
     * @return Returns @b true if constrol battery invert 0x3f is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isControlBatteryInvert() const noexcept { return _value == CONTROL_BATTERY_INVERT; }
    /**
     * @return Returns @b true if constrol battery invert 0x44 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isLimitBatteryInvert() const noexcept { return _value == LIMIT_BATTERY_INVERT; }
    /**
     * @return Returns @b true if write register is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isWriteRegister() const noexcept { return _value == WRITE_REGISTER; }
    /**
     * @return Returns @b true if read register is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadRegister() const noexcept { return _value == READ_REGISTER; }
    /**
     * @return Returns @b true if invalid type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"EXCEPTION",
                                                                      "FACTORY_VALUES",
                                                                      "READ_ERROR",
                                                                      "READ_OPERATING_DATA_33",
                                                                      "READ_OPERATING_DATA_3E",
                                                                      "SWITCH_OFF_GRID_RELAY",
                                                                      "SWITCH_ON_GRID_RELAY",
                                                                      "FORCE_IDLE",
                                                                      "DEACTIVATE_IDLE",
                                                                      "START_CONSTANT_VOLTAGE",
                                                                      "END_CONSTANT_VOLTAGE",
                                                                      "SET_POWER_FACTOR",
                                                                      "CONTROL_BATTERY_INVERT",
                                                                      "LIMIT_BATTERY_INVERT",
                                                                      "WRITE_REGISTER",
                                                                      "READ_REGISTER"};

  private:
    std::uint8_t _value;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
