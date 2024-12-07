#pragma once

// catta
#include <catta/modbus/SlaveUartState.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::SlaveUartState>
{
  public:
    static constexpr std::string_view name = "catta::modbus::SlaveUartState";
};

}  // namespace tostring
}  // namespace catta
