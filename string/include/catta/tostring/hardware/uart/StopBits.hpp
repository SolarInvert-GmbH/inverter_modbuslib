#pragma once

// catta
#include <catta/hardware/uart/StopBits.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::hardware::uart::StopBits>
{
  public:
    static constexpr std::string_view name = "catta::hardware::uart::StopBits";
};

}  // namespace tostring
}  // namespace catta
