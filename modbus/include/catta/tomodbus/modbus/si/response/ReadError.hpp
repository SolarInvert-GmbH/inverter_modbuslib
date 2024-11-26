#pragma once

// model
#include <catta/modbus/si/response/ReadError.hpp>

// tomodbus
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::si::response::ReadError>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::ReadError;
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
        const auto high = [next](const auto v) { return next(Output::data(static_cast<std::uint8_t>(v >> 8))); };
        const auto low = [next](const auto v) { return next(Output::data(static_cast<std::uint8_t>(v >> 0))); };
        switch (_state)
        {
            case START + 0:
                return next(Output::start());
            case START + 1:
                return next(Output::function(0x40));
            case START + 2:
                return next(Output::data(0x2E));
            case DATA + 0:
                return high(input.overVoltageAC().value());
            case DATA + 1:
                return low(input.overVoltageAC().value());
            case DATA + 2:
                return high(input.underVoltageAC().value());
            case DATA + 3:
                return low(input.underVoltageAC().value());
            case DATA + 4:
                return high(input.overVoltageDC().value());
            case DATA + 5:
                return low(input.overVoltageDC().value());
            case DATA + 6:
                return high(input.underVoltageDC().value());
            case DATA + 7:
                return low(input.underVoltageDC().value());
            case DATA + 8:
                return high(input.overFrequency().value());
            case DATA + 9:
                return low(input.overFrequency().value());
            case DATA + 10:
                return high(input.underFrequency().value());
            case DATA + 11:
                return low(input.underFrequency().value());
            case DATA + 12:
                return high(input.limitedPowerT1().value());
            case DATA + 13:
                return low(input.limitedPowerT1().value());
            case DATA + 14:
                return high(input.limitedPowerT2().value());
            case DATA + 15:
                return low(input.limitedPowerT2().value());
            case DATA + 16:
                return high(input.limitedPowerT3().value());
            case DATA + 17:
                return low(input.limitedPowerT3().value());
            case DATA + 18:
                return high(input.limitedPowerT4().value());
            case DATA + 19:
                return low(input.limitedPowerT4().value());
            case DATA + 20:
                return high(input.limitedPowerT5().value());
            case DATA + 21:
                return low(input.limitedPowerT5().value());
            case DATA + 22:
                return high(input.com().value());
            case DATA + 23:
                return low(input.com().value());
            case DATA + 24:
                return high(input.islandGrid().value());
            case DATA + 25:
                return low(input.islandGrid().value());
            case DATA + 26:
                return next(Output::data(0x00));
            case DATA + 27:
                return next(Output::data(0x00));
            case DATA + 28:
                return next(Output::data(0x00));
            case DATA + 29:
                return next(Output::data(0x00));
            case DATA + 30:
                return high(input.overCurrentInterrupt().value());
            case DATA + 31:
                return low(input.overCurrentInterrupt().value());
            case DATA + 32:
                return next(Output::data(0x00));
            case DATA + 33:
                return next(Output::data(0x00));
            case DATA + 34:
                return high(input.overVoltageInterrupt().value());
            case DATA + 35:
                return low(input.overVoltageInterrupt().value());
            case DATA + 36:
                return high(input.averageGridOverVoltage().value());
            case DATA + 37:
                return low(input.averageGridOverVoltage().value());
            case DATA + 38:
                return high(input.overTempratureShutdown().value());
            case DATA + 39:
                return low(input.overTempratureShutdown().value());
            case DATA + 40:
                return high(input.differenceGridVoltage().value());
            case DATA + 41:
                return low(input.differenceGridVoltage().value());
            case DATA + 42:
                return high(input.errorGridRelais().value());
            case DATA + 43:
                return low(input.errorGridRelais().value());
            case DATA + 44:
                return high(input.errorCurrentSensor().value());
            case DATA + 45:
                return low(input.errorCurrentSensor().value());
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
    static constexpr std::uint8_t TAIL = DATA + 46;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
