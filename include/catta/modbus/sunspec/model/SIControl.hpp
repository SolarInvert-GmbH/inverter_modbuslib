#pragma once

// sunspec
#include <catta/modbus/sunspec/ValueS16.hpp>
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
 * @brief Class for representing the SI control block for reading and writing.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class SIControl
{
  public:
    /**
     * Default constructor. Creates invalid common block.
     */
    constexpr SIControl() noexcept
        : SIControl(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueS16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty())
    {
    }
    /**
     * @return Returns invalid SI control block.
     */
    constexpr static SIControl empty() noexcept { return SIControl{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _pcdDiv.isEmpty(); }
    /**
     * @param[in] pcdDiv The DC Power Diverted from Inverter. Has to be valid, otherwise empty is returned.
     * @param[in] udcExt The Setpoint for DC voltage. Has to be valid, otherwise empty is returned.
     * @param[in] psetpoint The Setpoint for AC active power. Has to be valid, otherwise empty is returned.
     * @param[in] uminExt The minimum DC voltage. Has to be valid, otherwise empty is returned.
     * @param[in] umaxExt The maximum DC voltage. Has to be valid, otherwise empty is returned.
     * @return Returns common block if input is valid, otherwise empty.
     */
    static constexpr SIControl create(const catta::modbus::sunspec::ValueU16 pcdDiv, const catta::modbus::sunspec::ValueU16 udcExt,
                                      const catta::modbus::sunspec::ValueS16 psetpoint, const catta::modbus::sunspec::ValueU16 uminExt,
                                      const catta::modbus::sunspec::ValueU16 umaxExt)
    {
        return pcdDiv.isEmpty() || udcExt.isEmpty() || psetpoint.isEmpty() || uminExt.isEmpty() || umaxExt.isEmpty()
                   ? empty()
                   : SIControl(pcdDiv, udcExt, psetpoint, uminExt, umaxExt);
    }
    /**
     * @return Returns the DC Power Diverted from Inverter. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 pcdDiv() const noexcept { return _pcdDiv; }
    /**
     * @return Returns the Setpoint for DC voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 udcExt() const noexcept { return _udcExt; }
    /**
     * @return Returns the Setpoint for AC active power. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueS16 psetpoint() const noexcept { return _psetpoint; }
    /**
     * @return Returns the minimum DC voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 uminExt() const noexcept { return _uminExt; }
    /**
     * @return Returns the maximum DC voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 umaxExt() const noexcept { return _umaxExt; }
    /**
     * @param[in] other The other SIControl.
     * @return Returns @b true if the two SIControl objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const SIControl& other) const noexcept = default;

  private:
    constexpr SIControl(const catta::modbus::sunspec::ValueU16 pcdDiv, const catta::modbus::sunspec::ValueU16 udcExt,
                        const catta::modbus::sunspec::ValueS16 psetpoint, const catta::modbus::sunspec::ValueU16 uminExt,
                        const catta::modbus::sunspec::ValueU16 umaxExt)
        : _pcdDiv(pcdDiv), _udcExt(udcExt), _psetpoint(psetpoint), _uminExt(uminExt), _umaxExt(umaxExt)
    {
    }
    catta::modbus::sunspec::ValueU16 _pcdDiv;
    catta::modbus::sunspec::ValueU16 _udcExt;
    catta::modbus::sunspec::ValueS16 _psetpoint;
    catta::modbus::sunspec::ValueU16 _uminExt;
    catta::modbus::sunspec::ValueU16 _umaxExt;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
