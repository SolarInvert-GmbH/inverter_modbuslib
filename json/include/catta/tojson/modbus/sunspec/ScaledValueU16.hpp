#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaledValueU16.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ScaleFactor.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::ScaledValueU16>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::ScaledValueU16;
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
            case SCALE + 0:
                return next(catta::json::Token::openString());
            case SCALE + 1:
                return next(catta::json::Token::character('s'));
            case SCALE + 2:
                return next(catta::json::Token::character('c'));
            case SCALE + 3:
                return next(catta::json::Token::character('a'));
            case SCALE + 4:
                return next(catta::json::Token::character('l'));
            case SCALE + 5:
                return next(catta::json::Token::character('e'));
            case SCALE + 6:
                return next(catta::json::Token::closeString());
            case SCALE + 7:
                return next(catta::json::Token::colon());
            case SCALE + 8:
                return handle(_scaleSerializer, input.scale(), catta::json::Token::comma());
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
                return handle(_valueSerializer, input.value(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ScaleFactor> _scaleSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _valueSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t SCALE = START + 1;
    static constexpr std::uint8_t VALUE = SCALE + 9;
    static constexpr std::uint8_t TAIL = VALUE + 9;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
