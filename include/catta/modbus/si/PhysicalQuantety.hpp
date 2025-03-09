#pragma once

// std
#include <cmath>
#include <cstdint>
#include <limits>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Class for representing physical quantety with unit.
 * @tparam UNIT The unit as c string.
 *
 * @author CattaTech - Maik Urbannek
 */
template <const char* UNIT>
class PhysicalQuantety
{
  public:
    /**
     * The unit as c string.
     */
    static constexpr const char* unit = UNIT;
    /**
     * Default Constructor. Returns empty physical quantety.
     */
    constexpr PhysicalQuantety() noexcept : PhysicalQuantety(EMPTY) {}
    /**
     * @return Returns invalid physical quantety.
     */
    constexpr static PhysicalQuantety empty() noexcept { return PhysicalQuantety{}; }
    /**
     * @param[in] quantety The quantety. Has to be a number, otherwise empty is returned.
     * @return Returns date if input is valid, otherwise empty.
     */
    static constexpr PhysicalQuantety create(const double quantety) { return std::isnan(quantety) ? empty() : PhysicalQuantety(quantety); }
    /**
     * @return Returns the quantety. Only valid if not empty.
     */
    constexpr double quantety() const noexcept { return _quantety; }
    /**
     * @return Returns @b true if physical quantety is valid, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return std::isnan(_quantety); }
    /**
     * @param[in] other The other PhysicalQuantety.
     * @return Returns @b true if the two PhysicalQuantety objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const PhysicalQuantety& other) const noexcept
    {
        if (this->isEmpty() && other.isEmpty()) return true;
        const double r = this->_quantety > other._quantety ? this->_quantety - other._quantety : other._quantety - this->_quantety;
        return r < epsilon;
    }

  private:
    constexpr PhysicalQuantety(const double quantety) noexcept : _quantety(quantety) {}
    double _quantety;
    static constexpr double EMPTY = std::numeric_limits<double>::quiet_NaN();
    static constexpr double epsilon = 0.00000'009;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
