// catta
#include <catta/Decimal.hpp>

// random
#include <catta/random/Decimal.hpp>

// fromtostring
#include <catta/fromstring/Decimal.hpp>
#include <catta/tostring/Decimal.hpp>

// std
#include <limits>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT, std::integral INTEGRAL>
static bool checkGetMaxPowerOfTen(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<catta::Decimal<INTEGRAL>>();
    using UNSIGNED = catta::Unsigned<INTEGRAL>::type;
    const UNSIGNED slow = [input]()
    {
        const INTEGRAL value = INTEGRAL(input);
        if (value >= 0)
            for (INTEGRAL i = 1; true; i = i * 10)
            {
                if ((value / i) < 10) return static_cast<UNSIGNED>(i);
            }
        else
            for (INTEGRAL i = 1; true; i = i * 10)
            {
                if ((value / i) > static_cast<INTEGRAL>(-10)) return static_cast<UNSIGNED>(i);
            }

        return UNSIGNED(0);
    }();
    const UNSIGNED fast = input.getMaxPowerOfTen();
    if (slow != fast)
    {
        std::cout << "Error expected " << std::uint64_t(slow) << " as max ten power for " << std::uint64_t(INTEGRAL(input)) << ", but got "
                  << std::uint64_t(fast) << "\n";
        return false;
    }
    if (debug)
        test.status("<" + catta::tostring::toString(catta::Decimal(slow)) + " " + catta::tostring::toString(catta::Decimal(fast)) +
                    "> <= " + catta::tostring::toString(input));
    if (slow != fast) return test.failedExpected(catta::Decimal(slow), catta::Decimal(fast), "output");
    return true;
}

template <std::integral INTEGRAL>
static int test_all()
{
    using Type = catta::Decimal<INTEGRAL>;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_getmaxpoweroften = checkGetMaxPowerOfTen<Output, INTEGRAL>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_getmaxpoweroften, "getmaxpoweroften", output, 10000)) error++;
    return error;
}

int main()
{
    return test_all<std::uint8_t>() + test_all<std::uint16_t>() + test_all<std::uint32_t>() + test_all<std::uint64_t>() + test_all<std::int8_t>() +
           test_all<std::int16_t>() + test_all<std::int32_t>() + test_all<std::int64_t>();
}
