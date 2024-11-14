// catta
#include <catta/parser/TextPosition.hpp>

// random
#include <catta/random/parser/TextPosition.hpp>

// fromtostring
#include <catta/fromstring/parser/TextPosition.hpp>
#include <catta/tostring/parser/TextPosition.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkNext(catta::test::Test<OUTPUT>& test)
{
    const auto textPosition = test.random().template create<catta::parser::TextPosition>();
    const auto nextRow = textPosition.nextRow();
    const auto nextColumn = textPosition.nextColumn();
    if (nextRow.row() != textPosition.row() + 1)
        return test.failedExpected(catta::Decimal(nextRow.row()), catta::Decimal(textPosition.row() + 1), "");
    if (nextRow.column() != 1) return test.failedExpected(catta::Decimal(nextRow.column()), catta::Decimal(std::size_t(1)), "");
    if (nextColumn.column() != textPosition.column() + 1)
        return test.failedExpected(catta::Decimal(nextColumn.column()), catta::Decimal(textPosition.column() + 1), "");
    if (nextColumn.row() != textPosition.row()) return test.failedExpected(catta::Decimal(nextColumn.row()), catta::Decimal(textPosition.row()), "");
    return true;
}

template <catta::test::Output OUTPUT>
static bool checkCompare(catta::test::Test<OUTPUT>& test)
{
    const auto textPosition = test.random().template create<catta::parser::TextPosition>();
    const std::array<catta::parser::TextPosition, 3> v = {textPosition, textPosition.nextColumn(), textPosition.nextRow()};
    const auto check = [v, &test](const std::array<bool, 3> expected, const auto compare, const std::string s)
    {
        for (std::size_t i = 0; i < 3; i++)
        {
            const bool value = compare(v[i], v[1]);
            if (value != expected[i])
                return test.failed(catta::tostring::toString(v[i]) + s + catta::tostring::toString(v[1]) + " should be " +
                                   (expected[i] ? "true" : "false") + ".");
        }
        return true;
    };
    static constexpr bool f = false;
    static constexpr bool t = true;
    if (!check(
            {f, t, f}, [](auto a, auto b) { return a == b; }, "=="))
        return false;
    if (!check(
            {t, f, t}, [](auto a, auto b) { return a != b; }, "!="))
        return false;
    if (!check(
            {f, t, t}, [](auto a, auto b) { return a >= b; }, ">="))
        return false;
    if (!check(
            {f, f, t}, [](auto a, auto b) { return a > b; }, ">"))
        return false;
    if (!check(
            {t, t, f}, [](auto a, auto b) { return a <= b; }, "<="))
        return false;
    if (!check(
            {t, f, f}, [](auto a, auto b) { return a < b; }, "<"))
        return false;
    return true;
}

int main()
{
    using Type = catta::parser::TextPosition;
    using Output = catta::test::ConsoleOutput;
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_next = checkNext<Output>;
    const auto test_compare = checkCompare<Output>;
    Output output(catta::tostring::GetName<Type>::name.data());
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_next, "next", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_compare, "compare", output, 10000)) error++;
    return error;
}
