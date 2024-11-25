#pragma once

// model
#include <catta/modbus/sunspec/model/Inverter.hpp>

// tojson
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::sunspec::model::Inverter>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::model::Inverter;
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
        /* const auto character = [this, next, stay](const catta::modbus::sunspec::String& string)
         {
             const auto result = Output::data(static_cast<std::uint8_t>(string.data()[_index]));
             _index++;
             if (_index >= catta::modbus::sunspec::String::size)
             {
                 _index = 0;
                 return next(result);
             }
             return stay(result);
         };*/
        const auto u32 = [next](const auto v, const auto i) { return next(Output::data(static_cast<std::uint8_t>(v >> (8 * i)))); };
        const auto high = [next](const auto v) { return next(Output::data(static_cast<std::uint8_t>(v >> 8))); };
        const auto low = [next](const auto v) { return next(Output::data(static_cast<std::uint8_t>(v >> 0))); };
        switch (_state)
        {
            case START + 0:
                return next(Output::start());
            case START + 1:
                return next(Output::function(0x03));
            case START + 2:
                return next(Output::data(0x34));
            case DATA + 0:
                return high(input.ampere().overall().value());
            case DATA + 1:
                return low(input.ampere().overall().value());
            case DATA + 2:
                return high(input.ampere().phaseA().value());
            case DATA + 3:
                return low(input.ampere().phaseA().value());
            case DATA + 4:
                return high(input.ampere().phaseB().value());
            case DATA + 5:
                return low(input.ampere().phaseB().value());
            case DATA + 6:
                return high(input.ampere().phaseC().value());
            case DATA + 7:
                return low(input.ampere().phaseC().value());
            case DATA + 8:
                return high(input.ampere().scale().factorExponent());
            case DATA + 9:
                return low(input.ampere().scale().factorExponent());
            case DATA + 10:
                return high(input.voltage().phaseA().value());
            case DATA + 11:
                return low(input.voltage().phaseA().value());
            case DATA + 12:
                return high(input.voltage().phaseB().value());
            case DATA + 13:
                return low(input.voltage().phaseB().value());
            case DATA + 14:
                return high(input.voltage().phaseC().value());
            case DATA + 15:
                return low(input.voltage().phaseC().value());
            case DATA + 16:
                return high(input.voltage().scale().factorExponent());
            case DATA + 17:
                return low(input.voltage().scale().factorExponent());
            case DATA + 18:
                return high(input.watt().value().value());
            case DATA + 19:
                return low(input.watt().value().value());
            case DATA + 20:
                return high(input.watt().scale().factorExponent());
            case DATA + 21:
                return low(input.watt().scale().factorExponent());
            case DATA + 22:
                return high(input.hertz().value().value());
            case DATA + 23:
                return low(input.hertz().value().value());
            case DATA + 24:
                return high(input.hertz().scale().factorExponent());
            case DATA + 25:
                return low(input.hertz().scale().factorExponent());
            case DATA + 26:
                return high(input.powerFactor().value().value());
            case DATA + 27:
                return low(input.powerFactor().value().value());
            case DATA + 28:
                return high(input.powerFactor().scale().factorExponent());
            case DATA + 29:
                return low(input.powerFactor().scale().factorExponent());
            case DATA + 30:
                return u32(input.wattHours().value().value(), 3);
            case DATA + 31:
                return u32(input.wattHours().value().value(), 2);
            case DATA + 32:
                return u32(input.wattHours().value().value(), 1);
            case DATA + 33:
                return u32(input.wattHours().value().value(), 0);
            case DATA + 34:
                return high(input.wattHours().scale().factorExponent());
            case DATA + 35:
                return low(input.wattHours().scale().factorExponent());
            case DATA + 36:
                return high(input.dcVoltage().value().value());
            case DATA + 37:
                return low(input.dcVoltage().value().value());
            case DATA + 38:
                return high(input.dcVoltage().scale().factorExponent());
            case DATA + 39:
                return low(input.dcVoltage().scale().factorExponent());
            case DATA + 40:
                return high(input.cabinetTemperature().value().value());
            case DATA + 41:
                return low(input.cabinetTemperature().value().value());
            case DATA + 42:
                return high(input.cabinetTemperature().scale().factorExponent());
            case DATA + 43:
                return low(input.cabinetTemperature().scale().factorExponent());
            case DATA + 44:
                return high(input.operatingState().value());
            case DATA + 45:
                return low(input.operatingState().value());
            case DATA + 46:
                return high(input.vendorOperatingState().value());
            case DATA + 47:
                return low(input.vendorOperatingState().value());
            case DATA + 48:
                return u32(input.vendorEventBitfield().value(), 3);
            case DATA + 49:
                return u32(input.vendorEventBitfield().value(), 2);
            case DATA + 50:
                return u32(input.vendorEventBitfield().value(), 1);
            case DATA + 51:
                return u32(input.vendorEventBitfield().value(), 0);
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
    Output _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 52;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
