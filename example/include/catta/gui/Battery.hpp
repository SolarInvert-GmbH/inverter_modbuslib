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
            "UDCLOW",  "UDCSTART", "MODUS",      "PMAX",    "UMIN_ext",           "Z_usolbatfilt",      "usolbaterr", "USOLBAT", "UMAX_ext",
            "S_BIOFF", "pmaxerr",  "PMAXcharge", "UDCHIGH", "CONSTANT_VOLTAGE_X", "CONSTANT_VOLTAGE_Y", "DAC_X",      "COM_Y",   "CURVE"};
        static constexpr int GAP = 5;
        static constexpr int H_LINE = 65;

        static const int PER_LINE = 4;
        const int W_WRITE = (W - (PER_LINE + 1) * GAP) / PER_LINE;
        static const int W_SEND = 30;
        using Address = catta::modbus::si::RegisterAddress;

        static constexpr auto uMinReadAddress = Address::siControlUMinRead();
        static constexpr auto uMinWriteAddress = Address::siControlUMinWrite();
        static constexpr auto uMaxReadAddress = Address::siControlUMaxRead();
        static constexpr auto uMaxWriteAddress = Address::siControlUMaxWrite();
        static constexpr auto pMaxAddress = Address::basicSettingsMaxPower();

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

        static constexpr std::array<std::array<Address, 3>, CURVES_3> curve3AddressRead = {
            std::array<Address, 3>{Address::siControlConstantVoltageX0(), Address::siControlConstantVoltageX1(),
                                   Address::siControlConstantVoltageX2()},
            std::array<Address, 3>{Address::siControlConstantVoltageY0Read(), Address::siControlConstantVoltageY1Read(),
                                   Address::siControlConstantVoltageY2Read()}};

        static constexpr std::array<std::array<Address, 3>, CURVES_3> curve3AddressWrite = {
            std::array<Address, 3>{Address::siControlConstantVoltageX0(), Address::siControlConstantVoltageX1(),
                                   Address::siControlConstantVoltageX2()},
            std::array<Address, 3>{Address::siControlConstantVoltageY0Write(), Address::siControlConstantVoltageY1Write(),
                                   Address::siControlConstantVoltageY2Write()}};

        static constexpr std::array<std::array<Address, 10>, CURVES_10> curve10AddressRead = {
            std::array<Address, 10>{Address::siControlDacCurveX0(), Address::siControlDacCurveX1(), Address::siControlDacCurveX2(),
                                    Address::siControlDacCurveX3(), Address::siControlDacCurveX4(), Address::siControlDacCurveX5(),
                                    Address::siControlDacCurveX6(), Address::siControlDacCurveX7(), Address::siControlDacCurveX8(),
                                    Address::siControlDacCurveX9()},
            std::array<Address, 10>{Address::siControlDacCurveY0Read(), Address::siControlDacCurveY1Read(), Address::siControlDacCurveY2Read(),
                                    Address::siControlDacCurveY3Read(), Address::siControlDacCurveY4Read(), Address::siControlDacCurveY5Read(),
                                    Address::siControlDacCurveY6Read(), Address::siControlDacCurveY7Read(), Address::siControlDacCurveY8Read(),
                                    Address::siControlDacCurveY9Read()}};

        static constexpr std::array<std::array<Address, 10>, CURVES_10> curve10AddressWrite = {
            std::array<Address, 10>{Address::siControlDacCurveX0(), Address::siControlDacCurveX1(), Address::siControlDacCurveX2(),
                                    Address::siControlDacCurveX3(), Address::siControlDacCurveX4(), Address::siControlDacCurveX5(),
                                    Address::siControlDacCurveX6(), Address::siControlDacCurveX7(), Address::siControlDacCurveX8(),
                                    Address::siControlDacCurveX9()},
            std::array<Address, 10>{Address::siControlDacCurveY0Write(), Address::siControlDacCurveY1Write(), Address::siControlDacCurveY2Write(),
                                    Address::siControlDacCurveY3Write(), Address::siControlDacCurveY4Write(), Address::siControlDacCurveY5Write(),
                                    Address::siControlDacCurveY6Write(), Address::siControlDacCurveY7Write(), Address::siControlDacCurveY8Write(),
                                    Address::siControlDacCurveY9Write()}};

        static std::array<std::tuple<std::size_t, Battery*>, ROBIN_SIZE> cbArray;
        for (std::size_t i = 0; i < SIZE; i++)
        {
            cbArray[i] = std::tuple<std::size_t, Battery*>{i, this};
        }
        _write[U_DCLOW] = new WriteSingle(X + GAP + (int(U_DCLOW) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_DCLOW) / PER_LINE), W_WRITE,
                                          H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, dcLowReadAddress, dcLowWriteAddress, _toRegisterCenti,
                                          _fromRegisterCenti, W_SEND, "V", LABEL[U_DCLOW]);
        _write[U_DCSTART] = new WriteSingle(X + GAP + (int(U_DCSTART) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_DCSTART) / PER_LINE),
                                            W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, dcStartReadAddress, dcStartWriteAddress,
                                            _toRegisterCenti, _fromRegisterCenti, W_SEND, "V", LABEL[U_DCSTART]);
        _write[MODUS] =
            new WriteSingle(X + GAP + (int(MODUS) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(MODUS) / PER_LINE), W_WRITE, H_LINE,
                            FL_FLOAT_INPUT, 0.0, 255.0, 1.00, modusAddress, modusAddress, _toRegister256, _fromRegister256, W_SEND, "", LABEL[MODUS]);
        _write[P_MAX] = new WriteSingle(X + GAP + (int(P_MAX) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(P_MAX) / PER_LINE), W_WRITE, H_LINE,
                                        FL_FLOAT_INPUT, 0.1, 6550.0, 0.1, pMaxAddress, pMaxAddress, _toRegisterDeci, _fromRegisterDeci, W_SEND, "W",
                                        LABEL[P_MAX]);

        _write[U_MIN] = new WriteSingle(X + GAP + (int(U_MIN) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_MIN) / PER_LINE), W_WRITE, H_LINE,
                                        FL_FLOAT_INPUT, 0.01, 655.00, 0.01, uMinReadAddress, uMinWriteAddress, _toRegisterCenti, _fromRegisterCenti,
                                        W_SEND, "V", LABEL[U_MIN]);
        _write[Z_USOLBATFILT] = new WriteSingle(X + GAP + (int(Z_USOLBATFILT) % PER_LINE) * (GAP + W_WRITE),
                                                Y + H_LINE * (int(Z_USOLBATFILT) / PER_LINE), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.0, 255.0, 1.00,
                                                zUsolBatFil, zUsolBatFil, _toRegister256, _fromRegister256, W_SEND, "", LABEL[Z_USOLBATFILT]);
        _write[U_SOLBATERR] = new WriteSingle(X + GAP + (int(U_SOLBATERR) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_SOLBATERR) / PER_LINE),
                                              W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, uSolBatErrRead, uSolBatErrWrite, _toRegisterCenti,
                                              _fromRegisterCenti, W_SEND, "V", LABEL[U_SOLBATERR]);
        _write[U_SOLBAT] = new WriteSingle(X + GAP + (int(U_SOLBAT) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_SOLBAT) / PER_LINE), W_WRITE,
                                           H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, uSolBatRead, uSolBatWrite, _toRegisterCenti,
                                           _fromRegisterCenti, W_SEND, "V", LABEL[U_SOLBAT]);

        _write[U_MAX] = new WriteSingle(X + GAP + (int(U_MAX) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_MAX) / PER_LINE), W_WRITE, H_LINE,
                                        FL_FLOAT_INPUT, 0.01, 655.00, 0.01, uMaxReadAddress, uMaxWriteAddress, _toRegisterCenti, _fromRegisterCenti,
                                        W_SEND, "V", LABEL[U_MAX]);
        _write[S_BIOFF] = new WriteSingle(X + GAP + (int(S_BIOFF) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(S_BIOFF) / PER_LINE), W_WRITE,
                                          H_LINE, FL_FLOAT_INPUT, 0.0, 2.0, 1.0, sBioOffAddress, sBioOffAddress, _toRegister256, _fromRegister256,
                                          W_SEND, "", LABEL[S_BIOFF]);
        _write[P_MAXERR] =
            new WriteSingle(X + GAP + (int(P_MAXERR) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(P_MAXERR) / PER_LINE), W_WRITE, H_LINE,
                            FL_FLOAT_INPUT, 0.01, 655.00, 0.01, pMaxErr, pMaxErr, _toRegisterCenti, _fromRegisterCenti, W_SEND, "W", LABEL[P_MAXERR]);
        _write[P_MAX_CHARGE] = new WriteSingle(X + GAP + (int(P_MAX_CHARGE) % PER_LINE) * (GAP + W_WRITE),
                                               Y + H_LINE * (int(P_MAX_CHARGE) / PER_LINE), W_WRITE, H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01,
                                               pMaxCharge, pMaxCharge, _toRegisterCenti, _fromRegisterCenti, W_SEND, "W", LABEL[P_MAX_CHARGE]);

        _write[U_DCHIGH] = new WriteSingle(X + GAP + (int(U_DCHIGH) % PER_LINE) * (GAP + W_WRITE), Y + H_LINE * (int(U_DCHIGH) / PER_LINE), W_WRITE,
                                           H_LINE, FL_FLOAT_INPUT, 0.01, 655.00, 0.01, dcHighReadAddress, dcHighWriteAddress, _toRegisterCenti,
                                           _fromRegisterCenti, W_SEND, "V", LABEL[U_DCHIGH]);

        static const int PER_LINE_CURVE_3 = 2;
        const int W_WRITE_CURVE_3 = (W - (PER_LINE_CURVE_3 + 1) * GAP) / PER_LINE_CURVE_3;

        for (std::size_t i = 0; i < CURVES_3; i++)
        {
            cbArray[i + SIZE] = std::tuple<std::size_t, Battery*>{i + SIZE, this};
            const int y = Y + H_LINE * (int(SIZE / PER_LINE) + 1);
            _cvCurve3[i] = new Curve<3>(X + GAP + (int(i) % PER_LINE_CURVE_3) * (GAP + W_WRITE_CURVE_3), y + H_LINE * (int(i) / PER_LINE_CURVE_3),
                                        W_WRITE_CURVE_3, H_LINE, FL_INT_INPUT, 0.0, 256.0, 1.0, curve3AddressRead[i], curve3AddressWrite[i],
                                        _toRegister256, _fromRegister256, 30, "V", LABEL[i + SIZE]);
        }

        const int W_WRITE_CURVE_10 = W - 2 * GAP;

        for (std::size_t i = 0; i < CURVES_10; i++)
        {
            cbArray[i + SIZE + CURVES_3] = std::tuple<std::size_t, Battery*>{i + SIZE + CURVES_3, this};
            const int y = Y + H_LINE * (int(SIZE / PER_LINE) + 2);
            _cvCurve10[i] =
                new Curve<10>(X + GAP, y + H_LINE * (int(i)), W_WRITE_CURVE_10, H_LINE, FL_INT_INPUT, 0.0, 256.0, 1.0, curve10AddressRead[i],
                              curve10AddressWrite[i], _toRegister256, _fromRegister256, 30, "V", LABEL[i + SIZE + CURVES_3]);
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
     * @param[in] now The current time.
     * @return Returns the request to send.
     */
    catta::modbus::si::request::Request work(const bool canTakeRequest, const catta::modbus::si::response::Response& response,
                                             const catta::modbus::si::request::Request& request, const std::chrono::microseconds now)
    {
        catta::modbus::si::request::Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < ROBIN_SIZE; i++)
        {
            std::size_t j = (_roundRobin + i) % ROBIN_SIZE;
            const catta::modbus::si::request::Request r =
                j < SIZE              ? _write[j]->work(canTakeRequest && send.isEmpty(), response, request, now)
                : j - SIZE < CURVES_3 ? _cvCurve3[j - SIZE]->work(canTakeRequest && send.isEmpty(), response, request, now)
                                      : _cvCurve10[j - SIZE - CURVES_3]->work(canTakeRequest && send.isEmpty(), response, request, now);
            if (!r.isEmpty())
            {
                send = r;
                newRoundRobin = (j + 1) % ROBIN_SIZE;
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }
    /**
     * Better hide.
     */
    void stop()
    {
        for (std::size_t i = 0; i < _write.size(); i++) _write[i]->stop();
        for (std::size_t i = 0; i < _cvCurve3.size(); i++) _cvCurve3[i]->stop();
    }

  private:
    static constexpr std::size_t U_DCLOW = 0;
    static constexpr std::size_t U_DCSTART = U_DCLOW + 1;
    static constexpr std::size_t MODUS = U_DCSTART + 1;
    static constexpr std::size_t P_MAX = MODUS + 1;
    static constexpr std::size_t U_MIN = P_MAX + 1;
    static constexpr std::size_t Z_USOLBATFILT = U_MIN + 1;
    static constexpr std::size_t U_SOLBATERR = Z_USOLBATFILT + 1;
    static constexpr std::size_t U_SOLBAT = U_SOLBATERR + 1;
    static constexpr std::size_t U_MAX = U_SOLBAT + 1;
    static constexpr std::size_t S_BIOFF = U_MAX + 1;
    static constexpr std::size_t P_MAXERR = S_BIOFF + 1;
    static constexpr std::size_t P_MAX_CHARGE = P_MAXERR + 1;
    static constexpr std::size_t U_DCHIGH = P_MAX_CHARGE + 1;
    static constexpr std::size_t SIZE = U_DCHIGH + 1;

    static constexpr std::size_t X_CV = 0;
    static constexpr std::size_t Y_CV = X_CV + 1;
    static constexpr std::size_t CURVES_3 = Y_CV + 1;

    static constexpr std::size_t X_DAC = 0;
    static constexpr std::size_t Y_DAC = X_DAC + 1;
    static constexpr std::size_t CURVES_10 = Y_DAC + 1;

    static constexpr std::size_t ROBIN_SIZE = SIZE + CURVES_3 + CURVES_10;

    std::array<WriteSingle*, SIZE> _write;
    std::array<Curve<3>*, CURVES_3> _cvCurve3;
    std::array<Curve<10>*, CURVES_10> _cvCurve10;
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
