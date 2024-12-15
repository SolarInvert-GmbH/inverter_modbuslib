#pragma once

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::sunspec::ScaleFactor>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::sunspec::ScaleFactor;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto done = [this, input, error, stay]()
        {
            if (!input.type().isEnd()) return error();
            _state = DONE;
            return stay();
        };
        const auto handle = [this, stay, input, error]()
        {
            if (!input.type().integerNumber()) return error();
            const auto number = input.integerValue();
            if (number < -10 || number > 10) return error();
            _data = static_cast<std::int8_t>(number);
            _state++;
            return stay();
        };
        switch (_state)
        {
            case START + 0:
                return handle();
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _data(11) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? Output::create(_data) : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    std::int8_t _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TAIL = START + 1;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
