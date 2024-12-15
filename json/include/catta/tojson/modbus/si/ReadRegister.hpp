#pragma once

// si
#include <catta/modbus/si/ReadRegister.hpp>

// tojson
#include <catta/tojson/modbus/si/RegisterAddress.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::ReadRegister>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::ReadRegister;
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
            case REGISTER_ADDRESS + 0:
                return next(catta::json::Token::openString());
            case REGISTER_ADDRESS + 1:
                return next(catta::json::Token::character('r'));
            case REGISTER_ADDRESS + 2:
                return next(catta::json::Token::character('e'));
            case REGISTER_ADDRESS + 3:
                return next(catta::json::Token::character('g'));
            case REGISTER_ADDRESS + 4:
                return next(catta::json::Token::character('i'));
            case REGISTER_ADDRESS + 5:
                return next(catta::json::Token::character('s'));
            case REGISTER_ADDRESS + 6:
                return next(catta::json::Token::character('t'));
            case REGISTER_ADDRESS + 7:
                return next(catta::json::Token::character('e'));
            case REGISTER_ADDRESS + 8:
                return next(catta::json::Token::character('r'));
            case REGISTER_ADDRESS + 9:
                return next(catta::json::Token::character('A'));
            case REGISTER_ADDRESS + 10:
                return next(catta::json::Token::character('d'));
            case REGISTER_ADDRESS + 11:
                return next(catta::json::Token::character('d'));
            case REGISTER_ADDRESS + 12:
                return next(catta::json::Token::character('r'));
            case REGISTER_ADDRESS + 13:
                return next(catta::json::Token::character('e'));
            case REGISTER_ADDRESS + 14:
                return next(catta::json::Token::character('s'));
            case REGISTER_ADDRESS + 15:
                return next(catta::json::Token::character('s'));
            case REGISTER_ADDRESS + 16:
                return next(catta::json::Token::closeString());
            case REGISTER_ADDRESS + 17:
                return next(catta::json::Token::colon());
            case REGISTER_ADDRESS + 18:
                return handle(_registerAddressSerializer, input.registerAddress(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::si::RegisterAddress> _registerAddressSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t REGISTER_ADDRESS = START + 1;
    static constexpr std::uint8_t TAIL = REGISTER_ADDRESS + 19;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
