#pragma once

// catta
#include <catta/modbus/UartState.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::UartState>
{
  public:
    static constexpr std::string_view name = "catta::modbus::UartState";
};

}  // namespace tostring
}  // namespace catta
