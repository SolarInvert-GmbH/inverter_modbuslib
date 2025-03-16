#pragma once

// si
#include <catta/modbus/si/Cache.hpp>

// tojson
#include <catta/tojson/modbus/si/Type.hpp>
#include <catta/tojson/modbus/sunspec/ScaleFactor.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::Cache>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::Cache;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
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
        const auto jump = [stay, this](const std::uint16_t state, const catta::json::Token token)
        {
            _state = state;
            return stay(token);
        };
        const auto getNextHubState = [this, &input, jump](const std::uint16_t offset, const catta::json::Token token)
        {
            using Pair = std::tuple<std::uint16_t, bool>;
            const auto v = [](const std::uint16_t s, const auto e) { return Pair{s, !e.isEmpty()}; };
            const Pair values[] = {v(TYPE, input.type()),
                                   v(INVERTER_AMPS_SCALE_FACTOR, input.inverterAmpsScaleFactor()),
                                   v(INVERTER_PHASE_VOLTAGE_SCALE_FACTOR, input.inverterPhaseVoltageScaleFactor()),
                                   v(INVERTER_WATT_SCALE_FACTOR, input.inverterWattScaleFactor()),
                                   v(INVERTER_HERTZ_SCALE_FACTOR, input.inverterHertzScaleFactor()),
                                   v(INVERTER_POWER_FACTOR_SCALE_FACTOR, input.inverterPowerFactorScaleFactor()),
                                   v(INVERTER_WATT_HOURS_SCALE_FACTOR, input.inverterWattHoursScaleFactor()),
                                   v(INVERTER_DC_VOLTAGE_SCALE_FACTOR, input.inverterDcVoltageScaleFactor()),
                                   v(INVERTER_TEMPERATURE_SCALE_FACTOR, input.inverterTemperatureScaleFactor())};
            for (const auto& e : values)
                if (_state < std::get<0>(e) && std::get<1>(e)) return jump(std::get<0>(e) + offset, token);
            return jump(TAIL + 0, catta::json::Token::closeCurlyBracket());
        };
        const auto handle = [stay, getNextHubState, error](auto& serializer, const auto value)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return getNextHubState(0, catta::json::Token::comma());
            return stay(serializer.data());
        };
        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
            case START + 1:
                return getNextHubState(1, catta::json::Token::openString());
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
                return handle(_typeSerializer, input.type());
            case INVERTER_AMPS_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_AMPS_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_AMPS_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_AMPS_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_AMPS_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('A'));
            case INVERTER_AMPS_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('m'));
            case INVERTER_AMPS_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('p'));
            case INVERTER_AMPS_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case INVERTER_AMPS_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('S'));
            case INVERTER_AMPS_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('c'));
            case INVERTER_AMPS_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('l'));
            case INVERTER_AMPS_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_AMPS_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('F'));
            case INVERTER_AMPS_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_AMPS_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case INVERTER_AMPS_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_AMPS_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('o'));
            case INVERTER_AMPS_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('r'));
            case INVERTER_AMPS_SCALE_FACTOR + 24:
                return next(catta::json::Token::closeString());
            case INVERTER_AMPS_SCALE_FACTOR + 25:
                return next(catta::json::Token::colon());
            case INVERTER_AMPS_SCALE_FACTOR + 26:
                return handle(_inverterAmpsScaleFactorSerializer, input.inverterAmpsScaleFactor());
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('P'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('h'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('s'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('V'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('g'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('S'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('c'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('l'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('e'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('F'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('a'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('c'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('t'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('o'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 31:
                return next(catta::json::Token::character('r'));
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 32:
                return next(catta::json::Token::closeString());
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 33:
                return next(catta::json::Token::colon());
            case INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 34:
                return handle(_inverterPhaseVoltageScaleFactorSerializer, input.inverterPhaseVoltageScaleFactor());
            case INVERTER_WATT_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_WATT_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_WATT_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('S'));
            case INVERTER_WATT_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('l'));
            case INVERTER_WATT_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('F'));
            case INVERTER_WATT_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_SCALE_FACTOR + 24:
                return next(catta::json::Token::closeString());
            case INVERTER_WATT_SCALE_FACTOR + 25:
                return next(catta::json::Token::colon());
            case INVERTER_WATT_SCALE_FACTOR + 26:
                return handle(_inverterWattScaleFactorSerializer, input.inverterWattScaleFactor());
            case INVERTER_HERTZ_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_HERTZ_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_HERTZ_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_HERTZ_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_HERTZ_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('H'));
            case INVERTER_HERTZ_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('z'));
            case INVERTER_HERTZ_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('S'));
            case INVERTER_HERTZ_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('c'));
            case INVERTER_HERTZ_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('a'));
            case INVERTER_HERTZ_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('l'));
            case INVERTER_HERTZ_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('e'));
            case INVERTER_HERTZ_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('F'));
            case INVERTER_HERTZ_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('a'));
            case INVERTER_HERTZ_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('c'));
            case INVERTER_HERTZ_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('t'));
            case INVERTER_HERTZ_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('o'));
            case INVERTER_HERTZ_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('r'));
            case INVERTER_HERTZ_SCALE_FACTOR + 25:
                return next(catta::json::Token::closeString());
            case INVERTER_HERTZ_SCALE_FACTOR + 26:
                return next(catta::json::Token::colon());
            case INVERTER_HERTZ_SCALE_FACTOR + 27:
                return handle(_inverterHertzScaleFactorSerializer, input.inverterHertzScaleFactor());
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('P'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('w'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('F'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('S'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('l'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('F'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('a'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('c'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('t'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('o'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('r'));
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 31:
                return next(catta::json::Token::closeString());
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 32:
                return next(catta::json::Token::colon());
            case INVERTER_POWER_FACTOR_SCALE_FACTOR + 33:
                return handle(_inverterPowerFactorScaleFactorSerializer, input.inverterPowerFactorScaleFactor());
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('W'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('H'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('u'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('s'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('S'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('l'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('e'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('F'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('a'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('c'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('t'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('o'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('r'));
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 29:
                return next(catta::json::Token::closeString());
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 30:
                return next(catta::json::Token::colon());
            case INVERTER_WATT_HOURS_SCALE_FACTOR + 31:
                return handle(_inverterWattHoursScaleFactorSerializer, input.inverterWattHoursScaleFactor());
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('D'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('V'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('g'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('S'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('l'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('e'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('F'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('a'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('c'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('t'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('o'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('r'));
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 29:
                return next(catta::json::Token::closeString());
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 30:
                return next(catta::json::Token::colon());
            case INVERTER_DC_VOLTAGE_SCALE_FACTOR + 31:
                return handle(_inverterDcVoltageScaleFactorSerializer, input.inverterDcVoltageScaleFactor());
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 0:
                return next(catta::json::Token::openString());
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 1:
                return next(catta::json::Token::character('i'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 2:
                return next(catta::json::Token::character('n'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 3:
                return next(catta::json::Token::character('v'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 5:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 6:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 7:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 8:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 9:
                return next(catta::json::Token::character('T'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 10:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 11:
                return next(catta::json::Token::character('m'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 12:
                return next(catta::json::Token::character('p'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 13:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 14:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 15:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 16:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 17:
                return next(catta::json::Token::character('u'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 18:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 19:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 20:
                return next(catta::json::Token::character('S'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 21:
                return next(catta::json::Token::character('c'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 22:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 23:
                return next(catta::json::Token::character('l'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 24:
                return next(catta::json::Token::character('e'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 25:
                return next(catta::json::Token::character('F'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 26:
                return next(catta::json::Token::character('a'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 27:
                return next(catta::json::Token::character('c'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 28:
                return next(catta::json::Token::character('t'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 29:
                return next(catta::json::Token::character('o'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 30:
                return next(catta::json::Token::character('r'));
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 31:
                return next(catta::json::Token::closeString());
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 32:
                return next(catta::json::Token::colon());
            case INVERTER_TEMPERATURE_SCALE_FACTOR + 33:
                return handle(_inverterTemperatureScaleFactorSerializer, input.inverterTemperatureScaleFactor());
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
    std::uint16_t _state;
    catta::json::Token _data;
    Serializer<catta::modbus::si::Type> _typeSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterAmpsScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterPhaseVoltageScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterWattScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterHertzScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterPowerFactorScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterWattHoursScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterDcVoltageScaleFactorSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _inverterTemperatureScaleFactorSerializer;
    static constexpr std::uint16_t START = 0;
    static constexpr std::uint16_t TYPE = START + 2;
    static constexpr std::uint16_t INVERTER_AMPS_SCALE_FACTOR = TYPE + 8;
    static constexpr std::uint16_t INVERTER_PHASE_VOLTAGE_SCALE_FACTOR = INVERTER_AMPS_SCALE_FACTOR + 27;
    static constexpr std::uint16_t INVERTER_WATT_SCALE_FACTOR = INVERTER_PHASE_VOLTAGE_SCALE_FACTOR + 35;
    static constexpr std::uint16_t INVERTER_HERTZ_SCALE_FACTOR = INVERTER_WATT_SCALE_FACTOR + 27;
    static constexpr std::uint16_t INVERTER_POWER_FACTOR_SCALE_FACTOR = INVERTER_HERTZ_SCALE_FACTOR + 28;
    static constexpr std::uint16_t INVERTER_WATT_HOURS_SCALE_FACTOR = INVERTER_POWER_FACTOR_SCALE_FACTOR + 34;
    static constexpr std::uint16_t INVERTER_DC_VOLTAGE_SCALE_FACTOR = INVERTER_WATT_HOURS_SCALE_FACTOR + 32;
    static constexpr std::uint16_t INVERTER_TEMPERATURE_SCALE_FACTOR = INVERTER_DC_VOLTAGE_SCALE_FACTOR + 32;
    static constexpr std::uint16_t TAIL = INVERTER_TEMPERATURE_SCALE_FACTOR + 34;
    static constexpr std::uint16_t DONE = TAIL + 1;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
