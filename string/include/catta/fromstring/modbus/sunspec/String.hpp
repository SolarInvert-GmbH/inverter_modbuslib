#pragma once

// catta
#include <catta/modbus/sunspec/String.hpp>

// fromjson
#include <catta/fromjson/modbus/sunspec/String.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::modbus::sunspec::String>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::modbus::sunspec::String;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _index = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _index = DONE;
            return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
        };
        if (_index >= DONE) return error();
        if (_index == TAIL) return input == '\0' ? done() : error();
        if (input == '\0') return done();
        _data[_index] = input;
        _index++;
        return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr Parser() noexcept : _data{}, _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _index == DONE ? Output::create(_data.data()) : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_index == START) return catta::parser::State::start();
        if (_index < DONE) return catta::parser::State::running();
        if (_index == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::array<char, Output::size> _data;
    std::size_t _index;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TAIL = Output::size;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};

}  // namespace fromstring
}  // namespace catta
