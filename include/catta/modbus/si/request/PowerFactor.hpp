#pragma once

// request
#include <catta/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing the power factor block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class PowerFactor
{
  public:
    /**
     * Default constructor. Creates invalid power factor block.
     */
    constexpr PowerFactor() noexcept : PowerFactor(catta::modbus::sunspec::ValueU8<0, 255>::empty()) {}
    /**
     * @return Returns invalid power factor block.
     */
    constexpr static PowerFactor empty() noexcept { return PowerFactor{}; }
    /**
     *  @return Returns @b true if power factor is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _cosPhi.isEmpty(); }
    /**
     * @param[in] cosPhi Config the power factor. Has to be valid, otherwise empty is returned.
     * @return Returns PowerFactor controls block. if input is valid, otherwise empty.
     */
    static constexpr PowerFactor create(const catta::modbus::sunspec::ValueU8<0, 255> cosPhi)
    {
        return cosPhi.isEmpty() ? empty() : PowerFactor(cosPhi);
    }
    /**
     * @return Returns the power factor config. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU8<0, 255> cosPhi() const noexcept { return _cosPhi; }
    /**
     * @param[in] other The other PowerFactor.
     * @return Returns @b true if the two PowerFactor objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const PowerFactor& other) const noexcept = default;

  private:
    constexpr PowerFactor(const catta::modbus::sunspec::ValueU8<0, 255> cosPhi) : _cosPhi(cosPhi) {}
    catta::modbus::sunspec::ValueU8<0, 255> _cosPhi;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
