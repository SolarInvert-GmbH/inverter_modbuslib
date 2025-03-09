#pragma once

// si
#include <catta/modbus/si/PhysicalQuantety.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <const char* UNIT>
class Serializer<catta::modbus::si::PhysicalQuantety<UNIT>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::PhysicalQuantety<UNIT>;
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
        const auto handle = [this, stay, next]()
        {
            const char c = *_string;
            _string++;
            return c == '\0' ? next(catta::json::Token::closeString()) : stay(catta::json::Token::character(static_cast<char32_t>(c)));
        };
        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
            case QUANTETY + 0:
                return next(catta::json::Token::openString());
            case QUANTETY + 1:
                return next(catta::json::Token::character('Q'));
            case QUANTETY + 2:
                return next(catta::json::Token::character('u'));
            case QUANTETY + 3:
                return next(catta::json::Token::character('a'));
            case QUANTETY + 4:
                return next(catta::json::Token::character('n'));
            case QUANTETY + 5:
                return next(catta::json::Token::character('t'));
            case QUANTETY + 6:
                return next(catta::json::Token::character('e'));
            case QUANTETY + 7:
                return next(catta::json::Token::character('t'));
            case QUANTETY + 8:
                return next(catta::json::Token::character('y'));
            case QUANTETY + 9:
                return next(catta::json::Token::closeString());
            case QUANTETY + 10:
                return next(catta::json::Token::colon());
            case QUANTETY + 11:
                return next(catta::json::Token::floatNumber(input.quantety()));
            case QUANTETY + 12:
                return next(catta::json::Token::comma());
            case U + 0:
                return next(catta::json::Token::openString());
            case U + 1:
                return next(catta::json::Token::character('U'));
            case U + 2:
                return next(catta::json::Token::character('n'));
            case U + 3:
                return next(catta::json::Token::character('i'));
            case U + 4:
                return next(catta::json::Token::character('t'));
            case U + 5:
                return next(catta::json::Token::closeString());
            case U + 6:
                return next(catta::json::Token::colon());
            case U + 7:
                return next(catta::json::Token::openString());
            case U + 8:
                return handle();
            case U + 9:
                return next(catta::json::Token::closeCurlyBracket());
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _data(Output::empty()), _string(UNIT) {}
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
    const char* _string;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t QUANTETY = START + 1;
    static constexpr std::uint8_t U = QUANTETY + 13;
    static constexpr std::uint8_t TAIL = U + 10;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
