#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for representing two scaled unsigned 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledValue2U16
{
  public:
    /**
     * Default constructor. Creates invalid two scaled unsigned 16 bit numbers.
     */
    constexpr ScaledValue2U16() noexcept
        : ScaledValue2U16(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                          catta::modbus::sunspec::ScaleFactor::empty())
    {
    }
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ScaledValue2U16 empty() noexcept { return ScaledValue2U16{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _scale.isEmpty(); }
    /**
     * @param[in] min Representing the unsigned value for min. Has to be valid, otherwise empty is returned.
     * @param[in] max Representing the unsigned value for max. Has to be valid, otherwise empty is returned.
     * @param[in] scale Representing the scale. Has to be valid, otherwise empty is returned.
     * @return Returns two scaled unsigned 16 bit numbers if input is valid, otherwise empty.
     */
    static constexpr ScaledValue2U16 create(const catta::modbus::sunspec::ValueU16 min, const catta::modbus::sunspec::ValueU16 max,
                                            const catta::modbus::sunspec::ScaleFactor scale)
    {
        return min.isEmpty() || max.isEmpty() || scale.isEmpty() ? empty() : ScaledValue2U16(min, max, scale);
    }
    /**
     * @return Returns the value for min. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 min() const noexcept { return _min; }
    /**
     * @return Returns the value for max. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 max() const noexcept { return _max; }
    /**
     * @return Returns the scale. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaleFactor scale() const noexcept { return _scale; }
    /**
     * @param[in] other The other ScaledValue2U16.
     * @return Returns @b true if the two ScaledValue2U16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledValue2U16& other) const noexcept = default;

  private:
    constexpr ScaledValue2U16(const catta::modbus::sunspec::ValueU16 min, const catta::modbus::sunspec::ValueU16 max,
                              const catta::modbus::sunspec::ScaleFactor scale)
        : _min(min), _max(max), _scale(scale)
    {
    }
    catta::modbus::sunspec::ValueU16 _min;
    catta::modbus::sunspec::ValueU16 _max;
    catta::modbus::sunspec::ScaleFactor _scale;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
