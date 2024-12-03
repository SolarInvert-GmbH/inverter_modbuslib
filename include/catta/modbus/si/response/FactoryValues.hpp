#pragma once

// response
#include <catta/modbus/si/Date.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>
#include <catta/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Class for representing the factory values block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class FactoryValues
{
  public:
    /**
     * Default constructor. Creates invalid factory values block.
     */
    constexpr FactoryValues() noexcept
        : FactoryValues(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::si::Date::empty(), catta::modbus::sunspec::ValueU8<0, 255>::empty(),
                        catta::modbus::sunspec::ValueU8<0, 255>::empty(), catta::modbus::sunspec::ValueU8<0, 255>::empty())
    {
    }
    /**
     * @return Returns invalid factory values block.
     */
    constexpr static FactoryValues empty() noexcept { return FactoryValues{}; }
    /**
     *  @return Returns @b true if factory values is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _serialnumber.isEmpty(); }
    /**
     * @param[in] serialnumber Serial number of the device. Has to be valid, otherwise empty is returned.
     * @param[in] productionDate Production date of the device. Has to be valid, otherwise empty is returned.
     * @param[in] hardwareVersion Hardware version of the device. Has to be valid, otherwise empty is returned.
     * @param[in] firmwareVersion Firmware version of the device. Has to be valid, otherwise empty is returned.
     * @param[in] bootstrappVersion Bootstrapper version of the device. Has to be valid, otherwise empty is returned.
     * @return Returns FactoryValues controls block. if input is valid, otherwise empty.
     */
    static constexpr FactoryValues create(const catta::modbus::sunspec::ValueU16 serialnumber, const catta::modbus::si::Date productionDate,
                                          const catta::modbus::sunspec::ValueU8<0, 255> hardwareVersion,
                                          const catta::modbus::sunspec::ValueU8<0, 255> firmwareVersion,
                                          const catta::modbus::sunspec::ValueU8<0, 255> bootstrappVersion)
    {
        return serialnumber.isEmpty() || productionDate.isEmpty() || hardwareVersion.isEmpty() || firmwareVersion.isEmpty() ||
                       bootstrappVersion.isEmpty()
                   ? empty()
                   : FactoryValues(serialnumber, productionDate, hardwareVersion, firmwareVersion, bootstrappVersion);
    }
    /**
     * @return Returns the serial number of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 serialnumber() const noexcept { return _serialnumber; }
    /**
     * @return Returns the production date of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::si::Date productionDate() const noexcept { return _productionDate; }
    /**
     * @return Returns the hardware version of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU8<0, 255> hardwareVersion() const noexcept { return _hardwareVersion; }
    /**
     * @return Returns the firmware version of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU8<0, 255> firmwareVersion() const noexcept { return _firmwareVersion; }
    /**
     * @return Returns the bootstrapper version of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU8<0, 255> bootstrappVersion() const noexcept { return _bootstrappVersion; }
    /**
     * @param[in] other The other FactoryValues.
     * @return Returns @b true if the two FactoryValues objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const FactoryValues& other) const noexcept = default;

  private:
    constexpr FactoryValues(const catta::modbus::sunspec::ValueU16 serialnumber, const catta::modbus::si::Date productionDate,
                            const catta::modbus::sunspec::ValueU8<0, 255> hardwareVersion,
                            const catta::modbus::sunspec::ValueU8<0, 255> firmwareVersion, catta::modbus::sunspec::ValueU8<0, 255> bootstrappVersion)
        : _serialnumber(serialnumber),
          _productionDate(productionDate),
          _hardwareVersion(hardwareVersion),
          _firmwareVersion(firmwareVersion),
          _bootstrappVersion(bootstrappVersion)
    {
    }
    catta::modbus::sunspec::ValueU16 _serialnumber;
    catta::modbus::si::Date _productionDate;
    catta::modbus::sunspec::ValueU8<0, 255> _hardwareVersion;
    catta::modbus::sunspec::ValueU8<0, 255> _firmwareVersion;
    catta::modbus::sunspec::ValueU8<0, 255> _bootstrappVersion;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
