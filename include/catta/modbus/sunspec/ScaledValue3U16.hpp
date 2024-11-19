#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for representing three scaled unsigned 16 bit numbers.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledValue3U16
{
  public:
    /**
     * Default constructor. Creates invalid three scaled unsigned 16 bit numbers.
     */
    constexpr ScaledValue3U16() noexcept
        : ScaledValue3U16(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                          catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ScaleFactor::empty())
    {
    }
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ScaledValue3U16 empty() noexcept { return ScaledValue3U16{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _scale.isEmpty(); }
    /**
     * @param[in] phaseA Representing the unsigned value for phase a. Has to be valid, otherwise empty is returned.
     * @param[in] phaseB Representing the unsigned value for phase b. Has to be valid, otherwise empty is returned.
     * @param[in] phaseC Representing the unsigned value for phase c. Has to be valid, otherwise empty is returned.
     * @param[in] scale Representing the scale. Has to be valid, otherwise empty is returned.
     * @return Returns three scaled unsigned 16 bit numbers if input is valid, otherwise empty.
     */
    static constexpr ScaledValue3U16 create(const catta::modbus::sunspec::ValueU16 phaseA, const catta::modbus::sunspec::ValueU16 phaseB,
                                            const catta::modbus::sunspec::ValueU16 phaseC, const catta::modbus::sunspec::ScaleFactor scale)
    {
        return phaseA.isEmpty() || phaseB.isEmpty() || phaseC.isEmpty() || scale.isEmpty() ? empty() : ScaledValue3U16(phaseA, phaseB, phaseC, scale);
    }
    /**
     * @return Returns the value for phase a. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 phaseA() const noexcept { return _phaseA; }
    /**
     * @return Returns the value for phase b. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 phaseB() const noexcept { return _phaseB; }
    /**
     * @return Returns the value for phase c. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 phaseC() const noexcept { return _phaseC; }
    /**
     * @return Returns the scale. Is only valid if not empty.
     */
    catta::modbus::sunspec::ScaleFactor scale() const noexcept { return _scale; }
    /**
     * @param[in] other The other ScaledValue3U16.
     * @return Returns @b true if the two ScaledValue3U16 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledValue3U16& other) const noexcept = default;

  private:
    constexpr ScaledValue3U16(const catta::modbus::sunspec::ValueU16 phaseA, const catta::modbus::sunspec::ValueU16 phaseB,
                              const catta::modbus::sunspec::ValueU16 phaseC, const catta::modbus::sunspec::ScaleFactor scale)
        : _phaseA(phaseA), _phaseB(phaseB), _phaseC(phaseC), _scale(scale)
    {
    }
    catta::modbus::sunspec::ValueU16 _phaseA;
    catta::modbus::sunspec::ValueU16 _phaseB;
    catta::modbus::sunspec::ValueU16 _phaseC;
    catta::modbus::sunspec::ScaleFactor _scale;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
