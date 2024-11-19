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
 * @brief Class for representing signed 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ValueS16
{
  public:
    /**
     * Default constructor. Creates invalid signed 16 bit number.
     */
    constexpr ValueS16() noexcept : ValueS16(0x0000, true) {}
    /**
     * @return Returns invalid scaled signed value.
     */
    constexpr static ValueS16 empty() noexcept { return ValueS16{}; }
    /**
     *  @return Returns @b true if scaled signed value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the signed value.
     * @return Returns signed 16 bit number.
     */
    static constexpr ValueS16 create(const std::int16_t value) { return ValueS16(value, false); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    std::int16_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueS16.
     * @return Returns @b true if the two ValueS16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueS16& other) const noexcept = default;

  private:
    constexpr ValueS16(std::int16_t value, const bool empty) : _value(value), _empty(empty) {}
    std::int16_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
