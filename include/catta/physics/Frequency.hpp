#pragma once

// std
#include <compare>
#include <limits>
#include <ratio>
#include <type_traits>

// catta
#include <catta/RatioConcept.hpp>

namespace catta
{
namespace physics
{
/**
 * @tparam BASE Intereger type.
 * @tparam RATIO The resolution of the frequency. For example milli hertz or kilo hertz.
 * @brief Class to represent different resolutions of frequency.
 * @author CattaTech - Maik Urbannek
 */
template <std::signed_integral BASE, catta::RatioConcept RATIO>
class Frequency
{
  public:
    /**
     * The base signed integer type.
     */
    using Base = BASE;
    /**
     * The resolution of the frequency. For example milli hertz or kilo hertz.
     */
    using Ratio = RATIO;
    /**
     * @param[in] count The value of the frequency in the given resolution.
     * Constructor.
     */
    [[nodiscard]] explicit constexpr Frequency(const Base count) noexcept : _count(count) {}
    /**
     * Default constructor. Creates zero frequency in given resolution.
     */
    [[nodiscard]] constexpr Frequency() : Frequency(0) {}
    /**
     * @tparam OTHER The resolution of the input frequency. For example milli hertz or kilo hertz. The OTHER resolution has to fit with a whole intger
     * in RATIO resolution. So no information is lost. It is for example possible to create kilo hertz object with a milli hertz object, but not the
     * other way around.
     * @param other Frequency object with same or lower resolution than the to be created object.
     * Copy constructor.
     */
    template <catta::RatioConcept OTHER, std::enable_if_t<(OTHER::num * RATIO::den) % (RATIO::num * OTHER::den) == 0, bool> = true>
    [[nodiscard]] constexpr Frequency(const Frequency<BASE, OTHER>& other) noexcept
        : _count(BASE{BASE{(OTHER::num * RATIO::den) / (RATIO::num * OTHER::den)} * other.count()})
    {
    }
    /**
     * @return Returns the interger value of the frequency in the given resolution.
     */
    [[nodiscard]] constexpr Base count() const noexcept { return _count; }
    /**
     * @return Returns frequency with inverse sign.
     */
    [[nodiscard]] constexpr Frequency operator-() const noexcept { return Frequency{-_count}; }
    /**
     * @return Returns the same frequency.
     */
    [[nodiscard]] constexpr Frequency operator+() const noexcept { return *this; }
    /**
     * Increments frequency. frequency++ and ++frequency is the same (increments functions do not return anything).
     */
    constexpr void operator++() noexcept { _count++; }
    /**
     * Increments frequency. frequency++ and ++frequency is the same (increments functions do not return anything).
     */
    constexpr void operator++(int) noexcept { _count++; }
    /**
     * Decrements frequency. frequency-- and --frequency is the same (decrements functions do not return anything).
     */
    constexpr void operator--() noexcept { _count--; }
    /**
     * Decrements frequency. frequency-- and --frequency is the same (decrements functions do not return anything).
     */
    constexpr void operator--(int) noexcept { _count--; }
    /**
     * @param[in] other A scalar value to multiply with frequency.
     * @return Returns the scaled frequency.
     */
    [[nodiscard]] constexpr Frequency operator*(const Base other) const noexcept { return Frequency{_count * other}; }
    /**
     * @param[in] other A scalar value to divide from frequency.
     * @return Returns the scaled frequency. Beware posible information loss because integer arithmetic.
     */
    [[nodiscard]] constexpr Frequency operator/(const Base other) const noexcept { return Frequency{_count / other}; }
    /**
     * @param other Other Frequency object to compare.
     * @return Returns the tree-way comparision (implements <,>,<= and >=).
     */
    [[nodiscard]] constexpr auto operator<=>(const Frequency& other) const noexcept { return _count <=> other._count; }
    /**
     * @param other Other Frequency object to compare.
     * @return Returns @b true if two Frequency objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Frequency& other) const noexcept { return _count == other._count; }
    /**
     * @return Returns the smallest possible frequency value in the given resolution.
     */
    [[nodiscard]] constexpr static Frequency min() { return Frequency{std::numeric_limits<Base>::min()}; }
    /**
     * @return Returns the biggest possible frequency value in the given resolution.
     */
    [[nodiscard]] constexpr static Frequency max() { return Frequency{std::numeric_limits<Base>::max()}; }
    /**
     * @return Returns zero hertz. Is the same as default constructor.
     */
    [[nodiscard]] constexpr static Frequency zero() { return Frequency{}; }

  private:
    BASE _count;
};

/**
 * @tparam RATIO1 The scaling factor of the first frequency.
 * @tparam RATIO2 The scaling factor of the second frequency.
 * @return Returns the sum of both frequencies in scaling with the higest resolution (of RATIO1 and RATIO2).
 * Only possible without information loss.  One of the ratios has th fit with a whole intger in other ratio.
 */
template <catta::RatioConcept RATIO1, catta::RatioConcept RATIO2, std::signed_integral BASE,
          std::enable_if_t<(RATIO2::num * RATIO1::den) % (RATIO1::num * RATIO2::den) == 0, bool> = true>
[[nodiscard]] constexpr Frequency<BASE, RATIO1> operator+(const Frequency<BASE, RATIO1> a, const Frequency<BASE, RATIO2> b) noexcept
{
    return Frequency<BASE, RATIO1>{static_cast<BASE>(a.count() + BASE{Frequency<BASE, RATIO1>{b}.count()})};
}

/**
 * @tparam RATIO1 The scaling factor of the first frequency.
 * @tparam RATIO2 The scaling factor of the second frequency.
 * @return Returns the sum of both frequencies in scaling with the higest resolution (of RATIO1 and RATIO2).
 * Only possible without information loss.  One of the ratios has th fit with a whole intger in other ratio.
 */
template <
    catta::RatioConcept RATIO1, catta::RatioConcept RATIO2, std::signed_integral BASE,
    std::enable_if_t<(RATIO2::num * RATIO1::den) % (RATIO1::num * RATIO2::den) == 0 && (RATIO2::num != RATIO1::num || RATIO1::den != RATIO2::den),
                     bool> = true>
[[nodiscard]] constexpr Frequency<BASE, RATIO1> operator+(const Frequency<BASE, RATIO2> a, const Frequency<BASE, RATIO1> b) noexcept
{
    return Frequency<BASE, RATIO1>{static_cast<BASE>(BASE{Frequency<BASE, RATIO1>{a}.count()} + b.count())};
}

/**
 * @tparam RATIO1 The scaling factor of the first frequency.
 * @tparam RATIO2 The scaling factor of the second frequency.
 * @return Returns the differce of both frequencies in scaling with the higest resolution (of RATIO1 and RATIO2).
 * Only possible without information loss.  One of the ratios has th fit with a whole intger in other ratio.
 */
template <catta::RatioConcept RATIO1, catta::RatioConcept RATIO2, std::signed_integral BASE,
          std::enable_if_t<(RATIO2::num * RATIO1::den) % (RATIO1::num * RATIO2::den) == 0, bool> = true>
[[nodiscard]] constexpr Frequency<BASE, RATIO1> operator-(const Frequency<BASE, RATIO1> a, const Frequency<BASE, RATIO2> b) noexcept
{
    return Frequency<BASE, RATIO1>{static_cast<BASE>(a.count() - BASE{Frequency<BASE, RATIO1>{b}.count()})};
}

/**
 * @tparam RATIO1 The scaling factor of the first frequency.
 * @tparam RATIO2 The scaling factor of the second frequency.
 * @return Returns the differce of both frequencies in scaling with the higest resolution (of RATIO1 and RATIO2).
 * Only possible without information loss.  One of the ratios has th fit with a whole intger in other ratio.
 */
template <
    catta::RatioConcept RATIO1, catta::RatioConcept RATIO2, std::signed_integral BASE,
    std::enable_if_t<(RATIO2::num * RATIO1::den) % (RATIO1::num * RATIO2::den) == 0 && (RATIO2::num != RATIO1::num || RATIO1::den != RATIO2::den),
                     bool> = true>
[[nodiscard]] constexpr Frequency<BASE, RATIO1> operator-(const Frequency<BASE, RATIO2> a, const Frequency<BASE, RATIO1> b) noexcept
{
    return Frequency<BASE, RATIO1>{static_cast<BASE>(BASE{Frequency<BASE, RATIO1>{a}.count()} - b.count())};
}

/**
 * Frequency class with 64 bit integer with one nano hertz resolution.
 */
using NanoHertz64 = Frequency<std::int64_t, std::nano>;
/**
 * Frequency class with 64 bit integer with one micro hertz resolution.
 */
using MicroHertz64 = Frequency<std::int64_t, std::micro>;
/**
 * Frequency class with 64 bit integer with one milli hertz resolution.
 */
using MilliHertz64 = Frequency<std::int64_t, std::milli>;
/**
 * Frequency class with 64 bit integer with one hertz resolution.
 */
using Hertz64 = Frequency<std::int64_t, std::ratio<1>>;
/**
 * Frequency class with 64 bit integer with one kilo hertz resolution.
 */
using KiloHertz64 = Frequency<std::int64_t, std::kilo>;
/**
 * Frequency class with 64 bit integer with one mega hertz resolution.
 */
using MegaHertz64 = Frequency<std::int64_t, std::mega>;

/**
 * Frequency class with 32 bit integer with one nano hertz resolution.
 */
using NanoHertz32 = Frequency<std::int32_t, std::nano>;
/**
 * Frequency class with 32 bit integer with one micro hertz resolution.
 */
using MicroHertz32 = Frequency<std::int32_t, std::micro>;
/**
 * Frequency class with 32 bit integer with one milli hertz resolution.
 */
using MilliHertz32 = Frequency<std::int32_t, std::milli>;
/**
 * Frequency class with 32 bit integer with one hertz resolution.
 */
using Hertz32 = Frequency<std::int32_t, std::ratio<1>>;
/**
 * Frequency class with 32 bit integer with one kilo hertz resolution.
 */
using KiloHertz32 = Frequency<std::int32_t, std::kilo>;
/**
 * Frequency class with 32 bit integer with one mega hertz resolution.
 */
using MegaHertz32 = Frequency<std::int32_t, std::mega>;

/**
 * Frequency class with 16 bit integer with one nano hertz resolution.
 */
using NanoHertz16 = Frequency<std::int16_t, std::nano>;
/**
 * Frequency class with 16 bit integer with one micro hertz resolution.
 */
using MicroHertz16 = Frequency<std::int16_t, std::micro>;
/**
 * Frequency class with 16 bit integer with one milli hertz resolution.
 */
using MilliHertz16 = Frequency<std::int16_t, std::milli>;
/**
 * Frequency class with 16 bit integer with one hertz resolution.
 */
using Hertz16 = Frequency<std::int16_t, std::ratio<1>>;
/**
 * Frequency class with 16 bit integer with one kilo hertz resolution.
 */
using KiloHertz16 = Frequency<std::int16_t, std::kilo>;
/**
 * Frequency class with 16 bit integer with one mega hertz resolution.
 */
using MegaHertz16 = Frequency<std::int16_t, std::mega>;

/**
 * @namespace catta::physics::frequency64_literal Holds 64 bit frequency literals.
 */
namespace frequency64_literal
{
/**
 * @param[in] i The number of nano hertz.
 * @return Returns the given frequency in one nano hertz resolution.
 */
[[nodiscard]] constexpr NanoHertz64 operator""_nHz(const unsigned long long i) noexcept { return NanoHertz64(static_cast<NanoHertz64::Base>(i)); }
/**
 * @param[in] i The number of micro hertz.
 * @return Returns the given frequency in one micro hertz resolution.
 */
[[nodiscard]] constexpr MicroHertz64 operator""_uHz(const unsigned long long i) noexcept { return MicroHertz64(static_cast<MicroHertz64::Base>(i)); }
/**
 * @param[in] i The number of milli hertz.
 * @return Returns the given frequency in one milli hertz resolution.
 */
[[nodiscard]] constexpr MilliHertz64 operator""_mHz(const unsigned long long i) noexcept { return MilliHertz64(static_cast<MilliHertz64::Base>(i)); }
/**
 * @param[in] i The number of hertz.
 * @return Returns the given frequency in one hertz resolution.
 */
[[nodiscard]] constexpr Hertz64 operator""_Hz(const unsigned long long i) noexcept { return Hertz64(static_cast<Hertz64::Base>(i)); }
/**
 * @param[in] i The number of kilo hertz.
 * @return Returns the given frequency in one kilo hertz resolution.
 */
[[nodiscard]] constexpr KiloHertz64 operator""_kHz(const unsigned long long i) noexcept { return KiloHertz64(static_cast<KiloHertz64::Base>(i)); }
/**
 * @param[in] i The number of mega hertz.
 * @return Returns the given frequency in one mega hertz resolution.
 */
[[nodiscard]] constexpr MegaHertz64 operator""_MHz(const unsigned long long i) noexcept { return MegaHertz64(static_cast<MegaHertz64::Base>(i)); }
}  // namespace frequency64_literal

/**
 * @namespace catta::physics::frequency32_literal Holds 32 bit frequency literals.
 */
namespace frequency32_literal
{
/**
 * @param[in] i The number of nano hertz.
 * @return Returns the given frequency in one nano hertz resolution.
 */
[[nodiscard]] constexpr NanoHertz32 operator""_nHz(const unsigned long long i) noexcept { return NanoHertz32(static_cast<NanoHertz32::Base>(i)); }
/**
 * @param[in] i The number of micro hertz.
 * @return Returns the given frequency in one micro hertz resolution.
 */
[[nodiscard]] constexpr MicroHertz32 operator""_uHz(const unsigned long long i) noexcept { return MicroHertz32(static_cast<MicroHertz32::Base>(i)); }
/**
 * @param[in] i The number of milli hertz.
 * @return Returns the given frequency in one milli hertz resolution.
 */
[[nodiscard]] constexpr MilliHertz32 operator""_mHz(const unsigned long long i) noexcept { return MilliHertz32(static_cast<MilliHertz32::Base>(i)); }
/**
 * @param[in] i The number of hertz.
 * @return Returns the given frequency in one hertz resolution.
 */
[[nodiscard]] constexpr Hertz32 operator""_Hz(const unsigned long long i) noexcept { return Hertz32(static_cast<Hertz32::Base>(i)); }
/**
 * @param[in] i The number of kilo hertz.
 * @return Returns the given frequency in one kilo hertz resolution.
 */
[[nodiscard]] constexpr KiloHertz32 operator""_kHz(const unsigned long long i) noexcept { return KiloHertz32(static_cast<KiloHertz32::Base>(i)); }
/**
 * @param[in] i The number of mega hertz.
 * @return Returns the given frequency in one mega hertz resolution.
 */
[[nodiscard]] constexpr MegaHertz32 operator""_MHz(const unsigned long long i) noexcept { return MegaHertz32(static_cast<MegaHertz32::Base>(i)); }
}  // namespace frequency32_literal

/**
 * @namespace catta::physics::frequency16_literal Holds 16 bit frequency literals.
 */
namespace frequency16_literal
{
/**
 * @param[in] i The number of nano hertz.
 * @return Returns the given frequency in one nano hertz resolution.
 */
[[nodiscard]] constexpr NanoHertz16 operator""_nHz(const unsigned long long i) noexcept { return NanoHertz16(static_cast<NanoHertz16::Base>(i)); }
/**
 * @param[in] i The number of micro hertz.
 * @return Returns the given frequency in one micro hertz resolution.
 */
[[nodiscard]] constexpr MicroHertz16 operator""_uHz(const unsigned long long i) noexcept { return MicroHertz16(static_cast<MicroHertz16::Base>(i)); }
/**
 * @param[in] i The number of milli hertz.
 * @return Returns the given frequency in one milli hertz resolution.
 */
[[nodiscard]] constexpr MilliHertz16 operator""_mHz(const unsigned long long i) noexcept { return MilliHertz16(static_cast<MilliHertz16::Base>(i)); }
/**
 * @param[in] i The number of hertz.
 * @return Returns the given frequency in one hertz resolution.
 */
[[nodiscard]] constexpr Hertz16 operator""_Hz(const unsigned long long i) noexcept { return Hertz16(static_cast<Hertz16::Base>(i)); }
/**
 * @param[in] i The number of kilo hertz.
 * @return Returns the given frequency in one kilo hertz resolution.
 */
[[nodiscard]] constexpr KiloHertz16 operator""_kHz(const unsigned long long i) noexcept { return KiloHertz16(static_cast<KiloHertz16::Base>(i)); }
/**
 * @param[in] i The number of mega hertz.
 * @return Returns the given frequency in one mega hertz resolution.
 */
[[nodiscard]] constexpr MegaHertz16 operator""_MHz(const unsigned long long i) noexcept { return MegaHertz16(static_cast<MegaHertz16::Base>(i)); }
}  // namespace frequency16_literal
}  // namespace physics
}  // namespace catta
