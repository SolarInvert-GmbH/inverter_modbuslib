#pragma once

// gui
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>

// catta
#include <catta/EnumConcept.hpp>

// tofromstring
#include <catta/fromstring/modbus/sunspec/String.hpp>
#include <catta/fromstring/modbus/sunspec/ValueS16.hpp>
#include <catta/fromstring/modbus/sunspec/ValueU16.hpp>
#include <catta/fromstring/modbus/sunspec/ValueU32.hpp>
#include <catta/fromstring/modbus/sunspec/ValueU64.hpp>
#include <catta/fromstring/modbus/sunspec/ValueU8.hpp>
#include <catta/tostring/modbus/sunspec/String.hpp>
#include <catta/tostring/modbus/sunspec/ValueS16.hpp>
#include <catta/tostring/modbus/sunspec/ValueU16.hpp>
#include <catta/tostring/modbus/sunspec/ValueU32.hpp>
#include <catta/tostring/modbus/sunspec/ValueU64.hpp>
#include <catta/tostring/modbus/sunspec/ValueU8.hpp>

// std
#include <array>
#include <functional>

namespace catta
{
namespace gui
{
/**
 * @brief Widget the handled input.
 * @author CattaTech - Maik Urbannek
 */
class Input : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] initial The initial value.
     */
    template <class T>
    Input(const int X, const int Y, const int W, const int H, const T initial)
        : Input(X, Y, W, H, Access<T>::createName(initial), Access<T>::createMenu(initial), Access<T>::createIndex(initial))
    {
        this->_callback = [this]() -> bool { return this->value<T>().isEmpty(); };
    }

    /**
     * @return Return the value of the widget if valid, otherwise empty.
     */
    template <class T>
    T value() const noexcept
    {
        return Access<T>::value(*this);
    }

    /**
     * @param[in] t The value to set for input. Has to be not empty.
     */
    template <class T>
    void value(const T t) noexcept
    {
        return Access<T>::value(*this, t);
    }

  private:
    template <class T>
    class Access;

    template <class T>
    friend class Access;
    Input(const int X, const int Y, const int W, const int H, const std::string& string, const Fl_Menu_Item* m, const int c)
        : Fl_Group(X, Y, W, H), _box(X, Y, H, H, check), _input(X + H, Y, W - H, H, nullptr), _choice(X + H, Y, W - H, H, nullptr)
    {
        this->end();
        _box.box(FL_UP_BOX);
        _box.color(FL_DARK_GREEN);
        if (string.length())
        {
            this->_input.value(string.c_str());
            this->_input.callback(changedcb, this);
        }
        else
            this->_input.hide();
        if (m)
        {
            this->_choice.menu(m);
            this->_choice.value(c);
        }
        else
            this->_choice.hide();
    }
    static constexpr const char* check = "✓";
    static constexpr const char* cross = "✗";
    Fl_Box _box;
    Fl_Input _input;
    Fl_Choice _choice;
    std::function<bool()> _callback;
    static void changedcb(Fl_Widget*, void* object)
    {
        Input* input = static_cast<Input*>(object);
        if (input)
        {
            if (input->_callback())
            {
                input->_box.color(FL_RED);
                input->_box.label(cross);
            }
            else
            {
                input->_box.color(FL_DARK_GREEN);
                input->_box.label(check);
            }
            input->_box.redraw();
        }
    }
};

template <catta::EnumConcept ENUM>
class Input::Access<ENUM>
{
  public:
    static std::string createName(const ENUM) { return std::string(); }
    static const Fl_Menu_Item* createMenu(const ENUM)
    {
        static auto m = []()
        {
            auto menu = [](const char* text)
            {
                return Fl_Menu_Item{.text = text,
                                    .shortcut_ = 0,
                                    .callback_ = nullptr,
                                    .user_data_ = nullptr,
                                    .flags = 0,
                                    .labeltype_ = 0,
                                    .labelfont_ = 0,
                                    .labelsize_ = 0,
                                    .labelcolor_ = 0};
            };
            std::array<Fl_Menu_Item, ENUM::empty() + 1> a = {};
            for (std::uint8_t i = 0; i < ENUM::empty(); i++) a[i] = menu(ENUM::enumNames[i].data());
            a[ENUM::empty()] = menu(nullptr);
            return a;
        }();
        return m.data();
    }
    static int createIndex(const ENUM initial) { return initial; }
    static ENUM value(const Input& input) { return ENUM(static_cast<std::uint8_t>(input._choice.value())); }
    static void value(Input& input, const ENUM v) { input._choice.value(v); }
    Access() = delete;
};

template <class T>
requires requires(const T object)
{
    {
        T::empty()
        } -> std::same_as<T>;
    {
        object.isEmpty()
        } -> std::same_as<bool>;
    {
        object == object
        } -> std::same_as<bool>;
    {
        T::create(object.value())
        } -> std::same_as<T>;
}
class Input::Access<T>
{
  public:
    static std::string createName(const T initial) { return catta::tostring::toString(initial); }

    static const Fl_Menu_Item* createMenu(const T) { return nullptr; }
    static int createIndex(const T) { return 0; }
    static T value(const Input& input) { return catta::fromstring::fromString<T>(input._input.value()); }
    static void value(Input& input, const T v) { input._input.value(catta::tostring::toString(v).c_str()); }
    Access() = delete;
};

template <>
class Input::Access<catta::modbus::sunspec::ScaleFactor>
{
  public:
    static std::string createName(const catta::modbus::sunspec::ScaleFactor) { return std::string(); }

    static const Fl_Menu_Item* createMenu(const catta::modbus::sunspec::ScaleFactor)
    {
        auto menu = [](const char* text)
        {
            return Fl_Menu_Item{.text = text,
                                .shortcut_ = 0,
                                .callback_ = nullptr,
                                .user_data_ = nullptr,
                                .flags = 0,
                                .labeltype_ = 0,
                                .labelfont_ = 0,
                                .labelsize_ = 0,
                                .labelcolor_ = 0};
        };

        static const Fl_Menu_Item scaleFactorMenu[] = {
            menu("-10"), menu("-9"), menu("-8"), menu("-7"), menu("-6"), menu("-5"), menu("-4"), menu("-3"), menu("-2"), menu("-1"),  menu(" 0"),
            menu("+1"),  menu("+2"), menu("+3"), menu("+4"), menu("+5"), menu("+6"), menu("+7"), menu("+8"), menu("+9"), menu("+10"), menu(nullptr)};
        return scaleFactorMenu;
    }

    static int createIndex(const catta::modbus::sunspec::ScaleFactor initial) { return initial.factorExponent() + 10; }
    static catta::modbus::sunspec::ScaleFactor value(const Input& input)
    {
        return catta::modbus::sunspec::ScaleFactor::create(static_cast<std::int8_t>(input._choice.value() - 10));
    }
    static void value(Input& input, const catta::modbus::sunspec::ScaleFactor v) { input._choice.value(v.factorExponent() + 10); }
    Access() = delete;
};

template <>
class Input::Access<catta::modbus::sunspec::String>
{
  public:
    static std::string createName(const catta::modbus::sunspec::String initial) { return catta::tostring::toString(initial); }
    static const Fl_Menu_Item* createMenu(const catta::modbus::sunspec::String) { return nullptr; }
    static int createIndex(const catta::modbus::sunspec::String) { return 0; }
    static catta::modbus::sunspec::String value(const Input& input)
    {
        return catta::fromstring::fromString<catta::modbus::sunspec::String>(input._input.value());
    }
    static void value(Input& input, const catta::modbus::sunspec::String v) { input._input.value(catta::tostring::toString(v).c_str()); }
    Access() = delete;
};

}  // namespace gui
}  // namespace catta
