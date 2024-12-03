#pragma once

// response
#include <catta/modbus/si/response/Type.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::Type>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::Type;
    using Output = catta::json::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
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
                    _state = SUCCESS + 0;
                    break;
                case 1:
                    _state = EXCEPTION + 0;
                    break;
                case 2:
                    _state = FACTORY_VALUES + 0;
                    break;
                case 3:
                    _state = READ_ERROR + 0;
                    break;
                case 4:
                    _state = READ_OPERATING_DATA33 + 0;
                    break;
                case 5:
                    _state = READ_OPERATING_DATA3E + 0;
                    break;
                case 6:
                    _state = UINT16 + 0;
                    break;
                case 7:
                    _state = SINT16 + 0;
                    break;
                case 8:
                    _state = SCALE_FACTOR + 0;
                    break;
                case 9:
                    _state = CONNECTED_PHASE + 0;
                    break;
                case 10:
                    _state = UINT32 + 0;
                    break;
                case 11:
                    _state = UINT64 + 0;
                    break;
                default:
                    _state = STRING32 + 0;
                    break;
            }
            return stay(token);
        };
        switch (_state)
        {
            case START + 0:
                return start(catta::json::Token::openString());
            case SUCCESS + 0:
                return next(catta::json::Token::character('s'));
            case SUCCESS + 1:
                return next(catta::json::Token::character('u'));
            case SUCCESS + 2:
                return next(catta::json::Token::character('c'));
            case SUCCESS + 3:
                return next(catta::json::Token::character('c'));
            case SUCCESS + 4:
                return next(catta::json::Token::character('e'));
            case SUCCESS + 5:
                return next(catta::json::Token::character('s'));
            case SUCCESS + 6:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case EXCEPTION + 0:
                return next(catta::json::Token::character('e'));
            case EXCEPTION + 1:
                return next(catta::json::Token::character('x'));
            case EXCEPTION + 2:
                return next(catta::json::Token::character('c'));
            case EXCEPTION + 3:
                return next(catta::json::Token::character('e'));
            case EXCEPTION + 4:
                return next(catta::json::Token::character('p'));
            case EXCEPTION + 5:
                return next(catta::json::Token::character('t'));
            case EXCEPTION + 6:
                return next(catta::json::Token::character('i'));
            case EXCEPTION + 7:
                return next(catta::json::Token::character('o'));
            case EXCEPTION + 8:
                return jump(catta::json::Token::character('n'), TAIL + 0);
            case FACTORY_VALUES + 0:
                return next(catta::json::Token::character('f'));
            case FACTORY_VALUES + 1:
                return next(catta::json::Token::character('a'));
            case FACTORY_VALUES + 2:
                return next(catta::json::Token::character('c'));
            case FACTORY_VALUES + 3:
                return next(catta::json::Token::character('t'));
            case FACTORY_VALUES + 4:
                return next(catta::json::Token::character('o'));
            case FACTORY_VALUES + 5:
                return next(catta::json::Token::character('r'));
            case FACTORY_VALUES + 6:
                return next(catta::json::Token::character('y'));
            case FACTORY_VALUES + 7:
                return next(catta::json::Token::character('V'));
            case FACTORY_VALUES + 8:
                return next(catta::json::Token::character('a'));
            case FACTORY_VALUES + 9:
                return next(catta::json::Token::character('l'));
            case FACTORY_VALUES + 10:
                return next(catta::json::Token::character('u'));
            case FACTORY_VALUES + 11:
                return next(catta::json::Token::character('e'));
            case FACTORY_VALUES + 12:
                return jump(catta::json::Token::character('s'), TAIL + 0);
            case READ_ERROR + 0:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 1:
                return next(catta::json::Token::character('e'));
            case READ_ERROR + 2:
                return next(catta::json::Token::character('a'));
            case READ_ERROR + 3:
                return next(catta::json::Token::character('d'));
            case READ_ERROR + 4:
                return next(catta::json::Token::character('E'));
            case READ_ERROR + 5:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 6:
                return next(catta::json::Token::character('r'));
            case READ_ERROR + 7:
                return next(catta::json::Token::character('o'));
            case READ_ERROR + 8:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case READ_OPERATING_DATA33 + 0:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA33 + 1:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA33 + 2:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 3:
                return next(catta::json::Token::character('d'));
            case READ_OPERATING_DATA33 + 4:
                return next(catta::json::Token::character('O'));
            case READ_OPERATING_DATA33 + 5:
                return next(catta::json::Token::character('p'));
            case READ_OPERATING_DATA33 + 6:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA33 + 7:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA33 + 8:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 9:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA33 + 10:
                return next(catta::json::Token::character('i'));
            case READ_OPERATING_DATA33 + 11:
                return next(catta::json::Token::character('n'));
            case READ_OPERATING_DATA33 + 12:
                return next(catta::json::Token::character('g'));
            case READ_OPERATING_DATA33 + 13:
                return next(catta::json::Token::character('D'));
            case READ_OPERATING_DATA33 + 14:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 15:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA33 + 16:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA33 + 17:
                return next(catta::json::Token::character('3'));
            case READ_OPERATING_DATA33 + 18:
                return jump(catta::json::Token::character('3'), TAIL + 0);
            case READ_OPERATING_DATA3E + 0:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA3E + 1:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA3E + 2:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 3:
                return next(catta::json::Token::character('d'));
            case READ_OPERATING_DATA3E + 4:
                return next(catta::json::Token::character('O'));
            case READ_OPERATING_DATA3E + 5:
                return next(catta::json::Token::character('p'));
            case READ_OPERATING_DATA3E + 6:
                return next(catta::json::Token::character('e'));
            case READ_OPERATING_DATA3E + 7:
                return next(catta::json::Token::character('r'));
            case READ_OPERATING_DATA3E + 8:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 9:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA3E + 10:
                return next(catta::json::Token::character('i'));
            case READ_OPERATING_DATA3E + 11:
                return next(catta::json::Token::character('n'));
            case READ_OPERATING_DATA3E + 12:
                return next(catta::json::Token::character('g'));
            case READ_OPERATING_DATA3E + 13:
                return next(catta::json::Token::character('D'));
            case READ_OPERATING_DATA3E + 14:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 15:
                return next(catta::json::Token::character('t'));
            case READ_OPERATING_DATA3E + 16:
                return next(catta::json::Token::character('a'));
            case READ_OPERATING_DATA3E + 17:
                return next(catta::json::Token::character('3'));
            case READ_OPERATING_DATA3E + 18:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case UINT16 + 0:
                return next(catta::json::Token::character('u'));
            case UINT16 + 1:
                return next(catta::json::Token::character('i'));
            case UINT16 + 2:
                return next(catta::json::Token::character('n'));
            case UINT16 + 3:
                return next(catta::json::Token::character('t'));
            case UINT16 + 4:
                return next(catta::json::Token::character('1'));
            case UINT16 + 5:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case SINT16 + 0:
                return next(catta::json::Token::character('s'));
            case SINT16 + 1:
                return next(catta::json::Token::character('i'));
            case SINT16 + 2:
                return next(catta::json::Token::character('n'));
            case SINT16 + 3:
                return next(catta::json::Token::character('t'));
            case SINT16 + 4:
                return next(catta::json::Token::character('1'));
            case SINT16 + 5:
                return jump(catta::json::Token::character('6'), TAIL + 0);
            case SCALE_FACTOR + 0:
                return next(catta::json::Token::character('s'));
            case SCALE_FACTOR + 1:
                return next(catta::json::Token::character('c'));
            case SCALE_FACTOR + 2:
                return next(catta::json::Token::character('a'));
            case SCALE_FACTOR + 3:
                return next(catta::json::Token::character('l'));
            case SCALE_FACTOR + 4:
                return next(catta::json::Token::character('e'));
            case SCALE_FACTOR + 5:
                return next(catta::json::Token::character('F'));
            case SCALE_FACTOR + 6:
                return next(catta::json::Token::character('a'));
            case SCALE_FACTOR + 7:
                return next(catta::json::Token::character('c'));
            case SCALE_FACTOR + 8:
                return next(catta::json::Token::character('t'));
            case SCALE_FACTOR + 9:
                return next(catta::json::Token::character('o'));
            case SCALE_FACTOR + 10:
                return jump(catta::json::Token::character('r'), TAIL + 0);
            case CONNECTED_PHASE + 0:
                return next(catta::json::Token::character('c'));
            case CONNECTED_PHASE + 1:
                return next(catta::json::Token::character('o'));
            case CONNECTED_PHASE + 2:
                return next(catta::json::Token::character('n'));
            case CONNECTED_PHASE + 3:
                return next(catta::json::Token::character('n'));
            case CONNECTED_PHASE + 4:
                return next(catta::json::Token::character('e'));
            case CONNECTED_PHASE + 5:
                return next(catta::json::Token::character('c'));
            case CONNECTED_PHASE + 6:
                return next(catta::json::Token::character('t'));
            case CONNECTED_PHASE + 7:
                return next(catta::json::Token::character('e'));
            case CONNECTED_PHASE + 8:
                return next(catta::json::Token::character('d'));
            case CONNECTED_PHASE + 9:
                return next(catta::json::Token::character('P'));
            case CONNECTED_PHASE + 10:
                return next(catta::json::Token::character('h'));
            case CONNECTED_PHASE + 11:
                return next(catta::json::Token::character('a'));
            case CONNECTED_PHASE + 12:
                return next(catta::json::Token::character('s'));
            case CONNECTED_PHASE + 13:
                return jump(catta::json::Token::character('e'), TAIL + 0);
            case UINT32 + 0:
                return next(catta::json::Token::character('u'));
            case UINT32 + 1:
                return next(catta::json::Token::character('i'));
            case UINT32 + 2:
                return next(catta::json::Token::character('n'));
            case UINT32 + 3:
                return next(catta::json::Token::character('t'));
            case UINT32 + 4:
                return next(catta::json::Token::character('3'));
            case UINT32 + 5:
                return jump(catta::json::Token::character('2'), TAIL + 0);
            case UINT64 + 0:
                return next(catta::json::Token::character('u'));
            case UINT64 + 1:
                return next(catta::json::Token::character('i'));
            case UINT64 + 2:
                return next(catta::json::Token::character('n'));
            case UINT64 + 3:
                return next(catta::json::Token::character('t'));
            case UINT64 + 4:
                return next(catta::json::Token::character('6'));
            case UINT64 + 5:
                return jump(catta::json::Token::character('4'), TAIL + 0);
            case STRING32 + 0:
                return next(catta::json::Token::character('s'));
            case STRING32 + 1:
                return next(catta::json::Token::character('t'));
            case STRING32 + 2:
                return next(catta::json::Token::character('r'));
            case STRING32 + 3:
                return next(catta::json::Token::character('i'));
            case STRING32 + 4:
                return next(catta::json::Token::character('n'));
            case STRING32 + 5:
                return next(catta::json::Token::character('g'));
            case STRING32 + 6:
                return next(catta::json::Token::character('3'));
            case STRING32 + 7:
                return jump(catta::json::Token::character('2'), TAIL + 0);
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
    static constexpr std::uint8_t SUCCESS = START + 1;
    static constexpr std::uint8_t EXCEPTION = SUCCESS + 7;
    static constexpr std::uint8_t FACTORY_VALUES = EXCEPTION + 9;
    static constexpr std::uint8_t READ_ERROR = FACTORY_VALUES + 13;
    static constexpr std::uint8_t READ_OPERATING_DATA33 = READ_ERROR + 9;
    static constexpr std::uint8_t READ_OPERATING_DATA3E = READ_OPERATING_DATA33 + 19;
    static constexpr std::uint8_t UINT16 = READ_OPERATING_DATA3E + 19;
    static constexpr std::uint8_t SINT16 = UINT16 + 6;
    static constexpr std::uint8_t SCALE_FACTOR = SINT16 + 6;
    static constexpr std::uint8_t CONNECTED_PHASE = SCALE_FACTOR + 11;
    static constexpr std::uint8_t UINT32 = CONNECTED_PHASE + 14;
    static constexpr std::uint8_t UINT64 = UINT32 + 6;
    static constexpr std::uint8_t STRING32 = UINT64 + 6;
    static constexpr std::uint8_t TAIL = STRING32 + 8;
    static constexpr std::uint8_t DONE = TAIL + 2;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
