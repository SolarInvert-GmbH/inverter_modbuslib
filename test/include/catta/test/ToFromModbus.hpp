#pragma once

// parser
#include <catta/parser/DefaultTokenType.hpp>

// test
#include <catta/test/Test.hpp>

// fromtostring
#include <catta/tostring/modbus/Token.hpp>
#include <catta/tostring/parser/State.hpp>

// tofrommodbus
#include <catta/frommodbus/fromModbus.hpp>
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace test
{
/**
 * Tests one random T object. Serializes and deserializes random objects to/from modbus. The result object should be the same as the
 * random created one.
 * @param[in] test The test object.
 * @tparam OUTPUT The output class for the test.
 * @tparam T The class for which the test performed for.
 * @return Returns @b true if the test was successfull, otherwise @b false.
 */
template <catta::test::Output OUTPUT, class T, bool DEBUG = false>
static bool checkToFromModbus(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<T>();
    if (DEBUG) test.status(catta::tostring::toString(input));

    catta::tomodbus::Serializer<T> serializer;
    catta::frommodbus::Parser<T> parser;

    auto output = T{};
    for (std::size_t i = 0; i < 1000; i++)
    {
        const auto [token0, handled0] = serializer.read(input);
        if (serializer.state().isFailed()) return test.failed("Serializer failed.");
        const auto value = serializer.data();
        {
            if (DEBUG) test.status("   " + catta::tostring::toString(value));
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
}  // namespace test
}  // namespace catta
