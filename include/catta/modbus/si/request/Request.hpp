#pragma once

// std
#include <array>

// si
#include <catta/modbus/si/ReadRegister.hpp>
#include <catta/modbus/si/WriteRegister.hpp>

// request
#include <catta/modbus/si/request/ConstantVoltage.hpp>
#include <catta/modbus/si/request/ControlBatteryInvert.hpp>
#include <catta/modbus/si/request/LimitBatteryInvert.hpp>
#include <catta/modbus/si/request/PowerFactor.hpp>
#include <catta/modbus/si/request/Type.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace request
{
/**
 * @brief Class for representing a request.
 *
 * @author CattaTech - Maik Urbannek
 */
class Request
{
  public:
    /**
     * Default constructor. Creates invalid request.
     */
    constexpr Request() noexcept : Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::empty()) {}
    /**
     * @return Returns invalid request.
     */
    constexpr static Request empty() noexcept { return Request{}; }
    /**
     *  @return Returns @b true if request is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _type.isEmpty(); }
    /**
     * @param[in] value The read register command. Has to be not empty, otherwise empty is returned.
     * @return Returns read register request if input is valid, otherwise empty.
     */
    static constexpr Request readRegister(const catta::modbus::si::ReadRegister value)
    {
        return value.isEmpty() ? Request::empty()
                               : Request(std::array<std::uint16_t, 4>{value.registerAddress()}, catta::modbus::si::request::Type::readRegister());
    }
    /**
     * @param[in] value The write register command. Has to be not empty, otherwise empty is returned.
     * @return Returns write register request if input is valid, otherwise empty.
     */
    static constexpr Request writeRegister(const catta::modbus::si::WriteRegister value)
    {
        return value.isEmpty()
                   ? Request::empty()
                   : Request(std::array<std::uint16_t, 4>{value.registerAddress(), value.raw()}, catta::modbus::si::request::Type::writeRegister());
    }
    /**
     * @return Returns factory values request.
     */
    static constexpr Request factoryValues() { return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::factoryValues()); }
    /**
     * @return Returns read operating data33 request if input is valid, otherwise empty.
     */
    static constexpr Request readOperatingData33()
    {
        return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::readOperatingData33());
    }
    /**
     * @return Returns read operating data3e request if input is valid, otherwise empty.
     */
    static constexpr Request readOperatingData3e()
    {
        return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::readOperatingData3e());
    }
    /**
     * @return Returns switch off grid relay request if input is valid, otherwise empty.
     */
    static constexpr Request switchOffGridRelay()
    {
        return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::switchOffGridRelay());
    }
    /**
     * @return Returns switch on grid relay request if input is valid, otherwise empty.
     */
    static constexpr Request switchOnGridRelay()
    {
        return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::switchOnGridRelay());
    }
    /**
     * @return Returns force idle request if input is valid, otherwise empty.
     */
    static constexpr Request forceIdle() { return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::forceIdle()); }
    /**
     * @return Returns deactivate idle request if input is valid, otherwise empty.
     */
    static constexpr Request deactivateIdle() { return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::deactivateIdle()); }
    /**
     * @param[in] value The start constant voltage command. Has to be not empty, otherwise empty is returned.
     * @return Returns start constant voltage request if input is valid, otherwise empty.
     */
    static constexpr Request startConstantVoltage(const catta::modbus::si::request::ConstantVoltage value)
    {
        return value.isEmpty()
                   ? Request::empty()
                   : Request(std::array<std::uint16_t, 4>{value.uSet().value()}, catta::modbus::si::request::Type::startConstantVoltage());
    }
    /**
     * @return Returns end constant voltage request if input is valid, otherwise empty.
     */
    static constexpr Request endConstantVoltage()
    {
        return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::endConstantVoltage());
    }
    /**
     * @param[in] value The set power factor command. Has to be not empty, otherwise empty is returned.
     * @return Returns set power factor request if input is valid, otherwise empty.
     */
    static constexpr Request setPowerFactor(const catta::modbus::si::request::PowerFactor value)
    {
        return value.isEmpty() ? Request::empty()
                               : Request(std::array<std::uint16_t, 4>{value.cosPhi().value()}, catta::modbus::si::request::Type::setPowerFactor());
    }
    /**
     * @param[in] value The control battery invert command. Has to be not empty, otherwise empty is returned.
     * @return Returns control battery invert request if input is valid, otherwise empty.
     */
    static constexpr Request controlBatteryInvert(const catta::modbus::si::request::ControlBatteryInvert value)
    {
        return value.isEmpty()
                   ? Request::empty()
                   : Request(
                         std::array<std::uint16_t, 4>{static_cast<std::uint16_t>(value.pMax().power() | (value.pMax().charging() ? 0x8000 : 0x0000)),
                                                      value.uMin().value(), value.uMax().value(), value.timeout().value()},
                         catta::modbus::si::request::Type::controlBatteryInvert());
    }
    /**
     * @param[in] value The limit battery invert command. Has to be not empty, otherwise empty is returned.
     * @return Returns limit battery invert request if input is valid, otherwise empty.
     */
    static constexpr Request limitBatteryInvert(const catta::modbus::si::request::LimitBatteryInvert value)
    {
        return value.isEmpty()
                   ? Request::empty()
                   : Request(std::array<std::uint16_t, 4>{value.pMaxfeed().value()}, catta::modbus::si::request::Type::limitBatteryInvert());
    }
    /**
     * @return Returns read error request if input is valid, otherwise empty.
     */
    static constexpr Request readError() { return Request(std::array<std::uint16_t, 4>{}, catta::modbus::si::request::Type::readError()); }
    /**
     * @return Returns read register value. Is only valid if type is read register.
     */
    constexpr catta::modbus::si::ReadRegister readRegisterValue() const noexcept
    {
        return catta::modbus::si::ReadRegister::create(catta::modbus::si::RegisterAddress(static_cast<std::uint8_t>(_data[0])));
    }
    /**
     * @return Returns write register value. Is only valid if type is write register.
     */
    constexpr catta::modbus::si::WriteRegister writeRegisterValue() const noexcept
    {
        return catta::modbus::si::WriteRegister::fromRaw(catta::modbus::si::RegisterAddress(static_cast<std::uint8_t>(_data[0])), _data[1]);
    }
    /**
     * @return Returns start constant voltage value. Is only valid if type is start constant voltage.
     */
    constexpr catta::modbus::si::request::ConstantVoltage startConstantVoltageValue() const noexcept
    {
        return catta::modbus::si::request::ConstantVoltage::create(catta::modbus::sunspec::ValueU16::create(_data[0]));
    }
    /**
     * @return Returns set power factor value. Is only valid if type is set power factor.
     */
    constexpr catta::modbus::si::request::PowerFactor setPowerFactorValue() const noexcept
    {
        return catta::modbus::si::request::PowerFactor::create(catta::modbus::sunspec::ValueU8<0, 255>::create(static_cast<std::uint8_t>(_data[0])));
    }
    /**
     * @return Returns control battery invert value. Is only valid if type is control battery invert.
     */
    constexpr catta::modbus::si::request::ControlBatteryInvert controlBatteryInvertValue() const noexcept
    {
        return catta::modbus::si::request::ControlBatteryInvert::create(
            catta::modbus::si::PowerConfig::fromRaw(_data[0]), catta::modbus::sunspec::ValueU16::create(_data[1]),
            catta::modbus::sunspec::ValueU16::create(_data[2]), catta::modbus::sunspec::ValueU16::create(_data[3]));
    }
    /**
     * @return Returns limit battery invert value. Is only valid if type is limit battery invert.
     */
    constexpr catta::modbus::si::request::LimitBatteryInvert limitBatteryInvertValue() const noexcept
    {
        return catta::modbus::si::request::LimitBatteryInvert::create(
            catta::modbus::sunspec::ValueU8<0, 100>::create(static_cast<std::uint8_t>(_data[0])));
    }
    /**
     * @param[in] other The other Request.
     * @return Returns @b true if the two Request objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Request& other) const noexcept = default;
    /**
     * @return Returns the type of the request.
     */
    constexpr catta::modbus::si::request::Type type() const noexcept { return _type; }

  private:
    constexpr Request(const std::array<std::uint16_t, 4> data, const catta::modbus::si::request::Type type) : _data(data), _type(type) {}
    std::array<std::uint16_t, 4> _data;
    catta::modbus::si::request::Type _type;
};
}  // namespace request
}  // namespace si
}  // namespace modbus
}  // namespace catta
