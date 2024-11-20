// catta
#include <catta/modbus/sunspec/ValueU64.hpp>

// random
#include <catta/random/modbus/sunspec/ValueU64.hpp>

// fromtostring
#include <catta/fromstring/modbus/sunspec/ValueU64.hpp>
#include <catta/tostring/modbus/sunspec/ValueU64.hpp>

// json
#include <catta/fromjson/modbus/sunspec/ValueU64.hpp>
#include <catta/tojson/modbus/sunspec/ValueU64.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromJson.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

int main()
{
    using Type = catta::modbus::sunspec::ValueU64;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_tofromjson = catta::test::checkToFromJson<Output, Type, debug>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromjson, "tofromjson", output, 10000)) error++;
    return error;
}
