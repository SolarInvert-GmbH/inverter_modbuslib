#pragma once

// catta
#include <catta/modbus/sunspec/ValueU8.hpp>

// json
#include <catta/tojson/modbus/sunspec/ValueU8.hpp>

// fromstring
#include <catta/tostring/Decimal.hpp>
#include <catta/tostring/json/ToString.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <std::uint8_t MIN, std::uint8_t MAX>
class GetName<catta::modbus::sunspec::ValueU8<MIN, MAX>>
{
    using D = catta::Decimal<std::uint8_t>;
    constexpr static D min = D(MIN);
    constexpr static D max = D(MAX);
    constexpr static std::size_t minLength = catta::tostring::getLength<D>(min);
    constexpr static std::size_t maxLength = catta::tostring::getLength<D>(max);
    constexpr static std::array<char, minLength + 1> minName = catta::tostring::toStaticString<D, minLength>(min);
    constexpr static std::array<char, maxLength + 1> maxName = catta::tostring::toStaticString<D, maxLength>(max);
    constexpr static std::size_t length = 34 + minLength + maxLength;
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
        string("catta::modbus::sunspec::ValueU8<");
        string(minName.data());
        character(',');
        string(maxName.data());
        character('>');
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};

template <std::uint8_t MIN, std::uint8_t MAX>
class Serializer<catta::modbus::sunspec::ValueU8<MIN, MAX>>
{
  public:
    using ToString = catta::tostring::json::ToString<catta::modbus::sunspec::ValueU8<MIN, MAX>>;
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
