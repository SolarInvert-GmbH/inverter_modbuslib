#pragma once

// model
#include <catta/modbus/sunspec/model/CommonRead.hpp>

// tojson
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::sunspec::model::CommonRead>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::CommonRead;
    using Output = catta::modbus::Token;
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
            _data = Output::end();
            _state = DONE + 0;
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this](const Output token)
        {
            _data = token;
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto next = [stay, this](const Output token)
        {
            _state++;
            return stay(token);
        };
        const auto character = [this, next, stay](const catta::modbus::sunspec::String& string)
        {
            const auto result = Output::data(static_cast<std::uint8_t>(string.data()[_index]));
            _index++;
            if (_index >= catta::modbus::sunspec::String::size)
            {
                _index = 0;
                return next(result);
            }
            return stay(result);
        };
        const auto high = [next](const catta::modbus::sunspec::ValueU16 v) { return next(Output::data(static_cast<std::uint8_t>(v.value() >> 8))); };
        const auto low = [next](const catta::modbus::sunspec::ValueU16 v) { return next(Output::data(static_cast<std::uint8_t>(v.value() >> 0))); };
        switch (_state)
        {
            case START + 0:
                return next(Output::start());
            case START + 1:
                return next(Output::function(0x03));
            case START + 2:
                return next(Output::data(0x62));
            case DATA + 0:
                return character(input.manufacturer());
            case DATA + 1:
                return character(input.model());
            case DATA + 2:
                return character(input.serialNumber());
            case DATA + 3:
                return high(input.deviceAddress());
            case DATA + 4:
                return low(input.deviceAddress());
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _index(0), _data(Output::empty()) {}
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
    std::uint8_t _index;
    Output _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 5;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
