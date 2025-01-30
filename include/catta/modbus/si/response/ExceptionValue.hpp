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
 * @brief Represents the si exception value.
 * @author CattaTech - Maik Urbannek
 */
class ExceptionValue
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
    [[nodiscard]] constexpr explicit ExceptionValue(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid value.
     */
    [[nodiscard]] constexpr ExceptionValue() noexcept : ExceptionValue(EMPTY) {}
    /**
     * @return Returns the invalid function code.
     */
    [[nodiscard]] constexpr static ExceptionValue invalidFunctionCode() noexcept { return ExceptionValue{INVALID_FUNCTION_CODE}; }
    /**
     * @return Returns the invalid register address.
     */
    [[nodiscard]] constexpr static ExceptionValue invalidRegisterAddress() noexcept { return ExceptionValue{INVALID_REGISTER_ADDRESS}; }
    /**
     * @return Returns the invalid data value.
     */
    [[nodiscard]] constexpr static ExceptionValue invalidDataValue() noexcept { return ExceptionValue{INVALID_DATA_VALUE}; }
    /**
     * @return Returns the device error.
     */
    [[nodiscard]] constexpr static ExceptionValue deviceError() noexcept { return ExceptionValue{DEVICE_ERROR}; }
    /**
     * @return Returns the invalid value.
     */
    [[nodiscard]] constexpr static ExceptionValue empty() noexcept { return ExceptionValue{EMPTY}; }
    /**
     * @param[in] other The other ExceptionValue.
     * @return Returns @b true if the two ExceptionValue objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const ExceptionValue& other) const = default;
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
     * @return Returns @b true if invalid value is represented, otherwise @b false.
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
