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
 * @brief Describes a trivail parser token type. Has only value, end, error and empty as enums. It implements the TokenTypeConcept.
 * @author CattaTech - Maik Urbannek
 */
class DefaultTokenType
{
  private:
    constexpr static std::uint8_t VALUE = 0;
    constexpr static std::uint8_t END = 1;
    constexpr static std::uint8_t ERROR_TYPE = 2;
    constexpr static std::uint8_t EMPTY = 3;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use value(), end(), error() or empty(). Explicit constructor. Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit DefaultTokenType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty type.
     */
    [[nodiscard]] constexpr DefaultTokenType() noexcept : DefaultTokenType(EMPTY) {}
    /**
     * @return Returns the value type.
     */
    [[nodiscard]] constexpr static DefaultTokenType value() noexcept { return DefaultTokenType{VALUE}; }
    /**
     * @return Returns the end type.
     */
    [[nodiscard]] constexpr static DefaultTokenType end() noexcept { return DefaultTokenType{END}; }
    /**
     * @return Returns the error type.
     */
    [[nodiscard]] constexpr static DefaultTokenType error() noexcept { return DefaultTokenType{ERROR_TYPE}; }
    /**
     * @return Returns the empty type.
     */
    [[nodiscard]] constexpr static DefaultTokenType empty() noexcept { return DefaultTokenType{EMPTY}; }
    /**
     * @param[in] other The other DefaultTokenType.
     * @return Returns @b true if the two DefaultTokenType objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const DefaultTokenType& other) const = default;
    /**
     * @return Returns type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if value type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isValue() const noexcept { return _value == VALUE; }
    /**
     * @return Returns @b true if end type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEnd() const noexcept { return _value == END; }
    /**
     * @return Returns @b true if error type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isError() const noexcept { return _value == ERROR_TYPE; }
    /**
     * @return Returns @b true if empty type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"VALUE", "END", "ERROR"};

  private:
    std::uint8_t _value;
};
}  // namespace parser
}  // namespace catta
