#pragma once

// si
#include <catta/modbus/si/Type.hpp>

// gui
#include <catta/gui/CsvLogging.hpp>
#include <catta/gui/Led.hpp>
#include <catta/gui/Value.hpp>

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Native_File_Chooser.H>
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
    Values(const int X, const int Y, const int W, const int H)
        : Fl_Group(X, Y, W, H, nullptr),
          _operatingState2Text{},
          _invervalText{' ', '1', 's'},
          _acVoltages{std::tuple<std::string, const char*>{"", nullptr}, std::tuple<std::string, const char*>{"", nullptr},
                      std::tuple<std::string, const char*>{"", nullptr}}
    {
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 65;

        _send = new Fl_Button(X + GAP, Y + 9, W / 5 - 2 * GAP, 30, "Get values once");
        _send->callback(sendcb, this);
        _send->hide();

        _slider = new Fl_Slider(X + W / 5, Y + 15, (W * 3) / 5, 20, "Refreshinterval");
        _slider->align(FL_ALIGN_TOP);
        _slider->step(1.0 / 10.0);
        _slider->type(5);
        _slider->box(FL_FLAT_BOX);
        _slider->callback(slidercb, this);
        _interval = new Fl_Box(X + (W * 4) / 5, Y, W / 5, 50, _invervalText.data());

        static const int PER_LINE = 4;
        const int W_WRITE = (W - (PER_LINE + 1) * GAP) / PER_LINE;

        static const int W_UNIT = 30;

        for (std::size_t i = 0; i < VALUE_SIZE; i++)
        {
            _value[i] = new Value(X + GAP + (int(i) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(i) / PER_LINE + 1), W_WRITE, H_LINE,
                                  VALUE_LABEL[i], W_UNIT);
        }

        for (std::size_t i = 0; i < LED_SIZE; i++)
        {
            _led[i] = new Led(X + GAP + (int(i) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(i + VALUE_SIZE + PER_LINE - 1) / PER_LINE + 1),
                              W_WRITE, H_LINE, LED_LABEL[i]);
        }
        _saveCsv = new Fl_Button(X + GAP + (int(7) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(7 + VALUE_SIZE + PER_LINE - 1) / PER_LINE + 1),
                                 W_WRITE, 45, BUTTON_CSV_IDLE);
        _saveCsv->callback(savecb, this);
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
    void setAcCurrent(const std::string& value, const char* unit) noexcept { _value[AC_CURRENT]->set(value, unit); }
    /**
     * @param[in] value The string for the ac power field.
     * @param[in] unit The unit for the ac power field.
     */
    void setAcPower(const std::string& value, const char* unit) noexcept { _value[AC_POWER]->set(value, unit); }
    /**
     * @param[in] value The string for the frequency field.
     * @param[in] unit The unit for the frequency field.
     */
    void setFrequency(const std::string& value, const char* unit) noexcept { _value[FREQUENCY]->set(value, unit); }
    /**
     * @param[in] value The string for the power factor field.
     * @param[in] unit The unit for the power factor field.
     */
    void setPowerFactor(const std::string& value, const char* unit) noexcept { _value[POWER_FACTOR]->set(value, unit); }
    /**
     * @param[in] value The string for the energy production field.
     * @param[in] unit The unit for the energy production field.
     */
    void setEnergyProduction(const std::string& value, const char* unit) noexcept { _value[ENERGY_PRODUCTION]->set(value, unit); }
    /**
     * @param[in] value The string for the dc voltage field.
     * @param[in] unit The unit for the dc voltage field.
     */
    void setDcVoltage(const std::string& value, const char* unit) noexcept { _value[DC_VOLTAGE]->set(value, unit); }
    /**
     * @param[in] value The string for the ac voltage a field.
     * @param[in] unit The unit for the ac voltage a field.
     */
    void setAcVoltageA(const std::string& value, const char* unit) noexcept { setAcVoltage(0, value, unit); }
    /**
     * @param[in] value The string for the ac voltage b field.
     * @param[in] unit The unit for the ac voltage b field.
     */
    void setAcVoltageB(const std::string& value, const char* unit) noexcept { setAcVoltage(1, value, unit); }
    /**
     * @param[in] value The string for the ac voltage b field.
     * @param[in] unit The unit for the ac voltage b field.
     */
    void setAcVoltageC(const std::string& value, const char* unit) noexcept { setAcVoltage(2, value, unit); }
    /**
     * @param[in] value The string for the dc power field.
     * @param[in] unit The unit for the dc power field.
     */
    void setDcPower(const std::string& value, const char* unit) noexcept { _value[DC_POWER]->set(value, unit); }
    /**
     * @param[in] value The string for the temperature field.
     * @param[in] unit The unit for the temperature field.
     */
    void setTemperature(const std::string& value, const char* unit) noexcept { _value[TEMPERATURE]->set(value, unit); }
    /**
     * @param[in] callback The callback that is executed when the slider is changed.
     */
    void setCallbacks(const std::function<void(const std::chrono::microseconds)> sliderCallback, const std::function<void(void)> sendCallback)
    {
        _sliderCallback = sliderCallback;
        _sendCallback = sendCallback;
    }
    /**
     * @param[in] type The type.
     * @param[in] state The state.
     */
    void setOperatingState(const std::uint16_t state)
    {
        const std::string text = state < stateSize ? std::string(TYPE_STATE_MATRIX[state]) : std::string();
        _value[OPERATING_STATE_TEXT]->set(text, nullptr);
        if (state < stateSize)
        {
            _operatingState2Text[0] = state < 10 ? ' ' : '1';
            _operatingState2Text[1] = static_cast<char>('0' + state % 10);
            _value[OPERATING_STATE]->set(_operatingState2Text.data(), nullptr);
        }
        else
            _value[OPERATING_STATE]->set("", nullptr);
    }
    /**
     * @param[in] value The string for the pmax field.
     * @param[in] unit The unit for the pmax field.
     */
    void setPmax(const std::string& value, const char* unit) noexcept { _value[P_MAX]->set(value, unit); }
    /**
     * @param[in] value The string for the time field.
     */
    void setTime(const std::string& value) noexcept { _value[TIME]->set(value, nullptr); }
    /**
     * @param[in] value The string for the tnightoff field.
     * @param[in] unit The unit for the tnightoff field.
     */
    void setTnightoff(const std::string& value, const char* unit) noexcept { _value[TNIGHTOFF]->set(value, unit); }
    /**
     * @param[in] value The string for the startdelay field.
     * @param[in] unit The unit for the startdelay field.
     */
    void setStartdelay(const std::string& value, const char* unit) noexcept { _value[STARTDELAY]->set(value, unit); }
    /**
     * @param[in] value The string for the cosphi field.
     * @param[in] unit The unit for the cosphi field.
     */
    void setCosphi(const std::string& value, const char* unit) noexcept { _value[COSPHI]->set(value, unit); }
    /**
     * @param[in] value The string for the dac field.
     * @param[in] unit The unit for the dac field.
     */
    void setDac(const std::string& value, const char* unit) noexcept { _value[DAC]->set(value, unit); }
    /**
     * @param[in] relayOn The relayOn.
     */
    void setLed1(const std::optional<bool> relayOn) { _led[RELAY_ON]->set(relayOn); }
    /**
     * @param[in] uacOk The uacOk.
     * @param[in] freqOk The freqOk.
     * @param[in] wrWorking The wrWorking.
     * @param[in] pmaxActive The pmaxActive.
     */
    void setLed3(const std::optional<bool> uacOk, const std::optional<bool> freqOk, const std::optional<bool> wrWorking,
                 const std::optional<bool> pmaxActive)
    {
        _led[UAC_OK]->set(uacOk);
        _led[FREQ_OK]->set(freqOk);
        _led[WR_WORKING]->set(wrWorking);
        _led[PMAX_ACTIVE]->set(pmaxActive);
    }
    /**
     * Show locked stuff.
     */
    void lock()
    {
        _value[POWER_FACTOR]->hide();
        _value[COSPHI]->hide();
        _value[DAC]->hide();
        for (std::size_t i = 0; i < LED_SIZE; i++) _led[i]->hide();
    }
    /**
     * Hide locked stuff.
     */
    void unlock()
    {
        _value[POWER_FACTOR]->show();
        _value[COSPHI]->show();
        _value[DAC]->show();
        for (std::size_t i = 0; i < LED_SIZE; i++) _led[i]->show();
    }
    /**
     * Triggers the slider callback.
     */
    void triggerSliderCallback() { slidercb(nullptr, this); }
    /**
     * @param[in] now The current time.
     */
    void work(const std::chrono::microseconds now)
    {
        if (_lastCsv != std::chrono::microseconds::zero() && _lastCsv + _sliderValue < now)
        {
            const std::string line = [this]()
            {
                std::string s;
                for (std::size_t i = 0; i < VALUE_SIZE; i++) s += _value[i]->get();
                for (std::size_t i = 0; i < LED_SIZE; i++) s += _led[i]->get();
                return s;
            }();
            _csvLogging.line(line);
            _lastCsv = now;
        }
    }

  private:
    Fl_Slider* _slider;
    Fl_Box* _interval;
    Fl_Button* _send;

    static constexpr std::size_t AC_POWER = 0;
    static constexpr std::size_t AC_CURRENT = AC_POWER + 1;
    static constexpr std::size_t AC_VOLTAGE = AC_CURRENT + 1;
    static constexpr std::size_t FREQUENCY = AC_VOLTAGE + 1;
    static constexpr std::size_t P_MAX = FREQUENCY + 1;
    static constexpr std::size_t DC_POWER = P_MAX + 1;
    static constexpr std::size_t DC_VOLTAGE = DC_POWER + 1;
    static constexpr std::size_t ENERGY_PRODUCTION = DC_VOLTAGE + 1;
    static constexpr std::size_t TEMPERATURE = ENERGY_PRODUCTION + 1;
    static constexpr std::size_t OPERATING_STATE = TEMPERATURE + 1;
    static constexpr std::size_t OPERATING_STATE_TEXT = OPERATING_STATE + 1;
    static constexpr std::size_t TIME = OPERATING_STATE_TEXT + 1;
    static constexpr std::size_t TNIGHTOFF = TIME + 1;
    static constexpr std::size_t STARTDELAY = TNIGHTOFF + 1;
    static constexpr std::size_t POWER_FACTOR = STARTDELAY + 1;
    static constexpr std::size_t COSPHI = POWER_FACTOR + 1;
    static constexpr std::size_t DAC = COSPHI + 1;
    static constexpr std::size_t VALUE_SIZE = DAC + 1;

    std::array<Value*, VALUE_SIZE> _value;

    static constexpr std::size_t RELAY_ON = 0;
    static constexpr std::size_t UAC_OK = RELAY_ON + 1;
    static constexpr std::size_t FREQ_OK = UAC_OK + 1;
    static constexpr std::size_t WR_WORKING = FREQ_OK + 1;
    static constexpr std::size_t PMAX_ACTIVE = WR_WORKING + 1;
    static constexpr std::size_t LED_SIZE = PMAX_ACTIVE + 1;

    std::array<Led*, LED_SIZE> _led;
    Fl_Button* _saveCsv;
    std::array<char, 3> _operatingState2Text;
    std::function<void(const std::chrono::microseconds interval)> _sliderCallback;
    std::function<void()> _sendCallback;
    std::array<char, 4> _invervalText;
    std::chrono::microseconds _lastCsv;
    std::chrono::microseconds _sliderValue;
    catta::gui::CsvLogging _csvLogging;
    std::array<std::tuple<std::string, const char*>, 3> _acVoltages;

    static constexpr std::array<const char*, VALUE_SIZE> VALUE_LABEL = std::array<const char*, VALUE_SIZE>{
        "AC Power", "AC Current", "AC Voltage", "Frequency", "PMAX",       "DC Power (est.)", "DC Voltage", "Energy", "Temp",
        "Op.State", "Op.State",   "Time",       "Tnightoff", "Startdelay", "cosPHI - Target", "cosPHI",     "DAC"};

    static constexpr std::array<const char*, LED_SIZE> LED_LABEL =
        std::array<const char*, LED_SIZE>{"RELAY ON", "UAC OK", "FREQ OK", "WR WORKING", "PMAX Active"};

    static void slidercb(Fl_Widget*, void* object)
    {
        Values* values = static_cast<Values*>(object);
        if (values)
        {
            static constexpr std::array<char, 4> infinity = {static_cast<char>(0xe2), static_cast<char>(0x88), static_cast<char>(0x9e), '\0'};
            const double d = values->_slider->value();
            const int i = static_cast<int>(d * 10.0 + 1.5);
            std::chrono::microseconds s = std::chrono::microseconds::max();
            if (i > 10)
            {
                values->_invervalText = infinity;
                values->_send->show();
            }
            else
            {
                values->_invervalText[0] = i < 10 ? ' ' : static_cast<char>('0' + (i / 10) % 10);
                values->_invervalText[1] = static_cast<char>('0' + (i) % 10);
                values->_invervalText[2] = '\0';
                values->_send->hide();
                s = std::chrono::seconds{i};
            }
            values->_interval->label(values->_invervalText.data());
            values->_sliderValue = s;
            if (values->_sliderCallback) values->_sliderCallback(s);
        }
    }

    static void savecb(Fl_Widget*, void* object)
    {
        Values* values = static_cast<Values*>(object);
        if (!values) return;
        if (values->_lastCsv == std::chrono::microseconds::zero())
        {
            Fl_Native_File_Chooser chooser;
            chooser.title("Choose csv logging file");
            chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
            chooser.filter("CSV\t*.csv\n");
            chooser.options(Fl_Native_File_Chooser::SAVEAS_CONFIRM);
            if (chooser.show() == 0)  // blocking call/ no boackground communication
            {
                const std::string header = []()
                {
                    std::string s;
                    for (std::size_t i = 0; i < VALUE_SIZE; i++) s += std::string(VALUE_LABEL[i]) + ";;";
                    for (std::size_t i = 0; i < LED_SIZE; i++) s += std::string(LED_LABEL[i]) + ";";
                    return s;
                }();
                values->_csvLogging.start(std::string(chooser.filename()), header);
                values->_lastCsv = std::chrono::microseconds{1};
                values->_saveCsv->label(BUTTON_CSV_RUNNING);
            }
        }
        else
        {
            values->_lastCsv = std::chrono::microseconds{0};
            values->_saveCsv->label(BUTTON_CSV_IDLE);
        }
    }

    static void sendcb(Fl_Widget*, void* object)
    {
        Values* values = static_cast<Values*>(object);
        if (values && values->_sendCallback) values->_sendCallback();
    }

    static constexpr std::size_t stateSize = 12;
    static constexpr const char* TYPE_STATE_MATRIX[stateSize] = {"Starting up",    "Going to Umin",    "Trap State One",  "MPP Track",
                                                                 "Sweep",          "Constant Voltage", "Low Sun CV",      "WIND Track",
                                                                 "Trap State Two", "BAT Mode",         "BAT Safety Mode", "FRT"};
    static constexpr const char* BUTTON_CSV_IDLE = "Start csv Logging";
    static constexpr const char* BUTTON_CSV_RUNNING = "End csv Logging";
    void setAcVoltage(const std::size_t i, const std::string& value, const char* unit)
    {
        _acVoltages[i] = std::tuple<std::string, const char*>{value, unit};
        const std::size_t bestIndex = [this]() -> std::size_t
        {
            const auto isNoneZero = [this](const std::size_t i)
            {
                const std::string& s = std::get<0>(_acVoltages[i]);
                for (const char c : s)
                    if (c >= '1' && c <= '9') return true;
                return false;
            };
            const auto isNoneEmpty = [this](const std::size_t i)
            {
                const std::string& s = std::get<0>(_acVoltages[i]);
                return !s.empty();
            };
            for (std::size_t i = 0; i < _acVoltages.size(); i++)
                if (isNoneZero(i)) return i;
            for (std::size_t i = 0; i < _acVoltages.size(); i++)
                if (isNoneEmpty(i)) return i;
            return 0;
        }();
        _value[AC_VOLTAGE]->set(std::get<0>(_acVoltages[bestIndex]), std::get<1>(_acVoltages[bestIndex]));
    }
};
}  // namespace gui
}  // namespace catta
