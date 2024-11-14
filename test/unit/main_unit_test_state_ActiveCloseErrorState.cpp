// catta
#include <catta/state/ActiveCloseErrorState.hpp>
#include <catta/state/DefaultError.hpp>

// random
#include <catta/random/state/ActiveCloseErrorState.hpp>
#include <catta/random/state/DefaultError.hpp>

// fromtostring
#include <catta/fromstring/state/ActiveCloseErrorState.hpp>
#include <catta/fromstring/state/DefaultError.hpp>
#include <catta/tostring/state/ActiveCloseErrorState.hpp>
#include <catta/tostring/state/DefaultError.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

int main()
{
    using Type = catta::state::ActiveCloseErrorState<catta::state::DefaultError>;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}
