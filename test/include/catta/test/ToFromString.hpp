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
 * Tests one random T object. Creates const string from the random object and parses the string. The result object should be the same as the
 * randomcreated one.
 * @param[in] test The test object.
 * @tparam OUTPUT The output class for the test.
 * @tparam T The class for which the test performed for.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool DEBUG = false>
requires catta::tostring::ToStringable<T> && catta::fromstring::Parsable<T> && catta::tostring::Nameable<T> && catta::random::Randomable<T>
bool checkToFromString(catta::test::Test<OUTPUT>& test)
{
    catta::random::Random& random = test.random();
    const T input = random.create<T>();
    const auto serial = catta::tostring::toString(input);
    if (DEBUG) test.status(serial);
    const T output = catta::fromstring::fromString<T>(serial.data());
    if (input != output) return test.failedExpected(input, output, std::string(catta::tostring::GetName<T>::name.data()) + " (to from string)");
    return true;
}

}  // namespace test
}  // namespace catta
