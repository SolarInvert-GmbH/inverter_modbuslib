#pragma once

// model
#include <catta/modbus/sunspec/model/ImmediateControls.hpp>

// fromjson
#include <catta/fromjson/modbus/sunspec/model/ImmediateControls.hpp>

// fromstring
#include <catta/fromstring/fromString.hpp>
#include <catta/fromstring/json/FromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::modbus::sunspec::model::ImmediateControls>
{
  public:
    using FromString = catta::fromstring::json::FromString<catta::modbus::sunspec::model::ImmediateControls>;
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
