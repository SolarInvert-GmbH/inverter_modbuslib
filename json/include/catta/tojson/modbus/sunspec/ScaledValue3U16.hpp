#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaledValue3U16.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ScaleFactor.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::ScaledValue3U16>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::ScaledValue3U16;
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
            case PHASE_A + 0:
                return next(catta::json::Token::openString());
            case PHASE_A + 1:
                return next(catta::json::Token::character('p'));
            case PHASE_A + 2:
                return next(catta::json::Token::character('h'));
            case PHASE_A + 3:
                return next(catta::json::Token::character('a'));
            case PHASE_A + 4:
                return next(catta::json::Token::character('s'));
            case PHASE_A + 5:
                return next(catta::json::Token::character('e'));
            case PHASE_A + 6:
                return next(catta::json::Token::character('A'));
            case PHASE_A + 7:
                return next(catta::json::Token::closeString());
            case PHASE_A + 8:
                return next(catta::json::Token::colon());
            case PHASE_A + 9:
                return handle(_phaseASerializer, input.phaseA(), catta::json::Token::comma());
            case PHASE_B + 0:
                return next(catta::json::Token::openString());
            case PHASE_B + 1:
                return next(catta::json::Token::character('p'));
            case PHASE_B + 2:
                return next(catta::json::Token::character('h'));
            case PHASE_B + 3:
                return next(catta::json::Token::character('a'));
            case PHASE_B + 4:
                return next(catta::json::Token::character('s'));
            case PHASE_B + 5:
                return next(catta::json::Token::character('e'));
            case PHASE_B + 6:
                return next(catta::json::Token::character('B'));
            case PHASE_B + 7:
                return next(catta::json::Token::closeString());
            case PHASE_B + 8:
                return next(catta::json::Token::colon());
            case PHASE_B + 9:
                return handle(_phaseBSerializer, input.phaseB(), catta::json::Token::comma());
            case PHASE_C + 0:
                return next(catta::json::Token::openString());
            case PHASE_C + 1:
                return next(catta::json::Token::character('p'));
            case PHASE_C + 2:
                return next(catta::json::Token::character('h'));
            case PHASE_C + 3:
                return next(catta::json::Token::character('a'));
            case PHASE_C + 4:
                return next(catta::json::Token::character('s'));
            case PHASE_C + 5:
                return next(catta::json::Token::character('e'));
            case PHASE_C + 6:
                return next(catta::json::Token::character('C'));
            case PHASE_C + 7:
                return next(catta::json::Token::closeString());
            case PHASE_C + 8:
                return next(catta::json::Token::colon());
            case PHASE_C + 9:
                return handle(_phaseCSerializer, input.phaseC(), catta::json::Token::comma());
            case SCALE + 0:
                return next(catta::json::Token::openString());
            case SCALE + 1:
                return next(catta::json::Token::character('s'));
            case SCALE + 2:
                return next(catta::json::Token::character('c'));
            case SCALE + 3:
                return next(catta::json::Token::character('a'));
            case SCALE + 4:
                return next(catta::json::Token::character('l'));
            case SCALE + 5:
                return next(catta::json::Token::character('e'));
            case SCALE + 6:
                return next(catta::json::Token::closeString());
            case SCALE + 7:
                return next(catta::json::Token::colon());
            case SCALE + 8:
                return handle(_scaleSerializer, input.scale(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _phaseASerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _phaseBSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _phaseCSerializer;
    Serializer<catta::modbus::sunspec::ScaleFactor> _scaleSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t PHASE_A = START + 1;
    static constexpr std::uint8_t PHASE_B = PHASE_A + 10;
    static constexpr std::uint8_t PHASE_C = PHASE_B + 10;
    static constexpr std::uint8_t SCALE = PHASE_C + 10;
    static constexpr std::uint8_t TAIL = SCALE + 9;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
