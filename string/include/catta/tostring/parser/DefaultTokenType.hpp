#pragma once

// catta
#include <catta/parser/DefaultTokenType.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::parser::DefaultTokenType>
{
  public:
    static constexpr std::string_view name = "catta::parser::DefaultTokenType";
};

}  // namespace tostring
}  // namespace catta
