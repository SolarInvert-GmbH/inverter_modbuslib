#pragma once

// std
#include <optional>

// rp2040
#include <catta/rp2040/Pin.hpp>

// catta
#include <catta/hardware/uart/Baudrate.hpp>
#include <catta/hardware/uart/DataBits.hpp>
#include <catta/hardware/uart/Parity.hpp>
#include <catta/hardware/uart/StopBits.hpp>

namespace catta
{
namespace rp2040
{
class PinType;
/**
 * @brief Class to handle uart communication.
 * @author CattaTech - Maik Urbannek
 */
class Uart
{
  public:
    /**
     * Destructor. Frees uart handle.
     */
    ~Uart() noexcept { remove(); }
    /**
     * Move constructor.
     * @param[in,out] other Other uart handle. Moves handle in this uart. Other uart is empty afterwards.
     */
    [[nodiscard]] Uart(Uart &&other) noexcept : _tx(other._tx), _rx(other._rx), _device(other._device)
    {
        other._tx = Pin::empty();
        other._rx = Pin::empty();
        other._device = nullptr;
    }
    /**
     * Move assigment. If this uart handle was not empty befor the uart is freed.
     * @param[in,out] other Other uart handle. Moves handle in this uart. Other uart is empty afterwards.
     */
    void operator=(Uart &&other) noexcept
    {
        remove();
        _tx = other._tx;
        _rx = other._rx;
        _device = other._device;
        other._tx = Pin::empty();
        other._rx = Pin::empty();
        other._device = nullptr;
    }
    /**
     * @param[in] tx The pin for uart transive. Can only be gp00, gp12 or gp16.
     * @param[in] rx The pin for uart receive. Can only be gp01, gp13 or gp17.
     * @param[in] baudrate The baudrate for uart communication.
     * @param[in] parity The parity for uart communication. Can be empty for no parity.
     * @param[in] dataBits The data bits size for uart communication.  Can not be empty.
     * @param[in] stopBits The stop bits size for uart communication.  Can not be empty.
     * @return Returns uart handle for uart0 if tx,rx are possible uart0 pins and are free.
     */
    [[nodiscard]] static Uart device0(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
                                      const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                      const catta::hardware::uart::StopBits stopBits) noexcept;
    /**
     * @param[in] tx The pin for uart transive. Can only be gp04 or gp08.
     * @param[in] rx The pin for uart receive. Can only be gp05 or gp09.
     * @param[in] baudrate The baudrate for uart communication.
     * @param[in] parity The parity for uart communication. Can be empty for no parity.
     * @param[in] dataBits The data bits size for uart communication.  Can not be empty.
     * @param[in] stopBits The stop bits size for uart communication.  Can not be empty.
     * @return Returns uart handle for uart1 if tx,rx are possible uart1 pins and are free.
     */
    [[nodiscard]] static Uart device1(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
                                      const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                      const catta::hardware::uart::StopBits stopBits) noexcept;
    /**
     * @param[in] c The character to send via uart handle.
     * @return Returns @b true if the character was send, otherwise @b false. If @b false is returned, the character has to bes sent again.
     * @warning Do not use on invalid/empty handle.
     */
    [[nodiscard]] bool write(const char c) const noexcept;
    /**
     * @return Returns a character if received via uart, otherwise empty.
     */
    [[nodiscard]] std::optional<char> read() const noexcept;
    /**
     * @return Returns @b true if uart handle is invalid/empty, otherwise @b false.
     */
    [[nodiscard]] bool isEmpty() const noexcept { return _device == nullptr; }
    /**
     * @return Returns an invalid/empty handle.
     */
    [[nodiscard]] static Uart empty() noexcept { return Uart{Pin::empty(), Pin::empty(), nullptr}; }
    Uart(const Uart &) = delete;
    Uart operator=(const Uart &) = delete;

  private:
    Uart(const Pin tx, const Pin rx, void *device) : _tx(tx), _rx(rx), _device(device) {}
    Pin _tx;
    Pin _rx;
    void *_device;
    void remove() noexcept;
    static Uart createUart(const Pin tx, const Pin rx, void *device, const std::uint32_t baudrate, const catta::hardware::uart::Parity parity,
                           const catta::hardware::uart::DataBits dataBits, const catta::hardware::uart::StopBits stopBits) noexcept;
    template <std::size_t SIZE>
    static bool uartNotUsedAndPinIsFree(const std::array<rp2040::Pin, SIZE> &pinArray, const rp2040::Pin pin,
                                        const rp2040::PinType notAllowedPinType);
};
}  // namespace rp2040
}  // namespace catta

//
#include <catta/rp2040/Hardware.hpp>
#include <catta/rp2040/PinType.hpp>

//
#include "hardware_gpio/include/hardware/gpio.h"
#include "hardware_uart/include/hardware/uart.h"

template <std::size_t SIZE>
bool catta::rp2040::Uart::uartNotUsedAndPinIsFree(const std::array<rp2040::Pin, SIZE> &pinArray, const rp2040::Pin pin,
                                                  const rp2040::PinType notAllowedPinType)
{
    bool value = false;
    for (std::size_t i = 0; i < SIZE; i++)
    {
        const auto pinType = rp2040::Hardware::get().pinType(pinArray[i]);
        if (pin == pinArray[i])
        {
            if (!pinType.isEmpty()) return false;
            value = true;
        }
        if (pinType == notAllowedPinType) return false;
    }
    return value;
}

catta::rp2040::Uart catta::rp2040::Uart::createUart(const Pin tx, const Pin rx, void *device, const std::uint32_t baudrate,
                                                    const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                                    const catta::hardware::uart::StopBits stopBits) noexcept
{
    uart_inst_t *pointer = static_cast<uart_inst_t *>(device);
    const auto data_bits = [dataBits]() -> uint
    {
        switch (dataBits)
        {
            case catta::hardware::uart::DataBits::five():
                return 5;
            case catta::hardware::uart::DataBits::six():
                return 6;
            case catta::hardware::uart::DataBits::seven():
                return 7;
            case catta::hardware::uart::DataBits::eight():
                return 8;
            default:
                return 0;
        }
    }();
    const auto stop_bits = [stopBits]() -> uint
    {
        switch (stopBits)
        {
            case catta::hardware::uart::StopBits::one():
                return 1;
            case catta::hardware::uart::StopBits::two():
                return 2;
            default:
                return 0;
        }
    }();
    const auto p = [parity]() -> uart_parity_t
    {
        switch (parity)
        {
            case catta::hardware::uart::Parity::even():
                return UART_PARITY_EVEN;
            case catta::hardware::uart::Parity::odd():
                return UART_PARITY_ODD;
            default:
                return UART_PARITY_NONE;
        }
    }();
    if (data_bits == 0 || stop_bits == 0) return empty();
    gpio_set_function(tx, GPIO_FUNC_UART);
    gpio_set_function(rx, GPIO_FUNC_UART);
    if (uart_init(pointer, static_cast<uint>(baudrate)) == 0)
    {
        gpio_set_function(tx, GPIO_FUNC_NULL);
        gpio_set_function(rx, GPIO_FUNC_NULL);
        return empty();
    }
    uart_set_format(pointer, data_bits, stop_bits, p);
    return Uart{tx, rx, pointer};
}

[[nodiscard]] catta::rp2040::Uart catta::rp2040::Uart::device0(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
                                                               const catta::hardware::uart::Parity parity,
                                                               const catta::hardware::uart::DataBits dataBits,
                                                               const catta::hardware::uart::StopBits stopBits) noexcept
{
    const auto txPins = std::array<rp2040::Pin, 3>{rp2040::Pin::gp00(), rp2040::Pin::gp12(), rp2040::Pin::gp16()};
    const auto rxPins = std::array<rp2040::Pin, 3>{rp2040::Pin::gp01(), rp2040::Pin::gp13(), rp2040::Pin::gp17()};
    if (!uartNotUsedAndPinIsFree<3>(txPins, tx, rp2040::PinType::uart0Tx()) || !uartNotUsedAndPinIsFree<3>(rxPins, rx, rp2040::PinType::uart0Rx()))
        return empty();
    return createUart(tx, rx, uart0, baudrate.asInteger(), parity, dataBits, stopBits);
}

[[nodiscard]] catta::rp2040::Uart catta::rp2040::Uart::device1(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
                                                               const catta::hardware::uart::Parity parity,
                                                               const catta::hardware::uart::DataBits dataBits,
                                                               const catta::hardware::uart::StopBits stopBits) noexcept
{
    const auto txPins = std::array<rp2040::Pin, 2>{rp2040::Pin::gp04(), rp2040::Pin::gp08()};
    const auto rxPins = std::array<rp2040::Pin, 2>{rp2040::Pin::gp05(), rp2040::Pin::gp09()};
    if (!uartNotUsedAndPinIsFree<2>(txPins, tx, rp2040::PinType::uart1Tx()) || !uartNotUsedAndPinIsFree<2>(rxPins, rx, rp2040::PinType::uart1Rx()))
        return empty();
    return createUart(tx, rx, uart1, baudrate.asInteger(), parity, dataBits, stopBits);
}

void catta::rp2040::Uart::remove() noexcept
{
    if (_device)
    {
        uart_deinit(static_cast<uart_inst_t *>(_device));
        gpio_set_function(_tx, GPIO_FUNC_NULL);
        gpio_set_function(_rx, GPIO_FUNC_NULL);
    }
}

[[nodiscard]] bool catta::rp2040::Uart::write(const char c) const noexcept
{
    uart_inst_t *uart = static_cast<uart_inst_t *>(_device);
    if (!uart_is_writable(uart)) return false;
    uart_putc_raw(uart, c);
    return true;
}
[[nodiscard]] std::optional<char> catta::rp2040::Uart::read() const noexcept
{
    uart_inst_t *uart = static_cast<uart_inst_t *>(_device);
    return uart_is_readable((uart)) ? std::optional<char>(uart_getc(uart)) : std::optional<char>();
}
