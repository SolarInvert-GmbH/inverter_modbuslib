#pragma once

// model
#include <catta/modbus/sunspec/model/Storage.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::Storage>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::Storage;
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
            case W_CHA_MAX + 0:
                return next(catta::json::Token::openString());
            case W_CHA_MAX + 1:
                return next(catta::json::Token::character('w'));
            case W_CHA_MAX + 2:
                return next(catta::json::Token::character('C'));
            case W_CHA_MAX + 3:
                return next(catta::json::Token::character('h'));
            case W_CHA_MAX + 4:
                return next(catta::json::Token::character('a'));
            case W_CHA_MAX + 5:
                return next(catta::json::Token::character('M'));
            case W_CHA_MAX + 6:
                return next(catta::json::Token::character('a'));
            case W_CHA_MAX + 7:
                return next(catta::json::Token::character('x'));
            case W_CHA_MAX + 8:
                return next(catta::json::Token::closeString());
            case W_CHA_MAX + 9:
                return next(catta::json::Token::colon());
            case W_CHA_MAX + 10:
                return handle(_wChaMaxSerializer, input.wChaMax(), catta::json::Token::comma());
            case W_CHA_RATE + 0:
                return next(catta::json::Token::openString());
            case W_CHA_RATE + 1:
                return next(catta::json::Token::character('w'));
            case W_CHA_RATE + 2:
                return next(catta::json::Token::character('C'));
            case W_CHA_RATE + 3:
                return next(catta::json::Token::character('h'));
            case W_CHA_RATE + 4:
                return next(catta::json::Token::character('a'));
            case W_CHA_RATE + 5:
                return next(catta::json::Token::character('R'));
            case W_CHA_RATE + 6:
                return next(catta::json::Token::character('a'));
            case W_CHA_RATE + 7:
                return next(catta::json::Token::character('t'));
            case W_CHA_RATE + 8:
                return next(catta::json::Token::character('e'));
            case W_CHA_RATE + 9:
                return next(catta::json::Token::closeString());
            case W_CHA_RATE + 10:
                return next(catta::json::Token::colon());
            case W_CHA_RATE + 11:
                return handle(_wChaRateSerializer, input.wChaRate(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _wChaMaxSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _wChaRateSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t W_CHA_MAX = START + 1;
    static constexpr std::uint8_t W_CHA_RATE = W_CHA_MAX + 11;
    static constexpr std::uint8_t TAIL = W_CHA_RATE + 12;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
