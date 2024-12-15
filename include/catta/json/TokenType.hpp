#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace json
{
/**
 * @brief Represents the possible json token types.
 * @author CattaTech - Maik Urbannek
 */
class TokenType
{
  private:
    constexpr static std::uint8_t OPEN_CURLY_BRACKET = 0;
    constexpr static std::uint8_t CLOSE_CURLY_BRACKET = 1;
    constexpr static std::uint8_t OPEN_SQUARE_BRACKET = 2;
    constexpr static std::uint8_t CLOSE_SQUARE_BRACKET = 3;
    constexpr static std::uint8_t COLON = 4;
    constexpr static std::uint8_t COMMA = 5;
    constexpr static std::uint8_t NULL_OBJECT = 6;
    constexpr static std::uint8_t BOOL_TRUE = 7;
    constexpr static std::uint8_t BOOL_FALSE = 8;
    constexpr static std::uint8_t INTEGER_NUMBER = 9;
    constexpr static std::uint8_t FLOAT_NUMBER = 10;
    constexpr static std::uint8_t OPEN_STRING = 11;
    constexpr static std::uint8_t CHARACTER = 12;
    constexpr static std::uint8_t CLOSE_STRING = 13;
    constexpr static std::uint8_t END = 14;
    constexpr static std::uint8_t ERROR_STATE = 15;
    constexpr static std::uint8_t EMPTY = 16;

  public:
    /**
     * @param[in] value The enum value of the token types.
     * @warning This constructor should not be used. Use openCurlyBracket(), closeCurlyBracket(), openSquareBracket(), closeSquareBracket(), colon(),
     * comma(), nullObject(), boolTrue(), boolFalse(), integerNumber(), floatNumber(), openString(), character(), closeString(), end(), error() or
     * empty(). Explicit constructor. Converts uint8 to token types.
     */
    [[nodiscard]] constexpr explicit TokenType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty token types.
     */
    [[nodiscard]] constexpr TokenType() noexcept : TokenType(EMPTY) {}
    /**
     * @return Returns the open curly bracket.
     */
    [[nodiscard]] constexpr static TokenType openCurlyBracket() noexcept { return TokenType{OPEN_CURLY_BRACKET}; }
    /**
     * @return Returns the close curly bracket.
     */
    [[nodiscard]] constexpr static TokenType closeCurlyBracket() noexcept { return TokenType{CLOSE_CURLY_BRACKET}; }
    /**
     * @return Returns the open square bracket.
     */
    [[nodiscard]] constexpr static TokenType openSquareBracket() noexcept { return TokenType{OPEN_SQUARE_BRACKET}; }
    /**
     * @return Returns the close square bracket.
     */
    [[nodiscard]] constexpr static TokenType closeSquareBracket() noexcept { return TokenType{CLOSE_SQUARE_BRACKET}; }
    /**
     * @return Returns the colon.
     */
    [[nodiscard]] constexpr static TokenType colon() noexcept { return TokenType{COLON}; }
    /**
     * @return Returns the comma.
     */
    [[nodiscard]] constexpr static TokenType comma() noexcept { return TokenType{COMMA}; }
    /**
     * @return Returns the null object.
     */
    [[nodiscard]] constexpr static TokenType nullObject() noexcept { return TokenType{NULL_OBJECT}; }
    /**
     * @return Returns the true.
     */
    [[nodiscard]] constexpr static TokenType boolTrue() noexcept { return TokenType{BOOL_TRUE}; }
    /**
     * @return Returns the false.
     */
    [[nodiscard]] constexpr static TokenType boolFalse() noexcept { return TokenType{BOOL_FALSE}; }
    /**
     * @return Returns the integer number.
     */
    [[nodiscard]] constexpr static TokenType integerNumber() noexcept { return TokenType{INTEGER_NUMBER}; }
    /**
     * @return Returns the float number.
     */
    [[nodiscard]] constexpr static TokenType floatNumber() noexcept { return TokenType{FLOAT_NUMBER}; }
    /**
     * @return Returns the open string.
     */
    [[nodiscard]] constexpr static TokenType openString() noexcept { return TokenType{OPEN_STRING}; }
    /**
     * @return Returns the character.
     */
    [[nodiscard]] constexpr static TokenType character() noexcept { return TokenType{CHARACTER}; }
    /**
     * @return Returns the close string.
     */
    [[nodiscard]] constexpr static TokenType closeString() noexcept { return TokenType{CLOSE_STRING}; }
    /**
     * @return Returns the end.
     */
    [[nodiscard]] constexpr static TokenType end() noexcept { return TokenType{END}; }
    /**
     * @return Returns the error.
     */
    [[nodiscard]] constexpr static TokenType error() noexcept { return TokenType{ERROR_STATE}; }
    /**
     * @return Returns the empty token types.
     */
    [[nodiscard]] constexpr static TokenType empty() noexcept { return TokenType{EMPTY}; }
    /**
     * @param[in] other The other TokenType.
     * @return Returns @b true if the two TokenType objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const TokenType& other) const = default;
    /**
     * @return Returns token types as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if open curly bracket is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isOpenCurlyBracket() const noexcept { return _value == OPEN_CURLY_BRACKET; }
    /**
     * @return Returns @b true if close curly bracket is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCloseCurlyBracket() const noexcept { return _value == CLOSE_CURLY_BRACKET; }
    /**
     * @return Returns @b true if open square bracket is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isOpenSquareBracket() const noexcept { return _value == OPEN_SQUARE_BRACKET; }
    /**
     * @return Returns @b true if close square bracket is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCloseSquareBracket() const noexcept { return _value == CLOSE_SQUARE_BRACKET; }
    /**
     * @return Returns @b true if colon is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isColon() const noexcept { return _value == COLON; }
    /**
     * @return Returns @b true if comma is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isComma() const noexcept { return _value == COMMA; }
    /**
     * @return Returns @b true if null object is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isNullObject() const noexcept { return _value == NULL_OBJECT; }
    /**
     * @return Returns @b true if true is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBoolTrue() const noexcept { return _value == BOOL_TRUE; }
    /**
     * @return Returns @b true if false is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBoolFalse() const noexcept { return _value == BOOL_FALSE; }
    /**
     * @return Returns @b true if integer number is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isIntegerNumber() const noexcept { return _value == INTEGER_NUMBER; }
    /**
     * @return Returns @b true if float number is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFloatNumber() const noexcept { return _value == FLOAT_NUMBER; }
    /**
     * @return Returns @b true if open string is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isOpenString() const noexcept { return _value == OPEN_STRING; }
    /**
     * @return Returns @b true if character is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCharacter() const noexcept { return _value == CHARACTER; }
    /**
     * @return Returns @b true if close string is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCloseString() const noexcept { return _value == CLOSE_STRING; }
    /**
     * @return Returns @b true if end is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEnd() const noexcept { return _value == END; }
    /**
     * @return Returns @b true if error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isError() const noexcept { return _value == ERROR_STATE; }
    /**
     * @return Returns @b true if empty token types is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Token types in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"OPEN_CURLY_BRACKET",
                                                                      "CLOSE_CURLY_BRACKET",
                                                                      "OPEN_SQUARE_BRACKET",
                                                                      "CLOSE_SQUARE_BRACKET",
                                                                      "COLON",
                                                                      "COMMA",
                                                                      "NULL_OBJECT",
                                                                      "BOOL_TRUE",
                                                                      "BOOL_FALSE",
                                                                      "INTEGER_NUMBER",
                                                                      "FLOAT_NUMBER",
                                                                      "OPEN_STRING",
                                                                      "CHARACTER",
                                                                      "CLOSE_STRING",
                                                                      "END",
                                                                      "ERROR"};

  private:
    std::uint8_t _value;
};
}  // namespace json
}  // namespace catta
