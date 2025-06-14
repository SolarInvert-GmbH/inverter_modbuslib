#pragma once

// sunspec
#include <catta/modbus/sunspec/ConnectedPhase.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::ConnectedPhase>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::ConnectedPhase;
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
        const auto close = [jump, this](std::uint8_t data)
        {
            _data = data;
            return jump(TAIL + 0);
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::nullObject()   ? jump(TAIL + 0)
                       : input == catta::json::Token::openString() ? jump(HUB + 0)
                                                                   : error();
            case HUB + 0:
                return input == catta::json::Token::character('p') ? jump(HUB + 1) : error();
            case HUB + 1:
                return input == catta::json::Token::character('h') ? jump(HUB + 2) : error();
            case HUB + 2:
                return input == catta::json::Token::character('a') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('s') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('e') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('C')   ? jump(HUB + 8)
                       : input == catta::json::Token::character('B') ? jump(HUB + 7)
                       : input == catta::json::Token::character('A') ? jump(HUB + 6)
                                                                     : error();
            case HUB + 6:
                return input == catta::json::Token::closeString() ? close(0) : error();
            case HUB + 7:
                return input == catta::json::Token::closeString() ? close(1) : error();
            case HUB + 8:
                return input == catta::json::Token::closeString() ? close(2) : error();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _data(Output::empty()) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE + 0 ? Output(_data) : Output(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    std::uint8_t _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 9;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
