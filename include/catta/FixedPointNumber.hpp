#pragma once

#include <cstdint>
#include <limits>

namespace catta
{
/**
 * @brief A wrapper for 64 signed integer to indicate that the 64 signed integer is represented as fixed point number.
 * @tparam DECIMAL_PLACES Number of decimal places.
 * @author CattaTech - Maik Urbannek
 */
template <std::uint8_t DECIMAL_PLACES>
class FixedPointNumber
{
  public:
    /**
     * Constructor.
     * @param[in] integral The input integer. Can not the maximal number otherwiese empty is returned.
     * @return Returns the fixed number if valid, otherwiese empty.
     */
    constexpr static FixedPointNumber create(const std::int64_t integral) noexcept { return FixedPointNumber(integral); }
    /**
     * Default constructor.
     */
    constexpr FixedPointNumber() noexcept : FixedPointNumber(EMPTY) {}
    /**
     * @return Returns invalid fixed point number.
     */
    constexpr static FixedPointNumber empty() noexcept { return FixedPointNumber(); }
    /**
     * @return Returns the decimal as raw integer.
     */
    constexpr explicit operator std::int64_t() const noexcept { return _integral; }
    /**
     * @param[in] other The other FixedPointNumber.
     * @return Returns @b true if the two FixedPointNumber objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const FixedPointNumber& other) const noexcept = default;

  private:
    constexpr FixedPointNumber(const std::int64_t integral) noexcept : _integral(integral) {}
    std::int64_t _integral;
    static constexpr std::int64_t EMPTY = std::numeric_limits<std::int64_t>::min();
};

}  // namespace catta
