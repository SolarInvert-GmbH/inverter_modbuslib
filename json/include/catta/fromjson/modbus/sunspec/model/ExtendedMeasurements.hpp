#pragma once

// model
#include <catta/modbus/sunspec/model/ExtendedMeasurements.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU64.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::model::ExtendedMeasurements>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::model::ExtendedMeasurements;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
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
        const auto isInEndState = [](auto parser)
        {
            [[maybe_unused]] auto ignore = parser.read(catta::json::Token::end());
            return parser.state().isDone();
        };
        const auto handle = [stay, jump, error, input, isInEndState](auto& parser)
        {
            const auto close = catta::json::Token::closeCurlyBracket();
            const auto again = catta::json::Token::comma();
            const auto token = (input == close || input == again) && isInEndState(parser) ? catta::json::Token::end() : input;
            [[maybe_unused]] auto ignore = parser.read(token);
            if (parser.state().isFailed()) return error();
            if (parser.state().isDone()) return jump(input == close ? TAIL + 0 : HUB + 0);
            return stay();
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('a') ? jump(HUB + 2) : error();
            case HUB + 2:
                return input == catta::json::Token::character('c') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('W') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('a') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('t') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('t') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('h') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('o') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('u') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('r') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('s') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::closeString() ? jump(HUB + 13) : error();
            case HUB + 13:
                return !_acWatthoursParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 14:
                return handle(_acWatthoursParser);
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? Output::create(_acWatthoursParser.data()) : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    Parser<catta::modbus::sunspec::ValueU64> _acWatthoursParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 15;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
