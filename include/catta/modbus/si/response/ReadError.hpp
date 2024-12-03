#pragma once

// response
#include <catta/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Class for representing the read error block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ReadError
{
  public:
    /**
     * Default constructor. Creates invalid read error block.
     */
    constexpr ReadError() noexcept
        : ReadError(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty(),
                    catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU16::empty())
    {
    }
    /**
     * @return Returns invalid read error block.
     */
    constexpr static ReadError empty() noexcept { return ReadError{}; }
    /**
     *  @return Returns @b true if read error is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _overVoltageAC.isEmpty(); }
    /**
     * @param[in] overVoltageAC Too high voltage AC. Has to be valid, otherwise empty is returned.
     * @param[in] underVoltageAC Too low voltage AC. Has to be valid, otherwise empty is returned.
     * @param[in] overVoltageDC Too high voltage DC. Has to be valid, otherwise empty is returned.
     * @param[in] underVoltageDC Too low voltage DC. Has to be valid, otherwise empty is returned.
     * @param[in] overFrequency Too high frequency. Has to be valid, otherwise empty is returned.
     * @param[in] underFrequency Too low frequency. Has to be valid, otherwise empty is returned.
     * @param[in] limitedPowerT1 Temperature depended reduction of power output to 87.5%. Has to be valid, otherwise empty is returned.
     * @param[in] limitedPowerT2 Temperature depended reduction of power output to 75%. Has to be valid, otherwise empty is returned.
     * @param[in] limitedPowerT3 Temperature depended reduction of power output to 62.5%. Has to be valid, otherwise empty is returned.
     * @param[in] limitedPowerT4 Temperature depended reduction of power output to 50%. Has to be valid, otherwise empty is returned.
     * @param[in] limitedPowerT5 Temperature depended reduction of power output to 37.5%. Has to be valid, otherwise empty is returned.
     * @param[in] com Not implemented until v60. Failure in communication between grid inspector and control board. Has to be valid, otherwise empty
     * is returned.
     * @param[in] islandGrid Device is disconnected from grid. Has to be valid, otherwise empty is returned.
     * @param[in] overCurrentInterrupt Interrupt of too high current. Has to be valid, otherwise empty is returned.
     * @param[in] overVoltageInterrupt Interrupt of too high voltage. Has to be valid, otherwise empty is returned.
     * @param[in] averageGridOverVoltage 10 minute average of grid voltage too high. Has to be valid, otherwise empty is returned.
     * @param[in] overTempratureShutdown Shutdown because of too high temperature. Has to be valid, otherwise empty is returned.
     * @param[in] differenceGridVoltage Difference in measuring grid voltage. Only since v60. Has to be valid, otherwise empty is returned.
     * @param[in] errorGridRelais Failure in grid relais. Has to be valid, otherwise empty is returned.
     * @param[in] errorCurrentSensor Failure in reading current sensor. Has to be valid, otherwise empty is returned.
     * @return Returns ReadError block. if input is valid, otherwise empty.
     */
    static constexpr ReadError create(const catta::modbus::sunspec::ValueU16 overVoltageAC, const catta::modbus::sunspec::ValueU16 underVoltageAC,
                                      const catta::modbus::sunspec::ValueU16 overVoltageDC, const catta::modbus::sunspec::ValueU16 underVoltageDC,
                                      const catta::modbus::sunspec::ValueU16 overFrequency, const catta::modbus::sunspec::ValueU16 underFrequency,
                                      const catta::modbus::sunspec::ValueU16 limitedPowerT1, const catta::modbus::sunspec::ValueU16 limitedPowerT2,
                                      const catta::modbus::sunspec::ValueU16 limitedPowerT3, const catta::modbus::sunspec::ValueU16 limitedPowerT4,
                                      const catta::modbus::sunspec::ValueU16 limitedPowerT5, const catta::modbus::sunspec::ValueU16 com,
                                      const catta::modbus::sunspec::ValueU16 islandGrid, const catta::modbus::sunspec::ValueU16 overCurrentInterrupt,
                                      const catta::modbus::sunspec::ValueU16 overVoltageInterrupt,
                                      const catta::modbus::sunspec::ValueU16 averageGridOverVoltage,
                                      const catta::modbus::sunspec::ValueU16 overTempratureShutdown,
                                      const catta::modbus::sunspec::ValueU16 differenceGridVoltage,
                                      const catta::modbus::sunspec::ValueU16 errorGridRelais,
                                      const catta::modbus::sunspec::ValueU16 errorCurrentSensor)
    {
        return overVoltageAC.isEmpty() || underVoltageAC.isEmpty() || overVoltageDC.isEmpty() || underVoltageDC.isEmpty() ||
                       overFrequency.isEmpty() || underFrequency.isEmpty() || limitedPowerT1.isEmpty() || limitedPowerT2.isEmpty() ||
                       limitedPowerT3.isEmpty() || limitedPowerT4.isEmpty() || limitedPowerT5.isEmpty() || com.isEmpty() || islandGrid.isEmpty() ||
                       overCurrentInterrupt.isEmpty() || overVoltageInterrupt.isEmpty() || averageGridOverVoltage.isEmpty() ||
                       overTempratureShutdown.isEmpty() || differenceGridVoltage.isEmpty() || errorGridRelais.isEmpty() ||
                       errorCurrentSensor.isEmpty()
                   ? empty()
                   : ReadError(overVoltageAC, underVoltageAC, overVoltageDC, underVoltageDC, overFrequency, underFrequency, limitedPowerT1,
                               limitedPowerT2, limitedPowerT3, limitedPowerT4, limitedPowerT5, com, islandGrid, overCurrentInterrupt,
                               overVoltageInterrupt, averageGridOverVoltage, overTempratureShutdown, differenceGridVoltage, errorGridRelais,
                               errorCurrentSensor);
    }
    /**
     * @return Returns the error: overVoltageAC Too high voltage AC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overVoltageAC() const noexcept { return _overVoltageAC; }
    /**
     * @return Returns the error: underVoltageAC Too low voltage AC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underVoltageAC() const noexcept { return _underVoltageAC; }
    /**
     * @return Returns the error: overVoltageDC Too high voltage DC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overVoltageDC() const noexcept { return _overVoltageDC; }
    /**
     * @return Returns the error: underVoltageDC Too low voltage DC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underVoltageDC() const noexcept { return _underVoltageDC; }
    /**
     * @return Returns the error: overFrequency Too high frequency. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overFrequency() const noexcept { return _overFrequency; }
    /**
     * @return Returns the error: underFrequency Too low frequency. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underFrequency() const noexcept { return _underFrequency; }
    /**
     * @return Returns the error: limitedPowerT1 Temperature depended reduction of power output to 87.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT1() const noexcept { return _limitedPowerT1; }
    /**
     * @return Returns the error: limitedPowerT2 Temperature depended reduction of power output to 75%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT2() const noexcept { return _limitedPowerT2; }
    /**
     * @return Returns the error: limitedPowerT3 Temperature depended reduction of power output to 62.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT3() const noexcept { return _limitedPowerT3; }
    /**
     * @return Returns the error: limitedPowerT4 Temperature depended reduction of power output to 50%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT4() const noexcept { return _limitedPowerT4; }
    /**
     * @return Returns the error: Temperature depended reduction of power output to 37.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT5() const noexcept { return _limitedPowerT5; }
    /**
     * @return Returns the error: Not implemented until v60. Failure in communication between grid inspector and control board. Is only valid if not
     * empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 com() const noexcept { return _com; }
    /**
     * @return Returns the error: Device is disconnected from grid. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 islandGrid() const noexcept { return _islandGrid; }
    /**
     * @return Returns the error: Interrupt of too high current. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overCurrentInterrupt() const noexcept { return _overCurrentInterrupt; }
    /**
     * @return Returns the error: Interrupt of too high voltage. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overVoltageInterrupt() const noexcept { return _overVoltageInterrupt; }
    /**
     * @return Returns the error: 10 minute average of grid voltage too high. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 averageGridOverVoltage() const noexcept { return _averageGridOverVoltage; }
    /**
     * @return Returns the error: Shutdown because of too high temperature. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overTempratureShutdown() const noexcept { return _overTempratureShutdown; }
    /**
     * @return Returns the error: Difference in measuring grid voltage. Only since v60. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 differenceGridVoltage() const noexcept { return _differenceGridVoltage; }
    /**
     * @return Returns the error: Failure in grid relais. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 errorGridRelais() const noexcept { return _errorGridRelais; }
    /**
     * @return Returns the error: Failure in reading current sensor. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 errorCurrentSensor() const noexcept { return _errorCurrentSensor; }
    /**
     * @param[in] other The other ReadError.
     * @return Returns @b true if the two ReadError objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ReadError& other) const noexcept = default;

  private:
    constexpr ReadError(const catta::modbus::sunspec::ValueU16 overVoltageAC, const catta::modbus::sunspec::ValueU16 underVoltageAC,
                        const catta::modbus::sunspec::ValueU16 overVoltageDC, const catta::modbus::sunspec::ValueU16 underVoltageDC,
                        catta::modbus::sunspec::ValueU16 overFrequency, const catta::modbus::sunspec::ValueU16 underFrequency,
                        const catta::modbus::sunspec::ValueU16 limitedPowerT1, const catta::modbus::sunspec::ValueU16 limitedPowerT2,
                        const catta::modbus::sunspec::ValueU16 limitedPowerT3, const catta::modbus::sunspec::ValueU16 limitedPowerT4,
                        const catta::modbus::sunspec::ValueU16 limitedPowerT5, const catta::modbus::sunspec::ValueU16 com,
                        const catta::modbus::sunspec::ValueU16 islandGrid, const catta::modbus::sunspec::ValueU16 overCurrentInterrupt,
                        catta::modbus::sunspec::ValueU16 overVoltageInterrupt, const catta::modbus::sunspec::ValueU16 averageGridOverVoltage,
                        const catta::modbus::sunspec::ValueU16 overTempratureShutdown, const catta::modbus::sunspec::ValueU16 differenceGridVoltage,
                        const catta::modbus::sunspec::ValueU16 errorGridRelais, const catta::modbus::sunspec::ValueU16 errorCurrentSensor)
        : _overVoltageAC(overVoltageAC),
          _underVoltageAC(underVoltageAC),
          _overVoltageDC(overVoltageDC),
          _underVoltageDC(underVoltageDC),
          _overFrequency(overFrequency),
          _underFrequency(underFrequency),
          _limitedPowerT1(limitedPowerT1),
          _limitedPowerT2(limitedPowerT2),
          _limitedPowerT3(limitedPowerT3),
          _limitedPowerT4(limitedPowerT4),
          _limitedPowerT5(limitedPowerT5),
          _com(com),
          _islandGrid(islandGrid),
          _overCurrentInterrupt(overCurrentInterrupt),
          _overVoltageInterrupt(overVoltageInterrupt),
          _averageGridOverVoltage(averageGridOverVoltage),
          _overTempratureShutdown(overTempratureShutdown),
          _differenceGridVoltage(differenceGridVoltage),
          _errorGridRelais(errorGridRelais),
          _errorCurrentSensor(errorCurrentSensor)
    {
    }
    catta::modbus::sunspec::ValueU16 _overVoltageAC;
    catta::modbus::sunspec::ValueU16 _underVoltageAC;
    catta::modbus::sunspec::ValueU16 _overVoltageDC;
    catta::modbus::sunspec::ValueU16 _underVoltageDC;
    catta::modbus::sunspec::ValueU16 _overFrequency;
    catta::modbus::sunspec::ValueU16 _underFrequency;
    catta::modbus::sunspec::ValueU16 _limitedPowerT1;
    catta::modbus::sunspec::ValueU16 _limitedPowerT2;
    catta::modbus::sunspec::ValueU16 _limitedPowerT3;
    catta::modbus::sunspec::ValueU16 _limitedPowerT4;
    catta::modbus::sunspec::ValueU16 _limitedPowerT5;
    catta::modbus::sunspec::ValueU16 _com;
    catta::modbus::sunspec::ValueU16 _islandGrid;
    catta::modbus::sunspec::ValueU16 _overCurrentInterrupt;
    catta::modbus::sunspec::ValueU16 _overVoltageInterrupt;
    catta::modbus::sunspec::ValueU16 _averageGridOverVoltage;
    catta::modbus::sunspec::ValueU16 _overTempratureShutdown;
    catta::modbus::sunspec::ValueU16 _differenceGridVoltage;
    catta::modbus::sunspec::ValueU16 _errorGridRelais;
    catta::modbus::sunspec::ValueU16 _errorCurrentSensor;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
