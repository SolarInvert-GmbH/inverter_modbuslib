#pragma once

// catta
#include <catta/state/ActiveCloseErrorState.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>

template <class ERROR_TYPE>
class catta::fromstring::Parser<catta::state::ActiveCloseErrorState<ERROR_TYPE>>
{
  public:
    using Output = catta::state::ActiveCloseErrorState<ERROR_TYPE>;
    using Input = char;
    using Error = catta::state::DefaultError;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        using T = catta::state::ActiveCloseErrorState<ERROR_TYPE>;
        bool failed = true;
        const auto handle = [this, input, &failed](const std::string_view s, bool& possible, const T value)
        {
            if (possible)
            {
                if (_index < s.size() && input == s[_index])
                    failed = false;
                else if (_index == s.size() && !isValidEnumCharacter(input))
                {
                    _value = value;
                    _state = catta::parser::State::done();
                    return true;
                }
                else
                    possible = false;
            }
            return false;
        };
        static_assert(T::error(ERROR_TYPE{}) == 0);
        for (uint8_t i = 1; i < T{} + 1; i++)
            if (handle(enumNames[i], _possible[i], T{i, ERROR_TYPE{}})) return Tuple{Error{}, catta::parser::InputHandled::yes()};

        if (_possible[0])
        {
            bool run = true;
            while (run)
            {
                const auto [error, handled] = _parser.read(input);
                run = !handled;

                if (_parser.state().isDone())
                {
                    _value = T::error(_parser.data());
                    _state = catta::parser::State::done();
                    return Tuple{Error{}, catta::parser::InputHandled::yes()};
                }
            }
            if (_parser.state().isFailed())
                _possible[0] = false;
            else
                failed = false;
        }
        _index++;
        _state = failed ? catta::parser::State::failed() : catta::parser::State::running();
        return Tuple{failed ? Error::error() : Error{}, catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr catta::state::ActiveCloseErrorState<ERROR_TYPE> data() const noexcept { return _value; }
    [[nodiscard]] constexpr Parser() noexcept : _index(0), _state(catta::parser::State::start())
    {
        for (bool& b : _possible) b = true;
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    std::array<bool, catta::state::ActiveCloseErrorState<ERROR_TYPE>::empty() + 1> _possible;
    size_t _index;
    catta::state::ActiveCloseErrorState<ERROR_TYPE> _value;
    catta::parser::State _state;
    catta::fromstring::Parser<ERROR_TYPE> _parser;
    constexpr static std::array<std::string_view, catta::state::ActiveCloseErrorState<ERROR_TYPE>::empty() + 1> enumNames = {"", "ACTIVE", "CLOSED",
                                                                                                                             "EMPTY"};
};
