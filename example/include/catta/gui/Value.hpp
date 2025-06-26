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
     * Constructor.
     */
    Value(const int X, const int Y, const int W, const int H, const char* label) : Fl_Group(X, Y, W, H, nullptr), _textValue({})
    {
        const int wLabel = (W * 3) / 5;
        const int wValue = (W * 2) / 5;
        const int wSmall = wValue / 10;
        _label = new Fl_Box(X, Y, wLabel, H);
        _label->label(label);
        _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        _value = new Fl_Box(X + wLabel, Y, wSmall * 7, H, nullptr);
        _value->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
        _unit = new Fl_Box(X + wLabel + wSmall * 7, Y, wSmall * 3, H, nullptr);
        _unit->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        this->end();
    }
    /**
     * Destructor
     */
    ~Value()
    {
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
        _textValue = value;
        _value->label(_textValue.c_str());
        _unit->label(unit);
    }

  private:
    std::string _textValue;
    Fl_Box* _label;
    Fl_Box* _value;
    Fl_Box* _unit;
};
}  // namespace gui
}  // namespace catta
