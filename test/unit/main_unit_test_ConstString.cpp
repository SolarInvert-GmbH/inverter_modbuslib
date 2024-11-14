// catta
#include <catta/ConstString.hpp>

// random
#include <catta/random/ConstString.hpp>

// fromtostring
#include <catta/tostring/ConstString.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

template <std::size_t SIZE>
static int test_all()
{
    using Type = catta::ConstString<SIZE>;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    int error = 0;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}

int main() { return test_all<0>() + test_all<1>() + test_all<2>() + test_all<3>() + test_all<4>() + test_all<5>() + test_all<6>() + test_all<7>(); }
