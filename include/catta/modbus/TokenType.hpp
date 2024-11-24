#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
/**
 * @brief Represents the token type.
 * @author CattaTech - Maik Urbannek
 */
class TokenType
{
  private:
    constexpr static std::uint8_t ADDRESS = 0;
    constexpr static std::uint8_t FUNCTION = 1;
    constexpr static std::uint8_t LENGTH = 2;
    constexpr static std::uint8_t DATA = 3;
    constexpr static std::uint8_t END = 4;
    constexpr static std::uint8_t EMPTY = 5;

  public:
    /**
     * @param[in] value The enum value of the token.
     * @warning This constructor should not be used. Use address(), function(), length(), data(), end() or empty(). Explicit constructor. Converts
     * uint8 to token.
     */
    [[nodiscard]] constexpr explicit TokenType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid token type.
     */
    [[nodiscard]] constexpr TokenType() noexcept : TokenType(EMPTY) {}
    /**
     * @return Returns the address token.
     */
    [[nodiscard]] constexpr static TokenType address() noexcept { return TokenType{ADDRESS}; }
    /**
     * @return Returns the function token.
     */
    [[nodiscard]] constexpr static TokenType function() noexcept { return TokenType{FUNCTION}; }
    /**
     * @return Returns the length token.
     */
    [[nodiscard]] constexpr static TokenType length() noexcept { return TokenType{LENGTH}; }
    /**
     * @return Returns the data token.
     */
    [[nodiscard]] constexpr static TokenType data() noexcept { return TokenType{DATA}; }
    /**
     * @return Returns the end token.
     */
    [[nodiscard]] constexpr static TokenType end() noexcept { return TokenType{END}; }
    /**
     * @return Returns the invalid token type.
     */
    [[nodiscard]] constexpr static TokenType empty() noexcept { return TokenType{EMPTY}; }
    /**
     * @param[in] other The other TokenType.
     * @return Returns @b true if the two TokenType objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const TokenType& other) const = default;
    /**
     * @return Returns token as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if address token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isAddress() const noexcept { return _value == ADDRESS; }
    /**
     * @return Returns @b true if function token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFunction() const noexcept { return _value == FUNCTION; }
    /**
     * @return Returns @b true if length token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isLength() const noexcept { return _value == LENGTH; }
    /**
     * @return Returns @b true if data token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isData() const noexcept { return _value == DATA; }
    /**
     * @return Returns @b true if end token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEnd() const noexcept { return _value == END; }
    /**
     * @return Returns @b true if invalid token type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Token in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"ADDRESS", "FUNCTION", "LENGTH", "DATA", "END"};

  private:
    std::uint8_t _value;
};
}  // namespace modbus
}  // namespace catta
