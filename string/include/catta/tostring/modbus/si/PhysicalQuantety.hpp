#pragma once

// si
#include <catta/modbus/si/PhysicalQuantety.hpp>

// tojson
#include <catta/tojson/modbus/si/PhysicalQuantety.hpp>

// tostring
#include <catta/tostring/json/ToString.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <const char* UNIT>
class GetName<catta::modbus::si::PhysicalQuantety<UNIT>>
{
  private:
    static constexpr std::size_t unitLength = []()
    {
        std::size_t i = 0;
        for (const char* c = UNIT; (*c) != '\0'; c++) i++;
        return i;
    }();
    static constexpr std::size_t length = 37 + unitLength;
    constexpr static std::array<char, length + 1> raw = []()
    {
        std::array<char, length + 1> r = {};
        std::size_t i = 0;
        const auto character = [&r, &i](const char c)
        {
            r[i] = c;
            i++;
        };
        const auto string = [character](const char* s)
        {
            for (const char* p = s; *p != '\0'; p++) character(*p);
        };
        string("catta::modbus::si::PhysicalQuantety<");
        string(UNIT);
        string(">");
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};
template <const char* UNIT>
class Serializer<catta::modbus::si::PhysicalQuantety<UNIT>>
{
  private:
  public:
    using ToString = catta::tostring::json::ToString<catta::modbus::si::PhysicalQuantety<UNIT>>;
    using Error = ToString::Error;
    using Input = ToString::Input;
    using Output = ToString::Output;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept { return _toString.read(input); }
    [[nodiscard]] constexpr Serializer() noexcept {}
    [[nodiscard]] constexpr Output data() const noexcept { return _toString.data(); }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _toString.state(); }

  private:
    ToString _toString;
};

}  // namespace tostring
}  // namespace catta
