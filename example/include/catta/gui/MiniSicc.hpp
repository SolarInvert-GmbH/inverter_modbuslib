#pragma once

// gui
#include <catta/gui/Connection.hpp>
#include <catta/gui/Password.hpp>
#include <catta/gui/Values.hpp>

// modbus
#include <catta/modbus/ValueCache.hpp>

// fltk
#include <FL/Fl.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Rect.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Terminal.H>

namespace catta
{
namespace gui
{
/**
 * @brief MiniSicc monitors a inverter.
 * @author CattaTech - Maik Urbannek
 */
template <class UART, class TIME>
class MiniSicc : public Fl_Double_Window
{
  public:
    /**
     * @param[in] defaultUartName The default device address of the uart.
     * Constructor.
     */
    MiniSicc(const std::uint64_t id, const char* defaultUartName)
        : Fl_Double_Window(200, 200, WIDTH, HEIGHT, "miniSICC"),
          _run(true),
          _current(CLIENTS),
          _acCurrentCallback(*this),
          _acPowerCallback(*this),
          _frequencyCallback(*this),
          _acApparentPowerCallback(*this),
          _acReactivePowerCallback(*this),
          _powerFactorCallback(*this),
          _energyProductionCallback(*this),
          _dcVoltageCallback(*this),
          _dcPowerCallback(*this),
          _temperatureCallback(*this),
          _sliderCallback(*this)
    {
        Fl::scheme("plastic");  // plastic, gleam, oxy
        Fl::foreground(0x00, 0x00, 0x00);
        Fl::background(0x59, 0x6a, 0x79);
        static constexpr int passwordHeight = 70;
        this->_connection = new Connection<UART>(10, 10, WIDTH - 20, 130, defaultUartName, nullptr, CLIENTS);
        this->_passwort = new Password(10, 145, WIDTH - 20, passwordHeight, nullptr, crc(id), nullptr, nullptr);
        this->_tabs = new Fl_Tabs(10, 150 + passwordHeight, WIDTH - 20, HEIGHT - 160 - passwordHeight);
        Fl_Group* g0 = new Fl_Group(10, 180 + passwordHeight, WIDTH - 20, HEIGHT - 185 - passwordHeight, "Values");
        this->_values = new Values(15, 190 + passwordHeight, WIDTH - 30, HEIGHT - 195 - passwordHeight);
        g0->end();
        this->resizable(this->_tabs);
        this->end();
        this->callback(close_cb);
        this->show();
        _cache.setRequest(CACHE_AC_CURRENT_SCALE, REQUEST_AC_CURRENT_SCALE);
        _cache.setRequest(CACHE_AC_CURRENT, REQUEST_AC_CURRENT);
        _cache.setRequest(CACHE_AC_POWER_SCALE, REQUEST_AC_POWER_SCALE);
        _cache.setRequest(CACHE_AC_POWER, REQUEST_AC_POWER);
        _cache.setRequest(CACHE_FREQUENCY_SCALE, REQUEST_FREQUENCY_SCALE);
        _cache.setRequest(CACHE_FREQUENCY, REQUEST_FREQUENCY);
        _cache.setRequest(CACHE_AC_APPARENT_POWER_SCALE, REQUEST_AC_APPARENT_POWER_SCALE);
        _cache.setRequest(CACHE_AC_APPARENT_POWER, REQUEST_AC_APPARENT_POWER);
        _cache.setRequest(CACHE_AC_REACTIVE_POWER_SCALE, REQUEST_AC_REACTIVE_POWER_SCALE);
        _cache.setRequest(CACHE_AC_REACTIVE_POWER, REQUEST_AC_REACTIVE_POWER);
        _cache.setRequest(CACHE_POWER_FACTOR_SCALE, REQUEST_POWER_FACTOR_SCALE);
        _cache.setRequest(CACHE_POWER_FACTOR, REQUEST_POWER_FACTOR);
        _cache.setRequest(CACHE_ENERGY_PRODUCTION_SCALE, REQUEST_ENERGY_PRODUCTION_SCALE);
        _cache.setRequest(CACHE_ENERGY_PRODUCTION, REQUEST_ENERGY_PRODUCTION);
        _cache.setRequest(CACHE_DC_VOLTAGE_SCALE, REQUEST_DC_VOLTAGE_SCALE);
        _cache.setRequest(CACHE_DC_VOLTAGE, REQUEST_DC_VOLTAGE);
        _cache.setRequest(CACHE_DC_POWER_SCALE, REQUEST_DC_POWER_SCALE);
        _cache.setRequest(CACHE_DC_POWER, REQUEST_DC_POWER);
        _cache.setRequest(CACHE_TEMPERATURE_SCALE, REQUEST_TEMPERATURE_SCALE);
        _cache.setRequest(CACHE_TEMPERATURE, REQUEST_TEMPERATURE);
        _cache.setCallback(CACHE_AC_CURRENT, _acCurrentCallback);
        _cache.setCallback(CACHE_AC_POWER, _acPowerCallback);
        _cache.setCallback(CACHE_FREQUENCY, _frequencyCallback);
        _cache.setCallback(CACHE_AC_APPARENT_POWER, _acApparentPowerCallback);
        _cache.setCallback(CACHE_AC_REACTIVE_POWER, _acReactivePowerCallback);
        _cache.setCallback(CACHE_POWER_FACTOR, _powerFactorCallback);
        _cache.setCallback(CACHE_ENERGY_PRODUCTION, _energyProductionCallback);
        _cache.setCallback(CACHE_DC_VOLTAGE, _dcVoltageCallback);
        _cache.setCallback(CACHE_DC_POWER, _dcPowerCallback);
        _cache.setCallback(CACHE_TEMPERATURE, _temperatureCallback);
        _sliderCallback(std::chrono::seconds{1});
        _values->setCallback(_sliderCallback);
    }
    /**
     * Runs mini SICC window. Blocks until the window is closed.
     */
    void run()
    {
        using namespace std::chrono_literals;
        while (this->_run)
        {
            const auto now = TIME::get();
            bool somethingHappend = false;

            {
                const auto [happend, tookRequest, isInIdle, receivedResponse, receivedRequest, current] = _connection->loop(_request, now);
                if (tookRequest) _request = {};
                if (happend) somethingHappend = true;
                const Request cacheRequest =
                    _cache.work(_request.isEmpty() && isInIdle && _current == CLIENT_CACHE, receivedResponse, receivedRequest, now);
                if (!cacheRequest.isEmpty())
                {
                    _request = cacheRequest;
                    somethingHappend = true;
                }
                if (_current < CLIENTS && current >= CLIENTS)
                    for (std::size_t i = 0; i < CACHE_SIZE; i++) _cache.setInvalid(i);
                _current = current;
            }
            if (!somethingHappend) Fl::wait(0);
        }
    }

  private:
    static constexpr std::size_t CLIENT_CACHE = 0;
    static constexpr std::size_t CLIENTS = CLIENT_CACHE + 1;

    static constexpr std::size_t CACHE_AC_CURRENT_SCALE = 0;
    static constexpr std::size_t CACHE_AC_CURRENT = CACHE_AC_CURRENT_SCALE + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_SCALE = CACHE_AC_CURRENT + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_A = CACHE_AC_VOLTAGE_SCALE + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_B = CACHE_AC_VOLTAGE_A + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_C = CACHE_AC_VOLTAGE_B + 1;
    static constexpr std::size_t CACHE_AC_POWER_SCALE = CACHE_AC_VOLTAGE_C + 1;
    static constexpr std::size_t CACHE_AC_POWER = CACHE_AC_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_FREQUENCY_SCALE = CACHE_AC_POWER + 1;
    static constexpr std::size_t CACHE_FREQUENCY = CACHE_FREQUENCY_SCALE + 1;
    static constexpr std::size_t CACHE_AC_APPARENT_POWER_SCALE = CACHE_FREQUENCY + 1;
    static constexpr std::size_t CACHE_AC_APPARENT_POWER = CACHE_AC_APPARENT_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_AC_REACTIVE_POWER_SCALE = CACHE_AC_APPARENT_POWER + 1;
    static constexpr std::size_t CACHE_AC_REACTIVE_POWER = CACHE_AC_REACTIVE_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_POWER_FACTOR_SCALE = CACHE_AC_REACTIVE_POWER + 1;
    static constexpr std::size_t CACHE_POWER_FACTOR = CACHE_POWER_FACTOR_SCALE + 1;
    static constexpr std::size_t CACHE_ENERGY_PRODUCTION_SCALE = CACHE_POWER_FACTOR + 1;
    static constexpr std::size_t CACHE_ENERGY_PRODUCTION = CACHE_ENERGY_PRODUCTION_SCALE + 1;
    static constexpr std::size_t CACHE_DC_VOLTAGE_SCALE = CACHE_ENERGY_PRODUCTION + 1;
    static constexpr std::size_t CACHE_DC_VOLTAGE = CACHE_DC_VOLTAGE_SCALE + 1;
    static constexpr std::size_t CACHE_DC_POWER_SCALE = CACHE_DC_VOLTAGE + 1;
    static constexpr std::size_t CACHE_DC_POWER = CACHE_DC_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_TEMPERATURE_SCALE = CACHE_DC_POWER + 1;
    static constexpr std::size_t CACHE_TEMPERATURE = CACHE_TEMPERATURE_SCALE + 1;
    static constexpr std::size_t CACHE_SIZE = CACHE_TEMPERATURE + 1;

    using Request = catta::modbus::si::request::Request;
    using Response = catta::modbus::si::response::Response;
    using ReadRegister = catta::modbus::si::ReadRegister;
    using RegisterAddress = catta::modbus::si::RegisterAddress;

    bool _run;

    Connection<UART>* _connection;
    Password* _passwort;
    catta::modbus::ValueCache<CACHE_SIZE> _cache;
    Request _request;
    std::size_t _current;

    Fl_Tabs* _tabs;
    Values* _values;

    static constexpr int WIDTH = 600;
    static constexpr int HEIGHT = 800;

    static void close_cb(Fl_Widget* widget, void*)
    {
        MiniSicc* self = dynamic_cast<MiniSicc*>(widget);
        if (self) self->_run = false;
    }

    static constexpr RegisterAddress REGISTER_AC_CURRENT_SCALE = RegisterAddress::inverterAmpsScaleFactor();
    static constexpr RegisterAddress REGISTER_AC_CURRENT = RegisterAddress::inverterAmps();
    static constexpr RegisterAddress REGISTER_AC_VOLTAGE_SCALE = RegisterAddress::inverterPhaseVoltageScaleFactor();
    static constexpr RegisterAddress REGISTER_AC_VOLTAGE_A = RegisterAddress::inverterPhaseVoltageA();
    static constexpr RegisterAddress REGISTER_AC_VOLTAGE_B = RegisterAddress::inverterPhaseVoltageB();
    static constexpr RegisterAddress REGISTER_AC_VOLTAGE_C = RegisterAddress::inverterPhaseVoltageC();
    static constexpr RegisterAddress REGISTER_AC_POWER_SCALE = RegisterAddress::inverterAcPowerScaleFactor();
    static constexpr RegisterAddress REGISTER_AC_POWER = RegisterAddress::inverterAcPower();
    static constexpr RegisterAddress REGISTER_FREQUENCY_SCALE = RegisterAddress::inverterHertzScaleFactor();
    static constexpr RegisterAddress REGISTER_FREQUENCY = RegisterAddress::inverterHertz();
    static constexpr RegisterAddress REGISTER_AC_APPARENT_POWER_SCALE = RegisterAddress::inverterAcApparentPowerScaleFactor();
    static constexpr RegisterAddress REGISTER_AC_APPARENT_POWER = RegisterAddress::inverterAcApparentPower();
    static constexpr RegisterAddress REGISTER_AC_REACTIVE_POWER_SCALE = RegisterAddress::inverterAcReactivePowerScaleFactor();
    static constexpr RegisterAddress REGISTER_AC_REACTIVE_POWER = RegisterAddress::inverterAcReactivePower();
    static constexpr RegisterAddress REGISTER_POWER_FACTOR_SCALE = RegisterAddress::inverterPowerFactorScaleFactor();
    static constexpr RegisterAddress REGISTER_POWER_FACTOR = RegisterAddress::inverterPowerFactor();
    static constexpr RegisterAddress REGISTER_ENERGY_PRODUCTION_SCALE = RegisterAddress::inverterWattHoursScaleFactor();
    static constexpr RegisterAddress REGISTER_ENERGY_PRODUCTION = RegisterAddress::inverterWattHours();
    static constexpr RegisterAddress REGISTER_DC_VOLTAGE_SCALE = RegisterAddress::inverterPhaseVoltageScaleFactor();
    static constexpr RegisterAddress REGISTER_DC_VOLTAGE = RegisterAddress::inverterPhaseVoltageA();
    static constexpr RegisterAddress REGISTER_DC_POWER_SCALE = RegisterAddress::inverterDcPowerScaleFactor();
    static constexpr RegisterAddress REGISTER_DC_POWER = RegisterAddress::inverterDcPower();
    static constexpr RegisterAddress REGISTER_TEMPERATURE_SCALE = RegisterAddress::inverterTemperatureScaleFactor();
    static constexpr RegisterAddress REGISTER_TEMPERATURE = RegisterAddress::inverterTemperature();

    static constexpr Request REQUEST_AC_CURRENT_SCALE = Request::readRegister(ReadRegister::create(REGISTER_AC_CURRENT_SCALE));
    static constexpr Request REQUEST_AC_CURRENT = Request::readRegister(ReadRegister::create(REGISTER_AC_CURRENT));
    static constexpr Request REQUEST_AC_VOLTAGE_SCALE = Request::readRegister(ReadRegister::create(REGISTER_AC_VOLTAGE_SCALE));
    static constexpr Request REQUEST_AC_VOLTAGE_A = Request::readRegister(ReadRegister::create(REGISTER_AC_VOLTAGE_A));
    static constexpr Request REQUEST_AC_VOLTAGE_B = Request::readRegister(ReadRegister::create(REGISTER_AC_VOLTAGE_B));
    static constexpr Request REQUEST_AC_VOLTAGE_C = Request::readRegister(ReadRegister::create(REGISTER_AC_VOLTAGE_C));
    static constexpr Request REQUEST_AC_POWER_SCALE = Request::readRegister(ReadRegister::create(REGISTER_AC_POWER_SCALE));
    static constexpr Request REQUEST_AC_POWER = Request::readRegister(ReadRegister::create(REGISTER_AC_POWER));
    static constexpr Request REQUEST_FREQUENCY_SCALE = Request::readRegister(ReadRegister::create(REGISTER_FREQUENCY_SCALE));
    static constexpr Request REQUEST_FREQUENCY = Request::readRegister(ReadRegister::create(REGISTER_FREQUENCY));
    static constexpr Request REQUEST_AC_APPARENT_POWER_SCALE = Request::readRegister(ReadRegister::create(REGISTER_AC_APPARENT_POWER_SCALE));
    static constexpr Request REQUEST_AC_APPARENT_POWER = Request::readRegister(ReadRegister::create(REGISTER_AC_APPARENT_POWER));
    static constexpr Request REQUEST_AC_REACTIVE_POWER_SCALE = Request::readRegister(ReadRegister::create(REGISTER_AC_REACTIVE_POWER_SCALE));
    static constexpr Request REQUEST_AC_REACTIVE_POWER = Request::readRegister(ReadRegister::create(REGISTER_AC_REACTIVE_POWER));
    static constexpr Request REQUEST_POWER_FACTOR_SCALE = Request::readRegister(ReadRegister::create(REGISTER_POWER_FACTOR_SCALE));
    static constexpr Request REQUEST_POWER_FACTOR = Request::readRegister(ReadRegister::create(REGISTER_POWER_FACTOR));
    static constexpr Request REQUEST_ENERGY_PRODUCTION_SCALE = Request::readRegister(ReadRegister::create(REGISTER_ENERGY_PRODUCTION_SCALE));
    static constexpr Request REQUEST_ENERGY_PRODUCTION = Request::readRegister(ReadRegister::create(REGISTER_ENERGY_PRODUCTION));
    static constexpr Request REQUEST_DC_VOLTAGE_SCALE = Request::readRegister(ReadRegister::create(REGISTER_DC_VOLTAGE_SCALE));
    static constexpr Request REQUEST_DC_VOLTAGE = Request::readRegister(ReadRegister::create(REGISTER_DC_VOLTAGE));
    static constexpr Request REQUEST_DC_POWER_SCALE = Request::readRegister(ReadRegister::create(REGISTER_DC_POWER_SCALE));
    static constexpr Request REQUEST_DC_POWER = Request::readRegister(ReadRegister::create(REGISTER_DC_POWER));
    static constexpr Request REQUEST_TEMPERATURE_SCALE = Request::readRegister(ReadRegister::create(REGISTER_TEMPERATURE_SCALE));
    static constexpr Request REQUEST_TEMPERATURE = Request::readRegister(ReadRegister::create(REGISTER_TEMPERATURE));

    class AcCurrent
    {
      public:
        static constexpr const char* unit = "A";
        static constexpr std::size_t cacheScale = CACHE_AC_CURRENT_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_CURRENT;
        static void setValue(Values* values, const std::string& value) { values->setAcCurrent(value); }
    };

    class AcPower
    {
      public:
        static constexpr const char* unit = "W";
        static constexpr std::size_t cacheScale = CACHE_AC_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_POWER;
        static void setValue(Values* values, const std::string& value) { values->setAcPower(value); }
    };

    class Frequency
    {
      public:
        static constexpr const char* unit = "Hz";
        static constexpr std::size_t cacheScale = CACHE_FREQUENCY_SCALE;
        static constexpr RegisterAddress address = REGISTER_FREQUENCY;
        static void setValue(Values* values, const std::string& value) { values->setFrequency(value); }
    };

    class AcApparentPower
    {
      public:
        static constexpr const char* unit = "VA";
        static constexpr std::size_t cacheScale = CACHE_AC_APPARENT_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_APPARENT_POWER;
        static void setValue(Values* values, const std::string& value) { values->setAcApparentPower(value); }
    };

    class AcReactivePower
    {
      public:
        static constexpr const char* unit = "VA";
        static constexpr std::size_t cacheScale = CACHE_AC_REACTIVE_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_REACTIVE_POWER;
        static void setValue(Values* values, const std::string& value) { values->setAcReactivePower(value); }
    };

    class PowerFactor
    {
      public:
        static constexpr const char* unit = "%";
        static constexpr std::size_t cacheScale = CACHE_POWER_FACTOR_SCALE;
        static constexpr RegisterAddress address = REGISTER_POWER_FACTOR;
        static void setValue(Values* values, const std::string& value) { values->setPowerFactor(value); }
    };

    class EnergyProduction
    {
      public:
        static constexpr const char* unit = "Wh";
        static constexpr std::size_t cacheScale = CACHE_ENERGY_PRODUCTION_SCALE;
        static constexpr RegisterAddress address = REGISTER_ENERGY_PRODUCTION;
        static void setValue(Values* values, const std::string& value) { values->setEnergyProduction(value); }
    };

    class DcVoltage
    {
      public:
        static constexpr const char* unit = "V";
        static constexpr std::size_t cacheScale = CACHE_DC_VOLTAGE_SCALE;
        static constexpr RegisterAddress address = REGISTER_DC_VOLTAGE;
        static void setValue(Values* values, const std::string& value) { values->setDcVoltage(value); }
    };

    class DcPower
    {
      public:
        static constexpr const char* unit = "W";
        static constexpr std::size_t cacheScale = CACHE_DC_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_DC_POWER;
        static void setValue(Values* values, const std::string& value) { values->setDcPower(value); }
    };

    class Temperature
    {
      public:
        static constexpr const char* unit = "°C";
        static constexpr std::size_t cacheScale = CACHE_TEMPERATURE_SCALE;
        static constexpr RegisterAddress address = REGISTER_TEMPERATURE;
        static void setValue(Values* values, const std::string& value) { values->setTemperature(value); }
    };

    template <class T>
    class ScaledValueCallback
    {
      public:
        ScaledValueCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            const auto& scaleResponse = _miniSicc._cache.getResponse(T::cacheScale);
            const std::int16_t scale = static_cast<std::int16_t>(scaleResponse.value16Value());
            if (!scaleResponse.type().isValue16() || scale < -10 || scale > 10)
            {
                _miniSicc._cache.setInvalid(T::cacheScale);
                T::setValue(_miniSicc._values, std::string());
            }
            else
            {
                std::uint64_t t = 0;
                bool minus = false;

                switch (T::address.type())
                {
                    case catta::modbus::si::RegisterType::sint16():
                    {
                        if (!r.type().isValue16()) return T::setValue(_miniSicc._values, std::string());
                        if (static_cast<std::int16_t>(r.value16Value()) < 0)
                        {
                            minus = true;
                            t = static_cast<std::uint16_t>(-static_cast<std::int16_t>(r.value16Value()));
                        }
                        else
                            t = r.value16Value();
                        break;
                    }
                    case catta::modbus::si::RegisterType::uint16():
                        if (!r.type().isValue16()) return T::setValue(_miniSicc._values, std::string());
                        t = r.value16Value();
                        break;
                    case catta::modbus::si::RegisterType::uint32():
                        if (!r.type().isValue32()) return T::setValue(_miniSicc._values, std::string());
                        t = r.value32Value();
                        break;
                    case catta::modbus::si::RegisterType::uint64():
                        if (!r.type().isValue64()) return T::setValue(_miniSicc._values, std::string());
                        t = r.value64Value();
                        break;
                    default:
                        return T::setValue(_miniSicc._values, std::string());
                }
                const std::string scaledNumber = [scale, minus, t]()
                {
                    if (scale == 0) return std::to_string(t);
                    if (scale > 0) return std::to_string(t) + std::string(static_cast<std::size_t>(scale), '0');
                    const std::uint64_t factor = [scale]()
                    {
                        std::uint64_t result = 1;
                        for (std::int16_t i = 0; i > scale; i--) result = result * 10;
                        return result;
                    }();
                    std::string result;
                    if (minus) result += '-';
                    result += std::to_string(t / factor);
                    result += '.';
                    for (std::uint64_t i = factor / 10; i > 0; i = i / 10) result += static_cast<char>('0' + (t / i) % 10);
                    return result;
                }();
                T::setValue(_miniSicc._values, scaledNumber + ' ' + T::unit);
            }
        }

      private:
        MiniSicc& _miniSicc;
    };

    ScaledValueCallback<AcCurrent> _acCurrentCallback;
    ScaledValueCallback<AcPower> _acPowerCallback;
    ScaledValueCallback<Frequency> _frequencyCallback;
    ScaledValueCallback<AcApparentPower> _acApparentPowerCallback;
    ScaledValueCallback<AcReactivePower> _acReactivePowerCallback;
    ScaledValueCallback<PowerFactor> _powerFactorCallback;
    ScaledValueCallback<EnergyProduction> _energyProductionCallback;
    ScaledValueCallback<DcVoltage> _dcVoltageCallback;
    ScaledValueCallback<DcPower> _dcPowerCallback;
    ScaledValueCallback<Temperature> _temperatureCallback;

    class SliderCallback
    {
      public:
        SliderCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const std::chrono::microseconds t)
        {
            _miniSicc._cache.setValidTime(CACHE_AC_CURRENT, t * 4);
            _miniSicc._cache.setValidTime(CACHE_AC_POWER, t * 4);
            _miniSicc._cache.setValidTime(CACHE_FREQUENCY, t * 4);
            _miniSicc._cache.setValidTime(CACHE_AC_APPARENT_POWER, t * 4);
            _miniSicc._cache.setValidTime(CACHE_AC_REACTIVE_POWER, t * 4);
            _miniSicc._cache.setValidTime(CACHE_POWER_FACTOR, t * 4);
            _miniSicc._cache.setValidTime(CACHE_ENERGY_PRODUCTION, t * 4);
            _miniSicc._cache.setValidTime(CACHE_DC_VOLTAGE, t * 4);
            _miniSicc._cache.setValidTime(CACHE_DC_POWER, t * 4);
            _miniSicc._cache.setValidTime(CACHE_TEMPERATURE, t * 4);
        }

      private:
        MiniSicc& _miniSicc;
    } _sliderCallback;
    constexpr static std::uint16_t crc(const std::uint64_t input)
    {
        const auto next = [](const std::uint8_t byte, const std::uint16_t last)
        {
            const auto loop = [byte](const std::uint16_t last, const int i)
            {
                const std::uint16_t xorFlag = last & 0x8000;
                const std::uint16_t shift = static_cast<std::uint16_t>(last << 1);
                const std::uint16_t minor = (byte & (1 << i)) ? 1 : 0;
                return xorFlag == 0 ? (shift | minor) : (shift | minor) ^ 0x1021;
            };
            std::uint16_t value = last;
            for (int i = 7; i >= 0; i--) loop(value, i);
            return value;
        };
        std::uint16_t crc = 0xffff;
        for (uint8_t i = 0; i < 8; i++)
        {
            const std::uint8_t data = static_cast<std::uint8_t>(input >> (i * 8));
            crc = next(data, crc);
        }
        crc = next(0x00, crc);
        crc = next(0x00, crc);
        return crc;
    }
};
}  // namespace gui
}  // namespace catta
