#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>
#include <catta/modbus/sunspec/ValueU32.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for representing scaled unsigned 32 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledValueU32
{
  public:
    /**
     * Default constructor. Creates invalid scaled unsigned 32 bit numbers.
     */
    constexpr ScaledValueU32() noexcept : ScaledValueU32(catta::modbus::sunspec::ValueU32::empty(), catta::modbus::sunspec::ScaleFactor::empty()) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ScaledValueU32 empty() noexcept { return ScaledValueU32{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _value.isEmpty(); }
    /**
     * @param[in] value Representing the unsigned value. Has to be valid, otherwise empty is returned.
     * @param[in] scale Representing the scale. Has to be valid, otherwise empty is returned.
     * @return Returns scaled unsigned 32 bit numbers if input is valid, otherwise empty.
     */
    static constexpr ScaledValueU32 create(const catta::modbus::sunspec::ValueU32 value, const catta::modbus::sunspec::ScaleFactor scale)
    {
        return value.isEmpty() || scale.isEmpty() ? empty() : ScaledValueU32(value, scale);
    }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU32 value() const noexcept { return _value; }
    /**
     * @return Returns the scale. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaleFactor scale() const noexcept { return _scale; }
    /**
     * @param[in] other The other ScaledValueU32.
     * @return Returns @b true if the two ScaledValueU32 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledValueU32& other) const noexcept = default;

  private:
    constexpr ScaledValueU32(const catta::modbus::sunspec::ValueU32 value, const catta::modbus::sunspec::ScaleFactor scale)
        : _value(value), _scale(scale)
    {
    }
    catta::modbus::sunspec::ValueU32 _value;
    catta::modbus::sunspec::ScaleFactor _scale;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
