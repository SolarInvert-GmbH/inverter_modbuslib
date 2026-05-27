#pragma once

// esp32
#include <catta/esp32/Pin.hpp>

// catta
#include <catta/physics/Frequency.hpp>

namespace catta
{
namespace esp32
{
/**
 * @brief Class uses special Hardware to create a pwm signal.
 *
 * In other envirements a single pwm is called ledc.
 * @author CattaTech - Maik Urbannek
 */
template <std::uint8_t RESOLUTION>
class SinglePwm
{
  public:
    static_assert(RESOLUTION >= 1 && RESOLUTION <= 20);
    /**
     * The 100% duty. Allowed are values [0,fullDuty) (fullDuty is not allowed).
     */
    constexpr static std::uint32_t fullDuty = 1 << RESOLUTION;
    /**
     * Minimal frequency that can be handled.
     */
    constexpr static catta::physics::Hertz32 minFrequency = catta::physics::Hertz32(1);
    /**
     * Maximal frequency that can be handled.
     */
    constexpr static catta::physics::Hertz32 maxFrequency = catta::physics::Hertz32(80'000'000 >> RESOLUTION);
    /**
     * Destructor. Frees single pwm handle.
     */
    ~SinglePwm() noexcept { remove(); }
    /**
     * Move constructor.
     * @param[in,out] other Other single pwm handle. Moves handle in this uarsingle pwmt. Other single pwm is empty afterwards.
     */
    [[nodiscard]] SinglePwm(SinglePwm &&other) noexcept : _channel(other._channel), _frequency(other._frequency), _duty(other._duty)
    {
        other._channel = EMPTY;
        other._frequency = {};
        other._duty = fullDuty;
    }
    /**
     * Move assigment. If this single pwm handle was not empty befor the single pwm is freed.
     * @param[in,out] other Other single pwm handle. Moves handle in this single pwm. Other single pwm is empty afterwards.
     */
    void operator=(SinglePwm &&other) noexcept
    {
        remove();
        _channel = other._channel;
        _frequency = other._frequency;
        _duty = other._duty;
        other._frequency = {};
        other._duty = fullDuty;
    }
    /**
     * @param[in] pin The gpio pin that outputs the signal.
     * @param[in] frequency The frequency of the signal. Has to be in [1 Hz, maxFrequency].
     * @param[in] duty The duty of the signal. The duty is the percentage where the signal is high. The duty can be in [0,fullDuty). The fullDuty is
     * not allowed. 0 is 0% and fullDuty would be 100%.
     * @return Returns the handler for the first single pwm signal generator if input is valid, otherwise empty.
     */
    [[nodiscard]] static SinglePwm createChannel0(const Pin pin, const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept
    {
        return create(pin, 0, frequency, duty);
    }
    /**
     * @param[in] pin The gpio pin that outputs the signal.
     * @param[in] frequency The frequency of the signal. Has to be in [1 Hz, maxFrequency].
     * @param[in] duty The duty of the signal. The duty is the percentage where the signal is high. The duty can be in [0,fullDuty). The fullDuty is
     * not allowed. 0 is 0% and fullDuty would be 100%.
     * @return Returns the handler for the second single pwm signal generator if input is valid, otherwise empty.
     */
    [[nodiscard]] static SinglePwm createChannel1(const Pin pin, const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept
    {
        return create(pin, 1, frequency, duty);
    }
    /**
     * @param[in] pin The gpio pin that outputs the signal.
     * @param[in] frequency The frequency of the signal. Has to be in [1 Hz, maxFrequency].
     * @param[in] duty The duty of the signal. The duty is the percentage where the signal is high. The duty can be in [0,fullDuty). The fullDuty is
     * not allowed. 0 is 0% and fullDuty would be 100%.
     * @return Returns the handler for the third single pwm signal generator if input is valid, otherwise empty.
     */
    [[nodiscard]] static SinglePwm createChannel2(const Pin pin, const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept
    {
        return create(pin, 2, frequency, duty);
    }
    /**
     * @param[in] pin The gpio pin that outputs the signal.
     * @param[in] frequency The frequency of the signal. Has to be in [1 Hz, maxFrequency].
     * @param[in] duty The duty of the signal. The duty is the percentage where the signal is high. The duty can be in [0,fullDuty). The fullDuty is
     * not allowed. 0 is 0% and fullDuty would be 100%.
     * @return Returns the handler for the fourth single pwm signal generator if input is valid, otherwise empty.
     */
    [[nodiscard]] static SinglePwm createChannel3(const Pin pin, const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept
    {
        return create(pin, 3, frequency, duty);
    }
    /**
     * @return Returns an invalid/empty handle.
     */
    [[nodiscard]] static SinglePwm empty() noexcept { return SinglePwm(EMPTY); }
    /**
     * @param[in] frequency The frequency of the pwm.
     * @param[in] duty The duty of the pwm. Is the part that is one in relation to RESOLUTION.
     * @todo many value are not valid.
     * Sleeps for given time.
     */
    void set(const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept;
    /**
     * @return Returns @b true if uart handle is invalid/empty, otherwise @b false.
     */
    [[nodiscard]] bool isEmpty() const noexcept { return _channel == EMPTY; }
    SinglePwm(const SinglePwm &) = delete;
    SinglePwm operator=(const SinglePwm &) = delete;

  private:
    SinglePwm(const std::uint8_t channel, const catta::physics::Hertz32 frequency = catta::physics::Hertz32{}, const std::uint32_t duty = fullDuty)
        : _channel(channel), _frequency(frequency), _duty(duty)
    {
    }
    std::uint8_t _channel;
    catta::physics::Hertz32 _frequency;
    std::uint32_t _duty;
    static SinglePwm create(const Pin pin, const std::uint8_t channel, const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept;
    void remove() noexcept;
    static constexpr std::uint8_t EMPTY = 4;
};

}  // namespace esp32
}  // namespace catta

#include "driver/ledc/include/driver/ledc.h"
//
#include "esp_common/include/esp_err.h"

template <std::uint8_t RESOLUTION>
catta::esp32::SinglePwm<RESOLUTION> catta::esp32::SinglePwm<RESOLUTION>::create(const Pin pin, const std::uint8_t channel,
                                                                                const catta::physics::Hertz32 frequency,
                                                                                const std::uint32_t duty) noexcept
{
    if (pin.isEmpty() || channel >= EMPTY || frequency > maxFrequency || frequency < minFrequency || duty > fullDuty) return empty();
    ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_HIGH_SPEED_MODE,
                                      .duty_resolution = static_cast<ledc_timer_bit_t>(RESOLUTION),
                                      .timer_num = static_cast<ledc_timer_t>(channel),
                                      .freq_hz = static_cast<std::uint32_t>(frequency.count()),
                                      .clk_cfg = LEDC_USE_APB_CLK,
                                      .deconfigure = false};
    switch (ledc_timer_config(&ledc_timer))
    {
        case ESP_ERR_INVALID_ARG:
        case ESP_FAIL:
            return empty();
        default:  // ESP_OK Success
            break;
    }

    ledc_channel_config_t ledc_channel = {.gpio_num = pin,
                                          .speed_mode = LEDC_HIGH_SPEED_MODE,
                                          .channel = static_cast<ledc_channel_t>(channel),
                                          .intr_type = LEDC_INTR_DISABLE,
                                          .timer_sel = static_cast<ledc_timer_t>(channel),
                                          .duty = duty,
                                          .hpoint = 0,  //???
                                          .flags = {.output_invert = 0}};
    return ledc_channel_config(&ledc_channel) == ESP_OK ? SinglePwm(channel, frequency, duty) : empty();  // ESP_ERR_INVALID_ARG
}

template <std::uint8_t RESOLUTION>
void catta::esp32::SinglePwm<RESOLUTION>::set(const catta::physics::Hertz32 frequency, const std::uint32_t duty) noexcept
{
    if (frequency > maxFrequency || duty >= fullDuty)
    {
        // Error
    }
    if (frequency != _frequency)
        switch (ledc_set_freq(LEDC_HIGH_SPEED_MODE, static_cast<ledc_timer_t>(_channel), static_cast<std::uint32_t>(frequency.count())))
        {
            case ESP_ERR_INVALID_ARG:
            case ESP_FAIL:
            default:  // ESP_OK Success
                break;
        }
    if (duty != _duty)
    {
        if (ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(_channel), duty) != ESP_OK)
        {
            // ESP_ERR_INVALID_ARG
        }
        if (ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(_channel)) != ESP_OK)
        {
            // ESP_ERR_INVALID_ARG
        }
    }
}

template <std::uint8_t RESOLUTION>
void catta::esp32::SinglePwm<RESOLUTION>::remove() noexcept
{
    ledc_stop(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(_channel), 0);
}
