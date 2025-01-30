#pragma once

// response
#include <catta/modbus/si/response/ExceptionValue.hpp>

// request
#include <catta/modbus/si/request/Type.hpp>

namespace catta
{
namespace modbus
{
namespace si
{
namespace response
{
/**
 * @brief Class for representing the exception.
 *
 * @author CattaTech - Maik Urbannek
 */
class Exception
{
  public:
    /**
     * Default constructor. Creates invalid exception.
     */
    constexpr Exception() noexcept : Exception(catta::modbus::si::response::ExceptionValue::empty(), catta::modbus::si::request::Type::empty()) {}
    /**
     * @return Returns invalid exception.
     */
    constexpr static Exception empty() noexcept { return Exception{}; }
    /**
     *  @return Returns @b true if exception is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _value.isEmpty(); }
    /**
     * @param[in] value The value. Has to be valid, otherwise empty is returned.
     * @param[in] request The request. Has to be valid, otherwise empty is returned.
     * @return Returns exception if input is valid, otherwise empty.
     */
    static constexpr Exception create(const catta::modbus::si::response::ExceptionValue value, const catta::modbus::si::request::Type request)
    {
        return value.isEmpty() || request.isEmpty() ? empty() : Exception(value, request);
    }
    /**
     * @return Returns the value. Is only valid if not empty.
     */
    constexpr catta::modbus::si::response::ExceptionValue value() const noexcept { return _value; }
    /**
     * @return Returns the request. Is only valid if not empty.
     */
    constexpr catta::modbus::si::request::Type request() const noexcept { return _request; }
    /**
     * @param[in] other The other Exception.
     * @return Returns @b true if the two Exception objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const Exception& other) const noexcept = default;

  private:
    constexpr Exception(const catta::modbus::si::response::ExceptionValue value, const catta::modbus::si::request::Type request)
        : _value(value), _request(request)
    {
    }
    catta::modbus::si::response::ExceptionValue _value;
    catta::modbus::si::request::Type _request;
};
}  // namespace response
}  // namespace si
}  // namespace modbus
}  // namespace catta
