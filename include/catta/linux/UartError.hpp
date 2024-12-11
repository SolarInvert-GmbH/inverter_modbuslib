#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace linux
{
/**
 * @brief Represents the possible error when using catta::os::Uart.
 * @author CattaTech - Maik Urbannek
 */
class UartError
{
  private:
    constexpr static std::uint8_t INVALID_BAUDRATE = 0;
    constexpr static std::uint8_t COULD_NOT_SET_BAUDRATE = 1;
    constexpr static std::uint8_t COULD_NOT_OPEN_DEVICE = 2;
    constexpr static std::uint8_t DEVICE_IS_BUSY = 3;
    constexpr static std::uint8_t COULD_NOT_BIND = 4;
    constexpr static std::uint8_t WRITE_FAILED = 5;
    constexpr static std::uint8_t READ_FAILED = 6;
    constexpr static std::uint8_t CLOSED = 7;
    constexpr static std::uint8_t EMPTY = 8;

  public:
    /**
     * @param[in] value The enum value of the uart error.
     * @warning This constructor should not be used. Use invalidBaudrate(), couldNotSetBaudrate(), couldNotOpenDevice(), deviceIsBusy(),
     * couldNotBind(), writeFailed(), readFailed(), closed() or empty(). Explicit constructor. Converts uint8 to uart error.
     */
    [[nodiscard]] constexpr explicit UartError(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty error.
     */
    [[nodiscard]] constexpr UartError() noexcept : UartError(EMPTY) {}
    /**
     * @return Returns the invalid baudrate when creating uart.
     */
    [[nodiscard]] constexpr static UartError invalidBaudrate() noexcept { return UartError{INVALID_BAUDRATE}; }
    /**
     * @return Returns the error where setting of baudrate failed.
     */
    [[nodiscard]] constexpr static UartError couldNotSetBaudrate() noexcept { return UartError{COULD_NOT_SET_BAUDRATE}; }
    /**
     * @return Returns the error where devive could not opened.
     */
    [[nodiscard]] constexpr static UartError couldNotOpenDevice() noexcept { return UartError{COULD_NOT_OPEN_DEVICE}; }
    /**
     * @return Returns the error where device is already used.
     */
    [[nodiscard]] constexpr static UartError deviceIsBusy() noexcept { return UartError{DEVICE_IS_BUSY}; }
    /**
     * @return Returns the error where device could bound.
     */
    [[nodiscard]] constexpr static UartError couldNotBind() noexcept { return UartError{COULD_NOT_BIND}; }
    /**
     * @return Returns the error where write failed.
     */
    [[nodiscard]] constexpr static UartError writeFailed() noexcept { return UartError{WRITE_FAILED}; }
    /**
     * @return Returns the error where read failed.
     */
    [[nodiscard]] constexpr static UartError readFailed() noexcept { return UartError{READ_FAILED}; }
    /**
     * @return Returns the where the uart is closed.
     */
    [[nodiscard]] constexpr static UartError closed() noexcept { return UartError{CLOSED}; }
    /**
     * @return Returns the empty error.
     */
    [[nodiscard]] constexpr static UartError empty() noexcept { return UartError{EMPTY}; }
    /**
     * @param[in] other The other UartError.
     * @return Returns @b true if the two UartError objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const UartError& other) const = default;
    /**
     * @return Returns uart error as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if invalid baudrate when creating uart is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInvalidBaudrate() const noexcept { return _value == INVALID_BAUDRATE; }
    /**
     * @return Returns @b true if error where setting of baudrate failed is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCouldNotSetBaudrate() const noexcept { return _value == COULD_NOT_SET_BAUDRATE; }
    /**
     * @return Returns @b true if error where devive could not opened is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCouldNotOpenDevice() const noexcept { return _value == COULD_NOT_OPEN_DEVICE; }
    /**
     * @return Returns @b true if error where device is already used is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isDeviceIsBusy() const noexcept { return _value == DEVICE_IS_BUSY; }
    /**
     * @return Returns @b true if error where device could bound is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCouldNotBind() const noexcept { return _value == COULD_NOT_BIND; }
    /**
     * @return Returns @b true if error where write failed is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isWriteFailed() const noexcept { return _value == WRITE_FAILED; }
    /**
     * @return Returns @b true if error where read failed is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadFailed() const noexcept { return _value == READ_FAILED; }
    /**
     * @return Returns @b true if where the uart is closed is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isClosed() const noexcept { return _value == CLOSED; }
    /**
     * @return Returns @b true if empty error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Uart error in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {
        "INVALID_BAUDRATE", "COULD_NOT_SET_BAUDRATE", "COULD_NOT_OPEN_DEVICE", "DEVICE_IS_BUSY",
        "COULD_NOT_BIND",   "WRITE_FAILED",           "READ_FAILED",           "CLOSED"};

  private:
    std::uint8_t _value;
};
}  // namespace linux
}  // namespace catta
