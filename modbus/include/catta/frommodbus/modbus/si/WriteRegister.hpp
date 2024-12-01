#pragma once

// request
#include <catta/modbus/si/WriteRegister.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::WriteRegister>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::WriteRegister;
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
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case ADDRESS + 0:
                return input == Input::function(0x16) ? next() : error();
            case ADDRESS + 1:
                return high(_address);
            case ADDRESS + 2:
                return low(_address);
            case DATA + 0:
                return next();
            case DATA + 1:
                return next();
            case DATA + 2:
                return high(_data);
            case DATA + 3:
                return low(_data);
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _address(0), _data(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE) return Output::empty();
        using Type = catta::modbus::si::RegisterType;
        const auto address = catta::modbus::si::RegisterAddress::fromRaw(_address);
        const Type type = address.type();
        switch (type)
        {
            case Type::uint16():
                return Output::create(address, catta::modbus::sunspec::ValueU16::create(static_cast<std::uint16_t>(_data)));
            case Type::sint16():
                return Output::create(address, catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(_data)));
            case Type::connectedPhase():
                return Output::create(address, catta::modbus::sunspec::ConnectedPhase(static_cast<std::uint8_t>(_data)));
            default:
                return Output::empty();
        }
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
    std::uint16_t _address;
    std::uint16_t _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t ADDRESS = START + 1;
    static constexpr std::uint8_t DATA = ADDRESS + 3;
    static constexpr std::uint8_t TAIL = DATA + 4;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
