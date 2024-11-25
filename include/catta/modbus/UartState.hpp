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
 * @brief Represents the modbus uart state.
 * @author CattaTech - Maik Urbannek
 */
class UartState
{
  private:
    constexpr static std::uint8_t IDLE = 0;
    constexpr static std::uint8_t SEND = 1;
    constexpr static std::uint8_t RECEIVE = 2;
    constexpr static std::uint8_t ERROR_SEND_INVALID = 3;
    constexpr static std::uint8_t ERROR_RECEIVE_WITHOUT_REUQUEST = 4;
    constexpr static std::uint8_t ERROR_RECEIVE_LENGTH_NOT_VALID = 5;
    constexpr static std::uint8_t ERROR_RECEIVE_CODE_NOT_VALID = 6;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_ADDRESS = 7;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_ECHO = 8;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_CRC = 9;
    constexpr static std::uint8_t ERROR_RECEIVE_TIMEOUT_NO_RESPONSE = 10;
    constexpr static std::uint8_t ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE = 11;
    constexpr static std::uint8_t EMPTY = 12;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @warning This constructor should not be used. Use idle(), send(), receive(), errorSendInvalid(), errorReceiveWithoutReuquest(),
     * errorReceiveLengthNotValid(), errorReceiveCodeNotValid(), errorReceiveWrongAddress(), errorReceiveWrongEcho(), errorReceiveWrongCrc(),
     * errorReceiveTimeoutNoResponse(), errorReceiveTimeoutPartialResponse() or empty(). Explicit constructor. Converts uint8 to state.
     */
    [[nodiscard]] constexpr explicit UartState(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid state.
     */
    [[nodiscard]] constexpr UartState() noexcept : UartState(EMPTY) {}
    /**
     * @return Returns the idle state.
     */
    [[nodiscard]] constexpr static UartState idle() noexcept { return UartState{IDLE}; }
    /**
     * @return Returns the send state.
     */
    [[nodiscard]] constexpr static UartState send() noexcept { return UartState{SEND}; }
    /**
     * @return Returns the receive state.
     */
    [[nodiscard]] constexpr static UartState receive() noexcept { return UartState{RECEIVE}; }
    /**
     * @return Returns the error state (order of sent token is wrong).
     */
    [[nodiscard]] constexpr static UartState errorSendInvalid() noexcept { return UartState{ERROR_SEND_INVALID}; }
    /**
     * @return Returns the error state (received unexpected data).
     */
    [[nodiscard]] constexpr static UartState errorReceiveWithoutReuquest() noexcept { return UartState{ERROR_RECEIVE_WITHOUT_REUQUEST}; }
    /**
     * @return Returns the error state (length field > 252).
     */
    [[nodiscard]] constexpr static UartState errorReceiveLengthNotValid() noexcept { return UartState{ERROR_RECEIVE_LENGTH_NOT_VALID}; }
    /**
     * @return Returns the error state (exeception code field have to be 1, 2, 3 or 4).
     */
    [[nodiscard]] constexpr static UartState errorReceiveCodeNotValid() noexcept { return UartState{ERROR_RECEIVE_CODE_NOT_VALID}; }
    /**
     * @return Returns the error state (response has unexpected address).
     */
    [[nodiscard]] constexpr static UartState errorReceiveWrongAddress() noexcept { return UartState{ERROR_RECEIVE_WRONG_ADDRESS}; }
    /**
     * @return Returns the error state (response is not like request).
     */
    [[nodiscard]] constexpr static UartState errorReceiveWrongEcho() noexcept { return UartState{ERROR_RECEIVE_WRONG_ECHO}; }
    /**
     * @return Returns the error state (the received crc is wrong).
     */
    [[nodiscard]] constexpr static UartState errorReceiveWrongCrc() noexcept { return UartState{ERROR_RECEIVE_WRONG_CRC}; }
    /**
     * @return Returns the error state (no response bytes received).
     */
    [[nodiscard]] constexpr static UartState errorReceiveTimeoutNoResponse() noexcept { return UartState{ERROR_RECEIVE_TIMEOUT_NO_RESPONSE}; }
    /**
     * @return Returns the error state (not enough response bytes where received).
     */
    [[nodiscard]] constexpr static UartState errorReceiveTimeoutPartialResponse() noexcept
    {
        return UartState{ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE};
    }
    /**
     * @return Returns the invalid state.
     */
    [[nodiscard]] constexpr static UartState empty() noexcept { return UartState{EMPTY}; }
    /**
     * @param[in] other The other UartState.
     * @return Returns @b true if the two UartState objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const UartState& other) const = default;
    /**
     * @return Returns state as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if idle state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isIdle() const noexcept { return _value == IDLE; }
    /**
     * @return Returns @b true if send state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSend() const noexcept { return _value == SEND; }
    /**
     * @return Returns @b true if receive state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReceive() const noexcept { return _value == RECEIVE; }
    /**
     * @return Returns @b true if error state (order of sent token is wrong) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorSendInvalid() const noexcept { return _value == ERROR_SEND_INVALID; }
    /**
     * @return Returns @b true if error state (received unexpected data) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWithoutReuquest() const noexcept { return _value == ERROR_RECEIVE_WITHOUT_REUQUEST; }
    /**
     * @return Returns @b true if error state (length field > 252) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveLengthNotValid() const noexcept { return _value == ERROR_RECEIVE_LENGTH_NOT_VALID; }
    /**
     * @return Returns @b true if error state (exeception code field have to be 1, 2, 3 or 4) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveCodeNotValid() const noexcept { return _value == ERROR_RECEIVE_CODE_NOT_VALID; }
    /**
     * @return Returns @b true if error state (response has unexpected address) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWrongAddress() const noexcept { return _value == ERROR_RECEIVE_WRONG_ADDRESS; }
    /**
     * @return Returns @b true if error state (response is not like request) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWrongEcho() const noexcept { return _value == ERROR_RECEIVE_WRONG_ECHO; }
    /**
     * @return Returns @b true if error state (the received crc is wrong) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWrongCrc() const noexcept { return _value == ERROR_RECEIVE_WRONG_CRC; }
    /**
     * @return Returns @b true if error state (no response bytes received) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveTimeoutNoResponse() const noexcept { return _value == ERROR_RECEIVE_TIMEOUT_NO_RESPONSE; }
    /**
     * @return Returns @b true if error state (not enough response bytes where received) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveTimeoutPartialResponse() const noexcept { return _value == ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE; }
    /**
     * @return Returns @b true if invalid state is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * State in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"IDLE",
                                                                      "SEND",
                                                                      "RECEIVE",
                                                                      "ERROR_SEND_INVALID",
                                                                      "ERROR_RECEIVE_WITHOUT_REUQUEST",
                                                                      "ERROR_RECEIVE_LENGTH_NOT_VALID",
                                                                      "ERROR_RECEIVE_CODE_NOT_VALID",
                                                                      "ERROR_RECEIVE_WRONG_ADDRESS",
                                                                      "ERROR_RECEIVE_WRONG_ECHO",
                                                                      "ERROR_RECEIVE_WRONG_CRC",
                                                                      "ERROR_RECEIVE_TIMEOUT_NO_RESPONSE",
                                                                      "ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE"};

  private:
    std::uint8_t _value;
};
}  // namespace modbus
}  // namespace catta
