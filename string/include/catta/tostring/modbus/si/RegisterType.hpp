#pragma once

// catta
#include <catta/modbus/si/RegisterType.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::si::RegisterType>
{
  public:
    static constexpr std::string_view name = "catta::modbus::si::RegisterType";
};

}  // namespace tostring
}  // namespace catta
