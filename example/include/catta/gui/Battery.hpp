#pragma once

// gui
#include <catta/gui/Curve.hpp>

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// fltk
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

// std
#include <array>
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Battery shows battery config.
 * @author CattaTech - Maik Urbannek
 */
class Battery : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Battery(const int X, const int Y, const int W, const int H)
        : Fl_Group(X, Y, W, H, nullptr), _toRegister(*this), _fromRegister(*this), _lastAllIdle(false)
    {
        using Address = catta::modbus::si::RegisterAddress;
        static constexpr std::array<Address, 4> address = {Address::siControlMppStepDac0(), Address::siControlMppStepDac1(),
                                                           Address::siControlMppStepDac2(), Address::siControlMppStepDac3()};
        _x = new Curve<4>(X + 0, Y + 35, W, 35, FL_INT_INPUT, 0.0, 256.0, 1.0, address, address, _toRegister, _fromRegister);
        _write = new Fl_Button(X + 5, Y + 100, W - 10, 35, "write");
        _write->hide();
        _write->callback(writecb, this);
        this->end();
    }
    /**
     * Destructor.
     */
    ~Battery() {}
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request)
    {
        const auto result = _x->work(canTakeRequest, response, request);
        const bool thisAllIdle = _x->allIdleAndAtLeastOneDiffernt();
        if (thisAllIdle != _lastAllIdle)
        {
            if (thisAllIdle)
                _write->show();
            else
                _write->hide();
            _lastAllIdle = thisAllIdle;
        }
        return result;
    }

  private:
    class ToRegister
    {
      public:
        ToRegister(Battery& battery) : _battery(battery) {}
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input); }

      private:
        Battery& _battery;
    } _toRegister;
    class FromRegister
    {
      public:
        FromRegister(Battery& battery) : _battery(battery) {}
        double operator()(const std::uint16_t input) { return static_cast<double>(input); }

      private:
        Battery& _battery;
    } _fromRegister;
    Curve<4>* _x;
    Fl_Button* _write;
    bool _lastAllIdle;
    static void writecb(Fl_Widget*, void* object)
    {
        Battery* battery = static_cast<Battery*>(object);
        if (battery) battery->_x->write();
    }
};
}  // namespace gui
}  // namespace catta
