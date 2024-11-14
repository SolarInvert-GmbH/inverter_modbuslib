#pragma once

// std
#include <algorithm>

// catta
#include <catta/parser/InputHandled.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::parser::InputHandled>
{
  public:
    static constexpr std::string_view name = "catta::parser::InputHandled";
};

template <>
class Serializer<catta::parser::InputHandled>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::parser::InputHandled;
    using Output = char;

    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = catta::parser::State::failed();
            _data = '\0';
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this]()
        {
            _state = catta::parser::State::running();
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto done = [this]()
        {
            _state = catta::parser::State::done();
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        if (_state.isFailed() || _state.isDone()) return error();

        const std::string_view string = Input::enumNames[input ? 0 : 1];
        _data = string[_index];
        if (_data == '\0') return done();
        _index++;
        return stay();
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(catta::parser::State::start()), _index{0}, _data('\0') {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    catta::parser::State _state;
    std::size_t _index;
    char _data;
};
}  // namespace tostring
}  // namespace catta
