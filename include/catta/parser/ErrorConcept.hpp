#pragma once

// catta
#include <catta/EnumConcept.hpp>

namespace catta
{
namespace parser
{
/**
 * @brief ErrorConcept describes an interface for parsering errors. Is the same interface as EnumConcept.
 * @tparam T The class that is checked if it is parsering error type.
 *
 * Parsing error are represented by neum values. The errors are depend on the object reprensentation. So every parser has iths own possible errors.
 *
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept ErrorConcept = catta::EnumConcept<T>;
}  // namespace parser
}  // namespace catta
