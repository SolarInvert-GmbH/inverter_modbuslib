#pragma once

#include <catta/EnumConcept.hpp>

namespace catta
{
namespace state
{
/**
 * @tparam ERROR_TYPE The possible errors.
 *
 * @brief Represents the states active, closed and the error states from ERROR_TYPE.
 *
 * @author CattaTech - Maik Urbannek
 */
template <class ERROR_TYPE>
class ActiveCloseErrorState
{
  public:
  private:
    constexpr static std::uint8_t ERROR = 0;
    constexpr static std::uint8_t ACTIVE = 1;
    constexpr static std::uint8_t CLOSED = 2;
    constexpr static std::uint8_t EMPTY = 3;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @param[in] error The error value of the state.
     * @warning This constructor should not be used. Use error(),active(), closed() or empty(). Explicit constructor. Converts uint8 and error to
     * state.
     */
    [[nodiscard]] constexpr explicit ActiveCloseErrorState(const std::uint8_t value, const ERROR_TYPE& error) noexcept : _value(value), _error(error)
    {
    }
    /**
     * Default constructor. Creates empty state.
     */
    [[nodiscard]] constexpr ActiveCloseErrorState() noexcept : ActiveCloseErrorState(EMPTY, ERROR_TYPE{}) {}
    /**
     * @return Returns the error representation.
     */
    [[nodiscard]] constexpr static ActiveCloseErrorState error(const ERROR_TYPE& errorType) noexcept
    {
        return ActiveCloseErrorState{ERROR, errorType};
    }
    /**
     * @return Returns the active representation.
     */
    [[nodiscard]] constexpr static ActiveCloseErrorState active() noexcept { return ActiveCloseErrorState{ACTIVE, ERROR_TYPE{}}; }
    /**
     * @return Returns the closed representation.
     */
    [[nodiscard]] constexpr static ActiveCloseErrorState closed() noexcept { return ActiveCloseErrorState{CLOSED, ERROR_TYPE{}}; }
    /**
     * @return Returns the no state representation.
     */
    [[nodiscard]] constexpr static ActiveCloseErrorState empty() noexcept { return ActiveCloseErrorState{}; }
    /**
     * @param[in] other The other ActiveCloseErrorState.
     * @return Returns @b true if the two ActiveCloseErrorState objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const ActiveCloseErrorState& other) const noexcept
    {
        return _value == other._value && _error == other._error;
    }
    /**
     * @return Returns @b true if error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isError() const noexcept { return _value == ERROR; }
    /**
     * @return Returns @b true if active is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isActive() const noexcept { return _value == ACTIVE; }
    /**
     * @return Returns @b true if closed is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isClosed() const noexcept { return _value == CLOSED; }
    /**
     * @return Returns @b true if no error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * @return Returns the error value;
     */
    [[nodiscard]] constexpr ERROR_TYPE errorValue() const noexcept { return _error; }
    /**
     * @return Returns enum part of the error as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }

  private:
    std::uint8_t _value;
    ERROR_TYPE _error;
};

}  // namespace state
}  // namespace catta
