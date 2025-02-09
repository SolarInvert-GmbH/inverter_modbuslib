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
 * @brief Represents the modbus master uart state.
 * @author CattaTech - Maik Urbannek
 */
class MasterUartState
{
  private:
    constexpr static std::uint8_t IDLE = 0;
    constexpr static std::uint8_t SEND = 1;
    constexpr static std::uint8_t RECEIVE = 2;
    constexpr static std::uint8_t ERROR_SEND_INVALID = 3;
    constexpr static std::uint8_t ERROR_RECEIVE_WITHOUT_REUQUEST = 4;
    constexpr static std::uint8_t ERROR_RECEIVE_LENGTH_NOT_VALID = 5;
    constexpr static std::uint8_t ERROR_RECEIVE_CODE_NOT_VALID = 6;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_MODBUS_ID = 7;
    constexpr static std::uint8_t ERROR_RECEIVE_WRONG_CRC = 8;
    constexpr static std::uint8_t ERROR_RECEIVE_TIMEOUT_NO_RESPONSE = 9;
    constexpr static std::uint8_t ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE = 10;
    constexpr static std::uint8_t EMPTY = 11;

  public:
    /**
     * @param[in] value The enum value of the state.
     * @warning This constructor should not be used. Use idle(), send(), receive(), errorSendInvalid(), errorReceiveWithoutReuquest(),
     * errorReceiveLengthNotValid(), errorReceiveCodeNotValid(), errorReceiveWrongModbusId(), errorReceiveWrongCrc(), errorReceiveTimeoutNoResponse(),
     * errorReceiveTimeoutPartialResponse() or empty(). Explicit constructor. Converts uint8 to state.
     */
    [[nodiscard]] constexpr explicit MasterUartState(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid state.
     */
    [[nodiscard]] constexpr MasterUartState() noexcept : MasterUartState(EMPTY) {}
    /**
     * @return Returns the idle state.
     */
    [[nodiscard]] constexpr static MasterUartState idle() noexcept { return MasterUartState{IDLE}; }
    /**
     * @return Returns the send state.
     */
    [[nodiscard]] constexpr static MasterUartState send() noexcept { return MasterUartState{SEND}; }
    /**
     * @return Returns the receive state.
     */
    [[nodiscard]] constexpr static MasterUartState receive() noexcept { return MasterUartState{RECEIVE}; }
    /**
     * @return Returns the error state (order of sent token is wrong).
     */
    [[nodiscard]] constexpr static MasterUartState errorSendInvalid() noexcept { return MasterUartState{ERROR_SEND_INVALID}; }
    /**
     * @return Returns the error state (received unexpected data).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveWithoutReuquest() noexcept { return MasterUartState{ERROR_RECEIVE_WITHOUT_REUQUEST}; }
    /**
     * @return Returns the error state (length field > 252).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveLengthNotValid() noexcept { return MasterUartState{ERROR_RECEIVE_LENGTH_NOT_VALID}; }
    /**
     * @return Returns the error state (exception code field have to be 1, 2, 3 or 4).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveCodeNotValid() noexcept { return MasterUartState{ERROR_RECEIVE_CODE_NOT_VALID}; }
    /**
     * @return Returns the error state (response has unexpected modbus id).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveWrongModbusId() noexcept { return MasterUartState{ERROR_RECEIVE_WRONG_MODBUS_ID}; }
    /**
     * @return Returns the error state (the received crc is wrong).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveWrongCrc() noexcept { return MasterUartState{ERROR_RECEIVE_WRONG_CRC}; }
    /**
     * @return Returns the error state (no response bytes received).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveTimeoutNoResponse() noexcept
    {
        return MasterUartState{ERROR_RECEIVE_TIMEOUT_NO_RESPONSE};
    }
    /**
     * @return Returns the error state (not enough response bytes where received).
     */
    [[nodiscard]] constexpr static MasterUartState errorReceiveTimeoutPartialResponse() noexcept
    {
        return MasterUartState{ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE};
    }
    /**
     * @return Returns the invalid state.
     */
    [[nodiscard]] constexpr static MasterUartState empty() noexcept { return MasterUartState{EMPTY}; }
    /**
     * @param[in] other The other MasterUartState.
     * @return Returns @b true if the two MasterUartState objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const MasterUartState& other) const = default;
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
     * @return Returns @b true if error state (exception code field have to be 1, 2, 3 or 4) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveCodeNotValid() const noexcept { return _value == ERROR_RECEIVE_CODE_NOT_VALID; }
    /**
     * @return Returns @b true if error state (response has unexpected modbus id) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isErrorReceiveWrongModbusId() const noexcept { return _value == ERROR_RECEIVE_WRONG_MODBUS_ID; }
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
                                                                      "ERROR_RECEIVE_WRONG_MODBUS_ID",
                                                                      "ERROR_RECEIVE_WRONG_CRC",
                                                                      "ERROR_RECEIVE_TIMEOUT_NO_RESPONSE",
                                                                      "ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE"};

  private:
    std::uint8_t _value;
};
}  // namespace modbus
}  // namespace catta
