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
 * @brief Class for representing signed 32 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ValueS32
{
  public:
    /**
     * Default constructor. Creates invalid signed 32 bit number.
     */
    constexpr ValueS32() noexcept : ValueS32(0x00000000, true) {}
    /**
     * @return Returns invalid scaled signed value.
     */
    constexpr static ValueS32 empty() noexcept { return ValueS32{}; }
    /**
     *  @return Returns @b true if scaled signed value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty == true; }
    /**
     * @param[in] value Representing the signed value.
     * @return Returns signed 32 bit number.
     */
    static constexpr ValueS32 create(const std::int32_t value) { return ValueS32(value, false); }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr std::int32_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ValueS32.
     * @return Returns @b true if the two ValueS32 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ValueS32& other) const noexcept = default;

  private:
    constexpr ValueS32(std::int32_t value, const bool empty) : _value(value), _empty(empty) {}
    std::int32_t _value;
    bool _empty;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
