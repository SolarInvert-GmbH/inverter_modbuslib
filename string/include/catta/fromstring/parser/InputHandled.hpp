#pragma once

// catta
#include <catta/parser/InputHandled.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::parser::InputHandled>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::parser::InputHandled;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        bool failed = true;
        const auto handle = [this, input, &failed](const std::string_view s, bool& possible, const catta::parser::InputHandled value)
        {
            if (possible)
            {
                if (_index <= s.size() && input == s[_index])
                {
                    if (_index == s.size())
                    {
                        _value = value;
                        _state = catta::parser::State::done();
                        return true;
                    }
                    failed = false;
                }
                else
                    possible = false;
            }
            return false;
        };
        if (handle(catta::parser::InputHandled::enumNames[0], _possible[0], catta::parser::InputHandled::yes()))
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        if (handle(catta::parser::InputHandled::enumNames[1], _possible[1], catta::parser::InputHandled::no()))
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        _index++;
        _state = failed ? catta::parser::State::State::failed() : catta::parser::State::State::running();
        return Tuple{failed ? Error::error() : Error{}, catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr catta::parser::InputHandled data() const noexcept { return _value; }
    [[nodiscard]] constexpr Parser() noexcept : _index(0), _state(catta::parser::State::start())
    {
        for (bool& b : _possible) b = true;
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    std::array<bool, 2> _possible;
    size_t _index;
    catta::parser::InputHandled _value;
    catta::parser::State _state;
};
}  // namespace fromstring
}  // namespace catta
