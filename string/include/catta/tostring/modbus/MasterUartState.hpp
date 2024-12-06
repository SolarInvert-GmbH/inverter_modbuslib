#pragma once

// catta
#include <catta/modbus/MasterUartState.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::MasterUartState>
{
  public:
    static constexpr std::string_view name = "catta::modbus::MasterUartState";
};

}  // namespace tostring
}  // namespace catta
