#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::RegisterAddress>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::RegisterAddress;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        if (input.isEmpty())
        {
            switch (_index)
            {
                case 0:
                    _index = 1;
                    _state = catta::parser::State::running();
                    _data = Output::nullObject();
                    return Tuple{Error(), catta::parser::InputHandled::no()};
                case 1:
                    _index = 2;
                    _state = catta::parser::State::done();
                    _data = Output::end();
                    return Tuple{Error(), catta::parser::InputHandled::yes()};
                default:
                    _state = catta::parser::State::failed();
                    return Tuple{Error::error(), catta::parser::InputHandled::yes()};
            }
        }
        else
        {
            if (_index == 0)
            {
                _index++;
                _state = catta::parser::State::running();
                _data = Output::openString();
                return Tuple{Error(), catta::parser::InputHandled::no()};
            }
            if (_index < _names[input].size() + 1)
            {
                const size_t index = _index - 1;
                _index++;
                _state = catta::parser::State::running();
                _data = Output::character(static_cast<char32_t>(_names[input][index]));
                return Tuple{Error(), catta::parser::InputHandled::no()};
            }
            if (_index == _names[input].size() + 1)
            {
                _index++;
                _state = catta::parser::State::running();
                _data = Output::closeString();
                return Tuple{Error(), catta::parser::InputHandled::no()};
            }
            if (_index == _names[input].size() + 2)
            {
                _index++;
                _state = catta::parser::State::done();
                _data = Output::end();
                return Tuple{Error(), catta::parser::InputHandled::yes()};
            }
            _state = catta::parser::State::failed();
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(catta::parser::State::start()), _index(0), _data(Output::empty()) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

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
    catta::parser::State _state;
    size_t _index;
    catta::json::Token _data;
};
}  // namespace tojson
}  // namespace catta
