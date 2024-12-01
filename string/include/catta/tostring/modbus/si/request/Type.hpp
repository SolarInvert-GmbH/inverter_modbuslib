#pragma once

// catta
#include <catta/modbus/si/request/Type.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::si::request::Type>
{
  public:
    static constexpr std::string_view name = "catta::modbus::si::request::Type";
};

}  // namespace tostring
}  // namespace catta
