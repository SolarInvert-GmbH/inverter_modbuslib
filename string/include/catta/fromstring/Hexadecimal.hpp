#pragma once

// catta
#include <catta/Hexadecimal.hpp>
#include <catta/state/DefaultError.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <std::integral I>
class Parser<Hexadecimal<I>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = Hexadecimal<I>;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _index = sizeof(I) * 2 + 2;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        if (_index < sizeof(I) * 2)
        {
            const auto hex = hexadecimalToHalfByte(input);
            if (!hex) return error();
            const auto current = static_cast<I>(static_cast<I>(hex.value()) << ((sizeof(I) * 2 - 1 - _index) * 4));
            _data = Hexadecimal<I>(static_cast<I>(_data) | current);
        }
        else if (_index == sizeof(I) * 2)
        {
            if (input != '\0') return error();
        }
        else
            return error();
        _index++;
        return Tuple{Error{}, catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr Parser() noexcept : _data(0), _index(0) {}
    [[nodiscard]] constexpr Hexadecimal<I> data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_index == 0) return catta::parser::State::start();
        if (_index <= sizeof(I) * 2) return catta::parser::State::running();
        if (_index == sizeof(I) * 2 + 1) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    Hexadecimal<I> _data;
    std::size_t _index;
};

}  // namespace fromstring
}  // namespace catta
