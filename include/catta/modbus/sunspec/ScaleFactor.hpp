#pragma once

// std
#include <cstdint>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for represening power of 10 to scale unit.
 *
 * Is represented by the exponent. Valid exponents reach from -10…10. Represening 10^-10 … 10^10.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaleFactor
{
  public:
    /**
     * Default constructor. Creates invalid scale factor.
     */
    constexpr ScaleFactor() noexcept : ScaleFactor(EMPTY) {}
    /**
     * @return Returns invalid scale factor.
     */
    constexpr static ScaleFactor empty() noexcept { return ScaleFactor{}; }
    /**
     *  @return Returns @b true if scale factor is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _factorExponent < MIN || _factorExponent > MAX; }
    /**
     * @param[in] factorExponent Represening the exponent of the scaling factor. Has to be beetween -10 and 10, otherwise empty is returned.
     */
    static constexpr ScaleFactor create(const std::int8_t factorExponent)
    {
        return factorExponent >= MIN && factorExponent <= MAX ? ScaleFactor(factorExponent) : empty();
    }
    /**
     * @return Returns the factor exponent. Is only valid if not empty.
     */
    std::int8_t factorExponent() const noexcept { return _factorExponent; }
    /**
     * @param[in] other The other ScaleFactor.
     * @return Returns @b true if the two ScaleFactor objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaleFactor& other) const noexcept = default;

  private:
    constexpr ScaleFactor(std::int8_t factorExponent) : _factorExponent(factorExponent) {}
    std::int8_t _factorExponent;
    static constexpr std::int8_t MIN = -10;
    static constexpr std::int8_t MAX = +10;
    static constexpr std::int8_t EMPTY = MAX + 1;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
