#pragma once

// std
#include <concepts>
#include <string>

namespace catta
{
namespace test
{
/**
 * @brief Output is an interface for the catta::test::Test class. It handles the output for the test.
 *
 * has to implement:
 * void Output::statusLine(const std::string& test, const std::string& message);
 * void Output::failedLine(const std::string& test, const std::string& message);
 * void Output::specialLine(const std::string& test, const std::string& message);
 * void Output::goodLine(const std::string& test, const std::string& message);
 * void Output::volatileLine(const std::string& test, const std::string& message);
 * @tparam T The class that implements the output for test.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Output = requires(T a, const std::string& test, const std::string& message)
{
    {
        a.statusLine(test, message)
        } -> std::same_as<void>;
    {
        a.failedLine(test, message)
        } -> std::same_as<void>;
    {
        a.specialLine(test, message)
        } -> std::same_as<void>;
    {
        a.goodLine(test, message)
        } -> std::same_as<void>;
    {
        a.volatileLine(test, message)
        } -> std::same_as<void>;
};
}  // namespace test
}  // namespace catta
