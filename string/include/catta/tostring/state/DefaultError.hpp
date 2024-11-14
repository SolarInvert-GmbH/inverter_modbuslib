#pragma once

// catta
#include <catta/state/DefaultError.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::state::DefaultError>
{
  public:
    static constexpr std::string_view name = "catta::state::DefaultError";
};

}  // namespace tostring
}  // namespace catta
