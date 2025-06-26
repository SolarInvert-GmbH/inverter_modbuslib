#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

// std
#include <array>
#include <functional>

namespace catta
{
namespace gui
{
/**
 * @brief Handles unlocking and locking of extended functions.
 * @author CattaTech - Maik Urbannek
 */
class Password : public Fl_Group
{
  private:
    static constexpr int GAP = 10;
    static constexpr int H_LINE = 50;
    static constexpr int defaultWidth = 740;
    static constexpr int W_ELEMENT = (740 - 3 * GAP) / 4;

  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] L The label name.
     * @param[in] clientId The client id.
     * @param[in] onUnlock The unlock callback.
     * @param[in] onLock The lock callback.
     */
    Password(int X, int Y, int W, int H, const char* L, const std::uint16_t clientId, const std::function<void()>& onUnlock,
             const std::function<void()>& onLock)
        : Fl_Group(0, 0, defaultWidth + GAP * 2, H_LINE + GAP * 2, L),
          _clientId(clientId + 10000),
          _onUnlock{onUnlock},
          _onLock{onLock},
          _locked(true)
    {
        std::size_t index = 0;
        const auto addCharacter = [this, &index](const char c)
        {
            this->_text[index] = c;
            index++;
        };
        const auto addString = [addCharacter](const char* s)
        {
            for (const char* p = s; *p != '\0'; p++) addCharacter(*p);
        };
        const auto autoAddNumber = [addCharacter](const std::uint32_t number)
        {
            std::uint32_t f = 10000;
            for (std::uint32_t n = 0; n < 5; n++, f /= 10) addCharacter(static_cast<char>('0' + (number / f) % 10));
        };
        addString("ClientId: ");
        autoAddNumber(_clientId);
        this->_client = new Fl_Box(GAP, GAP, W_ELEMENT, H_LINE, _text.data());
        this->_unlocked = new Fl_Box(GAP * 2 + W_ELEMENT, GAP, W_ELEMENT * 2 + GAP, H_LINE, "unlocked");
        this->_unlocked->labelsize(24);
        this->_unlocked->labelfont(FL_BOLD);
        this->_unlocked->hide();
        this->_defaultColor = this->color2();
        this->_input = new Fl_Input(GAP * 3 + W_ELEMENT * 2, GAP, W_ELEMENT, H_LINE, "password");
        this->_button = new Fl_Button(GAP * 4 + W_ELEMENT * 3, GAP, W_ELEMENT, H_LINE, BUTTON_LOCK);
        this->_button->callback(buttoncb, this);
        this->box(FL_UP_BOX);
        this->end();
        this->resize(X, Y, W, H);
    }

    /**
     * Destructor.
     */
    ~Password()
    {
        if (_client) delete _client;
        if (_unlocked) delete _unlocked;
        if (_input) delete _input;
        if (_button) delete _button;
    }
    /**
     * @return Returns @b true if password is given, otherwiese @b false.
     */
    bool isLocked() const { return _locked; }

  private:
    std::uint32_t _clientId;
    std::function<void()> _onUnlock;
    std::function<void()> _onLock;
    std::array<char, 16> _text;
    bool _locked;
    Fl_Color _defaultColor;

    Fl_Box* _client;
    Fl_Box* _unlocked;
    Fl_Input* _input;
    Fl_Button* _button;

    constexpr static const char* BUTTON_LOCK = "unlock";
    constexpr static const char* BUTTON_UNLOCK = "lock";

    static void buttoncb(Fl_Widget*, void* object)
    {
        Password* password = static_cast<Password*>(object);
        if (password)
        {
            if (password->_locked)
            {
                const std::string clean = [password]()
                {
                    std::string o = std::string(password->_input->value());
                    std::string s;
                    for (const char c : o)
                        if (c != ' ' && c != '\t') s += c;
                    return s;
                }();
                if (std::to_string(password->blackMagic()) == clean)
                {
                    password->_locked = false;
                    if (password->_onUnlock) password->_onUnlock();
                    password->_button->label(BUTTON_UNLOCK);
                    password->_input->hide();
                    password->_input->value("");
                    password->color(fl_rgb_color(0xc0, 0x00, 0x00));
                    password->_unlocked->show();
                }
                else
                {
                    password->_input->value("Wrong password");
                }
            }
            else
            {
                password->_locked = true;
                if (password->_onLock) password->_onLock();
                password->_button->label(BUTTON_LOCK);
                password->_input->show();
                password->color(password->_defaultColor);
                password->_unlocked->hide();
            }
        }
    }
    constexpr std::uint32_t blackMagic() const { return _clientId * 2 + 1234; }
};
}  // namespace gui
}  // namespace catta
