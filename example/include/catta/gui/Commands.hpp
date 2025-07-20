#pragma once

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Spinner.H>

// std
#include <array>
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Commands shows commands.
 * @author CattaTech - Maik Urbannek
 */
class Commands : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Commands(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
    {
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 45;
        static constexpr int W_LABEL = 130;
        static constexpr int W_FLIP = 100;
        static constexpr int W_SPINNER = 100;
        static constexpr int W_SEND = 30;
        static const int X0 = X + 20;
        static const int X1 = X0 + W_LABEL + GAP;
        static const int X2 = X1 + W_FLIP + GAP;
        static const int X3 = X2 + W_SPINNER + GAP;
        _labelPwmControl = new Fl_Box(X0, Y + H_LINE * 1, W_LABEL, H_LINE, "PWM Control");
        _labelPwmControl->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _labelMode = new Fl_Box(X0, Y + H_LINE * 2, W_LABEL, H_LINE, "Mode");
        _labelMode->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _labelInverterControl = new Fl_Box(X0, Y + H_LINE * 3, W_LABEL, H_LINE, "Inverter Control");
        _labelInverterControl->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

        _flipPwmControl = new FlipButton(X1, Y + H_LINE * 1, W_FLIP, H_LINE);
        _flipMode = new FlipButton(X1, Y + H_LINE * 2, W_FLIP, H_LINE);
        _flipInverterControl = new FlipButton(X1, Y + H_LINE * 3, W_FLIP, H_LINE);

        _spinner = new Fl_Spinner(X2, Y + H_LINE * 2, W_SPINNER, H_LINE, nullptr);
        _spinner->type(FL_FLOAT_INPUT);
        _spinner->minimum(0.1);
        _spinner->maximum(6553.5);
        _spinner->step(0.1);
        _spinner->value(24.0);

        _sendPwmControl = new Fl_Button(X3, Y + H_LINE * 1, W_SEND, H_LINE, "@+5>");
        _sendPwmControl->callback(sendPwmControlCb, this);
        _sendMode = new Fl_Button(X3, Y + H_LINE * 2, W_SEND, H_LINE, "@+5>");
        _sendMode->callback(sendModeCb, this);
        _sendInverterControl = new Fl_Button(X3, Y + H_LINE * 3, W_SEND, H_LINE, "@+5>");
        _sendInverterControl->callback(sendInverterControlCb, this);

        this->end();
    }
    /**
     * Destructor.
     */
    ~Commands() {}
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request)
    {
        if (canTakeRequest && !_request.isEmpty())
        {
            const catta::modbus::si::request::Request result = _request;
            _request = {};
            _sendPwmControl->show();
            _sendMode->show();
            _sendInverterControl->show();
            return result;
        }
        (void)response;
        (void)request;
        return catta::modbus::si::request::Request::empty();
    }

  private:
    class FlipButton : public Fl_Group
    {
      public:
        FlipButton(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
        {
            const int w = W / 2;
            const int X0 = X;
            const int X1 = X0 + w;
            _on = new Fl_Button(X0, Y, w, H, "On");
            _on->type(102);
            _on->value(1);
            _on->compact(1);
            _off = new Fl_Button(X1, Y, w, H, "Off");
            _off->type(102);
            _off->compact(1);

            this->end();
        }
        bool value() { return _on->value(); }

      private:
        Fl_Button* _on;
        Fl_Button* _off;
    };
    Fl_Box* _labelPwmControl;
    Fl_Box* _labelMode;
    Fl_Box* _labelInverterControl;
    FlipButton* _flipPwmControl;
    FlipButton* _flipMode;
    FlipButton* _flipInverterControl;
    Fl_Spinner* _spinner;
    Fl_Button* _sendPwmControl;
    Fl_Button* _sendMode;
    Fl_Button* _sendInverterControl;
    catta::modbus::si::request::Request _request;

    static void sendPwmControlCb(Fl_Widget*, void* object)
    {
        Commands* commands = static_cast<Commands*>(object);
        if (commands)
        {
            const bool on = commands->_flipPwmControl->value();
            commands->_request = on ? catta::modbus::si::request::Request::forceIdle() : catta::modbus::si::request::Request::deactivateIdle();
            commands->_sendPwmControl->hide();
            commands->_sendMode->hide();
            commands->_sendInverterControl->hide();
        }
    }

    static void sendModeCb(Fl_Widget*, void* object)
    {
        Commands* commands = static_cast<Commands*>(object);
        if (commands)
        {
            const bool on = commands->_flipMode->value();
            const auto value = [commands]()
            {
                const catta::modbus::sunspec::ValueU16 uSet =
                    catta::modbus::sunspec::ValueU16::create(static_cast<std::uint16_t>(commands->_spinner->value() * 10.0));
                return catta::modbus::si::request::ConstantVoltage::create(uSet);
            };
            commands->_request =
                on ? catta::modbus::si::request::Request::startConstantVoltage(value()) : catta::modbus::si::request::Request::endConstantVoltage();
            commands->_sendPwmControl->hide();
            commands->_sendMode->hide();
            commands->_sendInverterControl->hide();
        }
    }

    static void sendInverterControlCb(Fl_Widget*, void* object)
    {
        Commands* commands = static_cast<Commands*>(object);
        if (commands)
        {
            const bool on = commands->_flipInverterControl->value();
            commands->_request =
                on ? catta::modbus::si::request::Request::switchOnGridRelay() : catta::modbus::si::request::Request::switchOffGridRelay();
            commands->_sendPwmControl->hide();
            commands->_sendMode->hide();
            commands->_sendInverterControl->hide();
        }
    }
};
}  // namespace gui
}  // namespace catta
