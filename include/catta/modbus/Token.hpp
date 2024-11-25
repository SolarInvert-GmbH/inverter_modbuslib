#pragma once

// modbus
#include <catta/modbus/TokenType.hpp>

namespace catta
{
namespace modbus
{
/**
 * @brief Represents the modbus token.
 *
 * @author CattaTech - Maik Urbannek
 */
class Token
{
  public:
    /**
     * Default constructor. Creates empty token.
     */
    [[nodiscard]] constexpr Token() noexcept : Token(catta::modbus::TokenType::empty(), NO_DATA) {}
    /**
     * @param[in] value The address value.
     * @return Returns an address token.
     */
    [[nodiscard]] constexpr static Token address(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::address(), value}; }
    /**
     * @param[in] value The function value.
     * @return Returns a function token.
     */
    [[nodiscard]] constexpr static Token function(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::function(), value}; }
    /**
     * @param[in] value The length value.
     * @return Returns a length token.
     */
    [[nodiscard]] constexpr static Token length(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::length(), value}; }
    /**
     * @param[in] value The function value. Has to be smaller than 253, otherwise empty is returned.
     * @return Returns a data token if input is valid, otherwise empty.
     */
    [[nodiscard]] constexpr static Token data(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::data(), value}; }
    /**
     * @return Returns an end token.
     */
    [[nodiscard]] constexpr static Token end() noexcept { return {catta::modbus::TokenType::end(), NO_DATA}; }
    /**
     * @return Returns an empty token.
     */
    [[nodiscard]] constexpr static Token empty() noexcept { return {}; }
    /**
     * @return Returns the value, only valid for address, function, length or data.
     */
    [[nodiscard]] constexpr std::uint8_t value() const noexcept { return _value; }
    /**
     * @return Returns the type.
     */
    [[nodiscard]] constexpr catta::modbus::TokenType type() const noexcept { return _type; }
    /**
     * @return Returns @b true if the token is empty, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _type.isEmpty(); }
    /**
     * @param[in] other The other Token.
     * @return Returns @b true if the two Token objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Token& other) const = default;

  private:
    constexpr Token(const catta::modbus::TokenType type, const std::uint8_t value) : _type(type), _value(value) {}
    catta::modbus::TokenType _type;
    std::uint8_t _value;
    static constexpr std::uint8_t NO_DATA = 0x0;
};
}  // namespace modbus
}  // namespace catta
