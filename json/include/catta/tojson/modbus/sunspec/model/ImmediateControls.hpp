#pragma once

// model
#include <catta/modbus/sunspec/model/ImmediateControls.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::ImmediateControls>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::ImmediateControls;
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
            case TIMEOUT_CONNECTION + 0:
                return next(catta::json::Token::openString());
            case TIMEOUT_CONNECTION + 1:
                return next(catta::json::Token::character('t'));
            case TIMEOUT_CONNECTION + 2:
                return next(catta::json::Token::character('i'));
            case TIMEOUT_CONNECTION + 3:
                return next(catta::json::Token::character('m'));
            case TIMEOUT_CONNECTION + 4:
                return next(catta::json::Token::character('e'));
            case TIMEOUT_CONNECTION + 5:
                return next(catta::json::Token::character('o'));
            case TIMEOUT_CONNECTION + 6:
                return next(catta::json::Token::character('u'));
            case TIMEOUT_CONNECTION + 7:
                return next(catta::json::Token::character('t'));
            case TIMEOUT_CONNECTION + 8:
                return next(catta::json::Token::character('C'));
            case TIMEOUT_CONNECTION + 9:
                return next(catta::json::Token::character('o'));
            case TIMEOUT_CONNECTION + 10:
                return next(catta::json::Token::character('n'));
            case TIMEOUT_CONNECTION + 11:
                return next(catta::json::Token::character('n'));
            case TIMEOUT_CONNECTION + 12:
                return next(catta::json::Token::character('e'));
            case TIMEOUT_CONNECTION + 13:
                return next(catta::json::Token::character('c'));
            case TIMEOUT_CONNECTION + 14:
                return next(catta::json::Token::character('t'));
            case TIMEOUT_CONNECTION + 15:
                return next(catta::json::Token::character('i'));
            case TIMEOUT_CONNECTION + 16:
                return next(catta::json::Token::character('o'));
            case TIMEOUT_CONNECTION + 17:
                return next(catta::json::Token::character('n'));
            case TIMEOUT_CONNECTION + 18:
                return next(catta::json::Token::closeString());
            case TIMEOUT_CONNECTION + 19:
                return next(catta::json::Token::colon());
            case TIMEOUT_CONNECTION + 20:
                return handle(_timeoutConnectionSerializer, input.timeoutConnection(), catta::json::Token::comma());
            case CONNECTION_CONTROL + 0:
                return next(catta::json::Token::openString());
            case CONNECTION_CONTROL + 1:
                return next(catta::json::Token::character('c'));
            case CONNECTION_CONTROL + 2:
                return next(catta::json::Token::character('o'));
            case CONNECTION_CONTROL + 3:
                return next(catta::json::Token::character('n'));
            case CONNECTION_CONTROL + 4:
                return next(catta::json::Token::character('n'));
            case CONNECTION_CONTROL + 5:
                return next(catta::json::Token::character('e'));
            case CONNECTION_CONTROL + 6:
                return next(catta::json::Token::character('c'));
            case CONNECTION_CONTROL + 7:
                return next(catta::json::Token::character('t'));
            case CONNECTION_CONTROL + 8:
                return next(catta::json::Token::character('i'));
            case CONNECTION_CONTROL + 9:
                return next(catta::json::Token::character('o'));
            case CONNECTION_CONTROL + 10:
                return next(catta::json::Token::character('n'));
            case CONNECTION_CONTROL + 11:
                return next(catta::json::Token::character('C'));
            case CONNECTION_CONTROL + 12:
                return next(catta::json::Token::character('o'));
            case CONNECTION_CONTROL + 13:
                return next(catta::json::Token::character('n'));
            case CONNECTION_CONTROL + 14:
                return next(catta::json::Token::character('t'));
            case CONNECTION_CONTROL + 15:
                return next(catta::json::Token::character('r'));
            case CONNECTION_CONTROL + 16:
                return next(catta::json::Token::character('o'));
            case CONNECTION_CONTROL + 17:
                return next(catta::json::Token::character('l'));
            case CONNECTION_CONTROL + 18:
                return next(catta::json::Token::closeString());
            case CONNECTION_CONTROL + 19:
                return next(catta::json::Token::colon());
            case CONNECTION_CONTROL + 20:
                return handle(_connectionControlSerializer, input.connectionControl(), catta::json::Token::comma());
            case POWER_LIMIT + 0:
                return next(catta::json::Token::openString());
            case POWER_LIMIT + 1:
                return next(catta::json::Token::character('p'));
            case POWER_LIMIT + 2:
                return next(catta::json::Token::character('o'));
            case POWER_LIMIT + 3:
                return next(catta::json::Token::character('w'));
            case POWER_LIMIT + 4:
                return next(catta::json::Token::character('e'));
            case POWER_LIMIT + 5:
                return next(catta::json::Token::character('r'));
            case POWER_LIMIT + 6:
                return next(catta::json::Token::character('L'));
            case POWER_LIMIT + 7:
                return next(catta::json::Token::character('i'));
            case POWER_LIMIT + 8:
                return next(catta::json::Token::character('m'));
            case POWER_LIMIT + 9:
                return next(catta::json::Token::character('i'));
            case POWER_LIMIT + 10:
                return next(catta::json::Token::character('t'));
            case POWER_LIMIT + 11:
                return next(catta::json::Token::closeString());
            case POWER_LIMIT + 12:
                return next(catta::json::Token::colon());
            case POWER_LIMIT + 13:
                return handle(_powerLimitSerializer, input.powerLimit(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _timeoutConnectionSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _connectionControlSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _powerLimitSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TIMEOUT_CONNECTION = START + 1;
    static constexpr std::uint8_t CONNECTION_CONTROL = TIMEOUT_CONNECTION + 21;
    static constexpr std::uint8_t POWER_LIMIT = CONNECTION_CONTROL + 21;
    static constexpr std::uint8_t TAIL = POWER_LIMIT + 14;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
