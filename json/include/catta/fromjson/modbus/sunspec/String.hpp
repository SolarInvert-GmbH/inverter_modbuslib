#pragma once

// sunspec
#include <catta/modbus/sunspec/String.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::String>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::String;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto close = [stay, this]()
        {
            _state = TAIL + 0;
            return stay();
        };
        const auto done = [this, input, error, stay]()
        {
            if (!input.type().isEnd()) return error();
            _state = DONE;
            return stay();
        };

        const auto data = [this, input, close, error, next]()
        {
            const std::uint8_t index = _state - DATA;
            if (input.type().isCloseString()) return close();
            if (index >= catta::modbus::sunspec::String::size || !input.type().isCharacter() || input.unicodeCharacterValue() > 0xff) return error();
            _data[index] = static_cast<char>(input.unicodeCharacterValue());
            return next();
        };
        switch (_state)
        {
            case START + 0:
                return input == Input::openString() ? next() : error();
            case TAIL + 0:
                return done();
            default:
                return _state < TAIL ? data() : error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _data{} {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? Output::create(_data.data()) : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    catta::modbus::sunspec::String::Raw _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 1;
    static constexpr std::uint8_t TAIL = DATA + catta::modbus::sunspec::String::size;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
