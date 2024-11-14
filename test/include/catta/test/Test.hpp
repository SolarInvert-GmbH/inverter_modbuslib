#pragma once

// std
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>

// string
#include <catta/tostring/Hexadecimal.hpp>

// random
#include <catta/random/Random.hpp>

// test
#include <catta/test/Output.hpp>

namespace catta
{
namespace test
{
/**
 * @tparam OUTPUT A class that implements the catta::test::Output interface.
 * @brief Class to handle tests.
 * @author CattaTech - Maik Urbannek
 */
template <Output OUTPUT>
class Test
{
  public:
    /**
     * @param[in] name The name of the sub test.
     * @param[in] output Output object for Logging test messages.
     * @param[in] seed The seed for the catta::random::Random object. If zero the time is used as seed, otherwise the seed ist used and the test
     * becomes determinisic (if the to test class/functionist determinisic).
     * @return Creates a test object.
     */
    static Test create(const std::string& name, OUTPUT& output, const uint64_t seed = 0) { return Test(name, output, seed); }
    /**
     * @param[in] message Message for test failing.
     * @return Returns @b false.
     */
    bool failed(const std::string& message)
    {
        _percentage = NO_PERCENTAGE;
        _output.failedLine(_name, message);
        _state = DONE_FALSE;
        return false;
    }
    /**
     * Prints message with wrong object and expected object.
     * @param[in] orginal The expected object.
     * @param[in] wrong The wrong object.
     * @param[in] name The short name of the object.
     * @return Returns @b false.
     */
    bool failedExpected(const catta::tostring::ToStringable auto& orginal, const catta::tostring::ToStringable auto& wrong, const std::string& name)
    {
        failed("Expected " + catta::tostring::toString(orginal) + " as " + name + ",");
        failed("but got  " + catta::tostring::toString(wrong) + ".");
        return false;
    }
    /**
     * Prints message with wrong object and expected object when T is catta::tostring::ToStringable, otherwise a short message is produced.
     * Can be used for template implementations.
     * @param[in] orginal The expected object.
     * @param[in] wrong The wrong object.
     * @param[in] name The short name of the object.
     * @return Returns @b false.
     */
    template <class T>
    bool failedExpectedSafe(const T&, const T&, const std::string& name)
    {
        return failed(name + "is not as expected.");
    }

    template <catta::tostring::ToStringable T>
    bool failedExpectedSafe(const T& orginal, const T& wrong, const std::string& name)
    {
        return failedExpected(orginal, wrong, name);
    }
    /**
     * @param[in] message Message for status message.
     */
    void status(const std::string& message)
    {
        _percentage = NO_PERCENTAGE;
        _output.statusLine(_name, message);
    }
    /**
     * @param[in] i Current percentage. Should not be bigger than size.
     * @param[in] size Hundred percent.
     */
    void percent(const std::size_t i, const std::size_t size)
    {
        const std::size_t newPercentage = ((i + 1) * 100) / (size);
        if (newPercentage != _percentage)
        {
            _output.volatileLine(_name, std::to_string(((i + 1) * 100) / (size)) + "%             ");
            _percentage = newPercentage;
        }
    }
    /**
     * @param[in] message Message for successful test.
     * @return Returns @b true.
     */
    bool successful()
    {
        _percentage = NO_PERCENTAGE;
        _output.goodLine(_name, "success");
        _state = DONE_TRUE;
        return true;
    }
    /**
     * @param[in] message Message for not implemented test.
     * @return Returns @b true.
     */
    bool featureNotImplementedYet()
    {
        _percentage = NO_PERCENTAGE;
        _output.specialLine(_name, "feature not implemented yet");
        _state = DONE_TRUE;
        return true;
    }
    /**
     * @param[in] message Message for not implemented feature.
     * @return Returns @b true.
     */
    bool testNotImplementedYet()
    {
        _percentage = NO_PERCENTAGE;
        _output.specialLine(_name, "test not implemented yet");
        _state = DONE_TRUE;
        return true;
    }
    /**
     * @return Returns the random object.
     */
    random::Random& random() { return _random; }
    /**
     * @return Returns @b true if test is not done yet, otherwise @b false;
     */
    bool isRunning() const noexcept { return _state >= RUNNING; }
    /**
     * @return Returns wether the test succeded or not. Empty is returned if test is not done yet.
     */
    std::optional<bool> result() const noexcept { return isRunning() ? std::optional<bool>{} : std::optional<bool>{_state == DONE_TRUE}; }

  private:
    Test(const std::string& name, OUTPUT& output, const std::uint64_t seed)
        : _random(random::Random::create(seed ? seed : time())), _output(output), _name(name), _percentage(NO_PERCENTAGE), _state(RUNNING)
    {
        _output.statusLine(_name, "begin[0x" + catta::tostring::toString(Hexadecimal(_random.seed())) + "]");
    }
    random::Random _random;
    OUTPUT& _output;
    std::string _name;
    std::size_t _percentage;
    std::uint8_t _state;
    static std::uint64_t time()
    {
        return static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    constexpr static std::size_t NO_PERCENTAGE = static_cast<std::size_t>(-1);
    static constexpr std::uint8_t DONE_FALSE = 0;
    static constexpr std::uint8_t DONE_TRUE = 1;
    static constexpr std::uint8_t RUNNING = 2;
};

/**
 * @brief This class is @b std::true_type if CLASS is a Test, otherwise @b std::false_type.
 * @tparam CLASS The class that is checked if it is a Test.
 * @author CattaTech - Maik Urbannek
 */
template <class>
struct isTest : std::false_type
{
};

template <class T>
struct isTest<catta::test::Test<T>> : std::true_type
{
};

/**
 * @brief TestConcept is satisfied if T is a Test.
 * @tparam T The class that is checked if it is a Test.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept TestConcept = isTest<T>::value;

/**
 * @tparam OUTPUT The output class for the test.
 * @param[in] testLoopFunction A callable that takes the reference of a test and returns a bool (success = @b true, failure = @b false). The function
 * execute one loop of the test. For failure should Test::failed() be used. For success no message is needed.
 * @param[in] name The name of the test.
 * @param[in] loops Number of runs of testLoopFunction.
 * @author CattaTech - Maik Urbannek
 */
template <catta::test::Output OUTPUT>
static bool execute(const auto testLoopFunction, const std::string& name, OUTPUT& output, const std::size_t loops)
{
    auto test = catta::test::Test<OUTPUT>::create(name, output);
    for (std::size_t i = 0; i < loops; i++)
        if (!testLoopFunction(test)) return false;
    return test.successful();
}

/**
 * @tparam OUTPUT The output class for the test.
 * @param[in] testFunction A callable that takes the reference of a test and returns a bool (success = @b true, failure = @b false). The function
 * execute once in the test. For failure should Test::failed() be used. For success no message is needed.
 * @param[in] name The name of the test.
 * @author CattaTech - Maik Urbannek
 */
template <catta::test::Output OUTPUT>
static bool execute(const auto testLoopFunction, const std::string& name, OUTPUT& output)
{
    auto test = catta::test::Test<OUTPUT>::create(name, output);
    return testLoopFunction(test) ? test.successful() : false;
}
}  // namespace test
}  // namespace catta
