#pragma once

// request
#include <catta/modbus/si/response/ReadOperatingData3e.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::response::ReadOperatingData3e>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::response::ReadOperatingData3e;
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
        const auto u32 = [next, input](std::uint32_t& v, const std::uint32_t i)
        {
            v = i == 3 ? static_cast<std::uint32_t>(input.value() << (8 * i))
                       : static_cast<std::uint32_t>(v | static_cast<std::uint32_t>(input.value() << (8 * i)));
            return next();
        };
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case START + 1:
                return input == Input::function(0x3E) ? next() : error();
            case START + 2:
                return input == Input::data(0x16) ? next() : error();
            case DATA + 0:
                return high(_serialNumber);
            case DATA + 1:
                return low(_serialNumber);
            case DATA + 2:
                return set(_type, catta::modbus::si::Type(input.value()).isEmpty());
            case DATA + 3:
                return set(_voltageType, catta::modbus::sunspec::ValueU8<1, 10>::create(input.value()).isEmpty());
            case DATA + 4:
                return set(_nominalPower, catta::modbus::sunspec::ValueU8<1, 32>::create(input.value()).isEmpty());
            case DATA + 5:
                return set(_cosphi, false);
            case DATA + 6:
                return u32(_gridSupplyDailySum, 3);
            case DATA + 7:
                return u32(_gridSupplyDailySum, 2);
            case DATA + 8:
                return u32(_gridSupplyDailySum, 1);
            case DATA + 9:
                return u32(_gridSupplyDailySum, 0);
            case DATA + 10:
                return high(_powerLimitation);
            case DATA + 11:
                return low(_powerLimitation);
            case DATA + 12:
                return u32(_operatingHours, 3);
            case DATA + 13:
                return u32(_operatingHours, 2);
            case DATA + 14:
                return u32(_operatingHours, 1);
            case DATA + 15:
                return u32(_operatingHours, 0);
            case DATA + 16:
                return set(_phase, catta::modbus::sunspec::ValueU8<0, 3>::create(input.value()).isEmpty());
            case DATA + 17:
                return set(_modbusId, catta::modbus::sunspec::ValueU8<0, 15>::create(input.value()).isEmpty());
            case DATA + 18:
                return next();
            case DATA + 19:
                return next();
            case DATA + 20:
                return next();
            case DATA + 21:
                return next();
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept
        : _state(START),
          _serialNumber(0),
          _type(0),
          _voltageType(0),
          _nominalPower(0),
          _cosphi(0),
          _gridSupplyDailySum(0),
          _powerLimitation(0),
          _operatingHours(0),
          _phase(0),
          _modbusId(0)
    {
    }
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto vu16 = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueU16::create(i); };
        const auto vu32 = [](const std::uint32_t i) { return catta::modbus::sunspec::ValueU32::create(i); };
        const auto t = [](const std::uint8_t i) { return catta::modbus::si::Type(i); };
        const auto vu8_1_10 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<1, 10>::create(i); };
        const auto vu8_1_32 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<1, 32>::create(i); };
        const auto vu8_0_3 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<0, 3>::create(i); };
        const auto vu8_0_15 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<0, 15>::create(i); };
        const auto vu8_0_255 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<0, 255>::create(i); };
        return _state == DONE
                   ? Output::create(vu16(_serialNumber), t(_type), vu8_1_10(_voltageType), vu8_1_32(_nominalPower), vu8_0_255(_cosphi),
                                    vu32(_gridSupplyDailySum), vu16(_powerLimitation), vu32(_operatingHours), vu8_0_3(_phase), vu8_0_15(_modbusId))
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
    std::uint16_t _serialNumber;
    std::uint8_t _type;
    std::uint8_t _voltageType;
    std::uint8_t _nominalPower;
    std::uint8_t _cosphi;
    std::uint32_t _gridSupplyDailySum;
    std::uint16_t _powerLimitation;
    std::uint32_t _operatingHours;
    std::uint8_t _phase;
    std::uint8_t _modbusId;

    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 22;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
