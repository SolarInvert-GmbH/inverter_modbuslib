#pragma once

// catta
#include <catta/Decimal.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <std::signed_integral I>
class Parser<Decimal<I>>
{
  public:
    typedef catta::state::DefaultError Error;
    typedef char Input;
    typedef Decimal<I> Output;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = 5;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            if (_state == 2) _data = Decimal(static_cast<I>(-static_cast<I>(_data)));
            _state = 4;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto next = [this](const std::uint8_t state)
        {
            _state = state;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto diget = [this, &input, next](const std::uint8_t state)
        {
            _data = Decimal(static_cast<I>(static_cast<I>(_data) * 10 + (input - '0')));
            return next(state);
        };
        const auto isDiget = [input]() { return input >= '0' && input <= '9'; };
        switch (_state)
        {
            case 0:
                return input == '-' ? next(1) : isDiget() ? diget(3) : error();
            case 1:
                return isDiget() ? diget(2) : error();
            case 2:
            case 3:
                return isDiget() ? diget(_state) : done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _data(0), _state(0) {}
    [[nodiscard]] constexpr Decimal<I> data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case 0:
                return catta::parser::State::start();
            case 1:
            case 2:
            case 3:
                return catta::parser::State::running();
            case 4:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    Decimal<I> _data;
    std::uint8_t _state;
};

template <std::unsigned_integral I>
class Parser<Decimal<I>>
{
  public:
    typedef catta::state::DefaultError Error;
    typedef char Input;
    typedef Decimal<I> Output;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = 3;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _state = 2;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto diget = [this, &input](const std::uint8_t state)
        {
            _state = state;
            _data = Decimal(static_cast<I>(static_cast<I>(_data) * 10 + static_cast<I>(input - '0')));
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto isDiget = [input]() { return input >= '0' && input <= '9'; };
        switch (_state)
        {
            case 0:
                return isDiget() ? diget(1) : error();
            case 1:
                return isDiget() ? diget(1) : done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _data(0), _state(0) {}
    [[nodiscard]] constexpr Decimal<I> data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case 0:
                return catta::parser::State::start();
            case 1:
                return catta::parser::State::running();
            case 2:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    Decimal<I> _data;
    std::uint8_t _state;
};

}  // namespace fromstring
}  // namespace catta
