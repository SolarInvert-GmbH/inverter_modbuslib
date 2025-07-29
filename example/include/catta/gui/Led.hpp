#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>

// std
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Led with label.
 * @author CattaTech - Maik Urbannek
 */
class Led : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] label The value name.
     * Constructor.
     */
    Led(const int X, const int Y, const int W, const int H, const char* label) : Fl_Group(X, Y, W, H, nullptr)
    {
        const int gap = 5;
        const int aLed = 12;
        const int YL = Y + (H - aLed) / 2;
        const int wLabel = W - gap * 3 - aLed;
        _label = new Fl_Box(X, Y, wLabel, H);
        _label->label(label);
        _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _led = new Fl_Box(X + wLabel + gap, YL, aLed, aLed, nullptr);
        _led->box(FL_UP_BOX);
        this->end();
    }
    /**
     * Destructor.
     */
    ~Led()
    {
        if (_label) delete _label;
        if (_led) delete _led;
    }
    /**
     * @param[in] value The led value.
     */
    void set(const std::optional<bool> value) noexcept
    {
        _value = value;
        if (value)
        {
            _led->show();
            _led->color(value.value() ? FL_GREEN : FL_GRAY);
            _led->redraw();
        }
        else
            _led->hide();
    }
    /**
     * @return Returns csv representation.
     */
    std::string get() const noexcept
    {
        if (!this->visible()) return std::string();
        if (!_value) return std::string(";");
        if (!_value.value()) return std::string("0;");
        return std::string("1;");
    }

  private:
    Fl_Box* _label;
    Fl_Box* _led;
    std::optional<bool> _value;
};
}  // namespace gui
}  // namespace catta
