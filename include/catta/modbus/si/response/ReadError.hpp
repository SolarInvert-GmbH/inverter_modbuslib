#pragma once

// response
#include <catta/modbus/sunspec/ValueU16.hpp>

// std
#include <array>

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
  private:
    static constexpr std::uint8_t OVER_VOLTAGE_AC = 0;
    static constexpr std::uint8_t UNDER_VOLTAGE_AC = OVER_VOLTAGE_AC + 1;
    static constexpr std::uint8_t OVER_VOLTAGE_DC = UNDER_VOLTAGE_AC + 1;
    static constexpr std::uint8_t UNDER_VOLTAGE_DC = OVER_VOLTAGE_DC + 1;
    static constexpr std::uint8_t OVER_FREQUENCY = UNDER_VOLTAGE_DC + 1;
    static constexpr std::uint8_t UNDER_FREQUENCY = OVER_FREQUENCY + 1;
    static constexpr std::uint8_t LIMITED_POWER_T1 = UNDER_FREQUENCY + 1;
    static constexpr std::uint8_t LIMITED_POWER_T2 = LIMITED_POWER_T1 + 1;
    static constexpr std::uint8_t LIMITED_POWER_T3 = LIMITED_POWER_T2 + 1;
    static constexpr std::uint8_t LIMITED_POWER_T4 = LIMITED_POWER_T3 + 1;
    static constexpr std::uint8_t LIMITED_POWER_T5 = LIMITED_POWER_T4 + 1;
    static constexpr std::uint8_t COM = LIMITED_POWER_T5 + 1;
    static constexpr std::uint8_t ISLAND_GRID = COM + 1;
    static constexpr std::uint8_t OVER_CURRENT_INTERRUPT = ISLAND_GRID + 1;
    static constexpr std::uint8_t OVER_VOLTAGE_INTERRUPT = OVER_CURRENT_INTERRUPT + 1;
    static constexpr std::uint8_t AVERAGE_GRID_OVER_VOLTAGE = OVER_VOLTAGE_INTERRUPT + 1;
    static constexpr std::uint8_t OVER_TEMPERATURE_SHUTDOWN = AVERAGE_GRID_OVER_VOLTAGE + 1;
    static constexpr std::uint8_t DIFFERENCE_GRID_VOLTAGE = OVER_TEMPERATURE_SHUTDOWN + 1;
    static constexpr std::uint8_t ERROR_GRID_RELAIS = DIFFERENCE_GRID_VOLTAGE + 1;
    static constexpr std::uint8_t ERROR_CURRENT_SENSOR = ERROR_GRID_RELAIS + 1;
    static constexpr std::uint8_t SIZE = ERROR_CURRENT_SENSOR + 1;

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
    constexpr bool isEmpty() const noexcept { return _data[0].isEmpty(); }
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
    constexpr catta::modbus::sunspec::ValueU16 overVoltageAC() const noexcept { return _data[OVER_VOLTAGE_AC]; }
    /**
     * @return Returns the error: underVoltageAC Too low voltage AC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underVoltageAC() const noexcept { return _data[UNDER_VOLTAGE_AC]; }
    /**
     * @return Returns the error: overVoltageDC Too high voltage DC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overVoltageDC() const noexcept { return _data[OVER_VOLTAGE_DC]; }
    /**
     * @return Returns the error: underVoltageDC Too low voltage DC. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underVoltageDC() const noexcept { return _data[UNDER_VOLTAGE_DC]; }
    /**
     * @return Returns the error: overFrequency Too high frequency. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overFrequency() const noexcept { return _data[OVER_FREQUENCY]; }
    /**
     * @return Returns the error: underFrequency Too low frequency. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 underFrequency() const noexcept { return _data[UNDER_FREQUENCY]; }
    /**
     * @return Returns the error: limitedPowerT1 Temperature depended reduction of power output to 87.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT1() const noexcept { return _data[LIMITED_POWER_T1]; }
    /**
     * @return Returns the error: limitedPowerT2 Temperature depended reduction of power output to 75%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT2() const noexcept { return _data[LIMITED_POWER_T2]; }
    /**
     * @return Returns the error: limitedPowerT3 Temperature depended reduction of power output to 62.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT3() const noexcept { return _data[LIMITED_POWER_T3]; }
    /**
     * @return Returns the error: limitedPowerT4 Temperature depended reduction of power output to 50%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT4() const noexcept { return _data[LIMITED_POWER_T4]; }
    /**
     * @return Returns the error: Temperature depended reduction of power output to 37.5%. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 limitedPowerT5() const noexcept { return _data[LIMITED_POWER_T5]; }
    /**
     * @return Returns the error: Not implemented until v60. Failure in communication between grid inspector and control board. Is only valid if not
     * empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 com() const noexcept { return _data[COM]; }
    /**
     * @return Returns the error: Device is disconnected from grid. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 islandGrid() const noexcept { return _data[ISLAND_GRID]; }
    /**
     * @return Returns the error: Interrupt of too high current. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overCurrentInterrupt() const noexcept { return _data[OVER_CURRENT_INTERRUPT]; }
    /**
     * @return Returns the error: Interrupt of too high voltage. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overVoltageInterrupt() const noexcept { return _data[OVER_VOLTAGE_INTERRUPT]; }
    /**
     * @return Returns the error: 10 minute average of grid voltage too high. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 averageGridOverVoltage() const noexcept { return _data[AVERAGE_GRID_OVER_VOLTAGE]; }
    /**
     * @return Returns the error: Shutdown because of too high temperature. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 overTempratureShutdown() const noexcept { return _data[OVER_TEMPERATURE_SHUTDOWN]; }
    /**
     * @return Returns the error: Difference in measuring grid voltage. Only since v60. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 differenceGridVoltage() const noexcept { return _data[DIFFERENCE_GRID_VOLTAGE]; }
    /**
     * @return Returns the error: Failure in grid relais. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 errorGridRelais() const noexcept { return _data[ERROR_GRID_RELAIS]; }
    /**
     * @return Returns the error: Failure in reading current sensor. Is only valid if not empty.
     */
    constexpr catta::modbus::sunspec::ValueU16 errorCurrentSensor() const noexcept { return _data[ERROR_CURRENT_SENSOR]; }
    /**
     * @param[in] other The other ReadError.
     * @return Returns @b true if the two ReadError objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ReadError& other) const noexcept = default;
    /**
     * @return Returns @b the raw data array.
     */
    constexpr const std::array<catta::modbus::sunspec::ValueU16, SIZE>& raw() const noexcept { return _data; }

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
        : _data{overVoltageAC,   underVoltageAC,       overVoltageDC,        underVoltageDC,         overFrequency,          underFrequency,
                limitedPowerT1,  limitedPowerT2,       limitedPowerT3,       limitedPowerT4,         limitedPowerT5,         com,
                islandGrid,      overCurrentInterrupt, overVoltageInterrupt, averageGridOverVoltage, overTempratureShutdown, differenceGridVoltage,
                errorGridRelais, errorCurrentSensor}
    {
    }
    std::array<catta::modbus::sunspec::ValueU16, SIZE> _data;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
