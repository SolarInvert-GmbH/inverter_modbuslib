#pragma once

// model
#include <catta/modbus/sunspec/model/ImmediateControls.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::sunspec::model::ImmediateControls>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::sunspec::model::ImmediateControls;
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
            case START + 1:
                return input == Input::function(0x03) ? next() : error();
            case START + 2:
                return input == Input::data(0x02) ? next() : error();
            case DATA + 0:
                return high(_timeoutConnection);
            case DATA + 1:
                return low(_timeoutConnection);
            case DATA + 2:
                return high(_connectionControl);
            case DATA + 3:
                return low(_connectionControl);
            case DATA + 4:
                return high(_powerLimit);
            case DATA + 5:
                return low(_powerLimit);
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _timeoutConnection(0), _connectionControl(0), _powerLimit(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        using V = catta::modbus::sunspec::ValueU16;
        return _state != DONE ? Output::empty()
                              : Output::create(V::create(_timeoutConnection), V::create(_connectionControl), V::create(_powerLimit));
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
    std::uint16_t _timeoutConnection;
    std::uint16_t _connectionControl;
    std::uint16_t _powerLimit;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 6;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
