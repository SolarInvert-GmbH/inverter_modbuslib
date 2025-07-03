#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Represents tracking selection.
 * @author CattaTech - Maik Urbannek
 */
class TrackingSelection
{
  private:
    constexpr static std::uint8_t CHARGE_TO_U_SOLAR_BATTERY_ERROR = 0;
    constexpr static std::uint8_t SWITCH_OFF = 1;
    constexpr static std::uint8_t CHARGE_TO_U_MAX = 2;
    constexpr static std::uint8_t EMPTY = 3;

  public:
    /**
     * @param[in] value The enum value of the tracking selection.
     * @warning This constructor should not be used. Use chargeToUSolarBatteryError(), switchOff(), chargeToUMax() or empty(). Explicit constructor.
     * Converts uint8 to tracking selection.
     */
    [[nodiscard]] constexpr explicit TrackingSelection(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid tracking selection.
     */
    [[nodiscard]] constexpr TrackingSelection() noexcept : TrackingSelection(EMPTY) {}
    /**
     * @return Returns the charge to U_SOLAR_BATTERY_ERROR with P_MAX_ERROR.
     */
    [[nodiscard]] constexpr static TrackingSelection chargeToUSolarBatteryError() noexcept
    {
        return TrackingSelection{CHARGE_TO_U_SOLAR_BATTERY_ERROR};
    }
    /**
     * @return Returns the switch off.
     */
    [[nodiscard]] constexpr static TrackingSelection switchOff() noexcept { return TrackingSelection{SWITCH_OFF}; }
    /**
     * @return Returns the charge to U_MAX with P_MAX_ERROR.
     */
    [[nodiscard]] constexpr static TrackingSelection chargeToUMax() noexcept { return TrackingSelection{CHARGE_TO_U_MAX}; }
    /**
     * @return Returns the invalid tracking selection.
     */
    [[nodiscard]] constexpr static TrackingSelection empty() noexcept { return TrackingSelection{EMPTY}; }
    /**
     * @param[in] other The other TrackingSelection.
     * @return Returns @b true if the two TrackingSelection objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const TrackingSelection& other) const = default;
    /**
     * @return Returns tracking selection as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if charge to U_SOLAR_BATTERY_ERROR with P_MAX_ERROR is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isChargeToUSolarBatteryError() const noexcept { return _value == CHARGE_TO_U_SOLAR_BATTERY_ERROR; }
    /**
     * @return Returns @b true if switch off is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSwitchOff() const noexcept { return _value == SWITCH_OFF; }
    /**
     * @return Returns @b true if charge to U_MAX with P_MAX_ERROR is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isChargeToUMax() const noexcept { return _value == CHARGE_TO_U_MAX; }
    /**
     * @return Returns @b true if invalid tracking selection is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Tracking selection in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"CHARGE_TO_U_SOLAR_BATTERY_ERROR", "SWITCH_OFF", "CHARGE_TO_U_MAX"};

  private:
    std::uint8_t _value;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
