// catta
#include <catta/modbus/si/RegisterAddress.hpp>

// random
#include <catta/random/modbus/si/RegisterAddress.hpp>

// fromtostring
#include <catta/fromstring/modbus/si/RegisterAddress.hpp>
#include <catta/tostring/modbus/si/RegisterAddress.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkToFromRaw(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<catta::modbus::si::RegisterAddress>();
    const auto output = catta::modbus::si::RegisterAddress::fromRaw(input.raw());
    if (debug) test.status(catta::tostring::toString(input));
    if (input != output) return test.failedExpected(output, input, "output");
    return true;
}

int main()
{
    using Type = catta::modbus::si::RegisterAddress;
    using Output = catta::test::ConsoleOutput;
    const auto test_create = checkToFromRaw<Output>;
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    Output output(catta::tostring::GetName<Type>::name.data());
    int error = 0;
    if (!catta::test::execute<Output>(test_create, "tofromraw", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}
