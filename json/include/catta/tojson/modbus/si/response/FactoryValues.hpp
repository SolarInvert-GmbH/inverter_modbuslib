#pragma once

// response
#include <catta/modbus/si/response/FactoryValues.hpp>

// tojson
#include <catta/tojson/modbus/si/Date.hpp>
#include <catta/tojson/modbus/sunspec/ValueU16.hpp>
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tojson
{
template <>
class Serializer<catta::modbus::si::response::FactoryValues>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::FactoryValues;
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
            case SERIALNUMBER + 0:
                return next(catta::json::Token::openString());
            case SERIALNUMBER + 1:
                return next(catta::json::Token::character('s'));
            case SERIALNUMBER + 2:
                return next(catta::json::Token::character('e'));
            case SERIALNUMBER + 3:
                return next(catta::json::Token::character('r'));
            case SERIALNUMBER + 4:
                return next(catta::json::Token::character('i'));
            case SERIALNUMBER + 5:
                return next(catta::json::Token::character('a'));
            case SERIALNUMBER + 6:
                return next(catta::json::Token::character('l'));
            case SERIALNUMBER + 7:
                return next(catta::json::Token::character('n'));
            case SERIALNUMBER + 8:
                return next(catta::json::Token::character('u'));
            case SERIALNUMBER + 9:
                return next(catta::json::Token::character('m'));
            case SERIALNUMBER + 10:
                return next(catta::json::Token::character('b'));
            case SERIALNUMBER + 11:
                return next(catta::json::Token::character('e'));
            case SERIALNUMBER + 12:
                return next(catta::json::Token::character('r'));
            case SERIALNUMBER + 13:
                return next(catta::json::Token::closeString());
            case SERIALNUMBER + 14:
                return next(catta::json::Token::colon());
            case SERIALNUMBER + 15:
                return handle(_serialnumberSerializer, input.serialnumber(), catta::json::Token::comma());
            case PRODUCTION_DATE + 0:
                return next(catta::json::Token::openString());
            case PRODUCTION_DATE + 1:
                return next(catta::json::Token::character('p'));
            case PRODUCTION_DATE + 2:
                return next(catta::json::Token::character('r'));
            case PRODUCTION_DATE + 3:
                return next(catta::json::Token::character('o'));
            case PRODUCTION_DATE + 4:
                return next(catta::json::Token::character('d'));
            case PRODUCTION_DATE + 5:
                return next(catta::json::Token::character('u'));
            case PRODUCTION_DATE + 6:
                return next(catta::json::Token::character('c'));
            case PRODUCTION_DATE + 7:
                return next(catta::json::Token::character('t'));
            case PRODUCTION_DATE + 8:
                return next(catta::json::Token::character('i'));
            case PRODUCTION_DATE + 9:
                return next(catta::json::Token::character('o'));
            case PRODUCTION_DATE + 10:
                return next(catta::json::Token::character('n'));
            case PRODUCTION_DATE + 11:
                return next(catta::json::Token::character('D'));
            case PRODUCTION_DATE + 12:
                return next(catta::json::Token::character('a'));
            case PRODUCTION_DATE + 13:
                return next(catta::json::Token::character('t'));
            case PRODUCTION_DATE + 14:
                return next(catta::json::Token::character('e'));
            case PRODUCTION_DATE + 15:
                return next(catta::json::Token::closeString());
            case PRODUCTION_DATE + 16:
                return next(catta::json::Token::colon());
            case PRODUCTION_DATE + 17:
                return handle(_productionDateSerializer, input.productionDate(), catta::json::Token::comma());
            case HARDWARE_VERSION + 0:
                return next(catta::json::Token::openString());
            case HARDWARE_VERSION + 1:
                return next(catta::json::Token::character('h'));
            case HARDWARE_VERSION + 2:
                return next(catta::json::Token::character('a'));
            case HARDWARE_VERSION + 3:
                return next(catta::json::Token::character('r'));
            case HARDWARE_VERSION + 4:
                return next(catta::json::Token::character('d'));
            case HARDWARE_VERSION + 5:
                return next(catta::json::Token::character('w'));
            case HARDWARE_VERSION + 6:
                return next(catta::json::Token::character('a'));
            case HARDWARE_VERSION + 7:
                return next(catta::json::Token::character('r'));
            case HARDWARE_VERSION + 8:
                return next(catta::json::Token::character('e'));
            case HARDWARE_VERSION + 9:
                return next(catta::json::Token::character('V'));
            case HARDWARE_VERSION + 10:
                return next(catta::json::Token::character('e'));
            case HARDWARE_VERSION + 11:
                return next(catta::json::Token::character('r'));
            case HARDWARE_VERSION + 12:
                return next(catta::json::Token::character('s'));
            case HARDWARE_VERSION + 13:
                return next(catta::json::Token::character('i'));
            case HARDWARE_VERSION + 14:
                return next(catta::json::Token::character('o'));
            case HARDWARE_VERSION + 15:
                return next(catta::json::Token::character('n'));
            case HARDWARE_VERSION + 16:
                return next(catta::json::Token::closeString());
            case HARDWARE_VERSION + 17:
                return next(catta::json::Token::colon());
            case HARDWARE_VERSION + 18:
                return handle(_hardwareVersionSerializer, input.hardwareVersion(), catta::json::Token::comma());
            case FIRMWARE_VERSION + 0:
                return next(catta::json::Token::openString());
            case FIRMWARE_VERSION + 1:
                return next(catta::json::Token::character('f'));
            case FIRMWARE_VERSION + 2:
                return next(catta::json::Token::character('i'));
            case FIRMWARE_VERSION + 3:
                return next(catta::json::Token::character('r'));
            case FIRMWARE_VERSION + 4:
                return next(catta::json::Token::character('m'));
            case FIRMWARE_VERSION + 5:
                return next(catta::json::Token::character('w'));
            case FIRMWARE_VERSION + 6:
                return next(catta::json::Token::character('a'));
            case FIRMWARE_VERSION + 7:
                return next(catta::json::Token::character('r'));
            case FIRMWARE_VERSION + 8:
                return next(catta::json::Token::character('e'));
            case FIRMWARE_VERSION + 9:
                return next(catta::json::Token::character('V'));
            case FIRMWARE_VERSION + 10:
                return next(catta::json::Token::character('e'));
            case FIRMWARE_VERSION + 11:
                return next(catta::json::Token::character('r'));
            case FIRMWARE_VERSION + 12:
                return next(catta::json::Token::character('s'));
            case FIRMWARE_VERSION + 13:
                return next(catta::json::Token::character('i'));
            case FIRMWARE_VERSION + 14:
                return next(catta::json::Token::character('o'));
            case FIRMWARE_VERSION + 15:
                return next(catta::json::Token::character('n'));
            case FIRMWARE_VERSION + 16:
                return next(catta::json::Token::closeString());
            case FIRMWARE_VERSION + 17:
                return next(catta::json::Token::colon());
            case FIRMWARE_VERSION + 18:
                return handle(_firmwareVersionSerializer, input.firmwareVersion(), catta::json::Token::comma());
            case BOTTSTRAPP_VERSION + 0:
                return next(catta::json::Token::openString());
            case BOTTSTRAPP_VERSION + 1:
                return next(catta::json::Token::character('b'));
            case BOTTSTRAPP_VERSION + 2:
                return next(catta::json::Token::character('o'));
            case BOTTSTRAPP_VERSION + 3:
                return next(catta::json::Token::character('t'));
            case BOTTSTRAPP_VERSION + 4:
                return next(catta::json::Token::character('t'));
            case BOTTSTRAPP_VERSION + 5:
                return next(catta::json::Token::character('s'));
            case BOTTSTRAPP_VERSION + 6:
                return next(catta::json::Token::character('t'));
            case BOTTSTRAPP_VERSION + 7:
                return next(catta::json::Token::character('r'));
            case BOTTSTRAPP_VERSION + 8:
                return next(catta::json::Token::character('a'));
            case BOTTSTRAPP_VERSION + 9:
                return next(catta::json::Token::character('p'));
            case BOTTSTRAPP_VERSION + 10:
                return next(catta::json::Token::character('p'));
            case BOTTSTRAPP_VERSION + 11:
                return next(catta::json::Token::character('V'));
            case BOTTSTRAPP_VERSION + 12:
                return next(catta::json::Token::character('e'));
            case BOTTSTRAPP_VERSION + 13:
                return next(catta::json::Token::character('r'));
            case BOTTSTRAPP_VERSION + 14:
                return next(catta::json::Token::character('s'));
            case BOTTSTRAPP_VERSION + 15:
                return next(catta::json::Token::character('i'));
            case BOTTSTRAPP_VERSION + 16:
                return next(catta::json::Token::character('o'));
            case BOTTSTRAPP_VERSION + 17:
                return next(catta::json::Token::character('n'));
            case BOTTSTRAPP_VERSION + 18:
                return next(catta::json::Token::closeString());
            case BOTTSTRAPP_VERSION + 19:
                return next(catta::json::Token::colon());
            case BOTTSTRAPP_VERSION + 20:
                return handle(_bottstrappVersionSerializer, input.bottstrappVersion(), catta::json::Token::closeCurlyBracket());
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
    Serializer<catta::modbus::sunspec::ValueU16> _serialnumberSerializer;
    Serializer<catta::modbus::si::Date> _productionDateSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 255>> _hardwareVersionSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 255>> _firmwareVersionSerializer;
    Serializer<catta::modbus::sunspec::ValueU8<0, 255>> _bottstrappVersionSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t SERIALNUMBER = START + 1;
    static constexpr std::uint8_t PRODUCTION_DATE = SERIALNUMBER + 16;
    static constexpr std::uint8_t HARDWARE_VERSION = PRODUCTION_DATE + 18;
    static constexpr std::uint8_t FIRMWARE_VERSION = HARDWARE_VERSION + 19;
    static constexpr std::uint8_t BOTTSTRAPP_VERSION = FIRMWARE_VERSION + 19;
    static constexpr std::uint8_t TAIL = BOTTSTRAPP_VERSION + 21;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tojson
}  // namespace catta
