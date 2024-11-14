#pragma once

// test
#include <catta/test/Output.hpp>

// std
#include <cstdio>

namespace catta
{
namespace test
{
/**
 * @brief Implementation of catta::test::Output inteface. Prints test message on console. Uses color.
 * @author CattaTech - Maik Urbannek
 */
class ConsoleOutput
{
  public:
    /**
     * Constructor.
     * @param[in] name The name of the test.
     */
    ConsoleOutput(const std::string& name) : _name(name) { puts(("Begin " + _name + " tests:").c_str()); }
    /**
     * Print a status line for a test.
     * @param[in] test The test object.
     * @param[in] message The message to print.
     */
    void statusLine(const std::string& test, const std::string& message) { line(test, message, std::string(), std::string()); }
    /**
     * Print a failed line for a test.
     * @param[in] test The test object.
     * @param[in] message The message to print.
     */
    void failedLine(const std::string& test, const std::string& message) { line(test, message, std::string("\033[1;31m"), std::string("\033[0m")); }
    /**
     * Print a special line for a test. For example "Test not implementet yet.".
     * @param[in] test The test object.
     * @param[in] message The message to print.
     */
    void specialLine(const std::string& test, const std::string& message) { line(test, message, std::string("\033[1;35m"), std::string("\033[0m")); }
    /**
     * Print a good line for a test. For example "Test succedded.":
     * @param[in] test The test object.
     * @param[in] message The message to print.
     */
    void goodLine(const std::string& test, const std::string& message) { line(test, message, std::string("\033[1;32m"), std::string("\033[0m")); }
    /**
     * Print a volatile line for a test. The line will be remove with next message. For example "Test percent.":
     * @param[in] test The test object.
     * @param[in] message The message to print.
     */
    void volatileLine(const std::string& test, const std::string& message)
    {
        printf("  TEST %s: %s\r", test.c_str(), message.c_str());
        fflush(stdout);
    }
    /**
     * Destructor.
     */
    ~ConsoleOutput() { puts(("End " + _name + " tests.").c_str()); }

  private:
    void line(const std::string& test, const std::string& message, const std::string& prefix, const std::string& postfix)
    {
        puts(("  TEST " + test + ": " + prefix + message + postfix).c_str());
    }
    std::string _name;
};

}  // namespace test
}  // namespace catta
