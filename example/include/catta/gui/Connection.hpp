#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
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

// tofromstring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/tostring/Hexadecimal.hpp>

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
          _modbus{requestTimeout, dataTimeout, stayInError, waitForIdle},
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
        this->_autoSearch =
            new Fl_Check_Button(GAP + W_INPUT + GAP + W_BUTTON + GAP + W_BUTTON + GAP + W_BOX + GAP, GAP, W_INPUT / 2 + 10, H_LINE, "auto");
        this->_autoSearch->callback(autocb, this);
        this->_autoSearch->value(1);
        this->_modbusId = new Fl_Input(GAP + W_INPUT + GAP + W_BUTTON + GAP + W_BUTTON + GAP + W_BOX + GAP + W_INPUT / 2 + 2 * GAP, GAP,
                                       W_INPUT / 2 - 2 * GAP, H_LINE);
        this->_modbusId->value("00");
        this->_modbusId->deactivate();
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
     * @retval isInIdle Returns @b true if the connection is free to accept new message, otherwise @b false.
     * @retval resultResponse Returns the response for the in the past given request. Matches to the current client.
     * @retval resultRequest Returns request to the corresponding response. Matches to the current client.
     * @retval current Returns the current client. The @b resultResponse is for the current client. Only the current client can send requests.
     */
    std::tuple<bool, bool, bool, catta::modbus::si::response::Response, catta::modbus::si::request::Request, std::size_t> loop(
        const catta::modbus::si::request::Request request, const std::chrono::microseconds now) noexcept
    {
        catta::modbus::si::response::Response resultResponse;
        catta::modbus::si::request::Request resultRequest;

        const auto setLable = [](const catta::modbus::sunspec::String::Raw& value, catta::modbus::sunspec::String::Raw& raw, Fl_Box* box)
        {
            raw = value;
            box->label(raw.data());
        };
        const auto setNextClient = [this]() { _current = (_current + 1) % _clients; };

        bool something = false;
        if (!_uart.isEmpty() && _error.isEmpty())
        {
            const auto resetConnectionTry = [this](const bool jump = false)
            {
                if (_autoSearch->value() == 1 && jump)  // auto case
                {
                    _id++;
                    _modbusId->value(catta::tostring::toString(catta::Hexadecimal(_id)).c_str());
                }
                _request = REQUEST_MANUFACTURER;
                _modbus = {requestTimeout, dataTimeout, stayInError, waitForIdle};
            };

            const auto [somethingHappend, error, response] = handleMasterUart(now, _id);
            something = somethingHappend;
            static constexpr bool JUMP = true;
            static constexpr bool DONT_JUMP = false;
            const auto handleSearch = [error, &response, resetConnectionTry, setLable, this](const bool jump,
                                                                                             catta::modbus::sunspec::String::Raw& raw, Fl_Box* box,
                                                                                             const std::size_t currentOnSuccess, const auto onSuccess)
            {
                if (error)
                    resetConnectionTry(jump);
                else if (!response.isEmpty())
                {
                    if (response.type().isString())
                    {
                        setLable(response.stringValue().data(), raw, box);
                        _current = currentOnSuccess;
                        onSuccess();
                    }
                    else
                        resetConnectionTry(true);
                }
            };

            if (_current < _clients)
            {
                if (error)
                    setNextClient();
                else if (!response.isEmpty())
                {
                    resultResponse = response;
                    resultRequest = _requestBackup;
                    _requestBackup = {};
                    setNextClient();
                }
            }
            else if (_current == _clients + UART_CONNECTED)
                handleSearch(JUMP, _stringManufacturer, _manufacturer, _clients + MANUFACTURE_RECEIVED, [this]() { _request = REQUEST_MODEL; });
            else if (_current == _clients + MANUFACTURE_RECEIVED)
                handleSearch(DONT_JUMP, _stringModel, _model, _clients + MODEL_RECEIVED, [this]() { _request = REQUEST_SERIAL_NUMBER; });
            else if (_current == _clients + MODEL_RECEIVED)
                handleSearch(DONT_JUMP, _stringSerialNumber, _serialNumber, 0,
                             [this]()
                             {
                                 _autoSearch->value(0);
                                 _requestBackup = {};
                             });
        }
        else
        {
            if (_current != _clients + UART_NOT_CONNECTED)
            {
                _timeout = now + TIMEOUT;
                _waitForClear = true;
                setLable({}, _stringManufacturer, _manufacturer);
                setLable({}, _stringModel, _model);
                setLable({}, _stringSerialNumber, _serialNumber);
                clearModbusHandling();
            }
        }

        bool tookRequest = false;
        if (_requestBackup.isEmpty() && _current < _clients)
        {
            if (request.isEmpty())
                setNextClient();
            else
            {
                tookRequest = true;
                _request = request;
                _requestBackup = request;
            }
        }
        const std::size_t current = _current < _clients ? _current : _clients;
        return std::tuple<bool, bool, bool, catta::modbus::si::response::Response, catta::modbus::si::request::Request, std::size_t>(
            something, tookRequest, _requestBackup.isEmpty(), resultResponse, resultRequest, current);
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
        if (_modbusId) delete _modbusId;
        if (_autoSearch) delete _autoSearch;
        if (_manufacturer) delete _manufacturer;
        if (_model) delete _model;
        if (_serialNumber) delete _serialNumber;
    }

  private:
    UART _uart;

    std::size_t _current;
    std::size_t _clients;

    static constexpr std::chrono::microseconds requestTimeout = std::chrono::milliseconds{500};
    static constexpr std::chrono::microseconds dataTimeout = std::chrono::milliseconds{500};  // should b mush smaller
    static constexpr std::chrono::microseconds stayInError = std::chrono::seconds{5};
    static constexpr std::chrono::microseconds waitForIdle = std::chrono::microseconds{1};

    catta::modbus::MasterUart _modbus;

    catta::tomodbus::Serializer<catta::modbus::si::request::Request> _serializer;
    catta::frommodbus::Parser<catta::modbus::si::response::Response> _parser;

    std::optional<std::uint8_t> _receivedByte;
    std::optional<std::uint8_t> _sendByte;
    catta::modbus::Token _sendToken;
    catta::modbus::Token _receiveToken;

    catta::modbus::si::request::Request _request;
    catta::modbus::si::request::Request _requestBackup;

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
    Fl_Input* _modbusId;
    Fl_Check_Button* _autoSearch;
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
    using ReadRegister = catta::modbus::si::ReadRegister;
    using RegisterAddress = catta::modbus::si::RegisterAddress;
    using Request = catta::modbus::si::request::Request;
    static constexpr Request REQUEST_MANUFACTURER = Request::readRegister(ReadRegister::create(RegisterAddress::commonManufacturer()));
    static constexpr Request REQUEST_MODEL = Request::readRegister(ReadRegister::create(RegisterAddress::commonModel()));
    static constexpr Request REQUEST_SERIAL_NUMBER = Request::readRegister(ReadRegister::create(RegisterAddress::commonSerialNumber()));
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
                const auto getChoice = [connection]()
                { return std::uint8_t(catta::fromstring::fromString<catta::Hexadecimal<std::uint8_t>>(connection->_modbusId->value())); };
                connection->_button0->deactivate();
                connection->_button1->activate();
                connection->_current = connection->_clients + UART_CONNECTED;
                connection->_id = getChoice();
                connection->_modbusId->value(catta::tostring::toString(catta::Hexadecimal(connection->_id)).c_str());
                connection->_modbusId->deactivate();
                connection->_autoSearch->deactivate();
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
    static void autocb(Fl_Widget*, void* object)
    {
        Connection* connection = static_cast<Connection*>(object);
        if (connection)
        {
            if (connection->_autoSearch->value())
                connection->_modbusId->deactivate();
            else
                connection->_modbusId->activate();
        }
    }
    void setDisconnect()
    {
        this->_button0->activate();
        this->_button1->deactivate();
        this->_error = _uart.error();
        this->_status->label(getErrorString());
        this->_autoSearch->activate();
        if (this->_autoSearch->value() == 0) this->_modbusId->activate();
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
        _modbus = {requestTimeout, dataTimeout, stayInError, waitForIdle};
    }

    std::tuple<bool, bool, catta::modbus::si::response::Response> handleMasterUart(const std::chrono::microseconds now, const std::uint8_t id)
    {
        const auto setTimeout = [this, now]() { _timeout = now + TIMEOUT; };
        const auto clearTimeout = [this]() { _timeout = std::chrono::microseconds::zero(); };
        using Tuple = std::tuple<bool, bool, catta::modbus::si::response::Response>;
        static constexpr Tuple EMPTY_TUPLE = Tuple(false, false, catta::modbus::si::response::Response::empty());
        if (_waitForClear)
        {
            if (now > _timeout)
            {
                clearTimeout();
                _waitForClear = false;
            }
            else
                return EMPTY_TUPLE;
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
                clearTimeout();
            }
            if (_parser.state().isFailed())
            {
                clearModbusHandling();
                setTimeout();
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
                setTimeout();
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
            clearTimeout();
        }
        if (_uart.isEmpty() || !_uart.error().isEmpty())
        {
            failed = true;
        }
        return Tuple{somethingHappend, failed, response};
    }
};
}  // namespace gui
}  // namespace catta
