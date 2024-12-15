#pragma once

// request
#include <catta/modbus/si/request/ControlBatteryInvert.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::request::ControlBatteryInvert>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::request::ControlBatteryInvert;
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
                return input == Input::function(0x3F) ? next() : error();
            case START + 2:
                return input == Input::data(0x0D) ? next() : error();
            case DATA + 0:
                return high(_pMax);
            case DATA + 1:
                return low(_pMax);
            case DATA + 2:
                return high(_uMin);
            case DATA + 3:
                return low(_uMin);
            case DATA + 4:
                return high(_uMax);
            case DATA + 5:
                return low(_uMax);
            case DATA + 6:
                return high(_timeout);
            case DATA + 7:
                return low(_timeout);
            case DATA + 8:
                return next();
            case DATA + 9:
                return next();
            case DATA + 10:
                return next();
            case DATA + 11:
                return next();
            case DATA + 12:
                return next();
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _pMax(0), _uMin(0), _uMax(0), _timeout(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto pc = [this]() { return catta::modbus::si::PowerConfig::create(_pMax & 0x7fff, (_pMax & 0x8000) != 0); };
        const auto v = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueU16::create(i); };
        return _state == DONE ? Output::create(pc(), v(_uMin), v(_uMax), v(_timeout)) : Output::empty();
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
    std::uint16_t _pMax;
    std::uint16_t _uMin;
    std::uint16_t _uMax;
    std::uint16_t _timeout;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 13;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
