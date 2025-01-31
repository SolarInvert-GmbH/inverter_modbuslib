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
    [[nodiscard]] constexpr Token() noexcept : Token(catta::modbus::TokenType::empty(), EMPTY_DATA) {}
    /**
     * @return Returns a start token.
     */
    [[nodiscard]] constexpr static Token start() noexcept { return {catta::modbus::TokenType::start(), EMPTY_DATA}; }
    /**
     * @param[in] value The function value.
     * @return Returns a function token.
     */
    [[nodiscard]] constexpr static Token function(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::function(), value}; }
    /**
     * @param[in] value The function value.
     * @return Returns a data token if input is valid, otherwise empty.
     */
    [[nodiscard]] constexpr static Token data(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::data(), value}; }
    /**
     * @param[in] value The function value.
     * @return Returns a exception token.
     */
    [[nodiscard]] constexpr static Token exception(const std::uint8_t value) noexcept { return {catta::modbus::TokenType::exception(), value}; }
    /**
     * @param[in] value The exception code value. Has to be 1, 2, 3 or 4, otherwise empty is returned.
     * @return Returns a exception code token if input is valid, otherwise empty.
     */
    [[nodiscard]] constexpr static Token code(const std::uint8_t value) noexcept
    {
        return value > 0 && value < 5 ? Token{catta::modbus::TokenType::code(), value} : empty();
    }
    /**
     * @return Returns an end token.
     */
    [[nodiscard]] constexpr static Token end() noexcept { return {catta::modbus::TokenType::end(), EMPTY_DATA}; }
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
    static constexpr std::uint8_t EMPTY_DATA = 0x0;
};
}  // namespace modbus
}  // namespace catta
