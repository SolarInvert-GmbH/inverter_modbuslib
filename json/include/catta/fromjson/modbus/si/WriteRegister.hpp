#pragma once

// si
#include <catta/modbus/si/WriteRegister.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/RegisterAddress.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::WriteRegister>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::WriteRegister;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto isInEndState = [](auto parser)
        {
            [[maybe_unused]] auto ignore = parser.read(catta::json::Token::end());
            return parser.state().isDone();
        };
        const auto handle = [stay, jump, error, input, isInEndState](auto& parser)
        {
            const auto close = catta::json::Token::closeCurlyBracket();
            const auto again = catta::json::Token::comma();
            const auto token = (input == close || input == again) && isInEndState(parser) ? catta::json::Token::end() : input;
            [[maybe_unused]] auto ignore = parser.read(token);
            if (parser.state().isFailed()) return error();
            if (parser.state().isDone()) return jump(input == close ? TAIL + 0 : HUB + 0);
            return stay();
        };
        const auto handleNumber = [this, jump, input, error]()
        {
            if (input.integerValue() < MINS16 || input.integerValue() > MAXU16) return error();
            _value = static_cast<std::int32_t>(input.integerValue());
            return jump(HUB + 33);
        };
        const auto handleABC = [this, next, input, error]()
        {
            if (!input.type().isCharacter()) return error();
            const auto result = [this, next](const std::int32_t v)
            {
                _value = v;
                return next();
            };
            switch (input.unicodeCharacterValue())
            {
                case 'A':
                    return result(A);
                case 'B':
                    return result(B);
                case 'C':
                    return result(C);
                default:
                    return error();
            }
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('v')   ? jump(HUB + 19)
                       : input == catta::json::Token::character('r') ? jump(HUB + 2)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('e') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('g') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('i') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::character('s') ? jump(HUB + 6) : error();
            case HUB + 6:
                return input == catta::json::Token::character('t') ? jump(HUB + 7) : error();
            case HUB + 7:
                return input == catta::json::Token::character('e') ? jump(HUB + 8) : error();
            case HUB + 8:
                return input == catta::json::Token::character('r') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('A') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('d') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('d') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::character('r') ? jump(HUB + 13) : error();
            case HUB + 13:
                return input == catta::json::Token::character('e') ? jump(HUB + 14) : error();
            case HUB + 14:
                return input == catta::json::Token::character('s') ? jump(HUB + 15) : error();
            case HUB + 15:
                return input == catta::json::Token::character('s') ? jump(HUB + 16) : error();
            case HUB + 16:
                return input == catta::json::Token::closeString() ? jump(HUB + 17) : error();
            case HUB + 17:
                return !_registerAddressParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 18:
                return handle(_registerAddressParser);
            case HUB + 19:
                return input == catta::json::Token::character('a') ? jump(HUB + 20) : error();
            case HUB + 20:
                return input == catta::json::Token::character('l') ? jump(HUB + 21) : error();
            case HUB + 21:
                return input == catta::json::Token::character('u') ? jump(HUB + 22) : error();
            case HUB + 22:
                return input == catta::json::Token::character('e') ? jump(HUB + 23) : error();
            case HUB + 23:
                return input == catta::json::Token::closeString() ? jump(HUB + 24) : error();
            case HUB + 24:
                return _value != EMPTY ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 25:
                return input == catta::json::Token::openString() ? next() : input.type().isIntegerNumber() ? handleNumber() : error();
            case HUB + 26:
                return input == catta::json::Token::character('p') ? next() : error();
            case HUB + 27:
                return input == catta::json::Token::character('h') ? next() : error();
            case HUB + 28:
                return input == catta::json::Token::character('a') ? next() : error();
            case HUB + 29:
                return input == catta::json::Token::character('s') ? next() : error();
            case HUB + 30:
                return input == catta::json::Token::character('e') ? next() : error();
            case HUB + 31:
                return handleABC();
            case HUB + 32:
                return input == catta::json::Token::closeString() ? next() : error();
            case HUB + 33:
                return input == catta::json::Token::closeCurlyBracket() ? jump(TAIL + 0)
                       : input == catta::json::Token::comma()           ? jump(HUB + 0)
                                                                        : error();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _value(EMPTY) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE) return Output::empty();
        using Type = catta::modbus::si::RegisterType;
        using Phase = catta::modbus::sunspec::ConnectedPhase;
        const auto address = _registerAddressParser.data();
        const Type type = address.type();
        switch (type)
        {
            case Type::uint16():
                return _value >= MINU16 ? Output::create(address, catta::modbus::sunspec::ValueU16::create(static_cast<std::uint16_t>(_value)))
                                        : Output::empty();
            case Type::sint16():
                return _value <= MAXS16 ? Output::create(address, catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(_value)))
                                        : Output::empty();
            case Type::connectedPhase():
                switch (_value)
                {
                    case A:
                        return Output::create(address, Phase::phaseA());
                    case B:
                        return Output::create(address, Phase::phaseB());
                    case C:
                        return Output::create(address, Phase::phaseC());
                    default:
                        return Output::empty();
                }
            default:
                return Output::empty();
        }
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    Parser<catta::modbus::si::RegisterAddress> _registerAddressParser;
    std::int32_t _value;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 34;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
    static constexpr std::int32_t MINS16 = -32'768;
    static constexpr std::int32_t MINU16 = 0;
    static constexpr std::int32_t MAXS16 = 32'767;
    static constexpr std::int32_t MAXU16 = 65'535;
    static constexpr std::int32_t A = MAXU16 + 1;
    static constexpr std::int32_t B = MAXU16 + 2;
    static constexpr std::int32_t C = MAXU16 + 3;
    static constexpr std::int32_t EMPTY = MAXU16 + 4;
};
}  // namespace fromjson
}  // namespace catta
