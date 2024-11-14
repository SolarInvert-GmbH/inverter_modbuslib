#pragma once

// catta
#include <catta/ConstString.hpp>
#include <catta/EnumConcept.hpp>

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// std
#include <algorithm>
#include <array>
#include <concepts>
#include <string>
#include <string_view>

namespace catta
{
namespace tostring
{
/**
 * @brief The catta::tostring::Serializer<T> class creates charcter streams from objects from type T by serializing the objects.
 * @tparam T The class which is serialized to string.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Serializer;

/**
 * @brief Serializable is satisfied if there is class catta::tostring::Serializer<T> with a read and a data methode.
 *
 * Can be used to implment additional serializer for varios types.
 * @see If T has catta::fromstring::Parsable and catta::tostring::Serializable satisfied, they should use the same string representation, so you can
 * parse the strings that where created.
 * @tparam T The class which is serialized to string.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Serializable =
    catta::parser::ObjectParserConcept<catta::tostring::Serializer<T>> && std::same_as<typename catta::tostring::Serializer<T>::Input, T> &&
    std::same_as < typename catta::tostring::Serializer<T>::Output,
char > ;

/**
 * @tparam T A class which implements the Serializable interface.
 * @param[in] input Input object to parse.
 * @return Returns the object from type T that is represented by input string if the string is a valid representation of an T object, otherwiese
 * implementation dependent.
 */
template <Serializable T>
[[nodiscard]] std::string toString(const T& input) noexcept
{
    Serializer<T> serializer;
    std::string s;
    while (true)
    {
        const auto [error, inputHandled] = serializer.read(input);
        if (!error.isEmpty()) return std::string();
        const char data = serializer.data();
        if (data == '\0') return s;
        s += data;
    }
}

/**
 * @tparam T A class which implements the Serializable interface.
 * @param[in] input Input object to serialize.
 * @return Returns the lenght of the output string.
 */
template <Serializable T>
[[nodiscard]] constexpr std::size_t getLength(const T& input) noexcept
{
    Serializer<T> serializer;
    std::size_t length = 0;
    while (true)
    {
        const auto [error, inputHandled] = serializer.read(input);
        if (!error.isEmpty()) return 0;
        const char data = serializer.data();
        if (data == '\0') return length;
        length++;
    }
}

/**
 * @tparam T A class which implements the Serializable interface.
 * @tparam L The length of the output string. Use @see getLength().
 * @param[in] input Input object to serialize.
 * @return Returns the string (as character array) that holds string representation of the input. Returns empty string if serialize failed.
 * @warning Dont checks for buffer overflow. The given L length has to big enough to hold the output. Use @see getLength().
 */
template <Serializable T, std::size_t L>
[[nodiscard]] constexpr std::array<char, L + 1> toStaticString(const T& input) noexcept
{
    Serializer<T> serializer;
    std::size_t index = 0;
    std::array<char, L + 1> array;
    while (true)
    {
        const auto [error, inputHandled] = serializer.read(input);
        if (!error.isEmpty()) return std::array<char, L + 1>{};
        const char data = serializer.data();
        array[index] = data;
        if (data == '\0') return array;
        index++;
    }
}

template <catta::EnumConcept T>
class Serializer<T>
{
  public:
    using Input = T;
    using Output = char;
    using Error = catta::state::DefaultError;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const std::string_view name = std::uint8_t(input) < std::uint8_t(T::empty()) ? T::enumNames[input] : empty;

        if (_index <= name.size())
        {
            const size_t index = _index;
            _value = name[index];
            _index++;
            if (_index < name.size())
            {
                _state = catta::parser::State::running();
                return Tuple{Error::empty(), catta::parser::InputHandled::no()};
            }
            else
            {
                _state = catta::parser::State::done();
                return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
            }
        }
        else
        {
            _value = '\0';
            _state = catta::parser::State::failed();
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        }
    }
    [[nodiscard]] constexpr char data() const noexcept { return _value; }
    [[nodiscard]] constexpr Serializer() noexcept : _index(0), _state(catta::parser::State::start()) {}
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    size_t _index;
    char _value;
    catta::parser::State _state;
    constexpr static std::string_view empty = "EMPTY";
};

/**
 * @brief The catta::tostring::GetName<T> class holds the name of the class/type in name as std::string_view. @see Nameable.
 * @tparam T The class to get name.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class GetName;

/**
 * @brief Nameable is satisfied if there is class catta::tostring::GetName<T> with a std::string_view member name has the name oft the class as value.
 * @tparam T The class which has a name.
 */
template <typename T>
concept Nameable = requires()
{
    std::same_as<decltype(catta::tostring::GetName<T>::name), std::string_view>;
};

/**
 * @brief ToStringable is satisfied if there is a function catta::tostring::toString(const T&t) which returns a standard string.
 *
 * Can be used to implment additional string creation for types.
 * @tparam T The class which string is created from.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept ToStringable = requires(const T& t)
{
    {
        catta::tostring::toString(t)
        } -> std::same_as<std::string>;
};

template <>
class GetName<std::uint8_t>
{
  public:
    constexpr static std::string_view name = "uint8_t";
};
template <>
class GetName<std::uint16_t>
{
  public:
    constexpr static std::string_view name = "uint16_t";
};
template <>
class GetName<std::uint32_t>
{
  public:
    constexpr static std::string_view name = "uint32_t";
};
template <>
class GetName<std::uint64_t>
{
  public:
    constexpr static std::string_view name = "uint64_t";
};
template <>
class GetName<std::int8_t>
{
  public:
    constexpr static std::string_view name = "int8_t";
};
template <>
class GetName<std::int16_t>
{
  public:
    constexpr static std::string_view name = "int16_t";
};
template <>
class GetName<std::int32_t>
{
  public:
    constexpr static std::string_view name = "int32_t";
};
template <>
class GetName<std::int64_t>
{
  public:
    constexpr static std::string_view name = "int64_t";
};
template <>
class GetName<float>
{
  public:
    constexpr static std::string_view name = "float";
};
template <>
class GetName<double>
{
  public:
    constexpr static std::string_view name = "double";
};
template <>
class GetName<char>
{
  public:
    constexpr static std::string_view name = "char";
};
template <>
class GetName<char8_t>
{
  public:
    constexpr static std::string_view name = "char8_t";
};
template <>
class GetName<char16_t>
{
  public:
    constexpr static std::string_view name = "char16_t";
};
template <>
class GetName<char32_t>
{
  public:
    constexpr static std::string_view name = "char32_t";
};

/**
 * @tparam T The class to create the name.
 * @return Returns the name of the class.
 */
template <Nameable T>
constexpr auto getNameAsConstString()
{
    return catta::ConstString<GetName<T>::name.size()>::create(GetName<T>::name.data());
}

}  // namespace tostring
}  // namespace catta
