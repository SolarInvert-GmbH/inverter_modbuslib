#pragma once

// request
#include <catta/modbus/si/response/ReadOperatingData33.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::response::ReadOperatingData33>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::response::ReadOperatingData33;
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
        const auto set = [next, input, error](std::uint8_t& v, const bool dead)
        {
            if (dead) return error();
            v = input.value();
            return next();
        };
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case START + 1:
                return input == Input::function(0x33) ? next() : error();
            case START + 2:
                return input == Input::data(0x15) ? next() : error();
            case DATA + 0:
                return high(_dcVoltage);
            case DATA + 1:
                return low(_dcVoltage);
            case DATA + 2:
                return next();
            case DATA + 3:
                return set(_acVoltage, false);
            case DATA + 4:
                return next();
            case DATA + 5:
                return high(_gridFrequency);
            case DATA + 6:
                return low(_gridFrequency);
            case DATA + 7:
                return high(_acPower);
            case DATA + 8:
                return low(_acPower);
            case DATA + 9:
                return next();
            case DATA + 10:
                return set(_s, catta::modbus::si::State(input.value()).isEmpty());
            case DATA + 11:
                return next();
            case DATA + 12:
                return next();
            case DATA + 13:
                return next();
            case DATA + 14:
                return next();
            case DATA + 15:
                return next();
            case DATA + 16:
                return next();
            case DATA + 17:
                return next();
            case DATA + 18:
                return next();
            case DATA + 19:
                return next();
            case DATA + 20:
                return next();
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _dcVoltage(0), _acVoltage(0), _gridFrequency(0), _acPower(0), _s(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto vu16 = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueU16::create(i); };
        const auto vs16 = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(i)); };
        const auto s = [](const std::uint8_t i) { return catta::modbus::si::State(i); };
        const auto vu8 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<0, 255>::create(i); };

        return _state == DONE ? Output::create(vu16(_dcVoltage), vu8(_acVoltage), vu16(_gridFrequency), vs16(_acPower), s(_s)) : Output::empty();
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
    std::uint16_t _dcVoltage;
    std::uint8_t _acVoltage;
    std::uint16_t _gridFrequency;
    std::uint16_t _acPower;
    std::uint8_t _s;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 21;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
