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
 * @tparam MIN Minimum posible std::uint8_t.
 * @tparam MAX Maximum posible std::uint8_t.
 * @brief Class for representing unsigned 8 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
template <std::uint8_t MIN, std::uint8_t MAX>
class ValueU8
{
    static_assert(MIN < MAX);

  public:
    /**
     * Default constructor. Creates invalid unsigned 8 bit number.
     */
    constexpr ValueU8() noexcept : ValueU8(0x00, true) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ValueU8 empty() noexcept { return ValueU8{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the unsigned value. Has to be in [MIN…MAX], otherwise empty is returned.
     * @return Returns unsigned 8 bit number if input is valid, otherwise empty.
     */
    static constexpr ValueU8 create(const std::uint8_t value) { return MIN <= value && MAX >= value ? ValueU8(value, false) : empty(); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr std::uint8_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueU8.
     * @return Returns @b true if the two ValueU8 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueU8& other) const noexcept = default;

  private:
    constexpr ValueU8(std::uint8_t value, const bool empty) : _value(value), _empty(empty) {}
    std::uint8_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
