#pragma once

// string
#include <catta/fromstring/fromString.hpp>
#include <catta/tostring/toString.hpp>

// random
#include <catta/random/Random.hpp>

// test
#include <catta/test/Test.hpp>

namespace catta
{
namespace test
{
/**
 * Tests one random T object. Move the randombject to another object.
 * @param[in] test The test object.
 * @tparam T The class for which the test performed for.
 * @tparam checkIfMovedObjectIsEmpty If true, it is tested that the object ist empty after it was moved from.
 * @tparam OUTPUT The output class for the test.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool checkIfMovedObjectIsEmpty>
requires catta::tostring::Nameable<T> && catta::random::Randomable<T>
bool checkCopyMove(catta::test::Test<OUTPUT>& test)
{
    const auto getName = []()
    {
        const auto view = catta::tostring::GetName<T>::name;
        return std::string(view.data(), view.size());
    };
    catta::random::Random& random = test.random();
    const T orginal0 = random.create<T>();
    const T orginal1 = random.create<T>();
    const auto assignAndCheck = [&test, &getName](T& assign, const T& original) -> bool
    {
        assign = original;
        if (assign != original) return test.failedExpectedSafe(original, assign, getName() + " copy result");
        return true;
    };
    const auto moveAndCheck = [&assignAndCheck, &test, &getName](T& target, T& source, const T& original)
    {
        if (!assignAndCheck(source, original)) return false;
        target = std::move(source);
        if (target != original) return test.failedExpectedSafe(original, target, getName() + " move target");
        if (checkIfMovedObjectIsEmpty)
        {
            if (source != T{}) return test.failedExpectedSafe(T{}, source, getName() + " move source");
        }
        return true;
    };

    T a;
    T b;
    if (!assignAndCheck(a, orginal0) || !assignAndCheck(a, orginal1) || !assignAndCheck(a, T{})) return false;
    if (!moveAndCheck(a, b, T{}) || !moveAndCheck(a, b, orginal0)) return false;
    return true;
}

/**
 * checkCopyMove() will not check for empty object after move.
 */
static constexpr bool NO_CHECK = false;

/**
 * checkCopyMove() will check for empty object after move.
 */
static constexpr bool CHECK_EMPTY = true;

}  // namespace test
}  // namespace catta
