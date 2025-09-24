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

// std
#include <array>

namespace catta
{
namespace gui
{
/**
 * @tparam N Number of curve Points.
 * @brief Curve handles showing and modifing curves.
 * @author CattaTech - Maik Urbannek
 */
template <std::size_t N>
class Curve : public Fl_Group
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
     * @param[in] label The name of the curve.
     * Constructor.
     */
    Curve(const int X, const int Y, const int W, const int H, const std::uint8_t spinnerType, const double minimum, const double maximum,
          const double step, const std::array<catta::modbus::si::RegisterAddress, N>& readAddress,
          const std::array<catta::modbus::si::RegisterAddress, N>& writeAddress, const std::function<std::uint16_t(const double)>& toRegister,
          const std::function<double(const std::uint16_t)>& fromRegister, const int W_SEND, const char* unit, const char* label)
        : Fl_Group(X, Y, W, H, nullptr), _sendCallback(*this), _roundRobin(0)
    {
        static_assert(N > 0);
        const int n = static_cast<int>(N);
        const int gap = 1;
        const int w = (W - n * gap - W_SEND) / n;
        int x = X + gap;
        const int H20 = (H * 3) / 10;
        const int H21 = (H * 7) / 10;
        const int Y20 = Y;
        const int Y21 = Y20 + H20;
        _label = new Fl_Box(X, Y20, w, H20, label);
        _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _label->labelsize(12);
        for (std::size_t i = 0; i < N; i++)
        {
            _writes[i] = new Write(x, Y21, w, H21, spinnerType, minimum, maximum, step, readAddress[i], writeAddress[i], toRegister, fromRegister);
            x += w + gap;
        }
        _sendButton = new SendButton<SendCallback>(x, Y21, W_SEND, H21, unit, _sendCallback);
        this->end();
        this->show();
    }

    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @param[in] now The current time.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request, const std::chrono::microseconds now)
    {
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < N; i++)
        {
            std::size_t j = (_roundRobin + i) % N;

            const catta::modbus::si::request::Request r = _writes[j]->work(canTakeRequest && send.isEmpty(), response, request, now);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % N;
            }
        }
        _roundRobin = newRoundRobin;
        const bool allIdleAndAtLeastOneDiffernt = [this]()
        {
            bool different = false;
            for (std::size_t i = 0; i < N; i++)
            {
                if (_writes[i]->getState() != Write::STATE_IDLE) return false;
                if (_writes[i]->isChanged()) different = true;
            }
            return different;
        }();
        _sendButton->setButtonMode(allIdleAndAtLeastOneDiffernt);

        return send;
    }

    /**
     * Destructor.
     */
    ~Curve()
    {
        for (std::size_t i = 0; i < N; i++) delete (_writes[i]);
        delete _sendButton;
    }
    /**
     * Better hide.
     */
    void stop()
    {
        for (std::size_t i = 0; i < _writes.size(); i++) _writes[i]->stop();
        _sendButton->setButtonMode(false);
    }
    /**
     * Begin request.
     */
    void start()
    {
        for (std::size_t i = 0; i < _writes.size(); i++) _writes[i]->start();
    }

  private:
    class SendCallback
    {
      public:
        SendCallback(Curve& curve) : _curve(curve) {}
        void operator()()
        {
            for (auto e : _curve._writes) e->write();
        }

      private:
        Curve& _curve;
    } _sendCallback;
    std::array<Write*, N> _writes;
    SendButton<SendCallback>* _sendButton;
    Fl_Box* _label;
    std::size_t _roundRobin;
};
}  // namespace gui
}  // namespace catta
