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
 * @brief Class for representing the Nameplate block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class Nameplate
{
  public:
    /**
     * Default constructor. Creates invalid Nameplate block.
     */
    constexpr Nameplate() noexcept : Nameplate(catta::modbus::sunspec::ValueU16::empty()) {}
    /**
     * @return Returns invalid Nameplate block.
     */
    constexpr static Nameplate empty() noexcept { return Nameplate{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _dERTyp.isEmpty(); }
    /**
     * @param[in] dERTyp Type of DER device. Default value is 4 to indicate PV device. Has to be valid, otherwise empty is returned.
     * @return Returns Nameplate block. if input is valid, otherwise empty.
     */
    static constexpr Nameplate create(const catta::modbus::sunspec::ValueU16 dERTyp) { return dERTyp.isEmpty() ? empty() : Nameplate(dERTyp); }
    /**
     * @return Returns the Type of DER device. Default value is 4 to indicate PV device. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 dERTyp() const noexcept { return _dERTyp; }
    /**
     * @param[in] other The other Nameplate.
     * @return Returns @b true if the two Nameplate objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Nameplate& other) const noexcept = default;

  private:
    constexpr Nameplate(const catta::modbus::sunspec::ValueU16 dERTyp) : _dERTyp(dERTyp) {}
    catta::modbus::sunspec::ValueU16 _dERTyp;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
