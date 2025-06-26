#pragma once

// si
#include <catta/modbus/si/Type.hpp>

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

        const int w1 = (W - 10) / 1;
        // const int w2 = (W - 20) / 2;
        const int w3 = (W - 30) / 3;
        const int X0 = X + 5;
        const int X1 = X + 10 + w3;
        const int X2 = X + 15 + w3 * 2;
        static constexpr int H_LINE = 45;
        _acCurrent = new Value(X0, Y + H_LINE * 1, w3, H_LINE, "AcCurrent");
        _acVoltage = new Value(X1, Y + H_LINE * 1, w3, H_LINE, "AcVoltage");
        _acPower = new Value(X2, Y + H_LINE * 1, w3, H_LINE, "AcPower");
        _frequency = new Value(X0, Y + H_LINE * 2, w3, H_LINE, "Frequency");
        _powerFactor = new Value(X1, Y + H_LINE * 2, w3, H_LINE, "PowerFactor");
        _energyProduction = new Value(X2, Y + H_LINE * 2, w3, H_LINE, "EnergyProduction");
        _dcVoltage = new Value(X0, Y + H_LINE * 3, w3, H_LINE, "DcVoltage");
        _dcPower = new Value(X1, Y + H_LINE * 3, w3, H_LINE, "DcPower");
        _temperature = new Value(X2, Y + H_LINE * 3, w3, H_LINE, "Temperature");
        _operatingState0 = new Fl_Box(X0, Y + H_LINE * 4, w3, H_LINE, "Operating Mode");
        _operatingState1 = new Fl_Box(X1, Y + H_LINE * 4, w3, H_LINE, "State");
        _operatingState2 = new Fl_Box(X2, Y + H_LINE * 4, w3, H_LINE, nullptr);
        _operatingState3 = new Fl_Box(X0, Y + H_LINE * 5, w1, H_LINE, nullptr);
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
    /**
     * @param[in] type The type.
     * @param[in] state The state.
     */
    void setOperatingState(const catta::modbus::si::Type type, const std::uint16_t state)
    {
        const char* text = type < typeSize && state < stateSize ? TYPE_STATE_MATRIX[type][state] : nullptr;
        _operatingState3->label(text);
        if (state < stateSize)
        {
            _operatingState2Text[0] = state < 10 ? ' ' : '1';
            _operatingState2Text[1] = static_cast<char>('0' + state % 10);
            _operatingState2->label(_operatingState2Text.data());
        }
        else
            _operatingState2->label(nullptr);
    }

  private:
    Fl_Slider* _slider;
    Fl_Box* _interval;
    Value* _acCurrent;
    Value* _acVoltage;
    Value* _acPower;
    Value* _frequency;
    Value* _powerFactor;
    Value* _energyProduction;
    Value* _dcVoltage;
    Value* _dcPower;
    Value* _temperature;
    Fl_Box* _operatingState0;
    Fl_Box* _operatingState1;
    Fl_Box* _operatingState2;
    Fl_Box* _operatingState3;
    std::array<char, 3> _operatingState2Text;
    std::function<void(const std::chrono::microseconds interval)> _callback;
    std::array<char, 4> _invervalText;

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
    static constexpr std::size_t typeSize = 3;
    static constexpr std::size_t stateSize = 12;
    static constexpr const char* TYPE_STATE_MATRIX[typeSize][stateSize] = {
        {"SOLAR_0", "SOLAR_1", "SOLAR_2", "SOLAR_3", "SOLAR_4", "SOLAR_5", "SOLAR_6", "SOLAR_7", "SOLAR_8", "SOLAR_9", "SOLAR_10", "SOLAR_11"},
        {"WIND_0", "WIND_1", "WIND_2", "WIND_3", "WIND_4", "WIND_5", "WIND_6", "WIND_7", "WIND_8", "WIND_9", "WIND_10", "WIND_11"},
        {"BATTERY_0", "BATTERY_1", "BATTERY_2", "BATTERY_3", "BATTERY_4", "BATTERY_5", "BATTERY_6", "BATTERY_7", "BATTERY_8", "BATTERY_9",
         "BATTERY_10", "BATTERY_11"}};
};
}  // namespace gui
}  // namespace catta
