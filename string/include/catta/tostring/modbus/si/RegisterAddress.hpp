#pragma once

// catta
#include <catta/modbus/si/RegisterAddress.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::si::RegisterAddress>
{
  public:
    static constexpr std::string_view name = "catta::modbus::si::RegisterAddress";
};

}  // namespace tostring
}  // namespace catta
