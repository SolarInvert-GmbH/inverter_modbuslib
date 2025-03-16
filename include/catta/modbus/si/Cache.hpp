#pragma once

// si
#include <catta/modbus/si/Type.hpp>

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Class for representing the cache.
 *
 * @author CattaTech - Maik Urbannek
 */
class Cache
{
  public:
    /**
     * Default constructor. Creates invalid cache.
     */
    constexpr Cache() noexcept
        : Cache(catta::modbus::si::Type::empty(), catta::modbus::sunspec::ScaleFactor::empty(), catta::modbus::sunspec::ScaleFactor::empty(),
                catta::modbus::sunspec::ScaleFactor::empty(), catta::modbus::sunspec::ScaleFactor::empty(),
                catta::modbus::sunspec::ScaleFactor::empty(), catta::modbus::sunspec::ScaleFactor::empty(),
                catta::modbus::sunspec::ScaleFactor::empty(), catta::modbus::sunspec::ScaleFactor::empty(), true)
    {
    }
    /**
     * @return Returns invalid cache.
     */
    constexpr static Cache empty() noexcept { return Cache{}; }
    /**
     *  @return Returns @b true if cache is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _empty; }
    /**
     * @param[in] type The type. Can be empty.
     * @param[in] inverterAmpsScaleFactor The inverter amps scale factor. Can be empty.
     * @param[in] inverterPhaseVoltageScaleFactor The inverter phase voltage scale factor. Can be empty.
     * @param[in] inverterWattScaleFactor The inverter watt scale factor. Can be empty.
     * @param[in] inverterHertzScaleFactor The inverter hertz scale factor. Can be empty.
     * @param[in] inverterPowerFactorScaleFactor The inverter power factor scale factor. Can be empty.
     * @param[in] inverterWattHoursScaleFactor The inverter watt hours scale factor. Can be empty.
     * @param[in] inverterDcVoltageScaleFactor The inverter dc voltage scale factor. Can be empty.
     * @param[in] inverterTemperatureScaleFactor The inverter temperature scale factor. Can be empty.
     * @return Returns the cache.
     */
    static constexpr Cache create(const catta::modbus::si::Type type, const catta::modbus::sunspec::ScaleFactor inverterAmpsScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterPhaseVoltageScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterWattScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterHertzScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterPowerFactorScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterWattHoursScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterDcVoltageScaleFactor,
                                  const catta::modbus::sunspec::ScaleFactor inverterTemperatureScaleFactor)
    {
        return Cache(type, inverterAmpsScaleFactor, inverterPhaseVoltageScaleFactor, inverterWattScaleFactor, inverterHertzScaleFactor,
                     inverterPowerFactorScaleFactor, inverterWattHoursScaleFactor, inverterDcVoltageScaleFactor, inverterTemperatureScaleFactor,
                     false);
    }
    /**
     * @return Returns the type.
     */
    constexpr catta::modbus::si::Type type() const noexcept { return _type; }
    /**
     * @return Returns the inverterAmpsScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterAmpsScaleFactor() const noexcept { return _inverterAmpsScaleFactor; }
    /**
     * @return Returns the inverterPhaseVoltageScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterPhaseVoltageScaleFactor() const noexcept { return _inverterPhaseVoltageScaleFactor; }
    /**
     * @return Returns the inverterWattScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterWattScaleFactor() const noexcept { return _inverterWattScaleFactor; }
    /**
     * @return Returns the inverterHertzScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterHertzScaleFactor() const noexcept { return _inverterHertzScaleFactor; }

    /**
     * @return Returns the inverterPowerFactorScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterPowerFactorScaleFactor() const noexcept { return _inverterPowerFactorScaleFactor; }
    /**
     * @return Returns the inverterWattHoursScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterWattHoursScaleFactor() const noexcept { return _inverterWattHoursScaleFactor; }
    /**
     * @return Returns the inverterDcVoltageScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterDcVoltageScaleFactor() const noexcept { return _inverterDcVoltageScaleFactor; }
    /**
     * @return Returns the inverterTemperatureScaleFactor.
     */
    constexpr catta::modbus::sunspec::ScaleFactor inverterTemperatureScaleFactor() const noexcept { return _inverterTemperatureScaleFactor; }
    /**
     * @param[in] other The other Cache.
     * @return Returns @b true if the two Cache objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Cache& other) const noexcept = default;

  private:
    constexpr Cache(const catta::modbus::si::Type type, const catta::modbus::sunspec::ScaleFactor inverterAmpsScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterPhaseVoltageScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterWattScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterHertzScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterPowerFactorScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterWattHoursScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterDcVoltageScaleFactor,
                    const catta::modbus::sunspec::ScaleFactor inverterTemperatureScaleFactor, const bool empty)
        : _type(type),
          _inverterAmpsScaleFactor(inverterAmpsScaleFactor),
          _inverterPhaseVoltageScaleFactor(inverterPhaseVoltageScaleFactor),
          _inverterWattScaleFactor(inverterWattScaleFactor),
          _inverterHertzScaleFactor(inverterHertzScaleFactor),
          _inverterPowerFactorScaleFactor(inverterPowerFactorScaleFactor),
          _inverterWattHoursScaleFactor(inverterWattHoursScaleFactor),
          _inverterDcVoltageScaleFactor(inverterDcVoltageScaleFactor),
          _inverterTemperatureScaleFactor(inverterTemperatureScaleFactor),
          _empty(empty)
    {
    }
    catta::modbus::si::Type _type;
    catta::modbus::sunspec::ScaleFactor _inverterAmpsScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterPhaseVoltageScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterWattScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterHertzScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterPowerFactorScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterWattHoursScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterDcVoltageScaleFactor;
    catta::modbus::sunspec::ScaleFactor _inverterTemperatureScaleFactor;
    bool _empty;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
