#pragma once

// request
#include <catta/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing the limit power feed in grid for batteryinvert device in mode 0 and 3 block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class LimitBatteryInvert
{
  public:
    /**
     * Default constructor. Creates invalid limit power feed in grid for batteryinvert device in mode 0 and 3 block.
     */
    constexpr LimitBatteryInvert() noexcept : LimitBatteryInvert(catta::modbus::sunspec::ValueU8<0, 100>::empty()) {}
    /**
     * @return Returns invalid LimitBatteryInvert block.
     */
    constexpr static LimitBatteryInvert empty() noexcept { return LimitBatteryInvert{}; }
    /**
     *  @return Returns @b true if _pMaxfeed is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _pMaxfeed.isEmpty(); }
    /**
     * @param[in] pMaxfeed Config the limit power feed in grid for batteryinvert device in mode 0 and 3. Has to be valid, otherwise empty is returned.
     * @return Returns LimitBatteryInvert controls block. if input is valid, otherwise empty.
     */
    static constexpr LimitBatteryInvert create(const catta::modbus::sunspec::ValueU8<0, 100> pMaxfeed)
    {
        return pMaxfeed.isEmpty() ? empty() : LimitBatteryInvert(pMaxfeed);
    }
    /**
     * @return Returns the limit power feed in grid for batteryinvert device in mode 0 and 3 config. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<0, 100> pMaxfeed() const noexcept { return _pMaxfeed; }
    /**
     * @param[in] other The other LimitBatteryInvert.
     * @return Returns @b true if the two LimitBatteryInvert objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const LimitBatteryInvert& other) const noexcept = default;

  private:
    constexpr LimitBatteryInvert(const catta::modbus::sunspec::ValueU8<0, 100> pMaxfeed) : _pMaxfeed(pMaxfeed) {}
    catta::modbus::sunspec::ValueU8<0, 100> _pMaxfeed;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
