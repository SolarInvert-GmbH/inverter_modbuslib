#pragma once

// catta
#include <catta/parser/State.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::parser::State>
{
  public:
    static constexpr std::string_view name = "catta::parser::State";
};

}  // namespace tostring
}  // namespace catta
