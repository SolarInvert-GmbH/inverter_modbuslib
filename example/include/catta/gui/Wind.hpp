#pragma once

// gui
#include <catta/gui/Curve.hpp>

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
 * @brief Wind shows wind config.
 * @author CattaTech - Maik Urbannek
 */
class Wind : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Wind(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
    {
        static constexpr std::array<const char*, ROBIN_SIZE + 1> LABEL = {"U_Sol_CV", "U_DC_START", "U_DC_HIGH", "P_MAX",   "Z_PT1WINDUSOL",
                                                                          "X 00…07",  "X 08…15",    "Y 00…07",   "Y 08…15", "WIND_CURVE"};
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 45;
        static const int W_REST = 20 + GAP * 5;
        static const int W2 = W / 2 - W_REST;
        static const int W_LABEL = W2 / 3;
        static const int W_WRITE = W2 / 3;
        static const int W_SEND = W2 / 3;
        static const int X0 = X + 20;
        static const int X1 = X0 + W_LABEL + GAP;
        static const int X2 = X1 + W_WRITE + GAP * 4;
        static const int X3 = X2 + 20 + W_SEND;
        static const int X4 = X3 + W_LABEL + GAP;
        static const int X5 = X4 + W_WRITE + GAP * 4;
        using Address = catta::modbus::si::RegisterAddress;
        static constexpr auto uSolCvReadAddress = Address::siControlBattaryCvModeRead();
        static constexpr auto uSolCvWriteAddress = Address::siControlBattaryCvModeWrite();
        static constexpr auto dcStartReadAddress = Address::siControlVoltageDcStartRead();
        static constexpr auto dcStartWriteAddress = Address::siControlVoltageDcStartWrite();
        static constexpr auto dcHighReadAddress = Address::siControlDcHighRead();
        static constexpr auto dcHighWriteAddress = Address::siControlDcHighWrite();
        static constexpr auto pMaxAddress = Address::basicSettingsMaxPower();
        static constexpr auto zPt1WindUsolAddress = Address::siControlFilterWindCurve();

        static constexpr std::array<std::array<Address, 8>, CURVES> curveAddressRead = {
            std::array<Address, 8>{Address::siControlWindCurveX00(), Address::siControlWindCurveX01(), Address::siControlWindCurveX02(),
                                   Address::siControlWindCurveX03(), Address::siControlWindCurveX04(), Address::siControlWindCurveX05(),
                                   Address::siControlWindCurveX06(), Address::siControlWindCurveX07()},
            std::array<Address, 8>{Address::siControlWindCurveX08(), Address::siControlWindCurveX09(), Address::siControlWindCurveX10(),
                                   Address::siControlWindCurveX11(), Address::siControlWindCurveX12(), Address::siControlWindCurveX13(),
                                   Address::siControlWindCurveX14(), Address::siControlWindCurveX15()},
            std::array<Address, 8>{Address::siControlWindCurveY00Read(), Address::siControlWindCurveY01Read(), Address::siControlWindCurveY02Read(),
                                   Address::siControlWindCurveY03Read(), Address::siControlWindCurveY04Read(), Address::siControlWindCurveY05Read(),
                                   Address::siControlWindCurveY06Read(), Address::siControlWindCurveY07Read()},
            std::array<Address, 8>{Address::siControlWindCurveY08Read(), Address::siControlWindCurveY09Read(), Address::siControlWindCurveY10Read(),
                                   Address::siControlWindCurveY11Read(), Address::siControlWindCurveY12Read(), Address::siControlWindCurveY13Read(),
                                   Address::siControlWindCurveY14Read(), Address::siControlWindCurveY15Read()}};

        static constexpr std::array<std::array<Address, 8>, CURVES> curveAddressWrite = {
            std::array<Address, 8>{Address::siControlWindCurveX00(), Address::siControlWindCurveX01(), Address::siControlWindCurveX02(),
                                   Address::siControlWindCurveX03(), Address::siControlWindCurveX04(), Address::siControlWindCurveX05(),
                                   Address::siControlWindCurveX06(), Address::siControlWindCurveX07()},
            std::array<Address, 8>{Address::siControlWindCurveX08(), Address::siControlWindCurveX09(), Address::siControlWindCurveX10(),
                                   Address::siControlWindCurveX11(), Address::siControlWindCurveX12(), Address::siControlWindCurveX13(),
                                   Address::siControlWindCurveX14(), Address::siControlWindCurveX15()},
            std::array<Address, 8>{Address::siControlWindCurveY00Write(), Address::siControlWindCurveY01Write(),
                                   Address::siControlWindCurveY02Write(), Address::siControlWindCurveY03Write(),
                                   Address::siControlWindCurveY04Write(), Address::siControlWindCurveY05Write(),
                                   Address::siControlWindCurveY06Write(), Address::siControlWindCurveY07Write()},
            std::array<Address, 8>{Address::siControlWindCurveY08Write(), Address::siControlWindCurveY09Write(),
                                   Address::siControlWindCurveY10Write(), Address::siControlWindCurveY11Write(),
                                   Address::siControlWindCurveY12Write(), Address::siControlWindCurveY13Write(),
                                   Address::siControlWindCurveY14Write(), Address::siControlWindCurveY15Write()}};

        static std::array<std::tuple<std::size_t, Wind*>, ROBIN_SIZE> cbArray;
        for (std::size_t i = 0; i < SIZE; i++)
        {
            cbArray[i] = std::tuple<std::size_t, Wind*>{i, this};
            _label[i] = new Fl_Box(i % 2 == 0 ? X0 : X3, Y + H_LINE * int(i / 2 + 1), W_LABEL, H_LINE, LABEL[i]);
            _label[i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _button[i] = new Fl_Button(i % 2 == 0 ? X2 : X5, Y + H_LINE * int(i / 2 + 1), W_SEND, H_LINE, "Send");
            _button[i]->hide();
            _button[i]->callback(writeCb, &cbArray[i]);
        }
        _write[U_SOL_CV] = new Write(U_SOL_CV % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_SOL_CV) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                     0.01, uSolCvReadAddress, uSolCvWriteAddress, _toRegisterCenti, _fromRegisterCenti);

        _write[U_DC_START] = new Write(U_DC_START % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_DC_START) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                       655.00, 0.01, dcStartReadAddress, dcStartWriteAddress, _toRegisterCenti, _fromRegisterCenti);

        _write[U_DC_HIGH] = new Write(U_DC_HIGH % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_DC_HIGH) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                      655.00, 0.01, dcHighReadAddress, dcHighWriteAddress, _toRegisterCenti, _fromRegisterCenti);

        _write[P_MAX] = new Write(P_MAX % 2 == 0 ? X1 : X4, Y + H_LINE * (int(P_MAX) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.1, 6550.0, 0.1,
                                  pMaxAddress, pMaxAddress, _toRegisterDeci, _fromRegisterDeci);

        _write[Z_PT1WINDUSOL] =
            new Write(Z_PT1WINDUSOL % 2 == 0 ? X1 : X4, Y + H_LINE * (int(Z_PT1WINDUSOL) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.1, 25.5, 0.1,
                      zPt1WindUsolAddress, zPt1WindUsolAddress, _toRegisterDeci, _fromRegisterDeci);
        _label[ROBIN_SIZE] = new Fl_Box(X, Y + H_LINE * 4, W, H_LINE, LABEL[ROBIN_SIZE]);
        for (std::size_t i = 0; i < CURVES; i++)
        {
            cbArray[i + SIZE] = std::tuple<std::size_t, Wind*>{i + SIZE, this};
            const int y = Y + H_LINE * (int(i) + 5);
            const int W_LABEL_CURVE = (W_LABEL * 7) / 10;
            const int W_SEND_CURVE = (W_SEND * 5) / 10;
            const int W_CURVE = W - W_LABEL_CURVE - W_SEND_CURVE;
            const int X0 = X;
            const int X1 = X0 + W_LABEL_CURVE;
            const int X2 = X1 + W_CURVE;
            _label[SIZE + i] = new Fl_Box(X0, y, W_LABEL_CURVE, H_LINE, LABEL[SIZE + i]);
            _label[SIZE + i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _curve[i] = new Curve<8>(X1, y, W_CURVE, H_LINE, FL_INT_INPUT, 0.0, 256.0, 1.0, curveAddressRead[i], curveAddressWrite[i], _toRegister256,
                                     _fromRegister256);
            _button[SIZE + i] = new Fl_Button(X2, y, W_SEND_CURVE, H_LINE, "Send");
            _button[SIZE + i]->hide();
            _button[SIZE + i]->callback(writeCb, &cbArray[i + SIZE]);
        }
        this->end();
    }
    /**
     * Destructor.
     */
    ~Wind() {}
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request)
    {
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < ROBIN_SIZE; i++)
        {
            std::size_t j = (_roundRobin + i) % ROBIN_SIZE;
            const catta::modbus::si::request::Request r = j < SIZE ? _write[j]->work(canTakeRequest && send.isEmpty(), response, request)
                                                                   : _curve[j - SIZE]->work(canTakeRequest && send.isEmpty(), response, request);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % ROBIN_SIZE;
            }
            if (j < SIZE)
            {
                if (_write[j]->getState() == Write::STATE_IDLE && _write[j]->isChanged())
                    _button[j]->show();
                else
                    _button[j]->hide();
            }
            else
            {
                if (_curve[j - SIZE]->allIdleAndAtLeastOneDiffernt())
                    _button[j]->show();
                else
                    _button[j]->hide();
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }

  private:
    static constexpr std::size_t U_SOL_CV = 0;
    static constexpr std::size_t U_DC_START = U_SOL_CV + 1;
    static constexpr std::size_t U_DC_HIGH = U_DC_START + 1;
    static constexpr std::size_t P_MAX = U_DC_HIGH + 1;
    static constexpr std::size_t Z_PT1WINDUSOL = P_MAX + 1;
    static constexpr std::size_t SIZE = Z_PT1WINDUSOL + 1;

    static constexpr std::size_t X_PAC_0 = 0;
    static constexpr std::size_t X_PAC_1 = X_PAC_0 + 1;
    static constexpr std::size_t Y_U_SOL_0 = X_PAC_1 + 1;
    static constexpr std::size_t Y_U_SOL_1 = Y_U_SOL_0 + 1;
    static constexpr std::size_t CURVES = Y_U_SOL_1 + 1;

    static constexpr std::size_t ROBIN_SIZE = SIZE + CURVES;

    std::array<Fl_Box*, ROBIN_SIZE + 1> _label;
    std::array<Write*, SIZE> _write;
    std::array<Fl_Button*, ROBIN_SIZE> _button;
    std::array<Curve<8>*, CURVES> _curve;
    std::size_t _roundRobin;
    class ToRegisterCenti
    {
      public:
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input * 100.0); }

      private:
    } _toRegisterCenti;
    class FromRegisterCenti
    {
      public:
        double operator()(const std::uint16_t input) { return static_cast<double>(input) / 100.0; }

      private:
    } _fromRegisterCenti;

    class ToRegisterDeci
    {
      public:
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input * 10.0); }

      private:
    } _toRegisterDeci;
    class FromRegisterDeci
    {
      public:
        double operator()(const std::uint16_t input) { return static_cast<double>(input) / 10.0; }

      private:
    } _fromRegisterDeci;

    class ToRegister256
    {
      public:
        std::uint16_t operator()(const double input) { return static_cast<std::uint16_t>(input); }
    } _toRegister256;
    class FromRegister256
    {
      public:
        double operator()(const std::uint16_t input) { return static_cast<double>(input); }
    } _fromRegister256;

    static void writeCb(Fl_Widget*, void* object)
    {
        std::tuple<std::size_t, Wind*>* tuple = static_cast<std::tuple<std::size_t, Wind*>*>(object);
        if (tuple == nullptr) return;
        const std::size_t index = std::get<0>(*tuple);
        Wind* wind = std::get<1>(*tuple);
        if (wind == nullptr) return;
        if (index < SIZE)
            wind->_write[index]->write();
        else if (index < SIZE + CURVES)
            wind->_curve[index - SIZE]->write();
    }
};
}  // namespace gui
}  // namespace catta
