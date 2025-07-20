#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

// std
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief SendButton.
 * @author CattaTech - Maik Urbannek
 */
template <class CALLBACK>
class SendButton : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] unit The unit.
     * @param[in] callback The send callback.
     * Constructor.
     */
    SendButton(const int X, const int Y, const int W, const int H, const char* unit, const CALLBACK callback)
        : Fl_Group(X, Y, W, H, nullptr), _callback(callback), _old(false)
    {
        _unit = new Fl_Box(X, Y, W, H, unit);
        _button = new Fl_Button(X, Y, W, H, "@+5>");
        _button->callback(sendCb, this);
        _button->hide();
        this->end();
    }
    /**
     * Destructor
     */
    ~SendButton()
    {
        if (_unit) delete _unit;
        if (_button) delete _button;
    }
    /**
     * @param[in] value @b true show button, @b false show unit.
     */
    void setButtonMode(const bool value)
    {
        if (_old != value)
        {
            if (value)
            {
                _button->show();
                _unit->hide();
            }
            else
            {
                _button->hide();
                _unit->show();
            }
            _old = value;
        }
    }

  private:
    CALLBACK _callback;
    Fl_Box* _unit;
    Fl_Button* _button;
    bool _old;
    static void sendCb(Fl_Widget*, void* object)
    {
        SendButton* sendButton = static_cast<SendButton*>(object);
        if (sendButton != nullptr) sendButton->_callback();
    }
};
}  // namespace gui
}  // namespace catta
