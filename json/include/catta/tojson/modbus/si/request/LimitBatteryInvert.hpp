#pragma once

// request
#include <catta/modbus/si/request/LimitBatteryInvert.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::request::LimitBatteryInvert>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::request::LimitBatteryInvert;
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
            case P_MAXFEED + 0:
                return next(catta::json::Token::openString());
            case P_MAXFEED + 1:
                return next(catta::json::Token::character('p'));
            case P_MAXFEED + 2:
                return next(catta::json::Token::character('M'));
            case P_MAXFEED + 3:
                return next(catta::json::Token::character('a'));
            case P_MAXFEED + 4:
                return next(catta::json::Token::character('x'));
            case P_MAXFEED + 5:
                return next(catta::json::Token::character('f'));
            case P_MAXFEED + 6:
                return next(catta::json::Token::character('e'));
            case P_MAXFEED + 7:
                return next(catta::json::Token::character('e'));
            case P_MAXFEED + 8:
                return next(catta::json::Token::character('d'));
            case P_MAXFEED + 9:
                return next(catta::json::Token::closeString());
            case P_MAXFEED + 10:
                return next(catta::json::Token::colon());
            case P_MAXFEED + 11:
                return handle(_pMaxfeedSerializer, input.pMaxfeed(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU8<0, 100>> _pMaxfeedSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t P_MAXFEED = START + 1;
    static constexpr std::uint8_t TAIL = P_MAXFEED + 12;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
