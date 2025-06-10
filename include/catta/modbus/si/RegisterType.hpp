#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Represents the si register type.
 * @author CattaTech - Maik Urbannek
 */
class RegisterType
{
  private:
    constexpr static std::uint8_t UINT16 = 0;
    constexpr static std::uint8_t SINT16 = 1;
    constexpr static std::uint8_t SCALE_FACTOR = 2;
    constexpr static std::uint8_t CONNECTED_PHASE = 3;
    constexpr static std::uint8_t UINT32 = 4;
    constexpr static std::uint8_t UINT64 = 5;
    constexpr static std::uint8_t STRING32 = 6;
    constexpr static std::uint8_t EMPTY = 7;

  public:
    /**
     * @param[in] value The enum value of the register type.
     * @warning This constructor should not be used. Use uint16(), sint16(), scaleFactor(), connectedPhase(), uint32(), uint64(), string32() or
     * empty(). Explicit constructor. Converts uint8 to register type.
     */
    [[nodiscard]] constexpr explicit RegisterType(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid register type.
     */
    [[nodiscard]] constexpr RegisterType() noexcept : RegisterType(EMPTY) {}
    /**
     * @return Returns the uint16 type.
     */
    [[nodiscard]] constexpr static RegisterType uint16() noexcept { return RegisterType{UINT16}; }
    /**
     * @return Returns the sint16 type.
     */
    [[nodiscard]] constexpr static RegisterType sint16() noexcept { return RegisterType{SINT16}; }
    /**
     * @return Returns the scaled factor type.
     */
    [[nodiscard]] constexpr static RegisterType scaleFactor() noexcept { return RegisterType{SCALE_FACTOR}; }
    /**
     * @return Returns the connected phase enum type.
     */
    [[nodiscard]] constexpr static RegisterType connectedPhase() noexcept { return RegisterType{CONNECTED_PHASE}; }
    /**
     * @return Returns the uint32 type.
     */
    [[nodiscard]] constexpr static RegisterType uint32() noexcept { return RegisterType{UINT32}; }
    /**
     * @return Returns the uint64 type.
     */
    [[nodiscard]] constexpr static RegisterType uint64() noexcept { return RegisterType{UINT64}; }
    /**
     * @return Returns the string32 type.
     */
    [[nodiscard]] constexpr static RegisterType string32() noexcept { return RegisterType{STRING32}; }
    /**
     * @return Returns the invalid register type.
     */
    [[nodiscard]] constexpr static RegisterType empty() noexcept { return RegisterType{EMPTY}; }
    /**
     * @param[in] other The other RegisterType.
     * @return Returns @b true if the two RegisterType objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const RegisterType& other) const = default;
    /**
     * @return Returns register type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if uint16 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint16() const noexcept { return _value == UINT16; }
    /**
     * @return Returns @b true if sint16 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSint16() const noexcept { return _value == SINT16; }
    /**
     * @return Returns @b true if scaled factor type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isScaleFactor() const noexcept { return _value == SCALE_FACTOR; }
    /**
     * @return Returns @b true if connected phase enum type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isConnectedPhase() const noexcept { return _value == CONNECTED_PHASE; }
    /**
     * @return Returns @b true if uint32 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint32() const noexcept { return _value == UINT32; }
    /**
     * @return Returns @b true if uint64 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint64() const noexcept { return _value == UINT64; }
    /**
     * @return Returns @b true if string32 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isString32() const noexcept { return _value == STRING32; }
    /**
     * @return Returns @b true if invalid register type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Register type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"UINT16", "SINT16", "SCALE_FACTOR", "CONNECTED_PHASE",
                                                                      "UINT32", "UINT64", "STRING32"};

    /**
     * @return Returns the needed bytes for the type.
     */
    constexpr std::uint8_t size() const noexcept
    {
        switch (_value)
        {
            case UINT16:
            case SINT16:
            case SCALE_FACTOR:
            case CONNECTED_PHASE:
                return 2;
            case UINT32:
                return 4;
            case UINT64:
                return 8;
            case STRING32:
                return 32;
            default:
                return 0;
        }
    }

    /**
     * @return Returns the abbreviation for the type.
     */
    constexpr std::string_view abbreviation() const noexcept
    {
        switch (_value)
        {
            case UINT16:
                return std::string_view("uI16");
            case SINT16:
                return std::string_view("sI16");
            case SCALE_FACTOR:
                return std::string_view("ScFa");
            case CONNECTED_PHASE:
                return std::string_view("CoPh");
            case UINT32:
                return std::string_view("uI32");
            case UINT64:
                return std::string_view("uI64");
            case STRING32:
                return std::string_view("St32");
            default:
                return std::string_view("EMPT");
        }
    }

  private:
    std::uint8_t _value;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
