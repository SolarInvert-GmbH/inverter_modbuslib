#pragma once

// modbus
#include <catta/modbus/Token.hpp>
#include <catta/modbus/UartState.hpp>
#include <catta/parser/InputHandled.hpp>

// std
#include <chrono>
#include <optional>
#include <tuple>

namespace catta
{
namespace modbus
{
/**
 * @brief Handles bytestream and modbus token stream two way conversion.
 *
 * This implements unicast master communiction. This class can send request and waits for the responsen. Other communiction on bus leads to errors.
 *
 * @author CattaTech - Maik Urbannek
 */
class Uart
{
  public:
    /**
     * Default constructor.
     */
    constexpr Uart() noexcept : _state(IDLE), _length(0), _index(0), _crc(0xffff), _waitUntil{} {}
    /**
     * @param[in] now Current time.
     * @param[in] received The bytes received from modbus.
     * @param[in] send The token to send. The input handled will be set, if send token was handled. Send token can only be handled in idle state.
     * @param[in] address The address of the slave.
     * @return Returns tuple of :
     *    - the current state of the modbus uart
     *    - the receive token, that represents the input @b received bytes
     *    - the bytes to send, that represents the input @b send token
     *    - the input handled, that is @b handledYes if the @b send token was handled, otherwiese @b HandeledNo. On @b HandeledNo the work methode has
     * to be called next time with the same send token.
     */
    constexpr std::tuple<catta::modbus::UartState, catta::modbus::Token, std::optional<std::uint8_t>, catta::parser::InputHandled> work(
        const std::chrono::microseconds now, const std::optional<std::uint8_t> received, const catta::modbus::Token send, const std::uint8_t address)
    {
        using State = catta::modbus::UartState;
        using Token = catta::modbus::Token;
        using Byte = std::optional<std::uint8_t>;
        using Handled = catta::parser::InputHandled;
        using Tuple = std::tuple<State, Token, Byte, Handled>;
        const auto getErrorState = [this]()
        {
            switch (_state)
            {
                case ERROR_SEND_INVALID:
                    return State::errorSendInvalid();
                case ERROR_RECEIVE_WITHOUT_REUQUEST:
                    return State::errorReceiveWithoutReuquest();
                case ERROR_RECEIVE_LENGTH_NOT_VALID:
                    return State::errorReceiveLengthNotValid();
                case ERROR_RECEIVE_CODE_NOT_VALID:
                    return State::errorReceiveCodeNotValid();
                case ERROR_RECEIVE_WRONG_ADDRESS:
                    return State::errorReceiveWrongAddress();
                case ERROR_RECEIVE_WRONG_ECHO:
                    return State::errorReceiveWrongEcho();
                case ERROR_RECEIVE_WRONG_CRC:
                    return State::errorReceiveWrongCrc();
                case ERROR_RECEIVE_TIMEOUT_NO_RESPONSE:
                    return State::errorReceiveTimeoutNoResponse();
                case ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE:
                    return State::errorReceiveTimeoutPartialResponse();
                default:
                    return State::empty();
            }
        };
        const auto error = [now, this, getErrorState](const std::uint8_t state)
        {
            _state = state;
            _waitUntil = now + stayInError;
            return Tuple{getErrorState(), Token::empty(), Byte{}, Handled::yes()};
        };
        const auto computeCrc = [this](const std::uint8_t data)
        {
            const std::uint16_t v = data;
            _crc = ((_crc ^ v) | 0xFF00) & (_crc | 0x00FF);
            for (std::uint8_t i = 0; i < 8; i++)
            {
                const bool leastSignifcantByteSet = _crc & 0x0001;
                _crc = _crc / 2;
                if (leastSignifcantByteSet) _crc = _crc ^ 0xA001;
            }
        };
        const auto stay = [](const catta::modbus::UartState state) { return Tuple{state, Token::empty(), Byte{}, Handled::no()}; };
        const auto sendCrc0 = [this]()
        {
            _state = SEND_CRC1;
            return Tuple{State::send(), Token::empty(), Byte{static_cast<std::uint8_t>((_crc >> 0) & 0xff)}, Handled::no()};
        };
        const auto sendCrc1 = [this, now]()
        {
            const std::uint8_t result = static_cast<std::uint8_t>((_crc >> 8) & 0xff);
            _crc = 0xffff;
            _state = RECEVIE_WAIT_FOR_ADDRESS;
            _waitUntil = now + requestTimeout;
            _length = 0;
            return Tuple{State::send(), Token::empty(), Byte{result}, Handled::yes()};
        };
        const auto sendMiddle = [this, computeCrc](const std::uint8_t state, const std::uint8_t value)
        {
            _state = state;
            computeCrc(value);
            return Tuple{State::send(), Token::empty(), Byte{value}, Handled::yes()};
        };
        const auto sendFirst = [this, sendMiddle, address]()
        {
            _crc = 0xffff;
            return sendMiddle(SEND_FUNCTION, address);
        };
        const auto sendData = [send, sendMiddle]() { return sendMiddle(SEND_DATA, send.value()); };
        const auto receiveBase = [this, now, computeCrc, received](const std::uint8_t state, const Token token, const Handled handled)
        {
            _state = state;
            _waitUntil = now + dataTimeout;
            computeCrc(received.value());
            return Tuple{State::receive(), token, Byte{}, handled};
        };
        const auto receiveAddress = [this, receiveBase, received, address, error, send]()
        {
            _crc = 0xffff;
            if (received.value() == address)
                return send.type().isStart() ? receiveBase(RECEVIE_WAIT_FOR_ECHO, Token::start(), Handled::yes())
                                             : receiveBase(RECEVIE_WAIT_FOR_FUNCTION, Token::start(), Handled::no());
            if (received.value() == static_cast<std::uint8_t>(address & 0x80))
                return receiveBase(RECEVIE_WAIT_FOR_CODE, Token::exception(), Handled::no());
            return error(ERROR_RECEIVE_WRONG_ADDRESS);
        };
        const auto receiveFunction = [receiveBase, received]()
        { return receiveBase(RECEVIE_WAIT_FOR_LENGTH, Token::function(received.value()), Handled::no()); };
        const auto receiveLength = [this, receiveBase, received, error]()
        {
            if (received.value() >= 253) return error(ERROR_RECEIVE_LENGTH_NOT_VALID);
            _length = received.value();
            _index = 0;
            return receiveBase(RECEVIE_WAIT_FOR_DATA, Token::data(received.value()), Handled::no());
        };
        const auto receiveData = [this, receiveBase, received]()
        {
            _index++;
            return receiveBase(_index >= _length ? RECEVIE_WAIT_FOR_CRC0 : RECEVIE_WAIT_FOR_DATA, Token::data(received.value()), Handled::no());
        };
        const auto receiveCode = [error, receiveBase, received]()
        {
            if (received.value() <= 0 || received.value() > 4) return error(ERROR_RECEIVE_CODE_NOT_VALID);
            return receiveBase(RECEVIE_WAIT_FOR_CRC0, Token::data(received.value()), Handled::no());
        };
        const auto receiveCrc0 = [this, now, received, error]()
        {
            const std::uint8_t low = static_cast<std::uint8_t>(_crc);
            if (low != received.value()) return error(ERROR_RECEIVE_WRONG_CRC);
            _state = RECEVIE_WAIT_FOR_CRC1;
            _waitUntil = now + dataTimeout;
            return Tuple{State::receive(), Token::empty(), Byte{}, Handled::no()};
        };
        const auto receiveCrc1 = [this, now, received, error, send]()
        {
            const std::uint8_t high = static_cast<std::uint8_t>(_crc >> 8);
            if (high != received.value()) return error(ERROR_RECEIVE_WRONG_CRC);
            _state = WAIT_FOR_IDLE;
            _waitUntil = now + dataTimeout;
            return Tuple{State::receive(), Token::end(), Byte{}, send.type().isEnd() ? Handled::yes() : Handled::no()};
        };
        const auto receiveEcho = [receiveBase, received, error, send, receiveCrc0]()
        {
            if (send.type().isEnd()) return receiveCrc0();
            if (send.value() != received.value()) return error(ERROR_RECEIVE_WRONG_ECHO);
            return receiveBase(RECEVIE_WAIT_FOR_ECHO, send, Handled::yes());
        };
        const auto idle = [this, stay]()
        {
            _state = IDLE;
            _length = 0;
            _index = 0;
            _crc = 0xffff;
            _waitUntil = {};
            return stay(State::idle());
        };
        const auto handleError = [this, now, idle, stay](const State state) { return now > _waitUntil ? idle() : stay(state); };
        switch (_state)
        {
            case IDLE:
                return received                ? error(ERROR_RECEIVE_WITHOUT_REUQUEST)
                       : send.isEmpty()        ? stay(State::idle())
                       : send.type().isStart() ? sendFirst()
                                               : error(ERROR_SEND_INVALID);
            case SEND_FUNCTION:
                return received                   ? error(ERROR_RECEIVE_WITHOUT_REUQUEST)
                       : send.isEmpty()           ? stay(State::send())
                       : send.type().isFunction() ? sendData()
                                                  : error(ERROR_SEND_INVALID);
            case SEND_DATA:
                return received               ? error(ERROR_RECEIVE_WITHOUT_REUQUEST)
                       : send.isEmpty()       ? stay(State::send())
                       : send.type().isData() ? sendData()
                       : send.type().isEnd()  ? sendCrc0()
                                              : error(ERROR_SEND_INVALID);
            case SEND_CRC1:
                return received              ? error(ERROR_RECEIVE_WITHOUT_REUQUEST)
                       : send.isEmpty()      ? stay(State::send())
                       : send.type().isEnd() ? sendCrc1()
                                             : error(ERROR_SEND_INVALID);
            case RECEVIE_WAIT_FOR_ADDRESS:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_NO_RESPONSE) : received ? receiveAddress() : stay(State::receive());
            case RECEVIE_WAIT_FOR_ECHO:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveEcho() : stay(State::receive());
            case RECEVIE_WAIT_FOR_FUNCTION:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveFunction() : stay(State::receive());
            case RECEVIE_WAIT_FOR_LENGTH:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveLength() : stay(State::receive());
            case RECEVIE_WAIT_FOR_DATA:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveData() : stay(State::receive());
            case RECEVIE_WAIT_FOR_CODE:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveCode() : stay(State::receive());
            case RECEVIE_WAIT_FOR_CRC0:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveCrc0() : stay(State::receive());
            case RECEVIE_WAIT_FOR_CRC1:
                return now > _waitUntil ? error(ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE) : received ? receiveCrc1() : stay(State::receive());
            case WAIT_FOR_IDLE:
                return now > _waitUntil ? idle() : stay(State::receive());
            case ERROR_SEND_INVALID:
                return handleError(State::errorSendInvalid());
            case ERROR_RECEIVE_WITHOUT_REUQUEST:
                return handleError(State::errorReceiveWithoutReuquest());
            case ERROR_RECEIVE_LENGTH_NOT_VALID:
                return handleError(State::errorReceiveLengthNotValid());
            case ERROR_RECEIVE_CODE_NOT_VALID:
                return handleError(State::errorReceiveCodeNotValid());
            case ERROR_RECEIVE_WRONG_ADDRESS:
                return handleError(State::errorReceiveWrongAddress());
            case ERROR_RECEIVE_WRONG_CRC:
                return handleError(State::errorReceiveWrongCrc());
            case ERROR_RECEIVE_TIMEOUT_NO_RESPONSE:
                return handleError(State::errorReceiveTimeoutNoResponse());
            case ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE:
                return handleError(State::errorReceiveTimeoutPartialResponse());
            default:
                return idle();
        }
    }

  private:
    std::uint8_t _state;
    std::uint8_t _length;
    std::uint8_t _index;
    std::uint16_t _crc;
    std::chrono::microseconds _waitUntil;

    static constexpr std::uint8_t IDLE = 0;
    static constexpr std::uint8_t SEND_FUNCTION = IDLE + 1;
    static constexpr std::uint8_t SEND_DATA = SEND_FUNCTION + 1;
    static constexpr std::uint8_t SEND_CRC0 = SEND_DATA + 1;
    static constexpr std::uint8_t SEND_CRC1 = SEND_CRC0 + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_ADDRESS = SEND_CRC1 + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_ECHO = RECEVIE_WAIT_FOR_ADDRESS + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_FUNCTION = RECEVIE_WAIT_FOR_ECHO + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_LENGTH = RECEVIE_WAIT_FOR_FUNCTION + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_DATA = RECEVIE_WAIT_FOR_LENGTH + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_CODE = RECEVIE_WAIT_FOR_DATA + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_CRC0 = RECEVIE_WAIT_FOR_CODE + 1;
    static constexpr std::uint8_t RECEVIE_WAIT_FOR_CRC1 = RECEVIE_WAIT_FOR_CRC0 + 1;
    static constexpr std::uint8_t WAIT_FOR_IDLE = RECEVIE_WAIT_FOR_CRC1 + 1;
    static constexpr std::uint8_t ERROR_SEND_INVALID = WAIT_FOR_IDLE + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_WITHOUT_REUQUEST = ERROR_SEND_INVALID + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_LENGTH_NOT_VALID = ERROR_RECEIVE_WITHOUT_REUQUEST + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_CODE_NOT_VALID = ERROR_RECEIVE_LENGTH_NOT_VALID + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_WRONG_ADDRESS = ERROR_RECEIVE_CODE_NOT_VALID + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_WRONG_ECHO = ERROR_RECEIVE_WRONG_ADDRESS + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_WRONG_CRC = ERROR_RECEIVE_WRONG_ECHO + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_TIMEOUT_NO_RESPONSE = ERROR_RECEIVE_WRONG_CRC + 1;
    static constexpr std::uint8_t ERROR_RECEIVE_TIMEOUT_PARTIAL_RESPONSE = ERROR_RECEIVE_TIMEOUT_NO_RESPONSE + 1;

    static constexpr std::chrono::microseconds requestTimeout = std::chrono::milliseconds{500};
    static constexpr std::chrono::microseconds dataTimeout = std::chrono::microseconds{500};
    static constexpr std::chrono::microseconds stayInError = std::chrono::seconds{5};
    static constexpr std::chrono::microseconds waitForIdle = std::chrono::microseconds{1};
};
}  // namespace modbus
}  // namespace catta
