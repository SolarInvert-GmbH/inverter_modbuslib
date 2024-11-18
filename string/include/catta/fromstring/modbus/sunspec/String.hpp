#pragma once

// catta
#include <catta/modbus/sunspec/String.hpp>

// fromjson
#include <catta/fromjson/modbus/sunspec/String.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>
#include <catta/fromstring/json/FromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::modbus::sunspec::String>
{
  public:
    using FromString = catta::fromstring::json::FromString<catta::modbus::sunspec::String>;
    using Error = FromString::Error;
    using Input = FromString::Input;
    using Output = FromString::Output;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept { return _fromString.read(input); }
    [[nodiscard]] constexpr Parser() noexcept {}
    [[nodiscard]] constexpr Output data() const noexcept { return _fromString.data(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _fromString.state(); }

  private:
    FromString _fromString;
};

}  // namespace fromstring
}  // namespace catta
