#pragma once

// model
#include <catta/modbus/sunspec/model/CommonRead.hpp>

// fromjson
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::sunspec::model::CommonRead>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::sunspec::model::CommonRead;
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
        const auto character = [this, next, stay, input, error](Raw& string)
        {
            if (!input.type().isData()) return error();
            string[_index] = static_cast<char>(input.value());
            _index++;
            if (_index >= String::size)
            {
                _index = 0;
                return next();
            }
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
                return input == Input::data(0x62) ? next() : error();
            case DATA + 0:
                return character(_manufacturer);
            case DATA + 1:
                return character(_model);
            case DATA + 2:
                return character(_serialNumber);
            case DATA + 3:
                return high(_deviceAddress);
            case DATA + 4:
                return low(_deviceAddress);
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _state == DONE ? Output::create(String::create(_manufacturer.data()), String::create(_model.data()),
                                               String::create(_serialNumber.data()), Value::create(_deviceAddress))
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
    std::uint8_t _index;
    using String = catta::modbus::sunspec::String;
    using Raw = String::Raw;
    using Value = catta::modbus::sunspec::ValueU16;
    Raw _manufacturer;
    Raw _model;
    Raw _serialNumber;
    std::uint16_t _deviceAddress;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 5;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
