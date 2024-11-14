// catta
#include <catta/parser/LineColumnCounter.hpp>

// random
#include <catta/random/Random.hpp>

// fromtostring
#include <catta/tostring/parser/TextPosition.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

template <catta::test::Output OUTPUT, class CHAR>
static bool checkCases(catta::test::Test<OUTPUT>& test)
{
    typedef catta::parser::TextPosition T;
    typedef std::array<CHAR, 7> S;
    typedef std::pair<S, T> P;
    constexpr std::array<P, 6> cases = {P{S{'a', 'b', 'c', '\n', 'a', 'b'}, T{2, 3}},
                                        P{S{'a', 'b', 'c', '\n', '\r', 'a', 'b'}, T{2, 3}},
                                        P{S{'a', 'b', 'c', '\r', '\n', 'a', 'b'}, T{2, 3}},
                                        P{S{'\n', '\n', '\n', '\n', '\n', '\n'}, T{7, 1}},
                                        P{S{}, T{1, 1}},
                                        P{S{'\n', '\r', '\r', '\n'}, T{3, 1}}};
    for (const auto& [string, expected] : cases)
    {
        catta::parser::LineColumnCounter<CHAR> counter;
        for (const auto c : string)
            if (c) counter.read(c);
        if (counter.position() != expected) return test.failedExpected(expected, counter.position(), "counter position");
    }
    return true;
}

template <class CHAR>
const static std::string name;
template <>
const std::string name<char> = "catta::parser::LineColumnCounter<char>";
template <>
const std::string name<char32_t> = "catta::parser::LineColumnCounter<char32_t>";

template <class CHAR>
static int test_all()
{
    using Output = catta::test::ConsoleOutput;
    Output output(name<CHAR>);
    const auto test_case = checkCases<Output, CHAR>;
    int error = 0;
    if (!catta::test::execute<Output>(test_case, "case", output)) error++;
    return error;
}

int main()
{
    int error = 0;
    error += test_all<char>();
    error += test_all<char32_t>();
    return error;
}
