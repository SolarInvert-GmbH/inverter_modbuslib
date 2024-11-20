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
 * @brief Class for representing the storage controls block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class Storage
{
  public:
    /**
     * Default constructor. Creates invalid storage block.
     */
    constexpr Storage() noexcept : Storage(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty()) {}
    /**
     * @return Returns invalid storage block.
     */
    constexpr static Storage empty() noexcept { return Storage{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _wChaMax.isEmpty(); }
    /**
     * @param[in] wChaMax Setpoint for maximum charge. Has to be valid, otherwise empty is returned.
     * @param[in] wChaRate Setpoint for maximum charging rate. Default is MaxChaRte. Has to be valid, otherwise empty is returned.
     * @return Returns storage controls block. if input is valid, otherwise empty.
     */
    static constexpr Storage create(const catta::modbus::sunspec::ValueU16 wChaMax, const catta::modbus::sunspec::ValueU16 wChaRate)
    {
        return wChaMax.isEmpty() || wChaRate.isEmpty() ? empty() : Storage(wChaMax, wChaRate);
    }
    /**
     * @return Returns the Setpoint for maximum charge. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 wChaMax() const noexcept { return _wChaMax; }
    /**
     * @return Returns the Setpoint for maximum charging rate. Default is MaxChaRte. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 wChaRate() const noexcept { return _wChaRate; }
    /**
     * @param[in] other The other Storage.
     * @return Returns @b true if the two Storage objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Storage& other) const noexcept = default;

  private:
    constexpr Storage(const catta::modbus::sunspec::ValueU16 wChaMax, const catta::modbus::sunspec::ValueU16 wChaRate)
        : _wChaMax(wChaMax), _wChaRate(wChaRate)
    {
    }
    catta::modbus::sunspec::ValueU16 _wChaMax;
    catta::modbus::sunspec::ValueU16 _wChaRate;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
