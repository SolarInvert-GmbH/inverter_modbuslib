#pragma once

// catta
#include <catta/ConstString.hpp>
#include <catta/EnumConcept.hpp>

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// std
#include <concepts>

namespace catta
{
namespace fromstring
{
/**
 * @brief The catta::fromstring::Parser<T> class creates objects from type T by parsing strings.
 * @tparam T The class wich is parsed from string.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Parser;

/**
 * @brief Parsable is satisfied if there is class catta::fromstring::Parser<T> with a read and a data methode.
 *
 * Can be used to implment additional parsers for varios types.
 * @see If T is catta::fromstring::Parsable and catta::tostring::ToConstStringable or catta::tostring::ToStdStringable satisfied, they should use the
 * same string reprentattion, so you can parse the strings taht where created.
 * @tparam T The class wich is parsed from string.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Parsable = catta::parser::ObjectParserConcept<catta::fromstring::Parser<T>> && std::same_as < typename catta::fromstring::Parser<T>::Input,
char > &&std::same_as<typename catta::fromstring::Parser<T>::Output, T>;

/**
 * @tparam T A class which implements the Parsable interface.
 * @param[in] input C string (for compile time handling).
 * @return Returns the object from type T that is represented by input string if the string is a valid representation of an T object, otherwiese
 * implementation dependent.
 */
template <Parsable T>
[[nodiscard]] constexpr T fromString(const char* input) noexcept
{
    Parser<T> parser;
    while (true)
    {
        const auto [error, inputHandled] = parser.read(*input);
        if (!error.isEmpty()) return T{};
        if (parser.state().isDone()) return *input == '\0' ? parser.data() : T{};
        if (inputHandled) input++;
    }
}

template <catta::EnumConcept T>
class Parser<T>
{
  public:
    typedef T Output;
    typedef char Input;
    typedef catta::state::DefaultError Error;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        bool failed = true;
        const auto handle = [this, input, &failed](const std::string_view s, bool& possible, const T value)
        {
            if (possible)
            {
                if (_index < s.size() && input == s[_index])
                    failed = false;
                else if (_index == s.size() && !isValidEnumCharacter(input))
                {
                    _value = value;
                    _state = catta::parser::State::done();
                    return true;
                }
                else
                    possible = false;
            }
            return false;
        };
        for (uint8_t i = 0; i < T{}; i++)
            if (handle(T::enumNames[i], _possible[i], T{i})) return Tuple{Error{}, catta::parser::InputHandled::no()};
        if (handle(empty, _possible[T{}], T{})) return Tuple{Error{}, catta::parser::InputHandled::no()};
        _index++;
        _state = failed ? catta::parser::State::failed() : catta::parser::State::running();
        return Tuple{failed ? Error::error() : Error{}, catta::parser::InputHandled::yes()};
    }
    [[nodiscard]] constexpr T data() const noexcept { return _value; }
    [[nodiscard]] constexpr Parser() noexcept : _index(0), _state(catta::parser::State::start())
    {
        for (bool& b : _possible) b = true;
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    std::array<bool, T::empty() + 1> _possible;
    size_t _index;
    T _value;
    catta::parser::State _state;
    constexpr static std::string_view empty = "EMPTY";
};

}  // namespace fromstring
}  // namespace catta
