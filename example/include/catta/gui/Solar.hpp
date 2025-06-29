#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>

// std
#include <array>
#include <string>

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
    Solar(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
    {
        this->end();
        this->hide();
    }
    /**
     * Destructor.
     */
    ~Solar() {}

  private:
};
}  // namespace gui
}  // namespace catta
