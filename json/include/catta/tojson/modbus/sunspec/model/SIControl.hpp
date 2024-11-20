#pragma once

// model
#include <catta/modbus/sunspec/model/SIControl.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ValueS16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::SIControl>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::SIControl;
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
        const auto handle = [stay, next, error](auto& serializer, const auto value, const catta::json::Token token)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return next(token);
            return stay(serializer.data());
        };
        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
            case PCD_DIV + 0:
                return next(catta::json::Token::openString());
            case PCD_DIV + 1:
                return next(catta::json::Token::character('p'));
            case PCD_DIV + 2:
                return next(catta::json::Token::character('c'));
            case PCD_DIV + 3:
                return next(catta::json::Token::character('d'));
            case PCD_DIV + 4:
                return next(catta::json::Token::character('D'));
            case PCD_DIV + 5:
                return next(catta::json::Token::character('i'));
            case PCD_DIV + 6:
                return next(catta::json::Token::character('v'));
            case PCD_DIV + 7:
                return next(catta::json::Token::closeString());
            case PCD_DIV + 8:
                return next(catta::json::Token::colon());
            case PCD_DIV + 9:
                return handle(_pcdDivSerializer, input.pcdDiv(), catta::json::Token::comma());
            case UDC_EXT + 0:
                return next(catta::json::Token::openString());
            case UDC_EXT + 1:
                return next(catta::json::Token::character('u'));
            case UDC_EXT + 2:
                return next(catta::json::Token::character('d'));
            case UDC_EXT + 3:
                return next(catta::json::Token::character('c'));
            case UDC_EXT + 4:
                return next(catta::json::Token::character('E'));
            case UDC_EXT + 5:
                return next(catta::json::Token::character('x'));
            case UDC_EXT + 6:
                return next(catta::json::Token::character('t'));
            case UDC_EXT + 7:
                return next(catta::json::Token::closeString());
            case UDC_EXT + 8:
                return next(catta::json::Token::colon());
            case UDC_EXT + 9:
                return handle(_udcExtSerializer, input.udcExt(), catta::json::Token::comma());
            case PSETPOINT + 0:
                return next(catta::json::Token::openString());
            case PSETPOINT + 1:
                return next(catta::json::Token::character('p'));
            case PSETPOINT + 2:
                return next(catta::json::Token::character('s'));
            case PSETPOINT + 3:
                return next(catta::json::Token::character('e'));
            case PSETPOINT + 4:
                return next(catta::json::Token::character('t'));
            case PSETPOINT + 5:
                return next(catta::json::Token::character('p'));
            case PSETPOINT + 6:
                return next(catta::json::Token::character('o'));
            case PSETPOINT + 7:
                return next(catta::json::Token::character('i'));
            case PSETPOINT + 8:
                return next(catta::json::Token::character('n'));
            case PSETPOINT + 9:
                return next(catta::json::Token::character('t'));
            case PSETPOINT + 10:
                return next(catta::json::Token::closeString());
            case PSETPOINT + 11:
                return next(catta::json::Token::colon());
            case PSETPOINT + 12:
                return handle(_psetpointSerializer, input.psetpoint(), catta::json::Token::comma());
            case UMIN_EXT + 0:
                return next(catta::json::Token::openString());
            case UMIN_EXT + 1:
                return next(catta::json::Token::character('u'));
            case UMIN_EXT + 2:
                return next(catta::json::Token::character('m'));
            case UMIN_EXT + 3:
                return next(catta::json::Token::character('i'));
            case UMIN_EXT + 4:
                return next(catta::json::Token::character('n'));
            case UMIN_EXT + 5:
                return next(catta::json::Token::character('E'));
            case UMIN_EXT + 6:
                return next(catta::json::Token::character('x'));
            case UMIN_EXT + 7:
                return next(catta::json::Token::character('t'));
            case UMIN_EXT + 8:
                return next(catta::json::Token::closeString());
            case UMIN_EXT + 9:
                return next(catta::json::Token::colon());
            case UMIN_EXT + 10:
                return handle(_uminExtSerializer, input.uminExt(), catta::json::Token::comma());
            case UMAX_EXT + 0:
                return next(catta::json::Token::openString());
            case UMAX_EXT + 1:
                return next(catta::json::Token::character('u'));
            case UMAX_EXT + 2:
                return next(catta::json::Token::character('m'));
            case UMAX_EXT + 3:
                return next(catta::json::Token::character('a'));
            case UMAX_EXT + 4:
                return next(catta::json::Token::character('x'));
            case UMAX_EXT + 5:
                return next(catta::json::Token::character('E'));
            case UMAX_EXT + 6:
                return next(catta::json::Token::character('x'));
            case UMAX_EXT + 7:
                return next(catta::json::Token::character('t'));
            case UMAX_EXT + 8:
                return next(catta::json::Token::closeString());
            case UMAX_EXT + 9:
                return next(catta::json::Token::colon());
            case UMAX_EXT + 10:
                return handle(_umaxExtSerializer, input.umaxExt(), catta::json::Token::closeCurlyBracket());
            case TAIL + 0:
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
    Serializer<catta::modbus::sunspec::ValueU16> _pcdDivSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _udcExtSerializer;
    Serializer<catta::modbus::sunspec::ValueS16> _psetpointSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _uminExtSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _umaxExtSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t PCD_DIV = START + 1;
    static constexpr std::uint8_t UDC_EXT = PCD_DIV + 10;
    static constexpr std::uint8_t PSETPOINT = UDC_EXT + 10;
    static constexpr std::uint8_t UMIN_EXT = PSETPOINT + 13;
    static constexpr std::uint8_t UMAX_EXT = UMIN_EXT + 11;
    static constexpr std::uint8_t TAIL = UMAX_EXT + 11;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
