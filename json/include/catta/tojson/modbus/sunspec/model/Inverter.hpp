#pragma once

// model
#include <catta/modbus/sunspec/model/Inverter.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ScaledValue3U16.hpp>
#include <catta/tojson/modbus/sunspec/ScaledValue4U16.hpp>
#include <catta/tojson/modbus/sunspec/ScaledValueS16.hpp>
#include <catta/tojson/modbus/sunspec/ScaledValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ScaledValueU32.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU32.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::Inverter>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::Inverter;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _data = catta::json::Token::end();
            _state = DONE + 0;
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this](const catta::json::Token token)
        {
            _data = token;
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto next = [stay, this](const catta::json::Token token)
        {
            _state++;
            return stay(token);
        };
        const auto handle = [stay, next, error](auto& serializer, const auto value, const catta::json::Token token)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return next(token);
            return stay(serializer.data());
        };
        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
            case AMPERE + 0:
                return next(catta::json::Token::openString());
            case AMPERE + 1:
                return next(catta::json::Token::character('a'));
            case AMPERE + 2:
                return next(catta::json::Token::character('m'));
            case AMPERE + 3:
                return next(catta::json::Token::character('p'));
            case AMPERE + 4:
                return next(catta::json::Token::character('e'));
            case AMPERE + 5:
                return next(catta::json::Token::character('r'));
            case AMPERE + 6:
                return next(catta::json::Token::character('e'));
            case AMPERE + 7:
                return next(catta::json::Token::closeString());
            case AMPERE + 8:
                return next(catta::json::Token::colon());
            case AMPERE + 9:
                return handle(_ampereSerializer, input.ampere(), catta::json::Token::comma());
            case VOLTAGE + 0:
                return next(catta::json::Token::openString());
            case VOLTAGE + 1:
                return next(catta::json::Token::character('v'));
            case VOLTAGE + 2:
                return next(catta::json::Token::character('o'));
            case VOLTAGE + 3:
                return next(catta::json::Token::character('l'));
            case VOLTAGE + 4:
                return next(catta::json::Token::character('t'));
            case VOLTAGE + 5:
                return next(catta::json::Token::character('a'));
            case VOLTAGE + 6:
                return next(catta::json::Token::character('g'));
            case VOLTAGE + 7:
                return next(catta::json::Token::character('e'));
            case VOLTAGE + 8:
                return next(catta::json::Token::closeString());
            case VOLTAGE + 9:
                return next(catta::json::Token::colon());
            case VOLTAGE + 10:
                return handle(_voltageSerializer, input.voltage(), catta::json::Token::comma());
            case WATT + 0:
                return next(catta::json::Token::openString());
            case WATT + 1:
                return next(catta::json::Token::character('w'));
            case WATT + 2:
                return next(catta::json::Token::character('a'));
            case WATT + 3:
                return next(catta::json::Token::character('t'));
            case WATT + 4:
                return next(catta::json::Token::character('t'));
            case WATT + 5:
                return next(catta::json::Token::closeString());
            case WATT + 6:
                return next(catta::json::Token::colon());
            case WATT + 7:
                return handle(_wattSerializer, input.watt(), catta::json::Token::comma());
            case HERTZ + 0:
                return next(catta::json::Token::openString());
            case HERTZ + 1:
                return next(catta::json::Token::character('h'));
            case HERTZ + 2:
                return next(catta::json::Token::character('e'));
            case HERTZ + 3:
                return next(catta::json::Token::character('r'));
            case HERTZ + 4:
                return next(catta::json::Token::character('t'));
            case HERTZ + 5:
                return next(catta::json::Token::character('z'));
            case HERTZ + 6:
                return next(catta::json::Token::closeString());
            case HERTZ + 7:
                return next(catta::json::Token::colon());
            case HERTZ + 8:
                return handle(_hertzSerializer, input.hertz(), catta::json::Token::comma());
            case POWER_FACTOR + 0:
                return next(catta::json::Token::openString());
            case POWER_FACTOR + 1:
                return next(catta::json::Token::character('p'));
            case POWER_FACTOR + 2:
                return next(catta::json::Token::character('o'));
            case POWER_FACTOR + 3:
                return next(catta::json::Token::character('w'));
            case POWER_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case POWER_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case POWER_FACTOR + 6:
                return next(catta::json::Token::character('F'));
            case POWER_FACTOR + 7:
                return next(catta::json::Token::character('a'));
            case POWER_FACTOR + 8:
                return next(catta::json::Token::character('c'));
            case POWER_FACTOR + 9:
                return next(catta::json::Token::character('t'));
            case POWER_FACTOR + 10:
                return next(catta::json::Token::character('o'));
            case POWER_FACTOR + 11:
                return next(catta::json::Token::character('r'));
            case POWER_FACTOR + 12:
                return next(catta::json::Token::closeString());
            case POWER_FACTOR + 13:
                return next(catta::json::Token::colon());
            case POWER_FACTOR + 14:
                return handle(_powerFactorSerializer, input.powerFactor(), catta::json::Token::comma());
            case WATT_HOURS + 0:
                return next(catta::json::Token::openString());
            case WATT_HOURS + 1:
                return next(catta::json::Token::character('w'));
            case WATT_HOURS + 2:
                return next(catta::json::Token::character('a'));
            case WATT_HOURS + 3:
                return next(catta::json::Token::character('t'));
            case WATT_HOURS + 4:
                return next(catta::json::Token::character('t'));
            case WATT_HOURS + 5:
                return next(catta::json::Token::character('H'));
            case WATT_HOURS + 6:
                return next(catta::json::Token::character('o'));
            case WATT_HOURS + 7:
                return next(catta::json::Token::character('u'));
            case WATT_HOURS + 8:
                return next(catta::json::Token::character('r'));
            case WATT_HOURS + 9:
                return next(catta::json::Token::character('s'));
            case WATT_HOURS + 10:
                return next(catta::json::Token::closeString());
            case WATT_HOURS + 11:
                return next(catta::json::Token::colon());
            case WATT_HOURS + 12:
                return handle(_wattHoursSerializer, input.wattHours(), catta::json::Token::comma());
            case DC_VOLTAGE + 0:
                return next(catta::json::Token::openString());
            case DC_VOLTAGE + 1:
                return next(catta::json::Token::character('d'));
            case DC_VOLTAGE + 2:
                return next(catta::json::Token::character('c'));
            case DC_VOLTAGE + 3:
                return next(catta::json::Token::character('V'));
            case DC_VOLTAGE + 4:
                return next(catta::json::Token::character('o'));
            case DC_VOLTAGE + 5:
                return next(catta::json::Token::character('l'));
            case DC_VOLTAGE + 6:
                return next(catta::json::Token::character('t'));
            case DC_VOLTAGE + 7:
                return next(catta::json::Token::character('a'));
            case DC_VOLTAGE + 8:
                return next(catta::json::Token::character('g'));
            case DC_VOLTAGE + 9:
                return next(catta::json::Token::character('e'));
            case DC_VOLTAGE + 10:
                return next(catta::json::Token::closeString());
            case DC_VOLTAGE + 11:
                return next(catta::json::Token::colon());
            case DC_VOLTAGE + 12:
                return handle(_dcVoltageSerializer, input.dcVoltage(), catta::json::Token::comma());
            case CABINET_TEMPERATURE + 0:
                return next(catta::json::Token::openString());
            case CABINET_TEMPERATURE + 1:
                return next(catta::json::Token::character('c'));
            case CABINET_TEMPERATURE + 2:
                return next(catta::json::Token::character('a'));
            case CABINET_TEMPERATURE + 3:
                return next(catta::json::Token::character('b'));
            case CABINET_TEMPERATURE + 4:
                return next(catta::json::Token::character('i'));
            case CABINET_TEMPERATURE + 5:
                return next(catta::json::Token::character('n'));
            case CABINET_TEMPERATURE + 6:
                return next(catta::json::Token::character('e'));
            case CABINET_TEMPERATURE + 7:
                return next(catta::json::Token::character('t'));
            case CABINET_TEMPERATURE + 8:
                return next(catta::json::Token::character('T'));
            case CABINET_TEMPERATURE + 9:
                return next(catta::json::Token::character('e'));
            case CABINET_TEMPERATURE + 10:
                return next(catta::json::Token::character('m'));
            case CABINET_TEMPERATURE + 11:
                return next(catta::json::Token::character('p'));
            case CABINET_TEMPERATURE + 12:
                return next(catta::json::Token::character('e'));
            case CABINET_TEMPERATURE + 13:
                return next(catta::json::Token::character('r'));
            case CABINET_TEMPERATURE + 14:
                return next(catta::json::Token::character('a'));
            case CABINET_TEMPERATURE + 15:
                return next(catta::json::Token::character('t'));
            case CABINET_TEMPERATURE + 16:
                return next(catta::json::Token::character('u'));
            case CABINET_TEMPERATURE + 17:
                return next(catta::json::Token::character('r'));
            case CABINET_TEMPERATURE + 18:
                return next(catta::json::Token::character('e'));
            case CABINET_TEMPERATURE + 19:
                return next(catta::json::Token::closeString());
            case CABINET_TEMPERATURE + 20:
                return next(catta::json::Token::colon());
            case CABINET_TEMPERATURE + 21:
                return handle(_cabinetTemperatureSerializer, input.cabinetTemperature(), catta::json::Token::comma());
            case OPERATING_STATE + 0:
                return next(catta::json::Token::openString());
            case OPERATING_STATE + 1:
                return next(catta::json::Token::character('o'));
            case OPERATING_STATE + 2:
                return next(catta::json::Token::character('p'));
            case OPERATING_STATE + 3:
                return next(catta::json::Token::character('e'));
            case OPERATING_STATE + 4:
                return next(catta::json::Token::character('r'));
            case OPERATING_STATE + 5:
                return next(catta::json::Token::character('a'));
            case OPERATING_STATE + 6:
                return next(catta::json::Token::character('t'));
            case OPERATING_STATE + 7:
                return next(catta::json::Token::character('i'));
            case OPERATING_STATE + 8:
                return next(catta::json::Token::character('n'));
            case OPERATING_STATE + 9:
                return next(catta::json::Token::character('g'));
            case OPERATING_STATE + 10:
                return next(catta::json::Token::character('S'));
            case OPERATING_STATE + 11:
                return next(catta::json::Token::character('t'));
            case OPERATING_STATE + 12:
                return next(catta::json::Token::character('a'));
            case OPERATING_STATE + 13:
                return next(catta::json::Token::character('t'));
            case OPERATING_STATE + 14:
                return next(catta::json::Token::character('e'));
            case OPERATING_STATE + 15:
                return next(catta::json::Token::closeString());
            case OPERATING_STATE + 16:
                return next(catta::json::Token::colon());
            case OPERATING_STATE + 17:
                return handle(_operatingStateSerializer, input.operatingState(), catta::json::Token::comma());
            case VENDOR_OPERATING_STATE + 0:
                return next(catta::json::Token::openString());
            case VENDOR_OPERATING_STATE + 1:
                return next(catta::json::Token::character('v'));
            case VENDOR_OPERATING_STATE + 2:
                return next(catta::json::Token::character('e'));
            case VENDOR_OPERATING_STATE + 3:
                return next(catta::json::Token::character('n'));
            case VENDOR_OPERATING_STATE + 4:
                return next(catta::json::Token::character('d'));
            case VENDOR_OPERATING_STATE + 5:
                return next(catta::json::Token::character('o'));
            case VENDOR_OPERATING_STATE + 6:
                return next(catta::json::Token::character('r'));
            case VENDOR_OPERATING_STATE + 7:
                return next(catta::json::Token::character('O'));
            case VENDOR_OPERATING_STATE + 8:
                return next(catta::json::Token::character('p'));
            case VENDOR_OPERATING_STATE + 9:
                return next(catta::json::Token::character('e'));
            case VENDOR_OPERATING_STATE + 10:
                return next(catta::json::Token::character('r'));
            case VENDOR_OPERATING_STATE + 11:
                return next(catta::json::Token::character('a'));
            case VENDOR_OPERATING_STATE + 12:
                return next(catta::json::Token::character('t'));
            case VENDOR_OPERATING_STATE + 13:
                return next(catta::json::Token::character('i'));
            case VENDOR_OPERATING_STATE + 14:
                return next(catta::json::Token::character('n'));
            case VENDOR_OPERATING_STATE + 15:
                return next(catta::json::Token::character('g'));
            case VENDOR_OPERATING_STATE + 16:
                return next(catta::json::Token::character('S'));
            case VENDOR_OPERATING_STATE + 17:
                return next(catta::json::Token::character('t'));
            case VENDOR_OPERATING_STATE + 18:
                return next(catta::json::Token::character('a'));
            case VENDOR_OPERATING_STATE + 19:
                return next(catta::json::Token::character('t'));
            case VENDOR_OPERATING_STATE + 20:
                return next(catta::json::Token::character('e'));
            case VENDOR_OPERATING_STATE + 21:
                return next(catta::json::Token::closeString());
            case VENDOR_OPERATING_STATE + 22:
                return next(catta::json::Token::colon());
            case VENDOR_OPERATING_STATE + 23:
                return handle(_vendorOperatingStateSerializer, input.vendorOperatingState(), catta::json::Token::comma());
            case VENDOR_EVENT_BITFIELD + 0:
                return next(catta::json::Token::openString());
            case VENDOR_EVENT_BITFIELD + 1:
                return next(catta::json::Token::character('v'));
            case VENDOR_EVENT_BITFIELD + 2:
                return next(catta::json::Token::character('e'));
            case VENDOR_EVENT_BITFIELD + 3:
                return next(catta::json::Token::character('n'));
            case VENDOR_EVENT_BITFIELD + 4:
                return next(catta::json::Token::character('d'));
            case VENDOR_EVENT_BITFIELD + 5:
                return next(catta::json::Token::character('o'));
            case VENDOR_EVENT_BITFIELD + 6:
                return next(catta::json::Token::character('r'));
            case VENDOR_EVENT_BITFIELD + 7:
                return next(catta::json::Token::character('E'));
            case VENDOR_EVENT_BITFIELD + 8:
                return next(catta::json::Token::character('v'));
            case VENDOR_EVENT_BITFIELD + 9:
                return next(catta::json::Token::character('e'));
            case VENDOR_EVENT_BITFIELD + 10:
                return next(catta::json::Token::character('n'));
            case VENDOR_EVENT_BITFIELD + 11:
                return next(catta::json::Token::character('t'));
            case VENDOR_EVENT_BITFIELD + 12:
                return next(catta::json::Token::character('B'));
            case VENDOR_EVENT_BITFIELD + 13:
                return next(catta::json::Token::character('i'));
            case VENDOR_EVENT_BITFIELD + 14:
                return next(catta::json::Token::character('t'));
            case VENDOR_EVENT_BITFIELD + 15:
                return next(catta::json::Token::character('f'));
            case VENDOR_EVENT_BITFIELD + 16:
                return next(catta::json::Token::character('i'));
            case VENDOR_EVENT_BITFIELD + 17:
                return next(catta::json::Token::character('e'));
            case VENDOR_EVENT_BITFIELD + 18:
                return next(catta::json::Token::character('l'));
            case VENDOR_EVENT_BITFIELD + 19:
                return next(catta::json::Token::character('d'));
            case VENDOR_EVENT_BITFIELD + 20:
                return next(catta::json::Token::closeString());
            case VENDOR_EVENT_BITFIELD + 21:
                return next(catta::json::Token::colon());
            case VENDOR_EVENT_BITFIELD + 22:
                return handle(_vendorEventBitfieldSerializer, input.vendorEventBitfield(), catta::json::Token::closeCurlyBracket());
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _data(Output::empty()) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    catta::json::Token _data;
    Serializer<catta::modbus::sunspec::ScaledValue4U16> _ampereSerializer;
    Serializer<catta::modbus::sunspec::ScaledValue3U16> _voltageSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueS16> _wattSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueU16> _hertzSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueS16> _powerFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueU32> _wattHoursSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueU16> _dcVoltageSerializer;
    Serializer<catta::modbus::sunspec::ScaledValueS16> _cabinetTemperatureSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _operatingStateSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _vendorOperatingStateSerializer;
    Serializer<catta::modbus::sunspec::ValueU32> _vendorEventBitfieldSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t AMPERE = START + 1;
    static constexpr std::uint8_t VOLTAGE = AMPERE + 10;
    static constexpr std::uint8_t WATT = VOLTAGE + 11;
    static constexpr std::uint8_t HERTZ = WATT + 8;
    static constexpr std::uint8_t POWER_FACTOR = HERTZ + 9;
    static constexpr std::uint8_t WATT_HOURS = POWER_FACTOR + 15;
    static constexpr std::uint8_t DC_VOLTAGE = WATT_HOURS + 13;
    static constexpr std::uint8_t CABINET_TEMPERATURE = DC_VOLTAGE + 13;
    static constexpr std::uint8_t OPERATING_STATE = CABINET_TEMPERATURE + 22;
    static constexpr std::uint8_t VENDOR_OPERATING_STATE = OPERATING_STATE + 18;
    static constexpr std::uint8_t VENDOR_EVENT_BITFIELD = VENDOR_OPERATING_STATE + 24;
    static constexpr std::uint8_t TAIL = VENDOR_EVENT_BITFIELD + 23;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
