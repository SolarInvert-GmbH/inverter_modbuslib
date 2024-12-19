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
namespace request
{
/**
 * @brief Represents the si type.
 * @author CattaTech - Maik Urbannek
 */
class Type
{
  private:
    constexpr static std::uint8_t READ_REGISTER = 0;
    constexpr static std::uint8_t WRITE_REGISTER = 1;
    constexpr static std::uint8_t FACTORY_VALUES = 2;
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
    constexpr static std::uint8_t READ_ERROR = 14;
    constexpr static std::uint8_t EMPTY = 15;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use readRegister(), writeRegister(), factoryValues(), readOperatingData33(),
     * readOperatingData3e(), switchOffGridRelay(), switchOnGridRelay(), forceIdle(), deactivateIdle(), startConstantVoltage(), endConstantVoltage(),
     * setPowerFactor(), controlBatteryInvert(), limitBatteryInvert(), readError() or empty(). Explicit constructor. Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit Type(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr Type() noexcept : Type(EMPTY) {}
    /**
     * @return Returns the read register 0x03.
     */
    [[nodiscard]] constexpr static Type readRegister() noexcept { return Type{READ_REGISTER}; }
    /**
     * @return Returns the write register 0x16.
     */
    [[nodiscard]] constexpr static Type writeRegister() noexcept { return Type{WRITE_REGISTER}; }
    /**
     * @return Returns the factory values request 0x31.
     */
    [[nodiscard]] constexpr static Type factoryValues() noexcept { return Type{FACTORY_VALUES}; }
    /**
     * @return Returns the read operating data 0x33.
     */
    [[nodiscard]] constexpr static Type readOperatingData33() noexcept { return Type{READ_OPERATING_DATA_33}; }
    /**
     * @return Returns the read operating data 0x3e.
     */
    [[nodiscard]] constexpr static Type readOperatingData3e() noexcept { return Type{READ_OPERATING_DATA_3E}; }
    /**
     * @return Returns the switch off grid relay 0x34.
     */
    [[nodiscard]] constexpr static Type switchOffGridRelay() noexcept { return Type{SWITCH_OFF_GRID_RELAY}; }
    /**
     * @return Returns the switch on grid relay 0x35.
     */
    [[nodiscard]] constexpr static Type switchOnGridRelay() noexcept { return Type{SWITCH_ON_GRID_RELAY}; }
    /**
     * @return Returns the force idle 0x36.
     */
    [[nodiscard]] constexpr static Type forceIdle() noexcept { return Type{FORCE_IDLE}; }
    /**
     * @return Returns the deactivate idle 0x37.
     */
    [[nodiscard]] constexpr static Type deactivateIdle() noexcept { return Type{DEACTIVATE_IDLE}; }
    /**
     * @return Returns the start constant voltage 0x38.
     */
    [[nodiscard]] constexpr static Type startConstantVoltage() noexcept { return Type{START_CONSTANT_VOLTAGE}; }
    /**
     * @return Returns the end constant voltage 0x39.
     */
    [[nodiscard]] constexpr static Type endConstantVoltage() noexcept { return Type{END_CONSTANT_VOLTAGE}; }
    /**
     * @return Returns the set power factor 0x3b.
     */
    [[nodiscard]] constexpr static Type setPowerFactor() noexcept { return Type{SET_POWER_FACTOR}; }
    /**
     * @return Returns the constrol battery invert 0x3f.
     */
    [[nodiscard]] constexpr static Type controlBatteryInvert() noexcept { return Type{CONTROL_BATTERY_INVERT}; }
    /**
     * @return Returns the constrol battery invert 0x44.
     */
    [[nodiscard]] constexpr static Type limitBatteryInvert() noexcept { return Type{LIMIT_BATTERY_INVERT}; }
    /**
     * @return Returns the read error 0x40.
     */
    [[nodiscard]] constexpr static Type readError() noexcept { return Type{READ_ERROR}; }
    /**
     * @return Returns the invalid type.
     */
    [[nodiscard]] constexpr static Type empty() noexcept { return Type{EMPTY}; }
    /**
     * @param[in] other The other Type.
     * @return Returns @b true if the two Type objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Type& other) const = default;
    /**
     * @return Returns type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if read register 0x03 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadRegister() const noexcept { return _value == READ_REGISTER; }
    /**
     * @return Returns @b true if write register 0x16 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isWriteRegister() const noexcept { return _value == WRITE_REGISTER; }
    /**
     * @return Returns @b true if factory values request 0x31 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFactoryValues() const noexcept { return _value == FACTORY_VALUES; }
    /**
     * @return Returns @b true if read operating data 0x33 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadOperatingData33() const noexcept { return _value == READ_OPERATING_DATA_33; }
    /**
     * @return Returns @b true if read operating data 0x3e is represented, otherwise @b false.
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
     * @return Returns @b true if read error 0x40 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadError() const noexcept { return _value == READ_ERROR; }
    /**
     * @return Returns @b true if invalid type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"READ_REGISTER",
                                                                      "WRITE_REGISTER",
                                                                      "FACTORY_VALUES",
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
                                                                      "READ_ERROR"};

  private:
    std::uint8_t _value;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
