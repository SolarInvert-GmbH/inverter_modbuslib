#pragma once

// sunspec
#include <catta/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/modbus/sunspec/ScaledValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
namespace model
{
/**
 * @brief Class for representing the basic settings controls block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class BasicSettingsRead
{
  public:
    /**
     * Default constructor. Creates invalid basic settings controls block.
     */
    constexpr BasicSettingsRead() noexcept
        : BasicSettingsRead(catta::modbus::sunspec::ScaledValueU16::empty(), catta::modbus::sunspec::ScaledValueU16::empty(),
                            catta::modbus::sunspec::ScaledValueU16::empty(), catta::modbus::sunspec::ScaledValueU16::empty(),
                            catta::modbus::sunspec::ConnectedPhase::empty())
    {
    }
    /**
     * @return Returns invalid basic settings controls block.
     */
    constexpr static BasicSettingsRead empty() noexcept { return BasicSettingsRead{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _wMax.isEmpty(); }
    /**
     * @param[in] wMax Setting for maximum power output. Has to be valid, otherwise empty is returned.
     * @param[in] vMax Setpoint for maximum voltage.. Has to be valid, otherwise empty is returned.
     * @param[in] vMin Setpoint for minimum voltage. Has to be valid, otherwise empty is returned.
     * @param[in] ecpNomHz Setpoint for nominal frequency at the ECP. Has to be valid, otherwise empty is returned.
     * @param[in] connPhase Identity of connected phase for single phase inverters. A=1 B=2 C=3.
     * @return Returns BasicSettingsRead controls block. if input is valid, otherwise empty.
     */
    static constexpr BasicSettingsRead create(const catta::modbus::sunspec::ScaledValueU16 wMax, const catta::modbus::sunspec::ScaledValueU16 vMax,
                                              const catta::modbus::sunspec::ScaledValueU16 vMin,
                                              const catta::modbus::sunspec::ScaledValueU16 ecpNomHz,
                                              const catta::modbus::sunspec::ConnectedPhase connPhase)
    {
        return wMax.isEmpty() || vMax.isEmpty() || vMin.isEmpty() || ecpNomHz.isEmpty() || connPhase.isEmpty()
                   ? empty()
                   : BasicSettingsRead(wMax, vMax, vMin, ecpNomHz, connPhase);
    }
    /**
     * @return Returns the Setting for maximum power output. Default to WRtg. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 wMax() const noexcept { return _wMax; }
    /**
     * @return Returns the Setpoint for maximum voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 vMax() const noexcept { return _vMax; }
    /**
     * @return Returns the Setpoint for minimum voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 vMin() const noexcept { return _vMin; }
    /**
     * @return Returns the Setpoint for nominal frequency at the ECP. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaledValueU16 ecpNomHz() const noexcept { return _ecpNomHz; }
    /**
     * @return Returns the Identity of connected phase for single phase inverters. A=1 B=2 C=3. Is only valid if not empty.
     */
    catta::modbus::sunspec::ConnectedPhase connPhase() const noexcept { return _connPhase; }
    /**
     * @param[in] other The other BasicSettingsRead.
     * @return Returns @b true if the two BasicSettingsRead objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const BasicSettingsRead& other) const noexcept = default;

  private:
    constexpr BasicSettingsRead(const catta::modbus::sunspec::ScaledValueU16 wMax, const catta::modbus::sunspec::ScaledValueU16 vMax,
                                const catta::modbus::sunspec::ScaledValueU16 vMin, const catta::modbus::sunspec::ScaledValueU16 ecpNomHz,
                                catta::modbus::sunspec::ConnectedPhase connPhase)
        : _wMax(wMax), _vMax(vMax), _vMin(vMin), _ecpNomHz(ecpNomHz), _connPhase(connPhase)
    {
    }
    catta::modbus::sunspec::ScaledValueU16 _wMax;
    catta::modbus::sunspec::ScaledValueU16 _vMax;
    catta::modbus::sunspec::ScaledValueU16 _vMin;
    catta::modbus::sunspec::ScaledValueU16 _ecpNomHz;
    catta::modbus::sunspec::ConnectedPhase _connPhase;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
