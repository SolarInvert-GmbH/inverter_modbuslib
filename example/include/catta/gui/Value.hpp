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
 * @brief Value with label.
 * @author CattaTech - Maik Urbannek
 */
class Value : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] label The value name.
     * @param[in] W_UNIT The width of the unit.
     * Constructor.
     */
    Value(const int X, const int Y, const int W, const int H, const char* label, const int W_UNIT) : Fl_Group(X, Y, W, H, nullptr), _textValue({})
    {
        const int gap = 5;

        const int H20 = (H * 3) / 10;
        const int H21 = (H * 7) / 10;
        const int Y20 = Y;
        const int Y21 = Y20 + H20;

        _label = new Fl_Box(X, Y20, W, H20, label);
        _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _label->labelsize(12);
        _box = new Fl_Box(X, Y21, W - W_UNIT, H21);
        _box->box(FL_RFLAT_BOX);
        _box->color(fl_rgb_color(0x20, 0xff, 0x00));
        _box->hide();
        _value = new Fl_Box(X + gap, Y21 + gap, W - W_UNIT - 2 * gap, H21 - 2 * gap, nullptr);
        _value->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
        _value->box(FL_FLAT_BOX);
        _value->hide();
        _unit = new Fl_Box(X + W - W_UNIT, Y21, W_UNIT, H21, nullptr);
        _unit->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        this->end();
    }
    /**
     * Destructor
     */
    ~Value()
    {
        if (_box) delete _box;
        if (_label) delete _label;
        if (_value) delete _value;
        if (_unit) delete _unit;
    }
    /**
     * @param[in] value The string to set for the value.
     * @param[in] unit The string to set for the value.
     */
    void set(const std::string& value, const char* unit) noexcept
    {
        if (value.empty())
        {
            _box->hide();
            _value->hide();
        }
        else
        {
            _box->show();
            _value->show();
        }
        _textValue = value;
        _value->label(_textValue.c_str());
        _unit->label(unit);
    }
    /**
     * @return Returns value if visible, otherwise empty.
     */
    std::string get() const noexcept
    {
        const auto safe = [](const char* s) { return s == nullptr ? std::string() : std::string(s); };
        return this->visible() ? safe(_value->label()) + ';' + safe(_unit->label()) + ';' : std::string();
    }

  private:
    std::string _textValue;
    Fl_Box* _box;
    Fl_Box* _label;
    Fl_Box* _value;
    Fl_Box* _unit;
};
}  // namespace gui
}  // namespace catta
