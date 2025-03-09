#pragma once

// catta
#include <catta/FixedPointNumber.hpp>

// fromstring
#include <catta/fromstring/Decimal.hpp>

namespace catta
{
namespace fromstring
{
template <std::uint8_t DECIMAL_PLACES>
class Parser<catta::FixedPointNumber<DECIMAL_PLACES>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::FixedPointNumber<DECIMAL_PLACES>;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto end = [this]()
        {
            _state = DONE;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error{}, catta::parser::InputHandled::yes()}; };
        const auto jump = [this, stay](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto top = [this, input, error, jump, end]()
        {
            const auto [readError, handled] = _parser.read(input == '.' ? '\0' : input);
            if (_parser.state().isDone()) return input == '.' ? jump(BOTTOM) : end();
            if (readError.isError()) return error();
            _state = TOP;
            return Tuple{Error{}, handled};
            return error();
        };
        const auto bottom = [this, input, error, stay, end]()
        {
            if (input == '\0') return end();
            if (input < '0' || input > '9' || _factor <= 0) return error();
            const std::int64_t i = static_cast<std::int64_t>(input - '0');
            _bottom += i * _factor;
            _factor /= 10;
            return stay();
        };
        switch (_state)
        {
            case START + 0:
                _minus = input == '-';
                return top();
            case TOP + 0:
                return top();
            case BOTTOM + 0:
                return bottom();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(0), _bottom(0), _factor(FACTOR / 10), _minus(false) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE) return Output::empty();
        const std::int64_t top = static_cast<std::int64_t>(_parser.data());
        const std::int64_t bottom = _minus ? -_bottom : _bottom;
        return Output::create(top * FACTOR + bottom);
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return _parser.state();
            case TOP:
            case BOTTOM:
                return catta::parser::State::running();
            case DONE:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    catta::fromstring::Parser<catta::Decimal<std::int64_t>> _parser;
    std::uint8_t _state;
    std::int64_t _bottom;
    std::int64_t _factor;
    bool _minus;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TOP = 1;
    static constexpr std::uint8_t BOTTOM = 2;
    static constexpr std::uint8_t DONE = 3;
    static constexpr std::uint8_t ERROR = 4;
    static constexpr std::int64_t FACTOR = []()
    {
        std::int64_t n = 1;
        for (std::uint8_t i = 0; i < DECIMAL_PLACES; i++) n *= 10;
        return n;
    }();
};

}  // namespace fromstring
}  // namespace catta
