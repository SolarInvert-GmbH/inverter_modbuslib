#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace state
{
/**
 * @brief Describes a trivail state error. Has only error or not error (empty) as enums. It implements the ErrorConcept.
 * @author CattaTech - Maik Urbannek
 */
class DefaultError
{
  private:
    constexpr static std::uint8_t ERROR = 0;
    constexpr static std::uint8_t EMPTY = 1;

  public:
    /**
     * @param[in] value The enum value of the error representation.
     * @warning This constructor should not be used. Use error() or empty(). Explicit constructor. Converts uint8 to error representation.
     */
    [[nodiscard]] constexpr explicit DefaultError(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates no error representation.
     */
    [[nodiscard]] constexpr DefaultError() noexcept : DefaultError(EMPTY) {}
    /**
     * @return Returns the running state.
     */
    [[nodiscard]] constexpr static DefaultError error() noexcept { return DefaultError{ERROR}; }
    /**
     * @return Returns the no error representation.
     */
    [[nodiscard]] constexpr static DefaultError empty() noexcept { return DefaultError{EMPTY}; }
    /**
     * @param[in] other The other DefaultError.
     * @return Returns @b true if the two DefaultError objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const DefaultError& other) const = default;
    /**
     * @return Returns error representation as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if running state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isError() const noexcept { return _value == ERROR; }
    /**
     * @return Returns @b true if no error representation is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Error representation in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"ERROR"};

  private:
    std::uint8_t _value;
};
}  // namespace state
}  // namespace catta
