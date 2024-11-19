#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaledValue3U16.hpp>
#include <catta/modbus/sunspec/ScaledValue4U16.hpp>
#include <catta/modbus/sunspec/ScaledValueS16.hpp>
#include <catta/modbus/sunspec/ScaledValueU16.hpp>
#include <catta/modbus/sunspec/ScaledValueU32.hpp>

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
 * @author CattaTech - Lars Joachimsthaler
 */
class Inverter
{
  public:
    /**
     * Default constructor. Creates invalid common block.
     */
    constexpr Inverter() noexcept
        : Inverter(catta::modbus::sunspec::ScaledValue4U16::empty(), catta::modbus::sunspec::ScaledValue3U16::empty(),
                   catta::modbus::sunspec::ScaledValueS16::empty(), catta::modbus::sunspec::ScaledValueU16::empty(),
                   catta::modbus::sunspec::ScaledValueS16::empty(), catta::modbus::sunspec::ScaledValueU32::empty(),
                   catta::modbus::sunspec::ScaledValueU16::empty(), catta::modbus::sunspec::ScaledValueS16::empty())
    {
    }
    /**
     * @return Returns invalid common block.
     */
    constexpr static Inverter empty() noexcept { return Inverter{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _ampere.isEmpty(); }
    /**
     * @param[in] ampere The modbus device AC Current on 3 Phases. Has to be valid, otherwise empty is returned.
     * @param[in] voltage The modbus device AC Voltage on 3 Phases. Has to be valid, otherwise empty is returned.
     * @param[in] watt The modbus device AC Power. Has to be valid, otherwise empty is returned.
     * @param[in] hertz The modbus device Line Frequency. Has to be valid, otherwise empty is returned.
     * @param[in] powerFactor The modbus device AC Power Factor. Has to be valid, otherwise empty is returned.
     * @param[in] wattHours The modbus device AC Energy. Has to be valid, otherwise empty is returned.
     * @param[in] dcVoltage The modbus device DC Voltage. Has to be valid, otherwise empty is returned.
     * @param[in] cabinetTemperature The modbus device Cabinet Temperature. Has to be valid, otherwise empty is returned.
     * @return Returns common block if input is valid, otherwise empty.
     */
    static constexpr Inverter create(const catta::modbus::sunspec::ScaledValue4U16 ampere, const catta::modbus::sunspec::ScaledValue3U16 voltage,
                                     const catta::modbus::sunspec::ScaledValueS16 watt, const catta::modbus::sunspec::ScaledValueU16 hertz,
                                     const catta::modbus::sunspec::ScaledValueS16 powerFactor, const catta::modbus::sunspec::ScaledValueU32 wattHours,
                                     const catta::modbus::sunspec::ScaledValueU16 dcVoltage,
                                     const catta::modbus::sunspec::ScaledValueS16 cabinetTemperature)
    {
        return ampere.isEmpty() || voltage.isEmpty() || watt.isEmpty() || hertz.isEmpty() || powerFactor.isEmpty() || wattHours.isEmpty() ||
                       dcVoltage.isEmpty() || cabinetTemperature.isEmpty()
                   ? empty()
                   : Inverter(ampere, voltage, watt, hertz, powerFactor, wattHours, dcVoltage, cabinetTemperature);
    }
    /**
     * @return Returns the AC Current. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValue4U16 ampere() const noexcept { return _ampere; }
    /**
     * @return Returns the Voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValue3U16 voltage() const noexcept { return _voltage; }
    /**
     * @return Returns the AC Power. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueS16 watt() const noexcept { return _watt; }
    /**
     * @return Returns the Line Frequency. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 hertz() const noexcept { return _hertz; }
    /**
     * @return Returns the AC Power Factor. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueS16 powerFactor() const noexcept { return _powerFactor; }
    /**
     * @return Returns the AC Energy. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU32 wattHours() const noexcept { return _wattHours; }
    /**
     * @return Returns the DC Voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 dcVoltage() const noexcept { return _dcVoltage; }
    /**
     * @return Returns the Cabinet Temperature. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueS16 cabinetTemperature() const noexcept { return _cabinetTemperature; }
    /**
     * @param[in] other The other Inverter.
     * @return Returns @b true if the two Inverter objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Inverter& other) const noexcept = default;

  private:
    constexpr Inverter(const catta::modbus::sunspec::ScaledValue4U16 ampere, const catta::modbus::sunspec::ScaledValue3U16 voltage,
                       const catta::modbus::sunspec::ScaledValueS16 watt, const catta::modbus::sunspec::ScaledValueU16 hertz,
                       const catta::modbus::sunspec::ScaledValueS16 powerFactor, const catta::modbus::sunspec::ScaledValueU32 wattHours,
                       const catta::modbus::sunspec::ScaledValueU16 dcVoltage, const catta::modbus::sunspec::ScaledValueS16 cabinetTemperature)
        : _ampere(ampere),
          _voltage(voltage),
          _watt(watt),
          _hertz(hertz),
          _powerFactor(powerFactor),
          _wattHours(wattHours),
          _dcVoltage(dcVoltage),
          _cabinetTemperature(cabinetTemperature)
    {
    }
    catta::modbus::sunspec::ScaledValue4U16 _ampere;
    catta::modbus::sunspec::ScaledValue3U16 _voltage;
    catta::modbus::sunspec::ScaledValueS16 _watt;
    catta::modbus::sunspec::ScaledValueU16 _hertz;
    catta::modbus::sunspec::ScaledValueS16 _powerFactor;
    catta::modbus::sunspec::ScaledValueU32 _wattHours;
    catta::modbus::sunspec::ScaledValueU16 _dcVoltage;
    catta::modbus::sunspec::ScaledValueS16 _cabinetTemperature;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
