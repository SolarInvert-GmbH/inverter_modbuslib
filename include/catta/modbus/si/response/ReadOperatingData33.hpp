#pragma once

// response
#include <catta/modbus/si/State.hpp>
#include <catta/modbus/sunspec/ValueS16.hpp>
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
 * @brief Class for representing the read operating data 0x33 block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ReadOperatingData33
{
  public:
    /**
     * Default constructor. Creates invalid read operating data 0x33 block.
     */
    constexpr ReadOperatingData33() noexcept
        : ReadOperatingData33(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU8<0, 255>::empty(),
                              catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueS16::empty(), catta::modbus::si::State::empty())
    {
    }
    /**
     * @return Returns invalid read operating data 0x33 block.
     */
    constexpr static ReadOperatingData33 empty() noexcept { return ReadOperatingData33{}; }
    /**
     *  @return Returns @b true if read operating data 0x33 is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _dcVoltage.isEmpty(); }
    /**
     * @param[in] dcVoltage Voltage on dc side of the device. Has to be valid, otherwise empty is returned.
     * @param[in] acVoltage Grid voltage. Has to be valid, otherwise empty is returned.
     * @param[in] gridFrequency Grid frequency Has to be valid, otherwise empty is returned.
     * @param[in] acPower Power output of the device. Has to be valid, otherwise empty is returned.
     * @param[in] state State of the device (00: Init level 1, 01: Init level 2 ,02: Init level 3 ,03: MPPT ,04: Reset ,05: Konstantspng. ,06: Low
     * Power ,Mode ,07: Wind ,08: Factory Mode ,09: Battery ,10: Battery Safety). Has to be valid, otherwise empty is returned.
     * @return Returns ReadOperatingData33 controls block. if input is valid, otherwise empty.
     */
    static constexpr ReadOperatingData33 create(const catta::modbus::sunspec::ValueU16 dcVoltage,
                                                const catta::modbus::sunspec::ValueU8<0, 255> acVoltage,
                                                const catta::modbus::sunspec::ValueU16 gridFrequency, const catta::modbus::sunspec::ValueS16 acPower,
                                                const catta::modbus::si::State state)
    {
        return dcVoltage.isEmpty() || acVoltage.isEmpty() || gridFrequency.isEmpty() || acPower.isEmpty() || state.isEmpty()
                   ? empty()
                   : ReadOperatingData33(dcVoltage, acVoltage, gridFrequency, acPower, state);
    }
    /**
     * @return Returns the voltage on dc side of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 dcVoltage() const noexcept { return _dcVoltage; }
    /**
     * @return Returns the grid voltage. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU8<0, 255> acVoltage() const noexcept { return _acVoltage; }
    /**
     * @return Returns the grid frequency. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 gridFrequency() const noexcept { return _gridFrequency; }
    /**
     * @return Returns the power output of the device. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueS16 acPower() const noexcept { return _acPower; }
    /**
     * @return Returns the state of the device (00: Init level 1, 01: Init level 2 ,02: Init level 3 ,03: MPPT ,04: Reset ,05: Konstantspng. ,06: Low
     * Power ,Mode ,07: Wind ,08: Factory Mode ,09: Battery ,10: Battery Safety). Is only valid if not empty.
     */
    constexpr catta::modbus::si::State state() const noexcept { return _state; }
    /**
     * @param[in] other The other ReadOperatingData33.
     * @return Returns @b true if the two ReadOperatingData33 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ReadOperatingData33& other) const noexcept = default;

  private:
    constexpr ReadOperatingData33(const catta::modbus::sunspec::ValueU16 dcVoltage, const catta::modbus::sunspec::ValueU8<0, 255> acVoltage,
                                  const catta::modbus::sunspec::ValueU16 gridFrequency, const catta::modbus::sunspec::ValueS16 acPower,
                                  catta::modbus::si::State state)
        : _dcVoltage(dcVoltage), _acVoltage(acVoltage), _gridFrequency(gridFrequency), _acPower(acPower), _state(state)
    {
    }
    catta::modbus::sunspec::ValueU16 _dcVoltage;
    catta::modbus::sunspec::ValueU8<0, 255> _acVoltage;
    catta::modbus::sunspec::ValueU16 _gridFrequency;
    catta::modbus::sunspec::ValueS16 _acPower;
    catta::modbus::si::State _state;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
