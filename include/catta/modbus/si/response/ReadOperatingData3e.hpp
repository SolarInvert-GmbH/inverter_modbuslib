#pragma once

// response
#include <catta/modbus/si/Type.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>
#include <catta/modbus/sunspec/ValueU32.hpp>
#include <catta/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Class for representing the read operating data 0x3e block.
 *
 * @author CattaTech - Lars Joachimsthaler
 */
class ReadOperatingData3e
{
  public:
    /**
     * Default constructor. Creates invalid read operating data 0x3e block.
     */
    constexpr ReadOperatingData3e() noexcept
        : ReadOperatingData3e(catta::modbus::sunspec::ValueU16::empty(), catta::modbus::si::Type::empty(),
                              catta::modbus::sunspec::ValueU8<1, 10>::empty(), catta::modbus::sunspec::ValueU8<1, 32>::empty(),
                              catta::modbus::sunspec::ValueU8<0, 255>::empty(), catta::modbus::sunspec::ValueU32::empty(),
                              catta::modbus::sunspec::ValueU16::empty(), catta::modbus::sunspec::ValueU32::empty(),
                              catta::modbus::sunspec::ValueU8<0, 3>::empty(), catta::modbus::sunspec::ValueU8<0, 15>::empty())
    {
    }
    /**
     * @return Returns invalid read operating data 0x3e block.
     */
    constexpr static ReadOperatingData3e empty() noexcept { return ReadOperatingData3e{}; }
    /**
     *  @return Returns @b true if read operating data 0x3e is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _serialNumber.isEmpty(); }
    /**
     * @param[in] serialNumber Serial Number. Has to be valid, otherwise empty is returned.
     * @param[in] type Type of inverter (eg. solar). Has to be valid, otherwise empty is returned.
     * @param[in] voltageType Type of voltage. Has to be valid, otherwise empty is returned.
     * @param[in] nominalPower Powerclass of the device. Has to be valid, otherwise empty is returned.
     * @param[in] cosphi Power factor. Has to be valid, otherwise empty is returned.
     * @param[in] gridSupplyDailySum To grid daily supplied energy of the device. Has to be valid, otherwise empty is returned.
     * @param[in] powerLimitation Power limitation of the device. Has to be valid, otherwise empty is returned.
     * @param[in] operatingHours Sum of operating hours of the device. Has to be valid, otherwise empty is returned.
     * @param[in] phase Operating phase.. Has to be valid, otherwise empty is returned.
     * @param[in] modbusId Modbus Id set by jumpers. Has to be valid, otherwise empty is returned.
     * @return Returns ReadOperatingData3e block. if input is valid, otherwise empty.
     */
    static constexpr ReadOperatingData3e create(
        const catta::modbus::sunspec::ValueU16 serialNumber, const catta::modbus::si::Type type,
        const catta::modbus::sunspec::ValueU8<1, 10> voltageType, const catta::modbus::sunspec::ValueU8<1, 32> nominalPower,
        const catta::modbus::sunspec::ValueU8<0, 255> cosphi, const catta::modbus::sunspec::ValueU32 gridSupplyDailySum,
        const catta::modbus::sunspec::ValueU16 powerLimitation, const catta::modbus::sunspec::ValueU32 operatingHours,
        const catta::modbus::sunspec::ValueU8<0, 3> phase, const catta::modbus::sunspec::ValueU8<0, 15> modbusId)
    {
        return serialNumber.isEmpty() || type.isEmpty() || voltageType.isEmpty() || nominalPower.isEmpty() || cosphi.isEmpty() ||
                       gridSupplyDailySum.isEmpty() || powerLimitation.isEmpty() || operatingHours.isEmpty() || phase.isEmpty() || modbusId.isEmpty()
                   ? empty()
                   : ReadOperatingData3e(serialNumber, type, voltageType, nominalPower, cosphi, gridSupplyDailySum, powerLimitation, operatingHours,
                                         phase, modbusId);
    }
    /**
     * @return Returns the serial Number. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 serialNumber() const noexcept { return _serialNumber; }
    /**
     * @return Returns the type of inverter (eg. solar). Is only valid if not empty.
     */
    catta::modbus::si::Type type() const noexcept { return _type; }
    /**
     * @return Returns the type of voltage. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<1, 10> voltageType() const noexcept { return _voltageType; }
    /**
     * @return Returns the powerclass of the device. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<1, 32> nominalPower() const noexcept { return _nominalPower; }
    /**
     * @return Returns the power factor. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<0, 255> cosphi() const noexcept { return _cosphi; }
    /**
     * @return Returns the to grid daily supplied energy of the device. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU32 gridSupplyDailySum() const noexcept { return _gridSupplyDailySum; }
    /**
     * @return Returns the power limitation of the device. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU16 powerLimitation() const noexcept { return _powerLimitation; }
    /**
     * @return Returns the sum of operating hours of the device. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU32 operatingHours() const noexcept { return _operatingHours; }
    /**
     * @return Returns the operating phase. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<0, 3> phase() const noexcept { return _phase; }
    /**
     * @return Returns the modbus Id set by jumpers. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<0, 15> modbusId() const noexcept { return _modbusId; }
    /**
     * @param[in] other The other ReadOperatingData3e.
     * @return Returns @b true if the two ReadOperatingData3e objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ReadOperatingData3e& other) const noexcept = default;

  private:
    constexpr ReadOperatingData3e(const catta::modbus::sunspec::ValueU16 serialNumber, const catta::modbus::si::Type type,
                                  const catta::modbus::sunspec::ValueU8<1, 10> voltageType, const catta::modbus::sunspec::ValueU8<1, 32> nominalPower,
                                  catta::modbus::sunspec::ValueU8<0, 255> cosphi, const catta::modbus::sunspec::ValueU32 gridSupplyDailySum,
                                  const catta::modbus::sunspec::ValueU16 powerLimitation, const catta::modbus::sunspec::ValueU32 operatingHours,
                                  const catta::modbus::sunspec::ValueU8<0, 3> phase, const catta::modbus::sunspec::ValueU8<0, 15> modbusId)
        : _serialNumber(serialNumber),
          _type(type),
          _voltageType(voltageType),
          _nominalPower(nominalPower),
          _cosphi(cosphi),
          _gridSupplyDailySum(gridSupplyDailySum),
          _powerLimitation(powerLimitation),
          _operatingHours(operatingHours),
          _phase(phase),
          _modbusId(modbusId)
    {
    }
    catta::modbus::sunspec::ValueU16 _serialNumber;
    catta::modbus::si::Type _type;
    catta::modbus::sunspec::ValueU8<1, 10> _voltageType;
    catta::modbus::sunspec::ValueU8<1, 32> _nominalPower;
    catta::modbus::sunspec::ValueU8<0, 255> _cosphi;
    catta::modbus::sunspec::ValueU32 _gridSupplyDailySum;
    catta::modbus::sunspec::ValueU16 _powerLimitation;
    catta::modbus::sunspec::ValueU32 _operatingHours;
    catta::modbus::sunspec::ValueU8<0, 3> _phase;
    catta::modbus::sunspec::ValueU8<0, 15> _modbusId;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
