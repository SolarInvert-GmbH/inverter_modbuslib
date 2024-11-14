// catta
#include <catta/Hexadecimal.hpp>

// random
#include <catta/random/Hexadecimal.hpp>

// fromtostring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/tostring/Hexadecimal.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <std::integral INTEGRAL>
static int test_all()
{
    using Type = catta::Hexadecimal<INTEGRAL>;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}

int main()
{
    return test_all<std::uint8_t>() + test_all<std::uint16_t>() + test_all<std::uint32_t>() + test_all<std::uint64_t>() + test_all<std::int8_t>() +
           test_all<std::int16_t>() + test_all<std::int32_t>() + test_all<std::int64_t>();
}
