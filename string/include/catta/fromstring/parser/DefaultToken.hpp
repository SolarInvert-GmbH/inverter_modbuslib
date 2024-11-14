#pragma once

// catta
#include <catta/parser/DefaultToken.hpp>

// fromstring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <class Character, catta::parser::ErrorConcept ERROR>
class Parser<catta::parser::DefaultToken<Character, ERROR>>
{
  private:
    using Type = catta::parser::DefaultTokenType;
    using Base = std::conditional<sizeof(Character) == 4, std::uint32_t, std::uint8_t>::type;
    using Hex = catta::Hexadecimal<Base>;
    constexpr static std::string_view EMPTY = "EMPTY";
    constexpr static std::string_view END = Type::enumNames[Type::end()].data();

  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::parser::DefaultToken<Character, ERROR>;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        if (!_value.type().isEmpty()) return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        bool failed = true;
        const auto handleConst = [&failed, this, input](const std::string_view s, bool& b, const catta::parser::DefaultToken<Character, ERROR> v)
        {
            if (b)
            {
                if (_index > s.size() || input != s[_index])
                {
                    b = false;
                    return false;
                }
                if (_index == s.size())
                {
                    _value = v;
                    _done = true;
                    return true;
                }
                failed = false;
            }
            return false;
        };
        if (handleConst(EMPTY, _empty, catta::parser::DefaultToken<Character, ERROR>::empty()) ||
            handleConst(END, _end, catta::parser::DefaultToken<Character, ERROR>::end()))
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        const auto [hError, hHandled] = _hexadecimal.read(input);
        if (_hexadecimal.state().isDone())
        {
            _value = catta::parser::DefaultToken<Character, ERROR>::character(static_cast<Character>(Base{_hexadecimal.data()}));
            _done = true;
            return Tuple{hError, hHandled};
        }
        if (hError.isEmpty()) failed = false;
        const auto [eError, eHandled] = _error.read(input);
        if (_error.state().isDone())
        {
            _value = catta::parser::DefaultToken<Character, ERROR>::error(_error.data());
            _done = true;
            return Tuple{eError, eHandled};
        }
        if (eError.isEmpty()) failed = false;

        if (failed) return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        _index++;

        return Tuple{Error{}, catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr Parser() noexcept : _empty{true}, _end{true}, _done(false), _index{0} {}
    [[nodiscard]] constexpr catta::parser::DefaultToken<Character, ERROR> data() const noexcept { return _value; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_index == 0) return catta::parser::State::start();
        if (_done) return catta::parser::State::done();
        return _hexadecimal.state().isFailed() && _error.state().isFailed() && !_empty && !_end ? catta::parser::State::failed()
                                                                                                : catta::parser::State::running();
    }

  private:
    Parser<catta::Hexadecimal<Base>> _hexadecimal;
    Parser<ERROR> _error;
    bool _empty;
    bool _end;
    bool _done;
    std::size_t _index;
    catta::parser::DefaultToken<Character, ERROR> _value;
};
}  // namespace fromstring
}  // namespace catta
