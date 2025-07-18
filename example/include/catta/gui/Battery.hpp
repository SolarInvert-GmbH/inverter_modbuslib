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
 * @brief Battery shows battery config.
 * @author CattaTech - Maik Urbannek
 */
class Battery : public Fl_Group
{
  public:
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * Constructor.
     */
    Battery(const int X, const int Y, const int W, const int H) : Fl_Group(X, Y, W, H, nullptr)
    {
        static constexpr std::array<const char*, ROBIN_SIZE + 1> LABEL = {
            "U_MIN",         "U_MAX",     "P_MAX",     "U_SOL_CV",     "U_DC_LOW", "U_DC_HIGH", "MODUS", "S_BIOFF", "U_DC_START", "Z_U_SOL_BAT_FILT",
            "U_SOL_BAT_ERR", "U_SOL_BAT", "P_MAX_ERR", "P_MAX_CHARGE", "CV_X",     "CV_Y",      "CURVE"};
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

        static constexpr auto uMinReadAddress = Address::siControlUMinRead();
        static constexpr auto uMinWriteAddress = Address::siControlUMinWrite();
        static constexpr auto uMaxReadAddress = Address::siControlUMaxRead();
        static constexpr auto uMaxWriteAddress = Address::siControlUMaxWrite();
        static constexpr auto pMaxAddress = Address::basicSettingsMaxPower();

        static constexpr auto uSolCvReadAddress = Address::siControlBattaryCvModeRead();
        static constexpr auto uSolCvWriteAddress = Address::siControlBattaryCvModeWrite();
        static constexpr auto dcLowReadAddress = Address::siControlDcLowRead();
        static constexpr auto dcLowWriteAddress = Address::siControlDcLowWrite();
        static constexpr auto dcHighReadAddress = Address::siControlDcHighRead();
        static constexpr auto dcHighWriteAddress = Address::siControlDcHighWrite();

        static constexpr auto modusAddress = Address::siControlModus();
        static constexpr auto sBioOffAddress = catta::modbus::si::RegisterAddress::siControlTrackingSelection();
        static constexpr auto dcStartReadAddress = Address::siControlVoltageDcStartRead();
        static constexpr auto dcStartWriteAddress = Address::siControlVoltageDcStartWrite();

        static constexpr auto zUsolBatFil = Address::siControlSolarBatteryFilterStep();
        static constexpr auto uSolBatErrRead = Address::siControlBattarySaftyModeRead();
        static constexpr auto uSolBatErrWrite = Address::siControlBattarySaftyModeWrite();
        static constexpr auto uSolBatRead = Address::siControlBattaryBiModeRead();
        static constexpr auto uSolBatWrite = Address::siControlBattaryBiModeWrite();

        static constexpr auto pMaxErr = Address::siControlPowerLimitSaftyMode();
        static constexpr auto pMaxCharge = Address::storageNominalChargePower();

        static constexpr std::array<std::array<Address, 3>, CURVES> curveAddressRead = {
            std::array<Address, 3>{Address::siControlConstantVoltageX0(), Address::siControlConstantVoltageX1(),
                                   Address::siControlConstantVoltageX2()},
            std::array<Address, 3>{Address::siControlConstantVoltageY0Read(), Address::siControlConstantVoltageY1Read(),
                                   Address::siControlConstantVoltageY2Read()}};

        static constexpr std::array<std::array<Address, 3>, CURVES> curveAddressWrite = {
            std::array<Address, 3>{Address::siControlConstantVoltageX0(), Address::siControlConstantVoltageX1(),
                                   Address::siControlConstantVoltageX2()},
            std::array<Address, 3>{Address::siControlConstantVoltageY0Write(), Address::siControlConstantVoltageY1Write(),
                                   Address::siControlConstantVoltageY2Write()}};

        static std::array<std::tuple<std::size_t, Battery*>, ROBIN_SIZE> cbArray;
        for (std::size_t i = 0; i < SIZE; i++)
        {
            cbArray[i] = std::tuple<std::size_t, Battery*>{i, this};
            _label[i] = new Fl_Box(i % 2 == 0 ? X0 : X3, Y + H_LINE * int(i / 2 + 1), W_LABEL, H_LINE, LABEL[i]);
            _label[i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _button[i] = new Fl_Button(i % 2 == 0 ? X2 : X5, Y + H_LINE * int(i / 2 + 1), W_SEND, H_LINE, "Send");
            _button[i]->hide();
            _button[i]->callback(writeCb, &cbArray[i]);
        }
        _write[U_MIN] = new Write(U_MIN % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_MIN) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01,
                                  uMinReadAddress, uMinWriteAddress, _toRegisterCenti, _fromRegisterCenti);
        _write[U_MAX] = new Write(U_MAX % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_MAX) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01,
                                  uMaxReadAddress, uMaxWriteAddress, _toRegisterCenti, _fromRegisterCenti);
        _write[P_MAX] = new Write(P_MAX % 2 == 0 ? X1 : X4, Y + H_LINE * (int(P_MAX) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.1, 6550.0, 0.1,
                                  pMaxAddress, pMaxAddress, _toRegisterDeci, _fromRegisterDeci);

        _write[U_SOLCV] = new Write(U_SOLCV % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_SOLCV) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                    0.01, uSolCvReadAddress, uSolCvWriteAddress, _toRegisterCenti, _fromRegisterCenti);
        _write[U_DCLOW] = new Write(U_DCLOW % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_DCLOW) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                    0.01, dcLowReadAddress, dcLowWriteAddress, _toRegisterCenti, _fromRegisterCenti);
        _write[U_DCHIGH] = new Write(U_DCHIGH % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_DCHIGH) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                     0.01, dcHighReadAddress, dcHighWriteAddress, _toRegisterCenti, _fromRegisterCenti);

        _write[MODUS] = new Write(MODUS % 2 == 0 ? X1 : X4, Y + H_LINE * (int(MODUS) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 255.0, 1.00,
                                  modusAddress, modusAddress, _toRegister256, _fromRegister256);
        _write[S_BIOFF] = new Write(S_BIOFF % 2 == 0 ? X1 : X4, Y + H_LINE * (int(S_BIOFF) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 2.0, 1.0,
                                    sBioOffAddress, sBioOffAddress, _toRegister256, _fromRegister256);
        _write[U_DCSTART] = new Write(U_DCSTART % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_DCSTART) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                      655.00, 0.01, dcStartReadAddress, dcStartWriteAddress, _toRegisterCenti, _fromRegisterCenti);

        _write[Z_USOLBATFILT] = new Write(Z_USOLBATFILT % 2 == 0 ? X1 : X4, Y + H_LINE * (int(Z_USOLBATFILT) / 2 + 1), W_WRITE, H_LINE,
                                          FL_FLOAT_INPUT, 0.0, 255.0, 1.00, zUsolBatFil, zUsolBatFil, _toRegister256, _fromRegister256);
        _write[U_SOLBATERR] = new Write(U_SOLBATERR % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_SOLBATERR) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT,
                                        0.01, 655.00, 0.01, uSolBatErrRead, uSolBatErrWrite, _toRegisterCenti, _fromRegisterCenti);
        _write[U_SOLBAT] = new Write(U_SOLBAT % 2 == 0 ? X1 : X4, Y + H_LINE * (int(U_SOLBAT) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                     0.01, uSolBatRead, uSolBatWrite, _toRegisterCenti, _fromRegisterCenti);

        _write[P_MAXERR] = new Write(P_MAXERR % 2 == 0 ? X1 : X4, Y + H_LINE * (int(P_MAXERR) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                     0.01, pMaxErr, pMaxErr, _toRegisterCenti, _fromRegisterCenti);
        _write[P_MAX_CHARGE] = new Write(P_MAX_CHARGE % 2 == 0 ? X1 : X4, Y + H_LINE * (int(P_MAX_CHARGE) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT,
                                         0.01, 655.00, 0.01, pMaxCharge, pMaxCharge, _toRegisterCenti, _fromRegisterCenti);

        _label[ROBIN_SIZE] = new Fl_Box(X, Y + H_LINE * 4, W, H_LINE, LABEL[ROBIN_SIZE]);
        for (std::size_t i = 0; i < CURVES; i++)
        {
            cbArray[i + SIZE] = std::tuple<std::size_t, Battery*>{i + SIZE, this};
            const int y = Y + H_LINE * (int(i) + 9);
            const int W_LABEL_CURVE = (W_LABEL * 7) / 10;
            const int W_SEND_CURVE = (W_SEND * 5) / 10;
            const int W_CURVE = W - W_LABEL_CURVE - W_SEND_CURVE;
            const int X0 = X;
            const int X1 = X0 + W_LABEL_CURVE;
            const int X2 = X1 + W_CURVE;
            _label[SIZE + i] = new Fl_Box(X0, y, W_LABEL_CURVE, H_LINE, LABEL[SIZE + i]);
            _label[SIZE + i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _cvCurve[i] = new Curve<3>(X1, y, W_CURVE, H_LINE, FL_INT_INPUT, 0.0, 256.0, 1.0, curveAddressRead[i], curveAddressWrite[i],
                                       _toRegister256, _fromRegister256);
            _button[SIZE + i] = new Fl_Button(X2, y, W_SEND_CURVE, H_LINE, "Send");
            _button[SIZE + i]->hide();
            _button[SIZE + i]->callback(writeCb, &cbArray[i + SIZE]);
        }
        this->end();
    }
    /**
     * Destructor.
     */
    ~Battery() {}
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
                                                                   : _cvCurve[j - SIZE]->work(canTakeRequest && send.isEmpty(), response, request);
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
                if (_cvCurve[j - SIZE]->allIdleAndAtLeastOneDiffernt())
                    _button[j]->show();
                else
                    _button[j]->hide();
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }

  private:
    static constexpr std::size_t U_MIN = 0;
    static constexpr std::size_t U_MAX = U_MIN + 1;
    static constexpr std::size_t P_MAX = U_MAX + 1;

    static constexpr std::size_t U_SOLCV = P_MAX + 1;
    static constexpr std::size_t U_DCLOW = U_SOLCV + 1;
    static constexpr std::size_t U_DCHIGH = U_DCLOW + 1;

    static constexpr std::size_t MODUS = U_DCHIGH + 1;
    static constexpr std::size_t S_BIOFF = MODUS + 1;
    static constexpr std::size_t U_DCSTART = S_BIOFF + 1;

    static constexpr std::size_t Z_USOLBATFILT = U_DCSTART + 1;
    static constexpr std::size_t U_SOLBATERR = Z_USOLBATFILT + 1;
    static constexpr std::size_t U_SOLBAT = U_SOLBATERR + 1;

    static constexpr std::size_t P_MAXERR = U_SOLBAT + 1;
    static constexpr std::size_t P_MAX_CHARGE = P_MAXERR + 1;
    static constexpr std::size_t SIZE = P_MAX_CHARGE + 1;

    static constexpr std::size_t X_CV = 0;
    static constexpr std::size_t Y_CV = X_CV + 1;
    static constexpr std::size_t CURVES = Y_CV + 1;

    static constexpr std::size_t ROBIN_SIZE = SIZE + CURVES;

    std::array<Fl_Box*, ROBIN_SIZE + 1> _label;
    std::array<Write*, SIZE> _write;
    std::array<Fl_Button*, ROBIN_SIZE> _button;
    std::array<Curve<3>*, CURVES> _cvCurve;
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
        std::tuple<std::size_t, Battery*>* tuple = static_cast<std::tuple<std::size_t, Battery*>*>(object);
        if (tuple == nullptr) return;
        const std::size_t index = std::get<0>(*tuple);
        Battery* battery = std::get<1>(*tuple);
        if (battery == nullptr) return;
        if (index < SIZE)
            battery->_write[index]->write();
        else if (index < SIZE + CURVES)
            battery->_cvCurve[index - SIZE]->write();
    }
};
}  // namespace gui
}  // namespace catta
