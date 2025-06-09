#pragma once

// gui
#include <catta/gui/Connection.hpp>
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
    MiniSicc(const char* defaultUartName)
        : Fl_Double_Window(200, 200, WIDTH, HEIGHT, "miniSICC"), _run(true), _current(CLIENTS), _temperatureCallback(*this), _sliderCallback(*this)
    {
        this->_connection = new Connection<UART>(10, 10, WIDTH - 20, 130, defaultUartName, nullptr, CLIENTS);
        this->_tabs = new Fl_Tabs(10, 150, WIDTH - 20, HEIGHT - 160);
        Fl_Group* g0 = new Fl_Group(10, 180, WIDTH - 20, HEIGHT - 185, "Values");
        this->_values = new Values(15, 190, WIDTH - 30, HEIGHT - 195);
        g0->end();
        this->resizable(this->_tabs);
        this->end();
        this->callback(close_cb);
        this->show();
        _cache.setRequest(CACHE_TEMPERATURE_SCALE, REQUEST_TEMPERATURE_SCALE);
        _cache.setRequest(CACHE_TEMPERATURE, REQUEST_TEMPERATURE);
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
            Fl::wait(0);
            if (!somethingHappend) TIME::sleep(10us);
        }
    }

  private:
    static constexpr std::size_t CLIENT_CACHE = 0;
    static constexpr std::size_t CLIENTS = CLIENT_CACHE + 1;

    static constexpr std::size_t CACHE_TEMPERATURE_SCALE = 0;
    static constexpr std::size_t CACHE_TEMPERATURE = CACHE_TEMPERATURE_SCALE + 1;
    static constexpr std::size_t CACHE_SIZE = CACHE_TEMPERATURE + 1;

    using Request = catta::modbus::si::request::Request;
    using Response = catta::modbus::si::response::Response;
    using ReadRegister = catta::modbus::si::ReadRegister;
    using RegisterAddress = catta::modbus::si::RegisterAddress;

    bool _run;

    Connection<UART>* _connection;
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

    static constexpr Request REQUEST_TEMPERATURE_SCALE =
        Request::readRegister(ReadRegister::create(RegisterAddress::inverterTemperatureScaleFactor()));
    static constexpr Request REQUEST_TEMPERATURE = Request::readRegister(ReadRegister::create(RegisterAddress::inverterTemperature()));

    class Temperature
    {
      public:
        static constexpr const char* unit = "°C";
        static constexpr std::size_t cacheScale = CACHE_TEMPERATURE_SCALE;
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
                if (r.type().isValue16())
                {
                    const std::int16_t t = static_cast<std::int16_t>(r.value16Value());
                    const std::string scaledNumber = [scale, t]()
                    {
                        if (scale == 0) return std::to_string(t);
                        if (scale > 0) return std::to_string(t) + std::string(static_cast<std::size_t>(scale), '0');
                        const std::uint32_t factor = [scale]()
                        {
                            std::uint32_t result = 1;
                            for (std::int16_t i = 0; i > scale; i--) result = result * 10;
                            return result;
                        }();
                        std::string result;
                        std::uint32_t number;
                        if (t < 0)
                        {
                            number = static_cast<std::uint32_t>(-t);
                            result += '-';
                        }
                        else
                            number = static_cast<std::uint32_t>(t);
                        result += std::to_string(number / factor);
                        result += '.';
                        for (std::uint32_t i = factor / 10; i > 0; i = i / 10) result += static_cast<char>('0' + (number / i) % 10);
                        return result;
                    }();
                    T::setValue(_miniSicc._values, scaledNumber + ' ' + T::unit);
                }
                else
                    T::setValue(_miniSicc._values, std::string());
            }
        }

      private:
        MiniSicc& _miniSicc;
    };

    ScaledValueCallback<Temperature> _temperatureCallback;

    class SliderCallback
    {
      public:
        SliderCallback(MiniSicc& miniSicc) : _miniSicc(miniSicc) {}
        void operator()(const std::chrono::microseconds t) { _miniSicc._cache.setValidTime(CACHE_TEMPERATURE, t * 4); }

      private:
        MiniSicc& _miniSicc;
    } _sliderCallback;
};
}  // namespace gui
}  // namespace catta
