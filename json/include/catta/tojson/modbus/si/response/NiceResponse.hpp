#pragma once

// request
#include <catta/modbus/si/response/NiceResponse.hpp>

// tojson
#include <catta/tojson/modbus/si/RegisterAddress.hpp>
#include <catta/tojson/modbus/si/RegisterValue.hpp>
#include <catta/tojson/modbus/si/response/Exception.hpp>
#include <catta/tojson/modbus/si/response/FactoryValues.hpp>
#include <catta/tojson/modbus/si/response/NiceType.hpp>
#include <catta/tojson/modbus/si/response/ReadError.hpp>
#include <catta/tojson/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/tojson/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::NiceResponse>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::NiceResponse;
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
        const auto handle = [stay, next, error](auto& serializer, const auto value, const catta::json::Token token)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return next(token);
            return stay(serializer.data());
        };
        const auto handleSplitt = [&input, handle, this, jump](const catta::json::Token token)
        {
            using Type = catta::modbus::si::response::NiceType;
            switch (input.type())
            {
                case Type::exception():
                    return handle(_exceptionSerializer, input.exceptionValue(), token);
                case Type::factoryValues():
                    return handle(_factoryValuesSerializer, input.factoryValuesValue(), token);
                case Type::readError():
                    return handle(_readErrorSerializer, input.readErrorValue(), token);
                case Type::readOperatingData33():
                    return handle(_readOperatingData33Serializer, input.readOperatingData33Value(), token);
                case Type::readOperatingData3e():
                    return handle(_readOperatingData3eSerializer, input.readOperatingData3eValue(), token);
                case Type::writeRegister():
                    return handle(_writeRegisterSerializer, input.writeRegisterValue(), token);
                case Type::readRegister():
                    return handle(_registerValueSerializer, input.registerValue(), token);
                default:
                    return jump(input.successValue() ? catta::json::Token::boolTrue() : catta::json::Token::boolFalse(), VALUE + 8);
            }
        };

        switch (_state)
        {
            case START + 0:
                return input.isEmpty() ? jump(catta::json::Token::nullObject(), TAIL + 0) : next(catta::json::Token::openCurlyBracket());
            case TYPE + 0:
                return next(catta::json::Token::openString());
            case TYPE + 1:
                return next(catta::json::Token::character('t'));
            case TYPE + 2:
                return next(catta::json::Token::character('y'));
            case TYPE + 3:
                return next(catta::json::Token::character('p'));
            case TYPE + 4:
                return next(catta::json::Token::character('e'));
            case TYPE + 5:
                return next(catta::json::Token::closeString());
            case TYPE + 6:
                return next(catta::json::Token::colon());
            case TYPE + 7:
                return handle(_typeSerializer, input.type(), catta::json::Token::comma());
            case VALUE + 0:
                return next(catta::json::Token::openString());
            case VALUE + 1:
                return next(catta::json::Token::character('v'));
            case VALUE + 2:
                return next(catta::json::Token::character('a'));
            case VALUE + 3:
                return next(catta::json::Token::character('l'));
            case VALUE + 4:
                return next(catta::json::Token::character('u'));
            case VALUE + 5:
                return next(catta::json::Token::character('e'));
            case VALUE + 6:
                return next(catta::json::Token::closeString());
            case VALUE + 7:
                return jump(catta::json::Token::colon(), VALUE + 9);
            case VALUE + 8:
                return jump(catta::json::Token::closeCurlyBracket(), TAIL + 0);
            case VALUE + 9:
                return handleSplitt(catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::si::response::NiceType> _typeSerializer;
    Serializer<catta::modbus::si::response::Exception> _exceptionSerializer;
    Serializer<catta::modbus::si::response::FactoryValues> _factoryValuesSerializer;
    Serializer<catta::modbus::si::response::ReadError> _readErrorSerializer;
    Serializer<catta::modbus::si::response::ReadOperatingData33> _readOperatingData33Serializer;
    Serializer<catta::modbus::si::response::ReadOperatingData3e> _readOperatingData3eSerializer;
    Serializer<catta::modbus::si::RegisterValue> _registerValueSerializer;
    Serializer<catta::modbus::si::RegisterAddress> _writeRegisterSerializer;
    Serializer<catta::modbus::si::RegisterAddress> _registerAddressSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TYPE = START + 1;
    static constexpr std::uint8_t VALUE = TYPE + 8;
    static constexpr std::uint8_t TAIL = VALUE + 10;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
