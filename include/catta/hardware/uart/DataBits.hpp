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
 * @brief DataBits represents the number data bits of the uart communication. The two uart devices have to have the same number of data bits.
 * @author CattaTech - Maik Urbannek
 */
class DataBits
{
  private:
    constexpr static std::uint8_t FIVE = 0;
    constexpr static std::uint8_t SIX = 1;
    constexpr static std::uint8_t SEVEN = 2;
    constexpr static std::uint8_t EIGHT = 3;
    constexpr static std::uint8_t EMPTY = 4;

  public:
    /**
     * @param[in] value The enum value of the data bits.
     * @warning This constructor should not be used. Use five(), six(), seven(), eight() or empty(). Explicit constructor. Converts uint8 to data
     * bits.
     */
    [[nodiscard]] constexpr explicit DataBits(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty data bits.
     */
    [[nodiscard]] constexpr DataBits() noexcept : DataBits(EMPTY) {}
    /**
     * @return Returns the five stop bits.
     */
    [[nodiscard]] constexpr static DataBits five() noexcept { return DataBits{FIVE}; }
    /**
     * @return Returns the six stop bits.
     */
    [[nodiscard]] constexpr static DataBits six() noexcept { return DataBits{SIX}; }
    /**
     * @return Returns the seven stop bits.
     */
    [[nodiscard]] constexpr static DataBits seven() noexcept { return DataBits{SEVEN}; }
    /**
     * @return Returns the eight stop bits.
     */
    [[nodiscard]] constexpr static DataBits eight() noexcept { return DataBits{EIGHT}; }
    /**
     * @return Returns the empty data bits.
     */
    [[nodiscard]] constexpr static DataBits empty() noexcept { return DataBits{EMPTY}; }
    /**
     * @param[in] other The other DataBits.
     * @return Returns @b true if the two DataBits objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const DataBits& other) const = default;
    /**
     * @return Returns data bits as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if five stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFive() const noexcept { return _value == FIVE; }
    /**
     * @return Returns @b true if six stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSix() const noexcept { return _value == SIX; }
    /**
     * @return Returns @b true if seven stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSeven() const noexcept { return _value == SEVEN; }
    /**
     * @return Returns @b true if eight stop bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEight() const noexcept { return _value == EIGHT; }
    /**
     * @return Returns @b true if empty data bits is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Data bits in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"FIVE", "SIX", "SEVEN", "EIGHT"};

  private:
    std::uint8_t _value;
};
}  // namespace uart
}  // namespace hardware
}  // namespace catta
