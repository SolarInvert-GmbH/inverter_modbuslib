#pragma once

// catta
#include <catta/json/Token.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/json/ParsingError.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::json::Token>
{
  public:
    static constexpr std::string_view name = "catta::json::Token";
};

template <>
class Serializer<catta::json::Token>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = 7;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto end = [this]()
        {
            _data = '\0';
            _state = 6;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error{}, catta::parser::InputHandled::no()}; };
        const auto jump = [this, stay](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto character = [jump, this](const char c, const std::uint8_t state)
        {
            _data = c;
            return jump(state);
        };
        const auto handle = [stay, this](auto& serializer, const auto value, const char c, const auto function)
        {
            [[maybe_unused]] const auto [readError, handled] = serializer.read(value);
            const char data = serializer.data();
            if (data != '\0')
            {
                _data = data;
                return stay();
            }
            else
            {
                _data = c;
                return function();
            }
        };
        const auto findTarget = [input, jump]()
        {
            using Type = catta::json::TokenType;
            switch (input.type())
            {
                case Type::integerNumber():
                    return jump(2);
                case Type::floatNumber():
                    return jump(2);
                case Type::character():
                    return jump(3);
                case Type::error():
                    return jump(4);
                default:
                    return jump(1);
            }
        };
        const auto done = [jump]() { return jump(5); };
        switch (_state)
        {
            case 0:
                return handle(_serializer0, input.type(), '{', findTarget);
            case 1:
                return character('}', 5);
            case 2:
                return handle(_serializer2, catta::Hexadecimal<std::int64_t>(input.integerValue()), '}', done);
            case 3:
                return handle(_serializer1, catta::Hexadecimal<std::uint32_t>(input.unicodeCharacterValue()), '}', done);
            case 4:
                return handle(_serializer3, input.errorValue(), '}', done);
            case 5:
                return end();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case 0:
                return _serializer0.state();
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return catta::parser::State::running();
            case 6:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    catta::tostring::Serializer<catta::json::TokenType> _serializer0;
    catta::tostring::Serializer<catta::Hexadecimal<std::uint32_t>> _serializer1;
    catta::tostring::Serializer<catta::Hexadecimal<std::int64_t>> _serializer2;
    catta::tostring::Serializer<catta::json::ParsingError> _serializer3;
    std::uint8_t _state;
    char _data;
};

}  // namespace tostring
}  // namespace catta
