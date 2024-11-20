#pragma once

// model
#include <catta/modbus/sunspec/model/BasicSettingsWrite.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::BasicSettingsWrite>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::BasicSettingsWrite;
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
            case W_MAX + 0:
                return next(catta::json::Token::openString());
            case W_MAX + 1:
                return next(catta::json::Token::character('w'));
            case W_MAX + 2:
                return next(catta::json::Token::character('M'));
            case W_MAX + 3:
                return next(catta::json::Token::character('a'));
            case W_MAX + 4:
                return next(catta::json::Token::character('x'));
            case W_MAX + 5:
                return next(catta::json::Token::closeString());
            case W_MAX + 6:
                return next(catta::json::Token::colon());
            case W_MAX + 7:
                return handle(_wMaxSerializer, input.wMax(), catta::json::Token::comma());
            case V_MAX + 0:
                return next(catta::json::Token::openString());
            case V_MAX + 1:
                return next(catta::json::Token::character('v'));
            case V_MAX + 2:
                return next(catta::json::Token::character('M'));
            case V_MAX + 3:
                return next(catta::json::Token::character('a'));
            case V_MAX + 4:
                return next(catta::json::Token::character('x'));
            case V_MAX + 5:
                return next(catta::json::Token::closeString());
            case V_MAX + 6:
                return next(catta::json::Token::colon());
            case V_MAX + 7:
                return handle(_vMaxSerializer, input.vMax(), catta::json::Token::comma());
            case V_MIN + 0:
                return next(catta::json::Token::openString());
            case V_MIN + 1:
                return next(catta::json::Token::character('v'));
            case V_MIN + 2:
                return next(catta::json::Token::character('M'));
            case V_MIN + 3:
                return next(catta::json::Token::character('i'));
            case V_MIN + 4:
                return next(catta::json::Token::character('n'));
            case V_MIN + 5:
                return next(catta::json::Token::closeString());
            case V_MIN + 6:
                return next(catta::json::Token::colon());
            case V_MIN + 7:
                return handle(_vMinSerializer, input.vMin(), catta::json::Token::comma());
            case ECP_NOM_HZ + 0:
                return next(catta::json::Token::openString());
            case ECP_NOM_HZ + 1:
                return next(catta::json::Token::character('e'));
            case ECP_NOM_HZ + 2:
                return next(catta::json::Token::character('c'));
            case ECP_NOM_HZ + 3:
                return next(catta::json::Token::character('p'));
            case ECP_NOM_HZ + 4:
                return next(catta::json::Token::character('N'));
            case ECP_NOM_HZ + 5:
                return next(catta::json::Token::character('o'));
            case ECP_NOM_HZ + 6:
                return next(catta::json::Token::character('m'));
            case ECP_NOM_HZ + 7:
                return next(catta::json::Token::character('H'));
            case ECP_NOM_HZ + 8:
                return next(catta::json::Token::character('z'));
            case ECP_NOM_HZ + 9:
                return next(catta::json::Token::closeString());
            case ECP_NOM_HZ + 10:
                return next(catta::json::Token::colon());
            case ECP_NOM_HZ + 11:
                return handle(_ecpNomHzSerializer, input.ecpNomHz(), catta::json::Token::comma());
            case CONN_PHASE + 0:
                return next(catta::json::Token::openString());
            case CONN_PHASE + 1:
                return next(catta::json::Token::character('c'));
            case CONN_PHASE + 2:
                return next(catta::json::Token::character('o'));
            case CONN_PHASE + 3:
                return next(catta::json::Token::character('n'));
            case CONN_PHASE + 4:
                return next(catta::json::Token::character('n'));
            case CONN_PHASE + 5:
                return next(catta::json::Token::character('P'));
            case CONN_PHASE + 6:
                return next(catta::json::Token::character('h'));
            case CONN_PHASE + 7:
                return next(catta::json::Token::character('a'));
            case CONN_PHASE + 8:
                return next(catta::json::Token::character('s'));
            case CONN_PHASE + 9:
                return next(catta::json::Token::character('e'));
            case CONN_PHASE + 10:
                return next(catta::json::Token::closeString());
            case CONN_PHASE + 11:
                return next(catta::json::Token::colon());
            case CONN_PHASE + 12:
                return handle(_connPhaseSerializer, input.connPhase(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _wMaxSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _vMaxSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _vMinSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _ecpNomHzSerializer;
    Serializer<catta::modbus::sunspec::ConnectedPhase> _connPhaseSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t W_MAX = START + 1;
    static constexpr std::uint8_t V_MAX = W_MAX + 8;
    static constexpr std::uint8_t V_MIN = V_MAX + 8;
    static constexpr std::uint8_t ECP_NOM_HZ = V_MIN + 8;
    static constexpr std::uint8_t CONN_PHASE = ECP_NOM_HZ + 12;
    static constexpr std::uint8_t TAIL = CONN_PHASE + 13;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
