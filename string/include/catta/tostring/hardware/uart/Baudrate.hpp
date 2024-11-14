#pragma once

// catta
#include <catta/hardware/uart/Baudrate.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::hardware::uart::Baudrate>
{
  public:
    static constexpr std::string_view name = "catta::hardware::uart::Baudrate";
};

}  // namespace tostring
}  // namespace catta
