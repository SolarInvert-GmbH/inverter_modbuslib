#pragma once

// catta
#include <catta/hardware/uart/DataBits.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::hardware::uart::DataBits>
{
  public:
    static constexpr std::string_view name = "catta::hardware::uart::DataBits";
};

}  // namespace tostring
}  // namespace catta
