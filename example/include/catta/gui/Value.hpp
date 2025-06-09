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
    Value(const int X, const int Y, const int W, const int H, const char* label) : Fl_Group(X, Y, W, H, nullptr), _text({})
    {
        _label = new Fl_Box(X, Y, (W * 2) / 3, H);
        _label->label(label);
        _value = new Fl_Box(X + (W * 2) / 3, Y, W / 3, H, nullptr);
        _value->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
        this->end();
    }
    /**
     * Destructor
     */
    ~Value()
    {
        if (_label) delete _label;
        if (_value) delete _value;
    }
    /**
     * @param[in] text The string to set for the value.
     */
    void set(const std::string& text) noexcept
    {
        _text = text;
        _value->label(_text.c_str());
    }

  private:
    std::string _text;
    Fl_Box* _label;
    Fl_Box* _value;
};
}  // namespace gui
}  // namespace catta
