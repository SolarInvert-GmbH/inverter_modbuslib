#pragma once

// si
#include <catta/modbus/sunspec/ValueU8.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
/**
 * @brief Class for representing the date.
 *
 * @author CattaTech - Maik Urbannek
 */
class Date
{
  public:
    /**
     * Default constructor. Creates invalid date.
     */
    constexpr Date() noexcept
        : Date(catta::modbus::sunspec::ValueU8<1, 31>::empty(), catta::modbus::sunspec::ValueU8<1, 12>::empty(),
               catta::modbus::sunspec::ValueU8<0, 99>::empty())
    {
    }
    /**
     * @return Returns invalid date.
     */
    constexpr static Date empty() noexcept { return Date{}; }
    /**
     *  @return Returns @b true if date is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _day.isEmpty(); }
    /**
     * @param[in] day The day. Has to be valid, otherwise empty is returned.
     * @param[in] month The month. Has to be valid, otherwise empty is returned.
     * @param[in] year The year. Has to be valid, otherwise empty is returned.
     * @return Returns date if input is valid, otherwise empty.
     */
    static constexpr Date create(const catta::modbus::sunspec::ValueU8<1, 31> day, const catta::modbus::sunspec::ValueU8<1, 12> month,
                                 const catta::modbus::sunspec::ValueU8<0, 99> year)
    {
        return day.isEmpty() || month.isEmpty() || year.isEmpty() ? empty() : Date(day, month, year);
    }
    /**
     * @return Returns the day. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<1, 31> day() const noexcept { return _day; }
    /**
     * @return Returns the month. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<1, 12> month() const noexcept { return _month; }
    /**
     * @return Returns the year. Is only valid if not empty.
     */
    catta::modbus::sunspec::ValueU8<0, 99> year() const noexcept { return _year; }
    /**
     * @param[in] other The other Date.
     * @return Returns @b true if the two Date objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Date& other) const noexcept = default;

  private:
    constexpr Date(const catta::modbus::sunspec::ValueU8<1, 31> day, const catta::modbus::sunspec::ValueU8<1, 12> month,
                   const catta::modbus::sunspec::ValueU8<0, 99> year)
        : _day(day), _month(month), _year(year)
    {
    }
    catta::modbus::sunspec::ValueU8<1, 31> _day;
    catta::modbus::sunspec::ValueU8<1, 12> _month;
    catta::modbus::sunspec::ValueU8<0, 99> _year;
};
}  // namespace si
}  // namespace modbus
}  // namespace catta
