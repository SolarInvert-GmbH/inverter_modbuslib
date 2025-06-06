#pragma once

// gui
#include <catta/gui/Connection.hpp>

// modbus
#include <catta/modbus/ValueCache.hpp>

// fltk
#include <FL/Fl.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Rect.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Terminal.H>

namespace catta
{
namespace gui
{
/**
 * @brief MiniSicc monitors a inverter.
 * @author CattaTech - Maik Urbannek
 */
template <class UART, class TIME>
class MiniSicc : public Fl_Double_Window
{
  public:
    /**
     * @param[in] defaultUartName The default device address of the uart.
     * Constructor.
     */
    MiniSicc(const char* defaultUartName) : Fl_Double_Window(200, 200, WIDTH, HEIGHT, "miniSICC"), _run(true), _current(CLIENTS)
    {
        this->_connection = new Connection<UART>(10, 10, WIDTH - 20, HEIGHT - 20, defaultUartName, nullptr, CLIENTS);
        this->resizable(this->_connection);
        this->end();
        this->callback(close_cb);
        this->show();
    }
    /**
     * Runs mini SICC window. Blocks until the window is closed.
     */
    void run()
    {
        using namespace std::chrono_literals;
        while (this->_run)
        {
            const auto now = TIME::get();
            bool somethingHappend = false;

            {
                const auto [happend, tookRequest, receivedResponse, receivedRequest, current] = _connection->loop(_request, now);
                if (happend) somethingHappend = true;
                const Request cacheRequest = _cache.work(_request.isEmpty() && _current == CLIENT_CACHE, receivedResponse, receivedRequest, now);
                if (!cacheRequest.isEmpty())
                {
                    _request = cacheRequest;
                    somethingHappend = true;
                }
                if (_current < CLIENTS && current >= CLIENTS)
                    for (std::size_t i = 0; i < CACHE_SIZE; i++) _cache.setInvalid(i);
                _current = current;
            }
            Fl::wait(0);
            if (!somethingHappend) TIME::sleep(10us);
        }
    }

  private:
    static constexpr std::size_t CLIENTS = 1;
    static constexpr std::size_t CACHE_SIZE = 2;
    static constexpr std::size_t CLIENT_CACHE = 0;

    using Request = catta::modbus::si::request::Request;
    using Response = catta::modbus::si::response::Response;

    bool _run;

    Connection<UART>* _connection;
    catta::modbus::ValueCache<CACHE_SIZE> _cache;
    Request _request;
    std::size_t _current;

    static constexpr int WIDTH = 600;
    static constexpr int HEIGHT = 800;

    static void close_cb(Fl_Widget* widget, void*)
    {
        MiniSicc* self = dynamic_cast<MiniSicc*>(widget);
        if (self) self->_run = false;
    }
};
}  // namespace gui
}  // namespace catta
