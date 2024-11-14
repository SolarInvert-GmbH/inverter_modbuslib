#pragma once

// catta
#include <catta/json/TokenType.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::json::TokenType>
{
  public:
    static constexpr std::string_view name = "catta::json::TokenType";
};

}  // namespace tostring
}  // namespace catta
