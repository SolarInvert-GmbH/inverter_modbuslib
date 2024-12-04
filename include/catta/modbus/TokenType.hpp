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
    constexpr static std::uint8_t START = 0;
    constexpr static std::uint8_t FUNCTION = 1;
    constexpr static std::uint8_t DATA = 2;
    constexpr static std::uint8_t EXCEPTION = 3;
    constexpr static std::uint8_t CODE = 4;
    constexpr static std::uint8_t END = 5;
    constexpr static std::uint8_t EMPTY = 6;

  public:
    /**
     * @param[in] value The enum value of the token.
     * @warning This constructor should not be used. Use start(), function(), data(), exception(), code(), end() or empty(). Explicit constructor.
     * Converts uint8 to token.
     */
    [[nodiscard]] constexpr explicit TokenType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid token type.
     */
    [[nodiscard]] constexpr TokenType() noexcept : TokenType(EMPTY) {}
    /**
     * @return Returns the start token.
     */
    [[nodiscard]] constexpr static TokenType start() noexcept { return TokenType{START}; }
    /**
     * @return Returns the function token.
     */
    [[nodiscard]] constexpr static TokenType function() noexcept { return TokenType{FUNCTION}; }
    /**
     * @return Returns the data token.
     */
    [[nodiscard]] constexpr static TokenType data() noexcept { return TokenType{DATA}; }
    /**
     * @return Returns the exception token.
     */
    [[nodiscard]] constexpr static TokenType exception() noexcept { return TokenType{EXCEPTION}; }
    /**
     * @return Returns the exeption code token.
     */
    [[nodiscard]] constexpr static TokenType code() noexcept { return TokenType{CODE}; }
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
     * @return Returns @b true if start token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isStart() const noexcept { return _value == START; }
    /**
     * @return Returns @b true if function token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFunction() const noexcept { return _value == FUNCTION; }
    /**
     * @return Returns @b true if data token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isData() const noexcept { return _value == DATA; }
    /**
     * @return Returns @b true if exception token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isException() const noexcept { return _value == EXCEPTION; }
    /**
     * @return Returns @b true if exeption code token is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCode() const noexcept { return _value == CODE; }
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
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"START", "FUNCTION", "DATA", "EXCEPTION", "CODE", "END"};

  private:
    std::uint8_t _value;
};
}  // namespace modbus
}  // namespace catta
