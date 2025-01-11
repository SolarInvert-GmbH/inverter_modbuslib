#pragma once

// fltk
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

namespace catta
{
namespace gui
{
/**
 * @brief DummyInverter simulates inverter on Modbus level.
 * @author CattaTech - Maik Urbannek
 */
class DummyInverter : public Fl_Double_Window
{
  public:
    /**
     * Constructor.
     */
    DummyInverter() : Fl_Double_Window(200, 200, 200, 200, "DummyInverter"), _run(true)
    {
        this->resizable(this);
        this->end();
        this->callback(close_cb);
        this->show();
    }
    /**
     * Runs dummy inverter simulation window. Blocks until the window is closed.
     */
    void run()
    {
        while (_run)
        {
            Fl::wait(0);
            // TODO limit Framerate
        }
    }

  private:
    bool _run;
    static void close_cb(Fl_Widget* widget, void*)
    {
        DummyInverter* self = dynamic_cast<DummyInverter*>(widget);
        if (self) self->_run = false;
    }
};
}  // namespace gui
}  // namespace catta
