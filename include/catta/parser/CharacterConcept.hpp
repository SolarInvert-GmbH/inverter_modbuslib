#pragma once

// std
#include <concepts>
#include <cstdint>

namespace catta
{
namespace parser
{
/**
 * @brief CharacterConcept describes possible parser character types. Can be char, std::uint8_t, char8_t or char32_t.
 * @tparam T The class that is checked if it is char, std::uint8_t, char8_t or char32_t.
 *
 * Character are possible type for input (and sometimes output) in parser.
 *
 * char is ascii encoded.
 * std::uint8_t (aka byte) is binary encoded.
 * char8_t is utf8 encoded unicode.
 * char32_t is utf32 encoded unicode.
 *
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept CharacterConcept = std::same_as<char, T> || std::same_as<std::uint8_t, T> || std::same_as<char8_t, T> || std::same_as<char32_t, T>;
}  // namespace parser
}  // namespace catta
