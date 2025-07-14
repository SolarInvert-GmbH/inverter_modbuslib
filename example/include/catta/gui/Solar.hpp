#pragma once

// gui
#include <catta/gui/Write.hpp>

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

// std
#include <array>

namespace catta
{
namespace gui
{
/**
 * @brief Solar shows solar config.
 * @author CattaTech - Maik Urbannek
 */
class Solar : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Solar(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr), _roundRobin(0)
    {
        static constexpr std::array<const char*, SIZE> LABEL = {"U_Sol_CV", "S_Bio_Off"};
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 45;
        static constexpr int W_LABEL = 100;
        static constexpr int W_WRITE = 100;
        static constexpr int W_SEND = 100;
        static const int X0 = X + 20;
        static const int X1 = X0 + W_LABEL + GAP;
        static const int X2 = X1 + W_WRITE + GAP * 4;
        static constexpr auto uSolCvReadAddress = catta::modbus::si::RegisterAddress::siControlBattaryCvModeRead();
        static constexpr auto uSolCvWriteAddress = catta::modbus::si::RegisterAddress::siControlBattaryCvModeWrite();
        static constexpr auto sBioOffAddress = catta::modbus::si::RegisterAddress::siControlTrackingSelection();

        for (std::size_t i = 0; i < SIZE; i++)
        {
            _label[i] = new Fl_Box(X0, Y + H_LINE * int(i + 1), W_LABEL, H_LINE, LABEL[i]);
            _label[i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _button[i] = new Fl_Button(X2, Y + H_LINE * int(i + 1), W_SEND, H_LINE, "Send");
            _button[i]->hide();
        }
        _write[U_SOL_CV] = new Write(X1, Y + H_LINE * 1, W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, uSolCvReadAddress, uSolCvWriteAddress,
                                     _toRegisterUsolCv, _fromRegisterUsolCv);
        _button[U_SOL_CV]->callback(uSolCvCb, this);

        _write[S_BIO_OFF] = new Write(X1, Y + H_LINE * 2, W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 2.0, 1.0, sBioOffAddress, sBioOffAddress,
                                      _toRegisterSbioOff, _fromRegisterSbioOff);
        _button[S_BIO_OFF]->callback(sBioOffCb, this);
        this->end();
    }
    /**
     * Destructor.
     */
    ~Solar() {}
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request)
    {
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < _write.size(); i++)
        {
            std::size_t j = (_roundRobin + i) % _write.size();
            const catta::modbus::si::request::Request r = _write[j]->work(canTakeRequest && send.isEmpty(), response, request);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % _write.size();
            }
            if (_write[j]->getState() == Write::STATE_IDLE && _write[j]->isChanged())
                _button[j]->show();
            else
                _button[j]->hide();
        }
        _roundRobin = newRoundRobin;
        return send;
    }

  private:
    static constexpr std::size_t U_SOL_CV = 0;
    static constexpr std::size_t S_BIO_OFF = U_SOL_CV + 1;
    static constexpr std::size_t SIZE = S_BIO_OFF + 1;
    std::array<Fl_Box*, SIZE> _label;
    std::array<Write*, SIZE> _write;
    std::array<Fl_Button*, SIZE> _button;
    std::size_t _roundRobin;
    class ToRegisterUsolCv
    {
      public:
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input * 100.0); }

      private:
    } _toRegisterUsolCv;
    class FromRegisterUsolCv
    {
      public:
        double operator()(const std::uint16_t input) { return static_cast<double>(input) / 100.0; }

      private:
    } _fromRegisterUsolCv;

    class ToRegisterSbioOff
    {
      public:
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input); }

      private:
    } _toRegisterSbioOff;
    class FromRegistersSbioOff
    {
      public:
        double operator()(const std::uint16_t input) { return static_cast<double>(input); }

      private:
    } _fromRegisterSbioOff;

    static void uSolCvCb(Fl_Widget*, void* object)
    {
        Solar* solar = static_cast<Solar*>(object);
        if (solar) solar->_write[U_SOL_CV]->write();
    }

    static void sBioOffCb(Fl_Widget*, void* object)
    {
        Solar* solar = static_cast<Solar*>(object);
        if (solar) solar->_write[S_BIO_OFF]->write();
    }
};
}  // namespace gui
}  // namespace catta
