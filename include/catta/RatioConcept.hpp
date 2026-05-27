#pragma once

// std
#include <concepts>
#include <ratio>

namespace catta
{
/**
 * @brief RatioConcept is satisfied if T is a std::ratio.
 * @tparam T The class that is checked if it is a std::ratio.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept RatioConcept = requires(const T& t0, const T& t1)
{
    std::same_as<std::ratio<T::num, T::den>, T>;
};
}  // namespace catta
