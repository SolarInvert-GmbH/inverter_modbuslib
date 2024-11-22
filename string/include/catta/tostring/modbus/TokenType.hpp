#pragma once

// catta
#include <catta/modbus/TokenType.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::TokenType>
{
  public:
    static constexpr std::string_view name = "catta::modbus::TokenType";
};

}  // namespace tostring
}  // namespace catta
