#pragma once

// si
#include <catta/modbus/si/PowerConfig.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::PowerConfig>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::PowerConfig;
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
        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
            case CHARGING + 0:
                return next(catta::json::Token::openString());
            case CHARGING + 1:
                return next(catta::json::Token::character('C'));
            case CHARGING + 2:
                return next(catta::json::Token::character('h'));
            case CHARGING + 3:
                return next(catta::json::Token::character('a'));
            case CHARGING + 4:
                return next(catta::json::Token::character('r'));
            case CHARGING + 5:
                return next(catta::json::Token::character('g'));
            case CHARGING + 6:
                return next(catta::json::Token::character('i'));
            case CHARGING + 7:
                return next(catta::json::Token::character('n'));
            case CHARGING + 8:
                return next(catta::json::Token::character('g'));
            case CHARGING + 9:
                return next(catta::json::Token::closeString());
            case CHARGING + 10:
                return next(catta::json::Token::colon());
            case CHARGING + 11:
                return next(input.charging() ? catta::json::Token::boolTrue() : catta::json::Token::boolFalse());
            case CHARGING + 12:
                return next(catta::json::Token::comma());
            case POWER + 0:
                return next(catta::json::Token::openString());
            case POWER + 1:
                return next(catta::json::Token::character('P'));
            case POWER + 2:
                return next(catta::json::Token::character('o'));
            case POWER + 3:
                return next(catta::json::Token::character('w'));
            case POWER + 4:
                return next(catta::json::Token::character('e'));
            case POWER + 5:
                return next(catta::json::Token::character('r'));
            case POWER + 6:
                return next(catta::json::Token::closeString());
            case POWER + 7:
                return next(catta::json::Token::colon());
            case POWER + 8:
                return next(catta::json::Token::integerNumber(input.power()));
            case POWER + 9:
                return next(catta::json::Token::closeCurlyBracket());
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
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t CHARGING = START + 1;
    static constexpr std::uint8_t POWER = CHARGING + 13;
    static constexpr std::uint8_t TAIL = POWER + 10;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
