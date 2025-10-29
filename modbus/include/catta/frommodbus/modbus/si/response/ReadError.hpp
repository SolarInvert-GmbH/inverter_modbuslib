#pragma once

// request
#include <catta/modbus/si/response/ReadError.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::response::ReadError>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::response::ReadError;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto high = [next, input](std::uint16_t& v)
        {
            v = static_cast<std::uint16_t>(input.value() << 8);
            return next();
        };
        const auto low = [next, input](std::uint16_t& v)
        {
            v = static_cast<std::uint16_t>(v | input.value());
            return next();
        };
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case START + 1:
                return input == Input::function(0x40) ? next() : error();
            case START + 2:
                return input == Input::data(0x2E) ? next() : error();
            case DATA + 0:
                return high(_overVoltageAC);
            case DATA + 1:
                return low(_overVoltageAC);
            case DATA + 2:
                return high(_underVoltageAC);
            case DATA + 3:
                return low(_underVoltageAC);
            case DATA + 4:
                return high(_overVoltageDC);
            case DATA + 5:
                return low(_overVoltageDC);
            case DATA + 6:
                return high(_underVoltageDC);
            case DATA + 7:
                return low(_underVoltageDC);
            case DATA + 8:
                return high(_overFrequency);
            case DATA + 9:
                return low(_overFrequency);
            case DATA + 10:
                return high(_underFrequency);
            case DATA + 11:
                return low(_underFrequency);
            case DATA + 12:
                return high(_limitedPowerT1);
            case DATA + 13:
                return low(_limitedPowerT1);
            case DATA + 14:
                return high(_limitedPowerT2);
            case DATA + 15:
                return low(_limitedPowerT2);
            case DATA + 16:
                return high(_limitedPowerT3);
            case DATA + 17:
                return low(_limitedPowerT3);
            case DATA + 18:
                return high(_limitedPowerT4);
            case DATA + 19:
                return low(_limitedPowerT4);
            case DATA + 20:
                return high(_limitedPowerT5);
            case DATA + 21:
                return low(_limitedPowerT5);
            case DATA + 22:
                return high(_com);
            case DATA + 23:
                return low(_com);
            case DATA + 24:
                return high(_islandGrid);
            case DATA + 25:
                return low(_islandGrid);
            case DATA + 26:
                return high(_overCurrentInterrupt);
            case DATA + 27:
                return low(_overCurrentInterrupt);
            case DATA + 28:
                return high(_overVoltageInterrupt);
            case DATA + 29:
                return low(_overVoltageInterrupt);
            case DATA + 30:
                return high(_averageGridOverVoltage);
            case DATA + 31:
                return low(_averageGridOverVoltage);
            case DATA + 32:
                return high(_overTempratureShutdown);
            case DATA + 33:
                return low(_overTempratureShutdown);
            case DATA + 34:
                return high(_differenceGridVoltage);
            case DATA + 35:
                return low(_differenceGridVoltage);
            case DATA + 36:
                return high(_errorGridRelais);
            case DATA + 37:
                return low(_errorGridRelais);
            case DATA + 38:
                return high(_errorCurrentSensor);
            case DATA + 39:
                return low(_errorCurrentSensor);
            case DATA + 40:
                return next();
            case DATA + 41:
                return next();
            case DATA + 42:
                return next();
            case DATA + 43:
                return next();
            case DATA + 44:
                return next();
            case DATA + 45:
                return next();
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept
        : _state(START),
          _overVoltageAC(0),
          _underVoltageAC(0),
          _overVoltageDC(0),
          _underVoltageDC(0),
          _overFrequency(0),
          _underFrequency(0),
          _limitedPowerT1(0),
          _limitedPowerT2(0),
          _limitedPowerT3(0),
          _limitedPowerT4(0),
          _limitedPowerT5(0),
          _com(0),
          _islandGrid(0),
          _overCurrentInterrupt(0),
          _overVoltageInterrupt(0),
          _averageGridOverVoltage(0),
          _overTempratureShutdown(0),
          _differenceGridVoltage(0),
          _errorGridRelais(0),
          _errorCurrentSensor(0)
    {
    }
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto v = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueU16::create(i); };
        return _state == DONE ? Output::create(v(_overVoltageAC), v(_underVoltageAC), v(_overVoltageDC), v(_underVoltageDC), v(_overFrequency),
                                               v(_underFrequency), v(_limitedPowerT1), v(_limitedPowerT2), v(_limitedPowerT3), v(_limitedPowerT4),
                                               v(_limitedPowerT5), v(_com), v(_islandGrid), v(_overCurrentInterrupt), v(_overVoltageInterrupt),
                                               v(_averageGridOverVoltage), v(_overTempratureShutdown), v(_differenceGridVoltage), v(_errorGridRelais),
                                               v(_errorCurrentSensor)

                                                   )
                              : Output::empty();
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    std::uint16_t _overVoltageAC;
    std::uint16_t _underVoltageAC;
    std::uint16_t _overVoltageDC;
    std::uint16_t _underVoltageDC;
    std::uint16_t _overFrequency;
    std::uint16_t _underFrequency;
    std::uint16_t _limitedPowerT1;
    std::uint16_t _limitedPowerT2;
    std::uint16_t _limitedPowerT3;
    std::uint16_t _limitedPowerT4;
    std::uint16_t _limitedPowerT5;
    std::uint16_t _com;
    std::uint16_t _islandGrid;
    std::uint16_t _overCurrentInterrupt;
    std::uint16_t _overVoltageInterrupt;
    std::uint16_t _averageGridOverVoltage;
    std::uint16_t _overTempratureShutdown;
    std::uint16_t _differenceGridVoltage;
    std::uint16_t _errorGridRelais;
    std::uint16_t _errorCurrentSensor;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 46;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
