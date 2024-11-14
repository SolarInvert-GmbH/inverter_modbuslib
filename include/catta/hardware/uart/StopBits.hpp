#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace hardware
{
namespace uart
{
/**
 * @brief StopBits represents the number stop bits of the uart communication. The two uart devices have to have the same number of stop bits.
 * @author CattaTech - Maik Urbannek
 */
class StopBits
{
  private:
    constexpr static std::uint8_t ONE = 0;
    constexpr static std::uint8_t TWO = 1;
    constexpr static std::uint8_t EMPTY = 2;

  public:
    /**
     * @param[in] value The enum value of the stop bits.
     * @warning This constructor should not be used. Use one(), two() or empty(). Explicit constructor. Converts uint8 to stop bits.
     */
    [[nodiscard]] constexpr explicit StopBits(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty stop bits.
     */
    [[nodiscard]] constexpr StopBits() noexcept : StopBits(EMPTY) {}
    /**
     * @return Returns the one stop bit.
     */
    [[nodiscard]] constexpr static StopBits one() noexcept { return StopBits{ONE}; }
    /**
     * @return Returns the two stop bits.
     */
    [[nodiscard]] constexpr static StopBits two() noexcept { return StopBits{TWO}; }
    /**
     * @return Returns the empty stop bits.
     */
    [[nodiscard]] constexpr static StopBits empty() noexcept { return StopBits{EMPTY}; }
    /**
     * @param[in] other The other StopBits.
     * @return Returns @b true if the two StopBits objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const StopBits& other) const = default;
    /**
     * @return Returns stop bits as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if one stop bit is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isOne() const noexcept { return _value == ONE; }
    /**
     * @return Returns @b true if two stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isTwo() const noexcept { return _value == TWO; }
    /**
     * @return Returns @b true if empty stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Stop bits in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"ONE", "TWO"};

  private:
    std::uint8_t _value;
};
}  // namespace uart
}  // namespace hardware
}  // namespace catta
