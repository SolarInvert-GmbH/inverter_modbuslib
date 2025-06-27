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
        const int gap = 10;
        const int w2 = W / 2 - gap;
        const int wLabel = (w2 * 4) / 9;
        const int wGap = (w2 * 1) / 9;
        const int wValue = (w2 * 4) / 9;
        const int h = 50;
        _reduction = new Element(X + gap + (gap + w2) * 0, Y + h * 1, wLabel, wGap, wValue, h, "Reduction");
        _modulePower = new Element(X + gap + (gap + w2) * 1, Y + h * 1, wLabel, wGap, wValue, h, "Module Power");
        _date = new Element(X + gap + (gap + w2) * 0, Y + h * 2, wLabel, wGap, wValue, h, "Production Date");
        _version = new Element(X + gap + (gap + w2) * 1, Y + h * 2, wLabel, wGap, wValue, h, "SW-Version");
        _bom = new Element(X + gap + (gap + w2) * 0, Y + h * 4, wLabel, wGap, wValue, h, "BOM");
        lock();
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Static()
    {
        if (_version) delete _version;
        if (_date) delete _date;
        if (_bom) delete _bom;
        if (_reduction) delete _reduction;
        if (_modulePower) delete _modulePower;
    }
    /**
     * @param[in] text The string for the version field.
     */
    void setVersion(const std::string& text) noexcept { _version->set(text); }
    /**
     * @param[in] text The string for the date field.
     */
    void setDate(const std::string& text) noexcept { _date->set(text); }
    /**
     * @param[in] text The string for the bom field.
     */
    void setBom(const std::string& text) noexcept { _bom->set(text); }
    /**
     * @param[in] text The string for the reduction field.
     */
    void setReduction(const std::string& text) noexcept { _reduction->set(text); }
    /**
     * @param[in] text The string for the module power field.
     */
    void setModulePower(const std::string& text) noexcept { _modulePower->set(text); }
    /**
     * Show locked stuff.
     */
    void lock() { _bom->hide(); }
    /**
     * Hide locked stuff.
     */
    void unlock() { _bom->show(); }

  private:
    class Element
    {
      public:
        Element(const int X, const int Y, const int W_LABEL, const int W_GAP, const int W_VALUE, const int H, const char* label) : _string{}
        {
            _label = new Fl_Box(X, Y, W_LABEL, H, label);
            _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _value = new Fl_Box(X + W_LABEL + W_GAP, Y, W_VALUE, H, nullptr);
            _value->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        }
        void show()
        {
            _label->show();
            _value->show();
        }
        void hide()
        {
            _label->hide();
            _value->hide();
        }
        void set(const std::string s)
        {
            _string = s;
            _value->label(_string.c_str());
        }
        ~Element()
        {
            if (_label) delete _label;
            if (_value) delete _value;
        }

      private:
        std::string _string;
        Fl_Box* _label;
        Fl_Box* _value;
    };

    Element* _version;
    Element* _date;
    Element* _bom;
    Element* _reduction;
    Element* _modulePower;
};
}  // namespace gui
}  // namespace catta
