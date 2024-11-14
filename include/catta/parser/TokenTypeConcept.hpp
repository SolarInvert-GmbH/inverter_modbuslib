#pragma once

// catta
#include <catta/EnumConcept.hpp>

namespace catta
{
namespace parser
{
/**
 * @brief TokenTypeConcept describes an interface for parser token type. A token type is an enum type.
 * @tparam T The class that is checked if it is parser token type.
 *
 * Token are needed for parsing sequences of elements. Each element is represented by a token. The token type represents the different possible token.
 * Every token type must have error and end as enum. Error represents an parsing error token. End represents the last token (sequence/stream ended).
 *
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept TokenTypeConcept = requires(const T& type)
{
    catta::EnumConcept<T>;
    {
        type.isError()
        } -> std::same_as<bool>;
    {
        type.isEnd()
        } -> std::same_as<bool>;
};
}  // namespace parser
}  // namespace catta
