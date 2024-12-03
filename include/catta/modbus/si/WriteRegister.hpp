#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>
#include <catta/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/modbus/sunspec/ValueS16.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>

// std
#include <array>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Class for representing the possible sunspec write register command.
 *
 * @author CattaTech - Maik Urbannek
 */
class WriteRegister
{
  public:
    /**
     * Default constructor. Creates invalid write command.
     */
    constexpr WriteRegister() noexcept : WriteRegister(catta::modbus::si::RegisterAddress::empty(), 0) {}
    /**
     * @return Returns invalid write command.
     */
    constexpr static WriteRegister empty() noexcept { return WriteRegister{}; }
    /**
     *  @return Returns @b true if write command is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _registerAddress.isEmpty(); }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns write command if input is valid, otherwise empty.
     */
    static constexpr WriteRegister create(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::ValueU16 value)
    {
        return !registerAddress.isWritable() || !registerAddress.type().isUint16() || value.isEmpty()
                   ? empty()
                   : WriteRegister(registerAddress, static_cast<std::uint16_t>(value.value()));
    }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns write command if input is valid, otherwise empty.
     */
    static constexpr WriteRegister create(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::ValueS16 value)
    {
        return !registerAddress.isWritable() || !registerAddress.type().isSint16() || value.isEmpty()
                   ? empty()
                   : WriteRegister(registerAddress, static_cast<std::uint16_t>(value.value()));
    }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns write command if input is valid, otherwise empty.
     */
    static constexpr WriteRegister create(const catta::modbus::si::RegisterAddress registerAddress,
                                          const catta::modbus::sunspec::ConnectedPhase value)
    {
        return !registerAddress.isWritable() || !registerAddress.type().isConnectedPhase() || value.isEmpty()
                   ? empty()
                   : WriteRegister(registerAddress, static_cast<std::uint16_t>(value));
    }

    /**
     * @param[in] registerAddress The register address. Can not be empty, otherwise empty is returned.
     * @param[in] raw The raw data of the value. Has to be valid accourding to register address.
     * @return Returns write command if input is valid, otherwise empty.
     */
    static constexpr WriteRegister fromRaw(catta::modbus::si::RegisterAddress registerAddress, const std::uint16_t raw) noexcept
    {
        switch (registerAddress.type())
        {
            case catta::modbus::si::RegisterType::uint16():
                return WriteRegister::create(registerAddress, catta::modbus::sunspec::ValueU16::create(static_cast<std::uint16_t>(raw)));
            case catta::modbus::si::RegisterType::sint16():
                return WriteRegister::create(registerAddress, catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(raw)));
            case catta::modbus::si::RegisterType::connectedPhase():
                return WriteRegister::create(registerAddress, catta::modbus::sunspec::ConnectedPhase(static_cast<std::uint8_t>(raw)));
            default:
                return WriteRegister::empty();
        }
    }

    /**
     * @return Returns the register address. Is only valid if not empty.
     */
    constexpr catta::modbus::si::RegisterAddress registerAddress() const noexcept { return _registerAddress; }
    /**
     * @return Returns the raw value. Is only valid if not empty.
     */
    constexpr std::uint16_t raw() const noexcept { return _value; }
    /**
     * @param[in] other The other WriteRegister.
     * @return Returns @b true if the two WriteRegister objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const WriteRegister& other) const noexcept = default;

  private:
    constexpr WriteRegister(const catta::modbus::si::RegisterAddress registerAddress, const std::uint16_t value)
        : _registerAddress(registerAddress), _value(value)
    {
    }
    catta::modbus::si::RegisterAddress _registerAddress;
    std::uint16_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
