#pragma once

// std
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace catta
{
template <std::size_t SIZE>
/**
 * @brief Class for represening c strings with maximal length. They can be created an handeled at compiletime.
 *
 * Has to have at least one '\0' at the end. Everything after the last '\0' is ignored.
 *
 * @tparam SIZE The maximal length (number of bytes) of the const string (without '\0').
 *
 * @author CattaTech - Maik Urbannek
 */
class ConstString
{
  public:
    /**
     * @return Returs the maximal length of the const string.
     */
    [[nodiscard]] constexpr static std::size_t maxSize() noexcept { return SIZE; }
    /**
     * @return Returs the length of the const string. A const string object on the position size() is always '\0'.
     */
    [[nodiscard]] constexpr std::size_t size() const noexcept { return _size; }
    /**
     * Typedef for the underlying stl array.
     */
    typedef std::array<char, SIZE + 1> Raw;
    /**
     * value_type for stl compatibility.
     */
    using value_type = typename Raw::value_type;
    /**
     * pointer for stl compatibility.
     */
    using pointer = typename Raw::const_pointer;
    /**
     * const_pointer for stl compatibility.
     */
    using const_pointer = typename Raw::const_pointer;
    /**
     * reference for stl compatibility.
     */
    using reference = typename Raw::const_reference;
    /**
     * const_reference for stl compatibility.
     */
    using const_reference = typename Raw::const_reference;
    /**
     * iterator for stl compatibility.
     */
    using iterator = typename Raw::iterator;
    /**
     * const_iterator for stl compatibility.
     */
    using const_iterator = typename Raw::const_iterator;
    /**
     * const_reverse_iterator for stl compatibility.
     */
    using const_reverse_iterator = typename Raw::const_reverse_iterator;
    /**
     * size_type for stl compatibility.
     */
    using size_type = typename Raw::size_type;
    /**
     * difference_type for stl compatibility.
     */
    using difference_type = typename Raw::difference_type;
    /**
     * @return Returns iterator for stl compatibility.
     */
    [[nodiscard]] constexpr auto cbegin() const noexcept { return _data.cbegin(); }
    /**
     * @return Returns iterator for stl compatibility.
     */
    [[nodiscard]] constexpr auto cend() const noexcept { return _data.cbegin() + _size; }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo starts with '\0' and uses whole raw data (but
     */
    [[nodiscard]] constexpr auto crbegin() const noexcept { return _data.crbegin() + static_cast<difference_type>(SIZE - _size + 1); }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo starts with '\0' and uses whole raw data (but
     */
    [[nodiscard]] constexpr auto crend() const noexcept { return _data.crend(); }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo is to long with all '\0'.
     */
    [[nodiscard]] constexpr auto begin() const noexcept { return _data.cbegin(); }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo is to long with all '\0'.
     */
    [[nodiscard]] constexpr auto end() const noexcept { return _data.cbegin() + _size; }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo starts with '\0' and uses whole raw data (but
     */
    [[nodiscard]] constexpr auto rbegin() const noexcept { return _data.crbegin() + static_cast<difference_type>(SIZE - _size + 1); }
    /**
     * @return Returns iterator for stl compatibility.
     * @todo starts with '\0' and uses whole raw data (but
     */
    [[nodiscard]] constexpr auto rend() const noexcept { return _data.crend(); }
    /**
     * Constant to indicate that find() or rfind() have nothing found.
     */
    constexpr static std::size_t npos = std::string_view::npos;
    /**
     * @tparam OTHER The maximal length (number of bytes) of the string to search for (without '\0').
     * @param[in] other The string to search for.
     * @param[in] pos The position in the const string
     * @return Returns the position where the first occurrence of the substring @b other after the position @b pos is if the substring exists,
     * otherwise the constant @b npos.
     */
    template <std::size_t OTHER>
    [[nodiscard]] constexpr std::size_t find(const ConstString<OTHER>& other, const std::size_t pos = 0) const noexcept
    {
        return std::string_view(_data.data()).find(other.data(), pos);
    }
    /**
     * @tparam OTHER The maximal length (number of bytes) of the string to search for (without '\0').
     * @param[in] other The string to search for.
     * @param[in] pos The position in the const string
     * @return Returns the position where the last occurrence of the substring @b other after the position @b pos is if the substring exists,
     * otherwise the constant @b npos.
     */
    template <std::size_t OTHER>
    [[nodiscard]] constexpr std::size_t rfind(const ConstString<OTHER>& other, const std::size_t pos = npos) const noexcept
    {
        return std::string_view(_data.data()).rfind(other.data(), pos);
    }

    /**
     * @return Returns the c string.
     */
    [[nodiscard]] constexpr const char* data() const noexcept { return _data.data(); }
    /**
     * @param[in] index The index of the character. Has to be less than size(), otherwise undefined behavior.
     * @return Returns the character with given index.
     */
    [[nodiscard]] constexpr const_reference operator[](const std::size_t index) const noexcept { return _data[index]; }
    /**
     * @param[in] index The index of the character. Has to be less than size(), otherwise exception.
     * @return Returns the character with given index.
     */
    [[nodiscard]] constexpr const_reference at(const std::size_t index) const { return _data.at(index); }
    /**
     * @param[in] input C string as input. Has to be null terminated. Throws if input is longer than @b SIZE.
     * @return Returns a const string with input as data.
     */
    [[nodiscard]] constexpr static ConstString create(const char* input)
    {
        Raw data = {};
        std::size_t i = 0;
        for (; i < SIZE && input[i] != '\0'; i++) data[i] = input[i];
        if (input[i] != '\0') throw(std::out_of_range("catta::ConstString::create: input to long."));
        return {data, i};
    }
    /**
     * @param[in] input C string as stl array. Has to be null terminated. Throws if input in not null terminated. Everything after the first '\0' is
     * ignored.
     * @return Returns a const string with input as data.
     */
    [[nodiscard]] constexpr static ConstString create(const Raw& input)
    {
        Raw data = {};
        std::size_t i = 0;
        for (; i < SIZE && input[i] != '\0'; i++) data[i] = input[i];
        if (input[i] != '\0') throw(std::out_of_range("catta::ConstString::create: input to long."));
        return {data, i};
    }
    /**
     * Defalut constructor. Returns empty const string.
     */
    [[nodiscard]] constexpr ConstString() noexcept : ConstString(Raw{}, 0) {}
    /**
     * @tparam OTHER The maximal length (number of bytes) of the other string (without '\0').
     * @param[in] other The other const string to add.
     * @return Returns this const string concatenate with the other const string.
     */
    template <std::size_t OTHER>
    [[nodiscard]] constexpr ConstString<SIZE + OTHER> operator+(const ConstString<OTHER>& other) const noexcept
    {
        typename ConstString<SIZE + OTHER>::Raw data = {};
        std::size_t i = 0;
        for (std::size_t j = 0; this->_data[j] != '\0'; j++, i++) data[i] = _data[j];
        for (std::size_t j = 0; other[j] != '\0'; j++, i++) data[i] = other[j];
        return ConstString<SIZE + OTHER>{data, i};
    }
    /**
     * @tparam OTHER The maximal length (number of bytes) of the other string (without '\0').
     * @param[in] other The other const string to compare.
     * @return Returns @b true if the two const strings are the same, otherwise @b false. Improtant are only the characteres until '\0'. This allows
     * two const strings with different maximum length to be the same.
     */
    template <std::size_t OTHER>
    constexpr bool operator==(const ConstString<OTHER>& other) const noexcept
    {
        return std::equal(begin(), begin() + _size, other.begin(), other.begin() + _size);
    }
    /**
     * @tparam OTHER The maximal length (number of bytes) of the other string (without '\0').
     * @param[in] other The other const string to compare.
     * @return Returns @b true if the two const strings are not the same, otherwise @b false. Improtant are only the characteres until '\0'. This
     * allows two const strings with different maximum length to be the same.
     */
    template <std::size_t OTHER>
    constexpr bool operator!=(const ConstString<OTHER>& other) const noexcept
    {
        return !(*this == other);
    }

  private:
    constexpr ConstString(const Raw& data, std::size_t size) : _data(data), _size(size) {}
    Raw _data;
    std::size_t _size;
    template <std::size_t OTHER>
    friend class ConstString;
};

/**
 * @brief This class is @b std::true_type if CLASS is a ConstString (or a reference to ConstString), otherwise @b std::false_type.
 * @tparam CLASS The class that is checked if it is a const string.
 * @author CattaTech - Maik Urbannek
 */
template <class CLASS>
struct isConstString : std::false_type
{
};

template <std::size_t SIZE>
struct isConstString<catta::ConstString<SIZE>> : std::true_type
{
};

template <std::size_t SIZE>
struct isConstString<catta::ConstString<SIZE>&> : std::true_type
{
};

template <std::size_t SIZE>
struct isConstString<const catta::ConstString<SIZE>&> : std::true_type
{
};

/**
 * @brief ConstStringConcept is satisfied if T is a ConstString (or a reference to ConstString).
 * @tparam T The class that is checked if it is a const string.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
concept ConstStringConcept = isConstString<T>::value;

}  // namespace catta
