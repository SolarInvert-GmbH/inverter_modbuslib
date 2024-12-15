#pragma once

// response
#include <catta/modbus/si/response/ReadError.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::ReadError>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::ReadError;
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
            case OVER_VOLTAGE_A_C + 0:
                return next(catta::json::Token::openString());
            case OVER_VOLTAGE_A_C + 1:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_A_C + 2:
                return next(catta::json::Token::character('v'));
            case OVER_VOLTAGE_A_C + 3:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_A_C + 4:
                return next(catta::json::Token::character('r'));
            case OVER_VOLTAGE_A_C + 5:
                return next(catta::json::Token::character('V'));
            case OVER_VOLTAGE_A_C + 6:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_A_C + 7:
                return next(catta::json::Token::character('l'));
            case OVER_VOLTAGE_A_C + 8:
                return next(catta::json::Token::character('t'));
            case OVER_VOLTAGE_A_C + 9:
                return next(catta::json::Token::character('a'));
            case OVER_VOLTAGE_A_C + 10:
                return next(catta::json::Token::character('g'));
            case OVER_VOLTAGE_A_C + 11:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_A_C + 12:
                return next(catta::json::Token::character('A'));
            case OVER_VOLTAGE_A_C + 13:
                return next(catta::json::Token::character('C'));
            case OVER_VOLTAGE_A_C + 14:
                return next(catta::json::Token::closeString());
            case OVER_VOLTAGE_A_C + 15:
                return next(catta::json::Token::colon());
            case OVER_VOLTAGE_A_C + 16:
                return handle(_overVoltageACSerializer, input.overVoltageAC(), catta::json::Token::comma());
            case UNDER_VOLTAGE_A_C + 0:
                return next(catta::json::Token::openString());
            case UNDER_VOLTAGE_A_C + 1:
                return next(catta::json::Token::character('u'));
            case UNDER_VOLTAGE_A_C + 2:
                return next(catta::json::Token::character('n'));
            case UNDER_VOLTAGE_A_C + 3:
                return next(catta::json::Token::character('d'));
            case UNDER_VOLTAGE_A_C + 4:
                return next(catta::json::Token::character('e'));
            case UNDER_VOLTAGE_A_C + 5:
                return next(catta::json::Token::character('r'));
            case UNDER_VOLTAGE_A_C + 6:
                return next(catta::json::Token::character('V'));
            case UNDER_VOLTAGE_A_C + 7:
                return next(catta::json::Token::character('o'));
            case UNDER_VOLTAGE_A_C + 8:
                return next(catta::json::Token::character('l'));
            case UNDER_VOLTAGE_A_C + 9:
                return next(catta::json::Token::character('t'));
            case UNDER_VOLTAGE_A_C + 10:
                return next(catta::json::Token::character('a'));
            case UNDER_VOLTAGE_A_C + 11:
                return next(catta::json::Token::character('g'));
            case UNDER_VOLTAGE_A_C + 12:
                return next(catta::json::Token::character('e'));
            case UNDER_VOLTAGE_A_C + 13:
                return next(catta::json::Token::character('A'));
            case UNDER_VOLTAGE_A_C + 14:
                return next(catta::json::Token::character('C'));
            case UNDER_VOLTAGE_A_C + 15:
                return next(catta::json::Token::closeString());
            case UNDER_VOLTAGE_A_C + 16:
                return next(catta::json::Token::colon());
            case UNDER_VOLTAGE_A_C + 17:
                return handle(_underVoltageACSerializer, input.underVoltageAC(), catta::json::Token::comma());
            case OVER_VOLTAGE_D_C + 0:
                return next(catta::json::Token::openString());
            case OVER_VOLTAGE_D_C + 1:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_D_C + 2:
                return next(catta::json::Token::character('v'));
            case OVER_VOLTAGE_D_C + 3:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_D_C + 4:
                return next(catta::json::Token::character('r'));
            case OVER_VOLTAGE_D_C + 5:
                return next(catta::json::Token::character('V'));
            case OVER_VOLTAGE_D_C + 6:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_D_C + 7:
                return next(catta::json::Token::character('l'));
            case OVER_VOLTAGE_D_C + 8:
                return next(catta::json::Token::character('t'));
            case OVER_VOLTAGE_D_C + 9:
                return next(catta::json::Token::character('a'));
            case OVER_VOLTAGE_D_C + 10:
                return next(catta::json::Token::character('g'));
            case OVER_VOLTAGE_D_C + 11:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_D_C + 12:
                return next(catta::json::Token::character('D'));
            case OVER_VOLTAGE_D_C + 13:
                return next(catta::json::Token::character('C'));
            case OVER_VOLTAGE_D_C + 14:
                return next(catta::json::Token::closeString());
            case OVER_VOLTAGE_D_C + 15:
                return next(catta::json::Token::colon());
            case OVER_VOLTAGE_D_C + 16:
                return handle(_overVoltageDCSerializer, input.overVoltageDC(), catta::json::Token::comma());
            case UNDER_VOLTAGE_D_C + 0:
                return next(catta::json::Token::openString());
            case UNDER_VOLTAGE_D_C + 1:
                return next(catta::json::Token::character('u'));
            case UNDER_VOLTAGE_D_C + 2:
                return next(catta::json::Token::character('n'));
            case UNDER_VOLTAGE_D_C + 3:
                return next(catta::json::Token::character('d'));
            case UNDER_VOLTAGE_D_C + 4:
                return next(catta::json::Token::character('e'));
            case UNDER_VOLTAGE_D_C + 5:
                return next(catta::json::Token::character('r'));
            case UNDER_VOLTAGE_D_C + 6:
                return next(catta::json::Token::character('V'));
            case UNDER_VOLTAGE_D_C + 7:
                return next(catta::json::Token::character('o'));
            case UNDER_VOLTAGE_D_C + 8:
                return next(catta::json::Token::character('l'));
            case UNDER_VOLTAGE_D_C + 9:
                return next(catta::json::Token::character('t'));
            case UNDER_VOLTAGE_D_C + 10:
                return next(catta::json::Token::character('a'));
            case UNDER_VOLTAGE_D_C + 11:
                return next(catta::json::Token::character('g'));
            case UNDER_VOLTAGE_D_C + 12:
                return next(catta::json::Token::character('e'));
            case UNDER_VOLTAGE_D_C + 13:
                return next(catta::json::Token::character('D'));
            case UNDER_VOLTAGE_D_C + 14:
                return next(catta::json::Token::character('C'));
            case UNDER_VOLTAGE_D_C + 15:
                return next(catta::json::Token::closeString());
            case UNDER_VOLTAGE_D_C + 16:
                return next(catta::json::Token::colon());
            case UNDER_VOLTAGE_D_C + 17:
                return handle(_underVoltageDCSerializer, input.underVoltageDC(), catta::json::Token::comma());
            case OVER_FREQUENCY + 0:
                return next(catta::json::Token::openString());
            case OVER_FREQUENCY + 1:
                return next(catta::json::Token::character('o'));
            case OVER_FREQUENCY + 2:
                return next(catta::json::Token::character('v'));
            case OVER_FREQUENCY + 3:
                return next(catta::json::Token::character('e'));
            case OVER_FREQUENCY + 4:
                return next(catta::json::Token::character('r'));
            case OVER_FREQUENCY + 5:
                return next(catta::json::Token::character('F'));
            case OVER_FREQUENCY + 6:
                return next(catta::json::Token::character('r'));
            case OVER_FREQUENCY + 7:
                return next(catta::json::Token::character('e'));
            case OVER_FREQUENCY + 8:
                return next(catta::json::Token::character('q'));
            case OVER_FREQUENCY + 9:
                return next(catta::json::Token::character('u'));
            case OVER_FREQUENCY + 10:
                return next(catta::json::Token::character('e'));
            case OVER_FREQUENCY + 11:
                return next(catta::json::Token::character('n'));
            case OVER_FREQUENCY + 12:
                return next(catta::json::Token::character('c'));
            case OVER_FREQUENCY + 13:
                return next(catta::json::Token::character('y'));
            case OVER_FREQUENCY + 14:
                return next(catta::json::Token::closeString());
            case OVER_FREQUENCY + 15:
                return next(catta::json::Token::colon());
            case OVER_FREQUENCY + 16:
                return handle(_overFrequencySerializer, input.overFrequency(), catta::json::Token::comma());
            case UNDER_FREQUENCY + 0:
                return next(catta::json::Token::openString());
            case UNDER_FREQUENCY + 1:
                return next(catta::json::Token::character('u'));
            case UNDER_FREQUENCY + 2:
                return next(catta::json::Token::character('n'));
            case UNDER_FREQUENCY + 3:
                return next(catta::json::Token::character('d'));
            case UNDER_FREQUENCY + 4:
                return next(catta::json::Token::character('e'));
            case UNDER_FREQUENCY + 5:
                return next(catta::json::Token::character('r'));
            case UNDER_FREQUENCY + 6:
                return next(catta::json::Token::character('F'));
            case UNDER_FREQUENCY + 7:
                return next(catta::json::Token::character('r'));
            case UNDER_FREQUENCY + 8:
                return next(catta::json::Token::character('e'));
            case UNDER_FREQUENCY + 9:
                return next(catta::json::Token::character('q'));
            case UNDER_FREQUENCY + 10:
                return next(catta::json::Token::character('u'));
            case UNDER_FREQUENCY + 11:
                return next(catta::json::Token::character('e'));
            case UNDER_FREQUENCY + 12:
                return next(catta::json::Token::character('n'));
            case UNDER_FREQUENCY + 13:
                return next(catta::json::Token::character('c'));
            case UNDER_FREQUENCY + 14:
                return next(catta::json::Token::character('y'));
            case UNDER_FREQUENCY + 15:
                return next(catta::json::Token::closeString());
            case UNDER_FREQUENCY + 16:
                return next(catta::json::Token::colon());
            case UNDER_FREQUENCY + 17:
                return handle(_underFrequencySerializer, input.underFrequency(), catta::json::Token::comma());
            case LIMITED_POWER_T1 + 0:
                return next(catta::json::Token::openString());
            case LIMITED_POWER_T1 + 1:
                return next(catta::json::Token::character('l'));
            case LIMITED_POWER_T1 + 2:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T1 + 3:
                return next(catta::json::Token::character('m'));
            case LIMITED_POWER_T1 + 4:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T1 + 5:
                return next(catta::json::Token::character('t'));
            case LIMITED_POWER_T1 + 6:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T1 + 7:
                return next(catta::json::Token::character('d'));
            case LIMITED_POWER_T1 + 8:
                return next(catta::json::Token::character('P'));
            case LIMITED_POWER_T1 + 9:
                return next(catta::json::Token::character('o'));
            case LIMITED_POWER_T1 + 10:
                return next(catta::json::Token::character('w'));
            case LIMITED_POWER_T1 + 11:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T1 + 12:
                return next(catta::json::Token::character('r'));
            case LIMITED_POWER_T1 + 13:
                return next(catta::json::Token::character('T'));
            case LIMITED_POWER_T1 + 14:
                return next(catta::json::Token::character('1'));
            case LIMITED_POWER_T1 + 15:
                return next(catta::json::Token::closeString());
            case LIMITED_POWER_T1 + 16:
                return next(catta::json::Token::colon());
            case LIMITED_POWER_T1 + 17:
                return handle(_limitedPowerT1Serializer, input.limitedPowerT1(), catta::json::Token::comma());
            case LIMITED_POWER_T2 + 0:
                return next(catta::json::Token::openString());
            case LIMITED_POWER_T2 + 1:
                return next(catta::json::Token::character('l'));
            case LIMITED_POWER_T2 + 2:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T2 + 3:
                return next(catta::json::Token::character('m'));
            case LIMITED_POWER_T2 + 4:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T2 + 5:
                return next(catta::json::Token::character('t'));
            case LIMITED_POWER_T2 + 6:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T2 + 7:
                return next(catta::json::Token::character('d'));
            case LIMITED_POWER_T2 + 8:
                return next(catta::json::Token::character('P'));
            case LIMITED_POWER_T2 + 9:
                return next(catta::json::Token::character('o'));
            case LIMITED_POWER_T2 + 10:
                return next(catta::json::Token::character('w'));
            case LIMITED_POWER_T2 + 11:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T2 + 12:
                return next(catta::json::Token::character('r'));
            case LIMITED_POWER_T2 + 13:
                return next(catta::json::Token::character('T'));
            case LIMITED_POWER_T2 + 14:
                return next(catta::json::Token::character('2'));
            case LIMITED_POWER_T2 + 15:
                return next(catta::json::Token::closeString());
            case LIMITED_POWER_T2 + 16:
                return next(catta::json::Token::colon());
            case LIMITED_POWER_T2 + 17:
                return handle(_limitedPowerT2Serializer, input.limitedPowerT2(), catta::json::Token::comma());
            case LIMITED_POWER_T3 + 0:
                return next(catta::json::Token::openString());
            case LIMITED_POWER_T3 + 1:
                return next(catta::json::Token::character('l'));
            case LIMITED_POWER_T3 + 2:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T3 + 3:
                return next(catta::json::Token::character('m'));
            case LIMITED_POWER_T3 + 4:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T3 + 5:
                return next(catta::json::Token::character('t'));
            case LIMITED_POWER_T3 + 6:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T3 + 7:
                return next(catta::json::Token::character('d'));
            case LIMITED_POWER_T3 + 8:
                return next(catta::json::Token::character('P'));
            case LIMITED_POWER_T3 + 9:
                return next(catta::json::Token::character('o'));
            case LIMITED_POWER_T3 + 10:
                return next(catta::json::Token::character('w'));
            case LIMITED_POWER_T3 + 11:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T3 + 12:
                return next(catta::json::Token::character('r'));
            case LIMITED_POWER_T3 + 13:
                return next(catta::json::Token::character('T'));
            case LIMITED_POWER_T3 + 14:
                return next(catta::json::Token::character('3'));
            case LIMITED_POWER_T3 + 15:
                return next(catta::json::Token::closeString());
            case LIMITED_POWER_T3 + 16:
                return next(catta::json::Token::colon());
            case LIMITED_POWER_T3 + 17:
                return handle(_limitedPowerT3Serializer, input.limitedPowerT3(), catta::json::Token::comma());
            case LIMITED_POWER_T4 + 0:
                return next(catta::json::Token::openString());
            case LIMITED_POWER_T4 + 1:
                return next(catta::json::Token::character('l'));
            case LIMITED_POWER_T4 + 2:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T4 + 3:
                return next(catta::json::Token::character('m'));
            case LIMITED_POWER_T4 + 4:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T4 + 5:
                return next(catta::json::Token::character('t'));
            case LIMITED_POWER_T4 + 6:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T4 + 7:
                return next(catta::json::Token::character('d'));
            case LIMITED_POWER_T4 + 8:
                return next(catta::json::Token::character('P'));
            case LIMITED_POWER_T4 + 9:
                return next(catta::json::Token::character('o'));
            case LIMITED_POWER_T4 + 10:
                return next(catta::json::Token::character('w'));
            case LIMITED_POWER_T4 + 11:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T4 + 12:
                return next(catta::json::Token::character('r'));
            case LIMITED_POWER_T4 + 13:
                return next(catta::json::Token::character('T'));
            case LIMITED_POWER_T4 + 14:
                return next(catta::json::Token::character('4'));
            case LIMITED_POWER_T4 + 15:
                return next(catta::json::Token::closeString());
            case LIMITED_POWER_T4 + 16:
                return next(catta::json::Token::colon());
            case LIMITED_POWER_T4 + 17:
                return handle(_limitedPowerT4Serializer, input.limitedPowerT4(), catta::json::Token::comma());
            case LIMITED_POWER_T5 + 0:
                return next(catta::json::Token::openString());
            case LIMITED_POWER_T5 + 1:
                return next(catta::json::Token::character('l'));
            case LIMITED_POWER_T5 + 2:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T5 + 3:
                return next(catta::json::Token::character('m'));
            case LIMITED_POWER_T5 + 4:
                return next(catta::json::Token::character('i'));
            case LIMITED_POWER_T5 + 5:
                return next(catta::json::Token::character('t'));
            case LIMITED_POWER_T5 + 6:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T5 + 7:
                return next(catta::json::Token::character('d'));
            case LIMITED_POWER_T5 + 8:
                return next(catta::json::Token::character('P'));
            case LIMITED_POWER_T5 + 9:
                return next(catta::json::Token::character('o'));
            case LIMITED_POWER_T5 + 10:
                return next(catta::json::Token::character('w'));
            case LIMITED_POWER_T5 + 11:
                return next(catta::json::Token::character('e'));
            case LIMITED_POWER_T5 + 12:
                return next(catta::json::Token::character('r'));
            case LIMITED_POWER_T5 + 13:
                return next(catta::json::Token::character('T'));
            case LIMITED_POWER_T5 + 14:
                return next(catta::json::Token::character('5'));
            case LIMITED_POWER_T5 + 15:
                return next(catta::json::Token::closeString());
            case LIMITED_POWER_T5 + 16:
                return next(catta::json::Token::colon());
            case LIMITED_POWER_T5 + 17:
                return handle(_limitedPowerT5Serializer, input.limitedPowerT5(), catta::json::Token::comma());
            case COM + 0:
                return next(catta::json::Token::openString());
            case COM + 1:
                return next(catta::json::Token::character('c'));
            case COM + 2:
                return next(catta::json::Token::character('o'));
            case COM + 3:
                return next(catta::json::Token::character('m'));
            case COM + 4:
                return next(catta::json::Token::closeString());
            case COM + 5:
                return next(catta::json::Token::colon());
            case COM + 6:
                return handle(_comSerializer, input.com(), catta::json::Token::comma());
            case ISLAND_GRID + 0:
                return next(catta::json::Token::openString());
            case ISLAND_GRID + 1:
                return next(catta::json::Token::character('i'));
            case ISLAND_GRID + 2:
                return next(catta::json::Token::character('s'));
            case ISLAND_GRID + 3:
                return next(catta::json::Token::character('l'));
            case ISLAND_GRID + 4:
                return next(catta::json::Token::character('a'));
            case ISLAND_GRID + 5:
                return next(catta::json::Token::character('n'));
            case ISLAND_GRID + 6:
                return next(catta::json::Token::character('d'));
            case ISLAND_GRID + 7:
                return next(catta::json::Token::character('G'));
            case ISLAND_GRID + 8:
                return next(catta::json::Token::character('r'));
            case ISLAND_GRID + 9:
                return next(catta::json::Token::character('i'));
            case ISLAND_GRID + 10:
                return next(catta::json::Token::character('d'));
            case ISLAND_GRID + 11:
                return next(catta::json::Token::closeString());
            case ISLAND_GRID + 12:
                return next(catta::json::Token::colon());
            case ISLAND_GRID + 13:
                return handle(_islandGridSerializer, input.islandGrid(), catta::json::Token::comma());
            case OVER_CURRENT_INTERRUPT + 0:
                return next(catta::json::Token::openString());
            case OVER_CURRENT_INTERRUPT + 1:
                return next(catta::json::Token::character('o'));
            case OVER_CURRENT_INTERRUPT + 2:
                return next(catta::json::Token::character('v'));
            case OVER_CURRENT_INTERRUPT + 3:
                return next(catta::json::Token::character('e'));
            case OVER_CURRENT_INTERRUPT + 4:
                return next(catta::json::Token::character('r'));
            case OVER_CURRENT_INTERRUPT + 5:
                return next(catta::json::Token::character('C'));
            case OVER_CURRENT_INTERRUPT + 6:
                return next(catta::json::Token::character('u'));
            case OVER_CURRENT_INTERRUPT + 7:
                return next(catta::json::Token::character('r'));
            case OVER_CURRENT_INTERRUPT + 8:
                return next(catta::json::Token::character('r'));
            case OVER_CURRENT_INTERRUPT + 9:
                return next(catta::json::Token::character('e'));
            case OVER_CURRENT_INTERRUPT + 10:
                return next(catta::json::Token::character('n'));
            case OVER_CURRENT_INTERRUPT + 11:
                return next(catta::json::Token::character('t'));
            case OVER_CURRENT_INTERRUPT + 12:
                return next(catta::json::Token::character('I'));
            case OVER_CURRENT_INTERRUPT + 13:
                return next(catta::json::Token::character('n'));
            case OVER_CURRENT_INTERRUPT + 14:
                return next(catta::json::Token::character('t'));
            case OVER_CURRENT_INTERRUPT + 15:
                return next(catta::json::Token::character('e'));
            case OVER_CURRENT_INTERRUPT + 16:
                return next(catta::json::Token::character('r'));
            case OVER_CURRENT_INTERRUPT + 17:
                return next(catta::json::Token::character('r'));
            case OVER_CURRENT_INTERRUPT + 18:
                return next(catta::json::Token::character('u'));
            case OVER_CURRENT_INTERRUPT + 19:
                return next(catta::json::Token::character('p'));
            case OVER_CURRENT_INTERRUPT + 20:
                return next(catta::json::Token::character('t'));
            case OVER_CURRENT_INTERRUPT + 21:
                return next(catta::json::Token::closeString());
            case OVER_CURRENT_INTERRUPT + 22:
                return next(catta::json::Token::colon());
            case OVER_CURRENT_INTERRUPT + 23:
                return handle(_overCurrentInterruptSerializer, input.overCurrentInterrupt(), catta::json::Token::comma());
            case OVER_VOLTAGE_INTERRUPT + 0:
                return next(catta::json::Token::openString());
            case OVER_VOLTAGE_INTERRUPT + 1:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_INTERRUPT + 2:
                return next(catta::json::Token::character('v'));
            case OVER_VOLTAGE_INTERRUPT + 3:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_INTERRUPT + 4:
                return next(catta::json::Token::character('r'));
            case OVER_VOLTAGE_INTERRUPT + 5:
                return next(catta::json::Token::character('V'));
            case OVER_VOLTAGE_INTERRUPT + 6:
                return next(catta::json::Token::character('o'));
            case OVER_VOLTAGE_INTERRUPT + 7:
                return next(catta::json::Token::character('l'));
            case OVER_VOLTAGE_INTERRUPT + 8:
                return next(catta::json::Token::character('t'));
            case OVER_VOLTAGE_INTERRUPT + 9:
                return next(catta::json::Token::character('a'));
            case OVER_VOLTAGE_INTERRUPT + 10:
                return next(catta::json::Token::character('g'));
            case OVER_VOLTAGE_INTERRUPT + 11:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_INTERRUPT + 12:
                return next(catta::json::Token::character('I'));
            case OVER_VOLTAGE_INTERRUPT + 13:
                return next(catta::json::Token::character('n'));
            case OVER_VOLTAGE_INTERRUPT + 14:
                return next(catta::json::Token::character('t'));
            case OVER_VOLTAGE_INTERRUPT + 15:
                return next(catta::json::Token::character('e'));
            case OVER_VOLTAGE_INTERRUPT + 16:
                return next(catta::json::Token::character('r'));
            case OVER_VOLTAGE_INTERRUPT + 17:
                return next(catta::json::Token::character('r'));
            case OVER_VOLTAGE_INTERRUPT + 18:
                return next(catta::json::Token::character('u'));
            case OVER_VOLTAGE_INTERRUPT + 19:
                return next(catta::json::Token::character('p'));
            case OVER_VOLTAGE_INTERRUPT + 20:
                return next(catta::json::Token::character('t'));
            case OVER_VOLTAGE_INTERRUPT + 21:
                return next(catta::json::Token::closeString());
            case OVER_VOLTAGE_INTERRUPT + 22:
                return next(catta::json::Token::colon());
            case OVER_VOLTAGE_INTERRUPT + 23:
                return handle(_overVoltageInterruptSerializer, input.overVoltageInterrupt(), catta::json::Token::comma());
            case AVERAGE_GRID_OVER_VOLTAGE + 0:
                return next(catta::json::Token::openString());
            case AVERAGE_GRID_OVER_VOLTAGE + 1:
                return next(catta::json::Token::character('a'));
            case AVERAGE_GRID_OVER_VOLTAGE + 2:
                return next(catta::json::Token::character('v'));
            case AVERAGE_GRID_OVER_VOLTAGE + 3:
                return next(catta::json::Token::character('e'));
            case AVERAGE_GRID_OVER_VOLTAGE + 4:
                return next(catta::json::Token::character('r'));
            case AVERAGE_GRID_OVER_VOLTAGE + 5:
                return next(catta::json::Token::character('a'));
            case AVERAGE_GRID_OVER_VOLTAGE + 6:
                return next(catta::json::Token::character('g'));
            case AVERAGE_GRID_OVER_VOLTAGE + 7:
                return next(catta::json::Token::character('e'));
            case AVERAGE_GRID_OVER_VOLTAGE + 8:
                return next(catta::json::Token::character('G'));
            case AVERAGE_GRID_OVER_VOLTAGE + 9:
                return next(catta::json::Token::character('r'));
            case AVERAGE_GRID_OVER_VOLTAGE + 10:
                return next(catta::json::Token::character('i'));
            case AVERAGE_GRID_OVER_VOLTAGE + 11:
                return next(catta::json::Token::character('d'));
            case AVERAGE_GRID_OVER_VOLTAGE + 12:
                return next(catta::json::Token::character('O'));
            case AVERAGE_GRID_OVER_VOLTAGE + 13:
                return next(catta::json::Token::character('v'));
            case AVERAGE_GRID_OVER_VOLTAGE + 14:
                return next(catta::json::Token::character('e'));
            case AVERAGE_GRID_OVER_VOLTAGE + 15:
                return next(catta::json::Token::character('r'));
            case AVERAGE_GRID_OVER_VOLTAGE + 16:
                return next(catta::json::Token::character('V'));
            case AVERAGE_GRID_OVER_VOLTAGE + 17:
                return next(catta::json::Token::character('o'));
            case AVERAGE_GRID_OVER_VOLTAGE + 18:
                return next(catta::json::Token::character('l'));
            case AVERAGE_GRID_OVER_VOLTAGE + 19:
                return next(catta::json::Token::character('t'));
            case AVERAGE_GRID_OVER_VOLTAGE + 20:
                return next(catta::json::Token::character('a'));
            case AVERAGE_GRID_OVER_VOLTAGE + 21:
                return next(catta::json::Token::character('g'));
            case AVERAGE_GRID_OVER_VOLTAGE + 22:
                return next(catta::json::Token::character('e'));
            case AVERAGE_GRID_OVER_VOLTAGE + 23:
                return next(catta::json::Token::closeString());
            case AVERAGE_GRID_OVER_VOLTAGE + 24:
                return next(catta::json::Token::colon());
            case AVERAGE_GRID_OVER_VOLTAGE + 25:
                return handle(_averageGridOverVoltageSerializer, input.averageGridOverVoltage(), catta::json::Token::comma());
            case OVER_TEMPRATURE_SHUTDOWN + 0:
                return next(catta::json::Token::openString());
            case OVER_TEMPRATURE_SHUTDOWN + 1:
                return next(catta::json::Token::character('o'));
            case OVER_TEMPRATURE_SHUTDOWN + 2:
                return next(catta::json::Token::character('v'));
            case OVER_TEMPRATURE_SHUTDOWN + 3:
                return next(catta::json::Token::character('e'));
            case OVER_TEMPRATURE_SHUTDOWN + 4:
                return next(catta::json::Token::character('r'));
            case OVER_TEMPRATURE_SHUTDOWN + 5:
                return next(catta::json::Token::character('T'));
            case OVER_TEMPRATURE_SHUTDOWN + 6:
                return next(catta::json::Token::character('e'));
            case OVER_TEMPRATURE_SHUTDOWN + 7:
                return next(catta::json::Token::character('m'));
            case OVER_TEMPRATURE_SHUTDOWN + 8:
                return next(catta::json::Token::character('p'));
            case OVER_TEMPRATURE_SHUTDOWN + 9:
                return next(catta::json::Token::character('r'));
            case OVER_TEMPRATURE_SHUTDOWN + 10:
                return next(catta::json::Token::character('a'));
            case OVER_TEMPRATURE_SHUTDOWN + 11:
                return next(catta::json::Token::character('t'));
            case OVER_TEMPRATURE_SHUTDOWN + 12:
                return next(catta::json::Token::character('u'));
            case OVER_TEMPRATURE_SHUTDOWN + 13:
                return next(catta::json::Token::character('r'));
            case OVER_TEMPRATURE_SHUTDOWN + 14:
                return next(catta::json::Token::character('e'));
            case OVER_TEMPRATURE_SHUTDOWN + 15:
                return next(catta::json::Token::character('S'));
            case OVER_TEMPRATURE_SHUTDOWN + 16:
                return next(catta::json::Token::character('h'));
            case OVER_TEMPRATURE_SHUTDOWN + 17:
                return next(catta::json::Token::character('u'));
            case OVER_TEMPRATURE_SHUTDOWN + 18:
                return next(catta::json::Token::character('t'));
            case OVER_TEMPRATURE_SHUTDOWN + 19:
                return next(catta::json::Token::character('d'));
            case OVER_TEMPRATURE_SHUTDOWN + 20:
                return next(catta::json::Token::character('o'));
            case OVER_TEMPRATURE_SHUTDOWN + 21:
                return next(catta::json::Token::character('w'));
            case OVER_TEMPRATURE_SHUTDOWN + 22:
                return next(catta::json::Token::character('n'));
            case OVER_TEMPRATURE_SHUTDOWN + 23:
                return next(catta::json::Token::closeString());
            case OVER_TEMPRATURE_SHUTDOWN + 24:
                return next(catta::json::Token::colon());
            case OVER_TEMPRATURE_SHUTDOWN + 25:
                return handle(_overTempratureShutdownSerializer, input.overTempratureShutdown(), catta::json::Token::comma());
            case DIFFERENCE_GRID_VOLTAGE + 0:
                return next(catta::json::Token::openString());
            case DIFFERENCE_GRID_VOLTAGE + 1:
                return next(catta::json::Token::character('d'));
            case DIFFERENCE_GRID_VOLTAGE + 2:
                return next(catta::json::Token::character('i'));
            case DIFFERENCE_GRID_VOLTAGE + 3:
                return next(catta::json::Token::character('f'));
            case DIFFERENCE_GRID_VOLTAGE + 4:
                return next(catta::json::Token::character('f'));
            case DIFFERENCE_GRID_VOLTAGE + 5:
                return next(catta::json::Token::character('e'));
            case DIFFERENCE_GRID_VOLTAGE + 6:
                return next(catta::json::Token::character('r'));
            case DIFFERENCE_GRID_VOLTAGE + 7:
                return next(catta::json::Token::character('e'));
            case DIFFERENCE_GRID_VOLTAGE + 8:
                return next(catta::json::Token::character('n'));
            case DIFFERENCE_GRID_VOLTAGE + 9:
                return next(catta::json::Token::character('c'));
            case DIFFERENCE_GRID_VOLTAGE + 10:
                return next(catta::json::Token::character('e'));
            case DIFFERENCE_GRID_VOLTAGE + 11:
                return next(catta::json::Token::character('G'));
            case DIFFERENCE_GRID_VOLTAGE + 12:
                return next(catta::json::Token::character('r'));
            case DIFFERENCE_GRID_VOLTAGE + 13:
                return next(catta::json::Token::character('i'));
            case DIFFERENCE_GRID_VOLTAGE + 14:
                return next(catta::json::Token::character('d'));
            case DIFFERENCE_GRID_VOLTAGE + 15:
                return next(catta::json::Token::character('V'));
            case DIFFERENCE_GRID_VOLTAGE + 16:
                return next(catta::json::Token::character('o'));
            case DIFFERENCE_GRID_VOLTAGE + 17:
                return next(catta::json::Token::character('l'));
            case DIFFERENCE_GRID_VOLTAGE + 18:
                return next(catta::json::Token::character('t'));
            case DIFFERENCE_GRID_VOLTAGE + 19:
                return next(catta::json::Token::character('a'));
            case DIFFERENCE_GRID_VOLTAGE + 20:
                return next(catta::json::Token::character('g'));
            case DIFFERENCE_GRID_VOLTAGE + 21:
                return next(catta::json::Token::character('e'));
            case DIFFERENCE_GRID_VOLTAGE + 22:
                return next(catta::json::Token::closeString());
            case DIFFERENCE_GRID_VOLTAGE + 23:
                return next(catta::json::Token::colon());
            case DIFFERENCE_GRID_VOLTAGE + 24:
                return handle(_differenceGridVoltageSerializer, input.differenceGridVoltage(), catta::json::Token::comma());
            case ERROR_GRID_RELAIS + 0:
                return next(catta::json::Token::openString());
            case ERROR_GRID_RELAIS + 1:
                return next(catta::json::Token::character('e'));
            case ERROR_GRID_RELAIS + 2:
                return next(catta::json::Token::character('r'));
            case ERROR_GRID_RELAIS + 3:
                return next(catta::json::Token::character('r'));
            case ERROR_GRID_RELAIS + 4:
                return next(catta::json::Token::character('o'));
            case ERROR_GRID_RELAIS + 5:
                return next(catta::json::Token::character('r'));
            case ERROR_GRID_RELAIS + 6:
                return next(catta::json::Token::character('G'));
            case ERROR_GRID_RELAIS + 7:
                return next(catta::json::Token::character('r'));
            case ERROR_GRID_RELAIS + 8:
                return next(catta::json::Token::character('i'));
            case ERROR_GRID_RELAIS + 9:
                return next(catta::json::Token::character('d'));
            case ERROR_GRID_RELAIS + 10:
                return next(catta::json::Token::character('R'));
            case ERROR_GRID_RELAIS + 11:
                return next(catta::json::Token::character('e'));
            case ERROR_GRID_RELAIS + 12:
                return next(catta::json::Token::character('l'));
            case ERROR_GRID_RELAIS + 13:
                return next(catta::json::Token::character('a'));
            case ERROR_GRID_RELAIS + 14:
                return next(catta::json::Token::character('i'));
            case ERROR_GRID_RELAIS + 15:
                return next(catta::json::Token::character('s'));
            case ERROR_GRID_RELAIS + 16:
                return next(catta::json::Token::closeString());
            case ERROR_GRID_RELAIS + 17:
                return next(catta::json::Token::colon());
            case ERROR_GRID_RELAIS + 18:
                return handle(_errorGridRelaisSerializer, input.errorGridRelais(), catta::json::Token::comma());
            case ERROR_CURRENT_SENSOR + 0:
                return next(catta::json::Token::openString());
            case ERROR_CURRENT_SENSOR + 1:
                return next(catta::json::Token::character('e'));
            case ERROR_CURRENT_SENSOR + 2:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 3:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 4:
                return next(catta::json::Token::character('o'));
            case ERROR_CURRENT_SENSOR + 5:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 6:
                return next(catta::json::Token::character('C'));
            case ERROR_CURRENT_SENSOR + 7:
                return next(catta::json::Token::character('u'));
            case ERROR_CURRENT_SENSOR + 8:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 9:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 10:
                return next(catta::json::Token::character('e'));
            case ERROR_CURRENT_SENSOR + 11:
                return next(catta::json::Token::character('n'));
            case ERROR_CURRENT_SENSOR + 12:
                return next(catta::json::Token::character('t'));
            case ERROR_CURRENT_SENSOR + 13:
                return next(catta::json::Token::character('S'));
            case ERROR_CURRENT_SENSOR + 14:
                return next(catta::json::Token::character('e'));
            case ERROR_CURRENT_SENSOR + 15:
                return next(catta::json::Token::character('n'));
            case ERROR_CURRENT_SENSOR + 16:
                return next(catta::json::Token::character('s'));
            case ERROR_CURRENT_SENSOR + 17:
                return next(catta::json::Token::character('o'));
            case ERROR_CURRENT_SENSOR + 18:
                return next(catta::json::Token::character('r'));
            case ERROR_CURRENT_SENSOR + 19:
                return next(catta::json::Token::closeString());
            case ERROR_CURRENT_SENSOR + 20:
                return next(catta::json::Token::colon());
            case ERROR_CURRENT_SENSOR + 21:
                return handle(_errorCurrentSensorSerializer, input.errorCurrentSensor(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _overVoltageACSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _underVoltageACSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _overVoltageDCSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _underVoltageDCSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _overFrequencySerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _underFrequencySerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _limitedPowerT1Serializer;
    Serializer<catta::modbus::sunspec::ValueU16> _limitedPowerT2Serializer;
    Serializer<catta::modbus::sunspec::ValueU16> _limitedPowerT3Serializer;
    Serializer<catta::modbus::sunspec::ValueU16> _limitedPowerT4Serializer;
    Serializer<catta::modbus::sunspec::ValueU16> _limitedPowerT5Serializer;
    Serializer<catta::modbus::sunspec::ValueU16> _comSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _islandGridSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _overCurrentInterruptSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _overVoltageInterruptSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _averageGridOverVoltageSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _overTempratureShutdownSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _differenceGridVoltageSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _errorGridRelaisSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _errorCurrentSensorSerializer;
    static constexpr std::uint16_t START = 0;
    static constexpr std::uint16_t OVER_VOLTAGE_A_C = START + 1;
    static constexpr std::uint16_t UNDER_VOLTAGE_A_C = OVER_VOLTAGE_A_C + 17;
    static constexpr std::uint16_t OVER_VOLTAGE_D_C = UNDER_VOLTAGE_A_C + 18;
    static constexpr std::uint16_t UNDER_VOLTAGE_D_C = OVER_VOLTAGE_D_C + 17;
    static constexpr std::uint16_t OVER_FREQUENCY = UNDER_VOLTAGE_D_C + 18;
    static constexpr std::uint16_t UNDER_FREQUENCY = OVER_FREQUENCY + 17;
    static constexpr std::uint16_t LIMITED_POWER_T1 = UNDER_FREQUENCY + 18;
    static constexpr std::uint16_t LIMITED_POWER_T2 = LIMITED_POWER_T1 + 18;
    static constexpr std::uint16_t LIMITED_POWER_T3 = LIMITED_POWER_T2 + 18;
    static constexpr std::uint16_t LIMITED_POWER_T4 = LIMITED_POWER_T3 + 18;
    static constexpr std::uint16_t LIMITED_POWER_T5 = LIMITED_POWER_T4 + 18;
    static constexpr std::uint16_t COM = LIMITED_POWER_T5 + 18;
    static constexpr std::uint16_t ISLAND_GRID = COM + 7;
    static constexpr std::uint16_t OVER_CURRENT_INTERRUPT = ISLAND_GRID + 14;
    static constexpr std::uint16_t OVER_VOLTAGE_INTERRUPT = OVER_CURRENT_INTERRUPT + 24;
    static constexpr std::uint16_t AVERAGE_GRID_OVER_VOLTAGE = OVER_VOLTAGE_INTERRUPT + 24;
    static constexpr std::uint16_t OVER_TEMPRATURE_SHUTDOWN = AVERAGE_GRID_OVER_VOLTAGE + 26;
    static constexpr std::uint16_t DIFFERENCE_GRID_VOLTAGE = OVER_TEMPRATURE_SHUTDOWN + 26;
    static constexpr std::uint16_t ERROR_GRID_RELAIS = DIFFERENCE_GRID_VOLTAGE + 25;
    static constexpr std::uint16_t ERROR_CURRENT_SENSOR = ERROR_GRID_RELAIS + 19;
    static constexpr std::uint16_t TAIL = ERROR_CURRENT_SENSOR + 22;
    static constexpr std::uint16_t DONE = TAIL + 1;
    static constexpr std::uint16_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
