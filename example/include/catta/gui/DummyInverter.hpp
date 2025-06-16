#pragma once

// gui
#include <catta/gui/Input.hpp>
#include <catta/gui/SiRegister.hpp>
#include <catta/gui/Uart.hpp>

// modbus
#include <catta/modbus/SlaveUart.hpp>

// toformmodbus
#include <catta/frommodbus/modbus/si/request/Request.hpp>
#include <catta/tomodbus/modbus/si/response/Response.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>
#include <catta/tostring/modbus/sunspec/ScaleFactor.hpp>

// fltk
#include <FL/Fl.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Rect.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Terminal.H>

// std
#include <functional>

namespace catta
{
namespace gui
{
/**
 * @brief DummyInverter simulates inverter on Modbus level.
 * @author CattaTech - Maik Urbannek
 */
template <class UART, class TIME>
class DummyInverter : public Fl_Double_Window
{
  private:
    class My_Scroll : public Fl_Scroll
    {
      public:
        static constexpr int SCROLL_WIDTH = 20;
        My_Scroll(int X, int Y, int W, int H, const char* L = nullptr) : Fl_Scroll(X, Y, W, H, L)
        {
            this->scrollbar_size(SCROLL_WIDTH);
            this->type(Fl_Scroll::VERTICAL_ALWAYS);
        }
        void resize(int X, int Y, int W, int H) FL_OVERRIDE
        {
            Fl_Rect* p = bounds();
            Fl_Widget::resize(X, Y, W, H);
            int dx = X - p->x();
            int dw = W - p->w() - SCROLL_WIDTH;
            int dy = Y - p->y();
            int dh = H - p->h();
            if (as_window()) dx = dy = 0;
            p++;

            const int RL = p->x();
            const int RR = RL + p->w();
            const int RT = p->y();
            const int RB = RT + p->h();
            p++;

            Fl_Widget* const* a = array();

            for (int i = children() - 2; i--; p++)
            {
                Fl_Widget* o = *a++;
                int L = p->x();
                int R = L + p->w();
                int T = p->y();
                int B = T + p->h();

                L += dw * (L - RL) / (RR - RL);
                R += dw * (R - RL) / (RR - RL);
                T += dh * (T - RT) / (RB - RT);
                B += dh * (B - RT) / (RB - RT);
                o->resize(L + dx, T + dy, R - L, B - T);
            }
        }
    };

    class SiRegisterGroup : public My_Scroll
    {
      private:
        constexpr static std::size_t SI_REGISTER = catta::modbus::si::RegisterAddress::empty();

      public:
        static constexpr int defaultHeight = SiRegister::defaultHeight * SI_REGISTER;
        static constexpr int defaultWidth = SiRegister::defaultWidth;

        SiRegisterGroup(int X, int Y, int W, int H, const char* L = nullptr)
            : My_Scroll(0, 0, SiRegister::defaultWidth, SiRegister::defaultHeight * 25, L), _siRegister(createSiRegister())
        {
            this->end();
            this->resize(X, Y, W, H);
        }
        ~SiRegisterGroup()
        {
            for (auto e : _siRegister) delete e;
        }
        catta::modbus::si::response::Response handleRequest(const catta::modbus::si::request::Request& request)
        {
            using Response = catta::modbus::si::response::Response;
            using Type = catta::modbus::si::request::Type;
            switch (request.type())
            {
                case Type::readRegister():
                {
                    const auto address = request.readRegisterValue().registerAddress();
                    if (address.isEmpty()) return Response::empty();
                    return _siRegister[address]->handleRequest(request);
                }
                case Type::writeRegister():
                {
                    const auto address = request.writeRegisterValue().registerAddress();
                    if (address.isEmpty()) return Response::empty();
                    return _siRegister[address]->handleRequest(request);
                }
                default:
                    return Response::empty();
            }
        }

      private:
        static std::array<SiRegister*, SI_REGISTER> createSiRegister()
        {
            std::array<SiRegister*, SI_REGISTER> a;
            for (std::size_t i = 0; i < SI_REGISTER; i++)
            {
                using Type = catta::modbus::si::RegisterType;
                using Address = catta::modbus::si::RegisterAddress;
                const auto address = Address(static_cast<std::uint8_t>(i));
                const int X = 0;
                const int Y = static_cast<int>(i * SiRegister::defaultHeight);
                const int W = SiRegister::defaultWidth;
                const int H = SiRegister::defaultHeight;
                switch (address.type())
                {
                    case Type::uint16():
                        a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::ValueU16::create(0));
                        break;
                    case Type::sint16():
                        a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::ValueS16::create(0));
                        break;
                    case Type::scaleFactor():
                        a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::ScaleFactor::create(0));
                        break;
                    case Type::connectedPhase():
                        a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::ConnectedPhase(0));
                        break;
                    case Type::uint32():
                        a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::ValueU32::create(0));
                        break;
                    default:
                        switch (address)
                        {
                            case Address::commonManufacturer():
                                a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::String::create("Manufacturer"));
                                break;
                            case Address::commonModel():
                                a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::String::create("Model"));
                                break;
                            default:
                                a[i] = new SiRegister(X, Y, W, H, address, catta::modbus::sunspec::String::create("SerialNumber"));
                                break;
                        }
                }
            }
            return a;
        }
        std::array<SiRegister*, SI_REGISTER> _siRegister;
    };

    static constexpr int W_NAME = 320;
    static constexpr int W_ACTION = 100;
    static constexpr int W_LINE_NAME = 320;
    static constexpr int W_INPUT = 200;

    template <class T>
    requires requires(std::tuple<Fl_Box*, catta::gui::Input*>* input)
    {
        std::same_as<decltype(T::type), catta::modbus::si::request::Type>;
        std::same_as<decltype(T::lines), std::size_t>;
        {
            T::create()
            } -> std::same_as<std::tuple<Fl_Box*, catta::gui::Input*>*>;
        {
            T::getResponse(input)
            } -> std::same_as<catta::modbus::si::response::Response>;
    }
    class SiRequest : public Fl_Group
    {
      private:
        static constexpr int H = 25;

      public:
        static constexpr int defaultHeight = static_cast<int>(H * (T::lines == 0 ? 1 : T::lines));
        static constexpr int defaultWidth = W_NAME + W_ACTION + W_LINE_NAME + W_INPUT;
        static constexpr int inputWidth = W_INPUT;

        SiRequest(int X, int Y, int W, int H)
            : Fl_Group(0, 0, defaultWidth, defaultHeight, nullptr),
              _nameBox(0, 0, W_NAME, SiRequest::H, catta::modbus::si::request::Type::enumNames[T::type].data()),
              _actionChoice(W_NAME, 0, W_ACTION, SiRequest::H),
              _input(T::create())
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

            static const Fl_Menu_Item actionMenu[] = {menu("respond"),    menu("do nothing"), menu("execption1"), menu("execption2"),
                                                      menu("execption3"), menu("execption4"), menu(nullptr)};

            this->end();
            this->resize(X, Y, W, H);
            this->_actionChoice.menu(actionMenu);
            this->_actionChoice.callback(actioncb, this);
            this->_nameBox.box(FL_UP_BOX);
            for (std::size_t i = 0; i < T::lines; i++)
            {
                std::get<0>(this->_input[i])->box(FL_UP_BOX);
            }
        }
        catta::modbus::si::response::Response handleRequest(const catta::modbus::si::request::Request& request)
        {
            using Response = catta::modbus::si::response::Response;
            if (request.type() != T::type) return Response::empty();

            switch (_actionChoice.value())
            {
                case 0:  // read
                    return T::getResponse(this->_input);
                case 1:  // nothing
                    return Response::empty();
                default:  // execption1…4
                {
                    const auto value = catta::modbus::si::response::ExceptionValue(static_cast<std::uint8_t>(this->_actionChoice.value() - 2));
                    const auto function = request.type();
                    const auto exception = catta::modbus::si::response::Exception::create(value, function);
                    return Response::exception(exception);
                }
            }
        }
        ~SiRequest()
        {
            if (this->_input)
            {
                for (std::size_t i = 0; i < T::lines; i++)
                {
                    delete std::get<0>(this->_input[i]);
                    delete std::get<1>(this->_input[i]);
                }
                delete[] this->_input;
            }
        }

      private:
        Fl_Box _nameBox;
        Fl_Choice _actionChoice;
        std::tuple<Fl_Box*, catta::gui::Input*>* _input;
        static void actioncb(Fl_Widget*, void* object)
        {
            SiRequest* siRequest = static_cast<SiRequest*>(object);
            if (siRequest)
            {
                if (siRequest->_actionChoice.value() == 0)
                    for (std::size_t i = 0; i < T::lines; i++) std::get<1>(siRequest->_input[i])->activate();
                else
                    for (std::size_t i = 0; i < T::lines; i++) std::get<1>(siRequest->_input[i])->deactivate();
            }
        }
    };

    class SiFactoryValues
    {
      private:
        using T0 = catta::modbus::sunspec::ValueU16;
        using T1 = catta::modbus::sunspec::ValueU8<1, 31>;
        using T2 = catta::modbus::sunspec::ValueU8<1, 12>;
        using T3 = catta::modbus::sunspec::ValueU8<0, 99>;
        using T4 = catta::modbus::sunspec::ValueU8<0, 255>;
        using T5 = catta::modbus::sunspec::ValueU8<0, 255>;
        using T6 = catta::modbus::sunspec::ValueU8<0, 255>;

      public:
        static constexpr auto type = catta::modbus::si::request::Type::factoryValues();
        static constexpr std::size_t lines = 7;
        static std::tuple<Fl_Box*, catta::gui::Input*>* create()
        {
            std::tuple<Fl_Box*, catta::gui::Input*>* input = new std::tuple<Fl_Box*, catta::gui::Input*>[lines];
            auto set = [input](const int i, const char* name, const auto inital)
            {
                input[i] = std::tuple<Fl_Box*, catta::gui::Input*>{
                    new Fl_Box(DummyInverter::W_NAME + DummyInverter::W_ACTION, i * 25, DummyInverter::W_LINE_NAME, 25, name),
                    new catta::gui::Input(DummyInverter::W_NAME + DummyInverter::W_ACTION + DummyInverter::W_LINE_NAME, i * 25,
                                          DummyInverter::W_INPUT, 25, inital)};
            };
            set(0, "serialnumber", T0::create(1));
            set(1, "production.day", T1::create(1));
            set(2, "production.month", T2::create(1));
            set(3, "production.year", T3::create(25));
            set(4, "hardwareVersion", T4::create(5));
            set(5, "firmwareVersion", T5::create(6));
            set(6, "bootstrappVersion", T6::create(7));
            return input;
        }
        static catta::modbus::si::response::Response getResponse(std::tuple<Fl_Box*, catta::gui::Input*>* input)
        {
            const auto production = catta::modbus::si::Date::create(std::get<1>(input[1])->value<T1>(), std::get<1>(input[2])->value<T2>(),
                                                                    std::get<1>(input[3])->value<T3>());
            const auto value =
                catta::modbus::si::response::FactoryValues::create(std::get<1>(input[0])->value<T0>(), production, std::get<1>(input[4])->value<T4>(),
                                                                   std::get<1>(input[5])->value<T5>(), std::get<1>(input[6])->value<T6>());
            return catta::modbus::si::response::Response::factoryValues(value);
        }
    };

    class SiReadOperatingData33
    {
      private:
        using T0 = catta::modbus::sunspec::ValueU16;
        using T1 = catta::modbus::sunspec::ValueU8<0, 255>;
        using T2 = catta::modbus::sunspec::ValueU16;
        using T3 = catta::modbus::sunspec::ValueS16;
        using T4 = catta::modbus::si::State;

      public:
        static constexpr auto type = catta::modbus::si::request::Type::readOperatingData33();
        static constexpr std::size_t lines = 5;
        static std::tuple<Fl_Box*, catta::gui::Input*>* create()
        {
            std::tuple<Fl_Box*, catta::gui::Input*>* input = new std::tuple<Fl_Box*, catta::gui::Input*>[lines];
            auto set = [input](const int i, const char* name, const auto inital)
            {
                input[i] = std::tuple<Fl_Box*, catta::gui::Input*>{
                    new Fl_Box(DummyInverter::W_NAME + DummyInverter::W_ACTION, i * 25, DummyInverter::W_LINE_NAME, 25, name),
                    new catta::gui::Input(DummyInverter::W_NAME + DummyInverter::W_ACTION + DummyInverter::W_LINE_NAME, i * 25,
                                          DummyInverter::W_INPUT, 25, inital)};
            };
            set(0, "dcVoltage", T0::create(1));
            set(1, "acVoltage", T1::create(2));
            set(2, "gridFrequency", T2::create(3));
            set(3, "acPower", T3::create(4));
            set(4, "state", T4(0));
            return input;
        }
        static catta::modbus::si::response::Response getResponse(std::tuple<Fl_Box*, catta::gui::Input*>* input)
        {
            const auto value = catta::modbus::si::response::ReadOperatingData33::create(
                std::get<1>(input[0])->value<T0>(), std::get<1>(input[1])->value<T1>(), std::get<1>(input[2])->value<T2>(),
                std::get<1>(input[3])->value<T3>(), std::get<1>(input[4])->value<T4>());
            return catta::modbus::si::response::Response::readOperatingData33(value);
        }
    };

    class SiReadOperatingData3e
    {
      private:
        using T0 = catta::modbus::sunspec::ValueU16;
        using T1 = catta::modbus::si::Type;
        using T2 = catta::modbus::sunspec::ValueU8<1, 10>;
        using T3 = catta::modbus::sunspec::ValueU8<1, 32>;
        using T4 = catta::modbus::sunspec::ValueU8<0, 255>;
        using T5 = catta::modbus::sunspec::ValueU32;
        using T6 = catta::modbus::sunspec::ValueU16;
        using T7 = catta::modbus::sunspec::ValueU32;
        using T8 = catta::modbus::sunspec::ValueU8<0, 3>;
        using T9 = catta::modbus::sunspec::ValueU8<0, 15>;

      public:
        static constexpr auto type = catta::modbus::si::request::Type::readOperatingData3e();
        static constexpr std::size_t lines = 10;
        static std::tuple<Fl_Box*, catta::gui::Input*>* create()
        {
            std::tuple<Fl_Box*, catta::gui::Input*>* input = new std::tuple<Fl_Box*, catta::gui::Input*>[lines];
            auto set = [input](const int i, const char* name, const auto inital)
            {
                input[i] = std::tuple<Fl_Box*, catta::gui::Input*>{
                    new Fl_Box(DummyInverter::W_NAME + DummyInverter::W_ACTION, i * 25, DummyInverter::W_LINE_NAME, 25, name),
                    new catta::gui::Input(DummyInverter::W_NAME + DummyInverter::W_ACTION + DummyInverter::W_LINE_NAME, i * 25,
                                          DummyInverter::W_INPUT, 25, inital)};
            };
            set(0, "serialNumber", T0::create(1));
            set(1, "type", T1(2));
            set(2, "voltageType", T2::create(3));
            set(3, "nominalPower", T3::create(4));
            set(4, "cosphi", T4::create(5));
            set(5, "gridSupplyDailySum", T5::create(6));
            set(6, "powerLimitation", T6::create(7));
            set(7, "operatingHours", T7::create(8));
            set(8, "phase", T8::create(0));
            set(9, "modbusId", T9::create(10));
            return input;
        }
        static catta::modbus::si::response::Response getResponse(std::tuple<Fl_Box*, catta::gui::Input*>* input)
        {
            const auto value = catta::modbus::si::response::ReadOperatingData3e::create(
                std::get<1>(input[0])->value<T0>(), std::get<1>(input[1])->value<T1>(), std::get<1>(input[2])->value<T2>(),
                std::get<1>(input[3])->value<T3>(), std::get<1>(input[4])->value<T4>(), std::get<1>(input[5])->value<T5>(),
                std::get<1>(input[6])->value<T6>(), std::get<1>(input[7])->value<T7>(), std::get<1>(input[8])->value<T8>(),
                std::get<1>(input[9])->value<T9>());
            return catta::modbus::si::response::Response::readOperatingData3e(value);
        }
    };
    template <std::uint8_t TYPE>
    class BoolResponse
    {
      private:
        using T0 = Boolean;

      public:
        static constexpr auto type = catta::modbus::si::request::Type(TYPE);
        static constexpr std::size_t lines = 1;
        static std::tuple<Fl_Box*, catta::gui::Input*>* create()
        {
            std::tuple<Fl_Box*, catta::gui::Input*>* input = new std::tuple<Fl_Box*, catta::gui::Input*>[lines];
            auto set = [input](const int i, const char* name, const auto inital)
            {
                input[i] = std::tuple<Fl_Box*, catta::gui::Input*>{
                    new Fl_Box(DummyInverter::W_NAME + DummyInverter::W_ACTION, i * 25, DummyInverter::W_LINE_NAME, 25, name),
                    new catta::gui::Input(DummyInverter::W_NAME + DummyInverter::W_ACTION + DummyInverter::W_LINE_NAME, i * 25,
                                          DummyInverter::W_INPUT, 25, inital)};
            };
            set(0, "result", Boolean(true));
            return input;
        }
        static catta::modbus::si::response::Response getResponse(std::tuple<Fl_Box*, catta::gui::Input*>* input)
        {
            using Type = catta::modbus::si::request::Type;
            using Response = catta::modbus::si::response::Response;
            const auto value = [input]() { return std::get<1>(input[0])->value<T0>().value(); };
            switch (type)
            {
                case Type::switchOffGridRelay():
                    return Response::switchOffGridRelay(value());
                case Type::switchOnGridRelay():
                    return Response::switchOnGridRelay(value());
                case Type::forceIdle():
                    return Response::forceIdle(value());
                case Type::deactivateIdle():
                    return Response::deactivateIdle(value());
                case Type::startConstantVoltage():
                    return Response::startConstantVoltage(value());
                case Type::endConstantVoltage():
                    return Response::endConstantVoltage(value());
                case Type::setPowerFactor():
                    return Response::setPowerFactor(value());
                case Type::controlBatteryInvert():
                    return Response::controlBatteryInvert(value());
                case Type::limitBatteryInvert():
                    return Response::limitBatteryInvert(value());
                default:
                    return Response::empty();
            }
        }
    };

    class SiReadError
    {
      public:
        static constexpr auto type = catta::modbus::si::request::Type::readError();
        static constexpr std::size_t lines = 20;
        static std::tuple<Fl_Box*, catta::gui::Input*>* create()
        {
            using T = catta::modbus::sunspec::ValueU16;
            std::tuple<Fl_Box*, catta::gui::Input*>* input = new std::tuple<Fl_Box*, catta::gui::Input*>[lines];
            auto set = [input](const int i, const char* name, const auto inital)
            {
                input[i] = std::tuple<Fl_Box*, catta::gui::Input*>{
                    new Fl_Box(DummyInverter::W_NAME + DummyInverter::W_ACTION, i * 25, DummyInverter::W_LINE_NAME, 25, name),
                    new catta::gui::Input(DummyInverter::W_NAME + DummyInverter::W_ACTION + DummyInverter::W_LINE_NAME, i * 25,
                                          DummyInverter::W_INPUT, 25, inital)};
            };
            set(0, "overVoltageAC", T::create(1));
            set(1, "underVoltageAC", T::create(2));
            set(2, "overVoltageDC", T::create(3));
            set(3, "underVoltageDC", T::create(4));
            set(4, "overFrequency", T::create(5));
            set(5, "underFrequency", T::create(6));
            set(6, "limitedPowerT1", T::create(7));
            set(7, "limitedPowerT2", T::create(8));
            set(8, "limitedPowerT3", T::create(9));
            set(9, "limitedPowerT4", T::create(10));
            set(10, "limitedPowerT5", T::create(11));
            set(11, "com", T::create(12));
            set(12, "islandGrid", T::create(13));
            set(13, "overCurrentInterrupt", T::create(14));
            set(14, "overVoltageInterrupt", T::create(15));
            set(15, "averageGridOverVoltage", T::create(16));
            set(16, "overTempratureShutdown", T::create(17));
            set(17, "differenceGridVoltage", T::create(18));
            set(18, "errorGridRelais", T::create(19));
            set(19, "errorCurrentSensor", T::create(20));
            return input;
        }
        static catta::modbus::si::response::Response getResponse(std::tuple<Fl_Box*, catta::gui::Input*>* input)
        {
            using T = catta::modbus::sunspec::ValueU16;
            const auto value = catta::modbus::si::response::ReadError::create(
                std::get<1>(input[0])->value<T>(), std::get<1>(input[1])->value<T>(), std::get<1>(input[2])->value<T>(),
                std::get<1>(input[3])->value<T>(), std::get<1>(input[4])->value<T>(), std::get<1>(input[5])->value<T>(),
                std::get<1>(input[6])->value<T>(), std::get<1>(input[7])->value<T>(), std::get<1>(input[8])->value<T>(),
                std::get<1>(input[9])->value<T>(), std::get<1>(input[10])->value<T>(), std::get<1>(input[11])->value<T>(),
                std::get<1>(input[12])->value<T>(), std::get<1>(input[13])->value<T>(), std::get<1>(input[14])->value<T>(),
                std::get<1>(input[15])->value<T>(), std::get<1>(input[16])->value<T>(), std::get<1>(input[17])->value<T>(),
                std::get<1>(input[18])->value<T>(), std::get<1>(input[19])->value<T>());
            return catta::modbus::si::response::Response::readError(value);
        }
    };

  public:
    /**
     * @param[in] defaultUartName The name of the widget.
     * Constructor.
     */
    DummyInverter(const char* defaultUartName)
        : Fl_Double_Window(200, 200, SiRegisterGroup::defaultWidth + 50 + 10, SiRegister::defaultHeight * 25 + 50 + 35 + 10 + 150 + 25,
                           "DummyInverter"),
          _run(true),
          _debugChoice(0, SiRegister::defaultHeight * 25 + 50 + 35 + 10, SiRegisterGroup::defaultWidth + 50 + 10, 25),
          _terminal(0, SiRegister::defaultHeight * 25 + 50 + 35 + 10 + 25, SiRegisterGroup::defaultWidth + 50 + 10, 150)
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

        this->_tabs = new Fl_Tabs(25, 25, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 35 + 10);

        Fl_Group* g0 = new Fl_Group(25, 60, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 10, "Connection");
        this->_uart = new Uart<UART>(25 + 5, 60 + 5, SiRegisterGroup::defaultWidth, SiRegister::defaultHeight * 25, defaultUartName);
        g0->end();

        Fl_Group* g1 = new Fl_Group(25, 60, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 10, "Register");
        this->_siRegisterGroup = new SiRegisterGroup(25 + 5, 60 + 5, SiRegisterGroup::defaultWidth, SiRegister::defaultHeight * 25);
        g1->end();

        Fl_Group* g2 = new Fl_Group(25, 60, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 10, "FunctionCodes1");
        this->_siFactoryValues = new FactoryValues(25 + 5, 60 + 5, FactoryValues::defaultWidth, FactoryValues::defaultHeight);
        g2->end();

        Fl_Group* g3 = new Fl_Group(25, 60, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 10, "FunctionCodes2");

        int height = 0;
        this->_siReadOperatingData33 = new Operating33(25 + 5, 60 + 5 + height, Operating33::defaultWidth, Operating33::defaultHeight);
        height += Operating33::defaultHeight;
        this->_siReadOperatingData3e = new Operating3e(25 + 5, 60 + 5 + height, Operating3e::defaultWidth, Operating3e::defaultHeight);
        height += Operating3e::defaultHeight;
        this->_siSwitchOffGridRelay =
            new SwitchOffGridRelay(25 + 5, 60 + 5 + height, SwitchOffGridRelay::defaultWidth, SwitchOffGridRelay::defaultHeight);
        height += SwitchOffGridRelay::defaultHeight;
        this->_siSwitchOnGridRelay =
            new SwitchOnGridRelay(25 + 5, 60 + 5 + height, SwitchOnGridRelay::defaultWidth, SwitchOnGridRelay::defaultHeight);
        height += SwitchOnGridRelay::defaultHeight;
        this->_siForceIdle = new ForceIdle(25 + 5, 60 + 5 + height, ForceIdle::defaultWidth, ForceIdle::defaultHeight);
        height += ForceIdle::defaultHeight;
        this->_siDeactivateIdle = new DeactivateIdle(25 + 5, 60 + 5 + height, DeactivateIdle::defaultWidth, DeactivateIdle::defaultHeight);
        height += DeactivateIdle::defaultHeight;
        this->_siStartConstantVoltage =
            new StartConstantVoltage(25 + 5, 60 + 5 + height, StartConstantVoltage::defaultWidth, StartConstantVoltage::defaultHeight);
        height += StartConstantVoltage::defaultHeight;
        this->_siEndConstantVoltage =
            new EndConstantVoltage(25 + 5, 60 + 5 + height, EndConstantVoltage::defaultWidth, EndConstantVoltage::defaultHeight);
        height += EndConstantVoltage::defaultHeight;
        this->_siSetPowerFactor = new SetPowerFactor(25 + 5, 60 + 5 + height, SetPowerFactor::defaultWidth, SetPowerFactor::defaultHeight);
        height += SetPowerFactor::defaultHeight;
        this->_siControlBatteryInvert =
            new ControlBatteryInvert(25 + 5, 60 + 5 + height, ControlBatteryInvert::defaultWidth, ControlBatteryInvert::defaultHeight);
        height += ControlBatteryInvert::defaultHeight;
        this->_siLimitBatteryInvert =
            new LimitBatteryInvert(25 + 5, 60 + 5 + height, LimitBatteryInvert::defaultWidth, LimitBatteryInvert::defaultHeight);
        height += LimitBatteryInvert::defaultHeight;
        g3->end();

        Fl_Group* g4 = new Fl_Group(25, 60, SiRegisterGroup::defaultWidth + 10, SiRegister::defaultHeight * 25 + 10, "FunctionCodes3");
        this->_siReadError = new ReadError(25 + 5, 60 + 5, ReadError::defaultWidth, ReadError::defaultHeight);
        g4->end();

        this->_tabs->end();

        static const Fl_Menu_Item debugMenu[] = {menu("Info"), menu("Debug"), menu("Verbose"), menu(nullptr)};

        this->_debugChoice.menu(debugMenu);

        this->resizable(_siRegisterGroup);
        this->end();
        this->callback(close_cb);
        this->show();
    }
    /**
     * Runs dummy inverter simulation window. Blocks until the window is closed.
     */
    void run()
    {
        using namespace std::chrono_literals;
        auto modbus = catta::modbus::SlaveUart();

        catta::frommodbus::Parser<catta::modbus::si::request::Request> parser;
        catta::tomodbus::Serializer<catta::modbus::si::response::Response> serializer;

        catta::modbus::SlaveUartState state;

        std::optional<std::uint8_t> receivedByte = {};
        std::optional<std::uint8_t> sendByte = {};
        catta::modbus::Token sendToken = {};
        catta::modbus::Token receiveToken = {};

        std::vector<std::uint8_t> sendLine;
        std::vector<std::uint8_t> receiveLine;

        const auto printLine = [](const std::vector<std::uint8_t>& vec)
        {
            std::string s;
            for (std::size_t i = 0; i < vec.size(); i++)
            {
                s += catta::tostring::toString(catta::Hexadecimal(vec[i]));
                if (i + 1 < vec.size()) s += ':';
            }
            return s;
        };

        catta::modbus::si::response::Response response = {};

        while (this->_run)
        {
            const bool isDebug = this->_debugChoice.value() > 0;
            const bool isVerbose = this->_debugChoice.value() > 1;

            const auto now = TIME::get();
            bool somethingHappend = false;

            const auto terminal = [this](const std::string& s) { this->_terminal.printf(s.c_str()); };

            const auto debugLog = [now, terminal, isVerbose](const std::string s)
            {
                if (isVerbose) terminal(printTimestamp(now) + ' ');
                terminal(s);
            };

            if (!sendByte && receiveToken.isEmpty())
            {
                const auto [modbusState, recevieTokenLocal, sendByteLocal, sendHandled] = modbus.work(now, receivedByte, sendToken);
                if (isVerbose && state != modbusState)
                {
                    debugLog("[Modbus::Uart::State] " + catta::tostring::toString(modbusState) + '\n');
                    state = modbusState;
                }
                if (isDebug && sendByteLocal) sendLine.push_back(sendByteLocal.value());
                if (isDebug && sendHandled && sendToken.type().isEnd())
                {
                    debugLog("Send: " + printLine(sendLine) + '\n');
                    sendLine = {};
                }
                if (sendHandled) sendToken = {};
                receivedByte = {};
                sendByte = sendByteLocal;

                receiveToken = recevieTokenLocal;
                if (sendByte || !receiveToken.isEmpty()) somethingHappend = true;
            }
            if (sendByte)
                if (_uart->write(static_cast<char>(sendByte.value())))
                {
                    if (isVerbose) debugLog("send: " + catta::tostring::toString(catta::Hexadecimal(sendByte.value())) + '\n');
                    sendByte = {};
                    somethingHappend = true;
                }
            if (!receivedByte)
            {
                const auto result = this->_uart->read();
                if (result)
                {
                    receiveLine.push_back(static_cast<std::uint8_t>(result.value()));
                    receivedByte = result;
                    somethingHappend = true;
                    if (isVerbose) debugLog("receive: " + catta::tostring::toString(catta::Hexadecimal(result.value())) + '\n');
                }
            }

            if (!receiveToken.isEmpty())
            {
                const auto [error, handled] = parser.read(receiveToken);
                if (handled) receiveToken = {};
                if (parser.state().isDone())
                {
                    const std::uint8_t id = modbus.modbusId();
                    const auto request = parser.data();
                    if (_uart->id() == id)
                        handleRequest(request, response);
                    else
                        modbus = {};
                    if (isDebug)
                    {
                        debugLog("Received Bytes: " + printLine(receiveLine) + '\n');
                        receiveLine = {};
                        debugLog("Received[" + catta::tostring::toString(catta::Hexadecimal(id)) + "]: ");
                    }
                    terminal(catta::tostring::toString(request) + '\n');
                    parser = {};
                }
                if (parser.state().isFailed())
                {
                    if (isDebug)
                    {
                        debugLog("Parsing error: " + printLine(receiveLine) + '\n');
                        receiveLine = {};
                    }
                    parser = {};
                }
                somethingHappend = true;
            }

            if (!response.isEmpty() && sendToken.isEmpty())
            {
                somethingHappend = true;
                [[maybe_unused]] const auto ignore = serializer.read(response);
                sendToken = serializer.data();
                if (serializer.state().isDone())
                {
                    serializer = {};
                    if (isDebug) debugLog("Send: " + catta::tostring::toString(response) + '\n');
                    response = {};
                }
                if (serializer.state().isFailed())
                {
                    if (isDebug)
                    {
                        debugLog("Serializing error: " + printLine(sendLine) + '\n');
                        debugLog(catta::tostring::toString(response) + '\n');
                        sendLine = {};
                    }
                    serializer = {};
                }
            }

            if (!somethingHappend) Fl::wait(0);
        }
    }

  private:
    using Operating33 = SiRequest<SiReadOperatingData33>;
    using Operating3e = SiRequest<SiReadOperatingData3e>;
    using SwitchOffGridRelay = SiRequest<BoolResponse<catta::modbus::si::request::Type::switchOffGridRelay()>>;
    using SwitchOnGridRelay = SiRequest<BoolResponse<catta::modbus::si::request::Type::switchOnGridRelay()>>;
    using ForceIdle = SiRequest<BoolResponse<catta::modbus::si::request::Type::forceIdle()>>;
    using DeactivateIdle = SiRequest<BoolResponse<catta::modbus::si::request::Type::deactivateIdle()>>;
    using StartConstantVoltage = SiRequest<BoolResponse<catta::modbus::si::request::Type::startConstantVoltage()>>;
    using EndConstantVoltage = SiRequest<BoolResponse<catta::modbus::si::request::Type::endConstantVoltage()>>;
    using SetPowerFactor = SiRequest<BoolResponse<catta::modbus::si::request::Type::setPowerFactor()>>;
    using ControlBatteryInvert = SiRequest<BoolResponse<catta::modbus::si::request::Type::controlBatteryInvert()>>;
    using LimitBatteryInvert = SiRequest<BoolResponse<catta::modbus::si::request::Type::limitBatteryInvert()>>;
    using ReadError = SiRequest<SiReadError>;
    using FactoryValues = SiRequest<SiFactoryValues>;

    bool _run;

    Fl_Tabs* _tabs;
    SiRegisterGroup* _siRegisterGroup;
    Operating33* _siReadOperatingData33;
    Operating3e* _siReadOperatingData3e;
    SwitchOffGridRelay* _siSwitchOffGridRelay;
    SwitchOnGridRelay* _siSwitchOnGridRelay;
    ForceIdle* _siForceIdle;
    DeactivateIdle* _siDeactivateIdle;
    StartConstantVoltage* _siStartConstantVoltage;
    EndConstantVoltage* _siEndConstantVoltage;
    SetPowerFactor* _siSetPowerFactor;
    ControlBatteryInvert* _siControlBatteryInvert;
    LimitBatteryInvert* _siLimitBatteryInvert;
    ReadError* _siReadError;
    FactoryValues* _siFactoryValues;
    Uart<UART>* _uart;
    Fl_Choice _debugChoice;
    Fl_Terminal _terminal;

    static void close_cb(Fl_Widget* widget, void*)
    {
        DummyInverter* self = dynamic_cast<DummyInverter*>(widget);
        if (self) self->_run = false;
    }

    void handleRequest(const catta::modbus::si::request::Request& request, catta::modbus::si::response::Response& response)
    {
        using Type = catta::modbus::si::request::Type;
        switch (request.type())
        {
            case Type::readRegister():
            case Type::writeRegister():
                response = _siRegisterGroup->handleRequest(request);
                break;
            case Type::factoryValues():
                response = _siFactoryValues->handleRequest(request);
                break;
            case Type::readOperatingData33():
                response = _siReadOperatingData33->handleRequest(request);
                break;
            case Type::readOperatingData3e():
                response = _siReadOperatingData3e->handleRequest(request);
                break;
            case Type::switchOffGridRelay():
                response = _siSwitchOffGridRelay->handleRequest(request);
                break;
            case Type::switchOnGridRelay():
                response = _siSwitchOnGridRelay->handleRequest(request);
                break;
            case Type::forceIdle():
                response = _siForceIdle->handleRequest(request);
                break;
            case Type::deactivateIdle():
                response = _siDeactivateIdle->handleRequest(request);
                break;
            case Type::startConstantVoltage():
                response = _siStartConstantVoltage->handleRequest(request);
                break;
            case Type::endConstantVoltage():
                response = _siEndConstantVoltage->handleRequest(request);
                break;
            case Type::setPowerFactor():
                response = _siSetPowerFactor->handleRequest(request);
                break;
            case Type::controlBatteryInvert():
                response = _siControlBatteryInvert->handleRequest(request);
                break;
            case Type::limitBatteryInvert():
                response = _siLimitBatteryInvert->handleRequest(request);
                break;
            case Type::readError():
                response = _siReadError->handleRequest(request);
                break;
            default:
                break;
        }
    }
    static std::string printTimestamp(const std::chrono::microseconds t)
    {
        std::string r = "00.00.0000-00:00:00-000:000";
        using namespace std::chrono;
        std::chrono::time_point<system_clock, microseconds> tp = std::chrono::time_point<system_clock, microseconds>(t);
        auto dp = floor<days>(tp);
        year_month_day ymd{dp};
        hh_mm_ss time{floor<microseconds>(tp - dp)};
        auto y = ymd.year();
        auto m = static_cast<unsigned>(ymd.month());
        auto d = static_cast<unsigned>(ymd.day());
        auto h = time.hours().count();
        auto M = time.minutes().count();
        auto s = time.seconds().count();
        auto ss = time.subseconds().count();
        const auto set = [&r](const auto source, const auto factor, const std::size_t index)
        { r[index] = static_cast<char>((static_cast<int>(source) / factor) % 10 + '0'); };
        set(d, 10, 0);
        set(d, 1, 1);
        set(m, 10, 3);
        set(m, 1, 4);
        set(y, 1000, 6);
        set(y, 100, 7);
        set(y, 10, 8);
        set(y, 1, 9);
        set(h, 10, 11);
        set(h, 1, 12);
        set(M, 10, 14);
        set(M, 1, 15);
        set(s, 10, 17);
        set(s, 1, 18);
        set(ss, 100 * 1000, 20);
        set(ss, 10 * 1000, 21);
        set(ss, 1 * 1000, 22);
        set(ss, 100, 24);
        set(ss, 10, 25);
        set(ss, 1, 26);
        return r;
    }
};
}  // namespace gui
}  // namespace catta
