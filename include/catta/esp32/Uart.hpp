#pragma once

// std
#include <optional>

// esp32
#include <catta/esp32/Pin.hpp>

// catta
#include <catta/hardware/uart/Baudrate.hpp>
#include <catta/hardware/uart/DataBits.hpp>
#include <catta/hardware/uart/Parity.hpp>
#include <catta/hardware/uart/StopBits.hpp>
#include <catta/state/DefaultError.hpp>

namespace catta
{
namespace esp32
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
        other._device = EMPTY;
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
        other._device = EMPTY;
    }
    /**
     * @param[in] tx The pin for uart transive.
     * @param[in] rx The pin for uart receive.
     * @todo Check wether pin and uart is free is missing.
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
     * @param[in] tx The pin for uart transive.
     * @param[in] rx The pin for uart receive.
     * @todo Check wether pin and uart is free is missing.
     * @param[in] baudrate The baudrate for uart communication.
     * @param[in] parity The parity for uart communication. Can be empty for no parity.
     * @param[in] dataBits The data bits size for uart communication.  Can not be empty.
     * @param[in] stopBits The stop bits size for uart communication.  Can not be empty.
     * @return Returns uart handle for uart1 if tx,rx are possible uart0 pins and are free.
     */
    [[nodiscard]] static Uart device1(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
                                      const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                      const catta::hardware::uart::StopBits stopBits) noexcept;
    /**
     * @param[in] tx The pin for uart transive.
     * @param[in] rx The pin for uart receive.
     * @todo Check wether pin and uart is free is missing.
     * @param[in] baudrate The baudrate for uart communication.
     * @param[in] parity The parity for uart communication. Can be empty for no parity.
     * @param[in] dataBits The data bits size for uart communication.  Can not be empty.
     * @param[in] stopBits The stop bits size for uart communication.  Can not be empty.
     * @return Returns uart handle for uart2 if tx,rx are possible uart0 pins and are free.
     */
    [[nodiscard]] static Uart device2(const Pin tx, const Pin rx, const catta::hardware::uart::Baudrate baudrate,
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
    [[nodiscard]] bool isEmpty() const noexcept { return _device == EMPTY; }
    /**
     * @return Returns an invalid/empty handle.
     */
    [[nodiscard]] static Uart empty() noexcept { return Uart{Pin::empty(), Pin::empty(), EMPTY}; }
    /**
     * Enum class of possible uart errors.
     */
    typedef typename catta::state::DefaultError Error;
    /**
     * @return Returns the uart error
     */
    [[nodiscard]] Error error() const noexcept { return catta::state::DefaultError::empty(); }
    Uart(const Uart &) = delete;
    Uart operator=(const Uart &) = delete;

  private:
    Uart(const Pin tx, const Pin rx, int device) : _tx(tx), _rx(rx), _device(device) {}
    Pin _tx;
    Pin _rx;
    int _device;
    constexpr static int EMPTY = 3;
    void remove() noexcept;
    static Uart createUart(const Pin tx, const Pin rx, const int device, const catta::hardware::uart::Baudrate baudrate,
                           const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                           const catta::hardware::uart::StopBits stopBits) noexcept;
};
}  // namespace esp32
}  // namespace catta

#include "driver/uart/include/driver/uart.h"

catta::esp32::Uart catta::esp32::Uart::createUart(const Pin tx, const Pin rx, const int device, const catta::hardware::uart::Baudrate baudrate,
                                                  const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                                  const catta::hardware::uart::StopBits stopBits) noexcept
{
    if (tx.isEmpty() || rx.isEmpty() || baudrate.isEmpty() || dataBits.isEmpty() || stopBits.isEmpty()) return empty();
    const auto data_bits = [dataBits]() -> uart_word_length_t
    {
        switch (dataBits)
        {
            case catta::hardware::uart::DataBits::five():
                return UART_DATA_5_BITS;
            case catta::hardware::uart::DataBits::six():
                return UART_DATA_6_BITS;
            case catta::hardware::uart::DataBits::seven():
                return UART_DATA_7_BITS;
            default:
                return UART_DATA_8_BITS;
        }
    }();
    const auto stop_bits = [stopBits]() -> uart_stop_bits_t
    {
        switch (stopBits)
        {
            case catta::hardware::uart::StopBits::one():
                return UART_STOP_BITS_1;
            default:
                return UART_STOP_BITS_2;
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
                return UART_PARITY_DISABLE;
        }
    }();
    uart_config_t uart_config = {.baud_rate = static_cast<int>(baudrate.asInteger()),
                                 .data_bits = data_bits,
                                 .parity = p,
                                 .stop_bits = stop_bits,
                                 .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
                                 .rx_flow_ctrl_thresh = 0,
                                 .source_clk = UART_SCLK_APB};
    if (uart_driver_install(static_cast<uart_port_t>(device), 2048, 0, 0, nullptr, 0) != ESP_OK) return empty();
    if (uart_param_config(static_cast<uart_port_t>(device), &uart_config) != ESP_OK ||
        uart_set_pin(static_cast<uart_port_t>(device), static_cast<int>(std::uint8_t(tx)), static_cast<int>(std::uint8_t(rx)), -1, -1) != ESP_OK)
    {
        uart_is_driver_installed(static_cast<uart_port_t>(device));
        return empty();
    }
    return Uart(tx, rx, device);
}

[[nodiscard]] catta::esp32::Uart catta::esp32::Uart::device0(const catta::esp32::Pin tx, const catta::esp32::Pin rx,
                                                             const catta::hardware::uart::Baudrate baudrate,
                                                             const catta::hardware::uart::Parity parity,
                                                             const catta::hardware::uart::DataBits dataBits,
                                                             const catta::hardware::uart::StopBits stopBits) noexcept
{
    return createUart(tx, rx, UART_NUM_0, baudrate, parity, dataBits, stopBits);
}

[[nodiscard]] catta::esp32::Uart catta::esp32::Uart::device1(const catta::esp32::Pin tx, const catta::esp32::Pin rx,
                                                             const catta::hardware::uart::Baudrate baudrate,
                                                             const catta::hardware::uart::Parity parity,
                                                             const catta::hardware::uart::DataBits dataBits,
                                                             const catta::hardware::uart::StopBits stopBits) noexcept
{
    return createUart(tx, rx, UART_NUM_1, baudrate, parity, dataBits, stopBits);
}

[[nodiscard]] catta::esp32::Uart catta::esp32::Uart::device2(const catta::esp32::Pin tx, const catta::esp32::Pin rx,
                                                             const catta::hardware::uart::Baudrate baudrate,
                                                             const catta::hardware::uart::Parity parity,
                                                             const catta::hardware::uart::DataBits dataBits,
                                                             const catta::hardware::uart::StopBits stopBits) noexcept
{
    return createUart(tx, rx, UART_NUM_2, baudrate, parity, dataBits, stopBits);
}

void catta::esp32::Uart::remove() noexcept { uart_is_driver_installed(static_cast<uart_port_t>(_device)); }

bool catta::esp32::Uart::write(const char c) const noexcept { return uart_tx_chars(static_cast<uart_port_t>(_device), &c, 1) == 1; }

std::optional<char> catta::esp32::Uart::read() const noexcept
{
    char c = '\0';
    return uart_read_bytes(static_cast<uart_port_t>(_device), &c, 1, 0) == 1 ? std::optional<char>{c} : std::optional<char>{};
}
