#pragma once

// model
#include <catta/modbus/si/request/Request.hpp>

// tomodbus
#include <catta/tomodbus/modbus/si/ReadRegister.hpp>
#include <catta/tomodbus/modbus/si/WriteRegister.hpp>
#include <catta/tomodbus/modbus/si/request/ConstantVoltage.hpp>
#include <catta/tomodbus/modbus/si/request/ControlBatteryInvert.hpp>
#include <catta/tomodbus/modbus/si/request/LimitBatteryInvert.hpp>
#include <catta/tomodbus/modbus/si/request/PowerFactor.hpp>
#include <catta/tomodbus/modbus/si/request/Small.hpp>
#include <catta/tomodbus/toModbus.hpp>

namespace catta
{
namespace tomodbus
{
template <>
class Serializer<catta::modbus::si::request::Request>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::request::Request;
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
        const auto handleSplitt = [&input, error, handle, this]()
        {
            using Type = catta::modbus::si::request::Type;
            switch (input.type())
            {
                case Type::readRegister():
                    return handle(_readRegisterSerializer, input.readRegisterValue());
                case Type::writeRegister():
                    return handle(_writeRegisterSerializer, input.writeRegisterValue());
                case Type::factoryValues():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x31));
                case Type::readOperatingData33():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x33));
                case Type::readOperatingData3e():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x3e));
                case Type::switchOffInverter():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x34));
                case Type::switchOnInverter():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x35));
                case Type::forceIdle():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x36));
                case Type::deactivateIdle():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x37));
                case Type::startConstantVoltage():
                    return handle(_constantVoltageSerializer, input.startConstantVoltageValue());
                case Type::endConstantVoltage():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x39));
                case Type::setPowerFactor():
                    return handle(_powerFactorSerializer, input.setPowerFactorValue());
                case Type::controlBatteryInvert():
                    return handle(_controlBatteryInvertSerializer, input.controlBatteryInvertValue());
                case Type::limitBatteryInvert():
                    return handle(_limitBatteryInvertSerializer, input.limitBatteryInvertValue());
                case Type::readError():
                    return handle(_smallSerializer, catta::modbus::si::request::Small::create(0x40));
                default:
                    return error();
            }
        };
        switch (_state)
        {
            case START + 0:
                return handleSplitt();
            case HANDLE + 0:
                return handleSplitt();
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
    Serializer<catta::modbus::si::request::Small> _smallSerializer;
    Serializer<catta::modbus::si::request::PowerFactor> _powerFactorSerializer;
    Serializer<catta::modbus::si::request::LimitBatteryInvert> _limitBatteryInvertSerializer;
    Serializer<catta::modbus::si::request::ConstantVoltage> _constantVoltageSerializer;
    Serializer<catta::modbus::si::request::ControlBatteryInvert> _controlBatteryInvertSerializer;
    Serializer<catta::modbus::si::WriteRegister> _writeRegisterSerializer;
    Serializer<catta::modbus::si::ReadRegister> _readRegisterSerializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HANDLE = START + 1;
    static constexpr std::uint8_t DONE = HANDLE + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace tomodbus
}  // namespace catta
