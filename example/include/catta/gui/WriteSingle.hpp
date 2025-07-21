#pragma once

// gui
#include <catta/gui/SendButton.hpp>
#include <catta/gui/Write.hpp>

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>

namespace catta
{
namespace gui
{

/**
 * @brief Write handles showing and modifing single register.
 * @author CattaTech - Maik Urbannek
 */
class WriteSingle : public Fl_Group
{
  public:
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
     * @param[in] W_SEND The width of the send button.
     * @param[in] unit The unit.
     * @param[in] label The name of the write.
     */

    WriteSingle(const int X, const int Y, const int W, const int H, const std::uint8_t spinnerType, const double minimum, const double maximum,
                const double step, const catta::modbus::si::RegisterAddress readAddress, const catta::modbus::si::RegisterAddress writeAddress,
                const std::function<std::uint16_t(const double)>& toRegister, const std::function<double(const std::uint16_t)>& fromRegister,
                const int W_SEND, const char* unit, const char* label)
        : Fl_Group(X, Y, W, H, nullptr), _sendCallback(*this)
    {
        const int gap = 1;
        const int w = W - gap - W_SEND;
        const int H20 = (H * 3) / 10;
        const int H21 = (H * 7) / 10;
        const int Y20 = Y;
        const int Y21 = Y20 + H20;
        _label = new Fl_Box(X, Y20, w, H20, label);
        _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _label->labelsize(12);
        _write = new Write(X, Y21, w, H21, spinnerType, minimum, maximum, step, readAddress, writeAddress, toRegister, fromRegister);
        _sendButton = new SendButton<SendCallback>(X + gap + w, Y21, W_SEND, H21, unit, _sendCallback);
        this->end();
    }
    /**
     * Destructor.
     */
    ~WriteSingle()
    {
        if (_write) delete _write;
        if (_sendButton) delete _sendButton;
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
        const bool value = _write->getState() == Write::STATE_IDLE && _write->isChanged();
        _sendButton->setButtonMode(value);
        return _write->work(canTakeRequest, response, request);
    }

  private:
    class SendCallback
    {
      public:
        SendCallback(WriteSingle& writeSingle) : _writeSingle(writeSingle) {}
        void operator()() { _writeSingle._write->write(); }

      private:
        WriteSingle& _writeSingle;
    } _sendCallback;
    Write* _write;
    SendButton<SendCallback>* _sendButton;
    Fl_Box* _label;
};
}  // namespace gui
}  // namespace catta
