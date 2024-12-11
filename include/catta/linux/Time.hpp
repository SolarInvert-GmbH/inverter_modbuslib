#pragma once

#include <chrono>

namespace catta
{
namespace linux
{
/**
 * @brief Static class for time stuff.
 * @author CattaTech - Maik Urbannek
 */
class Time
{
  public:
    /**
     *@return Returns the time since system start.
     */
    [[nodiscard]] static std::chrono::microseconds get() noexcept;
    /**
     * @param[in] duration Time to sleep.
     * @todo Has currently a bad 100 ms resolution
     * Sleeps for given time.
     */
    static void sleep(const std::chrono::microseconds duration) noexcept;
};

}  // namespace linux
}  // namespace catta

// std
#include <thread>

[[nodiscard]] std::chrono::microseconds catta::linux::Time::get() noexcept
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}
void catta::linux::Time::sleep(const std::chrono::microseconds duration) noexcept { std::this_thread::sleep_for(duration); }
