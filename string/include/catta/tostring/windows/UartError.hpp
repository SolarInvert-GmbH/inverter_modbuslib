#pragma once

// catta
#include <catta/windows/UartError.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::windows::UartError>
{
  public:
    static constexpr std::string_view name = "catta::windows::UartError";
};

}  // namespace tostring
}  // namespace catta
