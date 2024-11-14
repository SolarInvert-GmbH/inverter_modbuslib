#pragma once

// std
#include <array>
#include <concepts>
#include <cstdint>
#include <string_view>

namespace catta
{
/**
 * @brief EnumConcept describes all catta enum types that have ordered enums from zero to empty()-1.
 * @tparam T The class that is checked if it is an catta enum.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept EnumConcept = requires(const T& t0, const T& t1)
{
    {
        t0 == t1
        } -> std::same_as<bool>;
    {
        t0 != t1
        } -> std::same_as<bool>;
    {
        static_cast<std::uint8_t>(t0)
        } -> std::same_as<std::uint8_t>;
    {
        T::empty()
        } -> std::same_as<T>;
    {
        t0.isEmpty()
        } -> std::same_as<bool>;
    std::same_as<decltype(T::enumNames), std::array<std::string_view, T::empty()>>;
};

/**
 * @brief A helper class to iterate over all none empty enums of T.
 * @tparam T The enum type.
 * @author CattaTech - Maik Urbannek
 */
template <catta::EnumConcept T>
class EnumVisiter
{
  public:
    /**
     * @brief Iterator class for stl compatibility.
     * @author CattaTech - Maik Urbannek
     */
    class Iterator
    {
      public:
        /**
         * iterator_category for stl compatibility.
         */
        using iterator_category = std::input_iterator_tag;
        /**
         * difference_type for stl compatibility.
         */
        using difference_type = std::ptrdiff_t;
        /**
         * value_type for stl compatibility.
         */
        using value_type = T;
        /**
         * pointer for stl compatibility.
         */
        using pointer = void;
        /**
         * reference for stl compatibility.
         */
        using reference = const T&;
        /**
         * @return Returns the enum object as reference.
         */
        constexpr reference operator*() const noexcept { return _raw; }
        /**
         * Post iterator.
         * @return Returns the incremented iterator.
         */
        constexpr Iterator& operator++() noexcept
        {
            _raw = T(std::uint8_t(_raw) + 1);
            return *this;
        }
        /**
         * Pre iterator.
         * @return Returns the old iterator.
         */
        constexpr Iterator operator++(int) noexcept
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        /**
         * @param[in] other The other Iterator.
         * @return Returns @b true if the two Iterator objects are the same, otherwise @b false.
         */
        constexpr bool operator==(const Iterator& other) const noexcept { return this->_raw == other._raw; }
        /**
         * @param[in] other The other Iterator.
         * @return Returns @b true if the two Iterator objects are not the same, otherwise @b false.
         */
        constexpr bool operator!=(const Iterator& other) const noexcept { return !(*this == other); }
        /**
         * Copyconstructor.
         * @param[in] other To copy iterator.
         */
        constexpr Iterator(const Iterator& other) : _raw(other._raw) {}
        /**
         * Default constructor.
         */
        constexpr Iterator() : _raw(T::empty()) {}

      private:
        constexpr Iterator(const std::uint8_t raw) : _raw(T{raw}) {}
        T _raw;
        friend class EnumVisiter;
    };
    /**
     * const_iterator for stl compatibility.
     */
    typedef Iterator const_iterator;
    /**
     * @return Returns iterator for stl compatibility.
     */
    constexpr const_iterator begin() const { return 0; }
    /**
     * @return Returns iterator for stl compatibility.
     */
    constexpr const_iterator end() const { return std::uint8_t(T::empty()); }
    /**
     * @return Returns iterator for stl compatibility.
     */
    constexpr const_iterator cbegin() const { return begin(); }
    /**
     * @return Returns iterator for stl compatibility.
     */
    constexpr const_iterator cend() const { return end(); }
    /**
     * Default constructor.
     */
    constexpr EnumVisiter() = default;

  private:
};

/**
 * @tparam T The enum type.
 * Variable for iterating over catta enums.
 */
template <catta::EnumConcept T>
constexpr static EnumVisiter<T> enumVisiter = EnumVisiter<T>();

/**
 * @param[in] c Input character.
 * @return Returns @b true if the input character is an valid enum character (alphanumeric with underscore)
 */
constexpr bool isValidEnumCharacter(const char c) { return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'; }
}  // namespace catta
