#pragma once

// gui
#include <catta/gui/Connection.hpp>

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
    MiniSicc(const char* defaultUartName) : Fl_Double_Window(200, 200, WIDTH, HEIGHT, "miniSICC"), _run(true)
    {
        this->_connection = new Connection<UART>(10, 10, WIDTH - 20, HEIGHT - 20, defaultUartName, nullptr, 0);
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
                const catta::modbus::si::request::Request request;
                const auto [happend, tookRequest, response, current] = _connection->loop(request, now);
                if (happend) somethingHappend = true;
            }
            Fl::wait(0);
            if (!somethingHappend) TIME::sleep(10us);
        }
    }

  private:
    bool _run;

    Connection<UART>* _connection;

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
