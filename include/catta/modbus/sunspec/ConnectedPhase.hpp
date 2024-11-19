#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Represents phase connection.
 * @author CattaTech - Maik Urbannek
 */
class ConnectedPhase
{
  private:
    constexpr static std::uint8_t PHASE_A = 0;
    constexpr static std::uint8_t PHASE_B = 1;
    constexpr static std::uint8_t PHASE_C = 2;
    constexpr static std::uint8_t EMPTY = 3;

  public:
    /**
     * @param[in] value The enum value of the phase connection.
     * @warning This constructor should not be used. Use phaseA(), phaseB(), phaseC() or empty(). Explicit constructor. Converts uint8 to phase
     * connection.
     */
    [[nodiscard]] constexpr explicit ConnectedPhase(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid phase connection.
     */
    [[nodiscard]] constexpr ConnectedPhase() noexcept : ConnectedPhase(EMPTY) {}
    /**
     * @return Returns the phase a.
     */
    [[nodiscard]] constexpr static ConnectedPhase phaseA() noexcept { return ConnectedPhase{PHASE_A}; }
    /**
     * @return Returns the phase b.
     */
    [[nodiscard]] constexpr static ConnectedPhase phaseB() noexcept { return ConnectedPhase{PHASE_B}; }
    /**
     * @return Returns the phase c.
     */
    [[nodiscard]] constexpr static ConnectedPhase phaseC() noexcept { return ConnectedPhase{PHASE_C}; }
    /**
     * @return Returns the invalid phase connection.
     */
    [[nodiscard]] constexpr static ConnectedPhase empty() noexcept { return ConnectedPhase{EMPTY}; }
    /**
     * @param[in] other The other ConnectedPhase.
     * @return Returns @b true if the two ConnectedPhase objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const ConnectedPhase& other) const = default;
    /**
     * @return Returns phase connection as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if phase a is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isPhaseA() const noexcept { return _value == PHASE_A; }
    /**
     * @return Returns @b true if phase b is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isPhaseB() const noexcept { return _value == PHASE_B; }
    /**
     * @return Returns @b true if phase c is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isPhaseC() const noexcept { return _value == PHASE_C; }
    /**
     * @return Returns @b true if invalid phase connection is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Phase connection in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"PHASE_A", "PHASE_B", "PHASE_C"};

  private:
    std::uint8_t _value;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
