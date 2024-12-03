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
 * @brief Class for representing the possible sunspec read register command.
 *
 * @author CattaTech - Maik Urbannek
 */
class ReadRegister
{
  public:
    /**
     * Default constructor. Creates invalid read command.
     */
    constexpr ReadRegister() noexcept : ReadRegister(catta::modbus::si::RegisterAddress::empty()) {}
    /**
     * @return Returns invalid read command.
     */
    constexpr static ReadRegister empty() noexcept { return ReadRegister{}; }
    /**
     *  @return Returns @b true if read command is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _registerAddress.isEmpty(); }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @return Returns read command if input is valid, otherwise empty.
     */
    static constexpr ReadRegister create(const catta::modbus::si::RegisterAddress registerAddress)
    {
        return !registerAddress.isReadable() ? empty() : ReadRegister(registerAddress);
    }
    /**
     * @return Returns the register address. Is only valid if not empty.
     */
    constexpr catta::modbus::si::RegisterAddress registerAddress() const noexcept { return _registerAddress; }
    /**
     * @param[in] other The other ReadRegister.
     * @return Returns @b true if the two ReadRegister objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ReadRegister& other) const noexcept = default;

  private:
    constexpr ReadRegister(const catta::modbus::si::RegisterAddress registerAddress) : _registerAddress(registerAddress) {}
    catta::modbus::si::RegisterAddress _registerAddress;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
