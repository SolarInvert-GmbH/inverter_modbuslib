#pragma once

// gui
#include <catta/gui/Battery.hpp>
#include <catta/gui/Commands.hpp>
#include <catta/gui/Connection.hpp>
#include <catta/gui/Password.hpp>
#include <catta/gui/Solar.hpp>
#include <catta/gui/Static.hpp>
#include <catta/gui/Values.hpp>
#include <catta/gui/Wind.hpp>

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
          _acVoltageACallback(*this),
          _acVoltageBCallback(*this),
          _acVoltageCCallback(*this),
          _frequencyCallback(*this),
          _powerFactorCallback(*this),
          _energyProductionCallback(*this),
          _dcVoltageCallback(*this),
          _dcPowerCallback(*this),
          _temperatureCallback(*this),
          _pmaxCallback(*this),
          _nightShutdownCallback(*this),
          _startCountdownCallback(*this),
          _uptimeCallback(*this),
          _cosphiCallback(*this),
          _dacCallback(*this),
          _event1Callback(*this),
          _event3Callback(*this),
          _operatingStateCallback(*this),
          _derTypeCallbackCallback(*this),
          _reductionCallback(*this),
          _factoryValuesCallback(*this),
          _softwareVersionCallback(*this),
          _sliderCallback(*this),
          _unlock(*this),
          _lock(*this)
    {
        Fl::scheme("plastic");  // plastic, gleam, oxy
        Fl::foreground(0x00, 0x00, 0x00);
        Fl::background(0x59, 0x6a, 0x79);
        static constexpr int passwordHeight = 70;
        this->_connection = new Connection<UART>(10, 10, WIDTH - 20, 130, defaultUartName, nullptr, CLIENTS);
        this->_passwort = new Password(10, 145, WIDTH - 20, passwordHeight, nullptr, crc(id), _unlock, _lock);
        const int Xtab = 10;
        const int Ytab = 180 + passwordHeight;
        const int Wtab = WIDTH - 20;
        const int Htab = HEIGHT - 185 - passwordHeight;
        const int Xcontent = Xtab + 5;
        const int Ycontent = Ytab + 10;
        const int Wcontent = Wtab - 10;
        const int Hcontent = Htab - 10;
        this->_tabs = new Fl_Tabs(10, 150 + passwordHeight, WIDTH - 20, HEIGHT - 160 - passwordHeight);

        _tab0 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Values");
        this->_values = new Values(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab0->end();
        _tab1 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Statices");
        this->_static = new Static(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab1->end();
        _tab2 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Battery");
        this->_battery = new Battery(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab2->end();
        _tab3 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Solar");
        this->_solar = new Solar(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab3->end();
        _tab4 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Wind");
        this->_wind = new Wind(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab4->end();
        _tab5 = new Fl_Group(Xtab, Ytab, Wtab, Htab, "Commands");
        this->_commands = new Commands(Xcontent, Ycontent, Wcontent, Hcontent);
        _tab5->end();
        this->resizable(this->_tabs);
        this->end();
        this->callback(close_cb);
        this->show();

        _cache.setRequest(CACHE_DER_TYPE, REQUEST_DER_TYPE);
        _cache.setRequest(CACHE_REDUCTION, REQUEST_REDUCTION);
        _cache.setRequest(CACHE_FACTORY_VALUES, REQUEST_FACTORY_VALUES);
        _cache.setRequest(CACHE_SOFTWARE_VERSION, REQUEST_SOFTWARE_VERSION);
        _cache.setRequest(CACHE_AC_CURRENT_SCALE, REQUEST_AC_CURRENT_SCALE);
        _cache.setRequest(CACHE_AC_CURRENT, REQUEST_AC_CURRENT);
        _cache.setRequest(CACHE_AC_POWER_SCALE, REQUEST_AC_POWER_SCALE);
        _cache.setRequest(CACHE_AC_POWER, REQUEST_AC_POWER);
        _cache.setRequest(CACHE_AC_VOLTAGE_SCALE, REQUEST_AC_VOLTAGE_SCALE);
        _cache.setRequest(CACHE_AC_VOLTAGE_A, REQUEST_AC_VOLTAGE_A);
        _cache.setRequest(CACHE_AC_VOLTAGE_B, REQUEST_AC_VOLTAGE_B);
        _cache.setRequest(CACHE_AC_VOLTAGE_C, REQUEST_AC_VOLTAGE_C);
        _cache.setRequest(CACHE_FREQUENCY_SCALE, REQUEST_FREQUENCY_SCALE);
        _cache.setRequest(CACHE_FREQUENCY, REQUEST_FREQUENCY);
        _cache.setRequest(CACHE_POWER_FACTOR_SCALE, REQUEST_POWER_FACTOR_SCALE);
        _cache.setRequest(CACHE_POWER_FACTOR, REQUEST_POWER_FACTOR);
        _cache.setRequest(CACHE_COSPHI, REQUEST_COSPHI);
        _cache.setRequest(CACHE_DAC, REQUEST_DAC);
        _cache.setRequest(CACHE_EVENTS_1, REQUEST_EVENTS_1);
        _cache.setRequest(CACHE_EVENTS_3, REQUEST_EVENTS_3);
        _cache.setRequest(CACHE_ENERGY_PRODUCTION_SCALE, REQUEST_ENERGY_PRODUCTION_SCALE);
        _cache.setRequest(CACHE_ENERGY_PRODUCTION, REQUEST_ENERGY_PRODUCTION);
        _cache.setRequest(CACHE_DC_VOLTAGE_SCALE, REQUEST_DC_VOLTAGE_SCALE);
        _cache.setRequest(CACHE_DC_VOLTAGE, REQUEST_DC_VOLTAGE);
        _cache.setRequest(CACHE_DC_POWER_SCALE, REQUEST_DC_POWER_SCALE);
        _cache.setRequest(CACHE_DC_POWER, REQUEST_DC_POWER);
        _cache.setRequest(CACHE_TEMPERATURE_SCALE, REQUEST_TEMPERATURE_SCALE);
        _cache.setRequest(CACHE_TEMPERATURE, REQUEST_TEMPERATURE);
        _cache.setRequest(CACHE_PMAX, REQUEST_PMAX);
        _cache.setRequest(CACHE_NIGHT_SHUTDOWN, REQUEST_NIGHT_SHUTDOWN);
        _cache.setRequest(CACHE_START_COUNTDOWN, REQUEST_START_COUNTDOWN);
        _cache.setRequest(CACHE_UPTIME, REQUEST_UPTIME);
        _cache.setRequest(CACHE_VENDOR_OPERATING_STATE, REQUEST_VENDOR_OPERATING_STATE);
        _cache.setCallback(CACHE_AC_CURRENT, _acCurrentCallback);
        _cache.setCallback(CACHE_AC_POWER, _acPowerCallback);
        _cache.setCallback(CACHE_AC_VOLTAGE_A, _acVoltageACallback);
        _cache.setCallback(CACHE_AC_VOLTAGE_B, _acVoltageBCallback);
        _cache.setCallback(CACHE_AC_VOLTAGE_C, _acVoltageCCallback);
        _cache.setCallback(CACHE_FREQUENCY, _frequencyCallback);
        _cache.setCallback(CACHE_POWER_FACTOR, _powerFactorCallback);
        _cache.setCallback(CACHE_COSPHI, _cosphiCallback);
        _cache.setCallback(CACHE_DAC, _dacCallback);
        _cache.setCallback(CACHE_EVENTS_1, _event1Callback);
        _cache.setCallback(CACHE_EVENTS_3, _event3Callback);
        _cache.setCallback(CACHE_ENERGY_PRODUCTION, _energyProductionCallback);
        _cache.setCallback(CACHE_DC_VOLTAGE, _dcVoltageCallback);
        _cache.setCallback(CACHE_DC_POWER, _dcPowerCallback);
        _cache.setCallback(CACHE_TEMPERATURE, _temperatureCallback);
        _cache.setCallback(CACHE_PMAX, _pmaxCallback);
        _cache.setCallback(CACHE_NIGHT_SHUTDOWN, _nightShutdownCallback);
        _cache.setCallback(CACHE_START_COUNTDOWN, _startCountdownCallback);
        _cache.setCallback(CACHE_UPTIME, _uptimeCallback);
        _cache.setCallback(CACHE_VENDOR_OPERATING_STATE, _operatingStateCallback);
        _cache.setCallback(CACHE_DER_TYPE, _derTypeCallbackCallback);
        _cache.setCallback(CACHE_FACTORY_VALUES, _factoryValuesCallback);
        _cache.setCallback(CACHE_REDUCTION, _reductionCallback);
        _cache.setCallback(CACHE_SOFTWARE_VERSION, _softwareVersionCallback);
        _values->setCallback(_sliderCallback);
        _lock();
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
                const Request batteryRequest =
                    _battery->work(_request.isEmpty() && isInIdle && _current == CLIENT_BATTERY, receivedResponse, receivedRequest, now);
                if (!batteryRequest.isEmpty())
                {
                    _request = batteryRequest;
                    somethingHappend = true;
                }
                const Request solarRequest =
                    _solar->work(_request.isEmpty() && isInIdle && _current == CLIENT_SOLAR, receivedResponse, receivedRequest, now);
                if (!solarRequest.isEmpty())
                {
                    _request = solarRequest;
                    somethingHappend = true;
                }
                const Request windRequest =
                    _wind->work(_request.isEmpty() && isInIdle && _current == CLIENT_WIND, receivedResponse, receivedRequest, now);
                if (!windRequest.isEmpty())
                {
                    _request = windRequest;
                    somethingHappend = true;
                }
                const Request commandsRequest =
                    _commands->work(_request.isEmpty() && isInIdle && _current == CLIENT_COMMANDS, receivedResponse, receivedRequest);
                if (!commandsRequest.isEmpty())
                {
                    _request = commandsRequest;
                    somethingHappend = true;
                }
                if (_current < CLIENTS && current >= CLIENTS)
                    for (std::size_t i = 0; i < CACHE_SIZE; i++) _cache.setInvalid(i);
                _current = current;
            }
            _values->work(now);
            if (!somethingHappend) Fl::wait(0);
        }
    }

  private:
    static constexpr std::size_t CLIENT_CACHE = 0;
    static constexpr std::size_t CLIENT_BATTERY = CLIENT_CACHE + 1;
    static constexpr std::size_t CLIENT_SOLAR = CLIENT_BATTERY + 1;
    static constexpr std::size_t CLIENT_WIND = CLIENT_SOLAR + 1;
    static constexpr std::size_t CLIENT_COMMANDS = CLIENT_WIND + 1;
    static constexpr std::size_t CLIENTS = CLIENT_COMMANDS + 1;

    static constexpr std::size_t CACHE_DER_TYPE = 0;
    static constexpr std::size_t CACHE_REDUCTION = CACHE_DER_TYPE + 1;
    static constexpr std::size_t CACHE_FACTORY_VALUES = CACHE_REDUCTION + 1;
    static constexpr std::size_t CACHE_SOFTWARE_VERSION = CACHE_FACTORY_VALUES + 1;
    static constexpr std::size_t CACHE_AC_CURRENT_SCALE = CACHE_SOFTWARE_VERSION + 1;
    static constexpr std::size_t CACHE_AC_CURRENT = CACHE_AC_CURRENT_SCALE + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_SCALE = CACHE_AC_CURRENT + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_A = CACHE_AC_VOLTAGE_SCALE + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_B = CACHE_AC_VOLTAGE_A + 1;
    static constexpr std::size_t CACHE_AC_VOLTAGE_C = CACHE_AC_VOLTAGE_B + 1;
    static constexpr std::size_t CACHE_AC_POWER_SCALE = CACHE_AC_VOLTAGE_C + 1;
    static constexpr std::size_t CACHE_AC_POWER = CACHE_AC_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_FREQUENCY_SCALE = CACHE_AC_POWER + 1;
    static constexpr std::size_t CACHE_FREQUENCY = CACHE_FREQUENCY_SCALE + 1;
    static constexpr std::size_t CACHE_POWER_FACTOR_SCALE = CACHE_FREQUENCY + 1;
    static constexpr std::size_t CACHE_POWER_FACTOR = CACHE_POWER_FACTOR_SCALE + 1;
    static constexpr std::size_t CACHE_COSPHI = CACHE_POWER_FACTOR + 1;
    static constexpr std::size_t CACHE_DAC = CACHE_COSPHI + 1;
    static constexpr std::size_t CACHE_EVENTS_1 = CACHE_DAC + 1;
    static constexpr std::size_t CACHE_EVENTS_3 = CACHE_EVENTS_1 + 1;
    static constexpr std::size_t CACHE_ENERGY_PRODUCTION_SCALE = CACHE_EVENTS_3 + 1;
    static constexpr std::size_t CACHE_ENERGY_PRODUCTION = CACHE_ENERGY_PRODUCTION_SCALE + 1;
    static constexpr std::size_t CACHE_DC_VOLTAGE_SCALE = CACHE_ENERGY_PRODUCTION + 1;
    static constexpr std::size_t CACHE_DC_VOLTAGE = CACHE_DC_VOLTAGE_SCALE + 1;
    static constexpr std::size_t CACHE_DC_POWER_SCALE = CACHE_DC_VOLTAGE + 1;
    static constexpr std::size_t CACHE_DC_POWER = CACHE_DC_POWER_SCALE + 1;
    static constexpr std::size_t CACHE_TEMPERATURE_SCALE = CACHE_DC_POWER + 1;
    static constexpr std::size_t CACHE_TEMPERATURE = CACHE_TEMPERATURE_SCALE + 1;
    static constexpr std::size_t CACHE_PMAX = CACHE_TEMPERATURE + 1;
    static constexpr std::size_t CACHE_NIGHT_SHUTDOWN = CACHE_PMAX + 1;
    static constexpr std::size_t CACHE_START_COUNTDOWN = CACHE_NIGHT_SHUTDOWN + 1;
    static constexpr std::size_t CACHE_UPTIME = CACHE_START_COUNTDOWN + 1;
    static constexpr std::size_t CACHE_VENDOR_OPERATING_STATE = CACHE_UPTIME + 1;
    static constexpr std::size_t CACHE_SIZE = CACHE_VENDOR_OPERATING_STATE + 1;

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
    Static* _static;
    Battery* _battery;
    Solar* _solar;
    Wind* _wind;
    Commands* _commands;
    Fl_Group* _tab0;
    Fl_Group* _tab1;
    Fl_Group* _tab2;
    Fl_Group* _tab3;
    Fl_Group* _tab4;
    Fl_Group* _tab5;

    static constexpr int WIDTH = 600;
    static constexpr int HEIGHT = 800;

    static void close_cb(Fl_Widget* widget, void*)
    {
        MiniSicc* self = dynamic_cast<MiniSicc*>(widget);
        if (self) self->_run = false;
    }

    static constexpr RegisterAddress REGISTER_DER_TYPE = RegisterAddress::nameplateDerType();
    static constexpr RegisterAddress REGISTER_REDUCTION = RegisterAddress::siControlReduction();
    static constexpr RegisterAddress REGISTER_SOFTWARE_VERSION = RegisterAddress::commonVersion();
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
    static constexpr RegisterAddress REGISTER_POWER_FACTOR_SCALE = RegisterAddress::inverterPowerFactorScaleFactor();
    static constexpr RegisterAddress REGISTER_POWER_FACTOR = RegisterAddress::inverterPowerFactor();
    static constexpr RegisterAddress REGISTER_COSPHI = RegisterAddress::siControlCosphi();
    static constexpr RegisterAddress REGISTER_DAC = RegisterAddress::siControlSineduty();
    static constexpr RegisterAddress REGISTER_EVENT_1 = RegisterAddress::inverterVendorEventBitfield1();
    static constexpr RegisterAddress REGISTER_EVENT_3 = RegisterAddress::inverterVendorEventBitfield3();
    static constexpr RegisterAddress REGISTER_ENERGY_PRODUCTION_SCALE = RegisterAddress::inverterWattHoursScaleFactor();
    static constexpr RegisterAddress REGISTER_ENERGY_PRODUCTION = RegisterAddress::inverterWattHours();
    static constexpr RegisterAddress REGISTER_DC_VOLTAGE_SCALE = RegisterAddress::inverterDcPowerScaleFactor();
    static constexpr RegisterAddress REGISTER_DC_VOLTAGE = RegisterAddress::inverterDcVoltage();
    static constexpr RegisterAddress REGISTER_DC_POWER_SCALE = RegisterAddress::inverterDcPowerScaleFactor();
    static constexpr RegisterAddress REGISTER_DC_POWER = RegisterAddress::inverterDcPower();
    static constexpr RegisterAddress REGISTER_TEMPERATURE_SCALE = RegisterAddress::inverterTemperatureScaleFactor();
    static constexpr RegisterAddress REGISTER_TEMPERATURE = RegisterAddress::inverterTemperature();
    static constexpr RegisterAddress REGISTER_PMAX = RegisterAddress::siControlPmax();
    static constexpr RegisterAddress REGISTER_NIGHT_SHUTDOWN = RegisterAddress::siControlNightShutdown();
    static constexpr RegisterAddress REGISTER_START_COUNTDOWN = RegisterAddress::siControlStartCountdown();
    static constexpr RegisterAddress REGISTER_UPTIME = RegisterAddress::siControlUptime();
    static constexpr RegisterAddress REGISTER_VENDOR_OPERATING_STATE = RegisterAddress::inverterVendorOperatingState();

    static constexpr Request REQUEST_DER_TYPE = Request::readRegister(ReadRegister::create(REGISTER_DER_TYPE));
    static constexpr Request REQUEST_REDUCTION = Request::readRegister(ReadRegister::create(REGISTER_REDUCTION));
    static constexpr Request REQUEST_FACTORY_VALUES = Request::factoryValues();
    static constexpr Request REQUEST_SOFTWARE_VERSION = Request::readRegister(ReadRegister::create(REGISTER_SOFTWARE_VERSION));
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
    static constexpr Request REQUEST_POWER_FACTOR_SCALE = Request::readRegister(ReadRegister::create(REGISTER_POWER_FACTOR_SCALE));
    static constexpr Request REQUEST_POWER_FACTOR = Request::readRegister(ReadRegister::create(REGISTER_POWER_FACTOR));
    static constexpr Request REQUEST_COSPHI = Request::readRegister(ReadRegister::create(REGISTER_COSPHI));
    static constexpr Request REQUEST_DAC = Request::readRegister(ReadRegister::create(REGISTER_DAC));
    static constexpr Request REQUEST_EVENTS_1 = Request::readRegister(ReadRegister::create(REGISTER_EVENT_1));
    static constexpr Request REQUEST_EVENTS_3 = Request::readRegister(ReadRegister::create(REGISTER_EVENT_3));
    static constexpr Request REQUEST_ENERGY_PRODUCTION_SCALE = Request::readRegister(ReadRegister::create(REGISTER_ENERGY_PRODUCTION_SCALE));
    static constexpr Request REQUEST_ENERGY_PRODUCTION = Request::readRegister(ReadRegister::create(REGISTER_ENERGY_PRODUCTION));
    static constexpr Request REQUEST_DC_VOLTAGE_SCALE = Request::readRegister(ReadRegister::create(REGISTER_DC_VOLTAGE_SCALE));
    static constexpr Request REQUEST_DC_VOLTAGE = Request::readRegister(ReadRegister::create(REGISTER_DC_VOLTAGE));
    static constexpr Request REQUEST_DC_POWER_SCALE = Request::readRegister(ReadRegister::create(REGISTER_DC_POWER_SCALE));
    static constexpr Request REQUEST_DC_POWER = Request::readRegister(ReadRegister::create(REGISTER_DC_POWER));
    static constexpr Request REQUEST_TEMPERATURE_SCALE = Request::readRegister(ReadRegister::create(REGISTER_TEMPERATURE_SCALE));
    static constexpr Request REQUEST_TEMPERATURE = Request::readRegister(ReadRegister::create(REGISTER_TEMPERATURE));
    static constexpr Request REQUEST_PMAX = Request::readRegister(ReadRegister::create(REGISTER_PMAX));
    static constexpr Request REQUEST_NIGHT_SHUTDOWN = Request::readRegister(ReadRegister::create(REGISTER_NIGHT_SHUTDOWN));
    static constexpr Request REQUEST_START_COUNTDOWN = Request::readRegister(ReadRegister::create(REGISTER_START_COUNTDOWN));
    static constexpr Request REQUEST_UPTIME = Request::readRegister(ReadRegister::create(REGISTER_UPTIME));
    static constexpr Request REQUEST_VENDOR_OPERATING_STATE = Request::readRegister(ReadRegister::create(REGISTER_VENDOR_OPERATING_STATE));

    class AcCurrent
    {
      public:
        static constexpr const char* unit = "A";
        static constexpr std::size_t cacheScale = CACHE_AC_CURRENT_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_CURRENT;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setAcCurrent(value, unit); }
    };

    class AcPower
    {
      public:
        static constexpr const char* unit = "W";
        static constexpr std::size_t cacheScale = CACHE_AC_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_POWER;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setAcPower(value, unit); }
    };

    class Frequency
    {
      public:
        static constexpr const char* unit = "Hz";
        static constexpr std::size_t cacheScale = CACHE_FREQUENCY_SCALE;
        static constexpr RegisterAddress address = REGISTER_FREQUENCY;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setFrequency(value, unit); }
    };

    class PowerFactor
    {
      public:
        static constexpr const char* unit = nullptr;
        static constexpr std::size_t cacheScale = CACHE_POWER_FACTOR_SCALE;
        static constexpr RegisterAddress address = REGISTER_POWER_FACTOR;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setPowerFactor(value, unit); }
    };

    class EnergyProduction
    {
      public:
        static constexpr const char* unit = "Wh";
        static constexpr std::size_t cacheScale = CACHE_ENERGY_PRODUCTION_SCALE;
        static constexpr RegisterAddress address = REGISTER_ENERGY_PRODUCTION;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setEnergyProduction(value, unit); }
    };

    class DcVoltage
    {
      public:
        static constexpr const char* unit = "V";
        static constexpr std::size_t cacheScale = CACHE_DC_VOLTAGE_SCALE;
        static constexpr RegisterAddress address = REGISTER_DC_VOLTAGE;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setDcVoltage(value, unit); }
    };

    class DcPower
    {
      public:
        static constexpr const char* unit = "W";
        static constexpr std::size_t cacheScale = CACHE_DC_POWER_SCALE;
        static constexpr RegisterAddress address = REGISTER_DC_POWER;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setDcPower(value, unit); }
    };

    class Temperature
    {
      public:
        static constexpr const char* unit = "°C";
        static constexpr std::size_t cacheScale = CACHE_TEMPERATURE_SCALE;
        static constexpr RegisterAddress address = REGISTER_TEMPERATURE;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setTemperature(value, unit); }
    };

    class AcVoltageA
    {
      public:
        static constexpr const char* unit = "V";
        static constexpr std::size_t cacheScale = CACHE_AC_VOLTAGE_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_VOLTAGE_A;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setAcVoltageA(value, unit); }
    };

    class AcVoltageB
    {
      public:
        static constexpr const char* unit = "V";
        static constexpr std::size_t cacheScale = CACHE_AC_VOLTAGE_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_VOLTAGE_B;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setAcVoltageB(value, unit); }
    };

    class AcVoltageC
    {
      public:
        static constexpr const char* unit = "V";
        static constexpr std::size_t cacheScale = CACHE_AC_VOLTAGE_SCALE;
        static constexpr RegisterAddress address = REGISTER_AC_VOLTAGE_B;
        static void setValue(Values* values, const std::string& value, const char* unit) { values->setAcVoltageC(value, unit); }
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
                T::setValue(_miniSicc._values, std::string(), nullptr);
            }
            else
            {
                std::uint64_t t = 0;
                bool minus = false;

                switch (T::address.type())
                {
                    case catta::modbus::si::RegisterType::sint16():
                    {
                        if (!r.type().isValue16()) return T::setValue(_miniSicc._values, std::string(), nullptr);
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
                        if (!r.type().isValue16()) return T::setValue(_miniSicc._values, std::string(), nullptr);
                        t = r.value16Value();
                        break;
                    case catta::modbus::si::RegisterType::uint32():
                        if (!r.type().isValue32()) return T::setValue(_miniSicc._values, std::string(), nullptr);
                        t = r.value32Value();
                        break;
                    case catta::modbus::si::RegisterType::uint64():
                        if (!r.type().isValue64()) return T::setValue(_miniSicc._values, std::string(), nullptr);
                        t = r.value64Value();
                        break;
                    default:
                        return T::setValue(_miniSicc._values, std::string(), nullptr);
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
                T::setValue(_miniSicc._values, scaledNumber, T::unit);
            }
        }

      private:
        MiniSicc& _miniSicc;
    };

    ScaledValueCallback<AcCurrent> _acCurrentCallback;
    ScaledValueCallback<AcPower> _acPowerCallback;
    ScaledValueCallback<AcVoltageA> _acVoltageACallback;
    ScaledValueCallback<AcVoltageB> _acVoltageBCallback;
    ScaledValueCallback<AcVoltageC> _acVoltageCCallback;
    ScaledValueCallback<Frequency> _frequencyCallback;
    ScaledValueCallback<PowerFactor> _powerFactorCallback;
    ScaledValueCallback<EnergyProduction> _energyProductionCallback;
    ScaledValueCallback<DcVoltage> _dcVoltageCallback;
    ScaledValueCallback<DcPower> _dcPowerCallback;
    ScaledValueCallback<Temperature> _temperatureCallback;

    class PmaxCallback
    {
      public:
        PmaxCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                return _miniSicc._values->setPmax("", nullptr);
            else
                _miniSicc._values->setPmax(std::to_string(r.value16Value() / 10) + "." + std::to_string(r.value16Value() % 10), "W");
        }

      private:
        MiniSicc& _miniSicc;
    } _pmaxCallback;

    class NightShutdownCallback
    {
      public:
        NightShutdownCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                return _miniSicc._values->setTnightoff("", nullptr);
            else
                _miniSicc._values->setTnightoff(std::to_string(r.value16Value()), "s");
        }

      private:
        MiniSicc& _miniSicc;
    } _nightShutdownCallback;

    class StartCountdownCallback
    {
      public:
        StartCountdownCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                return _miniSicc._values->setStartdelay("", nullptr);
            else
                _miniSicc._values->setStartdelay(std::to_string(r.value16Value()), "s");
        }

      private:
        MiniSicc& _miniSicc;
    } _startCountdownCallback;

    class UptimeCallback
    {
      public:
        UptimeCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue32())
                return _miniSicc._values->setTime("");
            else
            {
                std::string t = "__h:__m:__s";
                const std::uint32_t v = r.value32Value();
                const auto set = [&t, v](const std::size_t index, const std::uint32_t factor, const std::uint32_t mod)
                { t[index] = static_cast<char>('0' + ((v % mod) / factor) % 10); };
                set(0, 36000, 360000);
                set(1, 3600, 360000);
                set(4, 600, 3600);
                set(5, 60, 3600);
                set(8, 10, 60);
                set(9, 1, 60);
                _miniSicc._values->setTime(t);
            }
        }

      private:
        MiniSicc& _miniSicc;
    } _uptimeCallback;

    class CosphiCallback
    {
      public:
        CosphiCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                return _miniSicc._values->setCosphi("", nullptr);
            else
            {
                const std::uint16_t v = r.value16Value();
                const std::string head = std::to_string(v / 1000);
                const std::string tail = [v]()
                {
                    std::string s = ".000";
                    s[1] = static_cast<char>('0' + (v / 100) % 10);
                    s[2] = static_cast<char>('0' + (v / 10) % 10);
                    s[3] = static_cast<char>('0' + (v / 1) % 10);
                    return s;
                }();
                _miniSicc._values->setCosphi(head + tail, nullptr);
            }
        }

      private:
        MiniSicc& _miniSicc;
    } _cosphiCallback;

    class DacCallback
    {
      public:
        DacCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                return _miniSicc._values->setDac("", nullptr);
            else
                _miniSicc._values->setDac(std::to_string(r.value16Value()), nullptr);
        }

      private:
        MiniSicc& _miniSicc;
    } _dacCallback;

    class Event1Callback
    {
      public:
        Event1Callback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            static constexpr std::optional<bool> empty = std::optional<bool>{};
            if (!r.type().isValue32())
                _miniSicc._values->setLed1(empty);
            else
            {
                const std::uint32_t v = r.value32Value();
                static constexpr std::uint32_t RELAY_OFF = 0x04;
                _miniSicc._values->setLed1(!(v & RELAY_OFF));
            }
        }

      private:
        MiniSicc& _miniSicc;
    } _event1Callback;

    class Event3Callback
    {
      public:
        Event3Callback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            static constexpr std::optional<bool> empty = std::optional<bool>{};
            if (!r.type().isValue32())
                _miniSicc._values->setLed3(empty, empty, empty, empty);
            else
            {
                const std::uint32_t v = r.value32Value();
                static constexpr std::uint32_t UAC_OK = 0x02;
                static constexpr std::uint32_t FREQ_OK = 0x08;
                static constexpr std::uint32_t WR_WORKING = 0x10;
                static constexpr std::uint32_t PMAX_ACTIVE = 0x40;
                _miniSicc._values->setLed3(v & UAC_OK, v & FREQ_OK, v & WR_WORKING, v & PMAX_ACTIVE);
            }
        }

      private:
        MiniSicc& _miniSicc;
    } _event3Callback;

    class OperatingStateCallback
    {
      public:
        OperatingStateCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            const std::uint16_t value = r.type().isValue16() ? r.value16Value() : 0xffff;
            _miniSicc._values->setOperatingState(value);
        }

      private:
        MiniSicc& _miniSicc;
    } _operatingStateCallback;

    class DerTypeCallback
    {
      public:
        DerTypeCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response&) { _miniSicc.handleProtectedTabs(); }

      private:
        MiniSicc& _miniSicc;
    } _derTypeCallbackCallback;

    class ReductionCallback
    {
      public:
        ReductionCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            if (!r.type().isValue16())
                _miniSicc._static->setReduction("");
            else
            {
                const std::uint16_t v = r.value16Value();
                bool started = false;
                std::string date = "    %";
                const auto set = [v, &date, &started](const std::size_t index, const std::uint16_t factor)
                {
                    const char c = static_cast<char>('0' + (v / factor) % 10);
                    if (c == '0' && !started)
                        date[index] = ' ';
                    else
                    {
                        started = true;
                        date[index] = c;
                    }
                };
                set(0, 100);
                set(1, 10);
                started = true;
                set(2, 1);
                _miniSicc._static->setReduction(date);
            }
        }

      private:
        MiniSicc& _miniSicc;
    } _reductionCallback;

    class FactoryValuesCallback
    {
      public:
        FactoryValuesCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            std::string date;
            std::string bom;
            if (r.type().isFactoryValues())
            {
                const std::uint8_t day = r.factoryValuesValue().productionDate().day().value();
                const std::uint8_t month = r.factoryValuesValue().productionDate().month().value();
                const std::uint16_t year = r.factoryValuesValue().productionDate().year().value() + 2000;
                date = "__.__.____";
                const auto set = [&date](const std::size_t i, const auto v, const auto f) { date[i] = static_cast<char>('0' + (v / f) % 10); };
                set(0, day, 10);
                set(1, day, 1);
                set(3, month, 10);
                set(4, month, 1);
                set(6, year, 1000);
                set(7, year, 100);
                set(8, year, 10);
                set(9, year, 1);
                bom = std::to_string(r.factoryValuesValue().hardwareVersion().value());
            }
            _miniSicc._static->setBom(bom);
            _miniSicc._static->setDate(date);
        }

      private:
        MiniSicc& _miniSicc;
    } _factoryValuesCallback;

    class SoftwareVersionCallback
    {
      public:
        SoftwareVersionCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const Response& r)
        {
            const std::string version = r.type().isString16() ? r.string16Value().data().data() : "";
            _miniSicc._static->setVersion(version);
        }

      private:
        MiniSicc& _miniSicc;
    } _softwareVersionCallback;

    class SliderCallback
    {
      public:
        SliderCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const std::chrono::microseconds t)
        {
            const std::chrono::microseconds time = t * 4;
            const std::chrono::microseconds never = std::chrono::microseconds::max();
            const std::chrono::microseconds lockedTime = _miniSicc._passwort->isLocked() ? never : time;
            _miniSicc._cache.setValidTime(CACHE_AC_CURRENT, time);
            _miniSicc._cache.setValidTime(CACHE_AC_POWER, time);
            _miniSicc._cache.setValidTime(CACHE_AC_VOLTAGE_A, time);
            _miniSicc._cache.setValidTime(CACHE_AC_VOLTAGE_B, time);
            _miniSicc._cache.setValidTime(CACHE_AC_VOLTAGE_C, time);
            _miniSicc._cache.setValidTime(CACHE_FREQUENCY, time);
            _miniSicc._cache.setValidTime(CACHE_POWER_FACTOR, lockedTime);
            _miniSicc._cache.setValidTime(CACHE_EVENTS_1, lockedTime);
            _miniSicc._cache.setValidTime(CACHE_EVENTS_3, lockedTime);
            _miniSicc._cache.setValidTime(CACHE_ENERGY_PRODUCTION, time);
            _miniSicc._cache.setValidTime(CACHE_DC_VOLTAGE, time);
            _miniSicc._cache.setValidTime(CACHE_DC_POWER, time);
            _miniSicc._cache.setValidTime(CACHE_TEMPERATURE, time);
            _miniSicc._cache.setValidTime(CACHE_PMAX, time);
            _miniSicc._cache.setValidTime(CACHE_NIGHT_SHUTDOWN, time);
            _miniSicc._cache.setValidTime(CACHE_START_COUNTDOWN, time);
            _miniSicc._cache.setValidTime(CACHE_UPTIME, time);
            _miniSicc._cache.setValidTime(CACHE_COSPHI, time);
            _miniSicc._cache.setValidTime(CACHE_DAC, time);
            _miniSicc._cache.setValidTime(CACHE_VENDOR_OPERATING_STATE, time);
        }

      private:
        MiniSicc& _miniSicc;
    } _sliderCallback;
    class Unlock
    {
      public:
        Unlock(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()()
        {
            _miniSicc._values->unlock();
            _miniSicc._static->unlock();
            _miniSicc._values->triggerSliderCallback();
            _miniSicc.handleProtectedTabs();
        }

      private:
        MiniSicc& _miniSicc;

    } _unlock;
    class Lock
    {
      public:
        Lock(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()()
        {
            _miniSicc._values->lock();
            _miniSicc._static->lock();
            _miniSicc._values->triggerSliderCallback();
            _miniSicc.handleProtectedTabs();
        }

      private:
        MiniSicc& _miniSicc;

    } _lock;
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
    const catta::modbus::si::Type getType() const
    {
        const auto& derType = _cache.getResponse(CACHE_DER_TYPE);
        if (!derType.type().isValue16()) return catta::modbus::si::Type::empty();
        const std::uint16_t value = derType.value16Value();
        if (value == 4) return catta::modbus::si::Type::solar();
        if (value == 82) return catta::modbus::si::Type::battery();
        if (value == 5) return catta::modbus::si::Type::wind();
        return catta::modbus::si::Type::empty();
    };
    void handleProtectedTabs()
    {
        const catta::modbus::si::Type type = getType();
        const bool isLocked = _passwort->isLocked();
        if (!isLocked && type.isBattery())
            _tabs->add(_tab2);
        else
        {
            _tabs->remove(_tab2);
            _battery->stop();
        }
        if (!isLocked && type.isSolar())
            _tabs->add(_tab3);
        else
        {
            _tabs->remove(_tab3);
            _solar->stop();
        }
        if (!isLocked && type.isWind())
            _tabs->add(_tab4);
        else
        {
            _tabs->remove(_tab4);
            _wind->stop();
        }
    }
};
}  // namespace gui
}  // namespace catta
