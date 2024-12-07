#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
/**
 * @brief Represents the modbus slave uart state.
 * @author CattaTech - Maik Urbannek
 */
class SlaveUartState
{
  private:
    constexpr static std::uint8_t IDLE = 0;
    constexpr static std::uint8_t RECEIVE = 1;
    constexpr static std::uint8_t SEND = 2;
    constexpr static std::uint8_t ERROR_SEND_INVALID = 3;
    constexpr static std::uint8_t ERROR_RECEIVE_CURRING_SEND = 4;
    constexpr static std::uint8_t ERROR_RECEIVE_LENGTH_NOT_VALID = 5;
    constexpr static std::uint8_t ERROR_RECEIVE_CODE_NOT_VALID = 6;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_CRC = 7;
    constexpr static std::uint8_t ERROR_RECEIVE_TIMEOUT_PARTIAL_REQUEST = 8;
    constexpr static std::uint8_t EMPTY = 9;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @warning This constructor should not be used. Use idle(), receive(), send(), errorSendInvalid(), errorReceiveCurringSend(),
     * errorReceiveLengthNotValid(), errorReceiveCodeNotValid(), errorReceiveWrongCrc(), errorReceiveTimeoutPartialRequest() or empty(). Explicit
     * constructor. Converts uint8 to state.
     */
    [[nodiscard]] constexpr explicit SlaveUartState(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid state.
     */
    [[nodiscard]] constexpr SlaveUartState() noexcept : SlaveUartState(EMPTY) {}
    /**
     * @return Returns the idle state.
     */
    [[nodiscard]] constexpr static SlaveUartState idle() noexcept { return SlaveUartState{IDLE}; }
    /**
     * @return Returns the receive state.
     */
    [[nodiscard]] constexpr static SlaveUartState receive() noexcept { return SlaveUartState{RECEIVE}; }
    /**
     * @return Returns the send state.
     */
    [[nodiscard]] constexpr static SlaveUartState send() noexcept { return SlaveUartState{SEND}; }
    /**
     * @return Returns the error state (order of sent token is wrong).
     */
    [[nodiscard]] constexpr static SlaveUartState errorSendInvalid() noexcept { return SlaveUartState{ERROR_SEND_INVALID}; }
    /**
     * @return Returns the error state (received curring send).
     */
    [[nodiscard]] constexpr static SlaveUartState errorReceiveCurringSend() noexcept { return SlaveUartState{ERROR_RECEIVE_CURRING_SEND}; }
    /**
     * @return Returns the error state (length field > 252).
     */
    [[nodiscard]] constexpr static SlaveUartState errorReceiveLengthNotValid() noexcept { return SlaveUartState{ERROR_RECEIVE_LENGTH_NOT_VALID}; }
    /**
     * @return Returns the error state (exception code field have to be 1, 2, 3 or 4).
     */
    [[nodiscard]] constexpr static SlaveUartState errorReceiveCodeNotValid() noexcept { return SlaveUartState{ERROR_RECEIVE_CODE_NOT_VALID}; }
    /**
     * @return Returns the error state (the received crc is wrong).
     */
    [[nodiscard]] constexpr static SlaveUartState errorReceiveWrongCrc() noexcept { return SlaveUartState{ERROR_RECEIVE_WRONG_CRC}; }
    /**
     * @return Returns the error state (not enough request bytes where received).
     */
    [[nodiscard]] constexpr static SlaveUartState errorReceiveTimeoutPartialRequest() noexcept
    {
        return SlaveUartState{ERROR_RECEIVE_TIMEOUT_PARTIAL_REQUEST};
    }
    /**
     * @return Returns the invalid state.
     */
    [[nodiscard]] constexpr static SlaveUartState empty() noexcept { return SlaveUartState{EMPTY}; }
    /**
     * @param[in] other The other SlaveUartState.
     * @return Returns @b true if the two SlaveUartState objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const SlaveUartState& other) const = default;
    /**
     * @return Returns state as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if idle state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isIdle() const noexcept { return _value == IDLE; }
    /**
     * @return Returns @b true if receive state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReceive() const noexcept { return _value == RECEIVE; }
    /**
     * @return Returns @b true if send state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSend() const noexcept { return _value == SEND; }
    /**
     * @return Returns @b true if error state (order of sent token is wrong) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorSendInvalid() const noexcept { return _value == ERROR_SEND_INVALID; }
    /**
     * @return Returns @b true if error state (received curring send) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveCurringSend() const noexcept { return _value == ERROR_RECEIVE_CURRING_SEND; }
    /**
     * @return Returns @b true if error state (length field > 252) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveLengthNotValid() const noexcept { return _value == ERROR_RECEIVE_LENGTH_NOT_VALID; }
    /**
     * @return Returns @b true if error state (exception code field have to be 1, 2, 3 or 4) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveCodeNotValid() const noexcept { return _value == ERROR_RECEIVE_CODE_NOT_VALID; }
    /**
     * @return Returns @b true if error state (the received crc is wrong) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWrongCrc() const noexcept { return _value == ERROR_RECEIVE_WRONG_CRC; }
    /**
     * @return Returns @b true if error state (not enough request bytes where received) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveTimeoutPartialRequest() const noexcept { return _value == ERROR_RECEIVE_TIMEOUT_PARTIAL_REQUEST; }
    /**
     * @return Returns @b true if invalid state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * State in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"IDLE",
                                                                      "RECEIVE",
                                                                      "SEND",
                                                                      "ERROR_SEND_INVALID",
                                                                      "ERROR_RECEIVE_CURRING_SEND",
                                                                      "ERROR_RECEIVE_LENGTH_NOT_VALID",
                                                                      "ERROR_RECEIVE_CODE_NOT_VALID",
                                                                      "ERROR_RECEIVE_WRONG_CRC",
                                                                      "ERROR_RECEIVE_TIMEOUT_PARTIAL_REQUEST"};

  private:
    std::uint8_t _value;
};
}  // namespace modbus
}  // namespace catta
