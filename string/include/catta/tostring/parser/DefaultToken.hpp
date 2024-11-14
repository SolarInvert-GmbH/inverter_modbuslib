#pragma once

// catta
#include <catta/parser/DefaultToken.hpp>

// tostring
#include <catta/tostring/Hexadecimal.hpp>
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{
template <class Character, catta::parser::ErrorConcept Error>
class GetName<catta::parser::DefaultToken<Character, Error>>
{
  private:
    constexpr static auto _name = catta::ConstString<30>::create("catta::parser::DefaultToken<") + getNameAsConstString<Character>() +
                                  catta::ConstString<1>::create(",") + getNameAsConstString<Error>() + catta::ConstString<1>::create(">");

  public:
    static constexpr std::string_view name = _name.data();
};

template <class Character, catta::parser::ErrorConcept ERROR>
class Serializer<catta::parser::DefaultToken<Character, ERROR>>
{
  private:
    using Type = catta::parser::DefaultTokenType;
    using Base = std::conditional<sizeof(Character) == 4, std::uint32_t, std::uint8_t>::type;
    using Hex = catta::Hexadecimal<Base>;
    constexpr static std::string_view EMPTY = "EMPTY";
    constexpr static std::string_view END = Type::enumNames[Type::end()].data();

  public:
    using Error = catta::state::DefaultError;
    using Input = catta::parser::DefaultToken<Character, ERROR>;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = catta::parser::State::failed();
            _data = '\0';
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = [this]()
        {
            _state = catta::parser::State::running();
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };
        const auto done = [this]()
        {
            _state = catta::parser::State::done();
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        if (_state.isFailed() || _state.isDone()) return error();
        if (input.type().isValue())
        {
            const auto hexadecimal = catta::Hexadecimal<Base>(static_cast<Base>(input.characterValue()));
            [[maybe_unused]] const auto ignore = _serializer.read(hexadecimal);
            _data = _serializer.data();
            return _data != '\0' ? stay() : done();
        }
        else
        {
            const std::string_view string = input.type().isEnd() ? END : input.type().isError() ? ERROR::enumNames[input.errorValue()] : EMPTY;
            _data = string[_index];
            if (_data == '\0') return done();
            _index++;
            return stay();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _state(catta::parser::State::start()), _index{0}, _data('\0') {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    Serializer<catta::Hexadecimal<Base>> _serializer;
    catta::parser::State _state;
    std::size_t _index;
    char _data;
};

}  // namespace tostring
}  // namespace catta
