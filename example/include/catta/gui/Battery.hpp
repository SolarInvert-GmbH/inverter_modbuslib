#pragma once

// gui
#include <catta/gui/Curve.hpp>
#include <catta/gui/WriteSingle.hpp>

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
        static const int W_LABEL = W2 / 2;
        static const int W_WRITE = W2 / 2;
        static const int W_SEND = 30;
        static const int X0 = X + 20;
        static const int X1 = X0 + W_LABEL + GAP;
        static const int X2 = X1 + W_WRITE + GAP * 4;
        static const int X3 = X2 + W_LABEL + GAP;
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
            _label[i] = new Fl_Box(i % 2 == 0 ? X0 : X2, Y + H_LINE * int(i / 2 + 1), W_LABEL, H_LINE, LABEL[i]);
            _label[i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        }
        _write[U_MIN] = new WriteSingle(U_MIN % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_MIN) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                        0.01, uMinReadAddress, uMinWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");
        _write[U_MAX] = new WriteSingle(U_MAX % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_MAX) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                                        0.01, uMaxReadAddress, uMaxWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");
        _write[P_MAX] = new WriteSingle(P_MAX % 2 == 0 ? X1 : X3, Y + H_LINE * (int(P_MAX) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.1, 6550.0,
                                        0.1, pMaxAddress, pMaxAddress, _toRegisterDeci, _fromRegisterDeci, W_SEND, "W");

        _write[U_SOLCV] = new WriteSingle(U_SOLCV % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_SOLCV) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                          655.00, 0.01, uSolCvReadAddress, uSolCvWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");
        _write[U_DCLOW] = new WriteSingle(U_DCLOW % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_DCLOW) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                          655.00, 0.01, dcLowReadAddress, dcLowWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");
        _write[U_DCHIGH] = new WriteSingle(U_DCHIGH % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_DCHIGH) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                           655.00, 0.01, dcHighReadAddress, dcHighWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");

        _write[MODUS] = new WriteSingle(MODUS % 2 == 0 ? X1 : X3, Y + H_LINE * (int(MODUS) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 255.0,
                                        1.00, modusAddress, modusAddress, _toRegister256, _fromRegister256, W_SEND, "");
        _write[S_BIOFF] = new WriteSingle(S_BIOFF % 2 == 0 ? X1 : X3, Y + H_LINE * (int(S_BIOFF) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 2.0,
                                          1.0, sBioOffAddress, sBioOffAddress, _toRegister256, _fromRegister256, W_SEND, "");
        _write[U_DCSTART] =
            new WriteSingle(U_DCSTART % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_DCSTART) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01,
                            dcStartReadAddress, dcStartWriteAddress, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");

        _write[Z_USOLBATFILT] =
            new WriteSingle(Z_USOLBATFILT % 2 == 0 ? X1 : X3, Y + H_LINE * (int(Z_USOLBATFILT) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 255.0,
                            1.00, zUsolBatFil, zUsolBatFil, _toRegister256, _fromRegister256, W_SEND, "");
        _write[U_SOLBATERR] =
            new WriteSingle(U_SOLBATERR % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_SOLBATERR) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                            0.01, uSolBatErrRead, uSolBatErrWrite, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");
        _write[U_SOLBAT] = new WriteSingle(U_SOLBAT % 2 == 0 ? X1 : X3, Y + H_LINE * (int(U_SOLBAT) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                           655.00, 0.01, uSolBatRead, uSolBatWrite, _toRegisterCenti, _fromRegisterCenti, W_SEND, "V");

        _write[P_MAXERR] = new WriteSingle(P_MAXERR % 2 == 0 ? X1 : X3, Y + H_LINE * (int(P_MAXERR) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01,
                                           655.00, 0.01, pMaxErr, pMaxErr, _toRegisterCenti, _fromRegisterCenti, W_SEND, "W");
        _write[P_MAX_CHARGE] =
            new WriteSingle(P_MAX_CHARGE % 2 == 0 ? X1 : X3, Y + H_LINE * (int(P_MAX_CHARGE) / 2 + 1), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00,
                            0.01, pMaxCharge, pMaxCharge, _toRegisterCenti, _fromRegisterCenti, W_SEND, "W");

        _label[ROBIN_SIZE] = new Fl_Box(X, Y + H_LINE * 8, W, H_LINE, LABEL[ROBIN_SIZE]);
        for (std::size_t i = 0; i < CURVES; i++)
        {
            cbArray[i + SIZE] = std::tuple<std::size_t, Battery*>{i + SIZE, this};
            const int y = Y + H_LINE * (int(i) + 9);
            const int W_LABEL_CURVE = (W_LABEL * 7) / 10;
            const int W_SEND_CURVE = (W_SEND * 5) / 10;
            const int W_CURVE = W - W_LABEL_CURVE - W_SEND_CURVE;
            const int X0 = X;
            const int X1 = X0 + W_LABEL_CURVE;
            _label[SIZE + i] = new Fl_Box(X0, y, W_LABEL_CURVE, H_LINE, LABEL[SIZE + i]);
            _label[SIZE + i]->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
            _cvCurve[i] = new Curve<3>(X1, y, W_CURVE, H_LINE, FL_INT_INPUT, 0.0, 256.0, 1.0, curveAddressRead[i], curveAddressWrite[i],
                                       _toRegister256, _fromRegister256, 30, "V");
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
    std::array<WriteSingle*, SIZE> _write;
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
};
}  // namespace gui
}  // namespace catta
