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
 * @brief Class for represening scaled signed int16_t values.
 *
 * @author CattaTech - Maik Urbannek
 */
class ScaledSValue
{
  public:
    /**
     * Default constructor. Creates invalid scaled signed value.
     */
    constexpr ScaledSValue() noexcept : ScaledSValue(ScaleFactor(), 0x0000) {}
    /**
     * @return Returns invalid scaled signed value.
     */
    constexpr static ScaledSValue empty() noexcept { return ScaledSValue{}; }
    /**
     *  @return Returns @b true if scaled signed value is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _scaleFactor.isEmpty(); }
    /**
     * @param[in] scaleFactor The scaling factor for the value. Has to be not empty, otherwise empty is returned.
     * @param[in] value Represening the signed value.
     * @return Returns scaled signed value if input is valid, otherwise empty.
     */
    static constexpr ScaledSValue create(const ScaleFactor scaleFactor, const std::int16_t value) { return ScaledSValue(scaleFactor, value); }
    /**
     * @return Returns the scale factor. Is only valid if not empty.
     */
    ScaleFactor scaleFactor() const noexcept { return _scaleFactor; }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    std::int16_t value() const noexcept { return _value; }
    /**
     * @param[in] other The other ScaledSValue.
     * @return Returns @b true if the two ScaledSValue objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const ScaledSValue& other) const noexcept = default;

  private:
    constexpr ScaledSValue(const ScaleFactor scaleFactor, std::int16_t value) : _scaleFactor(scaleFactor), _value(value) {}
    ScaleFactor _scaleFactor;
    std::int16_t _value;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
