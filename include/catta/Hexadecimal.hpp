#pragma once

// std
#include <concepts>
#include <cstdint>
#include <optional>

namespace catta
{
/**
 * @brief A wrapper for integer to indicate that the integer is represented as hexadecimal number.
 * @tparam INTEGRAL One of the eight integer types.
 * @author CattaTech - Maik Urbannek
 * @see Helper functions: isValidHalfByte(), hexadecimalToHalfByte() or halfByteToHexadecimal().
 */
template <std::integral INTEGRAL>
class Hexadecimal
{
  public:
    /**
     * Constructor.
     * @param[in] integral The input integer.
     */
    constexpr explicit Hexadecimal(const INTEGRAL integral) : _integral(integral) {}
    /**
     * Default constructor.
     */
    constexpr Hexadecimal() : Hexadecimal(0) {}
    /**
     * @return Returns the hexadecimal as raw integer.
     */
    constexpr explicit operator INTEGRAL() const { return _integral; }
    /**
     * @param[in] other The other Hexadecimal.
     * @return Returns @b true if the two Hexadecimal objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Hexadecimal& other) const { return this->_integral == other._integral; }
    /**
     * @param[in] other The other Hexadecimal.
     * @return Returns @b true if the two Hexadecimal objects are not the same, otherwise @b false.
     */
    constexpr bool operator!=(const Hexadecimal& other) const { return !(*this == other); }

  private:
    INTEGRAL _integral;
};

/**
 * @param[in] i Input byte.
 * @return Returns @b true if input byte i is a valid halfbyte (0x0 … 0xf), otherwise @b false.
 */
constexpr bool isValidHalfByte(const std::uint8_t i) { return (i & 0xf0) == 0x00; }

/**
 * @param[in] c Input character. Has to be hexadecimal character '0'…'9','a'…'f' or 'A'…'F' (otherwise empty is returned).
 * @return Converts hexadecimal character '0'…'9','a'…'f' or 'A'…'F' to coresponding halfbyte and other character to empty.
 * @see Inverse to halfByteToHexadecimal();
 */
constexpr std::optional<std::uint8_t> hexadecimalToHalfByte(const char c)
{
    switch (c)
    {
        case '0':
            return 0x0;
        case '1':
            return 0x1;
        case '2':
            return 0x2;
        case '3':
            return 0x3;
        case '4':
            return 0x4;
        case '5':
            return 0x5;
        case '6':
            return 0x6;
        case '7':
            return 0x7;
        case '8':
            return 0x8;
        case '9':
            return 0x9;
        case 'a':
        case 'A':
            return 0xa;
        case 'b':
        case 'B':
            return 0xb;
        case 'c':
        case 'C':
            return 0xc;
        case 'd':
        case 'D':
            return 0xd;
        case 'e':
        case 'E':
            return 0xe;
        case 'f':
        case 'F':
            return 0xf;
        default:
            return std::optional<std::uint8_t>{};
    }
}

/**
 * @param[in] c Input character. Has to be hexadecimal character '0'…'9','a'…'f' or 'A'…'F' (otherwise empty is returned).
 * @return Converts hexadecimal character '0'…'9','a'…'f' or 'A'…'F' to coresponding halfbyte and other character to empty.
 * @see Inverse to halfByteToHexadecimal();
 */
constexpr std::optional<std::uint8_t> hexadecimalToHalfByte(const char8_t c) { return hexadecimalToHalfByte(static_cast<char>(c)); }

/**
 * @param[in] c Input character. Has to be hexadecimal character '0'…'9','a'…'f' or 'A'…'F' (otherwise empty is returned).
 * @return Converts hexadecimal character '0'…'9','a'…'f' or 'A'…'F' to coresponding halfbyte and other character to empty.
 * @see Inverse to halfByteToHexadecimal();
 */
constexpr std::optional<std::uint8_t> hexadecimalToHalfByte(const char16_t c)
{
    return (c > 0xff) ? std::optional<std::uint8_t>{} : hexadecimalToHalfByte(static_cast<char>(c));
}

/**
 * @param[in] c Input character. Has to be hexadecimal character '0'…'9','a'…'f' or 'A'…'F' (otherwise empty is returned).
 * @return Converts hexadecimal character '0'…'9','a'…'f' or 'A'…'F' to coresponding halfbyte and other character to empty.
 * @see Inverse to halfByteToHexadecimal();
 */
constexpr std::optional<std::uint8_t> hexadecimalToHalfByte(const char32_t c)
{
    return (c > 0xff) ? std::optional<std::uint8_t>{} : hexadecimalToHalfByte(static_cast<char>(c));
}

/**
 * @param[in] i Input half byte. The upper four bits are ignored.
 * @return Converts a half byte 0x0…0xf (upper four bits are ignored) to coresponding hexadecimal character '0'…'9','a'…'f' or 'A'…'F'.
 * @see Inverse to hexadecimalToHalfByte();
 */
constexpr char halfByteToHexadecimal(const std::uint8_t i)
{
    switch (i & 0xf)
    {
        case 0x0:
            return '0';
        case 0x1:
            return '1';
        case 0x2:
            return '2';
        case 0x3:
            return '3';
        case 0x4:
            return '4';
        case 0x5:
            return '5';
        case 0x6:
            return '6';
        case 0x7:
            return '7';
        case 0x8:
            return '8';
        case 0x9:
            return '9';
        case 0xa:
            return 'a';
        case 0xb:
            return 'b';
        case 0xc:
            return 'c';
        case 0xd:
            return 'd';
        case 0xe:
            return 'e';
        default:
            return 'f';
    }
}

}  // namespace catta
