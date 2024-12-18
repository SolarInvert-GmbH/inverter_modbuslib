#pragma once

#include <chrono>

namespace catta
{
namespace esp32
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
     * @todo We implemented busy wait.
     * Sleeps for given time.
     */
    static void sleep(const std::chrono::microseconds duration) noexcept;
};

}  // namespace esp32
}  // namespace catta

#include "esp_timer/include/esp_timer.h"

[[nodiscard]] std::chrono::microseconds catta::esp32::Time::get() noexcept { return std::chrono::microseconds(esp_timer_get_time()); }
void catta::esp32::Time::sleep(const std::chrono::microseconds duration) noexcept
{
    const auto until = catta::esp32::Time::get() + duration;
    while (catta::esp32::Time::get() < until)
    {
    }
}
