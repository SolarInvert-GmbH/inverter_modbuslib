#pragma once

// sunspec
#include <catta/modbus/sunspec/ValueU8.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <std::uint8_t MIN, std::uint8_t MAX>
class Serializer<catta::modbus::sunspec::ValueU8<MIN, MAX>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::ValueU8<MIN, MAX>;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::no()}; };
        const auto done = [this]()
        {
            _data = Output::end();
            _state = DONE;
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto token = [this, stay](const Output t)
        {
            _data = t;
            _state++;
            return stay();
        };
        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? done() : token(Output::integerNumber(input.value()));
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
    Output _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TAIL = START + 1;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
