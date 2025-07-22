#pragma once

// gui
#include <catta/gui/Value.hpp>

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
 * @brief Static shows inmutable values.
 * @author CattaTech - Maik Urbannek
 */
class Static : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Static(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
    {
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 65;

        static const int PER_LINE = 4;
        const int W_WRITE = (W - (PER_LINE + 1) * GAP) / PER_LINE;

        static const int W_UNIT = 30;

        static constexpr std::array<const char*, SIZE> VALUE_LABEL =
            std::array<const char*, SIZE>{"SW-Version", "Production Date", "Reduction", "Module Power", "BOM"};
        for (std::size_t i = 0; i < SIZE; i++)
        {
            _value[i] = new Value(X + GAP + (int(i) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(i) / PER_LINE + 1), W_WRITE, H_LINE,
                                  VALUE_LABEL[i], W_UNIT);
        }
        lock();
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Static()
    {
        for (const auto e : _value)
            if (e) delete e;
    }
    /**
     * @param[in] text The string for the version field.
     */
    void setVersion(const std::string& text) noexcept { _value[SW_VERSION]->set(text, nullptr); }
    /**
     * @param[in] text The string for the date field.
     */
    void setDate(const std::string& text) noexcept { _value[DATE]->set(text, nullptr); }
    /**
     * @param[in] text The string for the bom field.
     */
    void setBom(const std::string& text) noexcept { _value[BOM]->set(text, nullptr); }
    /**
     * @param[in] text The string for the reduction field.
     */
    void setReduction(const std::string& text) noexcept { _value[REDUCTION]->set(text, "%"); }
    /**
     * @param[in] text The string for the module power field.
     */
    void setModulePower(const std::string& text) noexcept { _value[MODULE_POWER]->set(text, "W"); }
    /**
     * Show locked stuff.
     */
    void lock() { _value[BOM]->hide(); }
    /**
     * Hide locked stuff.
     */
    void unlock() { _value[BOM]->show(); }

  private:
    static constexpr std::size_t SW_VERSION = 0;
    static constexpr std::size_t DATE = SW_VERSION + 1;
    static constexpr std::size_t REDUCTION = DATE + 1;
    static constexpr std::size_t MODULE_POWER = REDUCTION + 1;
    static constexpr std::size_t BOM = MODULE_POWER + 1;
    static constexpr std::size_t SIZE = BOM + 1;

    std::array<catta::gui::Value*, SIZE> _value;
};
}  // namespace gui
}  // namespace catta
