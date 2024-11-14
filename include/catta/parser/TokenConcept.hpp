#pragma once

// catta
#include <catta/parser/ErrorConcept.hpp>
#include <catta/parser/TokenTypeConcept.hpp>

namespace catta
{
namespace parser
{
/**
 * @brief TokenConcept describes an interface for parsering token.
 * @tparam T The class that is checked if it is parsering token.
 *
 * Token are needed for parsing sequences of elements. Each element is represented by a token.
 *
 * The token implementations must be equality comparable (== and != mus be implemented). The token also need an errorValue() methode that return an
 * error that implements an ErrorConcept and an type() methode that return a type that implements a TokenTypeConcept.
 *
 * @see SequenceParserConcept
 * @see ErrorConcept
 * @see TokenTypeConcept
 *
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept TokenConcept = requires(const T& token)
{
    std::equality_comparable<T>;
    {
        token.errorValue()
        } -> ErrorConcept<>;
    {
        token.type()
        } -> TokenTypeConcept<>;
};
}  // namespace parser
}  // namespace catta
