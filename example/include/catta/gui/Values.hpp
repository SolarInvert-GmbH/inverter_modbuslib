#pragma once

// gui
#include <catta/gui/Value.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>

// std
#include <array>
#include <functional>
#include <string>

namespace catta
{
namespace gui
{
/**
 * @brief Values shows values.
 * @author CattaTech - Maik Urbannek
 */
class Values : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Values(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr), _invervalText{' ', '1', 's'}
    {
        _slider = new Fl_Slider(X + W / 5, Y + 15, (W * 3) / 5, 20, "Refreshinterval");
        _slider->align(FL_ALIGN_TOP);
        _slider->step(1.0 / 9.0);
        _slider->type(5);
        _slider->box(FL_FLAT_BOX);
        _slider->callback(slidercb, this);
        _interval = new Fl_Box(X + (W * 4) / 5, Y, W / 5, 50, _invervalText.data());

        const int w = (W - 20) / 2;
        const int X0 = X + 5;
        const int X1 = X + 10 + w;
        _acCurrent = new Value(X0, Y + 55 + H_LINE * 0, w, H_LINE, "AcCurrent");
        _acVoltage = new Value(X1, Y + 55 + H_LINE * 0, w, H_LINE, "AcVoltage");
        _acPower = new Value(X0, Y + 55 + H_LINE * 1, w, H_LINE, "AcPower");
        _frequency = new Value(X1, Y + 55 + H_LINE * 1, w, H_LINE, "Frequency");
        _acApparentPower = new Value(X0, Y + 55 + H_LINE * 2, w, H_LINE, "AcApparentPower");
        _acReactivePower = new Value(X1, Y + 55 + H_LINE * 2, w, H_LINE, "AcReactivePower");
        _powerFactor = new Value(X0, Y + 55 + H_LINE * 3, w, H_LINE, "PowerFactor");
        _energyProduction = new Value(X1, Y + 55 + H_LINE * 3, w, H_LINE, "EnergyProduction");
        _dcVoltage = new Value(X0, Y + 55 + H_LINE * 4, w, H_LINE, "DcVoltage");
        _dcPower = new Value(X1, Y + 55 + H_LINE * 4, w, H_LINE, "DcPower");
        _temperature = new Value(X0, Y + 55 + H_LINE * 5, w, H_LINE, "Temperature");
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Values() {}
    /**
     * @param[in] text The string for the ac current field.
     */
    void setAcCurrent(const std::string& text) noexcept { _acCurrent->set(text); }
    /**
     * @param[in] text The string for the ac voltage field.
     */
    void setAcVoltage(const std::string& text) noexcept { _acVoltage->set(text); }
    /**
     * @param[in] text The string for the ac power field.
     */
    void setAcPower(const std::string& text) noexcept { _acPower->set(text); }
    /**
     * @param[in] text The string for the frequency field.
     */
    void setFrequency(const std::string& text) noexcept { _frequency->set(text); }
    /**
     * @param[in] text The string for the ac apparent power field.
     */
    void setAcApparentPower(const std::string& text) noexcept { _acApparentPower->set(text); }
    /**
     * @param[in] text The string for the _ac reactive power field.
     */
    void setAcReactivePower(const std::string& text) noexcept { _acReactivePower->set(text); }
    /**
     * @param[in] text The string for the power factor field.
     */
    void setPowerFactor(const std::string& text) noexcept { _powerFactor->set(text); }
    /**
     * @param[in] text The string for the energy production field.
     */
    void setEnergyProduction(const std::string& text) noexcept { _energyProduction->set(text); }
    /**
     * @param[in] text The string for the dc voltage field.
     */
    void setDcVoltage(const std::string& text) noexcept { _dcVoltage->set(text); }
    /**
     * @param[in] text The string for the dc power field.
     */
    void setDcPower(const std::string& text) noexcept { _dcPower->set(text); }
    /**
     * @param[in] text The string for the temperature field.
     */
    void setTemperature(const std::string& text) noexcept { _temperature->set(text); }
    /**
     * @param[in] callback The callback that is executed when the slider is changed.
     */
    void setCallback(const std::function<void(const std::chrono::microseconds)> callback) { _callback = callback; }

  private:
    Fl_Slider* _slider;
    Fl_Box* _interval;
    Value* _acCurrent;
    Value* _acVoltage;
    Value* _acPower;
    Value* _frequency;
    Value* _acApparentPower;
    Value* _acReactivePower;
    Value* _powerFactor;
    Value* _energyProduction;
    Value* _dcVoltage;
    Value* _dcPower;
    Value* _temperature;
    std::function<void(const std::chrono::microseconds interval)> _callback;
    std::array<char, 4> _invervalText;
    static constexpr int H_LINE = 50;
    static constexpr int W_VALUE = 50;

    static void slidercb(Fl_Widget*, void* object)
    {
        Values* values = static_cast<Values*>(object);
        if (values)
        {
            const double d = values->_slider->value();
            const int i = static_cast<int>(d * 9.0 + 1.5);
            values->_invervalText[0] = i < 10 ? ' ' : static_cast<char>('0' + (i / 10) % 10);
            values->_invervalText[1] = static_cast<char>('0' + (i) % 10);
            values->_interval->label(values->_invervalText.data());
            const std::chrono::seconds s = std::chrono::seconds{i};
            if (values->_callback) values->_callback(s);
        }
    }
};
}  // namespace gui
}  // namespace catta
