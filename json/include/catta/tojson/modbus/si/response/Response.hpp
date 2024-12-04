#pragma once

// request
#include <catta/modbus/si/response/Response.hpp>

// tojson
#include <catta/tojson/modbus/si/WriteRegister.hpp>
#include <catta/tojson/modbus/si/response/Exception.hpp>
#include <catta/tojson/modbus/si/response/FactoryValues.hpp>
#include <catta/tojson/modbus/si/response/ReadError.hpp>
#include <catta/tojson/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/tojson/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/tojson/modbus/si/response/Type.hpp>
#include <catta/tojson/modbus/sunspec/String.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU32.hpp>
#include <catta/tojson/modbus/sunspec/ValueU64.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::Response>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::Response;
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
        const auto handle = [stay, next, error](auto& serializer, const auto value, const catta::json::Token token)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return next(token);
            return stay(serializer.data());
        };
        const auto handleSplitt = [&input, handle, this, jump](const catta::json::Token token)
        {
            using Type = catta::modbus::si::response::Type;
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
                case Type::value16():
                    return handle(_valueU16Serializer, catta::modbus::sunspec::ValueU16::create(input.value16Value()), token);
                case Type::value32():
                    return handle(_valueU32Serializer, catta::modbus::sunspec::ValueU32::create(input.value32Value()), token);
                case Type::value64():
                    return handle(_valueU64Serializer, catta::modbus::sunspec::ValueU64::create(input.value64Value()), token);
                case Type::string():
                    return handle(_stringSerializer, input.stringValue(), token);
                default:
                    return jump(catta::json::Token::nullObject(), VALUE + 8);
            }
        };

        switch (_state)
        {
            case START + 0:
                return next(catta::json::Token::openCurlyBracket());
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
    Serializer<catta::modbus::si::response::Type> _typeSerializer;
    Serializer<catta::modbus::si::response::Exception> _exceptionSerializer;
    Serializer<catta::modbus::si::response::FactoryValues> _factoryValuesSerializer;
    Serializer<catta::modbus::si::response::ReadError> _readErrorSerializer;
    Serializer<catta::modbus::si::response::ReadOperatingData33> _readOperatingData33Serializer;
    Serializer<catta::modbus::si::response::ReadOperatingData3e> _readOperatingData3eSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _valueU16Serializer;
    Serializer<catta::modbus::sunspec::ValueU32> _valueU32Serializer;
    Serializer<catta::modbus::sunspec::ValueU64> _valueU64Serializer;
    Serializer<catta::modbus::sunspec::String> _stringSerializer;
    Serializer<catta::modbus::si::WriteRegister> _writeRegisterSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TYPE = START + 1;
    static constexpr std::uint8_t VALUE = TYPE + 8;
    static constexpr std::uint8_t TAIL = VALUE + 10;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
