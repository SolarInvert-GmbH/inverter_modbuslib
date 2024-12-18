#pragma once

#include <chrono>

namespace catta
{
namespace rp2040
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
     * Sleeps for given time.
     */
    static void sleep(const std::chrono::microseconds duration) noexcept;
};
}  // namespace rp2040
}  // namespace catta

#include "hardware_base/include/hardware/address_mapped.h"
#include "hardware_clocks/include/hardware/clocks.h"
#include "hardware_timer/include/hardware/timer.h"
#include "pico_time/include/pico/time.h"

[[nodiscard]] std::chrono::microseconds catta::rp2040::Time::get() noexcept { return std::chrono::microseconds(time_us_64()); }
void catta::rp2040::Time::sleep(const std::chrono::microseconds duration) noexcept { sleep_us(static_cast<uint64_t>(duration.count())); }
