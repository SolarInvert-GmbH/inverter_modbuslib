#pragma once

// catta
#include <catta/modbus/Token.hpp>

// fromstring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::modbus::Token>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::modbus::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
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
        const auto handle0 = [input, error](auto& parser, const char c, const auto function)
        {
            if (parser.state().isActive())
            {
                const auto [readError, handled] = parser.read(input);
                if (parser.state().isDone()) return input == c ? function() : error();
                if (readError.isError()) return error();
                return Tuple{Error{}, handled};
            }
            return error();
        };
        const auto handle1 = [input, error](auto& parser, const char c, const auto function)
        {
            const auto [readError, handled] = parser.read(input == c ? '\0' : input);
            if (parser.state().isDone()) return input == c ? function() : error();
            if (parser.state().isFailed()) return error();
            return Tuple{Error{}, handled};
        };
        const auto f = [this, jump]()
        {
            using Type = catta::modbus::TokenType;
            switch (_parserType.data())
            {
                case Type::function():
                case Type::data():
                case Type::code():
                    return jump(HEXADECIMAL + 0);
                default:
                    return jump(CLOSE + 0);
            }
        };
        const auto tail = [this, error]()
        {
            using Type = catta::modbus::TokenType;
            using Token = catta::modbus::Token;
            switch (_parserType.data())
            {
                case Type::start():
                    _data = Token::start();
                    break;
                case Type::function():
                    _data = Token::function(std::uint8_t(_parserHexadecimal.data()));
                    break;
                case Type::data():
                    _data = Token::data(std::uint8_t(_parserHexadecimal.data()));
                    break;
                case Type::exception():
                    _data = Token::exception();
                    break;
                case Type::code():
                    _data = Token::code(std::uint8_t(_parserHexadecimal.data()));
                    break;
                case Type::end():
                    _data = Token::end();
                    break;
                default:
                    return error();
            }
            _state = TAIL;
            return Tuple{Error{}, catta::parser::InputHandled::yes()};
        };
        switch (_state)
        {
            case START + 0:
                return handle0(_parserType, '{', f);
            case CLOSE + 0:
                return input == '}' ? tail() : error();
            case HEXADECIMAL + 0:
                return handle1(_parserHexadecimal, '}', tail);
            case TAIL + 0:
                return input == '\0' ? end() : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _state == DONE ? _data : Output::empty(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return _parserType.state();
            case CLOSE:
            case HEXADECIMAL:
            case TAIL:
                return catta::parser::State::running();
            case DONE:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    catta::fromstring::Parser<catta::modbus::TokenType> _parserType;
    catta::fromstring::Parser<catta::Hexadecimal<std::uint8_t>> _parserHexadecimal;
    std::uint8_t _state;
    catta::modbus::Token _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t CLOSE = 1;
    static constexpr std::uint8_t HEXADECIMAL = 2;
    static constexpr std::uint8_t TAIL = 3;
    static constexpr std::uint8_t DONE = 4;
    static constexpr std::uint8_t ERROR = 5;
};

}  // namespace fromstring
}  // namespace catta
