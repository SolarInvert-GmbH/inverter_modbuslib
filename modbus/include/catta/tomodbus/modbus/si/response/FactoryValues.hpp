#pragma once

// model
#include <catta/modbus/si/response/FactoryValues.hpp>

// tomodbus
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::si::response::FactoryValues>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::FactoryValues;
    using Output = catta::modbus::Token;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
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
                return next(Output::function(0x31));
            case START + 2:
                return next(Output::data(0x0C));
            case DATA + 0:
                return high(input.serialnumber().value());
            case DATA + 1:
                return low(input.serialnumber().value());
            case DATA + 2:
                return next(Output::data(input.productionDate().day().value()));
            case DATA + 3:
                return next(Output::data(input.productionDate().month().value()));
            case DATA + 4:
                return next(Output::data(input.productionDate().year().value()));
            case DATA + 5:
                return next(Output::data(input.hardwareVersion().value()));
            case DATA + 6:
                return next(Output::data(input.firmwareVersion().value()));
            case DATA + 7:
                return next(Output::data(input.bootstrappVersion().value()));
            case DATA + 8:
                return next(Output::data(0x00));
            case DATA + 9:
                return next(Output::data(0x00));
            case DATA + 10:
                return next(Output::data(0x00));
            case DATA + 11:
                return next(Output::data(0x00));
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
    static constexpr std::uint8_t TAIL = DATA + 12;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
