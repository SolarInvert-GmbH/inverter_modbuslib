#pragma once

// gui
#include <catta/gui/Value.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>

// std
#include <array>
#include <functional>
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Values shows values.
 * @author CattaTech - Maik Urbannek
 */
class Values : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Values(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr), _invervalText{' ', '1', 's'}
    {
        _slider = new Fl_Slider(X + W / 5, Y + 15, (W * 3) / 5, 20, "Refreshinterval");
        _slider->align(FL_ALIGN_TOP);
        _slider->step(1.0 / 9.0);
        _slider->type(5);
        _slider->box(FL_FLAT_BOX);
        _slider->callback(slidercb, this);
        _interval = new Fl_Box(X + (W * 4) / 5, Y, W / 5, 50, _invervalText.data());

        const int w = (W - 20) / 2;
        _temperature = new Value(X + 5, Y + 55, w, H_LINE, "Temperature");
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Values() {}
    /**
     * @param[in] text The string for the temperature field.
     */
    void setTemperature(const std::string& text) noexcept { _temperature->set(text); }
    /**
     * @param[in] callback The callback that is executed when the slider is changed.
     */
    void setCallback(const std::function<void(const std::chrono::microseconds)> callback) { _callback = callback; }

  private:
    Fl_Slider* _slider;
    Fl_Box* _interval;
    Value* _temperature;
    std::function<void(const std::chrono::microseconds interval)> _callback;
    std::array<char, 4> _invervalText;
    static constexpr int H_LINE = 50;
    static constexpr int W_VALUE = 50;

    static void slidercb(Fl_Widget*, void* object)
    {
        Values* values = static_cast<Values*>(object);
        if (values)
        {
            const double d = values->_slider->value();
            const int i = static_cast<int>(d * 9.0 + 1.5);
            values->_invervalText[0] = i < 10 ? ' ' : static_cast<char>('0' + (i / 10) % 10);
            values->_invervalText[1] = static_cast<char>('0' + (i) % 10);
            values->_interval->label(values->_invervalText.data());
            const std::chrono::seconds s = std::chrono::seconds{i};
            if (values->_callback) values->_callback(s);
        }
    }
};
}  // namespace gui
}  // namespace catta
