#pragma once

// model
#include <catta/modbus/si/response/Response.hpp>

// tomodbus
#include <catta/tomodbus/modbus/si/response/FactoryValues.hpp>
#include <catta/tomodbus/modbus/si/response/ReadError.hpp>
#include <catta/tomodbus/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/tomodbus/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::si::response::Response>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::response::Response;
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
        const auto jump = [stay, this](const Output token, const std::uint8_t state)
        {
            _state = state;
            return stay(token);
        };
        const auto handle = [jump, error, done](auto& serializer, const auto value)
        {
            [[maybe_unused]] auto ignore = serializer.read(value);
            if (serializer.state().isFailed()) return error();
            if (serializer.state().isDone()) return done();
            return jump(serializer.data(), HANDLE + 0);
        };
        // TODO remove getFunctionCode
        const auto getFunctionCode = [input]() -> std::uint8_t
        {
            using Type = catta::modbus::si::response::Type;
            switch (input.type())
            {
                case Type::switchOffGridRelay():
                    return 0x34;
                case Type::switchOnGridRelay():
                    return 0x35;
                case Type::forceIdle():
                    return 0x36;
                case Type::deactivateIdle():
                    return 0x37;
                case Type::startConstantVoltage():
                    return 0x38;
                case Type::endConstantVoltage():
                    return 0x39;
                case Type::setPowerFactor():
                    return 0x3B;
                case Type::controlBatteryInvert():
                    return 0x3F;
                case Type::limitBatteryInvert():
                    return 0x44;
                default:
                    return 0x00;
            }
        };
        const auto handleSplitt = [&input, error, handle, jump, this]()
        {
            using Type = catta::modbus::si::response::Type;
            switch (input.type())
            {
                case Type::exception():
                    return jump(Output::start(), EXCEPTION + 0);
                case Type::factoryValues():
                    return handle(_factoryValuesSerializer, input.factoryValuesValue());
                case Type::readError():
                    return handle(_readErrorSerializer, input.readErrorValue());
                case Type::readOperatingData33():
                    return handle(_readOperatingData33Serializer, input.readOperatingData33Value());
                case Type::readOperatingData3e():
                    return handle(_readOperatingData3eSerializer, input.readOperatingData3eValue());
                case Type::switchOffGridRelay():
                case Type::switchOnGridRelay():
                case Type::forceIdle():
                case Type::deactivateIdle():
                case Type::startConstantVoltage():
                case Type::endConstantVoltage():
                case Type::setPowerFactor():
                case Type::controlBatteryInvert():
                case Type::limitBatteryInvert():
                    return jump(Output::start(), SUCCESS + 0);
                case Type::writeRegister():
                    return jump(Output::start(), WRITE_REGISTER + 0);
                case Type::value16():
                case Type::value32():
                case Type::value64():
                case Type::string16():
                case Type::string32():
                    return jump(Output::start(), READ_REGISTER + 0);
                default:
                    return error();
            }
        };
        const auto getSize = [input]() -> std::uint8_t
        {
            switch (input.type())
            {
                case catta::modbus::si::response::Type::value16():
                    return 2;
                case catta::modbus::si::response::Type::value32():
                    return 4;
                case catta::modbus::si::response::Type::value64():
                    return 8;
                case catta::modbus::si::response::Type::string16():
                    return 16;
                case catta::modbus::si::response::Type::string32():
                    return 32;
                default:
                    return 0;
            }
        };
        const auto high = [jump](const std::uint16_t i, const std::uint8_t state)
        { return jump(Output::data(static_cast<std::uint8_t>(i >> 8)), state); };
        const auto low = [jump](const std::uint16_t i, const std::uint8_t state)
        { return jump(Output::data(static_cast<std::uint8_t>(i >> 0)), state); };
        const auto lowRead = [this, low, input, getSize]()
        {
            const std::uint8_t index = _index;
            _index++;
            return low(input.raw()[index], _index >= getSize() / 2 ? TAIL + 0 : READ_REGISTER + 2);
        };
        switch (_state)
        {
            case START + 0:
                return handleSplitt();
            case HANDLE + 0:
                return handleSplitt();
            case READ_REGISTER + 0:
                return jump(Output::function(0x03), READ_REGISTER + 1);
            case READ_REGISTER + 1:
                return jump(Output::data(getSize()), READ_REGISTER + 2);
            case READ_REGISTER + 2:
                return high(input.raw()[_index], READ_REGISTER + 3);
            case READ_REGISTER + 3:
                return lowRead();
            case WRITE_REGISTER + 0:
                return jump(Output::function(0x10), WRITE_REGISTER + 1);
            case WRITE_REGISTER + 1:
                return high(input.writeRegisterValue().raw(), WRITE_REGISTER + 2);
            case WRITE_REGISTER + 2:
                return low(input.writeRegisterValue().raw(), WRITE_REGISTER + 3);
            case WRITE_REGISTER + 3:
                return jump(Output::data(0x00), WRITE_REGISTER + 4);
            case WRITE_REGISTER + 4:
                return jump(Output::data(0x01), TAIL + 0);
            case SUCCESS + 0:
                return jump(Output::function(getFunctionCode()), SUCCESS + 1);
            case SUCCESS + 1:
                return jump(Output::data(0x01), SUCCESS + 2);
            case SUCCESS + 2:
                return jump(Output::data(input.successValue() ? 0x01 : 0x00), TAIL + 0);
            case EXCEPTION + 0:
                return jump(Output::exception(input.exceptionValue().request().toModbus() | 0x80), EXCEPTION + 1);
            case EXCEPTION + 1:
                return jump(Output::data(0x01), EXCEPTION + 2);
            case EXCEPTION + 2:
                return jump(Output::data(input.exceptionValue().value() + 1), TAIL + 0);
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START), _count(0), _index(0), _data(Output::empty()) {}
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
    std::uint8_t _count;
    std::uint8_t _index;
    Output _data;
    Serializer<catta::modbus::si::response::FactoryValues> _factoryValuesSerializer;
    Serializer<catta::modbus::si::response::ReadError> _readErrorSerializer;
    Serializer<catta::modbus::si::response::ReadOperatingData33> _readOperatingData33Serializer;
    Serializer<catta::modbus::si::response::ReadOperatingData3e> _readOperatingData3eSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HANDLE = START + 1;
    static constexpr std::uint8_t READ_REGISTER = HANDLE + 1;
    static constexpr std::uint8_t WRITE_REGISTER = READ_REGISTER + 4;
    static constexpr std::uint8_t SUCCESS = WRITE_REGISTER + 5;
    static constexpr std::uint8_t EXCEPTION = SUCCESS + 3;
    static constexpr std::uint8_t TAIL = EXCEPTION + 3;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
