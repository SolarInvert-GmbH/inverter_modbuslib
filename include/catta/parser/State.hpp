#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace parser
{
/**
 * @brief State represents the states a string parser can be in.
 * @author CattaTech - Maik Urbannek
 */
class State
{
  private:
    constexpr static std::uint8_t RUNNING = 0;
    constexpr static std::uint8_t DONE = 1;
    constexpr static std::uint8_t FAILED = 2;
    constexpr static std::uint8_t START = 3;
    constexpr static std::uint8_t EMPTY = 4;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @warning This constructor should not be used. Use running(), done(), failed(), start() or empty(). Explicit constructor. Converts uint8 to
     * state.
     */
    [[nodiscard]] constexpr explicit State(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty state.
     */
    [[nodiscard]] constexpr State() noexcept : State(EMPTY) {}
    /**
     * @return Returns the running state.
     */
    [[nodiscard]] constexpr static State running() noexcept { return State{RUNNING}; }
    /**
     * @return Returns the done state.
     */
    [[nodiscard]] constexpr static State done() noexcept { return State{DONE}; }
    /**
     * @return Returns the failed state.
     */
    [[nodiscard]] constexpr static State failed() noexcept { return State{FAILED}; }
    /**
     * @return Returns the start state.
     */
    [[nodiscard]] constexpr static State start() noexcept { return State{START}; }
    /**
     * @return Returns the empty state.
     */
    [[nodiscard]] constexpr static State empty() noexcept { return State{EMPTY}; }
    /**
     * @param[in] other The other State.
     * @return Returns @b true if the two State objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const State& other) const = default;
    /**
     * @return Returns state as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if running state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isRunning() const noexcept { return _value == RUNNING; }
    /**
     * @return Returns @b true if done state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isDone() const noexcept { return _value == DONE; }
    /**
     * @return Returns @b true if failed state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFailed() const noexcept { return _value == FAILED; }
    /**
     * @return Returns @b true if start state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isStart() const noexcept { return _value == START; }
    /**
     * @return Returns @b true if empty state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * State in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"RUNNING", "DONE", "FAILED", "START"};
    /**
     * @return Returns @b true if state is active (running or start), otherwise @b false.
     */
    [[nodiscard]] constexpr bool isActive() const noexcept { return _value == RUNNING || _value == START; }

  private:
    std::uint8_t _value;
};
}  // namespace parser
}  // namespace catta
