#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>
#include <catta/modbus/sunspec/ValueS16.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for representing scaled signed 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledValueS16
{
  public:
    /**
     * Default constructor. Creates invalid scaled signed 16 bit numbers.
     */
    constexpr ScaledValueS16() noexcept : ScaledValueS16(catta::modbus::sunspec::ValueS16::empty(), catta::modbus::sunspec::ScaleFactor::empty()) {}
    /**
     * @return Returns invalid scaled signed value.
     */
    constexpr static ScaledValueS16 empty() noexcept { return ScaledValueS16{}; }
    /**
     *  @return Returns @b true if scaled signed value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _value.isEmpty(); }
    /**
     * @param[in] value Representing the signed value. Has to be valid, otherwise empty is returned.
     * @param[in] scale Representing the scale. Has to be valid, otherwise empty is returned.
     * @return Returns scaled signed 16 bit numbers if input is valid, otherwise empty.
     */
    static constexpr ScaledValueS16 create(const catta::modbus::sunspec::ValueS16 value, const catta::modbus::sunspec::ScaleFactor scale)
    {
        return value.isEmpty() || scale.isEmpty() ? empty() : ScaledValueS16(value, scale);
    }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueS16 value() const noexcept { return _value; }
    /**
     * @return Returns the scale. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaleFactor scale() const noexcept { return _scale; }
    /**
     * @param[in] other The other ScaledValueS16.
     * @return Returns @b true if the two ScaledValueS16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledValueS16& other) const noexcept = default;

  private:
    constexpr ScaledValueS16(const catta::modbus::sunspec::ValueS16 value, const catta::modbus::sunspec::ScaleFactor scale)
        : _value(value), _scale(scale)
    {
    }
    catta::modbus::sunspec::ValueS16 _value;
    catta::modbus::sunspec::ScaleFactor _scale;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
