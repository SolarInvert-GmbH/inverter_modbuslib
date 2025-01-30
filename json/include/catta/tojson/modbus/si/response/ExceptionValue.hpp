#pragma once

// response
#include <catta/modbus/si/response/ExceptionValue.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::ExceptionValue>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::ExceptionValue;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto done = [this]()
        {
            _data = catta::json::Token::end();
            _state = DONE + 0;
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this](const catta::json::Token token)
        {
            _data = token;
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto next = [stay, this](const catta::json::Token token)
        {
            _state++;
            return stay(token);
        };
        const auto jump = [stay, this](const catta::json::Token token, const std::uint8_t state)
        {
            _state = state;
            return stay(token);
        };
        const auto start = [stay, this, input](const catta::json::Token token)
        {
            switch (input)
            {
                case 0:
                    _state = INVALID_FUNCTION_CODE + 0;
                    break;
                case 1:
                    _state = INVALID_REGISTER_ADDRESS + 0;
                    break;
                case 2:
                    _state = INVALID_DATA_VALUE + 0;
                    break;
                default:
                    _state = DEVICE_ERROR + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return start(catta::json::Token::openString());
            case INVALID_FUNCTION_CODE + 0:
                return next(catta::json::Token::character('i'));
            case INVALID_FUNCTION_CODE + 1:
                return next(catta::json::Token::character('n'));
            case INVALID_FUNCTION_CODE + 2:
                return next(catta::json::Token::character('v'));
            case INVALID_FUNCTION_CODE + 3:
                return next(catta::json::Token::character('a'));
            case INVALID_FUNCTION_CODE + 4:
                return next(catta::json::Token::character('l'));
            case INVALID_FUNCTION_CODE + 5:
                return next(catta::json::Token::character('i'));
            case INVALID_FUNCTION_CODE + 6:
                return next(catta::json::Token::character('d'));
            case INVALID_FUNCTION_CODE + 7:
                return next(catta::json::Token::character('F'));
            case INVALID_FUNCTION_CODE + 8:
                return next(catta::json::Token::character('u'));
            case INVALID_FUNCTION_CODE + 9:
                return next(catta::json::Token::character('n'));
            case INVALID_FUNCTION_CODE + 10:
                return next(catta::json::Token::character('c'));
            case INVALID_FUNCTION_CODE + 11:
                return next(catta::json::Token::character('t'));
            case INVALID_FUNCTION_CODE + 12:
                return next(catta::json::Token::character('i'));
            case INVALID_FUNCTION_CODE + 13:
                return next(catta::json::Token::character('o'));
            case INVALID_FUNCTION_CODE + 14:
                return next(catta::json::Token::character('n'));
            case INVALID_FUNCTION_CODE + 15:
                return next(catta::json::Token::character('C'));
            case INVALID_FUNCTION_CODE + 16:
                return next(catta::json::Token::character('o'));
            case INVALID_FUNCTION_CODE + 17:
                return next(catta::json::Token::character('d'));
            case INVALID_FUNCTION_CODE + 18:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case INVALID_REGISTER_ADDRESS + 0:
                return next(catta::json::Token::character('i'));
            case INVALID_REGISTER_ADDRESS + 1:
                return next(catta::json::Token::character('n'));
            case INVALID_REGISTER_ADDRESS + 2:
                return next(catta::json::Token::character('v'));
            case INVALID_REGISTER_ADDRESS + 3:
                return next(catta::json::Token::character('a'));
            case INVALID_REGISTER_ADDRESS + 4:
                return next(catta::json::Token::character('l'));
            case INVALID_REGISTER_ADDRESS + 5:
                return next(catta::json::Token::character('i'));
            case INVALID_REGISTER_ADDRESS + 6:
                return next(catta::json::Token::character('d'));
            case INVALID_REGISTER_ADDRESS + 7:
                return next(catta::json::Token::character('R'));
            case INVALID_REGISTER_ADDRESS + 8:
                return next(catta::json::Token::character('e'));
            case INVALID_REGISTER_ADDRESS + 9:
                return next(catta::json::Token::character('g'));
            case INVALID_REGISTER_ADDRESS + 10:
                return next(catta::json::Token::character('i'));
            case INVALID_REGISTER_ADDRESS + 11:
                return next(catta::json::Token::character('s'));
            case INVALID_REGISTER_ADDRESS + 12:
                return next(catta::json::Token::character('t'));
            case INVALID_REGISTER_ADDRESS + 13:
                return next(catta::json::Token::character('e'));
            case INVALID_REGISTER_ADDRESS + 14:
                return next(catta::json::Token::character('r'));
            case INVALID_REGISTER_ADDRESS + 15:
                return next(catta::json::Token::character('A'));
            case INVALID_REGISTER_ADDRESS + 16:
                return next(catta::json::Token::character('d'));
            case INVALID_REGISTER_ADDRESS + 17:
                return next(catta::json::Token::character('d'));
            case INVALID_REGISTER_ADDRESS + 18:
                return next(catta::json::Token::character('r'));
            case INVALID_REGISTER_ADDRESS + 19:
                return next(catta::json::Token::character('e'));
            case INVALID_REGISTER_ADDRESS + 20:
                return next(catta::json::Token::character('s'));
            case INVALID_REGISTER_ADDRESS + 21:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case INVALID_DATA_VALUE + 0:
                return next(catta::json::Token::character('i'));
            case INVALID_DATA_VALUE + 1:
                return next(catta::json::Token::character('n'));
            case INVALID_DATA_VALUE + 2:
                return next(catta::json::Token::character('v'));
            case INVALID_DATA_VALUE + 3:
                return next(catta::json::Token::character('a'));
            case INVALID_DATA_VALUE + 4:
                return next(catta::json::Token::character('l'));
            case INVALID_DATA_VALUE + 5:
                return next(catta::json::Token::character('i'));
            case INVALID_DATA_VALUE + 6:
                return next(catta::json::Token::character('d'));
            case INVALID_DATA_VALUE + 7:
                return next(catta::json::Token::character('D'));
            case INVALID_DATA_VALUE + 8:
                return next(catta::json::Token::character('a'));
            case INVALID_DATA_VALUE + 9:
                return next(catta::json::Token::character('t'));
            case INVALID_DATA_VALUE + 10:
                return next(catta::json::Token::character('a'));
            case INVALID_DATA_VALUE + 11:
                return next(catta::json::Token::character('V'));
            case INVALID_DATA_VALUE + 12:
                return next(catta::json::Token::character('a'));
            case INVALID_DATA_VALUE + 13:
                return next(catta::json::Token::character('l'));
            case INVALID_DATA_VALUE + 14:
                return next(catta::json::Token::character('u'));
            case INVALID_DATA_VALUE + 15:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case DEVICE_ERROR + 0:
                return next(catta::json::Token::character('d'));
            case DEVICE_ERROR + 1:
                return next(catta::json::Token::character('e'));
            case DEVICE_ERROR + 2:
                return next(catta::json::Token::character('v'));
            case DEVICE_ERROR + 3:
                return next(catta::json::Token::character('i'));
            case DEVICE_ERROR + 4:
                return next(catta::json::Token::character('c'));
            case DEVICE_ERROR + 5:
                return next(catta::json::Token::character('e'));
            case DEVICE_ERROR + 6:
                return next(catta::json::Token::character('E'));
            case DEVICE_ERROR + 7:
                return next(catta::json::Token::character('r'));
            case DEVICE_ERROR + 8:
                return next(catta::json::Token::character('r'));
            case DEVICE_ERROR + 9:
                return next(catta::json::Token::character('o'));
            case DEVICE_ERROR + 10:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case TAIL + 0:
                return next(catta::json::Token::closeString());
            case TAIL + 1:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _data(Output::empty()) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    catta::json::Token _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t INVALID_FUNCTION_CODE = START + 1;
    static constexpr std::uint8_t INVALID_REGISTER_ADDRESS = INVALID_FUNCTION_CODE + 19;
    static constexpr std::uint8_t INVALID_DATA_VALUE = INVALID_REGISTER_ADDRESS + 22;
    static constexpr std::uint8_t DEVICE_ERROR = INVALID_DATA_VALUE + 16;
    static constexpr std::uint8_t TAIL = DEVICE_ERROR + 11;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
