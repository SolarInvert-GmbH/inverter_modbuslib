#pragma once

// catta
#include <catta/modbus/Token.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::Token>
{
  public:
    static constexpr std::string_view name = "catta::modbus::Token";
};

template <>
class Serializer<catta::modbus::Token>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = 7;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _data = '\0';
            _state = DONE;
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
            using Type = catta::modbus::TokenType;
            switch (input.type())
            {
                case Type::function():
                case Type::data():
                case Type::code():
                    return jump(HEXADECIMAL + 0);
                default:
                    return jump(CLOSE + 0);
            }
        };
        const auto tail = [jump]() { return jump(TAIL + 0); };
        switch (_state)
        {
            case START + 0:
                return handle(_serializerType, input.type(), '{', findTarget);
            case CLOSE + 0:
                return character('}', TAIL + 0);
            case HEXADECIMAL + 0:
                return handle(_serializerHexadicmal, catta::Hexadecimal<std::uint8_t>(input.value()), '}', tail);
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START + 0:
                return _serializerType.state();
            case CLOSE + 0:
            case HEXADECIMAL:
            case TAIL + 0:
                return catta::parser::State::running();
            case DONE + 0:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    catta::tostring::Serializer<catta::modbus::TokenType> _serializerType;
    catta::tostring::Serializer<catta::Hexadecimal<std::uint8_t>> _serializerHexadicmal;
    std::uint8_t _state;
    char _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t CLOSE = 1;
    static constexpr std::uint8_t HEXADECIMAL = 2;
    static constexpr std::uint8_t TAIL = 3;
    static constexpr std::uint8_t DONE = 4;
    static constexpr std::uint8_t ERROR = 5;
};

}  // namespace tostring
}  // namespace catta
