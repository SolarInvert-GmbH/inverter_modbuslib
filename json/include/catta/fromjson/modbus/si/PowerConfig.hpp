#pragma once

// si
#include <catta/modbus/si/PowerConfig.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::PowerConfig>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::PowerConfig;
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
            if (!input.type().isIntegerNumber()) return error();
            const auto n = input.integerValue();
            if (n < 0 || n > 3200) return error();
            _power = static_cast<std::uint16_t>(n);
            return next();
        };
        const auto handleBool = [next, error, input, this]()
        {
            switch (input.type())
            {
                case catta::json::TokenType::boolTrue():
                    _charging = 1;
                    return next();
                case catta::json::TokenType::boolFalse():
                    _charging = 0;
                    return next();
                default:
                    return error();
            }
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('C') ? next() : input == catta::json::Token::character('P') ? jump(HUB + 13) : error();
            case HUB + 2:
                return _charging != EMPTY_CHARGING ? error() : input == catta::json::Token::character('h') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('a') ? next() : error();
            case HUB + 4:
                return input == catta::json::Token::character('r') ? next() : error();
            case HUB + 5:
                return input == catta::json::Token::character('g') ? next() : error();
            case HUB + 6:
                return input == catta::json::Token::character('i') ? next() : error();
            case HUB + 7:
                return input == catta::json::Token::character('n') ? next() : error();
            case HUB + 8:
                return input == catta::json::Token::character('g') ? next() : error();
            case HUB + 9:
                return input == catta::json::Token::closeString() ? next() : error();
            case HUB + 10:
                return input == catta::json::Token::colon() ? next() : error();
            case HUB + 11:
                return handleBool();
            case HUB + 12:
                return input == catta::json::Token::comma()               ? jump(HUB + 0)
                       : input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                                                                          : error();
            case HUB + 13:
                return _power != EMPTY_POWER ? error() : input == catta::json::Token::character('o') ? next() : error();
            case HUB + 14:
                return input == catta::json::Token::character('w') ? next() : error();
            case HUB + 15:
                return input == catta::json::Token::character('e') ? next() : error();
            case HUB + 16:
                return input == catta::json::Token::character('r') ? next() : error();
            case HUB + 17:
                return input == catta::json::Token::closeString() ? next() : error();
            case HUB + 18:
                return input == catta::json::Token::colon() ? next() : error();
            case HUB + 19:
                return handleNumber();
            case HUB + 20:
                return input == catta::json::Token::comma()               ? jump(HUB + 0)
                       : input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                                                                          : error();
            case TAIL + 0:
                return _power == EMPTY_POWER || _charging == EMPTY_CHARGING ? error() : input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _power(EMPTY_POWER), _charging(EMPTY_CHARGING) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? Output::create(_power, _charging) : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    std::uint16_t _power;
    std::uint8_t _charging;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 21;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
    static constexpr std::uint16_t EMPTY_POWER = 3201;
    static constexpr std::uint8_t EMPTY_CHARGING = 2;
};
}  // namespace fromjson
}  // namespace catta
