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
 * @brief Represents the si type.
 * @author CattaTech - Maik Urbannek
 */
class Type
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
    constexpr static std::uint8_t VALUE_16 = 15;
    constexpr static std::uint8_t VALUE_32 = 16;
    constexpr static std::uint8_t VALUE_64 = 17;
    constexpr static std::uint8_t STRING = 18;
    constexpr static std::uint8_t EMPTY = 19;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use exception(), factoryValues(), readError(), readOperatingData33(), readOperatingData3e(),
     * switchOffGridRelay(), switchOnGridRelay(), forceIdle(), deactivateIdle(), startConstantVoltage(), endConstantVoltage(), setPowerFactor(),
     * controlBatteryInvert(), limitBatteryInvert(), writeRegister(), value16(), value32(), value64(), string() or empty(). Explicit constructor.
     * Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit Type(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr Type() noexcept : Type(EMPTY) {}
    /**
     * @return Returns the exception response.
     */
    [[nodiscard]] constexpr static Type exception() noexcept { return Type{EXCEPTION}; }
    /**
     * @return Returns the factory values 0x31 response.
     */
    [[nodiscard]] constexpr static Type factoryValues() noexcept { return Type{FACTORY_VALUES}; }
    /**
     * @return Returns the read error 0x40 response.
     */
    [[nodiscard]] constexpr static Type readError() noexcept { return Type{READ_ERROR}; }
    /**
     * @return Returns the read operating data 0x33 response.
     */
    [[nodiscard]] constexpr static Type readOperatingData33() noexcept { return Type{READ_OPERATING_DATA_33}; }
    /**
     * @return Returns the read operating data 0x3e response.
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
     * @return Returns the write register.
     */
    [[nodiscard]] constexpr static Type writeRegister() noexcept { return Type{WRITE_REGISTER}; }
    /**
     * @return Returns the 2 byte response.
     */
    [[nodiscard]] constexpr static Type value16() noexcept { return Type{VALUE_16}; }
    /**
     * @return Returns the 4 byte response.
     */
    [[nodiscard]] constexpr static Type value32() noexcept { return Type{VALUE_32}; }
    /**
     * @return Returns the 8 byte response.
     */
    [[nodiscard]] constexpr static Type value64() noexcept { return Type{VALUE_64}; }
    /**
     * @return Returns the string response.
     */
    [[nodiscard]] constexpr static Type string() noexcept { return Type{STRING}; }
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
     * @return Returns @b true if 2 byte response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isValue16() const noexcept { return _value == VALUE_16; }
    /**
     * @return Returns @b true if 4 byte response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isValue32() const noexcept { return _value == VALUE_32; }
    /**
     * @return Returns @b true if 8 byte response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isValue64() const noexcept { return _value == VALUE_64; }
    /**
     * @return Returns @b true if string response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isString() const noexcept { return _value == STRING; }
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
                                                                      "VALUE_16",
                                                                      "VALUE_32",
                                                                      "VALUE_64",
                                                                      "STRING"};

  private:
    std::uint8_t _value;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
