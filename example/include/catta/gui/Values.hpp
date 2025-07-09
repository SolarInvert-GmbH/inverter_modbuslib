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
#include <optional>
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
    Values(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr), _operatingState2Text{}, _invervalText{' ', '1', 's'}
    {
        _slider = new Fl_Slider(X + W / 5, Y + 15, (W * 3) / 5, 20, "Refreshinterval");
        _slider->align(FL_ALIGN_TOP);
        _slider->step(1.0 / 9.0);
        _slider->type(5);
        _slider->box(FL_FLAT_BOX);
        _slider->callback(slidercb, this);
        _interval = new Fl_Box(X + (W * 4) / 5, Y, W / 5, 50, _invervalText.data());

        const int gap = 5;
        const int w3 = (W - gap * 6) / 3;
        const int w4 = (W - gap * 8) / 4;
        const int X30 = X + gap;
        const int X31 = X30 + gap + w3;
        const int X32 = X31 + gap + w3;
        const int X40 = X + gap;
        const int X41 = X40 + gap + w4;
        const int X42 = X41 + gap + w4;
        const int X43 = X42 + gap + w4;

        static constexpr int H_LINE = 45;
        _acCurrent = new Value(X30, Y + H_LINE * 1, w3, H_LINE, "AcCurrent");
        _acVoltage = new Value(X31, Y + H_LINE * 1, w3, H_LINE, "AcVoltage");
        _acPower = new Value(X32, Y + H_LINE * 1, w3, H_LINE, "AcPower");
        _frequency = new Value(X30, Y + H_LINE * 2, w3, H_LINE, "Frequency");
        _energyProduction = new Value(X32, Y + H_LINE * 2, w3, H_LINE, "EnergyProduction");
        _dcVoltage = new Value(X30, Y + H_LINE * 3, w3, H_LINE, "DcVoltage");
        _dcPower = new Value(X31, Y + H_LINE * 3, w3, H_LINE, "DcPower");
        _temperature = new Value(X32, Y + H_LINE * 3, w3, H_LINE, "Temperature");
        _operatingState = new Value(X30, Y + H_LINE * 4, w3, H_LINE, "Operating Mode");
        _operatingStateText = new Fl_Box(X31, Y + H_LINE * 4, w3, H_LINE, nullptr);
        _operatingStateText->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
        _powerFactor = new Value(X30, Y + H_LINE * 5, w3, H_LINE, "PowerFactor");

        _relayOn = new Led(X43, Y + H_LINE * 5, w4, H_LINE, "RELAY ON");
        _uacOk = new Led(X40, Y + H_LINE * 6, w4, H_LINE, "UAC OK");
        _freqOk = new Led(X41, Y + H_LINE * 6, w4, H_LINE, "FREQ OK");
        _wrWorking = new Led(X42, Y + H_LINE * 6, w4, H_LINE, "WR WORKING");
        _pmaxActive = new Led(X43, Y + H_LINE * 6, w4, H_LINE, "PMAX Active");
        lock();
        this->end();
        this->show();
    }
    /**
     * Destructor.
     */
    ~Values() {}
    /**
     * @param[in] value The string for the ac current field.
     * @param[in] unit The unit for the ac current field.
     */
    void setAcCurrent(const std::string& value, const char* unit) noexcept { _acCurrent->set(value, unit); }
    /**
     * @param[in] value The string for the ac voltage field.
     * @param[in] unit The unit for the ac voltage field.
     */
    void setAcVoltage(const std::string& value, const char* unit) noexcept { _acVoltage->set(value, unit); }
    /**
     * @param[in] value The string for the ac power field.
     * @param[in] unit The unit for the ac power field.
     */
    void setAcPower(const std::string& value, const char* unit) noexcept { _acPower->set(value, unit); }
    /**
     * @param[in] value The string for the frequency field.
     * @param[in] unit The unit for the frequency field.
     */
    void setFrequency(const std::string& value, const char* unit) noexcept { _frequency->set(value, unit); }
    /**
     * @param[in] value The string for the power factor field.
     * @param[in] unit The unit for the power factor field.
     */
    void setPowerFactor(const std::string& value, const char* unit) noexcept { _powerFactor->set(value, unit); }
    /**
     * @param[in] value The string for the energy production field.
     * @param[in] unit The unit for the energy production field.
     */
    void setEnergyProduction(const std::string& value, const char* unit) noexcept { _energyProduction->set(value, unit); }
    /**
     * @param[in] value The string for the dc voltage field.
     * @param[in] unit The unit for the dc voltage field.
     */
    void setDcVoltage(const std::string& value, const char* unit) noexcept { _dcVoltage->set(value, unit); }
    /**
     * @param[in] value The string for the dc power field.
     * @param[in] unit The unit for the dc power field.
     */
    void setDcPower(const std::string& value, const char* unit) noexcept { _dcPower->set(value, unit); }
    /**
     * @param[in] value The string for the temperature field.
     * @param[in] unit The unit for the temperature field.
     */
    void setTemperature(const std::string& value, const char* unit) noexcept { _temperature->set(value, unit); }
    /**
     * @param[in] callback The callback that is executed when the slider is changed.
     */
    void setCallback(const std::function<void(const std::chrono::microseconds)> callback) { _callback = callback; }
    /**
     * @param[in] type The type.
     * @param[in] state The state.
     */
    void setOperatingState(const std::uint16_t state)
    {
        const char* text = state < stateSize ? TYPE_STATE_MATRIX[state] : nullptr;
        _operatingStateText->label(text);
        if (state < stateSize)
        {
            _operatingState2Text[0] = state < 10 ? ' ' : '1';
            _operatingState2Text[1] = static_cast<char>('0' + state % 10);
            _operatingState->set(_operatingState2Text.data(), nullptr);
        }
        else
            _operatingState->set("", nullptr);
    }
    /**
     * @param[in] relayOn The relayOn.
     */
    void setLed1(const std::optional<bool> relayOn) { _relayOn->set(relayOn); }
    /**
     * @param[in] uacOk The uacOk.
     * @param[in] freqOk The freqOk.
     * @param[in] wrWorking The wrWorking.
     * @param[in] pmaxActive The pmaxActive.
     */
    void setLed3(const std::optional<bool> uacOk, const std::optional<bool> freqOk, const std::optional<bool> wrWorking,
                 const std::optional<bool> pmaxActive)
    {
        _uacOk->set(uacOk);
        _freqOk->set(freqOk);
        _wrWorking->set(wrWorking);
        _pmaxActive->set(pmaxActive);
    }
    /**
     * Show locked stuff.
     */
    void lock()
    {
        _powerFactor->hide();
        _relayOn->hide();
        _uacOk->hide();
        _freqOk->hide();
        _wrWorking->hide();
        _pmaxActive->hide();
    }
    /**
     * Hide locked stuff.
     */
    void unlock()
    {
        _powerFactor->show();
        _relayOn->show();
        _uacOk->show();
        _freqOk->show();
        _wrWorking->show();
        _pmaxActive->show();
    }
    /**
     * Triggers the slider callback.
     */
    void triggerSliderCallback() { slidercb(nullptr, this); }

  private:
    class Led : public Fl_Group
    {
      public:
        Led(const int X, const int Y, const int W, const int H, const char* label) : Fl_Group(X, Y, W, H, nullptr)
        {
            const int gap = 5;
            const int aLed = 12;
            const int YL = Y + (H - aLed) / 2;
            const int wLabel = W - gap * 3 - aLed;
            _label = new Fl_Box(X, Y, wLabel, H);
            _label->label(label);
            _label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _led = new Fl_Box(X + wLabel + gap, YL, aLed, aLed, nullptr);
            _led->box(FL_UP_BOX);
            this->end();
        }
        ~Led()
        {
            if (_label) delete _label;
            if (_led) delete _led;
        }
        void set(const std::optional<bool> value) noexcept
        {
            _value = value;
            if (value)
            {
                _led->show();
                _led->color(value.value() ? FL_GREEN : FL_GRAY);
                _led->redraw();
            }
            else
                _led->hide();
        }

      private:
        Fl_Box* _label;
        Fl_Box* _led;
        std::optional<bool> _value;
    };
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
    Value* _operatingState;
    Fl_Box* _operatingStateText;
    Led* _relayOn;
    Led* _uacOk;
    Led* _freqOk;
    Led* _wrWorking;
    Led* _pmaxActive;
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
    static constexpr std::size_t stateSize = 12;
    static constexpr const char* TYPE_STATE_MATRIX[stateSize] = {"Starting up",
                                                                 "Going to Umin",
                                                                 "Trap State One",
                                                                 "MPP",
                                                                 "Sweep",
                                                                 "Constant Voltage",
                                                                 "Low Sun (Constant Voltage)",
                                                                 "WIND Characteristic curve",
                                                                 "Trap State Two",
                                                                 "BAT Mode",
                                                                 "BAT Safety Mode",
                                                                 "FRT"};
};
}  // namespace gui
}  // namespace catta
