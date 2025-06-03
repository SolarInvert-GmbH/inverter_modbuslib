#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

// hardware
#include <catta/hardware/uart/Baudrate.hpp>
#include <catta/hardware/uart/DataBits.hpp>
#include <catta/hardware/uart/Parity.hpp>
#include <catta/hardware/uart/StopBits.hpp>

// modbus
#include <catta/modbus/MasterUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/response/Response.hpp>
#include <catta/tomodbus/modbus/si/request/Request.hpp>

// std
#include <chrono>
#include <optional>
#include <tuple>

namespace catta
{
namespace gui
{
/**
 * @tparam UART Uart class.
 * @brief Handles Uart config and connection.
 * @author CattaTech - Maik Urbannek
 */
template <class UART>
class Connection : public Fl_Group
{
  private:
    static constexpr int GAP = 10;
    static constexpr int W_INPUT = 100;
    static constexpr int W_BUTTON = 100;
    static constexpr int W_BOX = 300;
    static constexpr int H_LINE = 50;
    static constexpr int defaultWidth = W_INPUT + GAP + W_BUTTON + GAP + W_BUTTON + GAP + W_BOX + GAP + W_INPUT;
    static constexpr int defaultHeight = H_LINE * 2 + GAP;
    static constexpr int W_LABLE = (defaultWidth - 2 * GAP) / 3;

  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] defaultName The default device address of the uart.
     * @param[in] L The label name.
     * @param[in] clients Number of clients that send request in round robin.
     */
    Connection(int X, int Y, int W, int H, const char* defaultName, const char* L, const std::size_t clients)
        : Fl_Group(0, 0, defaultWidth + GAP * 2, defaultHeight + GAP * 2, L),
          _uart(UART::empty()),
          _current(clients + UART_NOT_CONNECTED),
          _clients(clients),
          _modbus{},
          _serializer{},
          _parser{},
          _receivedByte{},
          _sendByte{},
          _sendToken{},
          _receiveToken{},
          _request{},
          _stringManufacturer{},
          _stringModel{},
          _stringSerialNumber{},
          _timeout{},
          _waitForClear(false),
          _id(0x00),
          _error(ERROR::empty())
    {
        this->_input = new Fl_Input(GAP, GAP, W_INPUT, H_LINE);
        this->_input->value(defaultName);
        this->_button0 = new Fl_Button(GAP + W_INPUT + GAP, GAP, W_BUTTON, H_LINE, "Connect");
        this->_button0->callback(opencb, this);
        this->_button1 = new Fl_Button(GAP + W_INPUT + GAP + W_BUTTON + GAP, GAP, W_BUTTON, H_LINE, "Disconnect");
        this->_button1->callback(closecb, this);
        this->_button1->deactivate();
        this->_status = new Fl_Box(GAP + W_INPUT + GAP + W_BUTTON + GAP + W_BUTTON + GAP, GAP, W_BOX, H_LINE, getErrorString());
        this->_status->box(FL_DOWN_BOX);
        auto menu = [](const char* text)
        {
            return Fl_Menu_Item{.text = text,
                                .shortcut_ = 0,
                                .callback_ = nullptr,
                                .user_data_ = nullptr,
                                .flags = 0,
                                .labeltype_ = 0,
                                .labelfont_ = 0,
                                .labelsize_ = 0,
                                .labelcolor_ = 0};
        };
        static const Fl_Menu_Item id[] = {menu("auto"), menu("00"), menu("01"), menu("02"), menu("03"), menu("04"),
                                          menu("05"),   menu("06"), menu("07"), menu("08"), menu("09"), menu("0a"),
                                          menu("0b"),   menu("0c"), menu("0d"), menu("0e"), menu("0f"), menu(nullptr)};
        this->_choice = new Fl_Choice(GAP + W_INPUT + GAP + W_BUTTON + GAP + W_BUTTON + GAP + W_BOX + GAP, GAP, W_INPUT, H_LINE);
        this->_choice->menu(id);
        this->_choice->value(0);
        this->_manufacturer = new Fl_Box(GAP, GAP * 2 + H_LINE, W_LABLE, H_LINE, _stringManufacturer.data());
        this->_model = new Fl_Box(GAP * 2 + W_LABLE, GAP * 2 + H_LINE, W_LABLE, H_LINE, _stringModel.data());
        this->_serialNumber = new Fl_Box(GAP * 3 + W_LABLE * 2, GAP * 2 + H_LINE, W_LABLE, H_LINE, _stringSerialNumber.data());
        this->_manufacturer->box(FL_DOWN_BOX);
        this->_model->box(FL_DOWN_BOX);
        this->_serialNumber->box(FL_DOWN_BOX);
        this->box(FL_UP_BOX);
        this->end();
        this->resize(X, Y, W, H);
    }

    /**
     * @param[in] request The new request from the current client. If the request is empty, the next client will be choosen. If @b tookRequest was @b
     * false the request was not accepted and the request has to be send next time again.
     * @param[in] now The current time.
     * @retval somethingHappend Returns @b true if something happend and the main loop should not wait, otherwise @b false.
     * @retval tookRequest Returns @b true if the input request was accepted, otherwise @b false.
     * @retval resultResponse Returns the response for the in the past given response. Matches to the current client.
     * @retval current Returns the current client. The @b resultResponse is for the current client. Only the current client can send requests.
     */
    std::tuple<bool, bool, catta::modbus::si::response::Response, std::size_t> loop(const catta::modbus::si::request::Request request,
                                                                                    const std::chrono::microseconds now) noexcept
    {
        catta::modbus::si::response::Response resultResponse;

        const auto isInIdle = [this]() -> bool { return _request.isEmpty() && _timeout.count() == 0; };

        bool something = false;
        if (!_uart.isEmpty() && _error.isEmpty())
        {
            const auto resetConnectionTry = [this](const bool jump = false)
            {
                if (_choice->value() == 0 && jump)  // auto
                {
                    _id = static_cast<std::uint8_t>((_id + 1) % 16);
                }
                _request = REQUEST_MANUFACTURER;
            };

            const auto [somethingHappend, error, response] = handleMasterUart(now, _id);
            something = somethingHappend;
            if (_current < _clients)
            {
                if (error)
                {
                    _current = (_current + 1) % _clients;
                }
                else if (!response.isEmpty())
                {
                    resultResponse = response;
                    _current = (_current + 1) % _clients;
                }
            }
            else if (_current == _clients + UART_CONNECTED)
            {
                if (error)
                    resetConnectionTry(true);
                else if (!response.isEmpty())
                {
                    if (response.type().isString())
                    {
                        _stringManufacturer = response.stringValue().data();
                        _manufacturer->label(_stringManufacturer.data());
                        _request = REQUEST_MODEL;
                        _current = _clients + MANUFACTURE_RECEIVED;
                    }
                    else
                        resetConnectionTry(true);
                }
            }
            else if (_current == _clients + MANUFACTURE_RECEIVED)
            {
                if (error)
                    resetConnectionTry();
                else if (!response.isEmpty())
                {
                    if (response.type().isString())
                    {
                        _stringModel = response.stringValue().data();
                        _model->label(_stringModel.data());
                        _request = REQUEST_SERIAL_NUMBER;
                        _current = _clients + MODEL_RECEIVED;
                    }
                    else
                        resetConnectionTry();
                }
            }
            else if (_current == _clients + MODEL_RECEIVED)
            {
                if (error)
                    resetConnectionTry();
                else if (!response.isEmpty())
                {
                    if (response.type().isString())
                    {
                        _stringSerialNumber = response.stringValue().data();
                        _serialNumber->label(_stringSerialNumber.data());
                        _choice->value(_id + 1);
                        _current = 0;
                    }
                    else
                        resetConnectionTry();
                }
            }
        }
        else
        {
            if (_current != _clients + UART_NOT_CONNECTED)
            {
                _timeout = now + TIMEOUT;
                _waitForClear = true;
                _stringManufacturer = {};
                _stringModel = {};
                _stringSerialNumber = {};
                _manufacturer->label(_stringManufacturer.data());
                _model->label(_stringModel.data());
                _serialNumber->label(_stringSerialNumber.data());
                clearModbusHandling();
            }
        }

        bool tookRequest = false;
        if (isInIdle() && _current < _clients)
        {
            if (request.isEmpty())
                _current = (_current + 1) % _clients;
            else
            {
                tookRequest = true;
                _request = request;
            }
        }
        const std::size_t current = _current < _clients ? _current : _clients;
        return std::tuple<bool, bool, catta::modbus::si::response::Response, std::size_t>(something, tookRequest, resultResponse, current);
    }
    /**
     * Destructor.
     */
    ~Connection()
    {
        if (_input) delete _input;
        if (_button0) delete _button0;
        if (_button1) delete _button1;
        if (_status) delete _status;
        if (_choice) delete _choice;
        if (_manufacturer) delete _manufacturer;
        if (_model) delete _model;
        if (_serialNumber) delete _serialNumber;
    }

  private:
    UART _uart;

    std::size_t _current;
    std::size_t _clients;

    catta::modbus::MasterUart _modbus;

    catta::tomodbus::Serializer<catta::modbus::si::request::Request> _serializer;
    catta::frommodbus::Parser<catta::modbus::si::response::Response> _parser;

    std::optional<std::uint8_t> _receivedByte;
    std::optional<std::uint8_t> _sendByte;
    catta::modbus::Token _sendToken;
    catta::modbus::Token _receiveToken;

    catta::modbus::si::request::Request _request;

    catta::modbus::sunspec::String::Raw _stringManufacturer;
    catta::modbus::sunspec::String::Raw _stringModel;
    catta::modbus::sunspec::String::Raw _stringSerialNumber;

    std::chrono::microseconds _timeout;
    bool _waitForClear;
    std::uint8_t _id;

    Fl_Input* _input;
    Fl_Button* _button0;
    Fl_Button* _button1;
    Fl_Box* _status;
    Fl_Choice* _choice;
    Fl_Box* _manufacturer;
    Fl_Box* _model;
    Fl_Box* _serialNumber;
    using ERROR = decltype(UART::empty().error());
    ERROR _error;

    static constexpr std::chrono::microseconds TIMEOUT = std::chrono::milliseconds{500};
    static constexpr std::size_t UART_NOT_CONNECTED = 1;
    static constexpr std::size_t UART_CONNECTED = UART_NOT_CONNECTED + 1;
    static constexpr std::size_t MANUFACTURE_RECEIVED = UART_CONNECTED + 1;
    static constexpr std::size_t MODEL_RECEIVED = MANUFACTURE_RECEIVED + 1;
    static constexpr catta::modbus::si::ReadRegister REGISTER_MANUFACTURER =
        catta::modbus::si::ReadRegister::create(catta::modbus::si::RegisterAddress::commonManufacturer());
    static constexpr catta::modbus::si::ReadRegister REGISTER_MODEL =
        catta::modbus::si::ReadRegister::create(catta::modbus::si::RegisterAddress::commonModel());
    static constexpr catta::modbus::si::ReadRegister REGISTER_SERIAL_NUMBER =
        catta::modbus::si::ReadRegister::create(catta::modbus::si::RegisterAddress::commonSerialNumber());
    static constexpr catta::modbus::si::request::Request REQUEST_MANUFACTURER =
        catta::modbus::si::request::Request::readRegister(REGISTER_MANUFACTURER);
    static constexpr catta::modbus::si::request::Request REQUEST_MODEL = catta::modbus::si::request::Request::readRegister(REGISTER_MODEL);
    static constexpr catta::modbus::si::request::Request REQUEST_SERIAL_NUMBER =
        catta::modbus::si::request::Request::readRegister(REGISTER_SERIAL_NUMBER);
    const char* getErrorString()
    {
        return this->_uart.isEmpty() ? "NOT_CONNECTED" : this->_error.isEmpty() ? "CONNECTED" : ERROR::enumNames[this->_error].data();
    }
    static void opencb(Fl_Widget*, void* object)
    {
        Connection* connection = static_cast<Connection*>(object);
        static constexpr auto baudrate = catta::hardware::uart::Baudrate::baudrate57600();
        static constexpr auto parity = catta::hardware::uart::Parity::empty();
        static constexpr auto dataBits = catta::hardware::uart::DataBits::eight();
        static constexpr auto stopBits = catta::hardware::uart::StopBits::one();
        if (connection && connection->_input && connection->_status && connection->_button0)
        {
            const std::string_view device = connection->_input->value();
            connection->_uart = UART::create(device, baudrate, parity, dataBits, stopBits);
            connection->_error = connection->_uart.error();
            connection->_status->label(connection->getErrorString());
            if (!(connection->_uart.isEmpty()) && connection->_uart.error().isEmpty())
            {
                connection->_button0->deactivate();
                connection->_button1->activate();
                connection->_current = connection->_clients + UART_CONNECTED;
                connection->_id =
                    connection->_choice->value() == 0 ? std::uint8_t(0x00) : static_cast<std::uint8_t>(connection->_choice->value() - 1);
                connection->_choice->deactivate();
                connection->_request = REQUEST_MANUFACTURER;
            }
            else
                connection->_uart = UART::empty();
        }
    }
    static void closecb(Fl_Widget*, void* object)
    {
        Connection* connection = static_cast<Connection*>(object);
        if (connection && connection->_status && connection->_button0)
        {
            connection->_uart = UART::empty();
            connection->setDisconnect();
        }
    }
    void setDisconnect()
    {
        this->_button0->activate();
        this->_button1->deactivate();
        this->_error = _uart.error();
        this->_status->label(getErrorString());
        this->_choice->activate();
    }

    bool write(const char c) noexcept
    {
        if (this->_uart.isEmpty()) return false;
        const auto result = this->_uart.write(c);
        if (this->_button0 && (this->_uart.isEmpty() || !this->_uart.error().isEmpty())) this->setDisconnect();
        return result;
    }

    std::optional<char> read() noexcept
    {
        if (this->_uart.isEmpty()) return false;
        const auto result = this->_uart.read();
        if (this->_button0 && (this->_uart.isEmpty() || !this->_uart.error().isEmpty())) this->setDisconnect();
        return result;
    }

    void clearModbusHandling()
    {
        _serializer = {};
        _parser = {};
        _receivedByte = {};
        _sendByte = {};
        _sendToken = {};
        _receiveToken = {};
        _request = {};
        _modbus = {};
    }

    std::tuple<bool, bool, catta::modbus::si::response::Response> handleMasterUart(const std::chrono::microseconds now, const std::uint8_t id)
    {
        if (_waitForClear)
        {
            if (now > _timeout)
            {
                _timeout = std::chrono::microseconds::zero();
                _waitForClear = false;
            }
            else
                return std::tuple<bool, bool, catta::modbus::si::response::Response>{false, false, catta::modbus::si::response::Response::empty()};
        }
        bool somethingHappend = false;
        bool failed = false;
        catta::modbus::si::response::Response response = {};

        if (!_sendByte && _receiveToken.isEmpty())
        {
            const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = _modbus.work(now, _receivedByte, _sendToken, id);
            if (sendHandled) _sendToken = {};
            _receivedByte = {};
            _sendByte = sendByteLocal;

            _receiveToken = recevieTokenLocal;
            if (_sendByte || !_receiveToken.isEmpty()) somethingHappend = true;
        }
        if (_sendByte)
            if (this->write(static_cast<char>(_sendByte.value())))
            {
                _sendByte = {};
                somethingHappend = true;
            }
        if (!_receivedByte)
        {
            const auto result = this->read();
            if (result)
            {
                _receivedByte = result;
                somethingHappend = true;
            }
        }

        if (!_receiveToken.isEmpty())
        {
            const auto [error, handled] = _parser.read(_receiveToken);
            if (handled) _receiveToken = {};
            if (_parser.state().isDone())
            {
                response = _parser.data();
                _parser = {};
                _timeout = std::chrono::microseconds::zero();
            }
            if (_parser.state().isFailed())
            {
                clearModbusHandling();
                _timeout = now + TIMEOUT;
                _waitForClear = true;
                failed = true;
            }
            somethingHappend = true;
        }

        if (!_request.isEmpty() && _sendToken.isEmpty())
        {
            somethingHappend = true;
            [[maybe_unused]] const auto ignore = _serializer.read(_request);
            _sendToken = _serializer.data();
            if (_serializer.state().isDone())
            {
                _serializer = {};
                _timeout = now + TIMEOUT;
                _request = {};
            }
            if (_serializer.state().isFailed())
            {
                clearModbusHandling();
                failed = true;
            }
        }
        if (_timeout.count() != 0 && now > _timeout)
        {
            clearModbusHandling();
            failed = true;
            _timeout = std::chrono::microseconds::zero();
        }
        if (_uart.isEmpty() || !_uart.error().isEmpty())
        {
            failed = true;
        }
        return std::tuple<bool, bool, catta::modbus::si::response::Response>{somethingHappend, failed, response};
    }
};
}  // namespace gui
}  // namespace catta
