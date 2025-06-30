#pragma once

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Spinner.H>

// std
#include <cstdint>
#include <functional>

namespace catta
{
namespace gui
{

static constexpr Fl_Color rgb(uchar r, uchar g, uchar b)
{
    if (!r && !g && !b)
        return FL_BLACK;
    else
        return static_cast<Fl_Color>(((((r << 8) | g) << 8) | b) << 8);
}

/**
 * @brief Write handles showing and modifing single register.
 * @author CattaTech - Maik Urbannek
 */
class Write
{
  public:
    /**
     * Reading state.
     */
    static constexpr std::uint8_t STATE_READING = 0;
    /**
     * Idle state.
     */
    static constexpr std::uint8_t STATE_IDLE = STATE_READING + 1;
    /**
     * Sending state.
     */
    static constexpr std::uint8_t STATE_WRITE = STATE_IDLE + 1;
    /**
     * Empty state.
     */
    static constexpr std::uint8_t STATE_EMPTY = STATE_WRITE + 1;
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] spinnerType Use FL_INT_INPUT or FL_FLOAT_INPUT.
     * @param[in] minimum The minimum value.
     * @param[in] maximum The maximum value.
     * @param[in] step The step to increse the value via button.
     * @param[in] readAddress The address to read the value.
     * @param[in] writeAddress The address to write the value.
     * @param[in] toRegister The callback to compute the register value from the widget value.
     * @param[in] fromRegister The callback to compute the widget value from the register value.
     */

    Write(const int X, const int Y, const int W, const int H, const std::uint8_t spinnerType, const double minimum, const double maximum,
          const double step, const catta::modbus::si::RegisterAddress readAddress, const catta::modbus::si::RegisterAddress writeAddress,
          const std::function<std::uint16_t(const double)>& toRegister, const std::function<double(const std::uint16_t)>& fromRegister)
        : _toRegister(toRegister), _fromRegister(fromRegister), _readAddress(readAddress), _writeAddress(writeAddress)
    {
        const int gap = 5;
        _box = new Fl_Box(X, Y, W, H);
        _box->box(FL_RFLAT_BOX);
        _spinner = new Fl_Spinner(X + gap, Y + gap, W - gap * 2, H - gap * 2, nullptr);
        _spinner->type(spinnerType);
        _spinner->minimum(minimum);
        _spinner->maximum(maximum);
        _spinner->step(step);
        _spinner->callback(callback_spinner, this);
        stop();
    }
    /**
     * Triggers the write. Use only in @b STATE_IDLE.
     */
    void write()
    {
        const double given = _spinner->value();
        if (isChanged())
        {
            _state = STATE_WRITE;
            _value = given;
            setWriteRequest();
            setColor(COLOR_SENDING);
        }
    }
    /**
     * Better hide.
     */
    void stop()
    {
        _state = STATE_EMPTY;
        _box->hide();
        _spinner->hide();
    }
    /**
     * Destructor.
     */
    ~Write()
    {
        if (_spinner) delete _spinner;
    }

    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request)
    {
        catta::modbus::si::request::Request result;
        switch (_state)
        {
            case STATE_READING:
                if (!_sent.isEmpty() && request == _sent)
                {
                    if (!response.type().isValue16())
                        setReadRequest();
                    else
                    {
                        const double value = _fromRegister(response.value16Value());
                        _value = value;
                        _spinner->value(value);
                        setColor(COLOR_IDLE);
                        _box->show();
                        _spinner->show();
                        _state = STATE_IDLE;
                    }
                }

                break;
            case STATE_IDLE:
                break;
            case STATE_WRITE:
                if (!_sent.isEmpty() && request == _sent)
                {
                    if (response.type().isWriteRegister())
                    {
                        _state = STATE_READING;
                        setReadRequest();
                    }
                    else
                    {
                        setColor(COLOR_ERROR);
                        _state = STATE_READING;
                        setReadRequest();
                    }
                }
                break;

            default:
                if (canTakeRequest)
                {
                    _state = STATE_READING;
                    setReadRequest();
                }
                break;
        }

        if (canTakeRequest)
        {
            result = _request;
            _sent = _request;
            _request = {};
        }

        return result;
    }
    /**
     * @return Returns the current state. STATE_READING, STATE_IDLE, STATE_WRITE and STATE_EMPTY are possible.
     */
    std::uint8_t getState() const { return _state; }
    /**
     * @return Returns @b true if the value in the widget is different than the received value, otherwise @b false.
     */
    bool isChanged() const
    {
        const double given = _spinner->value();
        const double band = _spinner->step() / 2.0;
        return given - band > _value || given + band < _value;
    }

  private:
    std::function<std::uint16_t(const double)> _toRegister;
    std::function<double(const std::uint16_t)> _fromRegister;
    catta::modbus::si::RegisterAddress _readAddress;
    catta::modbus::si::RegisterAddress _writeAddress;
    std::uint8_t _state;
    Fl_Spinner* _spinner;
    Fl_Box* _box;
    catta::modbus::si::request::Request _request;
    catta::modbus::si::request::Request _sent;
    double _value;

    static void callback_spinner(Fl_Widget*, void* o)
    {
        Write* s = static_cast<Write*>(o);
        if (s)
        {
            if (s->_state == STATE_IDLE)
                s->setColor(s->isChanged() ? COLOR_CHANGED : COLOR_IDLE);
            else
                s->_spinner->value(s->_value);
        }
    }

    static constexpr Fl_Color COLOR_IDLE = rgb(0x00, 0xb3, 0x00);
    static constexpr Fl_Color COLOR_CHANGED = rgb(0x33, 0x77, 0xff);
    static constexpr Fl_Color COLOR_SENDING = rgb(0xff, 0x80, 0x00);
    static constexpr Fl_Color COLOR_ERROR = rgb(0xe6, 0x00, 0x26);

    void setReadRequest() { _request = catta::modbus::si::request::Request::readRegister(catta::modbus::si::ReadRegister::create(_readAddress)); }
    void setWriteRequest()
    {
        const auto value = catta::modbus::sunspec::ValueU16::create(_toRegister(_value));
        const auto writeRegister = catta::modbus::si::WriteRegister::create(_writeAddress, value);
        _request = catta::modbus::si::request::Request::writeRegister(writeRegister);
    }
    void setColor(const Fl_Color color)
    {
        _box->color(color);
        _box->redraw();
        _spinner->redraw();
    }
};
}  // namespace gui
}  // namespace catta
