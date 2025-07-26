#pragma once

// gui
#include <catta/gui/WriteSingle.hpp>

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
        static constexpr std::array<const char*, SIZE> LABEL = {"Tracking Concept"};
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 65;
        static const int PER_LINE = 4;
        const int W_WRITE = (W - (PER_LINE + 1) * GAP) / PER_LINE;
        static const int W_SEND = 30;
        static constexpr auto sBioOffAddress = catta::modbus::si::RegisterAddress::siControlTrackingSelection();

        _write[S_BIO_OFF] = new WriteSingle(X + GAP + (int(S_BIO_OFF) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(S_BIO_OFF) / PER_LINE),
                                            W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 2.0, 1.0, sBioOffAddress, sBioOffAddress, _toRegisterSbioOff,
                                            _fromRegisterSbioOff, W_SEND, "", LABEL[S_BIO_OFF]);
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
     * @param[in] now The current time.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request, const std::chrono::microseconds now)
    {
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < _write.size(); i++)
        {
            std::size_t j = (_roundRobin + i) % _write.size();
            const catta::modbus::si::request::Request r = _write[j]->work(canTakeRequest && send.isEmpty(), response, request, now);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % _write.size();
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }
    /**
     * Better hide.
     */
    void stop()
    {
        for (std::size_t i = 0; i < _write.size(); i++) _write[i]->stop();
    }

  private:
    static constexpr std::size_t S_BIO_OFF = 0;
    static constexpr std::size_t SIZE = S_BIO_OFF + 1;
    std::array<WriteSingle*, SIZE> _write;
    std::size_t _roundRobin;

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
};
}  // namespace gui
}  // namespace catta
