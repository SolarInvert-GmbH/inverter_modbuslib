#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

// si
#include <catta/modbus/si/RegisterType.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Represents the si register address.
 * @author CattaTech - Maik Urbannek
 */
class RegisterAddress
{
  private:
    constexpr static std::uint8_t COMMON_MANUFACTURER = 0;
    constexpr static std::uint8_t COMMON_MODEL = 1;
    constexpr static std::uint8_t COMMON_VERSION = 2;
    constexpr static std::uint8_t COMMON_SERIAL_NUMBER = 3;
    constexpr static std::uint8_t COMMON_DEVICE_ADDRESS = 4;
    constexpr static std::uint8_t INVERTER_AMPS = 5;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_A = 6;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_B = 7;
    constexpr static std::uint8_t INVERTER_AMPS_PHASE_C = 8;
    constexpr static std::uint8_t INVERTER_AMPS_SCALE_FACTOR = 9;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_A = 10;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_B = 11;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_C = 12;
    constexpr static std::uint8_t INVERTER_PHASE_VOLTAGE_SCALE_FACTOR = 13;
    constexpr static std::uint8_t INVERTER_AC_POWER = 14;
    constexpr static std::uint8_t INVERTER_AC_POWER_SCALE_FACTOR = 15;
    constexpr static std::uint8_t INVERTER_HERTZ = 16;
    constexpr static std::uint8_t INVERTER_HERTZ_SCALE_FACTOR = 17;
    constexpr static std::uint8_t INVERTER_AC_APPARENT_POWER = 18;
    constexpr static std::uint8_t INVERTER_AC_APPARENT_POWER_SCALE_FACTOR = 19;
    constexpr static std::uint8_t INVERTER_AC_REACTIVE_POWER = 20;
    constexpr static std::uint8_t INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR = 21;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR = 22;
    constexpr static std::uint8_t INVERTER_POWER_FACTOR_SCALE_FACTOR = 23;
    constexpr static std::uint8_t INVERTER_WATT_HOURS = 24;
    constexpr static std::uint8_t INVERTER_WATT_HOURS_SCALE_FACTOR = 25;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE = 26;
    constexpr static std::uint8_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = 27;
    constexpr static std::uint8_t INVERTER_DC_POWER = 28;
    constexpr static std::uint8_t INVERTER_DC_POWER_SCALE_FACTOR = 29;
    constexpr static std::uint8_t INVERTER_TEMPERATURE = 30;
    constexpr static std::uint8_t INVERTER_TEMPERATURE_SCALE_FACTOR = 31;
    constexpr static std::uint8_t INVERTER_OPERATING_STATE = 32;
    constexpr static std::uint8_t INVERTER_VENDOR_OPERATING_STATE = 33;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_1 = 34;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_2 = 35;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_3 = 36;
    constexpr static std::uint8_t INVERTER_VENDOR_EVENT_BITFIELD_4 = 37;
    constexpr static std::uint8_t NAMEPLATE_DER_TYPE = 38;
    constexpr static std::uint8_t BASIC_SETTINGS_MAX_POWER = 39;
    constexpr static std::uint8_t EXTENDED_MESUREMENTS_AC_WATT_HOURS = 40;
    constexpr static std::uint8_t EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE = 41;
    constexpr static std::uint8_t STORAGE_NOMINAL_CHARGE_POWER = 42;
    constexpr static std::uint8_t SI_CONTROL_MODUS = 43;
    constexpr static std::uint8_t SI_CONTROL_U_MIN_READ = 44;
    constexpr static std::uint8_t SI_CONTROL_U_MAX_READ = 45;
    constexpr static std::uint8_t SI_CONTROL_VOLTAGE_DC_START_READ = 46;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_BI_MODE_READ = 47;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_SAFTY_MODE_READ = 48;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_CV_MODE_READ = 49;
    constexpr static std::uint8_t SI_CONTROL_DC_LOW_READ = 50;
    constexpr static std::uint8_t SI_CONTROL_DC_HIGH_READ = 51;
    constexpr static std::uint8_t SI_CONTROL_TRACKING_SELECTION = 52;
    constexpr static std::uint8_t SI_CONTROL_START_COUNTDOWN = 53;
    constexpr static std::uint8_t SI_CONTROL_NIGHT_SHUTDOWN = 54;
    constexpr static std::uint8_t SI_CONTROL_PMAX = 55;
    constexpr static std::uint8_t SI_CONTROL_COSPHI = 56;
    constexpr static std::uint8_t SI_CONTROL_UPTIME = 57;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_DAC_0 = 58;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_DAC_1 = 59;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_DAC_2 = 60;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_DAC_3 = 61;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_UDC_0 = 62;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_UDC_1 = 63;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_UDC_2 = 64;
    constexpr static std::uint8_t SI_CONTROL_MPP_STEP_UDC_3 = 65;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_DAC_0 = 66;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_DAC_1 = 67;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_DAC_2 = 68;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_DAC_3 = 69;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_UDC_0 = 70;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_UDC_1 = 71;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_UDC_2 = 72;
    constexpr static std::uint8_t SI_CONTROL_MPP_SAMPLE_UDC_3 = 73;
    constexpr static std::uint8_t SI_CONTROL_REDUCTION = 74;
    constexpr static std::uint8_t SI_CONTROL_SINEDUTY = 75;
    constexpr static std::uint8_t SI_CONTROL_FILTER_WIND_CURVE = 76;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_00 = 77;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_01 = 78;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_02 = 79;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_03 = 80;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_04 = 81;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_05 = 82;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_06 = 83;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_07 = 84;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_08 = 85;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_09 = 86;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_10 = 87;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_11 = 88;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_12 = 89;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_13 = 90;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_14 = 91;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_X_15 = 92;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_00_READ = 93;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_01_READ = 94;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_02_READ = 95;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_03_READ = 96;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_04_READ = 97;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_05_READ = 98;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_06_READ = 99;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_07_READ = 100;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_08_READ = 101;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_09_READ = 102;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_10_READ = 103;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_11_READ = 104;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_12_READ = 105;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_13_READ = 106;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_14_READ = 107;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_15_READ = 108;
    constexpr static std::uint8_t SI_CONTROL_SOLAR_BATTERY_FILTER_STEP = 109;
    constexpr static std::uint8_t SI_CONTROL_POWER_LIMIT_SAFTY_MODE = 110;
    constexpr static std::uint8_t SI_CONTROL_U_MAX_WRITE = 111;
    constexpr static std::uint8_t SI_CONTROL_U_MIN_WRITE = 112;
    constexpr static std::uint8_t SI_CONTROL_VOLTAGE_DC_START_WRITE = 113;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_BI_MODE_WRITE = 114;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_SAFTY_MODE_WRITE = 115;
    constexpr static std::uint8_t SI_CONTROL_BATTARY_CV_MODE_WRITE = 116;
    constexpr static std::uint8_t SI_CONTROL_DC_LOW_WRITE = 117;
    constexpr static std::uint8_t SI_CONTROL_DC_HIGH_WRITE = 118;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_00_WRITE = 119;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_01_WRITE = 120;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_02_WRITE = 121;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_03_WRITE = 122;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_04_WRITE = 123;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_05_WRITE = 124;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_06_WRITE = 125;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_07_WRITE = 126;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_08_WRITE = 127;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_09_WRITE = 128;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_10_WRITE = 129;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_11_WRITE = 130;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_12_WRITE = 131;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_13_WRITE = 132;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_14_WRITE = 133;
    constexpr static std::uint8_t SI_CONTROL_WIND_CURVE_Y_15_WRITE = 134;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE = 135;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE = 136;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE = 137;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_0_READ = 138;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_1_READ = 139;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_2_READ = 140;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_3_READ = 141;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_4_READ = 142;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_5_READ = 143;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_6_READ = 144;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_7_READ = 145;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_8_READ = 146;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_9_READ = 147;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_X_0 = 148;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_X_1 = 149;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_X_2 = 150;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ = 151;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ = 152;
    constexpr static std::uint8_t SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ = 153;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_0 = 154;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_1 = 155;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_2 = 156;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_3 = 157;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_4 = 158;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_5 = 159;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_6 = 160;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_7 = 161;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_8 = 162;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_X_9 = 163;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_0_WRITE = 164;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_1_WRITE = 165;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_2_WRITE = 166;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_3_WRITE = 167;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_4_WRITE = 168;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_5_WRITE = 169;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_6_WRITE = 170;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_7_WRITE = 171;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_8_WRITE = 172;
    constexpr static std::uint8_t SI_CONTROL_DAC_CURVE_Y_9_WRITE = 173;
    constexpr static std::uint8_t EMPTY = 174;

  public:
    /**
     * @param[in] value The enum value of the register.
     * @warning This constructor should not be used. Use commonManufacturer(), commonModel(), commonVersion(), commonSerialNumber(),
     * commonDeviceAddress(), inverterAmps(), inverterAmpsPhaseA(), inverterAmpsPhaseB(), inverterAmpsPhaseC(), inverterAmpsScaleFactor(),
     * inverterPhaseVoltageA(), inverterPhaseVoltageB(), inverterPhaseVoltageC(), inverterPhaseVoltageScaleFactor(), inverterAcPower(),
     * inverterAcPowerScaleFactor(), inverterHertz(), inverterHertzScaleFactor(), inverterAcApparentPower(), inverterAcApparentPowerScaleFactor(),
     * inverterAcReactivePower(), inverterAcReactivePowerScaleFactor(), inverterPowerFactor(), inverterPowerFactorScaleFactor(), inverterWattHours(),
     * inverterWattHoursScaleFactor(), inverterDcVoltage(), inverterDcVoltageScaleFactor(), inverterDcPower(), inverterDcPowerScaleFactor(),
     * inverterTemperature(), inverterTemperatureScaleFactor(), inverterOperatingState(), inverterVendorOperatingState(),
     * inverterVendorEventBitfield1(), inverterVendorEventBitfield2(), inverterVendorEventBitfield3(), inverterVendorEventBitfield4(),
     * nameplateDerType(), basicSettingsMaxPower(), extendedMesurementsAcWattHours(), extendedMesurementsAcLifetimeCharge(),
     * storageNominalChargePower(), siControlModus(), siControlUMinRead(), siControlUMaxRead(), siControlVoltageDcStartRead(),
     * siControlBattaryBiModeRead(), siControlBattarySaftyModeRead(), siControlBattaryCvModeRead(), siControlDcLowRead(), siControlDcHighRead(),
     * siControlTrackingSelection(), siControlStartCountdown(), siControlNightShutdown(), siControlPmax(), siControlCosphi(), siControlUptime(),
     * siControlMppStepDac0(), siControlMppStepDac1(), siControlMppStepDac2(), siControlMppStepDac3(), siControlMppStepUdc0(), siControlMppStepUdc1(),
     * siControlMppStepUdc2(), siControlMppStepUdc3(), siControlMppSampleDac0(), siControlMppSampleDac1(), siControlMppSampleDac2(),
     * siControlMppSampleDac3(), siControlMppSampleUdc0(), siControlMppSampleUdc1(), siControlMppSampleUdc2(), siControlMppSampleUdc3(),
     * siControlReduction(), siControlSineduty(), siControlFilterWindCurve(), siControlWindCurveX00(), siControlWindCurveX01(),
     * siControlWindCurveX02(), siControlWindCurveX03(), siControlWindCurveX04(), siControlWindCurveX05(), siControlWindCurveX06(),
     * siControlWindCurveX07(), siControlWindCurveX08(), siControlWindCurveX09(), siControlWindCurveX10(), siControlWindCurveX11(),
     * siControlWindCurveX12(), siControlWindCurveX13(), siControlWindCurveX14(), siControlWindCurveX15(), siControlWindCurveY00Read(),
     * siControlWindCurveY01Read(), siControlWindCurveY02Read(), siControlWindCurveY03Read(), siControlWindCurveY04Read(),
     * siControlWindCurveY05Read(), siControlWindCurveY06Read(), siControlWindCurveY07Read(), siControlWindCurveY08Read(),
     * siControlWindCurveY09Read(), siControlWindCurveY10Read(), siControlWindCurveY11Read(), siControlWindCurveY12Read(),
     * siControlWindCurveY13Read(), siControlWindCurveY14Read(), siControlWindCurveY15Read(), siControlSolarBatteryFilterStep(),
     * siControlPowerLimitSaftyMode(), siControlUMaxWrite(), siControlUMinWrite(), siControlVoltageDcStartWrite(), siControlBattaryBiModeWrite(),
     * siControlBattarySaftyModeWrite(), siControlBattaryCvModeWrite(), siControlDcLowWrite(), siControlDcHighWrite(), siControlWindCurveY00Write(),
     * siControlWindCurveY01Write(), siControlWindCurveY02Write(), siControlWindCurveY03Write(), siControlWindCurveY04Write(),
     * siControlWindCurveY05Write(), siControlWindCurveY06Write(), siControlWindCurveY07Write(), siControlWindCurveY08Write(),
     * siControlWindCurveY09Write(), siControlWindCurveY10Write(), siControlWindCurveY11Write(), siControlWindCurveY12Write(),
     * siControlWindCurveY13Write(), siControlWindCurveY14Write(), siControlWindCurveY15Write(), siControlConstantVoltageY0Write(),
     * siControlConstantVoltageY1Write(), siControlConstantVoltageY2Write(), siControlDacCurveY0Read(), siControlDacCurveY1Read(),
     * siControlDacCurveY2Read(), siControlDacCurveY3Read(), siControlDacCurveY4Read(), siControlDacCurveY5Read(), siControlDacCurveY6Read(),
     * siControlDacCurveY7Read(), siControlDacCurveY8Read(), siControlDacCurveY9Read(), siControlConstantVoltageX0(), siControlConstantVoltageX1(),
     * siControlConstantVoltageX2(), siControlConstantVoltageY0Read(), siControlConstantVoltageY1Read(), siControlConstantVoltageY2Read(),
     * siControlDacCurveX0(), siControlDacCurveX1(), siControlDacCurveX2(), siControlDacCurveX3(), siControlDacCurveX4(), siControlDacCurveX5(),
     * siControlDacCurveX6(), siControlDacCurveX7(), siControlDacCurveX8(), siControlDacCurveX9(), siControlDacCurveY0Write(),
     * siControlDacCurveY1Write(), siControlDacCurveY2Write(), siControlDacCurveY3Write(), siControlDacCurveY4Write(), siControlDacCurveY5Write(),
     * siControlDacCurveY6Write(), siControlDacCurveY7Write(), siControlDacCurveY8Write(), siControlDacCurveY9Write() or empty(). Explicit
     * constructor. Converts uint8 to register.
     */
    [[nodiscard]] constexpr explicit RegisterAddress(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid register.
     */
    [[nodiscard]] constexpr RegisterAddress() noexcept : RegisterAddress(EMPTY) {}
    /**
     * @return Returns the name of the manufacturer from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonManufacturer() noexcept { return RegisterAddress{COMMON_MANUFACTURER}; }
    /**
     * @return Returns the model name from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonModel() noexcept { return RegisterAddress{COMMON_MODEL}; }
    /**
     * @return Returns the version from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonVersion() noexcept { return RegisterAddress{COMMON_VERSION}; }
    /**
     * @return Returns the serial number from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonSerialNumber() noexcept { return RegisterAddress{COMMON_SERIAL_NUMBER}; }
    /**
     * @return Returns the device address from the common model.
     */
    [[nodiscard]] constexpr static RegisterAddress commonDeviceAddress() noexcept { return RegisterAddress{COMMON_DEVICE_ADDRESS}; }
    /**
     * @return Returns the device AC current on all phases from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmps() noexcept { return RegisterAddress{INVERTER_AMPS}; }
    /**
     * @return Returns the device AC current on phases a from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseA() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_A}; }
    /**
     * @return Returns the device AC current on phases b from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseB() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_B}; }
    /**
     * @return Returns the device AC current on phases c from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsPhaseC() noexcept { return RegisterAddress{INVERTER_AMPS_PHASE_C}; }
    /**
     * @return Returns the device AC current scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAmpsScaleFactor() noexcept { return RegisterAddress{INVERTER_AMPS_SCALE_FACTOR}; }
    /**
     * @return Returns the device AC Voltage on phase a from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageA() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_A}; }
    /**
     * @return Returns the device AC Voltage on phase b from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageB() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_B}; }
    /**
     * @return Returns the device AC Voltage on phase c from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageC() noexcept { return RegisterAddress{INVERTER_PHASE_VOLTAGE_C}; }
    /**
     * @return Returns the device AC Voltage scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPhaseVoltageScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_PHASE_VOLTAGE_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcPower() noexcept { return RegisterAddress{INVERTER_AC_POWER}; }
    /**
     * @return Returns the device AC power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcPowerScaleFactor() noexcept { return RegisterAddress{INVERTER_AC_POWER_SCALE_FACTOR}; }
    /**
     * @return Returns the device line frequency from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertz() noexcept { return RegisterAddress{INVERTER_HERTZ}; }
    /**
     * @return Returns the device line frequency scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterHertzScaleFactor() noexcept { return RegisterAddress{INVERTER_HERTZ_SCALE_FACTOR}; }
    /**
     * @return Returns the device AC apparent power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcApparentPower() noexcept { return RegisterAddress{INVERTER_AC_APPARENT_POWER}; }
    /**
     * @return Returns the device AC apparent power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcApparentPowerScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_AC_APPARENT_POWER_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC reactive power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcReactivePower() noexcept { return RegisterAddress{INVERTER_AC_REACTIVE_POWER}; }
    /**
     * @return Returns the device AC reactive power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterAcReactivePowerScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC power factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPowerFactor() noexcept { return RegisterAddress{INVERTER_POWER_FACTOR}; }
    /**
     * @return Returns the device AC power factor scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterPowerFactorScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_POWER_FACTOR_SCALE_FACTOR};
    }
    /**
     * @return Returns the device AC energy from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterWattHours() noexcept { return RegisterAddress{INVERTER_WATT_HOURS}; }
    /**
     * @return Returns the device AC energy scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterWattHoursScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_WATT_HOURS_SCALE_FACTOR};
    }
    /**
     * @return Returns the device DC voltage from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcVoltage() noexcept { return RegisterAddress{INVERTER_DC_VOLTAGE}; }
    /**
     * @return Returns the device DC voltage scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcVoltageScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_DC_VOLTAGE_SCALE_FACTOR};
    }
    /**
     * @return Returns the device DC power from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcPower() noexcept { return RegisterAddress{INVERTER_DC_POWER}; }
    /**
     * @return Returns the device DC power scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterDcPowerScaleFactor() noexcept { return RegisterAddress{INVERTER_DC_POWER_SCALE_FACTOR}; }
    /**
     * @return Returns the device cabinet temperature from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterTemperature() noexcept { return RegisterAddress{INVERTER_TEMPERATURE}; }
    /**
     * @return Returns the device cabinet temperature scale factor from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterTemperatureScaleFactor() noexcept
    {
        return RegisterAddress{INVERTER_TEMPERATURE_SCALE_FACTOR};
    }
    /**
     * @return Returns the operating state from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterOperatingState() noexcept { return RegisterAddress{INVERTER_OPERATING_STATE}; }
    /**
     * @return Returns the vendor operating state from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorOperatingState() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_OPERATING_STATE};
    }
    /**
     * @return Returns the vendor event bitfield 1 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield1() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_1};
    }
    /**
     * @return Returns the vendor event bitfield 2 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield2() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_2};
    }
    /**
     * @return Returns the vendor event bitfield 3 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield3() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_3};
    }
    /**
     * @return Returns the vendor event bitfield 4 from the inverter model.
     */
    [[nodiscard]] constexpr static RegisterAddress inverterVendorEventBitfield4() noexcept
    {
        return RegisterAddress{INVERTER_VENDOR_EVENT_BITFIELD_4};
    }
    /**
     * @return Returns the der type from the nameplate model.
     */
    [[nodiscard]] constexpr static RegisterAddress nameplateDerType() noexcept { return RegisterAddress{NAMEPLATE_DER_TYPE}; }
    /**
     * @return Returns the nominal power from the basic settings.
     */
    [[nodiscard]] constexpr static RegisterAddress basicSettingsMaxPower() noexcept { return RegisterAddress{BASIC_SETTINGS_MAX_POWER}; }
    /**
     * @return Returns the AC lifetime active (real) energy output from the extended mesurements model.
     */
    [[nodiscard]] constexpr static RegisterAddress extendedMesurementsAcWattHours() noexcept
    {
        return RegisterAddress{EXTENDED_MESUREMENTS_AC_WATT_HOURS};
    }
    /**
     * @return Returns the AC lifetime active (real) energy charge from the extended mesurements model.
     */
    [[nodiscard]] constexpr static RegisterAddress extendedMesurementsAcLifetimeCharge() noexcept
    {
        return RegisterAddress{EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE};
    }
    /**
     * @return Returns the nominal charge power from the storage model.
     */
    [[nodiscard]] constexpr static RegisterAddress storageNominalChargePower() noexcept { return RegisterAddress{STORAGE_NOMINAL_CHARGE_POWER}; }
    /**
     * @return Returns the modus from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlModus() noexcept { return RegisterAddress{SI_CONTROL_MODUS}; }
    /**
     * @return Returns the u min from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlUMinRead() noexcept { return RegisterAddress{SI_CONTROL_U_MIN_READ}; }
    /**
     * @return Returns the u max from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlUMaxRead() noexcept { return RegisterAddress{SI_CONTROL_U_MAX_READ}; }
    /**
     * @return Returns the start voltage from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlVoltageDcStartRead() noexcept
    {
        return RegisterAddress{SI_CONTROL_VOLTAGE_DC_START_READ};
    }
    /**
     * @return Returns the battery voltage setpoint in bi mode from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattaryBiModeRead() noexcept { return RegisterAddress{SI_CONTROL_BATTARY_BI_MODE_READ}; }
    /**
     * @return Returns the battery voltage setpoint in bi mode from the safty control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattarySaftyModeRead() noexcept
    {
        return RegisterAddress{SI_CONTROL_BATTARY_SAFTY_MODE_READ};
    }
    /**
     * @return Returns the battery voltage setpoint in cv mode from the safty control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattaryCvModeRead() noexcept { return RegisterAddress{SI_CONTROL_BATTARY_CV_MODE_READ}; }
    /**
     * @return Returns the low voltage for relay off from the safty control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDcLowRead() noexcept { return RegisterAddress{SI_CONTROL_DC_LOW_READ}; }
    /**
     * @return Returns the high voltage for relay off from the safty control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDcHighRead() noexcept { return RegisterAddress{SI_CONTROL_DC_HIGH_READ}; }
    /**
     * @return Returns the strategy switch for behavior in safety mode from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlTrackingSelection() noexcept { return RegisterAddress{SI_CONTROL_TRACKING_SELECTION}; }
    /**
     * @return Returns the start countdown from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlStartCountdown() noexcept { return RegisterAddress{SI_CONTROL_START_COUNTDOWN}; }
    /**
     * @return Returns the night shutdown from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlNightShutdown() noexcept { return RegisterAddress{SI_CONTROL_NIGHT_SHUTDOWN}; }
    /**
     * @return Returns the pmax from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlPmax() noexcept { return RegisterAddress{SI_CONTROL_PMAX}; }
    /**
     * @return Returns the cosphi from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlCosphi() noexcept { return RegisterAddress{SI_CONTROL_COSPHI}; }
    /**
     * @return Returns the uptime from the safty control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlUptime() noexcept { return RegisterAddress{SI_CONTROL_UPTIME}; }
    /**
     * @return Returns the mpp step dac 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepDac0() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_DAC_0}; }
    /**
     * @return Returns the mpp step dac 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepDac1() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_DAC_1}; }
    /**
     * @return Returns the mpp step dac 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepDac2() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_DAC_2}; }
    /**
     * @return Returns the mpp step dac 3 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepDac3() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_DAC_3}; }
    /**
     * @return Returns the mpp step udc 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepUdc0() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_UDC_0}; }
    /**
     * @return Returns the mpp step udc 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepUdc1() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_UDC_1}; }
    /**
     * @return Returns the mpp step udc 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepUdc2() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_UDC_2}; }
    /**
     * @return Returns the mpp step udc 3 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppStepUdc3() noexcept { return RegisterAddress{SI_CONTROL_MPP_STEP_UDC_3}; }
    /**
     * @return Returns the mpp sample dac 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleDac0() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_DAC_0}; }
    /**
     * @return Returns the mpp sample dac 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleDac1() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_DAC_1}; }
    /**
     * @return Returns the mpp sample dac 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleDac2() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_DAC_2}; }
    /**
     * @return Returns the mpp sample dac 3 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleDac3() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_DAC_3}; }
    /**
     * @return Returns the mpp sample udc 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleUdc0() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_UDC_0}; }
    /**
     * @return Returns the mpp sample udc 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleUdc1() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_UDC_1}; }
    /**
     * @return Returns the mpp sample udc 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleUdc2() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_UDC_2}; }
    /**
     * @return Returns the mpp sample udc 3 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlMppSampleUdc3() noexcept { return RegisterAddress{SI_CONTROL_MPP_SAMPLE_UDC_3}; }
    /**
     * @return Returns the reduction from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlReduction() noexcept { return RegisterAddress{SI_CONTROL_REDUCTION}; }
    /**
     * @return Returns the sineduty from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlSineduty() noexcept { return RegisterAddress{SI_CONTROL_SINEDUTY}; }
    /**
     * @return Returns the filter wind curve from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlFilterWindCurve() noexcept { return RegisterAddress{SI_CONTROL_FILTER_WIND_CURVE}; }
    /**
     * @return Returns the wind curve x 00 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX00() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_00}; }
    /**
     * @return Returns the wind curve x 01 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX01() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_01}; }
    /**
     * @return Returns the wind curve x 02 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX02() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_02}; }
    /**
     * @return Returns the wind curve x 03 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX03() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_03}; }
    /**
     * @return Returns the wind curve x 04 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX04() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_04}; }
    /**
     * @return Returns the wind curve x 05 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX05() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_05}; }
    /**
     * @return Returns the wind curve x 06 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX06() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_06}; }
    /**
     * @return Returns the wind curve x 07 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX07() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_07}; }
    /**
     * @return Returns the wind curve x 08 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX08() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_08}; }
    /**
     * @return Returns the wind curve x 09 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX09() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_09}; }
    /**
     * @return Returns the wind curve x 10 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX10() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_10}; }
    /**
     * @return Returns the wind curve x 11 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX11() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_11}; }
    /**
     * @return Returns the wind curve x 12 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX12() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_12}; }
    /**
     * @return Returns the wind curve x 13 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX13() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_13}; }
    /**
     * @return Returns the wind curve x 14 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX14() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_14}; }
    /**
     * @return Returns the wind curve x 15 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveX15() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_X_15}; }
    /**
     * @return Returns the wind curve y 00 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY00Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_00_READ}; }
    /**
     * @return Returns the wind curve y 01 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY01Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_01_READ}; }
    /**
     * @return Returns the wind curve y 02 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY02Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_02_READ}; }
    /**
     * @return Returns the wind curve y 03 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY03Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_03_READ}; }
    /**
     * @return Returns the wind curve y 04 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY04Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_04_READ}; }
    /**
     * @return Returns the wind curve y 05 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY05Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_05_READ}; }
    /**
     * @return Returns the wind curve y 06 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY06Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_06_READ}; }
    /**
     * @return Returns the wind curve y 07 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY07Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_07_READ}; }
    /**
     * @return Returns the wind curve y 08 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY08Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_08_READ}; }
    /**
     * @return Returns the wind curve y 09 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY09Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_09_READ}; }
    /**
     * @return Returns the wind curve y 10 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY10Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_10_READ}; }
    /**
     * @return Returns the wind curve y 11 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY11Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_11_READ}; }
    /**
     * @return Returns the wind curve y 12 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY12Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_12_READ}; }
    /**
     * @return Returns the wind curve y 13 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY13Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_13_READ}; }
    /**
     * @return Returns the wind curve y 14 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY14Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_14_READ}; }
    /**
     * @return Returns the wind curve y 15 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY15Read() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_15_READ}; }
    /**
     * @return Returns the solar battery filter step from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlSolarBatteryFilterStep() noexcept
    {
        return RegisterAddress{SI_CONTROL_SOLAR_BATTERY_FILTER_STEP};
    }
    /**
     * @return Returns the power limit for safty mode from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlPowerLimitSaftyMode() noexcept
    {
        return RegisterAddress{SI_CONTROL_POWER_LIMIT_SAFTY_MODE};
    }
    /**
     * @return Returns the u min from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlUMaxWrite() noexcept { return RegisterAddress{SI_CONTROL_U_MAX_WRITE}; }
    /**
     * @return Returns the u max from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlUMinWrite() noexcept { return RegisterAddress{SI_CONTROL_U_MIN_WRITE}; }
    /**
     * @return Returns the start voltage from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlVoltageDcStartWrite() noexcept
    {
        return RegisterAddress{SI_CONTROL_VOLTAGE_DC_START_WRITE};
    }
    /**
     * @return Returns the battery voltage setpoint in bi mode from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattaryBiModeWrite() noexcept
    {
        return RegisterAddress{SI_CONTROL_BATTARY_BI_MODE_WRITE};
    }
    /**
     * @return Returns the battery voltage setpoint in bi mode from the safty control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattarySaftyModeWrite() noexcept
    {
        return RegisterAddress{SI_CONTROL_BATTARY_SAFTY_MODE_WRITE};
    }
    /**
     * @return Returns the battery voltage setpoint in bi mode from the cv control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlBattaryCvModeWrite() noexcept
    {
        return RegisterAddress{SI_CONTROL_BATTARY_CV_MODE_WRITE};
    }
    /**
     * @return Returns the dc low from the cv control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDcLowWrite() noexcept { return RegisterAddress{SI_CONTROL_DC_LOW_WRITE}; }
    /**
     * @return Returns the dc high from the cv control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDcHighWrite() noexcept { return RegisterAddress{SI_CONTROL_DC_HIGH_WRITE}; }
    /**
     * @return Returns the wind curve y 00 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY00Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_00_WRITE}; }
    /**
     * @return Returns the wind curve y 01 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY01Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_01_WRITE}; }
    /**
     * @return Returns the wind curve y 02 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY02Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_02_WRITE}; }
    /**
     * @return Returns the wind curve y 03 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY03Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_03_WRITE}; }
    /**
     * @return Returns the wind curve y 04 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY04Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_04_WRITE}; }
    /**
     * @return Returns the wind curve y 05 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY05Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_05_WRITE}; }
    /**
     * @return Returns the wind curve y 06 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY06Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_06_WRITE}; }
    /**
     * @return Returns the wind curve y 07 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY07Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_07_WRITE}; }
    /**
     * @return Returns the wind curve y 08 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY08Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_08_WRITE}; }
    /**
     * @return Returns the wind curve y 09 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY09Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_09_WRITE}; }
    /**
     * @return Returns the wind curve y 10 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY10Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_10_WRITE}; }
    /**
     * @return Returns the wind curve y 11 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY11Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_11_WRITE}; }
    /**
     * @return Returns the wind curve y 12 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY12Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_12_WRITE}; }
    /**
     * @return Returns the wind curve y 13 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY13Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_13_WRITE}; }
    /**
     * @return Returns the wind curve y 14 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY14Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_14_WRITE}; }
    /**
     * @return Returns the wind curve y 15 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlWindCurveY15Write() noexcept { return RegisterAddress{SI_CONTROL_WIND_CURVE_Y_15_WRITE}; }
    /**
     * @return Returns the constant voltage y 0 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY0Write() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE};
    }
    /**
     * @return Returns the constant voltage y 1 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY1Write() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE};
    }
    /**
     * @return Returns the constant voltage y 2 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY2Write() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE};
    }
    /**
     * @return Returns the dac curve y 0 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY0Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_0_READ}; }
    /**
     * @return Returns the dac curve y 1 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY1Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_1_READ}; }
    /**
     * @return Returns the dac curve y 2 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY2Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_2_READ}; }
    /**
     * @return Returns the dac curve y 3 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY3Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_3_READ}; }
    /**
     * @return Returns the dac curve y 4 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY4Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_4_READ}; }
    /**
     * @return Returns the dac curve y 5 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY5Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_5_READ}; }
    /**
     * @return Returns the dac curve y 6 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY6Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_6_READ}; }
    /**
     * @return Returns the dac curve y 7 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY7Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_7_READ}; }
    /**
     * @return Returns the dac curve y 8 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY8Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_8_READ}; }
    /**
     * @return Returns the dac curve y 9 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY9Read() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_9_READ}; }
    /**
     * @return Returns the constant voltage x 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageX0() noexcept { return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_X_0}; }
    /**
     * @return Returns the constant voltage x 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageX1() noexcept { return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_X_1}; }
    /**
     * @return Returns the constant voltage x 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageX2() noexcept { return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_X_2}; }
    /**
     * @return Returns the constant voltage y 0 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY0Read() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ};
    }
    /**
     * @return Returns the constant voltage y 1 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY1Read() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ};
    }
    /**
     * @return Returns the constant voltage y 2 from the si control model (read).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlConstantVoltageY2Read() noexcept
    {
        return RegisterAddress{SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ};
    }
    /**
     * @return Returns the dac curve x 0 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX0() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_0}; }
    /**
     * @return Returns the dac curve x 1 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX1() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_1}; }
    /**
     * @return Returns the dac curve x 2 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX2() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_2}; }
    /**
     * @return Returns the dac curve x 3 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX3() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_3}; }
    /**
     * @return Returns the dac curve x 4 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX4() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_4}; }
    /**
     * @return Returns the dac curve x 5 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX5() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_5}; }
    /**
     * @return Returns the dac curve x 6 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX6() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_6}; }
    /**
     * @return Returns the dac curve x 7 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX7() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_7}; }
    /**
     * @return Returns the dac curve x 8 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX8() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_8}; }
    /**
     * @return Returns the dac curve x 9 from the si control model.
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveX9() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_X_9}; }
    /**
     * @return Returns the dac curve y 0 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY0Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_0_WRITE}; }
    /**
     * @return Returns the dac curve y 1 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY1Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_1_WRITE}; }
    /**
     * @return Returns the dac curve y 2 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY2Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_2_WRITE}; }
    /**
     * @return Returns the dac curve y 3 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY3Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_3_WRITE}; }
    /**
     * @return Returns the dac curve y 4 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY4Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_4_WRITE}; }
    /**
     * @return Returns the dac curve y 5 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY5Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_5_WRITE}; }
    /**
     * @return Returns the dac curve y 6 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY6Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_6_WRITE}; }
    /**
     * @return Returns the dac curve y 7 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY7Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_7_WRITE}; }
    /**
     * @return Returns the dac curve y 8 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY8Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_8_WRITE}; }
    /**
     * @return Returns the dac curve y 9 from the si control model (write).
     */
    [[nodiscard]] constexpr static RegisterAddress siControlDacCurveY9Write() noexcept { return RegisterAddress{SI_CONTROL_DAC_CURVE_Y_9_WRITE}; }
    /**
     * @return Returns the invalid register.
     */
    [[nodiscard]] constexpr static RegisterAddress empty() noexcept { return RegisterAddress{EMPTY}; }
    /**
     * @param[in] other The other RegisterAddress.
     * @return Returns @b true if the two RegisterAddress objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const RegisterAddress& other) const = default;
    /**
     * @return Returns register as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if name of the manufacturer from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonManufacturer() const noexcept { return _value == COMMON_MANUFACTURER; }
    /**
     * @return Returns @b true if model name from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonModel() const noexcept { return _value == COMMON_MODEL; }
    /**
     * @return Returns @b true if version from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonVersion() const noexcept { return _value == COMMON_VERSION; }
    /**
     * @return Returns @b true if serial number from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonSerialNumber() const noexcept { return _value == COMMON_SERIAL_NUMBER; }
    /**
     * @return Returns @b true if device address from the common model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isCommonDeviceAddress() const noexcept { return _value == COMMON_DEVICE_ADDRESS; }
    /**
     * @return Returns @b true if device AC current on all phases from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmps() const noexcept { return _value == INVERTER_AMPS; }
    /**
     * @return Returns @b true if device AC current on phases a from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseA() const noexcept { return _value == INVERTER_AMPS_PHASE_A; }
    /**
     * @return Returns @b true if device AC current on phases b from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseB() const noexcept { return _value == INVERTER_AMPS_PHASE_B; }
    /**
     * @return Returns @b true if device AC current on phases c from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsPhaseC() const noexcept { return _value == INVERTER_AMPS_PHASE_C; }
    /**
     * @return Returns @b true if device AC current scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAmpsScaleFactor() const noexcept { return _value == INVERTER_AMPS_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC Voltage on phase a from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageA() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_A; }
    /**
     * @return Returns @b true if device AC Voltage on phase b from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageB() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_B; }
    /**
     * @return Returns @b true if device AC Voltage on phase c from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageC() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_C; }
    /**
     * @return Returns @b true if device AC Voltage scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPhaseVoltageScaleFactor() const noexcept { return _value == INVERTER_PHASE_VOLTAGE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcPower() const noexcept { return _value == INVERTER_AC_POWER; }
    /**
     * @return Returns @b true if device AC power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcPowerScaleFactor() const noexcept { return _value == INVERTER_AC_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device line frequency from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertz() const noexcept { return _value == INVERTER_HERTZ; }
    /**
     * @return Returns @b true if device line frequency scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterHertzScaleFactor() const noexcept { return _value == INVERTER_HERTZ_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC apparent power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcApparentPower() const noexcept { return _value == INVERTER_AC_APPARENT_POWER; }
    /**
     * @return Returns @b true if device AC apparent power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcApparentPowerScaleFactor() const noexcept { return _value == INVERTER_AC_APPARENT_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC reactive power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcReactivePower() const noexcept { return _value == INVERTER_AC_REACTIVE_POWER; }
    /**
     * @return Returns @b true if device AC reactive power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterAcReactivePowerScaleFactor() const noexcept { return _value == INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC power factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPowerFactor() const noexcept { return _value == INVERTER_POWER_FACTOR; }
    /**
     * @return Returns @b true if device AC power factor scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterPowerFactorScaleFactor() const noexcept { return _value == INVERTER_POWER_FACTOR_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device AC energy from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterWattHours() const noexcept { return _value == INVERTER_WATT_HOURS; }
    /**
     * @return Returns @b true if device AC energy scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterWattHoursScaleFactor() const noexcept { return _value == INVERTER_WATT_HOURS_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device DC voltage from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcVoltage() const noexcept { return _value == INVERTER_DC_VOLTAGE; }
    /**
     * @return Returns @b true if device DC voltage scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcVoltageScaleFactor() const noexcept { return _value == INVERTER_DC_VOLTAGE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device DC power from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcPower() const noexcept { return _value == INVERTER_DC_POWER; }
    /**
     * @return Returns @b true if device DC power scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterDcPowerScaleFactor() const noexcept { return _value == INVERTER_DC_POWER_SCALE_FACTOR; }
    /**
     * @return Returns @b true if device cabinet temperature from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterTemperature() const noexcept { return _value == INVERTER_TEMPERATURE; }
    /**
     * @return Returns @b true if device cabinet temperature scale factor from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterTemperatureScaleFactor() const noexcept { return _value == INVERTER_TEMPERATURE_SCALE_FACTOR; }
    /**
     * @return Returns @b true if operating state from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterOperatingState() const noexcept { return _value == INVERTER_OPERATING_STATE; }
    /**
     * @return Returns @b true if vendor operating state from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorOperatingState() const noexcept { return _value == INVERTER_VENDOR_OPERATING_STATE; }
    /**
     * @return Returns @b true if vendor event bitfield 1 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield1() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_1; }
    /**
     * @return Returns @b true if vendor event bitfield 2 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield2() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_2; }
    /**
     * @return Returns @b true if vendor event bitfield 3 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield3() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_3; }
    /**
     * @return Returns @b true if vendor event bitfield 4 from the inverter model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInverterVendorEventBitfield4() const noexcept { return _value == INVERTER_VENDOR_EVENT_BITFIELD_4; }
    /**
     * @return Returns @b true if der type from the nameplate model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isNameplateDerType() const noexcept { return _value == NAMEPLATE_DER_TYPE; }
    /**
     * @return Returns @b true if nominal power from the basic settings is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBasicSettingsMaxPower() const noexcept { return _value == BASIC_SETTINGS_MAX_POWER; }
    /**
     * @return Returns @b true if AC lifetime active (real) energy output from the extended mesurements model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isExtendedMesurementsAcWattHours() const noexcept { return _value == EXTENDED_MESUREMENTS_AC_WATT_HOURS; }
    /**
     * @return Returns @b true if AC lifetime active (real) energy charge from the extended mesurements model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isExtendedMesurementsAcLifetimeCharge() const noexcept { return _value == EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE; }
    /**
     * @return Returns @b true if nominal charge power from the storage model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isStorageNominalChargePower() const noexcept { return _value == STORAGE_NOMINAL_CHARGE_POWER; }
    /**
     * @return Returns @b true if modus from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlModus() const noexcept { return _value == SI_CONTROL_MODUS; }
    /**
     * @return Returns @b true if u min from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlUMinRead() const noexcept { return _value == SI_CONTROL_U_MIN_READ; }
    /**
     * @return Returns @b true if u max from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlUMaxRead() const noexcept { return _value == SI_CONTROL_U_MAX_READ; }
    /**
     * @return Returns @b true if start voltage from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlVoltageDcStartRead() const noexcept { return _value == SI_CONTROL_VOLTAGE_DC_START_READ; }
    /**
     * @return Returns @b true if battery voltage setpoint in bi mode from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattaryBiModeRead() const noexcept { return _value == SI_CONTROL_BATTARY_BI_MODE_READ; }
    /**
     * @return Returns @b true if battery voltage setpoint in bi mode from the safty control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattarySaftyModeRead() const noexcept { return _value == SI_CONTROL_BATTARY_SAFTY_MODE_READ; }
    /**
     * @return Returns @b true if battery voltage setpoint in cv mode from the safty control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattaryCvModeRead() const noexcept { return _value == SI_CONTROL_BATTARY_CV_MODE_READ; }
    /**
     * @return Returns @b true if low voltage for relay off from the safty control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDcLowRead() const noexcept { return _value == SI_CONTROL_DC_LOW_READ; }
    /**
     * @return Returns @b true if high voltage for relay off from the safty control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDcHighRead() const noexcept { return _value == SI_CONTROL_DC_HIGH_READ; }
    /**
     * @return Returns @b true if strategy switch for behavior in safety mode from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlTrackingSelection() const noexcept { return _value == SI_CONTROL_TRACKING_SELECTION; }
    /**
     * @return Returns @b true if start countdown from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlStartCountdown() const noexcept { return _value == SI_CONTROL_START_COUNTDOWN; }
    /**
     * @return Returns @b true if night shutdown from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlNightShutdown() const noexcept { return _value == SI_CONTROL_NIGHT_SHUTDOWN; }
    /**
     * @return Returns @b true if pmax from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlPmax() const noexcept { return _value == SI_CONTROL_PMAX; }
    /**
     * @return Returns @b true if cosphi from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlCosphi() const noexcept { return _value == SI_CONTROL_COSPHI; }
    /**
     * @return Returns @b true if uptime from the safty control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlUptime() const noexcept { return _value == SI_CONTROL_UPTIME; }
    /**
     * @return Returns @b true if mpp step dac 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepDac0() const noexcept { return _value == SI_CONTROL_MPP_STEP_DAC_0; }
    /**
     * @return Returns @b true if mpp step dac 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepDac1() const noexcept { return _value == SI_CONTROL_MPP_STEP_DAC_1; }
    /**
     * @return Returns @b true if mpp step dac 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepDac2() const noexcept { return _value == SI_CONTROL_MPP_STEP_DAC_2; }
    /**
     * @return Returns @b true if mpp step dac 3 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepDac3() const noexcept { return _value == SI_CONTROL_MPP_STEP_DAC_3; }
    /**
     * @return Returns @b true if mpp step udc 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepUdc0() const noexcept { return _value == SI_CONTROL_MPP_STEP_UDC_0; }
    /**
     * @return Returns @b true if mpp step udc 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepUdc1() const noexcept { return _value == SI_CONTROL_MPP_STEP_UDC_1; }
    /**
     * @return Returns @b true if mpp step udc 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepUdc2() const noexcept { return _value == SI_CONTROL_MPP_STEP_UDC_2; }
    /**
     * @return Returns @b true if mpp step udc 3 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppStepUdc3() const noexcept { return _value == SI_CONTROL_MPP_STEP_UDC_3; }
    /**
     * @return Returns @b true if mpp sample dac 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleDac0() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_DAC_0; }
    /**
     * @return Returns @b true if mpp sample dac 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleDac1() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_DAC_1; }
    /**
     * @return Returns @b true if mpp sample dac 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleDac2() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_DAC_2; }
    /**
     * @return Returns @b true if mpp sample dac 3 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleDac3() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_DAC_3; }
    /**
     * @return Returns @b true if mpp sample udc 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleUdc0() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_UDC_0; }
    /**
     * @return Returns @b true if mpp sample udc 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleUdc1() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_UDC_1; }
    /**
     * @return Returns @b true if mpp sample udc 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleUdc2() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_UDC_2; }
    /**
     * @return Returns @b true if mpp sample udc 3 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlMppSampleUdc3() const noexcept { return _value == SI_CONTROL_MPP_SAMPLE_UDC_3; }
    /**
     * @return Returns @b true if reduction from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlReduction() const noexcept { return _value == SI_CONTROL_REDUCTION; }
    /**
     * @return Returns @b true if sineduty from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlSineduty() const noexcept { return _value == SI_CONTROL_SINEDUTY; }
    /**
     * @return Returns @b true if filter wind curve from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlFilterWindCurve() const noexcept { return _value == SI_CONTROL_FILTER_WIND_CURVE; }
    /**
     * @return Returns @b true if wind curve x 00 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX00() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_00; }
    /**
     * @return Returns @b true if wind curve x 01 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX01() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_01; }
    /**
     * @return Returns @b true if wind curve x 02 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX02() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_02; }
    /**
     * @return Returns @b true if wind curve x 03 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX03() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_03; }
    /**
     * @return Returns @b true if wind curve x 04 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX04() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_04; }
    /**
     * @return Returns @b true if wind curve x 05 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX05() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_05; }
    /**
     * @return Returns @b true if wind curve x 06 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX06() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_06; }
    /**
     * @return Returns @b true if wind curve x 07 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX07() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_07; }
    /**
     * @return Returns @b true if wind curve x 08 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX08() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_08; }
    /**
     * @return Returns @b true if wind curve x 09 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX09() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_09; }
    /**
     * @return Returns @b true if wind curve x 10 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX10() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_10; }
    /**
     * @return Returns @b true if wind curve x 11 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX11() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_11; }
    /**
     * @return Returns @b true if wind curve x 12 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX12() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_12; }
    /**
     * @return Returns @b true if wind curve x 13 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX13() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_13; }
    /**
     * @return Returns @b true if wind curve x 14 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX14() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_14; }
    /**
     * @return Returns @b true if wind curve x 15 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveX15() const noexcept { return _value == SI_CONTROL_WIND_CURVE_X_15; }
    /**
     * @return Returns @b true if wind curve y 00 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY00Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_00_READ; }
    /**
     * @return Returns @b true if wind curve y 01 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY01Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_01_READ; }
    /**
     * @return Returns @b true if wind curve y 02 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY02Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_02_READ; }
    /**
     * @return Returns @b true if wind curve y 03 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY03Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_03_READ; }
    /**
     * @return Returns @b true if wind curve y 04 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY04Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_04_READ; }
    /**
     * @return Returns @b true if wind curve y 05 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY05Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_05_READ; }
    /**
     * @return Returns @b true if wind curve y 06 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY06Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_06_READ; }
    /**
     * @return Returns @b true if wind curve y 07 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY07Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_07_READ; }
    /**
     * @return Returns @b true if wind curve y 08 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY08Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_08_READ; }
    /**
     * @return Returns @b true if wind curve y 09 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY09Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_09_READ; }
    /**
     * @return Returns @b true if wind curve y 10 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY10Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_10_READ; }
    /**
     * @return Returns @b true if wind curve y 11 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY11Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_11_READ; }
    /**
     * @return Returns @b true if wind curve y 12 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY12Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_12_READ; }
    /**
     * @return Returns @b true if wind curve y 13 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY13Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_13_READ; }
    /**
     * @return Returns @b true if wind curve y 14 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY14Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_14_READ; }
    /**
     * @return Returns @b true if wind curve y 15 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY15Read() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_15_READ; }
    /**
     * @return Returns @b true if solar battery filter step from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlSolarBatteryFilterStep() const noexcept { return _value == SI_CONTROL_SOLAR_BATTERY_FILTER_STEP; }
    /**
     * @return Returns @b true if power limit for safty mode from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlPowerLimitSaftyMode() const noexcept { return _value == SI_CONTROL_POWER_LIMIT_SAFTY_MODE; }
    /**
     * @return Returns @b true if u min from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlUMaxWrite() const noexcept { return _value == SI_CONTROL_U_MAX_WRITE; }
    /**
     * @return Returns @b true if u max from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlUMinWrite() const noexcept { return _value == SI_CONTROL_U_MIN_WRITE; }
    /**
     * @return Returns @b true if start voltage from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlVoltageDcStartWrite() const noexcept { return _value == SI_CONTROL_VOLTAGE_DC_START_WRITE; }
    /**
     * @return Returns @b true if battery voltage setpoint in bi mode from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattaryBiModeWrite() const noexcept { return _value == SI_CONTROL_BATTARY_BI_MODE_WRITE; }
    /**
     * @return Returns @b true if battery voltage setpoint in bi mode from the safty control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattarySaftyModeWrite() const noexcept { return _value == SI_CONTROL_BATTARY_SAFTY_MODE_WRITE; }
    /**
     * @return Returns @b true if battery voltage setpoint in bi mode from the cv control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlBattaryCvModeWrite() const noexcept { return _value == SI_CONTROL_BATTARY_CV_MODE_WRITE; }
    /**
     * @return Returns @b true if dc low from the cv control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDcLowWrite() const noexcept { return _value == SI_CONTROL_DC_LOW_WRITE; }
    /**
     * @return Returns @b true if dc high from the cv control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDcHighWrite() const noexcept { return _value == SI_CONTROL_DC_HIGH_WRITE; }
    /**
     * @return Returns @b true if wind curve y 00 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY00Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_00_WRITE; }
    /**
     * @return Returns @b true if wind curve y 01 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY01Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_01_WRITE; }
    /**
     * @return Returns @b true if wind curve y 02 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY02Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_02_WRITE; }
    /**
     * @return Returns @b true if wind curve y 03 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY03Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_03_WRITE; }
    /**
     * @return Returns @b true if wind curve y 04 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY04Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_04_WRITE; }
    /**
     * @return Returns @b true if wind curve y 05 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY05Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_05_WRITE; }
    /**
     * @return Returns @b true if wind curve y 06 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY06Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_06_WRITE; }
    /**
     * @return Returns @b true if wind curve y 07 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY07Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_07_WRITE; }
    /**
     * @return Returns @b true if wind curve y 08 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY08Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_08_WRITE; }
    /**
     * @return Returns @b true if wind curve y 09 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY09Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_09_WRITE; }
    /**
     * @return Returns @b true if wind curve y 10 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY10Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_10_WRITE; }
    /**
     * @return Returns @b true if wind curve y 11 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY11Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_11_WRITE; }
    /**
     * @return Returns @b true if wind curve y 12 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY12Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_12_WRITE; }
    /**
     * @return Returns @b true if wind curve y 13 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY13Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_13_WRITE; }
    /**
     * @return Returns @b true if wind curve y 14 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY14Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_14_WRITE; }
    /**
     * @return Returns @b true if wind curve y 15 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlWindCurveY15Write() const noexcept { return _value == SI_CONTROL_WIND_CURVE_Y_15_WRITE; }
    /**
     * @return Returns @b true if constant voltage y 0 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY0Write() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE; }
    /**
     * @return Returns @b true if constant voltage y 1 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY1Write() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE; }
    /**
     * @return Returns @b true if constant voltage y 2 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY2Write() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE; }
    /**
     * @return Returns @b true if dac curve y 0 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY0Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_0_READ; }
    /**
     * @return Returns @b true if dac curve y 1 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY1Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_1_READ; }
    /**
     * @return Returns @b true if dac curve y 2 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY2Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_2_READ; }
    /**
     * @return Returns @b true if dac curve y 3 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY3Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_3_READ; }
    /**
     * @return Returns @b true if dac curve y 4 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY4Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_4_READ; }
    /**
     * @return Returns @b true if dac curve y 5 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY5Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_5_READ; }
    /**
     * @return Returns @b true if dac curve y 6 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY6Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_6_READ; }
    /**
     * @return Returns @b true if dac curve y 7 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY7Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_7_READ; }
    /**
     * @return Returns @b true if dac curve y 8 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY8Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_8_READ; }
    /**
     * @return Returns @b true if dac curve y 9 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY9Read() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_9_READ; }
    /**
     * @return Returns @b true if constant voltage x 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageX0() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_X_0; }
    /**
     * @return Returns @b true if constant voltage x 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageX1() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_X_1; }
    /**
     * @return Returns @b true if constant voltage x 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageX2() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_X_2; }
    /**
     * @return Returns @b true if constant voltage y 0 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY0Read() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ; }
    /**
     * @return Returns @b true if constant voltage y 1 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY1Read() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ; }
    /**
     * @return Returns @b true if constant voltage y 2 from the si control model (read) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlConstantVoltageY2Read() const noexcept { return _value == SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ; }
    /**
     * @return Returns @b true if dac curve x 0 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX0() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_0; }
    /**
     * @return Returns @b true if dac curve x 1 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX1() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_1; }
    /**
     * @return Returns @b true if dac curve x 2 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX2() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_2; }
    /**
     * @return Returns @b true if dac curve x 3 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX3() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_3; }
    /**
     * @return Returns @b true if dac curve x 4 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX4() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_4; }
    /**
     * @return Returns @b true if dac curve x 5 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX5() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_5; }
    /**
     * @return Returns @b true if dac curve x 6 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX6() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_6; }
    /**
     * @return Returns @b true if dac curve x 7 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX7() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_7; }
    /**
     * @return Returns @b true if dac curve x 8 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX8() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_8; }
    /**
     * @return Returns @b true if dac curve x 9 from the si control model is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveX9() const noexcept { return _value == SI_CONTROL_DAC_CURVE_X_9; }
    /**
     * @return Returns @b true if dac curve y 0 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY0Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_0_WRITE; }
    /**
     * @return Returns @b true if dac curve y 1 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY1Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_1_WRITE; }
    /**
     * @return Returns @b true if dac curve y 2 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY2Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_2_WRITE; }
    /**
     * @return Returns @b true if dac curve y 3 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY3Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_3_WRITE; }
    /**
     * @return Returns @b true if dac curve y 4 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY4Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_4_WRITE; }
    /**
     * @return Returns @b true if dac curve y 5 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY5Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_5_WRITE; }
    /**
     * @return Returns @b true if dac curve y 6 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY6Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_6_WRITE; }
    /**
     * @return Returns @b true if dac curve y 7 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY7Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_7_WRITE; }
    /**
     * @return Returns @b true if dac curve y 8 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY8Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_8_WRITE; }
    /**
     * @return Returns @b true if dac curve y 9 from the si control model (write) is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSiControlDacCurveY9Write() const noexcept { return _value == SI_CONTROL_DAC_CURVE_Y_9_WRITE; }
    /**
     * @return Returns @b true if invalid register is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Register in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"COMMON_MANUFACTURER",
                                                                      "COMMON_MODEL",
                                                                      "COMMON_VERSION",
                                                                      "COMMON_SERIAL_NUMBER",
                                                                      "COMMON_DEVICE_ADDRESS",
                                                                      "INVERTER_AMPS",
                                                                      "INVERTER_AMPS_PHASE_A",
                                                                      "INVERTER_AMPS_PHASE_B",
                                                                      "INVERTER_AMPS_PHASE_C",
                                                                      "INVERTER_AMPS_SCALE_FACTOR",
                                                                      "INVERTER_PHASE_VOLTAGE_A",
                                                                      "INVERTER_PHASE_VOLTAGE_B",
                                                                      "INVERTER_PHASE_VOLTAGE_C",
                                                                      "INVERTER_PHASE_VOLTAGE_SCALE_FACTOR",
                                                                      "INVERTER_AC_POWER",
                                                                      "INVERTER_AC_POWER_SCALE_FACTOR",
                                                                      "INVERTER_HERTZ",
                                                                      "INVERTER_HERTZ_SCALE_FACTOR",
                                                                      "INVERTER_AC_APPARENT_POWER",
                                                                      "INVERTER_AC_APPARENT_POWER_SCALE_FACTOR",
                                                                      "INVERTER_AC_REACTIVE_POWER",
                                                                      "INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR",
                                                                      "INVERTER_POWER_FACTOR",
                                                                      "INVERTER_POWER_FACTOR_SCALE_FACTOR",
                                                                      "INVERTER_WATT_HOURS",
                                                                      "INVERTER_WATT_HOURS_SCALE_FACTOR",
                                                                      "INVERTER_DC_VOLTAGE",
                                                                      "INVERTER_DC_VOLTAGE_SCALE_FACTOR",
                                                                      "INVERTER_DC_POWER",
                                                                      "INVERTER_DC_POWER_SCALE_FACTOR",
                                                                      "INVERTER_TEMPERATURE",
                                                                      "INVERTER_TEMPERATURE_SCALE_FACTOR",
                                                                      "INVERTER_OPERATING_STATE",
                                                                      "INVERTER_VENDOR_OPERATING_STATE",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_1",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_2",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_3",
                                                                      "INVERTER_VENDOR_EVENT_BITFIELD_4",
                                                                      "NAMEPLATE_DER_TYPE",
                                                                      "BASIC_SETTINGS_MAX_POWER",
                                                                      "EXTENDED_MESUREMENTS_AC_WATT_HOURS",
                                                                      "EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE",
                                                                      "STORAGE_NOMINAL_CHARGE_POWER",
                                                                      "SI_CONTROL_MODUS",
                                                                      "SI_CONTROL_U_MIN_READ",
                                                                      "SI_CONTROL_U_MAX_READ",
                                                                      "SI_CONTROL_VOLTAGE_DC_START_READ",
                                                                      "SI_CONTROL_BATTARY_BI_MODE_READ",
                                                                      "SI_CONTROL_BATTARY_SAFTY_MODE_READ",
                                                                      "SI_CONTROL_BATTARY_CV_MODE_READ",
                                                                      "SI_CONTROL_DC_LOW_READ",
                                                                      "SI_CONTROL_DC_HIGH_READ",
                                                                      "SI_CONTROL_TRACKING_SELECTION",
                                                                      "SI_CONTROL_START_COUNTDOWN",
                                                                      "SI_CONTROL_NIGHT_SHUTDOWN",
                                                                      "SI_CONTROL_PMAX",
                                                                      "SI_CONTROL_COSPHI",
                                                                      "SI_CONTROL_UPTIME",
                                                                      "SI_CONTROL_MPP_STEP_DAC_0",
                                                                      "SI_CONTROL_MPP_STEP_DAC_1",
                                                                      "SI_CONTROL_MPP_STEP_DAC_2",
                                                                      "SI_CONTROL_MPP_STEP_DAC_3",
                                                                      "SI_CONTROL_MPP_STEP_UDC_0",
                                                                      "SI_CONTROL_MPP_STEP_UDC_1",
                                                                      "SI_CONTROL_MPP_STEP_UDC_2",
                                                                      "SI_CONTROL_MPP_STEP_UDC_3",
                                                                      "SI_CONTROL_MPP_SAMPLE_DAC_0",
                                                                      "SI_CONTROL_MPP_SAMPLE_DAC_1",
                                                                      "SI_CONTROL_MPP_SAMPLE_DAC_2",
                                                                      "SI_CONTROL_MPP_SAMPLE_DAC_3",
                                                                      "SI_CONTROL_MPP_SAMPLE_UDC_0",
                                                                      "SI_CONTROL_MPP_SAMPLE_UDC_1",
                                                                      "SI_CONTROL_MPP_SAMPLE_UDC_2",
                                                                      "SI_CONTROL_MPP_SAMPLE_UDC_3",
                                                                      "SI_CONTROL_REDUCTION",
                                                                      "SI_CONTROL_SINEDUTY",
                                                                      "SI_CONTROL_FILTER_WIND_CURVE",
                                                                      "SI_CONTROL_WIND_CURVE_X_00",
                                                                      "SI_CONTROL_WIND_CURVE_X_01",
                                                                      "SI_CONTROL_WIND_CURVE_X_02",
                                                                      "SI_CONTROL_WIND_CURVE_X_03",
                                                                      "SI_CONTROL_WIND_CURVE_X_04",
                                                                      "SI_CONTROL_WIND_CURVE_X_05",
                                                                      "SI_CONTROL_WIND_CURVE_X_06",
                                                                      "SI_CONTROL_WIND_CURVE_X_07",
                                                                      "SI_CONTROL_WIND_CURVE_X_08",
                                                                      "SI_CONTROL_WIND_CURVE_X_09",
                                                                      "SI_CONTROL_WIND_CURVE_X_10",
                                                                      "SI_CONTROL_WIND_CURVE_X_11",
                                                                      "SI_CONTROL_WIND_CURVE_X_12",
                                                                      "SI_CONTROL_WIND_CURVE_X_13",
                                                                      "SI_CONTROL_WIND_CURVE_X_14",
                                                                      "SI_CONTROL_WIND_CURVE_X_15",
                                                                      "SI_CONTROL_WIND_CURVE_Y_00_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_01_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_02_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_03_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_04_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_05_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_06_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_07_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_08_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_09_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_10_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_11_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_12_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_13_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_14_READ",
                                                                      "SI_CONTROL_WIND_CURVE_Y_15_READ",
                                                                      "SI_CONTROL_SOLAR_BATTERY_FILTER_STEP",
                                                                      "SI_CONTROL_POWER_LIMIT_SAFTY_MODE",
                                                                      "SI_CONTROL_U_MAX_WRITE",
                                                                      "SI_CONTROL_U_MIN_WRITE",
                                                                      "SI_CONTROL_VOLTAGE_DC_START_WRITE",
                                                                      "SI_CONTROL_BATTARY_BI_MODE_WRITE",
                                                                      "SI_CONTROL_BATTARY_SAFTY_MODE_WRITE",
                                                                      "SI_CONTROL_BATTARY_CV_MODE_WRITE",
                                                                      "SI_CONTROL_DC_LOW_WRITE",
                                                                      "SI_CONTROL_DC_HIGH_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_00_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_01_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_02_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_03_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_04_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_05_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_06_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_07_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_08_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_09_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_10_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_11_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_12_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_13_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_14_WRITE",
                                                                      "SI_CONTROL_WIND_CURVE_Y_15_WRITE",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_0_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_1_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_2_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_3_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_4_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_5_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_6_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_7_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_8_READ",
                                                                      "SI_CONTROL_DAC_CURVE_Y_9_READ",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_X_0",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_X_1",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_X_2",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ",
                                                                      "SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ",
                                                                      "SI_CONTROL_DAC_CURVE_X_0",
                                                                      "SI_CONTROL_DAC_CURVE_X_1",
                                                                      "SI_CONTROL_DAC_CURVE_X_2",
                                                                      "SI_CONTROL_DAC_CURVE_X_3",
                                                                      "SI_CONTROL_DAC_CURVE_X_4",
                                                                      "SI_CONTROL_DAC_CURVE_X_5",
                                                                      "SI_CONTROL_DAC_CURVE_X_6",
                                                                      "SI_CONTROL_DAC_CURVE_X_7",
                                                                      "SI_CONTROL_DAC_CURVE_X_8",
                                                                      "SI_CONTROL_DAC_CURVE_X_9",
                                                                      "SI_CONTROL_DAC_CURVE_Y_0_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_1_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_2_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_3_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_4_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_5_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_6_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_7_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_8_WRITE",
                                                                      "SI_CONTROL_DAC_CURVE_Y_9_WRITE"};

    /**
     *@return Returns the address of the register.
     */
    constexpr std::uint16_t raw() const noexcept
    {
        switch (_value)
        {
            case COMMON_MANUFACTURER:
                return std::uint16_t(40004);
            case COMMON_MODEL:
                return std::uint16_t(40020);
            case COMMON_VERSION:
                return std::uint16_t(40044);
            case COMMON_SERIAL_NUMBER:
                return std::uint16_t(40052);
            case COMMON_DEVICE_ADDRESS:
                return std::uint16_t(40068);
            case INVERTER_AMPS:
                return std::uint16_t(40072);
            case INVERTER_AMPS_PHASE_A:
                return std::uint16_t(40073);
            case INVERTER_AMPS_PHASE_B:
                return std::uint16_t(40074);
            case INVERTER_AMPS_PHASE_C:
                return std::uint16_t(40075);
            case INVERTER_AMPS_SCALE_FACTOR:
                return std::uint16_t(40076);
            case INVERTER_PHASE_VOLTAGE_A:
                return std::uint16_t(40080);
            case INVERTER_PHASE_VOLTAGE_B:
                return std::uint16_t(40081);
            case INVERTER_PHASE_VOLTAGE_C:
                return std::uint16_t(40082);
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR:
                return std::uint16_t(40083);
            case INVERTER_AC_POWER:
                return std::uint16_t(40084);
            case INVERTER_AC_POWER_SCALE_FACTOR:
                return std::uint16_t(40085);
            case INVERTER_HERTZ:
                return std::uint16_t(40086);
            case INVERTER_HERTZ_SCALE_FACTOR:
                return std::uint16_t(40087);
            case INVERTER_AC_APPARENT_POWER:
                return std::uint16_t(40088);
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR:
                return std::uint16_t(40089);
            case INVERTER_AC_REACTIVE_POWER:
                return std::uint16_t(40090);
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR:
                return std::uint16_t(40091);
            case INVERTER_POWER_FACTOR:
                return std::uint16_t(40092);
            case INVERTER_POWER_FACTOR_SCALE_FACTOR:
                return std::uint16_t(40093);
            case INVERTER_WATT_HOURS:
                return std::uint16_t(40094);
            case INVERTER_WATT_HOURS_SCALE_FACTOR:
                return std::uint16_t(40096);
            case INVERTER_DC_VOLTAGE:
                return std::uint16_t(40099);
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR:
                return std::uint16_t(40100);
            case INVERTER_DC_POWER:
                return std::uint16_t(40101);
            case INVERTER_DC_POWER_SCALE_FACTOR:
                return std::uint16_t(40102);
            case INVERTER_TEMPERATURE:
                return std::uint16_t(40103);
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return std::uint16_t(40107);
            case INVERTER_OPERATING_STATE:
                return std::uint16_t(40108);
            case INVERTER_VENDOR_OPERATING_STATE:
                return std::uint16_t(40109);
            case INVERTER_VENDOR_EVENT_BITFIELD_1:
                return std::uint16_t(40110);
            case INVERTER_VENDOR_EVENT_BITFIELD_2:
                return std::uint16_t(40112);
            case INVERTER_VENDOR_EVENT_BITFIELD_3:
                return std::uint16_t(40114);
            case INVERTER_VENDOR_EVENT_BITFIELD_4:
                return std::uint16_t(40116);
            case NAMEPLATE_DER_TYPE:
                return std::uint16_t(40124);
            case BASIC_SETTINGS_MAX_POWER:
                return std::uint16_t(40152);
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
                return std::uint16_t(40187);
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE:
                return std::uint16_t(40203);
            case STORAGE_NOMINAL_CHARGE_POWER:
                return std::uint16_t(40256);
            case SI_CONTROL_MODUS:
                return std::uint16_t(40282);
            case SI_CONTROL_U_MIN_READ:
                return std::uint16_t(40286);
            case SI_CONTROL_U_MAX_READ:
                return std::uint16_t(40287);
            case SI_CONTROL_VOLTAGE_DC_START_READ:
                return std::uint16_t(40291);
            case SI_CONTROL_BATTARY_BI_MODE_READ:
                return std::uint16_t(40294);
            case SI_CONTROL_BATTARY_SAFTY_MODE_READ:
                return std::uint16_t(40295);
            case SI_CONTROL_BATTARY_CV_MODE_READ:
                return std::uint16_t(40296);
            case SI_CONTROL_DC_LOW_READ:
                return std::uint16_t(40297);
            case SI_CONTROL_DC_HIGH_READ:
                return std::uint16_t(40298);
            case SI_CONTROL_TRACKING_SELECTION:
                return std::uint16_t(40331);
            case SI_CONTROL_START_COUNTDOWN:
                return std::uint16_t(40334);
            case SI_CONTROL_NIGHT_SHUTDOWN:
                return std::uint16_t(40335);
            case SI_CONTROL_PMAX:
                return std::uint16_t(40336);
            case SI_CONTROL_COSPHI:
                return std::uint16_t(40337);
            case SI_CONTROL_UPTIME:
                return std::uint16_t(40338);
            case SI_CONTROL_MPP_STEP_DAC_0:
                return std::uint16_t(40340);
            case SI_CONTROL_MPP_STEP_DAC_1:
                return std::uint16_t(40341);
            case SI_CONTROL_MPP_STEP_DAC_2:
                return std::uint16_t(40342);
            case SI_CONTROL_MPP_STEP_DAC_3:
                return std::uint16_t(40343);
            case SI_CONTROL_MPP_STEP_UDC_0:
                return std::uint16_t(40344);
            case SI_CONTROL_MPP_STEP_UDC_1:
                return std::uint16_t(40345);
            case SI_CONTROL_MPP_STEP_UDC_2:
                return std::uint16_t(40346);
            case SI_CONTROL_MPP_STEP_UDC_3:
                return std::uint16_t(40347);
            case SI_CONTROL_MPP_SAMPLE_DAC_0:
                return std::uint16_t(40348);
            case SI_CONTROL_MPP_SAMPLE_DAC_1:
                return std::uint16_t(40349);
            case SI_CONTROL_MPP_SAMPLE_DAC_2:
                return std::uint16_t(40350);
            case SI_CONTROL_MPP_SAMPLE_DAC_3:
                return std::uint16_t(40351);
            case SI_CONTROL_MPP_SAMPLE_UDC_0:
                return std::uint16_t(40352);
            case SI_CONTROL_MPP_SAMPLE_UDC_1:
                return std::uint16_t(40353);
            case SI_CONTROL_MPP_SAMPLE_UDC_2:
                return std::uint16_t(40354);
            case SI_CONTROL_MPP_SAMPLE_UDC_3:
                return std::uint16_t(40355);
            case SI_CONTROL_REDUCTION:
                return std::uint16_t(40356);
            case SI_CONTROL_SINEDUTY:
                return std::uint16_t(40357);
            case SI_CONTROL_FILTER_WIND_CURVE:
                return std::uint16_t(40360);
            case SI_CONTROL_WIND_CURVE_X_00:
                return std::uint16_t(40361);
            case SI_CONTROL_WIND_CURVE_X_01:
                return std::uint16_t(40362);
            case SI_CONTROL_WIND_CURVE_X_02:
                return std::uint16_t(40363);
            case SI_CONTROL_WIND_CURVE_X_03:
                return std::uint16_t(40364);
            case SI_CONTROL_WIND_CURVE_X_04:
                return std::uint16_t(40365);
            case SI_CONTROL_WIND_CURVE_X_05:
                return std::uint16_t(40366);
            case SI_CONTROL_WIND_CURVE_X_06:
                return std::uint16_t(40367);
            case SI_CONTROL_WIND_CURVE_X_07:
                return std::uint16_t(40368);
            case SI_CONTROL_WIND_CURVE_X_08:
                return std::uint16_t(40369);
            case SI_CONTROL_WIND_CURVE_X_09:
                return std::uint16_t(40370);
            case SI_CONTROL_WIND_CURVE_X_10:
                return std::uint16_t(40371);
            case SI_CONTROL_WIND_CURVE_X_11:
                return std::uint16_t(40372);
            case SI_CONTROL_WIND_CURVE_X_12:
                return std::uint16_t(40373);
            case SI_CONTROL_WIND_CURVE_X_13:
                return std::uint16_t(40374);
            case SI_CONTROL_WIND_CURVE_X_14:
                return std::uint16_t(40375);
            case SI_CONTROL_WIND_CURVE_X_15:
                return std::uint16_t(40376);
            case SI_CONTROL_WIND_CURVE_Y_00_READ:
                return std::uint16_t(40377);
            case SI_CONTROL_WIND_CURVE_Y_01_READ:
                return std::uint16_t(40378);
            case SI_CONTROL_WIND_CURVE_Y_02_READ:
                return std::uint16_t(40379);
            case SI_CONTROL_WIND_CURVE_Y_03_READ:
                return std::uint16_t(40380);
            case SI_CONTROL_WIND_CURVE_Y_04_READ:
                return std::uint16_t(40381);
            case SI_CONTROL_WIND_CURVE_Y_05_READ:
                return std::uint16_t(40382);
            case SI_CONTROL_WIND_CURVE_Y_06_READ:
                return std::uint16_t(40383);
            case SI_CONTROL_WIND_CURVE_Y_07_READ:
                return std::uint16_t(40384);
            case SI_CONTROL_WIND_CURVE_Y_08_READ:
                return std::uint16_t(40385);
            case SI_CONTROL_WIND_CURVE_Y_09_READ:
                return std::uint16_t(40386);
            case SI_CONTROL_WIND_CURVE_Y_10_READ:
                return std::uint16_t(40387);
            case SI_CONTROL_WIND_CURVE_Y_11_READ:
                return std::uint16_t(40388);
            case SI_CONTROL_WIND_CURVE_Y_12_READ:
                return std::uint16_t(40389);
            case SI_CONTROL_WIND_CURVE_Y_13_READ:
                return std::uint16_t(40390);
            case SI_CONTROL_WIND_CURVE_Y_14_READ:
                return std::uint16_t(40391);
            case SI_CONTROL_WIND_CURVE_Y_15_READ:
                return std::uint16_t(40392);
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP:
                return std::uint16_t(40394);
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE:
                return std::uint16_t(40399);
            case SI_CONTROL_U_MIN_WRITE:
                return std::uint16_t(40401);
            case SI_CONTROL_U_MAX_WRITE:
                return std::uint16_t(40402);
            case SI_CONTROL_VOLTAGE_DC_START_WRITE:
                return std::uint16_t(40403);
            case SI_CONTROL_BATTARY_BI_MODE_WRITE:
                return std::uint16_t(40404);
            case SI_CONTROL_BATTARY_SAFTY_MODE_WRITE:
                return std::uint16_t(40405);
            case SI_CONTROL_BATTARY_CV_MODE_WRITE:
                return std::uint16_t(40406);
            case SI_CONTROL_DC_LOW_WRITE:
                return std::uint16_t(40407);
            case SI_CONTROL_DC_HIGH_WRITE:
                return std::uint16_t(40408);
            case SI_CONTROL_WIND_CURVE_Y_00_WRITE:
                return std::uint16_t(40410);
            case SI_CONTROL_WIND_CURVE_Y_01_WRITE:
                return std::uint16_t(40411);
            case SI_CONTROL_WIND_CURVE_Y_02_WRITE:
                return std::uint16_t(40412);
            case SI_CONTROL_WIND_CURVE_Y_03_WRITE:
                return std::uint16_t(40413);
            case SI_CONTROL_WIND_CURVE_Y_04_WRITE:
                return std::uint16_t(40414);
            case SI_CONTROL_WIND_CURVE_Y_05_WRITE:
                return std::uint16_t(40415);
            case SI_CONTROL_WIND_CURVE_Y_06_WRITE:
                return std::uint16_t(40416);
            case SI_CONTROL_WIND_CURVE_Y_07_WRITE:
                return std::uint16_t(40417);
            case SI_CONTROL_WIND_CURVE_Y_08_WRITE:
                return std::uint16_t(40418);
            case SI_CONTROL_WIND_CURVE_Y_09_WRITE:
                return std::uint16_t(40419);
            case SI_CONTROL_WIND_CURVE_Y_10_WRITE:
                return std::uint16_t(40420);
            case SI_CONTROL_WIND_CURVE_Y_11_WRITE:
                return std::uint16_t(40421);
            case SI_CONTROL_WIND_CURVE_Y_12_WRITE:
                return std::uint16_t(40422);
            case SI_CONTROL_WIND_CURVE_Y_13_WRITE:
                return std::uint16_t(40423);
            case SI_CONTROL_WIND_CURVE_Y_14_WRITE:
                return std::uint16_t(40424);
            case SI_CONTROL_WIND_CURVE_Y_15_WRITE:
                return std::uint16_t(40425);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE:
                return std::uint16_t(40430);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE:
                return std::uint16_t(40431);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE:
                return std::uint16_t(40432);
            case SI_CONTROL_DAC_CURVE_Y_0_READ:
                return std::uint16_t(40433);
            case SI_CONTROL_DAC_CURVE_Y_1_READ:
                return std::uint16_t(40434);
            case SI_CONTROL_DAC_CURVE_Y_2_READ:
                return std::uint16_t(40435);
            case SI_CONTROL_DAC_CURVE_Y_3_READ:
                return std::uint16_t(40436);
            case SI_CONTROL_DAC_CURVE_Y_4_READ:
                return std::uint16_t(40437);
            case SI_CONTROL_DAC_CURVE_Y_5_READ:
                return std::uint16_t(40438);
            case SI_CONTROL_DAC_CURVE_Y_6_READ:
                return std::uint16_t(40439);
            case SI_CONTROL_DAC_CURVE_Y_7_READ:
                return std::uint16_t(40440);
            case SI_CONTROL_DAC_CURVE_Y_8_READ:
                return std::uint16_t(40441);
            case SI_CONTROL_DAC_CURVE_Y_9_READ:
                return std::uint16_t(40442);
            case SI_CONTROL_CONSTANT_VOLTAGE_X_0:
                return std::uint16_t(40451);
            case SI_CONTROL_CONSTANT_VOLTAGE_X_1:
                return std::uint16_t(40452);
            case SI_CONTROL_CONSTANT_VOLTAGE_X_2:
                return std::uint16_t(40453);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ:
                return std::uint16_t(40454);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ:
                return std::uint16_t(40455);
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ:
                return std::uint16_t(40456);
            case SI_CONTROL_DAC_CURVE_X_0:
                return std::uint16_t(40457);
            case SI_CONTROL_DAC_CURVE_X_1:
                return std::uint16_t(40458);
            case SI_CONTROL_DAC_CURVE_X_2:
                return std::uint16_t(40459);
            case SI_CONTROL_DAC_CURVE_X_3:
                return std::uint16_t(40460);
            case SI_CONTROL_DAC_CURVE_X_4:
                return std::uint16_t(40461);
            case SI_CONTROL_DAC_CURVE_X_5:
                return std::uint16_t(40462);
            case SI_CONTROL_DAC_CURVE_X_6:
                return std::uint16_t(40463);
            case SI_CONTROL_DAC_CURVE_X_7:
                return std::uint16_t(40464);
            case SI_CONTROL_DAC_CURVE_X_8:
                return std::uint16_t(40465);
            case SI_CONTROL_DAC_CURVE_X_9:
                return std::uint16_t(40466);
            case SI_CONTROL_DAC_CURVE_Y_0_WRITE:
                return std::uint16_t(40467);
            case SI_CONTROL_DAC_CURVE_Y_1_WRITE:
                return std::uint16_t(40468);
            case SI_CONTROL_DAC_CURVE_Y_2_WRITE:
                return std::uint16_t(40469);
            case SI_CONTROL_DAC_CURVE_Y_3_WRITE:
                return std::uint16_t(40470);
            case SI_CONTROL_DAC_CURVE_Y_4_WRITE:
                return std::uint16_t(40471);
            case SI_CONTROL_DAC_CURVE_Y_5_WRITE:
                return std::uint16_t(40472);
            case SI_CONTROL_DAC_CURVE_Y_6_WRITE:
                return std::uint16_t(40473);
            case SI_CONTROL_DAC_CURVE_Y_7_WRITE:
                return std::uint16_t(40474);
            case SI_CONTROL_DAC_CURVE_Y_8_WRITE:
                return std::uint16_t(40475);
            case SI_CONTROL_DAC_CURVE_Y_9_WRITE:
                return std::uint16_t(40476);
            default:
                return std::uint16_t(0);
        }
    }

    /**
     * @return Returns the type of the register.
     */
    constexpr catta::modbus::si::RegisterType type() const noexcept
    {
        using Type = catta::modbus::si::RegisterType;
        switch (_value)
        {
            case COMMON_MANUFACTURER:
                return Type::string32();
            case COMMON_MODEL:
                return Type::string32();
            case COMMON_VERSION:
                return Type::string16();
            case COMMON_SERIAL_NUMBER:
                return Type::string32();
            case COMMON_DEVICE_ADDRESS:
                return Type::uint16();
            case INVERTER_AMPS:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_A:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_B:
                return Type::uint16();
            case INVERTER_AMPS_PHASE_C:
                return Type::uint16();
            case INVERTER_AMPS_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_PHASE_VOLTAGE_A:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_B:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_C:
                return Type::uint16();
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_POWER:
                return Type::sint16();
            case INVERTER_AC_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_HERTZ:
                return Type::uint16();
            case INVERTER_HERTZ_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_APPARENT_POWER:
                return Type::uint16();
            case INVERTER_AC_APPARENT_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_AC_REACTIVE_POWER:
                return Type::uint16();
            case INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_POWER_FACTOR:
                return Type::sint16();
            case INVERTER_POWER_FACTOR_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_WATT_HOURS:
                return Type::uint32();
            case INVERTER_WATT_HOURS_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_DC_VOLTAGE:
                return Type::uint16();
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_DC_POWER:
                return Type::uint16();
            case INVERTER_DC_POWER_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_TEMPERATURE:
                return Type::sint16();
            case INVERTER_TEMPERATURE_SCALE_FACTOR:
                return Type::scaleFactor();
            case INVERTER_OPERATING_STATE:
                return Type::uint16();
            case INVERTER_VENDOR_OPERATING_STATE:
                return Type::uint16();
            case INVERTER_VENDOR_EVENT_BITFIELD_1:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_2:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_3:
                return Type::uint32();
            case INVERTER_VENDOR_EVENT_BITFIELD_4:
                return Type::uint32();
            case NAMEPLATE_DER_TYPE:
                return Type::uint16();
            case BASIC_SETTINGS_MAX_POWER:
                return Type::uint16();
            case EXTENDED_MESUREMENTS_AC_WATT_HOURS:
                return Type::uint32();
            case EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE:
                return Type::uint32();
            case STORAGE_NOMINAL_CHARGE_POWER:
                return Type::uint16();
            case SI_CONTROL_MODUS:
                return Type::uint16();
            case SI_CONTROL_U_MIN_READ:
                return Type::uint16();
            case SI_CONTROL_U_MAX_READ:
                return Type::uint16();
            case SI_CONTROL_VOLTAGE_DC_START_READ:
                return Type::uint16();
            case SI_CONTROL_BATTARY_BI_MODE_READ:
                return Type::uint16();
            case SI_CONTROL_BATTARY_SAFTY_MODE_READ:
                return Type::uint16();
            case SI_CONTROL_BATTARY_CV_MODE_READ:
                return Type::uint16();
            case SI_CONTROL_DC_LOW_READ:
                return Type::uint16();
            case SI_CONTROL_DC_HIGH_READ:
                return Type::uint16();
            case SI_CONTROL_TRACKING_SELECTION:
                return Type::uint16();
            case SI_CONTROL_START_COUNTDOWN:
                return Type::uint16();
            case SI_CONTROL_NIGHT_SHUTDOWN:
                return Type::uint16();
            case SI_CONTROL_PMAX:
                return Type::uint16();
            case SI_CONTROL_COSPHI:
                return Type::uint16();
            case SI_CONTROL_UPTIME:
                return Type::uint32();
            case SI_CONTROL_MPP_STEP_DAC_0:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_DAC_1:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_DAC_2:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_DAC_3:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_UDC_0:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_UDC_1:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_UDC_2:
                return Type::uint16();
            case SI_CONTROL_MPP_STEP_UDC_3:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_DAC_0:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_DAC_1:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_DAC_2:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_DAC_3:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_UDC_0:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_UDC_1:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_UDC_2:
                return Type::uint16();
            case SI_CONTROL_MPP_SAMPLE_UDC_3:
                return Type::uint16();
            case SI_CONTROL_REDUCTION:
                return Type::uint16();
            case SI_CONTROL_SINEDUTY:
                return Type::uint16();
            case SI_CONTROL_FILTER_WIND_CURVE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_00:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_01:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_02:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_03:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_04:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_05:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_06:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_07:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_08:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_09:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_10:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_11:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_12:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_13:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_14:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_X_15:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_00_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_01_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_02_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_03_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_04_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_05_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_06_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_07_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_08_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_09_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_10_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_11_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_12_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_13_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_14_READ:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_15_READ:
                return Type::uint16();
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP:
                return Type::uint16();
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE:
                return Type::uint16();
            case SI_CONTROL_U_MIN_WRITE:
                return Type::uint16();
            case SI_CONTROL_U_MAX_WRITE:
                return Type::uint16();
            case SI_CONTROL_VOLTAGE_DC_START_WRITE:
                return Type::uint16();
            case SI_CONTROL_BATTARY_BI_MODE_WRITE:
                return Type::uint16();
            case SI_CONTROL_BATTARY_SAFTY_MODE_WRITE:
                return Type::uint16();
            case SI_CONTROL_BATTARY_CV_MODE_WRITE:
                return Type::uint16();
            case SI_CONTROL_DC_LOW_WRITE:
                return Type::uint16();
            case SI_CONTROL_DC_HIGH_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_00_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_01_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_02_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_03_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_04_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_05_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_06_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_07_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_08_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_09_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_10_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_11_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_12_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_13_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_14_WRITE:
                return Type::uint16();
            case SI_CONTROL_WIND_CURVE_Y_15_WRITE:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_0_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_1_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_2_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_3_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_4_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_5_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_6_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_7_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_8_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_9_READ:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_X_0:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_X_1:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_X_2:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ:
                return Type::uint16();
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_0:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_1:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_2:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_3:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_4:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_5:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_6:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_7:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_8:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_X_9:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_0_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_1_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_2_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_3_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_4_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_5_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_6_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_7_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_8_WRITE:
                return Type::uint16();
            case SI_CONTROL_DAC_CURVE_Y_9_WRITE:
                return Type::uint16();
            default:
                return Type::empty();
        }
    }

    /**
     * @param[in] value The address as uint16. Has to be exact an address coresponding to and address, otherwise empty is returned.
     * @return Returns the registe address if input is valid, otherwise empty.
     */
    constexpr static catta::modbus::si::RegisterAddress fromRaw(const std::uint16_t value) noexcept
    {
        using Address = catta::modbus::si::RegisterAddress;
        switch (value)
        {
            case 40004:
                return Address(COMMON_MANUFACTURER);
            case 40020:
                return Address(COMMON_MODEL);
            case 40044:
                return Address(COMMON_VERSION);
            case 40052:
                return Address(COMMON_SERIAL_NUMBER);
            case 40068:
                return Address(COMMON_DEVICE_ADDRESS);
            case 40072:
                return Address(INVERTER_AMPS);
            case 40073:
                return Address(INVERTER_AMPS_PHASE_A);
            case 40074:
                return Address(INVERTER_AMPS_PHASE_B);
            case 40075:
                return Address(INVERTER_AMPS_PHASE_C);
            case 40076:
                return Address(INVERTER_AMPS_SCALE_FACTOR);
            case 40080:
                return Address(INVERTER_PHASE_VOLTAGE_A);
            case 40081:
                return Address(INVERTER_PHASE_VOLTAGE_B);
            case 40082:
                return Address(INVERTER_PHASE_VOLTAGE_C);
            case 40083:
                return Address(INVERTER_PHASE_VOLTAGE_SCALE_FACTOR);
            case 40084:
                return Address(INVERTER_AC_POWER);
            case 40085:
                return Address(INVERTER_AC_POWER_SCALE_FACTOR);
            case 40086:
                return Address(INVERTER_HERTZ);
            case 40087:
                return Address(INVERTER_HERTZ_SCALE_FACTOR);
            case 40088:
                return Address(INVERTER_AC_APPARENT_POWER);
            case 40089:
                return Address(INVERTER_AC_APPARENT_POWER_SCALE_FACTOR);
            case 40090:
                return Address(INVERTER_AC_REACTIVE_POWER);
            case 40091:
                return Address(INVERTER_AC_REACTIVE_POWER_SCALE_FACTOR);
            case 40092:
                return Address(INVERTER_POWER_FACTOR);
            case 40093:
                return Address(INVERTER_POWER_FACTOR_SCALE_FACTOR);
            case 40094:
                return Address(INVERTER_WATT_HOURS);
            case 40096:
                return Address(INVERTER_WATT_HOURS_SCALE_FACTOR);
            case 40099:
                return Address(INVERTER_DC_VOLTAGE);
            case 40100:
                return Address(INVERTER_DC_VOLTAGE_SCALE_FACTOR);
            case 40101:
                return Address(INVERTER_DC_POWER);
            case 40102:
                return Address(INVERTER_DC_POWER_SCALE_FACTOR);
            case 40103:
                return Address(INVERTER_TEMPERATURE);
            case 40107:
                return Address(INVERTER_TEMPERATURE_SCALE_FACTOR);
            case 40108:
                return Address(INVERTER_OPERATING_STATE);
            case 40109:
                return Address(INVERTER_VENDOR_OPERATING_STATE);
            case 40110:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_1);
            case 40112:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_2);
            case 40114:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_3);
            case 40116:
                return Address(INVERTER_VENDOR_EVENT_BITFIELD_4);
            case 40124:
                return Address(NAMEPLATE_DER_TYPE);
            case 40152:
                return Address(BASIC_SETTINGS_MAX_POWER);
            case 40187:
                return Address(EXTENDED_MESUREMENTS_AC_WATT_HOURS);
            case 40203:
                return Address(EXTENDED_MESUREMENTS_AC_LIFETIME_CHARGE);
            case 40256:
                return Address(STORAGE_NOMINAL_CHARGE_POWER);
            case 40282:
                return Address(SI_CONTROL_MODUS);
            case 40286:
                return Address(SI_CONTROL_U_MIN_READ);
            case 40287:
                return Address(SI_CONTROL_U_MAX_READ);
            case 40291:
                return Address(SI_CONTROL_VOLTAGE_DC_START_READ);
            case 40294:
                return Address(SI_CONTROL_BATTARY_BI_MODE_READ);
            case 40295:
                return Address(SI_CONTROL_BATTARY_SAFTY_MODE_READ);
            case 40296:
                return Address(SI_CONTROL_BATTARY_CV_MODE_READ);
            case 40297:
                return Address(SI_CONTROL_DC_LOW_READ);
            case 40298:
                return Address(SI_CONTROL_DC_HIGH_READ);
            case 40331:
                return Address(SI_CONTROL_TRACKING_SELECTION);
            case 40334:
                return Address(SI_CONTROL_START_COUNTDOWN);
            case 40335:
                return Address(SI_CONTROL_NIGHT_SHUTDOWN);
            case 40336:
                return Address(SI_CONTROL_PMAX);
            case 40337:
                return Address(SI_CONTROL_COSPHI);
            case 40338:
                return Address(SI_CONTROL_UPTIME);
            case 40340:
                return Address(SI_CONTROL_MPP_STEP_DAC_0);
            case 40341:
                return Address(SI_CONTROL_MPP_STEP_DAC_1);
            case 40342:
                return Address(SI_CONTROL_MPP_STEP_DAC_2);
            case 40343:
                return Address(SI_CONTROL_MPP_STEP_DAC_3);
            case 40344:
                return Address(SI_CONTROL_MPP_STEP_UDC_0);
            case 40345:
                return Address(SI_CONTROL_MPP_STEP_UDC_1);
            case 40346:
                return Address(SI_CONTROL_MPP_STEP_UDC_2);
            case 40347:
                return Address(SI_CONTROL_MPP_STEP_UDC_3);
            case 40348:
                return Address(SI_CONTROL_MPP_SAMPLE_DAC_0);
            case 40349:
                return Address(SI_CONTROL_MPP_SAMPLE_DAC_1);
            case 40350:
                return Address(SI_CONTROL_MPP_SAMPLE_DAC_2);
            case 40351:
                return Address(SI_CONTROL_MPP_SAMPLE_DAC_3);
            case 40352:
                return Address(SI_CONTROL_MPP_SAMPLE_UDC_0);
            case 40353:
                return Address(SI_CONTROL_MPP_SAMPLE_UDC_1);
            case 40354:
                return Address(SI_CONTROL_MPP_SAMPLE_UDC_2);
            case 40355:
                return Address(SI_CONTROL_MPP_SAMPLE_UDC_3);
            case 40356:
                return Address(SI_CONTROL_REDUCTION);
            case 40357:
                return Address(SI_CONTROL_SINEDUTY);
            case 40360:
                return Address(SI_CONTROL_FILTER_WIND_CURVE);
            case 40361:
                return Address(SI_CONTROL_WIND_CURVE_X_00);
            case 40362:
                return Address(SI_CONTROL_WIND_CURVE_X_01);
            case 40363:
                return Address(SI_CONTROL_WIND_CURVE_X_02);
            case 40364:
                return Address(SI_CONTROL_WIND_CURVE_X_03);
            case 40365:
                return Address(SI_CONTROL_WIND_CURVE_X_04);
            case 40366:
                return Address(SI_CONTROL_WIND_CURVE_X_05);
            case 40367:
                return Address(SI_CONTROL_WIND_CURVE_X_06);
            case 40368:
                return Address(SI_CONTROL_WIND_CURVE_X_07);
            case 40369:
                return Address(SI_CONTROL_WIND_CURVE_X_08);
            case 40370:
                return Address(SI_CONTROL_WIND_CURVE_X_09);
            case 40371:
                return Address(SI_CONTROL_WIND_CURVE_X_10);
            case 40372:
                return Address(SI_CONTROL_WIND_CURVE_X_11);
            case 40373:
                return Address(SI_CONTROL_WIND_CURVE_X_12);
            case 40374:
                return Address(SI_CONTROL_WIND_CURVE_X_13);
            case 40375:
                return Address(SI_CONTROL_WIND_CURVE_X_14);
            case 40376:
                return Address(SI_CONTROL_WIND_CURVE_X_15);
            case 40377:
                return Address(SI_CONTROL_WIND_CURVE_Y_00_READ);
            case 40378:
                return Address(SI_CONTROL_WIND_CURVE_Y_01_READ);
            case 40379:
                return Address(SI_CONTROL_WIND_CURVE_Y_02_READ);
            case 40380:
                return Address(SI_CONTROL_WIND_CURVE_Y_03_READ);
            case 40381:
                return Address(SI_CONTROL_WIND_CURVE_Y_04_READ);
            case 40382:
                return Address(SI_CONTROL_WIND_CURVE_Y_05_READ);
            case 40383:
                return Address(SI_CONTROL_WIND_CURVE_Y_06_READ);
            case 40384:
                return Address(SI_CONTROL_WIND_CURVE_Y_07_READ);
            case 40385:
                return Address(SI_CONTROL_WIND_CURVE_Y_08_READ);
            case 40386:
                return Address(SI_CONTROL_WIND_CURVE_Y_09_READ);
            case 40387:
                return Address(SI_CONTROL_WIND_CURVE_Y_10_READ);
            case 40388:
                return Address(SI_CONTROL_WIND_CURVE_Y_11_READ);
            case 40389:
                return Address(SI_CONTROL_WIND_CURVE_Y_12_READ);
            case 40390:
                return Address(SI_CONTROL_WIND_CURVE_Y_13_READ);
            case 40391:
                return Address(SI_CONTROL_WIND_CURVE_Y_14_READ);
            case 40392:
                return Address(SI_CONTROL_WIND_CURVE_Y_15_READ);
            case 40394:
                return Address(SI_CONTROL_SOLAR_BATTERY_FILTER_STEP);
            case 40399:
                return Address(SI_CONTROL_POWER_LIMIT_SAFTY_MODE);
            case 40401:
                return Address(SI_CONTROL_U_MAX_WRITE);
            case 40402:
                return Address(SI_CONTROL_U_MIN_WRITE);
            case 40403:
                return Address(SI_CONTROL_VOLTAGE_DC_START_WRITE);
            case 40404:
                return Address(SI_CONTROL_BATTARY_BI_MODE_WRITE);
            case 40405:
                return Address(SI_CONTROL_BATTARY_SAFTY_MODE_WRITE);
            case 40406:
                return Address(SI_CONTROL_BATTARY_CV_MODE_WRITE);
            case 40407:
                return Address(SI_CONTROL_DC_LOW_WRITE);
            case 40408:
                return Address(SI_CONTROL_DC_HIGH_WRITE);
            case 40410:
                return Address(SI_CONTROL_WIND_CURVE_Y_00_WRITE);
            case 40411:
                return Address(SI_CONTROL_WIND_CURVE_Y_01_WRITE);
            case 40412:
                return Address(SI_CONTROL_WIND_CURVE_Y_02_WRITE);
            case 40413:
                return Address(SI_CONTROL_WIND_CURVE_Y_03_WRITE);
            case 40414:
                return Address(SI_CONTROL_WIND_CURVE_Y_04_WRITE);
            case 40415:
                return Address(SI_CONTROL_WIND_CURVE_Y_05_WRITE);
            case 40416:
                return Address(SI_CONTROL_WIND_CURVE_Y_06_WRITE);
            case 40417:
                return Address(SI_CONTROL_WIND_CURVE_Y_07_WRITE);
            case 40418:
                return Address(SI_CONTROL_WIND_CURVE_Y_08_WRITE);
            case 40419:
                return Address(SI_CONTROL_WIND_CURVE_Y_09_WRITE);
            case 40420:
                return Address(SI_CONTROL_WIND_CURVE_Y_10_WRITE);
            case 40421:
                return Address(SI_CONTROL_WIND_CURVE_Y_11_WRITE);
            case 40422:
                return Address(SI_CONTROL_WIND_CURVE_Y_12_WRITE);
            case 40423:
                return Address(SI_CONTROL_WIND_CURVE_Y_13_WRITE);
            case 40424:
                return Address(SI_CONTROL_WIND_CURVE_Y_14_WRITE);
            case 40425:
                return Address(SI_CONTROL_WIND_CURVE_Y_15_WRITE);
            case 40430:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE);
            case 40431:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE);
            case 40432:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE);
            case 40433:
                return Address(SI_CONTROL_DAC_CURVE_Y_0_READ);
            case 40434:
                return Address(SI_CONTROL_DAC_CURVE_Y_1_READ);
            case 40435:
                return Address(SI_CONTROL_DAC_CURVE_Y_2_READ);
            case 40436:
                return Address(SI_CONTROL_DAC_CURVE_Y_3_READ);
            case 40437:
                return Address(SI_CONTROL_DAC_CURVE_Y_4_READ);
            case 40438:
                return Address(SI_CONTROL_DAC_CURVE_Y_5_READ);
            case 40439:
                return Address(SI_CONTROL_DAC_CURVE_Y_6_READ);
            case 40440:
                return Address(SI_CONTROL_DAC_CURVE_Y_7_READ);
            case 40441:
                return Address(SI_CONTROL_DAC_CURVE_Y_8_READ);
            case 40442:
                return Address(SI_CONTROL_DAC_CURVE_Y_9_READ);
            case 40451:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_X_0);
            case 40452:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_X_1);
            case 40453:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_X_2);
            case 40454:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_0_READ);
            case 40455:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_1_READ);
            case 40456:
                return Address(SI_CONTROL_CONSTANT_VOLTAGE_Y_2_READ);
            case 40457:
                return Address(SI_CONTROL_DAC_CURVE_X_0);
            case 40458:
                return Address(SI_CONTROL_DAC_CURVE_X_1);
            case 40459:
                return Address(SI_CONTROL_DAC_CURVE_X_2);
            case 40460:
                return Address(SI_CONTROL_DAC_CURVE_X_3);
            case 40461:
                return Address(SI_CONTROL_DAC_CURVE_X_4);
            case 40462:
                return Address(SI_CONTROL_DAC_CURVE_X_5);
            case 40463:
                return Address(SI_CONTROL_DAC_CURVE_X_6);
            case 40464:
                return Address(SI_CONTROL_DAC_CURVE_X_7);
            case 40465:
                return Address(SI_CONTROL_DAC_CURVE_X_8);
            case 40466:
                return Address(SI_CONTROL_DAC_CURVE_X_9);
            case 40467:
                return Address(SI_CONTROL_DAC_CURVE_Y_0_WRITE);
            case 40468:
                return Address(SI_CONTROL_DAC_CURVE_Y_1_WRITE);
            case 40469:
                return Address(SI_CONTROL_DAC_CURVE_Y_2_WRITE);
            case 40470:
                return Address(SI_CONTROL_DAC_CURVE_Y_3_WRITE);
            case 40471:
                return Address(SI_CONTROL_DAC_CURVE_Y_4_WRITE);
            case 40472:
                return Address(SI_CONTROL_DAC_CURVE_Y_5_WRITE);
            case 40473:
                return Address(SI_CONTROL_DAC_CURVE_Y_6_WRITE);
            case 40474:
                return Address(SI_CONTROL_DAC_CURVE_Y_7_WRITE);
            case 40475:
                return Address(SI_CONTROL_DAC_CURVE_Y_8_WRITE);
            case 40476:
                return Address(SI_CONTROL_DAC_CURVE_Y_9_WRITE);

            default:
                return Address();
        }
    }

    /**
     * @return Returns @b true if register is readable, otherwise @b false.
     */
    constexpr bool isReadable() const noexcept
    {
        switch (_value)
        {
            case SI_CONTROL_U_MIN_WRITE:
            case SI_CONTROL_U_MAX_WRITE:
            case SI_CONTROL_VOLTAGE_DC_START_WRITE:
            case SI_CONTROL_BATTARY_BI_MODE_WRITE:
            case SI_CONTROL_BATTARY_SAFTY_MODE_WRITE:
            case SI_CONTROL_BATTARY_CV_MODE_WRITE:
            case SI_CONTROL_DC_LOW_WRITE:
            case SI_CONTROL_DC_HIGH_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_00_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_01_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_02_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_03_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_04_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_05_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_06_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_07_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_08_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_09_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_10_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_11_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_12_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_13_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_14_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_15_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_0_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_1_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_2_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_3_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_4_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_5_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_6_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_7_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_8_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_9_WRITE:
                return false;
            default:
                return true;
        }
    }

    /**
     * @return Returns @b true if register is writable, otherwise @b false.
     */
    constexpr bool isWritable() const noexcept
    {
        switch (_value)
        {
            case COMMON_DEVICE_ADDRESS:
            case BASIC_SETTINGS_MAX_POWER:
            case STORAGE_NOMINAL_CHARGE_POWER:
            case SI_CONTROL_MODUS:
            case SI_CONTROL_U_MIN_READ:
            case SI_CONTROL_U_MAX_READ:
            case SI_CONTROL_TRACKING_SELECTION:
            case SI_CONTROL_MPP_STEP_DAC_0:
            case SI_CONTROL_MPP_STEP_DAC_1:
            case SI_CONTROL_MPP_STEP_DAC_2:
            case SI_CONTROL_MPP_STEP_DAC_3:
            case SI_CONTROL_MPP_STEP_UDC_0:
            case SI_CONTROL_MPP_STEP_UDC_1:
            case SI_CONTROL_MPP_STEP_UDC_2:
            case SI_CONTROL_MPP_STEP_UDC_3:
            case SI_CONTROL_MPP_SAMPLE_DAC_0:
            case SI_CONTROL_MPP_SAMPLE_DAC_1:
            case SI_CONTROL_MPP_SAMPLE_DAC_2:
            case SI_CONTROL_MPP_SAMPLE_DAC_3:
            case SI_CONTROL_MPP_SAMPLE_UDC_0:
            case SI_CONTROL_MPP_SAMPLE_UDC_1:
            case SI_CONTROL_MPP_SAMPLE_UDC_2:
            case SI_CONTROL_MPP_SAMPLE_UDC_3:
            case SI_CONTROL_REDUCTION:
            case SI_CONTROL_SINEDUTY:
            case SI_CONTROL_FILTER_WIND_CURVE:
            case SI_CONTROL_WIND_CURVE_X_00:
            case SI_CONTROL_WIND_CURVE_X_01:
            case SI_CONTROL_WIND_CURVE_X_02:
            case SI_CONTROL_WIND_CURVE_X_03:
            case SI_CONTROL_WIND_CURVE_X_04:
            case SI_CONTROL_WIND_CURVE_X_05:
            case SI_CONTROL_WIND_CURVE_X_06:
            case SI_CONTROL_WIND_CURVE_X_07:
            case SI_CONTROL_WIND_CURVE_X_08:
            case SI_CONTROL_WIND_CURVE_X_09:
            case SI_CONTROL_WIND_CURVE_X_10:
            case SI_CONTROL_WIND_CURVE_X_11:
            case SI_CONTROL_WIND_CURVE_X_12:
            case SI_CONTROL_WIND_CURVE_X_13:
            case SI_CONTROL_WIND_CURVE_X_14:
            case SI_CONTROL_WIND_CURVE_X_15:
            case SI_CONTROL_SOLAR_BATTERY_FILTER_STEP:
            case SI_CONTROL_POWER_LIMIT_SAFTY_MODE:
            case SI_CONTROL_VOLTAGE_DC_START_WRITE:
            case SI_CONTROL_BATTARY_BI_MODE_WRITE:
            case SI_CONTROL_BATTARY_SAFTY_MODE_WRITE:
            case SI_CONTROL_BATTARY_CV_MODE_WRITE:
            case SI_CONTROL_DC_LOW_WRITE:
            case SI_CONTROL_DC_HIGH_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_00_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_01_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_02_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_03_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_04_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_05_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_06_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_07_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_08_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_09_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_10_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_11_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_12_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_13_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_14_WRITE:
            case SI_CONTROL_WIND_CURVE_Y_15_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_0_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_1_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_Y_2_WRITE:
            case SI_CONTROL_CONSTANT_VOLTAGE_X_0:
            case SI_CONTROL_CONSTANT_VOLTAGE_X_1:
            case SI_CONTROL_CONSTANT_VOLTAGE_X_2:
            case SI_CONTROL_DAC_CURVE_X_0:
            case SI_CONTROL_DAC_CURVE_X_1:
            case SI_CONTROL_DAC_CURVE_X_2:
            case SI_CONTROL_DAC_CURVE_X_3:
            case SI_CONTROL_DAC_CURVE_X_4:
            case SI_CONTROL_DAC_CURVE_X_5:
            case SI_CONTROL_DAC_CURVE_X_6:
            case SI_CONTROL_DAC_CURVE_X_7:
            case SI_CONTROL_DAC_CURVE_X_8:
            case SI_CONTROL_DAC_CURVE_X_9:
            case SI_CONTROL_DAC_CURVE_Y_0_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_1_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_2_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_3_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_4_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_5_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_6_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_7_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_8_WRITE:
            case SI_CONTROL_DAC_CURVE_Y_9_WRITE:
                return true;
            default:
                return false;
        }
    }

  private:
    std::uint8_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
