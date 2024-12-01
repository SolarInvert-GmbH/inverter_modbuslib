#pragma once

// catta
#include <catta/modbus/si/request/Small.hpp>

// fromstring
#include <catta/fromstring/Hexadecimal.hpp>
#include <catta/fromstring/fromString.hpp>

namespace catta
{
namespace fromstring
{
template <>
class Parser<catta::modbus::si::request::Small>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = char;
    using Output = catta::modbus::si::request::Small;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        return _parserHexadecimal.read(input);
    }
    [[nodiscard]] constexpr Parser() noexcept {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        return _parserHexadecimal.state().isDone() ? Output::create(std::uint8_t(_parserHexadecimal.data())) : Output::empty();
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _parserHexadecimal.state(); }

  private:
    catta::fromstring::Parser<catta::Hexadecimal<std::uint8_t>> _parserHexadecimal;
};

}  // namespace fromstring
}  // namespace catta
