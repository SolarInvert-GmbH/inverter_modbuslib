#pragma once

// json
#include <catta/json/ParsingError.hpp>
#include <catta/json/TokenType.hpp>

// std
#include <bit>
#include <cstdint>

namespace catta
{
namespace json
{
/**
 * @brief Represents the smalles results of the lexical analysis of json files.
 *
 * @author CattaTech - Maik Urbannek
 */
class Token
{
  public:
    /**
     * Default constructor. Creates empty token.
     */
    [[nodiscard]] constexpr Token() noexcept : Token(catta::json::TokenType::empty(), NO_VALUE) {}
    /**
     * @return Returns an open curly bracket token '{'.
     */
    [[nodiscard]] constexpr static Token openCurlyBracket() noexcept { return {catta::json::TokenType::openCurlyBracket(), NO_VALUE}; }
    /**
     * @return Returns a close curly bracket token '}'.
     */
    [[nodiscard]] constexpr static Token closeCurlyBracket() noexcept { return {catta::json::TokenType::closeCurlyBracket(), NO_VALUE}; }
    /**
     * @return Returns an open square bracket token '['.
     */
    [[nodiscard]] constexpr static Token openSquareBracket() noexcept { return {catta::json::TokenType::openSquareBracket(), NO_VALUE}; }
    /**
     * @return Returns a close square bracket token ']'.
     */
    [[nodiscard]] constexpr static Token closeSquareBracket() noexcept { return {catta::json::TokenType::closeSquareBracket(), NO_VALUE}; }
    /**
     * @return Returns a colon token ':'.
     */
    [[nodiscard]] constexpr static Token colon() noexcept { return {catta::json::TokenType::colon(), NO_VALUE}; }
    /**
     * @return Returns a comma token ','.
     */
    [[nodiscard]] constexpr static Token comma() noexcept { return {catta::json::TokenType::comma(), NO_VALUE}; }
    /**
     * @return Returns a null token 'null'.
     */
    [[nodiscard]] constexpr static Token nullObject() noexcept { return {catta::json::TokenType::nullObject(), NO_VALUE}; }
    /**
     * @return Returns a true token 'true'.
     */
    [[nodiscard]] constexpr static Token boolTrue() noexcept { return {catta::json::TokenType::boolTrue(), NO_VALUE}; }
    /**
     * @return Returns a false token 'false'.
     */
    [[nodiscard]] constexpr static Token boolFalse() noexcept { return {catta::json::TokenType::boolFalse(), NO_VALUE}; }
    /**
     * @param[in] value The integer value of the token.
     * @return Returns the integer token with the given value. For example '42'.
     */
    [[nodiscard]] constexpr static Token integerNumber(const std::int64_t value) noexcept
    {
        return {catta::json::TokenType::integerNumber(), std::bit_cast<std::uint64_t>(value)};
    }
    /**
     * @param[in] value The float value of the token.
     * @return Returns the float token with the given value. For example '42.0'.
     */
    [[nodiscard]] constexpr static Token floatNumber(const double value) noexcept
    {
        return {catta::json::TokenType::floatNumber(), std::bit_cast<std::uint64_t>(value)};
    }
    /**
     * @return Returns an open string token '"'.
     */
    [[nodiscard]] constexpr static Token openString() noexcept { return {catta::json::TokenType::openString(), NO_VALUE}; }
    /**
     * @param[in] value The unicode character of the token.
     * @return Returns a unicode character token with the given value. For example 'a#, '🐒', '\\n' or '\\u000a'.
     */
    [[nodiscard]] constexpr static Token character(const char32_t value) noexcept
    {
        return {catta::json::TokenType::character(), static_cast<std::uint64_t>(value)};
    }
    /**
     * @return Returns a close string token '"'.
     */
    [[nodiscard]] constexpr static Token closeString() noexcept { return {catta::json::TokenType::closeString(), NO_VALUE}; }
    /**
     * @return Returns an end token '\0'.
     */
    [[nodiscard]] constexpr static Token end() noexcept { return {catta::json::TokenType::end(), NO_VALUE}; }
    /**
     * @param[in] value The error value of the token.
     * @return Returns an error token with the given value if the error is not empty, otherwise an empty token.
     */
    [[nodiscard]] constexpr static Token error(const catta::json::ParsingError value) noexcept
    {
        return value.isEmpty() ? empty() : Token{catta::json::TokenType::error(), static_cast<std::uint64_t>(value)};
    }
    /**
     * @return Returns an empty token.
     */
    [[nodiscard]] constexpr static Token empty() noexcept { return Token{}; }
    /**
     * @return Returns the integer value if type() is Type::integerNumber(), otherwise 0.
     */
    [[nodiscard]] constexpr std::int64_t integerValue() const noexcept { return std::bit_cast<std::int64_t>(_data); }
    /**
     * @return Returns the float value if type() is Type::floatNumber(), otherwise 0.0.
     */
    [[nodiscard]] constexpr double floatValue() const noexcept { return std::bit_cast<double>(_data); }
    /**
     * @return Returns the unicode character if type() is Type::character(), otherwise an empty unicode character.
     */
    [[nodiscard]] constexpr char32_t unicodeCharacterValue() const noexcept { return static_cast<char32_t>(_data); }
    /**
     * @return Returns the error if type() is Type::error(), otherwise an empty error.
     */
    [[nodiscard]] constexpr catta::json::ParsingError errorValue() const noexcept
    {
        return catta::json::ParsingError(static_cast<std::uint8_t>(_data));
    }
    /**
     * @return Returns @b true if the token is empty, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _type.isEmpty(); }
    /**
     * @return Returns the type of the token.
     */
    [[nodiscard]] constexpr catta::json::TokenType type() const noexcept { return _type; }
    /**
     * @param[in] other The other Token.
     * @return Returns @b true if the two Token objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Token& other) const noexcept = default;

  private:
    constexpr Token(const catta::json::TokenType type, const std::uint64_t data) : _type(type), _data(data) {}
    catta::json::TokenType _type;
    std::uint64_t _data;
    static constexpr std::uint64_t NO_VALUE = 0x0;
};

}  // namespace json
}  // namespace catta
