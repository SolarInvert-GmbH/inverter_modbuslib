#pragma once

// si
#include <catta/modbus/si/Type.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::Type>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::Type;
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
        const auto jump = [stay, this](const catta::json::Token token, const std::uint8_t state)
        {
            _state = state;
            return stay(token);
        };
        const auto start = [stay, this, input](const catta::json::Token token)
        {
            switch (input)
            {
                case 0:
                    _state = SOLAR + 0;
                    break;
                case 1:
                    _state = WIND + 0;
                    break;
                default:
                    _state = BATTERY + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? jump(catta::json::Token::nullObject(), TAIL + 1) : start(catta::json::Token::openString());
            case SOLAR + 0:
                return next(catta::json::Token::character('s'));
            case SOLAR + 1:
                return next(catta::json::Token::character('o'));
            case SOLAR + 2:
                return next(catta::json::Token::character('l'));
            case SOLAR + 3:
                return next(catta::json::Token::character('a'));
            case SOLAR + 4:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case WIND + 0:
                return next(catta::json::Token::character('w'));
            case WIND + 1:
                return next(catta::json::Token::character('i'));
            case WIND + 2:
                return next(catta::json::Token::character('n'));
            case WIND + 3:
                return jump(catta::json::Token::character('d'), TAIL + 0);
            case BATTERY + 0:
                return next(catta::json::Token::character('b'));
            case BATTERY + 1:
                return next(catta::json::Token::character('a'));
            case BATTERY + 2:
                return next(catta::json::Token::character('t'));
            case BATTERY + 3:
                return next(catta::json::Token::character('t'));
            case BATTERY + 4:
                return next(catta::json::Token::character('e'));
            case BATTERY + 5:
                return next(catta::json::Token::character('r'));
            case BATTERY + 6:
                return jump(catta::json::Token::character('y'), TAIL + 0);
            case TAIL + 0:
                return next(catta::json::Token::closeString());
            case TAIL + 1:
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
    static constexpr std::uint8_t SOLAR = START + 1;
    static constexpr std::uint8_t WIND = SOLAR + 5;
    static constexpr std::uint8_t BATTERY = WIND + 4;
    static constexpr std::uint8_t TAIL = BATTERY + 7;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
