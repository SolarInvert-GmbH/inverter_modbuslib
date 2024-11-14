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
 * @brief Parity represents the parity of the uart communication. The two uart devices have to have the same parity. No parity is a valid option.
 * @author CattaTech - Maik Urbannek
 */
class Parity
{
  private:
    constexpr static std::uint8_t EVEN = 0;
    constexpr static std::uint8_t ODD = 1;
    constexpr static std::uint8_t EMPTY = 2;

  public:
    /**
     * @param[in] value The enum value of the parity.
     * @warning This constructor should not be used. Use even(), odd() or empty(). Explicit constructor. Converts uint8 to parity.
     */
    [[nodiscard]] constexpr explicit Parity(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty parity.
     */
    [[nodiscard]] constexpr Parity() noexcept : Parity(EMPTY) {}
    /**
     * @return Returns the even parity.
     */
    [[nodiscard]] constexpr static Parity even() noexcept { return Parity{EVEN}; }
    /**
     * @return Returns the odd parity.
     */
    [[nodiscard]] constexpr static Parity odd() noexcept { return Parity{ODD}; }
    /**
     * @return Returns the empty parity.
     */
    [[nodiscard]] constexpr static Parity empty() noexcept { return Parity{EMPTY}; }
    /**
     * @param[in] other The other Parity.
     * @return Returns @b true if the two Parity objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Parity& other) const = default;
    /**
     * @return Returns parity as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if even parity is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEven() const noexcept { return _value == EVEN; }
    /**
     * @return Returns @b true if odd parity is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isOdd() const noexcept { return _value == ODD; }
    /**
     * @return Returns @b true if empty parity is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Parity in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"EVEN", "ODD"};

  private:
    std::uint8_t _value;
};
}  // namespace uart
}  // namespace hardware
}  // namespace catta
