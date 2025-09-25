#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

// si
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

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
          _locked(true),
          _state(IDLE),
          _isConnected(false)
    {
        _text = {};
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
        this->_button->deactivate();
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
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param modbusId The modbus id.
     * @param isConnected Is modbus uart connected.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const std::uint8_t modbusId, const bool isConnected)
    {
        const auto jump = [this](const std::uint8_t state, const catta::modbus::si::request::Request request)
        {
            _state = state;
            return request;
        };
        if (isConnected != _isConnected)
        {
            if (isConnected)
                _button->activate();
            else
            {
                _button->deactivate();
                if (!_locked) executeLock(false);
            }
            _isConnected = isConnected;
        }
        if (canTakeRequest)
        {
            switch (_state)
            {
                case LOCK_ENABLE_PERMANT:
                    return jump(LOCK_FUNCTION_ACTIVATE, REQUEST_ENABLE_PERMANT);
                case LOCK_FUNCTION_ACTIVATE:
                    return jump(IDLE, REQUEST_FUNCTION_ACTIVATE(modbusId));
                case UNLOCK_DISABLE_PERMANT:
                    return jump(UNLOCK_FUNCTION_DEACTIVATE, REQUEST_DISABLE_PERMANT);
                case UNLOCK_FUNCTION_DEACTIVATE:
                    return jump(IDLE, REQUEST_FUNCTION_DEACTIVATE);
                default:
                    return catta::modbus::si::request::Request::empty();
            }
        }
        return catta::modbus::si::request::Request::empty();
    }
    /**
     * On reset, the password is locked on inverter side. So the gui has also to be locked.
     */
    void reset()
    {
        _button->deactivate();
        if (!_locked) executeLock(false);
        _isConnected = false;
    }

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

    std::uint8_t _state;
    bool _isConnected;

    constexpr static const char* BUTTON_LOCK = "unlock";
    constexpr static const char* BUTTON_UNLOCK = "lock";

    void executeLock(const bool sendRequests)
    {
        _locked = true;
        if (_onLock) _onLock();
        _button->label(BUTTON_LOCK);
        _input->show();
        color(_defaultColor);
        _unlocked->hide();
        _state = sendRequests ? UNLOCK_DISABLE_PERMANT : IDLE;
    }

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
                    password->_state = LOCK_ENABLE_PERMANT;
                }
                else
                {
                    password->_input->value("Wrong password");
                }
            }
            else
            {
                password->executeLock(true);
            }
        }
    }
    constexpr std::uint32_t blackMagic() const { return _clientId * 2 + 1234; }
    constexpr static std::uint8_t IDLE = 0;
    constexpr static std::uint8_t LOCK_ENABLE_PERMANT = IDLE + 1;
    constexpr static std::uint8_t LOCK_FUNCTION_ACTIVATE = LOCK_ENABLE_PERMANT + 1;
    constexpr static std::uint8_t UNLOCK_DISABLE_PERMANT = LOCK_FUNCTION_ACTIVATE + 1;
    constexpr static std::uint8_t UNLOCK_FUNCTION_DEACTIVATE = UNLOCK_DISABLE_PERMANT + 1;

    using Request = catta::modbus::si::request::Request;
    using RegisterAddress = catta::modbus::si::RegisterAddress;
    using Value = catta::modbus::sunspec::ValueU16;
    using WriteRegister = catta::modbus::si::WriteRegister;

    constexpr static RegisterAddress REGISTER_FUNCTION_ACTIVATE = RegisterAddress::siControlFunctionActivate();
    constexpr static RegisterAddress REGISTER_ENABLE_PERMANT = RegisterAddress::siControlEnableWritePermanent();
    constexpr static Value VALUE_ENABLE_PERMANT = Value::create(0xABCD);
    constexpr static Value VALUE_DISABLE_PERMANT = Value::create(0xFFFF);
    constexpr static Value VALUE_FUNCTION_ACTIVATE(const std::uint8_t id) { return Value::create(0x00AC * id); }
    constexpr static Value VALUE_FUNCTION_DEACTIVATE = Value::create(0xFFFF);

    constexpr static Request REQUEST_ENABLE_PERMANT = Request::writeRegister(WriteRegister::create(REGISTER_ENABLE_PERMANT, VALUE_ENABLE_PERMANT));
    constexpr static Request REQUEST_DISABLE_PERMANT = Request::writeRegister(WriteRegister::create(REGISTER_ENABLE_PERMANT, VALUE_DISABLE_PERMANT));
    constexpr static Request REQUEST_FUNCTION_ACTIVATE(const std::uint8_t id)
    {
        return Request::writeRegister(WriteRegister::create(REGISTER_FUNCTION_ACTIVATE, VALUE_FUNCTION_ACTIVATE(id)));
    }
    constexpr static Request REQUEST_FUNCTION_DEACTIVATE =
        Request::writeRegister(WriteRegister::create(REGISTER_FUNCTION_ACTIVATE, VALUE_FUNCTION_DEACTIVATE));
};
}  // namespace gui
}  // namespace catta
