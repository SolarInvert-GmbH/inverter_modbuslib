#pragma once

// catta
#include <catta/parser/TextPosition.hpp>

// fromstring
#include <catta/fromstring/Decimal.hpp>
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::parser::TextPosition>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::parser::TextPosition;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _state = 8;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _state = 7;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error{}, catta::parser::InputHandled::yes()}; };
        const auto next = [this, stay]()
        {
            _state++;
            return stay();
        };
        const auto jumpTwo = [this, stay]()
        {
            _state += 2;
            return stay();
        };
        const auto isSpace = [input]() { return input == ' ' || input == '\t' || input == '\n' || input == '\v' || input == '\f' || input == '\r'; };
        const auto handleCharacter = [input, stay, error, isSpace](const char expected, const auto f)
        {
            if (isSpace()) return stay();
            if (input == expected) return f();
            return error();
        };
        const auto handleParser0 = [this, input, stay, error, next, isSpace]()
        {
            if (isSpace()) return stay();
            return std::get<0>(_parser.read(input)).isError() ? error() : next();
        };
        const auto handleParser1 = [this, input, error, handleCharacter, next, stay, jumpTwo](const char expectedNext, const auto callback)
        {
            const auto [readError, handled] = _parser.read(input);
            if (readError.isError()) return error();
            if (_parser.state().isDone())
            {
                callback();
                return handled ? next() : handleCharacter(expectedNext, jumpTwo);
            }
            else
                return stay();
        };
        switch (_state)
        {
            case 0:
                return handleCharacter('[', next);
            case 1:
                return handleParser0();
            case 2:
                return handleParser1(',',
                                     [this]()
                                     {
                                         _data = std::size_t(_parser.data());
                                         _parser = Parser<catta::Decimal<std::size_t>>{};
                                     });
            case 3:
                return handleCharacter(',', next);
            case 4:
                return handleParser0();
            case 5:
                return handleParser1(']', []() {});
            case 6:
                return handleCharacter(']', done);
            case 7:
                return input == '\0' ? next() : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _data{0}, _state(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return Output{_data, std::size_t(_parser.data())}; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case 0:
                return catta::parser::State::start();
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                return catta::parser::State::running();
            case 8:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        };
    }

  private:
    Parser<catta::Decimal<std::size_t>> _parser;
    std::size_t _data;
    std::uint8_t _state;
};
}  // namespace fromstring
}  // namespace catta
