#pragma once

#include <concepts>
#include <cstdint>

namespace catta
{
/**
 * @brief The catta::Unsigned<T> class provides the unsigned vairant of and std::integral in the type.
 * @tparam INTEGRAL The std::integral which is used to find the arcoding unsigned.
 * @author CattaTech - Maik Urbannek
 */
template <std::integral INTEGRAL>
class Unsigned;

/// @cond FALSE

template <>
class Unsigned<std::uint8_t>
{
  public:
    using type = std::uint8_t;
};

template <>
class Unsigned<std::uint16_t>
{
  public:
    using type = std::uint16_t;
};

template <>
class Unsigned<std::uint32_t>
{
  public:
    using type = std::uint32_t;
};

template <>
class Unsigned<std::uint64_t>
{
  public:
    using type = std::uint64_t;
};

template <>
class Unsigned<std::int8_t>
{
  public:
    using type = std::uint8_t;
};

template <>
class Unsigned<std::int16_t>
{
  public:
    using type = std::uint16_t;
};

template <>
class Unsigned<std::int32_t>
{
  public:
    using type = std::uint32_t;
};

template <>
class Unsigned<std::int64_t>
{
  public:
    using type = std::uint64_t;
};

/// @endcond

/**
 * @brief A wrapper for integer to indicate that the integer is represented as decimal number.
 * @tparam INTEGRAL One of the eight integer types.
 * @author CattaTech - Maik Urbannek
 */
template <std::integral INTEGRAL>
class Decimal
{
  public:
    /**
     * Constructor.
     * @param[in] integral The input integer.
     */
    constexpr explicit Decimal(const INTEGRAL integral) : _integral(integral) {}
    /**
     * Default constructor.
     */
    constexpr Decimal() : Decimal(0) {}
    /**
     * @return Returns the decimal as raw integer.
     */
    constexpr explicit operator INTEGRAL() const { return _integral; }
    /**
     * @param[in] other The other Decimal.
     * @return Returns @b true if the two Decimal objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Decimal& other) const { return this->_integral == other._integral; }
    /**
     * @return Returns the biggest power of ten that is not bigger than the decimal number.
     */
    constexpr Unsigned<INTEGRAL>::type getMaxPowerOfTen() const;

  private:
    INTEGRAL _integral;
};

/// @cond FALSE

template <>
constexpr std::uint8_t Decimal<std::uint8_t>::getMaxPowerOfTen() const
{
    if (_integral >= 100) return 100;
    if (_integral >= 10) return 10;
    return 1;
}

template <>
constexpr std::uint16_t Decimal<std::uint16_t>::getMaxPowerOfTen() const
{
    if (_integral >= 10'000) return 10'000;
    if (_integral >= 1'000) return 1'000;
    if (_integral >= 100) return 100;
    if (_integral >= 10) return 10;
    return 1;
}

template <>
constexpr std::uint32_t Decimal<std::uint32_t>::getMaxPowerOfTen() const
{
    if (_integral >= 100'000)
    {
        if (_integral >= 1'000'000'000) return 1'000'000'000;
        if (_integral >= 100'000'000) return 100'000'000;
        if (_integral >= 10'000'000) return 10'000'000;
        if (_integral >= 1'000'000) return 1'000'000;
        return 100'000;
    }
    else
    {
        if (_integral >= 10'000) return 10'000;
        if (_integral >= 1'000) return 1'000;
        if (_integral >= 100) return 100;
        if (_integral >= 10) return 10;
        return 1;
    }
}

template <>
constexpr std::uint64_t Decimal<std::uint64_t>::getMaxPowerOfTen() const
{
    if (_integral >= 1'000'000'000'000'000)
    {
        if (_integral >= 10'000'000'000'000'000'000ull) return 10'000'000'000'000'000'000ull;
        if (_integral >= 1'000'000'000'000'000'000) return 1'000'000'000'000'000'000;
        if (_integral >= 100'000'000'000'000'000) return 100'000'000'000'000'000;
        if (_integral >= 10'000'000'000'000'000) return 10'000'000'000'000'000;
        return 1'000'000'000'000'000;
    }
    else if (_integral >= 10'000'000'000)
    {
        if (_integral >= 100'000'000'000'000) return 100'000'000'000'000;
        if (_integral >= 10'000'000'000'000) return 10'000'000'000'000;
        if (_integral >= 1'000'000'000'000) return 1'000'000'000'000;
        if (_integral >= 100'000'000'000) return 100'000'000'000;
        return 10'000'000'000;
    }
    else if (_integral >= 100'000)
    {
        if (_integral >= 1'000'000'000) return 1'000'000'000;
        if (_integral >= 100'000'000) return 100'000'000;
        if (_integral >= 10'000'000) return 10'000'000;
        if (_integral >= 1'000'000) return 1'000'000;
        return 100'000;
    }
    else
    {
        if (_integral >= 10'000) return 10'000;
        if (_integral >= 1'000) return 1'000;
        if (_integral >= 100) return 100;
        if (_integral >= 10) return 10;
        return 1;
    }
}

template <>
constexpr std::uint8_t Decimal<std::int8_t>::getMaxPowerOfTen() const
{
    const std::uint8_t abs = static_cast<std::uint8_t>(_integral < 0 ? -_integral : _integral);
    return catta::Decimal<std::uint8_t>(abs).getMaxPowerOfTen();
}

template <>
constexpr std::uint16_t Decimal<std::int16_t>::getMaxPowerOfTen() const
{
    const std::uint16_t abs = static_cast<std::uint16_t>(_integral < 0 ? -_integral : _integral);
    return catta::Decimal<std::uint16_t>(abs).getMaxPowerOfTen();
}

template <>
constexpr std::uint32_t Decimal<std::int32_t>::getMaxPowerOfTen() const
{
    const std::uint32_t abs = static_cast<std::uint32_t>(_integral < 0 ? -_integral : _integral);
    return catta::Decimal<std::uint32_t>(abs).getMaxPowerOfTen();
}

template <>
constexpr std::uint64_t Decimal<std::int64_t>::getMaxPowerOfTen() const
{
    const std::uint64_t abs = static_cast<std::uint64_t>(_integral < 0 ? -_integral : _integral);
    return catta::Decimal<std::uint64_t>(abs).getMaxPowerOfTen();
}

/// @endcond

}  // namespace catta
