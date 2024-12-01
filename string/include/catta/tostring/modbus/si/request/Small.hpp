#pragma once

// catta
#include <catta/modbus/si/request/Small.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::si::request::Small>
{
  public:
    static constexpr std::string_view name = "catta::modbus::si::request::Small";
};

template <>
class Serializer<catta::modbus::si::request::Small>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::si::request::Small;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        return _serializerHexadicmal.read(catta::Hexadecimal(input.function()));
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _serializerHexadicmal.data(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _serializerHexadicmal.state(); }

  private:
    catta::tostring::Serializer<catta::Hexadecimal<std::uint8_t>> _serializerHexadicmal;
    std::uint8_t _state;
    char _data;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t CLOSE = 1;
    static constexpr std::uint8_t HEXADECIMAL = 2;
    static constexpr std::uint8_t TAIL = 3;
    static constexpr std::uint8_t DONE = 4;
    static constexpr std::uint8_t ERROR = 5;
};

}  // namespace tostring
}  // namespace catta
