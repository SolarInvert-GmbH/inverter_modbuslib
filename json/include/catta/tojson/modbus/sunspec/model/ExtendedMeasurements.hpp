#pragma once

// model
#include <catta/modbus/sunspec/model/ExtendedMeasurements.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU64.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::ExtendedMeasurements>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::ExtendedMeasurements;
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
            case AC_WATTHOURS + 0:
                return next(catta::json::Token::openString());
            case AC_WATTHOURS + 1:
                return next(catta::json::Token::character('a'));
            case AC_WATTHOURS + 2:
                return next(catta::json::Token::character('c'));
            case AC_WATTHOURS + 3:
                return next(catta::json::Token::character('W'));
            case AC_WATTHOURS + 4:
                return next(catta::json::Token::character('a'));
            case AC_WATTHOURS + 5:
                return next(catta::json::Token::character('t'));
            case AC_WATTHOURS + 6:
                return next(catta::json::Token::character('t'));
            case AC_WATTHOURS + 7:
                return next(catta::json::Token::character('h'));
            case AC_WATTHOURS + 8:
                return next(catta::json::Token::character('o'));
            case AC_WATTHOURS + 9:
                return next(catta::json::Token::character('u'));
            case AC_WATTHOURS + 10:
                return next(catta::json::Token::character('r'));
            case AC_WATTHOURS + 11:
                return next(catta::json::Token::character('s'));
            case AC_WATTHOURS + 12:
                return next(catta::json::Token::closeString());
            case AC_WATTHOURS + 13:
                return next(catta::json::Token::colon());
            case AC_WATTHOURS + 14:
                return handle(_acWatthoursSerializer, input.acWatthours(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU64> _acWatthoursSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t AC_WATTHOURS = START + 1;
    static constexpr std::uint8_t TAIL = AC_WATTHOURS + 15;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
