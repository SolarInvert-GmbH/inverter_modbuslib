#pragma once

// catta
#include <catta/linux/UartError.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::linux::UartError>
{
  public:
    static constexpr std::string_view name = "catta::linux::UartError";
};

}  // namespace tostring
}  // namespace catta
