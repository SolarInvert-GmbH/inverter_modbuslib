#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::RegisterAddress>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::RegisterAddress;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto handle = [this, input, error, stay, jump]()
        {
            bool failed = false;
            for (uint8_t i = 0; i < Output{}; i++)
                if (_possible[i])
                {
                    if (_index < _names[i].size() && input == Input::character(static_cast<char32_t>(_names.data()[i][_index])))
                        failed = false;
                    else if (_index == _names[i].size() && input == catta::json::Token::closeString())
                    {
                        _value = Output(i);
                        return jump(TAIL);
                    }
                    else
                        _possible[i] = false;
                }
            _index++;
            return failed ? error() : stay();
        };
        switch (_state)
        {
            case START:
                return input == catta::json::Token::nullObject() ? jump(TAIL) : input == catta::json::Token::openString() ? jump(STRING) : error();
            case STRING:
                return handle();
            case TAIL:
                return input == catta::json::Token::end() ? jump(DONE) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _index(0), _value(Output::empty()), _state(START)
    {
        for (bool& b : _possible) b = true;
    }
    [[nodiscard]] constexpr Output data() const noexcept { return _value; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    static constexpr std::array<std::string_view, 185> _names = {"CommonManufacturer",
                                                                 "CommonModel",
                                                                 "CommonVersion",
                                                                 "CommonSerialNumber",
                                                                 "CommonDeviceAddress",
                                                                 "InverterAmps",
                                                                 "InverterAmpsPhaseA",
                                                                 "InverterAmpsPhaseB",
                                                                 "InverterAmpsPhaseC",
                                                                 "InverterAmpsScaleFactor",
                                                                 "InverterPhaseVoltageA",
                                                                 "InverterPhaseVoltageB",
                                                                 "InverterPhaseVoltageC",
                                                                 "InverterPhaseVoltageScaleFactor",
                                                                 "InverterAcPower",
                                                                 "InverterAcPowerScaleFactor",
                                                                 "InverterHertz",
                                                                 "InverterHertzScaleFactor",
                                                                 "InverterAcApparentPower",
                                                                 "InverterAcApparentPowerScaleFactor",
                                                                 "InverterAcReactivePower",
                                                                 "InverterAcReactivePowerScaleFactor",
                                                                 "InverterPowerFactor",
                                                                 "InverterPowerFactorScaleFactor",
                                                                 "InverterWattHours",
                                                                 "InverterWattHoursScaleFactor",
                                                                 "InverterDcVoltage",
                                                                 "InverterDcVoltageScaleFactor",
                                                                 "InverterDcPower",
                                                                 "InverterDcPowerScaleFactor",
                                                                 "InverterTemperature",
                                                                 "InverterTemperatureScaleFactor",
                                                                 "InverterOperatingState",
                                                                 "InverterVendorOperatingState",
                                                                 "InverterVendorEventBitfield1",
                                                                 "InverterVendorEventBitfield2",
                                                                 "InverterVendorEventBitfield3",
                                                                 "InverterVendorEventBitfield4",
                                                                 "NameplateDerType",
                                                                 "BasicSettingsMaxPower",
                                                                 "ExtendedMesurementsAcWattHours",
                                                                 "ExtendedMesurementsAcLifetimeCharge",
                                                                 "StorageNominalChargePower",
                                                                 "SiControlModus",
                                                                 "SiControlUminRead",
                                                                 "SiControlUmaxRead",
                                                                 "SiControlVoltageDcStartRead",
                                                                 "SiControlBatteryBiModeRead",
                                                                 "SiControlBatterySaftyModeRead",
                                                                 "SiControlBatteryCvModeRead",
                                                                 "SiControlDcLowRead",
                                                                 "SiControlDcHighRead",
                                                                 "SiControlTrackingSelection",
                                                                 "SiControlFunctionActivate",
                                                                 "SiControlFunctionWriteEeprom",
                                                                 "SiControlFunctionReset",
                                                                 "SiControlStartCountdown",
                                                                 "SiControlNightShutdown",
                                                                 "SiControlPmax",
                                                                 "SiControlCosphi",
                                                                 "SiControlUptime",
                                                                 "SiControlMppStepDac0",
                                                                 "SiControlMppStepDac1",
                                                                 "SiControlMppStepDac2",
                                                                 "SiControlMppStepDac3",
                                                                 "SiControlMppStepUdc0",
                                                                 "SiControlMppStepUdc1",
                                                                 "SiControlMppStepUdc2",
                                                                 "SiControlMppStepUdc3",
                                                                 "SiControlMppSampleDac0",
                                                                 "SiControlMppSampleDac1",
                                                                 "SiControlMppSampleDac2",
                                                                 "SiControlMppSampleDac3",
                                                                 "SiControlMppSampleUdc0",
                                                                 "SiControlMppSampleUdc1",
                                                                 "SiControlMppSampleUdc2",
                                                                 "SiControlMppSampleUdc3",
                                                                 "SiControlReduction",
                                                                 "SiControlSineduty",
                                                                 "SiControlFilterWindCurve",
                                                                 "SiControlWindCurveX00read",
                                                                 "SiControlWindCurveX01read",
                                                                 "SiControlWindCurveX02read",
                                                                 "SiControlWindCurveX03read",
                                                                 "SiControlWindCurveX04read",
                                                                 "SiControlWindCurveX05read",
                                                                 "SiControlWindCurveX06read",
                                                                 "SiControlWindCurveX07read",
                                                                 "SiControlWindCurveX08read",
                                                                 "SiControlWindCurveX09read",
                                                                 "SiControlWindCurveX10read",
                                                                 "SiControlWindCurveX11read",
                                                                 "SiControlWindCurveX12read",
                                                                 "SiControlWindCurveX13read",
                                                                 "SiControlWindCurveX14read",
                                                                 "SiControlWindCurveX15read",
                                                                 "SiControlWindCurveY00Read",
                                                                 "SiControlWindCurveY01Read",
                                                                 "SiControlWindCurveY02Read",
                                                                 "SiControlWindCurveY03Read",
                                                                 "SiControlWindCurveY04Read",
                                                                 "SiControlWindCurveY05Read",
                                                                 "SiControlWindCurveY06Read",
                                                                 "SiControlWindCurveY07Read",
                                                                 "SiControlWindCurveY08Read",
                                                                 "SiControlWindCurveY09Read",
                                                                 "SiControlWindCurveY10Read",
                                                                 "SiControlWindCurveY11Read",
                                                                 "SiControlWindCurveY12Read",
                                                                 "SiControlWindCurveY13Read",
                                                                 "SiControlWindCurveY14Read",
                                                                 "SiControlWindCurveY15Read",
                                                                 "SiControlSolarBatteryFilterStep",
                                                                 "SiControlPowerLimitSaftyMode",
                                                                 "SiControlUminWrite",
                                                                 "SiControlUmaxWrite",
                                                                 "SiControlVoltageDcStartWrite",
                                                                 "SiControlBatteryBiModeWrite",
                                                                 "SiControlBatterySaftyModeWrite",
                                                                 "SiControlBatteryCvModeWrite",
                                                                 "SiControlDcLowWrite",
                                                                 "SiControlDcHighWrite",
                                                                 "SiControlWindCurveY00Write",
                                                                 "SiControlWindCurveY01Write",
                                                                 "SiControlWindCurveY02Write",
                                                                 "SiControlWindCurveY03Write",
                                                                 "SiControlWindCurveY04Write",
                                                                 "SiControlWindCurveY05Write",
                                                                 "SiControlWindCurveY06Write",
                                                                 "SiControlWindCurveY07Write",
                                                                 "SiControlWindCurveY08Write",
                                                                 "SiControlWindCurveY09Write",
                                                                 "SiControlWindCurveY10Write",
                                                                 "SiControlWindCurveY11Write",
                                                                 "SiControlWindCurveY12Write",
                                                                 "SiControlWindCurveY13Write",
                                                                 "SiControlWindCurveY14Write",
                                                                 "SiControlWindCurveY15Write",
                                                                 "SiControlConstantVoltageY0Write",
                                                                 "SiControlConstantVoltageY1Write",
                                                                 "SiControlConstantVoltageY2Write",
                                                                 "SiControlDacCurveY0",
                                                                 "SiControlDacCurveY1",
                                                                 "SiControlDacCurveY2",
                                                                 "SiControlDacCurveY3",
                                                                 "SiControlDacCurveY4",
                                                                 "SiControlDacCurveY5",
                                                                 "SiControlDacCurveY6",
                                                                 "SiControlDacCurveY7",
                                                                 "SiControlDacCurveY8",
                                                                 "SiControlDacCurveY9",
                                                                 "SiControlConstantVoltageX0",
                                                                 "SiControlConstantVoltageX1",
                                                                 "SiControlConstantVoltageX2",
                                                                 "SiControlConstantVoltageY0Read",
                                                                 "SiControlConstantVoltageY1Read",
                                                                 "SiControlConstantVoltageY2Read",
                                                                 "SiControlDacCurveX0",
                                                                 "SiControlDacCurveX1",
                                                                 "SiControlDacCurveX2",
                                                                 "SiControlDacCurveX3",
                                                                 "SiControlDacCurveX4",
                                                                 "SiControlDacCurveX5",
                                                                 "SiControlDacCurveX6",
                                                                 "SiControlDacCurveX7",
                                                                 "SiControlDacCurveX8",
                                                                 "SiControlDacCurveX9",
                                                                 "SiControlWindCurveX00write",
                                                                 "SiControlWindCurveX01write",
                                                                 "SiControlWindCurveX02write",
                                                                 "SiControlWindCurveX03write",
                                                                 "SiControlWindCurveX04write",
                                                                 "SiControlWindCurveX05write",
                                                                 "SiControlWindCurveX06write",
                                                                 "SiControlWindCurveX07write",
                                                                 "SiControlWindCurveX08write",
                                                                 "SiControlWindCurveX09write",
                                                                 "SiControlWindCurveX10write",
                                                                 "SiControlWindCurveX11write",
                                                                 "SiControlWindCurveX12write",
                                                                 "SiControlWindCurveX13write",
                                                                 "SiControlWindCurveX14write",
                                                                 "SiControlWindCurveX15write",
                                                                 "SiControlEnableWriteOnce",
                                                                 "SiControlEnableWritePermant"};
    std::array<bool, 185> _possible;
    size_t _index;
    Output _value;
    std::uint8_t _state;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t STRING = START + 1;
    static constexpr std::uint8_t TAIL = STRING + 1;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
