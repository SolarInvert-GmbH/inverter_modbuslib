// catta
#include <catta/modbus/si/RegisterType.hpp>

// random
#include <catta/random/modbus/si/RegisterType.hpp>

// fromtostring
#include <catta/fromstring/modbus/si/RegisterType.hpp>
#include <catta/tostring/modbus/si/RegisterType.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

int main()
{
    using Type = catta::modbus::si::RegisterType;
    using Output = catta::test::ConsoleOutput;
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    Output output(catta::tostring::GetName<Type>::name.data());
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}
