#pragma once

// sunspec
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
namespace model
{
/**
 * @brief Class for representing the immediate controls block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ImmediateControls
{
  public:
    /**
     * Default constructor. Creates invalid immediate controls block.
     */
    constexpr ImmediateControls() noexcept
        : ImmediateControls(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                            catta::modbus::sunspec::ValueU16::empty())
    {
    }
    /**
     * @return Returns invalid immediate controls block.
     */
    constexpr static ImmediateControls empty() noexcept { return ImmediateControls{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _timeoutConnection.isEmpty(); }
    /**
     * @param[in] timeoutConnection Timeout period for connect/disconnect. Has to be valid, otherwise empty is returned.
     * @param[in] connectionControl Enumerated valued. Connection control. Has to be valid, otherwise empty is returned.
     * @param[in] powerLimit Set power output to specified level. Has to be valid, otherwise empty is returned.
     * @return Returns immediate controls block. if input is valid, otherwise empty.
     */
    static constexpr ImmediateControls create(const catta::modbus::sunspec::ValueU16 timeoutConnection,
                                              const catta::modbus::sunspec::ValueU16 connectionControl,
                                              const catta::modbus::sunspec::ValueU16 powerLimit)
    {
        return timeoutConnection.isEmpty() || connectionControl.isEmpty() || powerLimit.isEmpty()
                   ? empty()
                   : ImmediateControls(timeoutConnection, connectionControl, powerLimit);
    }
    /**
     * @return Returns the Value of the Timeout period for connect/disconnect. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 timeoutConnection() const noexcept { return _timeoutConnection; }
    /**
     * @return Returns the Enumerated valued.  Connection control. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 connectionControl() const noexcept { return _connectionControl; }
    /**
     * @return Returns the Set power output to specified level. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 powerLimit() const noexcept { return _powerLimit; }
    /**
     * @param[in] other The other ImmediateControls.
     * @return Returns @b true if the two ImmediateControls objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ImmediateControls& other) const noexcept = default;

  private:
    constexpr ImmediateControls(const catta::modbus::sunspec::ValueU16 timeoutConnection, const catta::modbus::sunspec::ValueU16 connectionControl,
                                const catta::modbus::sunspec::ValueU16 powerLimit)
        : _timeoutConnection(timeoutConnection), _connectionControl(connectionControl), _powerLimit(powerLimit)
    {
    }
    catta::modbus::sunspec::ValueU16 _timeoutConnection;
    catta::modbus::sunspec::ValueU16 _connectionControl;
    catta::modbus::sunspec::ValueU16 _powerLimit;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
