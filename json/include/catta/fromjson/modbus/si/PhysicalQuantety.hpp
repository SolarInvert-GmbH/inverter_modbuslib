#pragma once

// si
#include <catta/modbus/si/PhysicalQuantety.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <const char* UNIT>
class Parser<catta::modbus::si::PhysicalQuantety<UNIT>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::PhysicalQuantety<UNIT>;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto handleNumber = [next, error, input, this]()
        {
            switch (input.type())
            {
                case catta::json::TokenType::integerNumber():
                    _quantety = Output::create(static_cast<double>(input.integerValue()));
                    return next();
                case catta::json::TokenType::floatNumber():
                    _quantety = Output::create(input.floatValue());
                    return next();
                default:
                    return error();
            }
        };
        const auto handleString = [stay, next, error, input, this]()
        {
            const char c = *_string;
            if (c == '\0')
                return input == catta::json::Token::closeString() ? next() : error();
            else
            {
                _string++;
                return input == catta::json::Token::character(static_cast<char32_t>(c)) ? stay() : error();
            }
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('Q') ? next() : input == catta::json::Token::character('U') ? jump(HUB + 13) : error();
            case HUB + 2:
                return !_quantety.isEmpty() ? error() : input == catta::json::Token::character('u') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('a') ? next() : error();
            case HUB + 4:
                return input == catta::json::Token::character('n') ? next() : error();
            case HUB + 5:
                return input == catta::json::Token::character('t') ? next() : error();
            case HUB + 6:
                return input == catta::json::Token::character('e') ? next() : error();
            case HUB + 7:
                return input == catta::json::Token::character('t') ? next() : error();
            case HUB + 8:
                return input == catta::json::Token::character('y') ? next() : error();
            case HUB + 9:
                return input == catta::json::Token::closeString() ? next() : error();
            case HUB + 10:
                return input == catta::json::Token::colon() ? next() : error();
            case HUB + 11:
                return handleNumber();
            case HUB + 12:
                return input == catta::json::Token::comma()               ? jump(HUB + 0)
                       : input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                                                                          : error();
            case HUB + 13:
                return *_string == '\0' ? error() : input == catta::json::Token::character('n') ? next() : error();
            case HUB + 14:
                return input == catta::json::Token::character('i') ? next() : error();
            case HUB + 15:
                return input == catta::json::Token::character('t') ? next() : error();
            case HUB + 16:
                return input == catta::json::Token::closeString() ? next() : error();
            case HUB + 17:
                return input == catta::json::Token::colon() ? next() : error();
            case HUB + 18:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 19:
                return handleString();
            case HUB + 20:
                return input == catta::json::Token::comma()               ? jump(HUB + 0)
                       : input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                                                                          : error();
            case TAIL + 0:
                return *_string != '\0' || _quantety.isEmpty() ? error() : input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _quantety(Output::empty()), _string(UNIT) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? _quantety : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    Output _quantety;
    const char* _string;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 21;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
    static constexpr std::uint16_t EMPTY_POWER = 3201;
    // static constexpr Output EMPTY_QUANTETY = Output::empty();
};
}  // namespace fromjson
}  // namespace catta
