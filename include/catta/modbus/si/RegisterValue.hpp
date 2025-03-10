#pragma once

// si
#include <catta/modbus/si/RegisterAddress.hpp>
#include <catta/modbus/sunspec/String.hpp>
#include <catta/modbus/sunspec/ValueU16.hpp>
#include <catta/modbus/sunspec/ValueU32.hpp>
#include <catta/modbus/sunspec/ValueU64.hpp>

// std
#include <array>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Class for representing the possible sunspec write register command.
 *
 * @author CattaTech - Maik Urbannek
 */
class RegisterValue
{
  public:
    /**
     * Default constructor. Creates invalid register value.
     */
    constexpr RegisterValue() noexcept : RegisterValue(Raw{}, catta::modbus::si::RegisterAddress::empty()) {}
    /**
     * @return Returns invalid register value.
     */
    constexpr static RegisterValue empty() noexcept { return RegisterValue{}; }
    /**
     *  @return Returns @b true if register value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _registerAddress.isEmpty(); }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns register value16 if input is valid, otherwise empty.
     */
    static constexpr RegisterValue value16(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::ValueU16 value)
    {
        const auto t = registerAddress.type();
        return value.isEmpty() || !(t.isUint16() || t.isSint16() || t.isConnectedPhase() || t.isScaleFactor())
                   ? empty()
                   : RegisterValue(Raw{value.value()}, registerAddress);
    }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns register value32 if input is valid, otherwise empty.
     */
    static constexpr RegisterValue value32(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::ValueU32 value)
    {
        return value.isEmpty() || !registerAddress.type().isUint32()
                   ? empty()
                   : RegisterValue(Raw{pack(value.value(), 1), pack(value.value(), 0)}, registerAddress);
    }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @return Returns register value64 if input is valid, otherwise empty.
     */
    static constexpr RegisterValue value64(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::ValueU64 value)
    {
        return value.isEmpty() || !registerAddress.type().isUint64()
                   ? empty()
                   : RegisterValue(Raw{pack(value.value(), 3), pack(value.value(), 2), pack(value.value(), 1), pack(value.value(), 0)},
                                   registerAddress);
    }
    /**
     * @param[in] registerAddress The registerAddress. Has to be valid, otherwise empty is returned.
     * @param[in] value The string. Has to be not empty, otherwise empty is returned.
     * @return Returns string response if input is valid, otherwise empty.
     */
    static constexpr RegisterValue string(const catta::modbus::si::RegisterAddress registerAddress, const catta::modbus::sunspec::String& value)
    {
        const auto pack = [&value]()
        {
            Raw r = {};
            for (std::size_t i = 0; i < catta::modbus::sunspec::String::size / 2; i++)
                r[i] = static_cast<std::uint16_t>((value.data()[(i * 2) + 0] << 8) | value.data()[(i * 2) + 1]);
            return r;
        };
        return value.isEmpty() || !registerAddress.type().isString32() ? RegisterValue::empty() : RegisterValue(pack(), registerAddress);
    }
    /**
     * Constructor. Dont use.
     * @param[in] data The raw data.
     * @param[in] registerAddress The register address. Can not be empty.
     */
    explicit constexpr RegisterValue(const std::array<std::uint16_t, 16>& data, const catta::modbus::si::RegisterAddress registerAddress)
        : _data(data), _registerAddress(registerAddress)
    {
    }

    /**
     * @return Returns the register address. Is only valid if not empty.
     */
    constexpr catta::modbus::si::RegisterAddress registerAddress() const noexcept { return _registerAddress; }
    /**
     * @return Returns value16 value. Is only valid if type is value16.
     */
    constexpr catta::modbus::sunspec::ValueU16 value16Value() const noexcept { return catta::modbus::sunspec::ValueU16::create(_data[0]); }
    /**
     * @return Returns value32 value. Is only valid if type is value32.
     */
    constexpr catta::modbus::sunspec::ValueU32 value32Value() const noexcept
    {
        return catta::modbus::sunspec::ValueU32::create(unpack(_data[0], _data[1]));
    }
    /**
     * @return Returns value64 value. Is only valid if type is value64.
     */
    constexpr catta::modbus::sunspec::ValueU64 value64Value() const noexcept
    {
        return catta::modbus::sunspec::ValueU64::create(unpack(_data[0], _data[1], _data[2], _data[3]));
    }
    /**
     * @return Returns string value. Is only valid if type is string.
     */
    constexpr catta::modbus::sunspec::String stringValue() const noexcept
    {
        catta::modbus::sunspec::String::Raw r = {};
        for (std::size_t i = 0; i < catta::modbus::sunspec::String::size / 2; i++)
        {
            r[i * 2 + 0] = static_cast<char>(_data[i] >> 8);
            r[i * 2 + 1] = static_cast<char>(_data[i] >> 0);
        }
        return catta::modbus::sunspec::String::create(r.data());
    }
    /**
     * @return Returns the raw value. Is only valid if not empty.
     */
    constexpr std::array<std::uint16_t, 16> raw() const noexcept { return _data; }
    /**
     * @param[in] other The other RegisterValue.
     * @return Returns @b true if the two RegisterValue objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const RegisterValue& other) const noexcept = default;

  private:
    using Raw = std::array<std::uint16_t, 16>;
    Raw _data;
    catta::modbus::si::RegisterAddress _registerAddress;
    constexpr static std::uint16_t pack(const auto v, const auto i) { return static_cast<std::uint16_t>(v >> (i * 16)); }
    constexpr static std::uint32_t unpack(const std::uint16_t v1, const std::uint16_t v0) { return static_cast<std::uint32_t>((v1 << (16)) | v0); }
    constexpr static std::uint64_t unpack(const std::uint16_t v3, const std::uint16_t v2, const std::uint16_t v1, const std::uint16_t v0)
    {
        return (static_cast<std::uint64_t>(v3) << 48) | (static_cast<std::uint64_t>(v2) << 32) | (static_cast<std::uint64_t>(v1) << 16) |
               (static_cast<std::uint64_t>(v0) << 0);
    }
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
