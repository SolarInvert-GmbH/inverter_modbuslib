#pragma once

// request
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing the constant voltage block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ConstantVoltage
{
  public:
    /**
     * Default constructor. Creates invalid constant voltage block.
     */
    constexpr ConstantVoltage() noexcept : ConstantVoltage(catta::modbus::sunspec::ValueU16::empty()) {}
    /**
     * @return Returns invalid constant voltage block.
     */
    constexpr static ConstantVoltage empty() noexcept { return ConstantVoltage{}; }
    /**
     *  @return Returns @b true if constant voltage is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _uSet.isEmpty(); }
    /**
     * @param[in] uSet Config the constant voltage. Has to be valid, otherwise empty is returned.
     * @return Returns ConstantVoltage controls block. if input is valid, otherwise empty.
     */
    static constexpr ConstantVoltage create(const catta::modbus::sunspec::ValueU16 uSet) { return uSet.isEmpty() ? empty() : ConstantVoltage(uSet); }
    /**
     * @return Returns the constant voltage config. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 uSet() const noexcept { return _uSet; }
    /**
     * @param[in] other The other ConstantVoltage.
     * @return Returns @b true if the two ConstantVoltage objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ConstantVoltage& other) const noexcept = default;

  private:
    constexpr ConstantVoltage(const catta::modbus::sunspec::ValueU16 uSet) : _uSet(uSet) {}
    catta::modbus::sunspec::ValueU16 _uSet;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
