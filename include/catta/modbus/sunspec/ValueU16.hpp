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
 * @brief Class for representing unsigned 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ValueU16
{
  public:
    /**
     * Default constructor. Creates invalid unsigned 16 bit number.
     */
    constexpr ValueU16() noexcept : ValueU16(0x0000, true) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ValueU16 empty() noexcept { return ValueU16{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the unsigned value.
     * @return Returns unsigned 16 bit number.
     */
    static constexpr ValueU16 create(const std::uint16_t value) { return ValueU16(value, false); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr std::uint16_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueU16.
     * @return Returns @b true if the two ValueU16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueU16& other) const noexcept = default;

  private:
    constexpr ValueU16(std::uint16_t value, const bool empty) : _value(value), _empty(empty) {}
    std::uint16_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
