#pragma once

// std
#include <cstdint>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing a small request.
 *
 * @author CattaTech - Maik Urbannek
 */
class Small
{
  public:
    /**
     * Default constructor. Creates invalid small request.
     */
    constexpr Small() noexcept : Small(EMPTY) {}
    /**
     * @return Returns invalid small request.
     */
    constexpr static Small empty() noexcept { return Small{}; }
    /**
     *  @return Returns @b true if small request is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _function == EMPTY; }
    /**
     * @param[in] function The function code. Has to be not 0x00, otherwise empty is returned.
     * @return Returns small request if input is valid, otherwise empty.
     */
    static constexpr Small create(const std::uint8_t function) { return Small(function); }
    /**
     * @return Returns function code. Is only valid if not empty.
     */
    constexpr std::uint8_t function() const noexcept { return _function; }
    /**
     * @param[in] other The other Small.
     * @return Returns @b true if the two Small objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Small& other) const noexcept = default;

  private:
    constexpr Small(const std::uint8_t function) : _function(function) {}
    std::uint8_t _function;
    static constexpr std::uint8_t EMPTY = 0x00;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
