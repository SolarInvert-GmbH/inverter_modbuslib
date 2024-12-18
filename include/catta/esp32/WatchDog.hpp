#pragma once

#include <chrono>

namespace catta
{
namespace esp32
{
/**
 * @brief Implements the watchdog handle.
 *
 * A watchdog reboots the esp32 if not feet (@see feed()). So the system can recover if it is in a failstate like an endless loop.
 * @author CattaTech - Maik Urbannek
 */
class WatchDog
{
  public:
    /**
     * @todo does not dedect collision
     * @todo workes only on core one
     * @param[in] seconds Time until the watchdog reboots esp32.
     */
    WatchDog(const std::chrono::seconds seconds);
    /**
     * Feeds the watchdog. If the watchdog is not feet, the esp32 will be rebooted
     */
    void feed() noexcept;
    /**
     * Destructor.
     */
    ~WatchDog() { remove(); }
    /**
     * Move constructor.
     * @param[in,out] other Other watchdog handle. Moves handle in this watchdog. Other watchdog is empty afterwards.
     */
    WatchDog(WatchDog &&other) : _seconds(other._seconds) { other = empty(); }
    /**
     * Move assigment. If this watchdog handle was not empty befor the watchdog is freed.
     * @param[in,out] other Other watchdog handle. Moves handle in this watchdog. Other watchdog is empty afterwards.
     */
    void operator=(WatchDog &&other) noexcept
    {
        remove();
        _seconds = other._seconds;
        other = empty();
    }
    /**
     * @return Returns empty/invalid watchdog.
     */
    [[nodiscard]] static WatchDog empty() noexcept { return WatchDog{std::chrono::seconds{}}; }
    WatchDog operator=(const WatchDog &) = delete;
    WatchDog(const WatchDog &) = delete;

  private:
    std::chrono::seconds _seconds;
    void remove() noexcept;
};
}  // namespace esp32
}  // namespace catta

#include "esp_system/include/esp_private/esp_int_wdt.h"
#include "esp_system/include/esp_task_wdt.h"
#include "soc/esp32/include/soc/timer_group_reg.h"
#include "soc/esp32/include/soc/timer_group_struct.h"

catta::esp32::WatchDog::WatchDog(const std::chrono::seconds seconds) : _seconds(seconds)
{
    const esp_task_wdt_config_t twdt_config = {
        .timeout_ms = static_cast<uint32_t>(seconds.count()) * 1000,
        .idle_core_mask = 0,
        .trigger_panic = true,
    };

    esp_task_wdt_reconfigure(&twdt_config);
    esp_task_wdt_add(nullptr);
}

void catta::esp32::WatchDog::feed() noexcept { esp_task_wdt_reset(); }

void catta::esp32::WatchDog::remove() noexcept { esp_task_wdt_delete(xTaskGetCurrentTaskHandle()); }
