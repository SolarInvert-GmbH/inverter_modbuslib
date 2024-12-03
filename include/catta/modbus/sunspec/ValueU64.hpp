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
 * @brief Class for representing unsigned 64 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ValueU64
{
  public:
    /**
     * Default constructor. Creates invalid unsigned 64 bit number.
     */
    constexpr ValueU64() noexcept : ValueU64(0x0000'0000, true) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ValueU64 empty() noexcept { return ValueU64{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the unsigned value.
     * @return Returns unsigned 64 bit number.
     */
    static constexpr ValueU64 create(const std::uint64_t value) { return ValueU64(value, false); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr std::uint64_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueU64.
     * @return Returns @b true if the two ValueU64 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueU64& other) const noexcept = default;

  private:
    constexpr ValueU64(std::uint64_t value, const bool empty) : _value(value), _empty(empty) {}
    std::uint64_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
