#pragma once

// catta
#include <catta/parser/TextPosition.hpp>

// tostring
#include <catta/tostring/Decimal.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::parser::TextPosition>
{
  public:
    static constexpr std::string_view name = "catta::parser::TextPosition";
};
template <>
class Serializer<catta::parser::TextPosition>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::parser::TextPosition;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error{}, catta::parser::InputHandled::no()}; };
        const auto next = [this, stay]()
        {
            _state++;
            return stay();
        };
        const auto character = [next, this](const char c)
        {
            _data = c;
            return next();
        };
        const auto done = [this]()
        {
            _data = '\0';
            _state = DONE;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto handle = [done, stay, next, this](const std::size_t i, const char c)
        {
            const auto decimal = catta::Decimal<std::size_t>(i);
            [[maybe_unused]] const auto ignore = _serializer.read(decimal);
            const char data = _serializer.data();

            if (data != '\0')
            {
                _data = data;
                return stay();
            }
            else
            {
                _data = c;
                _serializer = {};
                return next();
                return done();
            }
        };
        switch (_state)
        {
            case START:
                return character('[');
            case ROW + 0:
                return handle(input.row(), ',');
            case COLUMN + 0:
                return handle(input.column(), ']');
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _data{}, _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return catta::parser::State::start();
            case DONE:
                return catta::parser::State::done();
            default:
                return _state < DONE ? catta::parser::State::running() : catta::parser::State::failed();
        }
    }

  private:
    catta::tostring::Serializer<catta::Decimal<std::size_t>> _serializer;
    std::uint8_t _state;
    char _data;
    std::uint8_t _index;
    constexpr static std::uint8_t START = 0;
    constexpr static std::uint8_t ROW = START + 1;
    constexpr static std::uint8_t COLUMN = ROW + 1;
    constexpr static std::uint8_t TAIL = COLUMN + 1;
    constexpr static std::uint8_t DONE = TAIL + 1;
    constexpr static std::uint8_t ERROR = DONE + 1;
};

}  // namespace tostring
}  // namespace catta
