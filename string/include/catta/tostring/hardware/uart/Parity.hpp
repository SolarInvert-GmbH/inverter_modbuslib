#pragma once

// catta
#include <catta/hardware/uart/Parity.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::hardware::uart::Parity>
{
  public:
    static constexpr std::string_view name = "catta::hardware::uart::Parity";
};

}  // namespace tostring
}  // namespace catta
