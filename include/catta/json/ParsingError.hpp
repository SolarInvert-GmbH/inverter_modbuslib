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
 * @brief Represents the possible json parsing errors.
 * @author CattaTech - Maik Urbannek
 */
class ParsingError
{
  private:
    constexpr static std::uint8_t UNEXPECTED_LITERAL = 0;
    constexpr static std::uint8_t BAD_FORMED_NUMBER = 1;
    constexpr static std::uint8_t ACSII_CONTROL_NOT_ALLOWED = 2;
    constexpr static std::uint8_t BAD_FORMED_UTF8_STRING = 3;
    constexpr static std::uint8_t UNKNOWN_ESCAPE_SEQUENCE = 4;
    constexpr static std::uint8_t BAD_ESCAPE_UNICODE_SEQUENCE = 5;
    constexpr static std::uint8_t STRING_NOT_CLOSED = 6;
    constexpr static std::uint8_t INTERNAL_PARSER_ERROR = 7;
    constexpr static std::uint8_t JSON_ENDED = 8;
    constexpr static std::uint8_t EMPTY = 9;

  public:
    /**
     * @param[in] value The enum value of the parsing error.
     * @warning This constructor should not be used. Use unexpectedLiteral(), badFormedNumber(), acsiiControlNotAllowed(), badFormedUtf8String(),
     * unknownEscapeSequence(), badEscapeUnicodeSequence(), stringNotClosed(), internalParserError(), jsonEnded() or empty(). Explicit constructor.
     * Converts uint8 to parsing error.
     */
    [[nodiscard]] constexpr explicit ParsingError(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty parsing error.
     */
    [[nodiscard]] constexpr ParsingError() noexcept : ParsingError(EMPTY) {}
    /**
     * @return Returns the the unexpected literal error (Is created if a not known literal is parsed. Known are 'true', 'false' and 'null').
     */
    [[nodiscard]] constexpr static ParsingError unexpectedLiteral() noexcept { return ParsingError{UNEXPECTED_LITERAL}; }
    /**
     * @return Returns the the bad formed number error (Is created if a number is illformed. For example '1.1.1'.).
     */
    [[nodiscard]] constexpr static ParsingError badFormedNumber() noexcept { return ParsingError{BAD_FORMED_NUMBER}; }
    /**
     * @return Returns the the ascii control not allowed error (Is created if control character (0x00…0x1F) is used in a string. Use for example
     * '\\u000a' or '\\n' instead of newline in string.).
     */
    [[nodiscard]] constexpr static ParsingError acsiiControlNotAllowed() noexcept { return ParsingError{ACSII_CONTROL_NOT_ALLOWED}; }
    /**
     * @return Returns the the bad formed utf8 string error (Is created if a string is no valid utf8).
     */
    [[nodiscard]] constexpr static ParsingError badFormedUtf8String() noexcept { return ParsingError{BAD_FORMED_UTF8_STRING}; }
    /**
     * @return Returns the the unknown escape sequence error (Is created if a not known escape sequence is used in an string. Known are '\\\\', '\\/',
     * '\\b', '\\f', '\\n', '\\r', '\\t' and '\\uhhhh' (h is in [0…9a…fA…F])).
     */
    [[nodiscard]] constexpr static ParsingError unknownEscapeSequence() noexcept { return ParsingError{UNKNOWN_ESCAPE_SEQUENCE}; }
    /**
     * @return Returns the the bad escape unicode sequence error (Is created if one or two '\\uhhhh' (h is in [0…9a…fA…F]) are illformed (no valid
     * utf16)).
     */
    [[nodiscard]] constexpr static ParsingError badEscapeUnicodeSequence() noexcept { return ParsingError{BAD_ESCAPE_UNICODE_SEQUENCE}; }
    /**
     * @return Returns the the string not closed error (Is created if the string file ends with missing closed string).
     */
    [[nodiscard]] constexpr static ParsingError stringNotClosed() noexcept { return ParsingError{STRING_NOT_CLOSED}; }
    /**
     * @return Returns the the internal parser error (Should not be created).
     */
    [[nodiscard]] constexpr static ParsingError internalParserError() noexcept { return ParsingError{INTERNAL_PARSER_ERROR}; }
    /**
     * @return Returns the the json ended error (Is created if catta::json::TokenParser::read() is called after end token).
     */
    [[nodiscard]] constexpr static ParsingError jsonEnded() noexcept { return ParsingError{JSON_ENDED}; }
    /**
     * @return Returns the empty parsing error.
     */
    [[nodiscard]] constexpr static ParsingError empty() noexcept { return ParsingError{EMPTY}; }
    /**
     * @param[in] other The other ParsingError.
     * @return Returns @b true if the two ParsingError objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const ParsingError& other) const = default;
    /**
     * @return Returns parsing error as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if the unexpected literal error (Is created if a not known literal is parsed. Known are 'true', 'false' and 'null') is
     * represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUnexpectedLiteral() const noexcept { return _value == UNEXPECTED_LITERAL; }
    /**
     * @return Returns @b true if the bad formed number error (Is created if a number is illformed. For example '1.1.1'.) is represented, otherwise @b
     * false.
     */
    [[nodiscard]] constexpr bool isBadFormedNumber() const noexcept { return _value == BAD_FORMED_NUMBER; }
    /**
     * @return Returns @b true if the ascii control not allowed error (Is created if control character (0x00…0x1F) is used in a string. Use for
     * example
     * '\\u000a' or '\\n' instead of newline in string.) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isAcsiiControlNotAllowed() const noexcept { return _value == ACSII_CONTROL_NOT_ALLOWED; }
    /**
     * @return Returns @b true if the bad formed utf8 string error (Is created if a string is no valid utf8) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBadFormedUtf8String() const noexcept { return _value == BAD_FORMED_UTF8_STRING; }
    /**
     * @return Returns @b true if the unknown escape sequence error (Is created if a not known escape sequence is used in an string. Known are '\\\\',
     * '\\/',
     * '\\b', '\\f', '\\n', '\\r', '\\t' and '\\uhhhh' (h is in [0…9a…fA…F])) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUnknownEscapeSequence() const noexcept { return _value == UNKNOWN_ESCAPE_SEQUENCE; }
    /**
     * @return Returns @b true if the bad escape unicode sequence error (Is created if one or two '\\uhhhh' (h is in [0…9a…fA…F]) are illformed (no
     * valid utf16)) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBadEscapeUnicodeSequence() const noexcept { return _value == BAD_ESCAPE_UNICODE_SEQUENCE; }
    /**
     * @return Returns @b true if the string not closed error (Is created if the string file ends with missing closed string) is represented,
     * otherwise @b false.
     */
    [[nodiscard]] constexpr bool isStringNotClosed() const noexcept { return _value == STRING_NOT_CLOSED; }
    /**
     * @return Returns @b true if the internal parser error (Should not be created) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInternalParserError() const noexcept { return _value == INTERNAL_PARSER_ERROR; }
    /**
     * @return Returns @b true if the json ended error (Is created if catta::json::TokenParser::read() is called after end token) is represented,
     * otherwise @b false.
     */
    [[nodiscard]] constexpr bool isJsonEnded() const noexcept { return _value == JSON_ENDED; }
    /**
     * @return Returns @b true if empty parsing error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Parsing error in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {
        "UNEXPECTED_LITERAL",     "BAD_FORMED_NUMBER",       "ACSII_CONTROL_NOT_ALLOWED",
        "BAD_FORMED_UTF8_STRING", "UNKNOWN_ESCAPE_SEQUENCE", "BAD_ESCAPE_UNICODE_SEQUENCE",
        "STRING_NOT_CLOSED",      "INTERNAL_PARSER_ERROR",   "JSON_ENDED"};

  private:
    std::uint8_t _value;
};
}  // namespace json
}  // namespace catta
