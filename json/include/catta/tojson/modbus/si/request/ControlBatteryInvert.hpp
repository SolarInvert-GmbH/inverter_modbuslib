#pragma once

// request
#include <catta/modbus/si/request/ControlBatteryInvert.hpp>

// tojson
#include <catta/tojson/modbus/si/PowerConfig.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::request::ControlBatteryInvert>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::request::ControlBatteryInvert;
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
            case P_MAX + 0:
                return next(catta::json::Token::openString());
            case P_MAX + 1:
                return next(catta::json::Token::character('p'));
            case P_MAX + 2:
                return next(catta::json::Token::character('M'));
            case P_MAX + 3:
                return next(catta::json::Token::character('a'));
            case P_MAX + 4:
                return next(catta::json::Token::character('x'));
            case P_MAX + 5:
                return next(catta::json::Token::closeString());
            case P_MAX + 6:
                return next(catta::json::Token::colon());
            case P_MAX + 7:
                return handle(_pMaxSerializer, input.pMax(), catta::json::Token::comma());
            case U_MIN + 0:
                return next(catta::json::Token::openString());
            case U_MIN + 1:
                return next(catta::json::Token::character('u'));
            case U_MIN + 2:
                return next(catta::json::Token::character('M'));
            case U_MIN + 3:
                return next(catta::json::Token::character('i'));
            case U_MIN + 4:
                return next(catta::json::Token::character('n'));
            case U_MIN + 5:
                return next(catta::json::Token::closeString());
            case U_MIN + 6:
                return next(catta::json::Token::colon());
            case U_MIN + 7:
                return handle(_uMinSerializer, input.uMin(), catta::json::Token::comma());
            case U_MAX + 0:
                return next(catta::json::Token::openString());
            case U_MAX + 1:
                return next(catta::json::Token::character('u'));
            case U_MAX + 2:
                return next(catta::json::Token::character('M'));
            case U_MAX + 3:
                return next(catta::json::Token::character('a'));
            case U_MAX + 4:
                return next(catta::json::Token::character('x'));
            case U_MAX + 5:
                return next(catta::json::Token::closeString());
            case U_MAX + 6:
                return next(catta::json::Token::colon());
            case U_MAX + 7:
                return handle(_uMaxSerializer, input.uMax(), catta::json::Token::comma());
            case TIMEOUT + 0:
                return next(catta::json::Token::openString());
            case TIMEOUT + 1:
                return next(catta::json::Token::character('t'));
            case TIMEOUT + 2:
                return next(catta::json::Token::character('i'));
            case TIMEOUT + 3:
                return next(catta::json::Token::character('m'));
            case TIMEOUT + 4:
                return next(catta::json::Token::character('e'));
            case TIMEOUT + 5:
                return next(catta::json::Token::character('o'));
            case TIMEOUT + 6:
                return next(catta::json::Token::character('u'));
            case TIMEOUT + 7:
                return next(catta::json::Token::character('t'));
            case TIMEOUT + 8:
                return next(catta::json::Token::closeString());
            case TIMEOUT + 9:
                return next(catta::json::Token::colon());
            case TIMEOUT + 10:
                return handle(_timeoutSerializer, input.timeout(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::si::PowerConfig> _pMaxSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _uMinSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _uMaxSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _timeoutSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t P_MAX = START + 1;
    static constexpr std::uint8_t U_MIN = P_MAX + 8;
    static constexpr std::uint8_t U_MAX = U_MIN + 8;
    static constexpr std::uint8_t TIMEOUT = U_MAX + 8;
    static constexpr std::uint8_t TAIL = TIMEOUT + 11;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
