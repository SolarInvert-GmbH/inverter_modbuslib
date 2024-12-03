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
 * @brief Class for representing unsigned 32 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ValueU32
{
  public:
    /**
     * Default constructor. Creates invalid unsigned 32 bit number.
     */
    constexpr ValueU32() noexcept : ValueU32(0x0000'0000, true) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ValueU32 empty() noexcept { return ValueU32{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the unsigned value.
     * @return Returns unsigned 32 bit number.
     */
    static constexpr ValueU32 create(const std::uint32_t value) { return ValueU32(value, false); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr std::uint32_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueU32.
     * @return Returns @b true if the two ValueU32 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueU32& other) const noexcept = default;

  private:
    constexpr ValueU32(std::uint32_t value, const bool empty) : _value(value), _empty(empty) {}
    std::uint32_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
