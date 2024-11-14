#pragma once

// catta
#include <catta/json/ParsingError.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::json::ParsingError>
{
  public:
    static constexpr std::string_view name = "catta::json::ParsingError";
};

}  // namespace tostring
}  // namespace catta
