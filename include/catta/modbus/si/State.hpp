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
/**
 * @brief Represents the si state.
 * @author CattaTech - Maik Urbannek
 */
class State
{
  private:
    constexpr static std::uint8_t INIT_LEVEL_1 = 0;
    constexpr static std::uint8_t INIT_LEVEL_2 = 1;
    constexpr static std::uint8_t INIT_LEVEL_3 = 2;
    constexpr static std::uint8_t MPPT = 3;
    constexpr static std::uint8_t RESET = 4;
    constexpr static std::uint8_t CONSTANT_VOLTAGE = 5;
    constexpr static std::uint8_t LOWER_POWER_MODE = 6;
    constexpr static std::uint8_t WIND = 7;
    constexpr static std::uint8_t FACTORY_MODE = 8;
    constexpr static std::uint8_t BATTERY = 9;
    constexpr static std::uint8_t BATTERY_SAFETY = 10;
    constexpr static std::uint8_t EMPTY = 11;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @warning This constructor should not be used. Use initLevel1(), initLevel2(), initLevel3(), mppt(), reset(), constantVoltage(),
     * lowerPowerMode(), wind(), factoryMode(), battery(), batterySafety() or empty(). Explicit constructor. Converts uint8 to state.
     */
    [[nodiscard]] constexpr explicit State(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid state.
     */
    [[nodiscard]] constexpr State() noexcept : State(EMPTY) {}
    /**
     * @return Returns the init level 1.
     */
    [[nodiscard]] constexpr static State initLevel1() noexcept { return State{INIT_LEVEL_1}; }
    /**
     * @return Returns the init level 2.
     */
    [[nodiscard]] constexpr static State initLevel2() noexcept { return State{INIT_LEVEL_2}; }
    /**
     * @return Returns the init level 3.
     */
    [[nodiscard]] constexpr static State initLevel3() noexcept { return State{INIT_LEVEL_3}; }
    /**
     * @return Returns the mppt.
     */
    [[nodiscard]] constexpr static State mppt() noexcept { return State{MPPT}; }
    /**
     * @return Returns the reset.
     */
    [[nodiscard]] constexpr static State reset() noexcept { return State{RESET}; }
    /**
     * @return Returns the constant voltage.
     */
    [[nodiscard]] constexpr static State constantVoltage() noexcept { return State{CONSTANT_VOLTAGE}; }
    /**
     * @return Returns the lower power mode.
     */
    [[nodiscard]] constexpr static State lowerPowerMode() noexcept { return State{LOWER_POWER_MODE}; }
    /**
     * @return Returns the wind.
     */
    [[nodiscard]] constexpr static State wind() noexcept { return State{WIND}; }
    /**
     * @return Returns the factory mode.
     */
    [[nodiscard]] constexpr static State factoryMode() noexcept { return State{FACTORY_MODE}; }
    /**
     * @return Returns the battery.
     */
    [[nodiscard]] constexpr static State battery() noexcept { return State{BATTERY}; }
    /**
     * @return Returns the battery safety.
     */
    [[nodiscard]] constexpr static State batterySafety() noexcept { return State{BATTERY_SAFETY}; }
    /**
     * @return Returns the invalid state.
     */
    [[nodiscard]] constexpr static State empty() noexcept { return State{EMPTY}; }
    /**
     * @param[in] other The other State.
     * @return Returns @b true if the two State objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const State& other) const = default;
    /**
     * @return Returns state as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if init level 1 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInitLevel1() const noexcept { return _value == INIT_LEVEL_1; }
    /**
     * @return Returns @b true if init level 2 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInitLevel2() const noexcept { return _value == INIT_LEVEL_2; }
    /**
     * @return Returns @b true if init level 3 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInitLevel3() const noexcept { return _value == INIT_LEVEL_3; }
    /**
     * @return Returns @b true if mppt is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isMppt() const noexcept { return _value == MPPT; }
    /**
     * @return Returns @b true if reset is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReset() const noexcept { return _value == RESET; }
    /**
     * @return Returns @b true if constant voltage is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isConstantVoltage() const noexcept { return _value == CONSTANT_VOLTAGE; }
    /**
     * @return Returns @b true if lower power mode is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isLowerPowerMode() const noexcept { return _value == LOWER_POWER_MODE; }
    /**
     * @return Returns @b true if wind is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isWind() const noexcept { return _value == WIND; }
    /**
     * @return Returns @b true if factory mode is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFactoryMode() const noexcept { return _value == FACTORY_MODE; }
    /**
     * @return Returns @b true if battery is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBattery() const noexcept { return _value == BATTERY; }
    /**
     * @return Returns @b true if battery safety is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBatterySafety() const noexcept { return _value == BATTERY_SAFETY; }
    /**
     * @return Returns @b true if invalid state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * State in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"INIT_LEVEL_1", "INIT_LEVEL_2",     "INIT_LEVEL_3",     "MPPT",
                                                                      "RESET",        "CONSTANT_VOLTAGE", "LOWER_POWER_MODE", "WIND",
                                                                      "FACTORY_MODE", "BATTERY",          "BATTERY_SAFETY"};

  private:
    std::uint8_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
