#pragma once

// catta
#include <catta/modbus/sunspec/String16.hpp>

// fromstring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <>
class GetName<catta::modbus::sunspec::String16>
{
  public:
    static constexpr std::string_view name = "catta::modbus::sunspec::String16";
};

template <>
class Serializer<catta::modbus::sunspec::String16>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::sunspec::String16;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _index = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        catta::parser::InputHandled handled = catta::parser::InputHandled::no();
        if (_index < TAIL)
        {
            const char c = input.data()[_index];
            _data = c;
            if (c == '\0')
            {
                _index = TAIL;
                handled = catta::parser::InputHandled::yes();
            }
        }
        else if (_index == TAIL)
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
        if (_index == START) return catta::parser::State::start();
        if (_index < DONE) return catta::parser::State::running();
        if (_index == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    char _data;
    std::size_t _index;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TAIL = Input::size;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};

}  // namespace tostring
}  // namespace catta
