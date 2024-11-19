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
 * @brief Class for representing scaled unsigned 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledValueU16
{
  public:
    /**
     * Default constructor. Creates invalid scaled unsigned 16 bit numbers.
     */
    constexpr ScaledValueU16() noexcept : ScaledValueU16(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ScaleFactor::empty()) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ScaledValueU16 empty() noexcept { return ScaledValueU16{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _value.isEmpty(); }
    /**
     * @param[in] value Representing the unsigned value. Has to be valid, otherwise empty is returned.
     * @param[in] scale Representing the scale. Has to be valid, otherwise empty is returned.
     * @return Returns scaled unsigned 16 bit numbers if input is valid, otherwise empty.
     */
    static constexpr ScaledValueU16 create(const catta::modbus::sunspec::ValueU16 value, const catta::modbus::sunspec::ScaleFactor scale)
    {
        return value.isEmpty() || scale.isEmpty() ? empty() : ScaledValueU16(value, scale);
    }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 value() const noexcept { return _value; }
    /**
     * @return Returns the scale. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaleFactor scale() const noexcept { return _scale; }
    /**
     * @param[in] other The other ScaledValueU16.
     * @return Returns @b true if the two ScaledValueU16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledValueU16& other) const noexcept = default;

  private:
    constexpr ScaledValueU16(const catta::modbus::sunspec::ValueU16 value, const catta::modbus::sunspec::ScaleFactor scale)
        : _value(value), _scale(scale)
    {
    }
    catta::modbus::sunspec::ValueU16 _value;
    catta::modbus::sunspec::ScaleFactor _scale;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
