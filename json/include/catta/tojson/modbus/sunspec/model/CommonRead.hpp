#pragma once

// model
#include <catta/modbus/sunspec/model/CommonRead.hpp>

// tojson
#include <catta/tojson/modbus/sunspec/String.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::sunspec::model::CommonRead>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::CommonRead;
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
            case MANUFACTURER + 0:
                return next(catta::json::Token::openString());
            case MANUFACTURER + 1:
                return next(catta::json::Token::character('m'));
            case MANUFACTURER + 2:
                return next(catta::json::Token::character('a'));
            case MANUFACTURER + 3:
                return next(catta::json::Token::character('n'));
            case MANUFACTURER + 4:
                return next(catta::json::Token::character('u'));
            case MANUFACTURER + 5:
                return next(catta::json::Token::character('f'));
            case MANUFACTURER + 6:
                return next(catta::json::Token::character('a'));
            case MANUFACTURER + 7:
                return next(catta::json::Token::character('c'));
            case MANUFACTURER + 8:
                return next(catta::json::Token::character('t'));
            case MANUFACTURER + 9:
                return next(catta::json::Token::character('u'));
            case MANUFACTURER + 10:
                return next(catta::json::Token::character('r'));
            case MANUFACTURER + 11:
                return next(catta::json::Token::character('e'));
            case MANUFACTURER + 12:
                return next(catta::json::Token::character('r'));
            case MANUFACTURER + 13:
                return next(catta::json::Token::closeString());
            case MANUFACTURER + 14:
                return next(catta::json::Token::colon());
            case MANUFACTURER + 15:
                return handle(_manufacturerSerializer, input.manufacturer(), catta::json::Token::comma());
            case MODEL + 0:
                return next(catta::json::Token::openString());
            case MODEL + 1:
                return next(catta::json::Token::character('m'));
            case MODEL + 2:
                return next(catta::json::Token::character('o'));
            case MODEL + 3:
                return next(catta::json::Token::character('d'));
            case MODEL + 4:
                return next(catta::json::Token::character('e'));
            case MODEL + 5:
                return next(catta::json::Token::character('l'));
            case MODEL + 6:
                return next(catta::json::Token::closeString());
            case MODEL + 7:
                return next(catta::json::Token::colon());
            case MODEL + 8:
                return handle(_modelSerializer, input.model(), catta::json::Token::comma());
            case SERIAL_NUMBER + 0:
                return next(catta::json::Token::openString());
            case SERIAL_NUMBER + 1:
                return next(catta::json::Token::character('s'));
            case SERIAL_NUMBER + 2:
                return next(catta::json::Token::character('e'));
            case SERIAL_NUMBER + 3:
                return next(catta::json::Token::character('r'));
            case SERIAL_NUMBER + 4:
                return next(catta::json::Token::character('i'));
            case SERIAL_NUMBER + 5:
                return next(catta::json::Token::character('a'));
            case SERIAL_NUMBER + 6:
                return next(catta::json::Token::character('l'));
            case SERIAL_NUMBER + 7:
                return next(catta::json::Token::character('N'));
            case SERIAL_NUMBER + 8:
                return next(catta::json::Token::character('u'));
            case SERIAL_NUMBER + 9:
                return next(catta::json::Token::character('m'));
            case SERIAL_NUMBER + 10:
                return next(catta::json::Token::character('b'));
            case SERIAL_NUMBER + 11:
                return next(catta::json::Token::character('e'));
            case SERIAL_NUMBER + 12:
                return next(catta::json::Token::character('r'));
            case SERIAL_NUMBER + 13:
                return next(catta::json::Token::closeString());
            case SERIAL_NUMBER + 14:
                return next(catta::json::Token::colon());
            case SERIAL_NUMBER + 15:
                return handle(_serialNumberSerializer, input.serialNumber(), catta::json::Token::comma());
            case DEVICE_ADDRESS + 0:
                return next(catta::json::Token::openString());
            case DEVICE_ADDRESS + 1:
                return next(catta::json::Token::character('d'));
            case DEVICE_ADDRESS + 2:
                return next(catta::json::Token::character('e'));
            case DEVICE_ADDRESS + 3:
                return next(catta::json::Token::character('v'));
            case DEVICE_ADDRESS + 4:
                return next(catta::json::Token::character('i'));
            case DEVICE_ADDRESS + 5:
                return next(catta::json::Token::character('c'));
            case DEVICE_ADDRESS + 6:
                return next(catta::json::Token::character('e'));
            case DEVICE_ADDRESS + 7:
                return next(catta::json::Token::character('A'));
            case DEVICE_ADDRESS + 8:
                return next(catta::json::Token::character('d'));
            case DEVICE_ADDRESS + 9:
                return next(catta::json::Token::character('d'));
            case DEVICE_ADDRESS + 10:
                return next(catta::json::Token::character('r'));
            case DEVICE_ADDRESS + 11:
                return next(catta::json::Token::character('e'));
            case DEVICE_ADDRESS + 12:
                return next(catta::json::Token::character('s'));
            case DEVICE_ADDRESS + 13:
                return next(catta::json::Token::character('s'));
            case DEVICE_ADDRESS + 14:
                return next(catta::json::Token::closeString());
            case DEVICE_ADDRESS + 15:
                return next(catta::json::Token::colon());
            case DEVICE_ADDRESS + 16:
                return handle(_deviceAddressSerializer, input.deviceAddress(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::String> _manufacturerSerializer;
    Serializer<catta::modbus::sunspec::String> _modelSerializer;
    Serializer<catta::modbus::sunspec::String> _serialNumberSerializer;
    Serializer<catta::modbus::sunspec::ValueU16> _deviceAddressSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t MANUFACTURER = START + 1;
    static constexpr std::uint8_t MODEL = MANUFACTURER + 16;
    static constexpr std::uint8_t SERIAL_NUMBER = MODEL + 9;
    static constexpr std::uint8_t DEVICE_ADDRESS = SERIAL_NUMBER + 16;
    static constexpr std::uint8_t TAIL = DEVICE_ADDRESS + 17;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
