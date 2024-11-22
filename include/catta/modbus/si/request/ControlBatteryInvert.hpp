#pragma once

// request
#include <catta/modbus/si/PowerConfig.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing the control/limiting the power of the batteryInvert in Mode 0 and 3 block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ControlBatteryInvert
{
  public:
    /**
     * Default constructor. Creates invalid control/limiting the power of the batteryInvert in Mode 0 and 3 block.
     */
    constexpr ControlBatteryInvert() noexcept
        : ControlBatteryInvert(catta::modbus::si::PowerConfig::empty(), catta::modbus::sunspec::ValueU16::empty(),
                               catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty())
    {
    }
    /**
     * @return Returns invalid control/limiting the power of the batteryInvert in Mode 0 and 3 block.
     */
    constexpr static ControlBatteryInvert empty() noexcept { return ControlBatteryInvert{}; }
    /**
     *  @return Returns @b true if control/limiting the power of the batteryInvert in Mode 0 and 3 is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _pMax.isEmpty(); }
    /**
     * @param[in] pMax Config the max power Output. Has to be valid, otherwise empty is returned.
     * @param[in] uMin Config minimal dc voltage. Has to be valid, otherwise empty is returned.
     * @param[in] uMax Config maximal dc voltage. Has to be valid, otherwise empty is returned.
     * @param[in] timeout Config the timeout in seconds. Has to be valid, otherwise empty is returned.
     * @return Returns ControlBatteryInvert controls block. if input is valid, otherwise empty.
     */
    static constexpr ControlBatteryInvert create(const catta::modbus::si::PowerConfig pMax, const catta::modbus::sunspec::ValueU16 uMin,
                                                 const catta::modbus::sunspec::ValueU16 uMax, const catta::modbus::sunspec::ValueU16 timeout)
    {
        return pMax.isEmpty() || uMin.isEmpty() || uMax.isEmpty() || timeout.isEmpty() ? empty() : ControlBatteryInvert(pMax, uMin, uMax, timeout);
    }
    /**
     * @return Returns the power output config. Is only valid if not empty.
     */
    catta::modbus::si::PowerConfig pMax() const noexcept { return _pMax; }
    /**
     * @return Returns the minimal dc voltage config. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 uMin() const noexcept { return _uMin; }
    /**
     * @return Returns the maximal dc voltage config. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 uMax() const noexcept { return _uMax; }
    /**
     * @return Returns the timeoutconfig in seconds. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 timeout() const noexcept { return _timeout; }
    /**
     * @param[in] other The other ControlBatteryInvert.
     * @return Returns @b true if the two ControlBatteryInvert objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ControlBatteryInvert& other) const noexcept = default;

  private:
    constexpr ControlBatteryInvert(const catta::modbus::si::PowerConfig pMax, const catta::modbus::sunspec::ValueU16 uMin,
                                   const catta::modbus::sunspec::ValueU16 uMax, const catta::modbus::sunspec::ValueU16 timeout)
        : _pMax(pMax), _uMin(uMin), _uMax(uMax), _timeout(timeout)
    {
    }
    catta::modbus::si::PowerConfig _pMax;
    catta::modbus::sunspec::ValueU16 _uMin;
    catta::modbus::sunspec::ValueU16 _uMax;
    catta::modbus::sunspec::ValueU16 _timeout;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
