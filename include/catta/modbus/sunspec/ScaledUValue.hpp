#pragma once

// std
#include <cstdint>

// sunspec
#include <catta/modbus/sunspec/ScaleFactor.hpp>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for represening scaled unsigned int16_t values.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledUValue
{
  public:
    /**
     * Default constructor. Creates invalid scaled unsigned value.
     */
    constexpr ScaledUValue() noexcept : ScaledUValue(ScaleFactor(), 0x0000) {}
    /**
     * @return Returns invalid scaled unsigned value.
     */
    constexpr static ScaledUValue empty() noexcept { return ScaledUValue{}; }
    /**
     *  @return Returns @b true if scaled unsigned value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _scaleFactor.isEmpty(); }
    /**
     * @param[in] scaleFactor The scaling factor for the value. Has to be not empty, otherwise empty is returned.
     * @param[in] value Represening the unsigned value.
     * @return Returns scaled unsigned value if input is valid, otherwise empty.
     */
    static constexpr ScaledUValue create(const ScaleFactor scaleFactor, const std::uint16_t value) { return ScaledUValue(scaleFactor, value); }
    /**
     * @return Returns the scale factor. Is only valid if not empty.
     */
    ScaleFactor scaleFactor() const noexcept { return _scaleFactor; }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    std::uint16_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ScaledUValue.
     * @return Returns @b true if the two ScaledUValue objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledUValue& other) const noexcept = default;

  private:
    constexpr ScaledUValue(const ScaleFactor scaleFactor, std::uint16_t value) : _scaleFactor(scaleFactor), _value(value) {}
    ScaleFactor _scaleFactor;
    std::uint16_t _value;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
