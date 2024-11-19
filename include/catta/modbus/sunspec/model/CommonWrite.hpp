#pragma once

// sunspec
#include <catta/modbus/sunspec/String.hpp>
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
 * @brief Class for representing the common block for writing.
 *
 * @author CattaTech - Maik Urbannek
 */
class CommonWrite
{
  public:
    /**
     * Default constructor. Creates invalid common block.
     */
    constexpr CommonWrite() noexcept : CommonWrite(catta::modbus::sunspec::ValueU16::empty()) {}
    /**
     * @return Returns invalid common block.
     */
    constexpr static CommonWrite empty() noexcept { return CommonWrite{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _deviceAddress.isEmpty(); }
    /**
     * @param[in] deviceAddress The modbus device address. Has to be valid, otherwise empty is returned.
     * @return Returns common block if input is valid, otherwise empty.
     */
    static constexpr CommonWrite create(const catta::modbus::sunspec::ValueU16 deviceAddress)
    {
        return deviceAddress.isEmpty() ? empty() : CommonWrite(deviceAddress);
    }
    /**
     * @return Returns the modbus device address. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 deviceAddress() const noexcept { return _deviceAddress; }
    /**
     * @param[in] other The other CommonWrite.
     * @return Returns @b true if the two CommonWrite objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const CommonWrite& other) const noexcept = default;

  private:
    constexpr CommonWrite(const catta::modbus::sunspec::ValueU16 deviceAddress) : _deviceAddress(deviceAddress) {}
    catta::modbus::sunspec::ValueU16 _deviceAddress;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
