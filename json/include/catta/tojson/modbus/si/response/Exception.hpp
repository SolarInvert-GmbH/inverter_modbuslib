#pragma once

// response
#include <catta/modbus/si/response/Exception.hpp>

// tojson
#include <catta/tojson/modbus/si/request/Type.hpp>
#include <catta/tojson/modbus/si/response/ExceptionValue.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::Exception>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::Exception;
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
            case VALUE + 0:
                return next(catta::json::Token::openString());
            case VALUE + 1:
                return next(catta::json::Token::character('v'));
            case VALUE + 2:
                return next(catta::json::Token::character('a'));
            case VALUE + 3:
                return next(catta::json::Token::character('l'));
            case VALUE + 4:
                return next(catta::json::Token::character('u'));
            case VALUE + 5:
                return next(catta::json::Token::character('e'));
            case VALUE + 6:
                return next(catta::json::Token::closeString());
            case VALUE + 7:
                return next(catta::json::Token::colon());
            case VALUE + 8:
                return handle(_valueSerializer, input.value(), catta::json::Token::comma());
            case REQUEST + 0:
                return next(catta::json::Token::openString());
            case REQUEST + 1:
                return next(catta::json::Token::character('r'));
            case REQUEST + 2:
                return next(catta::json::Token::character('e'));
            case REQUEST + 3:
                return next(catta::json::Token::character('q'));
            case REQUEST + 4:
                return next(catta::json::Token::character('u'));
            case REQUEST + 5:
                return next(catta::json::Token::character('e'));
            case REQUEST + 6:
                return next(catta::json::Token::character('s'));
            case REQUEST + 7:
                return next(catta::json::Token::character('t'));
            case REQUEST + 8:
                return next(catta::json::Token::closeString());
            case REQUEST + 9:
                return next(catta::json::Token::colon());
            case REQUEST + 10:
                return handle(_requestSerializer, input.request(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::si::response::ExceptionValue> _valueSerializer;
    Serializer<catta::modbus::si::request::Type> _requestSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t VALUE = START + 1;
    static constexpr std::uint8_t REQUEST = VALUE + 9;
    static constexpr std::uint8_t TAIL = REQUEST + 11;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
