#pragma once

// si
#include <catta/modbus/si/RegisterValue.hpp>

// tojson
#include <catta/tojson/modbus/si/RegisterValue.hpp>

// tostring
#include <catta/tostring/json/ToString.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::si::RegisterValue>
{
  public:
    static constexpr std::string_view name = "catta::modbus::si::RegisterValue";
};
template <>
class Serializer<catta::modbus::si::RegisterValue>
{
  public:
    using ToString = catta::tostring::json::ToString<catta::modbus::si::RegisterValue>;
    using Error = ToString::Error;
    using Input = ToString::Input;
    using Output = ToString::Output;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept { return _toString.read(input); }
    [[nodiscard]] constexpr Serializer() noexcept {}
    [[nodiscard]] constexpr Output data() const noexcept { return _toString.data(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _toString.state(); }

  private:
    ToString _toString;
};

}  // namespace tostring
}  // namespace catta
