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
#include <FL/Fl_Spinner.H>

// std
#include <array>
#include <cstdint>
#include <string>
#include <tuple>

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
     * Constructor.
     */
    Curve(const int X, const int Y, const int W, const int H, const std::uint8_t spinnerType, const double minimum, const double maximum,
          const double step, const std::array<catta::modbus::si::RegisterAddress, N>& readAddress,
          const std::array<catta::modbus::si::RegisterAddress, N>& writeAddress, const std::function<std::uint16_t(const double)>& toRegister,
          const std::function<double(const std::uint16_t)>& fromRegister)
        : Fl_Group(X, Y, W, H, nullptr), _roundRobin(0)
    {
        static_assert(N > 0);
        const int n = static_cast<int>(N);
        const int gap = 10;
        const int w = (W - (n + 1) * gap) / n;
        int x = X + gap;
        for (std::size_t i = 0; i < N; i++)
        {
            _writes[i] = new Write(x, Y, w, H, spinnerType, minimum, maximum, step, readAddress[i], writeAddress[i], toRegister, fromRegister);
            x += w + gap;
        }
        this->end();
        this->show();
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
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < N; i++)
        {
            std::size_t j = (_roundRobin + i) % N;

            const catta::modbus::si::request::Request r = _writes[j]->work(canTakeRequest && send.isEmpty(), response, request);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % N;
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }
    /**
     * @return Returns @b true when all curve points are ready for writing and at least one point is different from received values, otherwise @b
     * false.
     */
    bool allIdleAndAtLeastOneDiffernt() const
    {
        bool different = false;
        for (std::size_t i = 0; i < N; i++)
        {
            if (_writes[i]->getState() != Write::STATE_IDLE) return false;
            if (_writes[i]->isChanged()) different = true;
        }
        return different;
    }
    /**
     * Triggers the write. Use only when @see allIdleAndAtLeastOneDiffernt() is @b true.
     */
    void write()
    {
        for (auto e : _writes) e->write();
    }
    /**
     * Destructor.
     */
    ~Curve()
    {
        for (std::size_t i = 0; i < N; i++) delete (_writes[i]);
    }

  private:
    std::array<Write*, N> _writes;
    std::size_t _roundRobin;
};
}  // namespace gui
}  // namespace catta
