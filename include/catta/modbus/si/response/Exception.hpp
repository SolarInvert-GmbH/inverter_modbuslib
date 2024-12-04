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
class Exception
{
  private:
    constexpr static std::uint8_t INVALID_FUNCTION_CODE = 0;
    constexpr static std::uint8_t INVALID_REGISTER_ADDRESS = 1;
    constexpr static std::uint8_t INVALID_DATA_VALUE = 2;
    constexpr static std::uint8_t DEVICE_ERROR = 3;
    constexpr static std::uint8_t EMPTY = 4;

  public:
    /**
     * @param[in] value The enum value of the type.
     * @warning This constructor should not be used. Use invalidFunctionCode(), invalidRegisterAddress(), invalidDataValue(), deviceError() or
     * empty(). Explicit constructor. Converts uint8 to type.
     */
    [[nodiscard]] constexpr explicit Exception(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid type.
     */
    [[nodiscard]] constexpr Exception() noexcept : Exception(EMPTY) {}
    /**
     * @return Returns the invalid function code.
     */
    [[nodiscard]] constexpr static Exception invalidFunctionCode() noexcept { return Exception{INVALID_FUNCTION_CODE}; }
    /**
     * @return Returns the invalid register address.
     */
    [[nodiscard]] constexpr static Exception invalidRegisterAddress() noexcept { return Exception{INVALID_REGISTER_ADDRESS}; }
    /**
     * @return Returns the invalid data value.
     */
    [[nodiscard]] constexpr static Exception invalidDataValue() noexcept { return Exception{INVALID_DATA_VALUE}; }
    /**
     * @return Returns the device error.
     */
    [[nodiscard]] constexpr static Exception deviceError() noexcept { return Exception{DEVICE_ERROR}; }
    /**
     * @return Returns the invalid type.
     */
    [[nodiscard]] constexpr static Exception empty() noexcept { return Exception{EMPTY}; }
    /**
     * @param[in] other The other Exception.
     * @return Returns @b true if the two Exception objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Exception& other) const = default;
    /**
     * @return Returns type as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if invalid function code is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInvalidFunctionCode() const noexcept { return _value == INVALID_FUNCTION_CODE; }
    /**
     * @return Returns @b true if invalid register address is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInvalidRegisterAddress() const noexcept { return _value == INVALID_REGISTER_ADDRESS; }
    /**
     * @return Returns @b true if invalid data value is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isInvalidDataValue() const noexcept { return _value == INVALID_DATA_VALUE; }
    /**
     * @return Returns @b true if device error is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isDeviceError() const noexcept { return _value == DEVICE_ERROR; }
    /**
     * @return Returns @b true if invalid type is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Type in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"INVALID_FUNCTION_CODE", "INVALID_REGISTER_ADDRESS", "INVALID_DATA_VALUE",
                                                                      "DEVICE_ERROR"};

  private:
    std::uint8_t _value;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
