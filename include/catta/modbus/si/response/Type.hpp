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
namespace response
{
/**
 * @brief Represents the si type.
 * @author CattaTech - Maik Urbannek
 */
class Type
{
  private:
    constexpr static std::uint8_t SUCCESS = 0;
    constexpr static std::uint8_t EXCEPTION = 1;
    constexpr static std::uint8_t FACTORY_VALUES = 2;
    constexpr static std::uint8_t READ_ERROR = 3;
    constexpr static std::uint8_t READ_OPERATING_DATA_33 = 4;
    constexpr static std::uint8_t READ_OPERATING_DATA_3E = 5;
    constexpr static std::uint8_t UINT16 = 6;
    constexpr static std::uint8_t SINT16 = 7;
    constexpr static std::uint8_t SCALE_FACTOR = 8;
    constexpr static std::uint8_t CONNECTED_PHASE = 9;
    constexpr static std::uint8_t UINT32 = 10;
    constexpr static std::uint8_t UINT64 = 11;
    constexpr static std::uint8_t STRING32 = 12;
    constexpr static std::uint8_t EMPTY = 13;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use success(), exception(), factoryValues(), readError(), readOperatingData33(),
     * readOperatingData3e(), uint16(), sint16(), scaleFactor(), connectedPhase(), uint32(), uint64(), string32() or empty(). Explicit constructor.
     * Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit Type(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr Type() noexcept : Type(EMPTY) {}
    /**
     * @return Returns the success response.
     */
    [[nodiscard]] constexpr static Type success() noexcept { return Type{SUCCESS}; }
    /**
     * @return Returns the exception response.
     */
    [[nodiscard]] constexpr static Type exception() noexcept { return Type{EXCEPTION}; }
    /**
     * @return Returns the factory values response.
     */
    [[nodiscard]] constexpr static Type factoryValues() noexcept { return Type{FACTORY_VALUES}; }
    /**
     * @return Returns the read error response.
     */
    [[nodiscard]] constexpr static Type readError() noexcept { return Type{READ_ERROR}; }
    /**
     * @return Returns the read operating data 0x33 response.
     */
    [[nodiscard]] constexpr static Type readOperatingData33() noexcept { return Type{READ_OPERATING_DATA_33}; }
    /**
     * @return Returns the read operating data 0x3e response.
     */
    [[nodiscard]] constexpr static Type readOperatingData3e() noexcept { return Type{READ_OPERATING_DATA_3E}; }
    /**
     * @return Returns the uint16 response.
     */
    [[nodiscard]] constexpr static Type uint16() noexcept { return Type{UINT16}; }
    /**
     * @return Returns the sint16 type.
     */
    [[nodiscard]] constexpr static Type sint16() noexcept { return Type{SINT16}; }
    /**
     * @return Returns the scaled response response.
     */
    [[nodiscard]] constexpr static Type scaleFactor() noexcept { return Type{SCALE_FACTOR}; }
    /**
     * @return Returns the connected phase enum response.
     */
    [[nodiscard]] constexpr static Type connectedPhase() noexcept { return Type{CONNECTED_PHASE}; }
    /**
     * @return Returns the uint32 response.
     */
    [[nodiscard]] constexpr static Type uint32() noexcept { return Type{UINT32}; }
    /**
     * @return Returns the uint64 response.
     */
    [[nodiscard]] constexpr static Type uint64() noexcept { return Type{UINT64}; }
    /**
     * @return Returns the string32 response.
     */
    [[nodiscard]] constexpr static Type string32() noexcept { return Type{STRING32}; }
    /**
     * @return Returns the invalid type.
     */
    [[nodiscard]] constexpr static Type empty() noexcept { return Type{EMPTY}; }
    /**
     * @param[in] other The other Type.
     * @return Returns @b true if the two Type objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Type& other) const = default;
    /**
     * @return Returns type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if success response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSuccess() const noexcept { return _value == SUCCESS; }
    /**
     * @return Returns @b true if exception response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isException() const noexcept { return _value == EXCEPTION; }
    /**
     * @return Returns @b true if factory values response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isFactoryValues() const noexcept { return _value == FACTORY_VALUES; }
    /**
     * @return Returns @b true if read error response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadError() const noexcept { return _value == READ_ERROR; }
    /**
     * @return Returns @b true if read operating data 0x33 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadOperatingData33() const noexcept { return _value == READ_OPERATING_DATA_33; }
    /**
     * @return Returns @b true if read operating data 0x3e response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isReadOperatingData3e() const noexcept { return _value == READ_OPERATING_DATA_3E; }
    /**
     * @return Returns @b true if uint16 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint16() const noexcept { return _value == UINT16; }
    /**
     * @return Returns @b true if sint16 type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isSint16() const noexcept { return _value == SINT16; }
    /**
     * @return Returns @b true if scaled response response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isScaleFactor() const noexcept { return _value == SCALE_FACTOR; }
    /**
     * @return Returns @b true if connected phase enum response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isConnectedPhase() const noexcept { return _value == CONNECTED_PHASE; }
    /**
     * @return Returns @b true if uint32 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint32() const noexcept { return _value == UINT32; }
    /**
     * @return Returns @b true if uint64 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isUint64() const noexcept { return _value == UINT64; }
    /**
     * @return Returns @b true if string32 response is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isString32() const noexcept { return _value == STRING32; }
    /**
     * @return Returns @b true if invalid type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"SUCCESS",
                                                                      "EXCEPTION",
                                                                      "FACTORY_VALUES",
                                                                      "READ_ERROR",
                                                                      "READ_OPERATING_DATA_33",
                                                                      "READ_OPERATING_DATA_3E",
                                                                      "UINT16",
                                                                      "SINT16",
                                                                      "SCALE_FACTOR",
                                                                      "CONNECTED_PHASE",
                                                                      "UINT32",
                                                                      "UINT64",
                                                                      "STRING32"};

  private:
    std::uint8_t _value;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
