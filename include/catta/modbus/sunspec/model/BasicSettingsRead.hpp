#pragma once

// sunspec
#include <catta/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/modbus/sunspec/ScaleFactor.hpp>
#include <catta/modbus/sunspec/ScaledValue2U16.hpp>
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
        : BasicSettingsRead(catta::modbus::sunspec::ScaledValueU16::empty(), catta::modbus::sunspec::ScaledValue2U16::empty(),
                            catta::modbus::sunspec::ScaleFactor::empty(), catta::modbus::sunspec::ScaleFactor::empty(),
                            catta::modbus::sunspec::ScaledValueU16::empty(), catta::modbus::sunspec::ConnectedPhase::empty())
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
     * @param[in] vMinMax Setpoint for minimum/maximum voltage. Has to be valid, otherwise empty is returned.
     * @param[in] wApparent Scale factor for apparent power. Has to be valid, otherwise empty is returned.
     * @param[in] wReactiv Scale factor for reactive power. Has to be valid, otherwise empty is returned.
     * @param[in] ecpNomHz Setpoint for nominal frequency at the ECP. Has to be valid, otherwise empty is returned.
     * @param[in] connPhase Identity of connected phase for single phase inverters. A=1 B=2 C=3.
     * @return Returns BasicSettingsRead controls block. if input is valid, otherwise empty.
     */
    static constexpr BasicSettingsRead create(const catta::modbus::sunspec::ScaledValueU16 wMax,
                                              const catta::modbus::sunspec::ScaledValue2U16 vMinMax,
                                              const catta::modbus::sunspec::ScaleFactor wApparent, const catta::modbus::sunspec::ScaleFactor wReactiv,
                                              const catta::modbus::sunspec::ScaledValueU16 ecpNomHz,
                                              const catta::modbus::sunspec::ConnectedPhase connPhase)
    {
        return wMax.isEmpty() || vMinMax.isEmpty() || wApparent.isEmpty() || wReactiv.isEmpty() || ecpNomHz.isEmpty() || connPhase.isEmpty()
                   ? empty()
                   : BasicSettingsRead(wMax, vMinMax, wApparent, wReactiv, ecpNomHz, connPhase);
    }
    /**
     * @return Returns the Setting for maximum power output. Default to WRtg. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ScaledValueU16 wMax() const noexcept { return _wMax; }
    /**
     * @return Returns the Setpoint for minimum/maximum voltage. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ScaledValue2U16 vMinMax() const noexcept { return _vMinMax; }
    /**
     * @return Returns the Scale factor for apparent power. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ScaleFactor wApparent() const noexcept { return _wApparent; }
    /**
     * @return Returns the Scale factor for reactive power. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ScaleFactor wReactiv() const noexcept { return _wReactiv; }
    /**
     * @return Returns the Setpoint for nominal frequency at the ECP. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ScaledValueU16 ecpNomHz() const noexcept { return _ecpNomHz; }
    /**
     * @return Returns the Identity of connected phase for single phase inverters. A=1 B=2 C=3. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ConnectedPhase connPhase() const noexcept { return _connPhase; }
    /**
     * @param[in] other The other BasicSettingsRead.
     * @return Returns @b true if the two BasicSettingsRead objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const BasicSettingsRead& other) const noexcept = default;

  private:
    constexpr BasicSettingsRead(const catta::modbus::sunspec::ScaledValueU16 wMax, const catta::modbus::sunspec::ScaledValue2U16 vMinMax,
                                const catta::modbus::sunspec::ScaleFactor wApparent, const catta::modbus::sunspec::ScaleFactor wReactiv,
                                const catta::modbus::sunspec::ScaledValueU16 ecpNomHz, catta::modbus::sunspec::ConnectedPhase connPhase)
        : _wMax(wMax), _vMinMax(vMinMax), _wApparent(wApparent), _wReactiv(wReactiv), _ecpNomHz(ecpNomHz), _connPhase(connPhase)
    {
    }
    catta::modbus::sunspec::ScaledValueU16 _wMax;
    catta::modbus::sunspec::ScaledValue2U16 _vMinMax;
    catta::modbus::sunspec::ScaleFactor _wApparent;
    catta::modbus::sunspec::ScaleFactor _wReactiv;
    catta::modbus::sunspec::ScaledValueU16 _ecpNomHz;
    catta::modbus::sunspec::ConnectedPhase _connPhase;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
