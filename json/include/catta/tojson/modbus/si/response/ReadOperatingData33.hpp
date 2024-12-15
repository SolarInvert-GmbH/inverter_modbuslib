#pragma once

// response
#include <catta/modbus/si/response/ReadOperatingData33.hpp>

// tojson
#include <catta/tojson/modbus/si/State.hpp>
#include <catta/tojson/modbus/sunspec/ValueS16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::ReadOperatingData33>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::ReadOperatingData33;
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
            case AC_VOLTAGE + 0:
                return next(catta::json::Token::openString());
            case AC_VOLTAGE + 1:
                return next(catta::json::Token::character('a'));
            case AC_VOLTAGE + 2:
                return next(catta::json::Token::character('c'));
            case AC_VOLTAGE + 3:
                return next(catta::json::Token::character('V'));
            case AC_VOLTAGE + 4:
                return next(catta::json::Token::character('o'));
            case AC_VOLTAGE + 5:
                return next(catta::json::Token::character('l'));
            case AC_VOLTAGE + 6:
                return next(catta::json::Token::character('t'));
            case AC_VOLTAGE + 7:
                return next(catta::json::Token::character('a'));
            case AC_VOLTAGE + 8:
                return next(catta::json::Token::character('g'));
            case AC_VOLTAGE + 9:
                return next(catta::json::Token::character('e'));
            case AC_VOLTAGE + 10:
                return next(catta::json::Token::closeString());
            case AC_VOLTAGE + 11:
                return next(catta::json::Token::colon());
            case AC_VOLTAGE + 12:
                return handle(_acVoltageSerializer, input.acVoltage(), catta::json::Token::comma());
            case GRID_FREQUENCY + 0:
                return next(catta::json::Token::openString());
            case GRID_FREQUENCY + 1:
                return next(catta::json::Token::character('g'));
            case GRID_FREQUENCY + 2:
                return next(catta::json::Token::character('r'));
            case GRID_FREQUENCY + 3:
                return next(catta::json::Token::character('i'));
            case GRID_FREQUENCY + 4:
                return next(catta::json::Token::character('d'));
            case GRID_FREQUENCY + 5:
                return next(catta::json::Token::character('F'));
            case GRID_FREQUENCY + 6:
                return next(catta::json::Token::character('r'));
            case GRID_FREQUENCY + 7:
                return next(catta::json::Token::character('e'));
            case GRID_FREQUENCY + 8:
                return next(catta::json::Token::character('q'));
            case GRID_FREQUENCY + 9:
                return next(catta::json::Token::character('u'));
            case GRID_FREQUENCY + 10:
                return next(catta::json::Token::character('e'));
            case GRID_FREQUENCY + 11:
                return next(catta::json::Token::character('n'));
            case GRID_FREQUENCY + 12:
                return next(catta::json::Token::character('c'));
            case GRID_FREQUENCY + 13:
                return next(catta::json::Token::character('y'));
            case GRID_FREQUENCY + 14:
                return next(catta::json::Token::closeString());
            case GRID_FREQUENCY + 15:
                return next(catta::json::Token::colon());
            case GRID_FREQUENCY + 16:
                return handle(_gridFrequencySerializer, input.gridFrequency(), catta::json::Token::comma());
            case AC_POWER + 0:
                return next(catta::json::Token::openString());
            case AC_POWER + 1:
                return next(catta::json::Token::character('a'));
            case AC_POWER + 2:
                return next(catta::json::Token::character('c'));
            case AC_POWER + 3:
                return next(catta::json::Token::character('P'));
            case AC_POWER + 4:
                return next(catta::json::Token::character('o'));
            case AC_POWER + 5:
                return next(catta::json::Token::character('w'));
            case AC_POWER + 6:
                return next(catta::json::Token::character('e'));
            case AC_POWER + 7:
                return next(catta::json::Token::character('r'));
            case AC_POWER + 8:
                return next(catta::json::Token::closeString());
            case AC_POWER + 9:
                return next(catta::json::Token::colon());
            case AC_POWER + 10:
                return handle(_acPowerSerializer, input.acPower(), catta::json::Token::comma());
            case STATE + 0:
                return next(catta::json::Token::openString());
            case STATE + 1:
                return next(catta::json::Token::character('s'));
            case STATE + 2:
                return next(catta::json::Token::character('t'));
            case STATE + 3:
                return next(catta::json::Token::character('a'));
            case STATE + 4:
                return next(catta::json::Token::character('t'));
            case STATE + 5:
                return next(catta::json::Token::character('e'));
            case STATE + 6:
                return next(catta::json::Token::closeString());
            case STATE + 7:
                return next(catta::json::Token::colon());
            case STATE + 8:
                return handle(_stateSerializer, input.state(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _dcVoltageSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 255>> _acVoltageSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _gridFrequencySerializer;
    Serializer<catta::modbus::sunspec::ValueS16> _acPowerSerializer;
    Serializer<catta::modbus::si::State> _stateSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DC_VOLTAGE = START + 1;
    static constexpr std::uint8_t AC_VOLTAGE = DC_VOLTAGE + 13;
    static constexpr std::uint8_t GRID_FREQUENCY = AC_VOLTAGE + 13;
    static constexpr std::uint8_t AC_POWER = GRID_FREQUENCY + 17;
    static constexpr std::uint8_t STATE = AC_POWER + 11;
    static constexpr std::uint8_t TAIL = STATE + 9;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
