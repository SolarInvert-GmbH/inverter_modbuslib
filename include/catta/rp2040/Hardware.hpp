#pragma once

// rp2040
#include <catta/rp2040/Pin.hpp>
#include <catta/rp2040/PinType.hpp>

namespace catta
{
namespace rp2040
{
/**
 * @brief Class to explore pico hardware.
 * @author CattaTech - Maik Urbannek
 */
class Hardware
{
  public:
    /**
     * @return Returns singlton handle on hardware configuration.
     */
    [[nodiscard]] static Hardware &get() noexcept
    {
        static Hardware hardware;
        return hardware;
    }
    /**
     * @return Returns the type of a given pin. The pin types are changed by creation or destruction of hardware handles like GpioIn or GpioOut.
     */
    [[nodiscard]] PinType pinType(const Pin pin) const noexcept;

  private:
    Hardware() {}
};
}  // namespace rp2040
}  // namespace catta
#include "hardware_gpio/include/hardware/gpio.h"

[[nodiscard]] catta::rp2040::PinType catta::rp2040::Hardware::pinType(const Pin pin) const noexcept
{
    if (pin.isEmpty()) return PinType::empty();
    switch (gpio_get_function(pin))
    {
        case GPIO_FUNC_SIO:
            return gpio_get_dir(static_cast<unsigned int>(std::uint8_t(pin))) ? PinType::gpioOut() : PinType::gpioIn();
        case GPIO_FUNC_UART:
            switch (pin)
            {
                case rp2040::Pin::gp00():
                case rp2040::Pin::gp12():
                case rp2040::Pin::gp16():
                    return PinType::uart0Tx();
                case rp2040::Pin::gp01():
                case rp2040::Pin::gp13():
                case rp2040::Pin::gp17():
                    return PinType::uart0Rx();
                case rp2040::Pin::gp04():
                case rp2040::Pin::gp08():
                    return PinType::uart1Tx();
                case rp2040::Pin::gp05():
                case rp2040::Pin::gp09():
                    return PinType::uart1Rx();
                default:
                    return PinType::empty();
            }
        default:
            return PinType::empty();
    }
}
