#pragma once

// catta
#include <catta/ConstString.hpp>

// tostring
#include <catta/tostring/Decimal.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{

template <std::size_t I>
class GetName<catta::ConstString<I>>
{
  private:
    using D = catta::Decimal<std::size_t>;
    constexpr static D d = D(I);
    constexpr static std::size_t numberLength = catta::tostring::getLength<D>(d);
    constexpr static std::array<char, numberLength + 1> numberName = catta::tostring::toStaticString<D, numberLength>(d);
    constexpr static std::size_t length = 20 + numberLength;
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
        string("catta::ConstString<");
        string(numberName.data());
        string(">");
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};

template <std::size_t I>
class Serializer<ConstString<I>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = ConstString<I>;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _index = sizeof(I) * 2 + 2;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        catta::parser::InputHandled handled = catta::parser::InputHandled::no();
        if (_index < sizeof(I) * 2)
        {
            _data = input[_index];
        }
        else if (_index == sizeof(I) * 2)
        {
            _data = '\0';
            handled = catta::parser::InputHandled::yes();
        }
        else
            return error();
        _index++;
        return Tuple{Error{}, handled};
    }
    [[nodiscard]] constexpr Serializer() noexcept : _data('\0'), _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_index == 0) return catta::parser::State::start();
        if (_index <= sizeof(I) * 2) return catta::parser::State::running();
        if (_index == sizeof(I) * 2 + 1) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    char _data;
    std::size_t _index;
};
}  // namespace tostring
}  // namespace catta
