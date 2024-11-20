#pragma once

// si
#include <catta/modbus/si/Date.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::Date>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::Date;
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
            case DAY + 0:
                return next(catta::json::Token::openString());
            case DAY + 1:
                return next(catta::json::Token::character('d'));
            case DAY + 2:
                return next(catta::json::Token::character('a'));
            case DAY + 3:
                return next(catta::json::Token::character('y'));
            case DAY + 4:
                return next(catta::json::Token::closeString());
            case DAY + 5:
                return next(catta::json::Token::colon());
            case DAY + 6:
                return handle(_daySerializer, input.day(), catta::json::Token::comma());
            case MONTH + 0:
                return next(catta::json::Token::openString());
            case MONTH + 1:
                return next(catta::json::Token::character('m'));
            case MONTH + 2:
                return next(catta::json::Token::character('o'));
            case MONTH + 3:
                return next(catta::json::Token::character('n'));
            case MONTH + 4:
                return next(catta::json::Token::character('t'));
            case MONTH + 5:
                return next(catta::json::Token::character('h'));
            case MONTH + 6:
                return next(catta::json::Token::closeString());
            case MONTH + 7:
                return next(catta::json::Token::colon());
            case MONTH + 8:
                return handle(_monthSerializer, input.month(), catta::json::Token::comma());
            case YEAR + 0:
                return next(catta::json::Token::openString());
            case YEAR + 1:
                return next(catta::json::Token::character('y'));
            case YEAR + 2:
                return next(catta::json::Token::character('e'));
            case YEAR + 3:
                return next(catta::json::Token::character('a'));
            case YEAR + 4:
                return next(catta::json::Token::character('r'));
            case YEAR + 5:
                return next(catta::json::Token::closeString());
            case YEAR + 6:
                return next(catta::json::Token::colon());
            case YEAR + 7:
                return handle(_yearSerializer, input.year(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU8<1, 31>> _daySerializer;
    Serializer<catta::modbus::sunspec::ValueU8<1, 12>> _monthSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 99>> _yearSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DAY = START + 1;
    static constexpr std::uint8_t MONTH = DAY + 7;
    static constexpr std::uint8_t YEAR = MONTH + 9;
    static constexpr std::uint8_t TAIL = YEAR + 8;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
