#pragma once

// response
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>

// tojson
#include <catta/tojson/modbus/si/Type.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU32.hpp>
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::ReadOperatingData3e>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::ReadOperatingData3e;
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
            case SERIAL_NUMBER + 0:
                return next(catta::json::Token::openString());
            case SERIAL_NUMBER + 1:
                return next(catta::json::Token::character('s'));
            case SERIAL_NUMBER + 2:
                return next(catta::json::Token::character('e'));
            case SERIAL_NUMBER + 3:
                return next(catta::json::Token::character('r'));
            case SERIAL_NUMBER + 4:
                return next(catta::json::Token::character('i'));
            case SERIAL_NUMBER + 5:
                return next(catta::json::Token::character('a'));
            case SERIAL_NUMBER + 6:
                return next(catta::json::Token::character('l'));
            case SERIAL_NUMBER + 7:
                return next(catta::json::Token::character('N'));
            case SERIAL_NUMBER + 8:
                return next(catta::json::Token::character('u'));
            case SERIAL_NUMBER + 9:
                return next(catta::json::Token::character('m'));
            case SERIAL_NUMBER + 10:
                return next(catta::json::Token::character('b'));
            case SERIAL_NUMBER + 11:
                return next(catta::json::Token::character('e'));
            case SERIAL_NUMBER + 12:
                return next(catta::json::Token::character('r'));
            case SERIAL_NUMBER + 13:
                return next(catta::json::Token::closeString());
            case SERIAL_NUMBER + 14:
                return next(catta::json::Token::colon());
            case SERIAL_NUMBER + 15:
                return handle(_serialNumberSerializer, input.serialNumber(), catta::json::Token::comma());
            case TYPE + 0:
                return next(catta::json::Token::openString());
            case TYPE + 1:
                return next(catta::json::Token::character('t'));
            case TYPE + 2:
                return next(catta::json::Token::character('y'));
            case TYPE + 3:
                return next(catta::json::Token::character('p'));
            case TYPE + 4:
                return next(catta::json::Token::character('e'));
            case TYPE + 5:
                return next(catta::json::Token::closeString());
            case TYPE + 6:
                return next(catta::json::Token::colon());
            case TYPE + 7:
                return handle(_typeSerializer, input.type(), catta::json::Token::comma());
            case VOLTAGE_TYPE + 0:
                return next(catta::json::Token::openString());
            case VOLTAGE_TYPE + 1:
                return next(catta::json::Token::character('v'));
            case VOLTAGE_TYPE + 2:
                return next(catta::json::Token::character('o'));
            case VOLTAGE_TYPE + 3:
                return next(catta::json::Token::character('l'));
            case VOLTAGE_TYPE + 4:
                return next(catta::json::Token::character('t'));
            case VOLTAGE_TYPE + 5:
                return next(catta::json::Token::character('a'));
            case VOLTAGE_TYPE + 6:
                return next(catta::json::Token::character('g'));
            case VOLTAGE_TYPE + 7:
                return next(catta::json::Token::character('e'));
            case VOLTAGE_TYPE + 8:
                return next(catta::json::Token::character('T'));
            case VOLTAGE_TYPE + 9:
                return next(catta::json::Token::character('y'));
            case VOLTAGE_TYPE + 10:
                return next(catta::json::Token::character('p'));
            case VOLTAGE_TYPE + 11:
                return next(catta::json::Token::character('e'));
            case VOLTAGE_TYPE + 12:
                return next(catta::json::Token::closeString());
            case VOLTAGE_TYPE + 13:
                return next(catta::json::Token::colon());
            case VOLTAGE_TYPE + 14:
                return handle(_voltageTypeSerializer, input.voltageType(), catta::json::Token::comma());
            case NOMINAL_POWER + 0:
                return next(catta::json::Token::openString());
            case NOMINAL_POWER + 1:
                return next(catta::json::Token::character('n'));
            case NOMINAL_POWER + 2:
                return next(catta::json::Token::character('o'));
            case NOMINAL_POWER + 3:
                return next(catta::json::Token::character('m'));
            case NOMINAL_POWER + 4:
                return next(catta::json::Token::character('i'));
            case NOMINAL_POWER + 5:
                return next(catta::json::Token::character('n'));
            case NOMINAL_POWER + 6:
                return next(catta::json::Token::character('a'));
            case NOMINAL_POWER + 7:
                return next(catta::json::Token::character('l'));
            case NOMINAL_POWER + 8:
                return next(catta::json::Token::character('P'));
            case NOMINAL_POWER + 9:
                return next(catta::json::Token::character('o'));
            case NOMINAL_POWER + 10:
                return next(catta::json::Token::character('w'));
            case NOMINAL_POWER + 11:
                return next(catta::json::Token::character('e'));
            case NOMINAL_POWER + 12:
                return next(catta::json::Token::character('r'));
            case NOMINAL_POWER + 13:
                return next(catta::json::Token::closeString());
            case NOMINAL_POWER + 14:
                return next(catta::json::Token::colon());
            case NOMINAL_POWER + 15:
                return handle(_nominalPowerSerializer, input.nominalPower(), catta::json::Token::comma());
            case COSPHI + 0:
                return next(catta::json::Token::openString());
            case COSPHI + 1:
                return next(catta::json::Token::character('c'));
            case COSPHI + 2:
                return next(catta::json::Token::character('o'));
            case COSPHI + 3:
                return next(catta::json::Token::character('s'));
            case COSPHI + 4:
                return next(catta::json::Token::character('p'));
            case COSPHI + 5:
                return next(catta::json::Token::character('h'));
            case COSPHI + 6:
                return next(catta::json::Token::character('i'));
            case COSPHI + 7:
                return next(catta::json::Token::closeString());
            case COSPHI + 8:
                return next(catta::json::Token::colon());
            case COSPHI + 9:
                return handle(_cosphiSerializer, input.cosphi(), catta::json::Token::comma());
            case GRID_SUPPLY_DAILY_SUM + 0:
                return next(catta::json::Token::openString());
            case GRID_SUPPLY_DAILY_SUM + 1:
                return next(catta::json::Token::character('g'));
            case GRID_SUPPLY_DAILY_SUM + 2:
                return next(catta::json::Token::character('r'));
            case GRID_SUPPLY_DAILY_SUM + 3:
                return next(catta::json::Token::character('i'));
            case GRID_SUPPLY_DAILY_SUM + 4:
                return next(catta::json::Token::character('d'));
            case GRID_SUPPLY_DAILY_SUM + 5:
                return next(catta::json::Token::character('S'));
            case GRID_SUPPLY_DAILY_SUM + 6:
                return next(catta::json::Token::character('u'));
            case GRID_SUPPLY_DAILY_SUM + 7:
                return next(catta::json::Token::character('p'));
            case GRID_SUPPLY_DAILY_SUM + 8:
                return next(catta::json::Token::character('p'));
            case GRID_SUPPLY_DAILY_SUM + 9:
                return next(catta::json::Token::character('l'));
            case GRID_SUPPLY_DAILY_SUM + 10:
                return next(catta::json::Token::character('y'));
            case GRID_SUPPLY_DAILY_SUM + 11:
                return next(catta::json::Token::character('D'));
            case GRID_SUPPLY_DAILY_SUM + 12:
                return next(catta::json::Token::character('a'));
            case GRID_SUPPLY_DAILY_SUM + 13:
                return next(catta::json::Token::character('i'));
            case GRID_SUPPLY_DAILY_SUM + 14:
                return next(catta::json::Token::character('l'));
            case GRID_SUPPLY_DAILY_SUM + 15:
                return next(catta::json::Token::character('y'));
            case GRID_SUPPLY_DAILY_SUM + 16:
                return next(catta::json::Token::character('S'));
            case GRID_SUPPLY_DAILY_SUM + 17:
                return next(catta::json::Token::character('u'));
            case GRID_SUPPLY_DAILY_SUM + 18:
                return next(catta::json::Token::character('m'));
            case GRID_SUPPLY_DAILY_SUM + 19:
                return next(catta::json::Token::closeString());
            case GRID_SUPPLY_DAILY_SUM + 20:
                return next(catta::json::Token::colon());
            case GRID_SUPPLY_DAILY_SUM + 21:
                return handle(_gridSupplyDailySumSerializer, input.gridSupplyDailySum(), catta::json::Token::comma());
            case POWER_LIMITATION + 0:
                return next(catta::json::Token::openString());
            case POWER_LIMITATION + 1:
                return next(catta::json::Token::character('p'));
            case POWER_LIMITATION + 2:
                return next(catta::json::Token::character('o'));
            case POWER_LIMITATION + 3:
                return next(catta::json::Token::character('w'));
            case POWER_LIMITATION + 4:
                return next(catta::json::Token::character('e'));
            case POWER_LIMITATION + 5:
                return next(catta::json::Token::character('r'));
            case POWER_LIMITATION + 6:
                return next(catta::json::Token::character('L'));
            case POWER_LIMITATION + 7:
                return next(catta::json::Token::character('i'));
            case POWER_LIMITATION + 8:
                return next(catta::json::Token::character('m'));
            case POWER_LIMITATION + 9:
                return next(catta::json::Token::character('i'));
            case POWER_LIMITATION + 10:
                return next(catta::json::Token::character('t'));
            case POWER_LIMITATION + 11:
                return next(catta::json::Token::character('a'));
            case POWER_LIMITATION + 12:
                return next(catta::json::Token::character('t'));
            case POWER_LIMITATION + 13:
                return next(catta::json::Token::character('i'));
            case POWER_LIMITATION + 14:
                return next(catta::json::Token::character('o'));
            case POWER_LIMITATION + 15:
                return next(catta::json::Token::character('n'));
            case POWER_LIMITATION + 16:
                return next(catta::json::Token::closeString());
            case POWER_LIMITATION + 17:
                return next(catta::json::Token::colon());
            case POWER_LIMITATION + 18:
                return handle(_powerLimitationSerializer, input.powerLimitation(), catta::json::Token::comma());
            case OPERATING_HOURS + 0:
                return next(catta::json::Token::openString());
            case OPERATING_HOURS + 1:
                return next(catta::json::Token::character('o'));
            case OPERATING_HOURS + 2:
                return next(catta::json::Token::character('p'));
            case OPERATING_HOURS + 3:
                return next(catta::json::Token::character('e'));
            case OPERATING_HOURS + 4:
                return next(catta::json::Token::character('r'));
            case OPERATING_HOURS + 5:
                return next(catta::json::Token::character('a'));
            case OPERATING_HOURS + 6:
                return next(catta::json::Token::character('t'));
            case OPERATING_HOURS + 7:
                return next(catta::json::Token::character('i'));
            case OPERATING_HOURS + 8:
                return next(catta::json::Token::character('n'));
            case OPERATING_HOURS + 9:
                return next(catta::json::Token::character('g'));
            case OPERATING_HOURS + 10:
                return next(catta::json::Token::character('H'));
            case OPERATING_HOURS + 11:
                return next(catta::json::Token::character('o'));
            case OPERATING_HOURS + 12:
                return next(catta::json::Token::character('u'));
            case OPERATING_HOURS + 13:
                return next(catta::json::Token::character('r'));
            case OPERATING_HOURS + 14:
                return next(catta::json::Token::character('s'));
            case OPERATING_HOURS + 15:
                return next(catta::json::Token::closeString());
            case OPERATING_HOURS + 16:
                return next(catta::json::Token::colon());
            case OPERATING_HOURS + 17:
                return handle(_operatingHoursSerializer, input.operatingHours(), catta::json::Token::comma());
            case PHASE + 0:
                return next(catta::json::Token::openString());
            case PHASE + 1:
                return next(catta::json::Token::character('p'));
            case PHASE + 2:
                return next(catta::json::Token::character('h'));
            case PHASE + 3:
                return next(catta::json::Token::character('a'));
            case PHASE + 4:
                return next(catta::json::Token::character('s'));
            case PHASE + 5:
                return next(catta::json::Token::character('e'));
            case PHASE + 6:
                return next(catta::json::Token::closeString());
            case PHASE + 7:
                return next(catta::json::Token::colon());
            case PHASE + 8:
                return handle(_phaseSerializer, input.phase(), catta::json::Token::comma());
            case MODBUS_ID + 0:
                return next(catta::json::Token::openString());
            case MODBUS_ID + 1:
                return next(catta::json::Token::character('m'));
            case MODBUS_ID + 2:
                return next(catta::json::Token::character('o'));
            case MODBUS_ID + 3:
                return next(catta::json::Token::character('d'));
            case MODBUS_ID + 4:
                return next(catta::json::Token::character('b'));
            case MODBUS_ID + 5:
                return next(catta::json::Token::character('u'));
            case MODBUS_ID + 6:
                return next(catta::json::Token::character('s'));
            case MODBUS_ID + 7:
                return next(catta::json::Token::character('I'));
            case MODBUS_ID + 8:
                return next(catta::json::Token::character('d'));
            case MODBUS_ID + 9:
                return next(catta::json::Token::closeString());
            case MODBUS_ID + 10:
                return next(catta::json::Token::colon());
            case MODBUS_ID + 11:
                return handle(_modbusIdSerializer, input.modbusId(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _serialNumberSerializer;
    Serializer<catta::modbus::si::Type> _typeSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<1, 10>> _voltageTypeSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<1, 32>> _nominalPowerSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _cosphiSerializer;
    Serializer<catta::modbus::sunspec::ValueU32> _gridSupplyDailySumSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _powerLimitationSerializer;
    Serializer<catta::modbus::sunspec::ValueU32> _operatingHoursSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 3>> _phaseSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 15>> _modbusIdSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t SERIAL_NUMBER = START + 1;
    static constexpr std::uint8_t TYPE = SERIAL_NUMBER + 16;
    static constexpr std::uint8_t VOLTAGE_TYPE = TYPE + 8;
    static constexpr std::uint8_t NOMINAL_POWER = VOLTAGE_TYPE + 15;
    static constexpr std::uint8_t COSPHI = NOMINAL_POWER + 16;
    static constexpr std::uint8_t GRID_SUPPLY_DAILY_SUM = COSPHI + 10;
    static constexpr std::uint8_t POWER_LIMITATION = GRID_SUPPLY_DAILY_SUM + 22;
    static constexpr std::uint8_t OPERATING_HOURS = POWER_LIMITATION + 19;
    static constexpr std::uint8_t PHASE = OPERATING_HOURS + 18;
    static constexpr std::uint8_t MODBUS_ID = PHASE + 9;
    static constexpr std::uint8_t TAIL = MODBUS_ID + 12;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
