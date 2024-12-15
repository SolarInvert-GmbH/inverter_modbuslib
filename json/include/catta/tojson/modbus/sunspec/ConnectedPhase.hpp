#pragma once

// sunspec
#include <catta/modbus/sunspec/ConnectedPhase.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::ConnectedPhase>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::ConnectedPhase;
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
                    _state = PHASE_A + 0;
                    break;
                case 1:
                    _state = PHASE_B + 0;
                    break;
                default:
                    _state = PHASE_C + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return start(catta::json::Token::openString());
            case PHASE_A + 0:
                return next(catta::json::Token::character('p'));
            case PHASE_A + 1:
                return next(catta::json::Token::character('h'));
            case PHASE_A + 2:
                return next(catta::json::Token::character('a'));
            case PHASE_A + 3:
                return next(catta::json::Token::character('s'));
            case PHASE_A + 4:
                return next(catta::json::Token::character('e'));
            case PHASE_A + 5:
                return jump(catta::json::Token::character('A'), TAIL + 0);
            case PHASE_B + 0:
                return next(catta::json::Token::character('p'));
            case PHASE_B + 1:
                return next(catta::json::Token::character('h'));
            case PHASE_B + 2:
                return next(catta::json::Token::character('a'));
            case PHASE_B + 3:
                return next(catta::json::Token::character('s'));
            case PHASE_B + 4:
                return next(catta::json::Token::character('e'));
            case PHASE_B + 5:
                return jump(catta::json::Token::character('B'), TAIL + 0);
            case PHASE_C + 0:
                return next(catta::json::Token::character('p'));
            case PHASE_C + 1:
                return next(catta::json::Token::character('h'));
            case PHASE_C + 2:
                return next(catta::json::Token::character('a'));
            case PHASE_C + 3:
                return next(catta::json::Token::character('s'));
            case PHASE_C + 4:
                return next(catta::json::Token::character('e'));
            case PHASE_C + 5:
                return jump(catta::json::Token::character('C'), TAIL + 0);
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
    static constexpr std::uint8_t PHASE_A = START + 1;
    static constexpr std::uint8_t PHASE_B = PHASE_A + 6;
    static constexpr std::uint8_t PHASE_C = PHASE_B + 6;
    static constexpr std::uint8_t TAIL = PHASE_C + 6;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
