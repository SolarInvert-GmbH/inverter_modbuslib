#pragma once

// parser
#include <catta/parser/DefaultTokenType.hpp>

// test
#include <catta/test/Test.hpp>

// fromtostring
#include <catta/tostring/json/Token.hpp>
#include <catta/tostring/parser/State.hpp>

// tofromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace test
{
/**
 * Tests one random T object. Serializes and deserializes random objects to/from json. The result object should be the same as the
 * random created one.
 * @param[in] test The test object.
 * @tparam OUTPUT The output class for the test.
 * @tparam T The class for which the test performed for.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool DEBUG = false>
static bool checkToFromJsonInput(catta::test::Test<OUTPUT>& test, const T input)
{
    if (DEBUG) test.status(catta::tostring::toString(input));

    catta::tojson::Serializer<T> serializer;
    catta::fromjson::Parser<T> parser;

    auto output = T{};
    for (std::size_t i = 0; i < 1000; i++)
    {
        const auto [token0, handled0] = serializer.read(input);
        if (serializer.state().isFailed()) return test.failed("Serializer failed.");
        const auto value = serializer.data();
        // if (token0.type().isValue())
        {
            if (DEBUG)
                test.status("   " + (value.type().isCharacter()
                                         ? ("CHARACTER{" + std::string(1, static_cast<char>(value.unicodeCharacterValue())) + "}")
                                         : catta::tostring::toString(value)));
            bool parsed = false;
            for (std::size_t j = 0; j < 10 && !parsed; j++)
            {
                const auto [token1, handled1] = parser.read(value);
                parsed = handled1;
                if (parser.state().isFailed()) return test.failed("Parser failed.");
                if (!parser.data().isEmpty())
                {
                    if (output.isEmpty())
                        output = parser.data();
                    else
                        test.failed("Parsed more than on object.");
                }
            }
            if (!parsed) return test.failed("Parser needed more than 10 ticks.");
        }
        if (handled0)
        {
            if (input != output) return test.failedExpected(input, output, "parsing result");
            if (!serializer.state().isDone()) test.failedExpected(catta::parser::State::done(), serializer.state(), "serializer state");
            if (!parser.state().isDone()) test.failedExpected(catta::parser::State::done(), parser.state(), "parser state");
            return true;
        }
    }
    return test.failed("Serializer needed more than 1000 ticks.");
}

/**
 * Tests one random T object. Serializes and deserializes random objects to/from json. The result object should be the same as the
 * random created one.
 * @param[in] test The test object.
 * @tparam OUTPUT The output class for the test.
 * @tparam T The class for which the test performed for.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool DEBUG = false>
static bool checkToFromJson(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<T>();
    return checkToFromJsonInput<OUTPUT, T, DEBUG>(test, input);
}

/**
 * Tests one random T object. Serializes and deserializes random objects to/from json. The result object should be the same as the
 * random created one.
 * @param[in] test The test object.
 * @tparam OUTPUT The output class for the test.
 * @tparam T The class for which the test performed for.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool DEBUG = false>
static bool checkToFromJsonEmpty(catta::test::Test<OUTPUT>& test)
{
    const auto input = T::empty();
    return checkToFromJsonInput<OUTPUT, T, DEBUG>(test, input);
}

}  // namespace test
}  // namespace catta
