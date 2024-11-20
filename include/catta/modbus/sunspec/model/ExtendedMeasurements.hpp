#pragma once

// sunspec
#include <catta/modbus/sunspec/ValueU64.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
namespace model
{
/**
 * @brief Class for representing the ExtendedMeasurements block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ExtendedMeasurements
{
  public:
    /**
     * Default constructor. Creates invalid ExtendedMeasurements block.
     */
    constexpr ExtendedMeasurements() noexcept : ExtendedMeasurements(catta::modbus::sunspec::ValueU64::empty()) {}
    /**
     * @return Returns invalid ExtendedMeasurements block.
     */
    constexpr static ExtendedMeasurements empty() noexcept { return ExtendedMeasurements{}; }
    /**
     *  @return Returns @b true if common block is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _acWatthours.isEmpty(); }
    /**
     * @param[in] acWatthours AC lifetime active (real) energy output. Has to be valid, otherwise empty is returned.
     * @return Returns ExtendedMeasurements block. if input is valid, otherwise empty.
     */
    static constexpr ExtendedMeasurements create(const catta::modbus::sunspec::ValueU64 acWatthours)
    {
        return acWatthours.isEmpty() ? empty() : ExtendedMeasurements(acWatthours);
    }
    /**
     * @return Returns AC lifetime active (real) energy output. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU64 acWatthours() const noexcept { return _acWatthours; }
    /**
     * @param[in] other The AC lifetime active (real) energy output.
     * @return Returns @b true if the two ExtendedMeasurements objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ExtendedMeasurements& other) const noexcept = default;

  private:
    constexpr ExtendedMeasurements(const catta::modbus::sunspec::ValueU64 acWatthours) : _acWatthours(acWatthours) {}
    catta::modbus::sunspec::ValueU64 _acWatthours;
};
}  // namespace model
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
