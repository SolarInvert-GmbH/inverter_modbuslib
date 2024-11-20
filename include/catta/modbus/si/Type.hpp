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
 * @brief Represents the si type.
 * @author CattaTech - Maik Urbannek
 */
class Type
{
  private:
    constexpr static std::uint8_t SOLAR = 0;
    constexpr static std::uint8_t WIND = 1;
    constexpr static std::uint8_t BATTERY = 2;
    constexpr static std::uint8_t EMPTY = 3;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use solar(), wind(), battery() or empty(). Explicit constructor. Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit Type(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr Type() noexcept : Type(EMPTY) {}
    /**
     * @return Returns the solar.
     */
    [[nodiscard]] constexpr static Type solar() noexcept { return Type{SOLAR}; }
    /**
     * @return Returns the wind.
     */
    [[nodiscard]] constexpr static Type wind() noexcept { return Type{WIND}; }
    /**
     * @return Returns the battery.
     */
    [[nodiscard]] constexpr static Type battery() noexcept { return Type{BATTERY}; }
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
     * @return Returns @b true if solar is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSolar() const noexcept { return _value == SOLAR; }
    /**
     * @return Returns @b true if wind is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isWind() const noexcept { return _value == WIND; }
    /**
     * @return Returns @b true if battery is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBattery() const noexcept { return _value == BATTERY; }
    /**
     * @return Returns @b true if invalid type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"SOLAR", "WIND", "BATTERY"};

  private:
    std::uint8_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
