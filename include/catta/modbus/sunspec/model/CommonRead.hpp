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
 * @brief Class for representing the common block for reading.
 *
 * @author CattaTech - Maik Urbannek
 */
class CommonRead
{
  public:
    /**
     * Default constructor. Creates invalid common block.
     */
    constexpr CommonRead() noexcept
        : CommonRead(catta::modbus::sunspec::String::empty(), catta::modbus::sunspec::String::empty(), catta::modbus::sunspec::String::empty(),
                     catta::modbus::sunspec::ValueU16::empty())
    {
    }
    /**
     * @return Returns invalid common block.
     */
    constexpr static CommonRead empty() noexcept { return CommonRead{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _manufacturer.isEmpty(); }
    /**
     * @param[in] manufacturer Name of the manufacturer. Has to be valid, otherwise empty is returned.
     * @param[in] model Name of the model. Has to be valid, otherwise empty is returned.
     * @param[in] serialNumber Serial number of the device. Has to be valid, otherwise empty is returned.
     * @param[in] deviceAddress The modbus device address. Has to be valid, otherwise empty is returned.
     * @return Returns common block if input is valid, otherwise empty.
     */
    static constexpr CommonRead create(const catta::modbus::sunspec::String manufacturer, const catta::modbus::sunspec::String model,
                                       const catta::modbus::sunspec::String serialNumber, const catta::modbus::sunspec::ValueU16 deviceAddress)
    {
        return manufacturer.isEmpty() || model.isEmpty() || serialNumber.isEmpty() || deviceAddress.isEmpty()
                   ? empty()
                   : CommonRead(manufacturer, model, serialNumber, deviceAddress);
    }
    /**
     * @return Returns the name of the manufacturer. Is only valid if not empty.
     */
    catta::modbus::sunspec::String manufacturer() const noexcept { return _manufacturer; }
    /**
     * @return Returns the model name. Is only valid if not empty.
     */
    catta::modbus::sunspec::String model() const noexcept { return _model; }
    /**
     * @return Returns the serial number. Is only valid if not empty.
     */
    catta::modbus::sunspec::String serialNumber() const noexcept { return _serialNumber; }
    /**
     * @return Returns the modbus device address. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 deviceAddress() const noexcept { return _deviceAddress; }
    /**
     * @param[in] other The other CommonRead.
     * @return Returns @b true if the two CommonRead objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const CommonRead& other) const noexcept = default;

  private:
    constexpr CommonRead(const catta::modbus::sunspec::String manufacturer, const catta::modbus::sunspec::String model,
                         const catta::modbus::sunspec::String serialNumber, const catta::modbus::sunspec::ValueU16 deviceAddress)
        : _manufacturer(manufacturer), _model(model), _serialNumber(serialNumber), _deviceAddress(deviceAddress)
    {
    }
    catta::modbus::sunspec::String _manufacturer;
    catta::modbus::sunspec::String _model;
    catta::modbus::sunspec::String _serialNumber;
    catta::modbus::sunspec::ValueU16 _deviceAddress;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
