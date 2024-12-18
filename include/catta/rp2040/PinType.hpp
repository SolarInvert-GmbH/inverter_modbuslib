#pragma once

// std
#include <array>
#include <cstdint>

namespace catta
{
namespace rp2040
{
/**
 * @brief Represent possible pin types to describe hardware configuration.
 * @author CattaTech - Maik Urbannek
 */
class PinType
{
  private:
    // @todo conflict with pico sdk GPIO_IN and GPIO_OUT are defined.
    static constexpr std::uint8_t GPIO_IN_ = 0;
    static constexpr std::uint8_t GPIO_OUT_ = 1;
    static constexpr std::uint8_t UART0_TX = 2;
    static constexpr std::uint8_t UART0_RX = 3;
    static constexpr std::uint8_t UART1_TX = 4;
    static constexpr std::uint8_t UART1_RX = 5;
    static constexpr std::uint8_t EMPTY = 6;

  public:
    /**
     * @param[in] value The enum value of the pin type.
     * @warning This constructor should not be used. Use gpioIn(), gpioOut(), uart0Tx(), uart0Rx(), uart1Tx(), uart1Rx() or empty().
     * Explicit constructor. Converts uint8 to data type.
     */
    [[nodiscard]] constexpr explicit PinType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid pin type.
     */
    [[nodiscard]] constexpr PinType() noexcept : PinType(EMPTY) {}
    /**
     * @return Returns the gpio in representation.
     */
    [[nodiscard]] constexpr static PinType gpioIn() noexcept { return PinType{GPIO_IN_}; }
    /**
     * @return Returns the gpio out representation.
     */
    [[nodiscard]] constexpr static PinType gpioOut() noexcept { return PinType{GPIO_OUT_}; }
    /**
     * @return Returns the uart0 tx representation.
     */
    [[nodiscard]] constexpr static PinType uart0Tx() noexcept { return PinType{UART0_TX}; }
    /**
     * @return Returns the uart0 rx representation.
     */
    [[nodiscard]] constexpr static PinType uart0Rx() noexcept { return PinType{UART0_RX}; }
    /**
     * @return Returns the uart1 tx representation.
     */
    [[nodiscard]] constexpr static PinType uart1Tx() noexcept { return PinType{UART1_TX}; }
    /**
     * @return Returns the uart1 rx representation.
     */
    [[nodiscard]] constexpr static PinType uart1Rx() noexcept { return PinType{UART1_RX}; }
    /**
     * @return Returns invalid pin type.
     */
    [[nodiscard]] constexpr static PinType empty() noexcept { return PinType{EMPTY}; }
    /**
     * @param[in] other The other PinType.
     * @return Returns @b true if the two PinType objects are the same, otherwise
     * @b false.
     */
    [[nodiscard]] constexpr bool operator==(const PinType &other) const noexcept { return this->_value == other._value; }
    /**
     * @param[in] other The other PinType.
     * @return Returns @b true if the two PinType objects are not the same,
     * otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator!=(const PinType &other) const noexcept { return !(*this == other); }
    /**
     * @return Returns the pin type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if the pin type is gpio in, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGpioIn() const noexcept { return _value == GPIO_IN_; }
    /**
     * @return Returns @b true if the pin type is gpio out, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGpioOut() const noexcept { return _value == GPIO_OUT_; }
    /**
     * @return Returns @b true if the pin type is uart0 tx, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUart0Tx() const noexcept { return _value == UART0_TX; }
    /**
     * @return Returns @b true if the pin type is uart0 rx, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUart0Rx() const noexcept { return _value == UART0_RX; }
    /**
     * @return Returns @b true if the pin type is uart1 tx, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUart1Tx() const noexcept { return _value == UART1_TX; }
    /**
     * @return Returns @b true if the pin type is uart1 rx, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUart1Rx() const noexcept { return _value == UART1_RX; }
    /**
     * @return Returns @b true if the pin type is invalid, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Pin types in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"GPIO_IN", "GPIO_OUT", "UART0_TX", "UART0_RX", "UART1_TX", "UART1_RX"};

  private:
    std::uint8_t _value;
};
}  // namespace rp2040
}  // namespace catta
