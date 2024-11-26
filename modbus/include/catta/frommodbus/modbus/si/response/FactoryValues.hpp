#pragma once

// request
#include <catta/modbus/si/response/FactoryValues.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::response::FactoryValues>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::response::FactoryValues;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
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
                return input == Input::function(0x31) ? next() : error();
            case START + 2:
                return input == Input::data(0x0C) ? next() : error();
            case DATA + 0:
                return high(_serialnumber);
            case DATA + 1:
                return low(_serialnumber);
            case DATA + 2:
                return set(_day, input.value() == 0 || input.value() > 31);
            case DATA + 3:
                return set(_month, input.value() == 0 || input.value() > 12);
            case DATA + 4:
                return set(_year, input.value() > 99);
            case DATA + 5:
                return set(_hardwareVersion, false);
            case DATA + 6:
                return set(_firmwareVersion, false);
            case DATA + 7:
                return set(_bootstrappVersion, false);
            case DATA + 8:
                return next();
            case DATA + 9:
                return next();
            case DATA + 10:
                return next();
            case DATA + 11:
                return next();
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept
        : _state(START), _serialnumber(0), _day(0), _month(0), _year(0), _hardwareVersion(0), _firmwareVersion(0), _bootstrappVersion(0)
    {
    }
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto date = [this]()
        {
            return catta::modbus::si::Date::create(catta::modbus::sunspec::ValueU8<1, 31>::create(_day),
                                                   catta::modbus::sunspec::ValueU8<1, 12>::create(_month),
                                                   catta::modbus::sunspec::ValueU8<0, 99>::create(_year));
        };
        const auto v16 = [](const std::uint16_t i) { return catta::modbus::sunspec::ValueU16::create(i); };
        const auto v8 = [](const std::uint8_t i) { return catta::modbus::sunspec::ValueU8<0, 255>::create(i); };
        return _state == DONE ? Output::create(v16(_serialnumber), date(), v8(_hardwareVersion), v8(_firmwareVersion), v8(_bootstrappVersion))
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
    std::uint16_t _serialnumber;
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint8_t _year;
    std::uint8_t _hardwareVersion;
    std::uint8_t _firmwareVersion;
    std::uint8_t _bootstrappVersion;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 12;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
