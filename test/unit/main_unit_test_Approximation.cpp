// catta
#include <catta/Approximation.hpp>

// random
#include <catta/random/Random.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT, std::int32_t Ampitude, std::uint32_t Periode, std::int32_t AllowedDiffernce>
static bool checkSinus(catta::test::Test<OUTPUT>& test)
{
    const auto classic = [](const std::uint32_t x)
    {
        const double a = static_cast<double>(Ampitude);
        const double p = static_cast<double>(Periode);
        const double t = static_cast<double>(x);
        static constexpr double twopi = 3.141592653589793 * 2.0;
        return static_cast<std::int32_t>(a * std::sin((t * twopi) / p));
    };

    const std::uint32_t input = test.random().template create<std::uint32_t>();
    const std::int32_t expected = classic(input);
    const std::int32_t output = catta::sinus<Ampitude, Periode>(input);
    const std::int32_t signedDifference = expected - output;
    const std::int32_t difference = signedDifference < 0 ? -signedDifference : signedDifference;
    if constexpr (debug)
        test.status("sinus<" + std::to_string(Ampitude) + "," + std::to_string(Periode) + ">(" + std::to_string(input) +
                    ") = " + std::to_string(output) + " float_sin = " + std::to_string(expected) + "   diff: " + std::to_string(difference));
    if (difference > AllowedDiffernce)
        return test.failed("Expected " + std::to_string(expected) + " ± " + std::to_string(AllowedDiffernce) + " as result for sinus<" +
                           std::to_string(Ampitude) + "," + std::to_string(Periode) + ">(" + std::to_string(input) + "), but got " +
                           std::to_string(output) + " (diff: " + std::to_string(difference) + ")");
    return true;
}

template <catta::test::Output OUTPUT, std::uint32_t Minimum, std::uint32_t Maximum>
static bool checkBounds(catta::test::Test<OUTPUT>& test, const auto methode, const char* name)
{
    const std::uint32_t input = test.random().template create<std::uint32_t>();
    const std::uint32_t output = methode(input);
    if constexpr (debug) test.status(std::string(name) + "(" + std::to_string(input) + ") = " + std::to_string(output));
    if (output < Minimum)
        return test.failed(std::string(name) + "(" + std::to_string(input) + ") = " + std::to_string(output) + " is smaller than minimum  " +
                           std::to_string(Minimum));
    if (output > Maximum)
        return test.failed(std::string(name) + "(" + std::to_string(input) + ") = " + std::to_string(output) + " is bigger than maximum  " +
                           std::to_string(Maximum));
    return true;
}

template <std::uint32_t Minimum, std::int32_t Ampitude, std::uint32_t Periode, std::int32_t AllowedDiffernce>
static int all()
{
    using Output = catta::test::ConsoleOutput;
    static constexpr std::uint32_t Maximum = static_cast<std::uint32_t>(Ampitude) * 2 + Minimum;
    const auto methodeSinusWindow = [](const std::uint32_t x) { return catta::sinusWindow<Minimum, Maximum, Periode>(x); };
    const auto methodeSaw = [](const std::uint32_t x) { return catta::saw<Periode>(x); };
    const auto methodeStep = [](const std::uint32_t x) { return catta::step<Periode, 32>(x); };
    const auto test_sinus = checkSinus<Output, Ampitude, Periode, AllowedDiffernce>;
    const auto test_sinuswindow = [methodeSinusWindow](auto& test)
    { return checkBounds<Output, Minimum, Maximum>(test, methodeSinusWindow, "sinuswindow"); };
    const auto test_saw = [methodeSaw](auto& test) { return checkBounds<Output, 0, Periode>(test, methodeSaw, "saw"); };
    const auto test_step = [methodeStep](auto& test) { return checkBounds<Output, 0, Periode>(test, methodeStep, "step"); };
    Output output("catta::Approximation");
    int error = 0;
    if (!catta::test::execute<Output>(test_sinus, "sinus", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_sinuswindow, "sinuswindow", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_saw, "saw", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_step, "step", output, 10000)) error++;
    return error;
}

int main() { return all<100, 1000, 1024, 13>(); }
