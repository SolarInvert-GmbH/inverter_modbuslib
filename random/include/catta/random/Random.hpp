#pragma once

// catta
#include <catta/EnumConcept.hpp>

// std
#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <random>
#include <string>

namespace catta
{
namespace random
{
/**
 * @brief The catta::random::Create<T> class creates random objects of differnt types T.
 * @tparam T The class for which random objects are to be created.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Create;

class Random;

/**
 * @brief Randomable is satisfied if there is class Create<T> with a constructor with takes a Random object and can create random T objects with cast
 * operator.
 *
 * Can be used to implment additional random factories for varios types.
 * @tparam T The class for which the Create class should be implemented.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Randomable = requires(catta::random::Random random)
{
    {
        catta::random::Create<T>(random)
        } -> std::convertible_to<T>;
};

/**
 * @brief Class to create pseudo random objects for varios types.
 */
class Random
{
  public:
    /**
     * @param[in] seed The seed for the random factory. For the same seed the same sequence of objects is created. That means for a given seed the
     * calls are deterministic.
     * @return Returns a random factory for creating pseudo random objects.
     */
    static Random create(const std::uint64_t seed) { return Random(seed); }
    /**
     * @return Returns the used seed. For the same seed the same sequence of objects is created. That means for a given seed the calls are
     * deterministic.
     */
    uint64_t seed() const { return _seed; }
    /**
     * @return Returns an pseudo random bool.
     */
    explicit operator bool() { return std::uniform_int_distribution<std::uint8_t>(0, 1)(_random) == 1; }
    /**
     * @return Returns an pseudo random uint8 integer.
     */
    explicit operator std::uint8_t() { return std::uniform_int_distribution<std::uint8_t>(0x00, 0xff)(_random); }
    /**
     * @return Returns an pseudo random uint16 integer.
     */
    explicit operator std::uint16_t() { return std::uniform_int_distribution<std::uint16_t>(0x0000, 0xffff)(_random); }
    /**
     * @return Returns an pseudo random uint32 integer.
     */
    explicit operator std::uint32_t() { return std::uniform_int_distribution<std::uint32_t>(0x00000000, 0xffffffff)(_random); }
    /**
     * @return Returns an pseudo random uint64 integer.
     */
    explicit operator std::uint64_t() { return std::uniform_int_distribution<std::uint64_t>(0x0000000000000000, 0xffffffffffffffff)(_random); }
    /**
     * @return Returns an pseudo random char integer.
     */
    explicit operator char() { return interval(char{' '}, char{'~'}); }
    /**
     * @return Returns an pseudo random char8_t integer.
     */
    explicit operator char8_t() { return interval(char8_t{' '}, char8_t{'~'}); }
    /**
     * @return Returns an pseudo random char16_t integer.
     */
    explicit operator char16_t()
    {
        typedef std::pair<char16_t, char16_t> Pair;
        const auto interval = [this]()
        {
            switch (this->interval(std::uint8_t(0), std::uint8_t(3)))
            {
                case 0:
                    return Pair{0x0001, 0x007E};
                case 1:
                    return Pair{0x0080, 0x07FF};
                case 2:
                    return Pair{0x0800, 0xD7FF};  // 0xD800-0xDFFF is not allowed
                default:
                    return Pair{0xE000, 0xFFFF};
            };
        }();
        return this->interval(interval.first, interval.second);
    }
    /**
     * @return Returns an pseudo random char32_t character.
     */
    explicit operator char32_t()
    {
        typedef std::pair<char32_t, char32_t> Pair;
        const auto interval = [this]()
        {
            switch (this->interval(std::uint8_t(0), std::uint8_t(4)))
            {
                case 0:
                    return Pair{0x00000001, 0x0000007E};
                case 1:
                    return Pair{0x00000080, 0x000007FF};
                case 2:
                    return Pair{0x00000800, 0x0000D7FF};  // 0xD800-0xDFFF is not allowed
                case 3:
                    return Pair{0x0000E000, 0x0000FFFF};
                default:
                    return Pair{0x00010000, 0x0010FFFF};
            };
        }();
        return this->interval(interval.first, interval.second);
    }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random uint8 integer form the interval {min,…,max}.
     */
    std::uint8_t interval(const std::uint8_t min, const std::uint8_t max) { return std::uniform_int_distribution<std::uint8_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random uint16 integer form the interval {min,…,max}.
     */
    std::uint16_t interval(const std::uint16_t min, const std::uint16_t max)
    {
        return std::uniform_int_distribution<std::uint16_t>(min, max)(_random);
    }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random uint32 integer form the interval {min,…,max}.
     */
    std::uint32_t interval(const std::uint32_t min, const std::uint32_t max)
    {
        return std::uniform_int_distribution<std::uint32_t>(min, max)(_random);
    }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random uint64 integer form the interval {min,…,max}.
     */
    std::uint64_t interval(const std::uint64_t min, const std::uint64_t max)
    {
        return std::uniform_int_distribution<std::uint64_t>(min, max)(_random);
    }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random int8 integer form the interval {min,…,max}.
     */
    std::int8_t interval(const std::int8_t min, const std::int8_t max) { return std::uniform_int_distribution<std::int8_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random int16 integer form the interval {min,…,max}.
     */
    std::int16_t interval(const std::int16_t min, const std::int16_t max) { return std::uniform_int_distribution<std::int16_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random int32 integer form the interval {min,…,max}.
     */
    std::int32_t interval(const std::int32_t min, const std::int32_t max) { return std::uniform_int_distribution<std::int32_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible integer.
     * @param[in] max The biggest possible integer.
     * @return Returns a random int64 integer form the interval {min,…,max}.
     */
    std::int64_t interval(const std::int64_t min, const std::int64_t max) { return std::uniform_int_distribution<std::int64_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible double.
     * @param[in] max The biggest possible double.
     * @return Returns a random double form the interval [min,…,max].
     */
    double interval(const double min, const double max) { return std::uniform_real_distribution<double>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible float.
     * @param[in] max The biggest possible float.
     * @return Returns a random float form the interval [min,…,max].
     */
    float interval(const float min, const float max) { return std::uniform_real_distribution<float>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible char.
     * @param[in] max The biggest possible char.
     * @return Returns a random char form the interval [min,…,max].
     */
    char interval(const char min, const char max) { return std::uniform_int_distribution<char>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible char8_t.
     * @param[in] max The biggest possible char8_t.
     * @return Returns a random char8_t form the interval [min,…,max].
     */
    char8_t interval(const char8_t min, const char8_t max) { return std::uniform_int_distribution<char8_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible char16_t.
     * @param[in] max The biggest possible char16_t.
     * @return Returns a random char16_t form the interval [min,…,max].
     */
    char16_t interval(const char16_t min, const char16_t max) { return std::uniform_int_distribution<char16_t>(min, max)(_random); }
    /**
     * @param[in] min The smalles possible char32_t.
     * @param[in] max The biggest possible char32_t.
     * @return Returns a random char32_t form the interval [min,…,max].
     */
    char32_t interval(const char32_t min, const char32_t max) { return std::uniform_int_distribution<char32_t>(min, max)(_random); }
    /**
     * @return Returns a random printable ascii character(none control asciis).
     */
    char ascii() { return interval(' ', '~'); }
    /**
     * @return Returns a random numeric character ('0'…'9').
     */
    char numeric() { return interval('0', '9'); }
    /**
     * @return Returns a random alpha character ('a'…'z','A'…'Z').
     */
    char alpha() { return alphanumericBase(ALPHANUMERIC_a, ALPHANUMERIC_Z); }
    /**
     * @return Returns a random alpha numeric character ('a'…'z','A'…'Z','0'…'9').
     */
    char alphaNumeric() { return alphanumericBase(ALPHANUMERIC_a, ALPHANUMERIC_9); }
    /**
     * @param[in] word Posible characters. Has to have at least one character.
     * @param[in] size The length of the output string.
     * @return Returns a random string created form the characters of the input word.
     */
    std::string fromWord(const std::string& word, const std::size_t size)
    {
        std::string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += word[interval(std::uint32_t(0), std::uint32_t(word.size() - 1))];
        return tmp;
    }
    /**
     * @param[in] size The length of the output string.
     * @return Returns a random u8string with with all possible character (0x00…0xff).
     */
    std::u8string u8string(const std::size_t size)
    {
        std::u8string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += std::uint8_t(*this);
        return tmp;
    }
    /**
     * @param[in] size The length of the output string.
     * @return Returns a random string with with all possible ascii character.
     */
    std::string string(const std::size_t size)
    {
        std::string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += ascii();
        return tmp;
    }
    /**
     * @param[in] size The length of the output string.
     * @return Returns a random string with with all possible alphanumeric character.
     */
    std::string alphaNumericString(const std::size_t size)
    {
        std::string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += alphaNumeric();
        return tmp;
    }
    /**
     * @param[in] size The length of the output string.
     * @return Returns a random string with with all possible alphanumeric character.
     */
    std::u32string alphaNumericU32string(const std::size_t size)
    {
        std::u32string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += static_cast<char32_t>(alphaNumeric());
        return tmp;
    }
    /**
     * @param[in] size The length of the output string.
     * @return Returns a random string with with all possible ascii character.
     */
    std::u32string u32string(const std::size_t size)
    {
        std::u32string tmp;
        for (std::size_t i = 0; i < size; i++) tmp += static_cast<char32_t>(ascii());
        return tmp;
    }
    /**
     * @param[in,out] begin Begin of the to shuffle part.
     * @param[in,out] end End of the to shuffle part.
     * Shuffles all elements between begin and end of the same range.
     */
    void shuffle(auto begin, auto end) { std::shuffle(begin, end, _random); }
    /**
     * @param[in,out] container The to shuffle container/range.
     * Shuffles all elements in the range.
     */
    void shuffle(auto& container) { std::shuffle(container.begin(), container.end(), _random); }
    /**
     * @tparam T Type that can be create randomly.
     * @param size Number of elements of the return vector.
     * @return Returns a vector of random elements of type T.
     */
    template <Randomable T>
    std::vector<T> vector(const std::size_t size)
    {
        std::vector<T> tmp;
        for (std::size_t i = 0; i < size; i++) tmp.push_back(create<T>());
        return tmp;
    }
    /**
     * @tparam T A class which implements the Randomable interface.
     * @return Returns a pseudo random object form the type T. Can be added for all data classes by implementing the Randomable interface.
     */
    template <Randomable T>
    T create()
    {
        return static_cast<T>(Create<T>(*this));
    }

  private:
    Random(const uint64_t seed) : _seed(seed), _random(seed) {}
    uint64_t _seed;
    std::mt19937_64 _random;
    static constexpr std::size_t ALPHANUMERIC_a = 0;
    static constexpr std::size_t ALPHANUMERIC_Z = 26 + 26 - 1;
    static constexpr std::size_t ALPHANUMERIC_0 = ALPHANUMERIC_Z + 1;
    static constexpr std::size_t ALPHANUMERIC_9 = ALPHANUMERIC_0 + 9;
    char alphanumericBase(const std::size_t begin, const std::size_t end)
    {
        static constexpr std::array<char, 26 + 26 + 10> possible = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                                                                    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
                                                                    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                                                    'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        return possible[interval(std::uint32_t(begin), std::uint32_t(end))];
    }
};

template <>
class Create<bool>
{
  public:
    Create(Random& random) : _value(static_cast<bool>(random)) {}
    operator bool() const { return _value; }

  private:
    bool _value;
};

template <std::unsigned_integral INTEGRAL>
class Create<INTEGRAL>
{
  public:
    Create(Random& random) : _value(static_cast<INTEGRAL>(random)) {}
    operator INTEGRAL() const { return _value; }

  private:
    INTEGRAL _value;
};

template <std::signed_integral INTEGRAL>
class Create<INTEGRAL>
{
  public:
    Create(Random& random) : _value(static_cast<INTEGRAL>(static_cast<typename std::make_unsigned<INTEGRAL>::type>(random))) {}
    operator INTEGRAL() const { return _value; }

  private:
    INTEGRAL _value;
};

template <catta::EnumConcept T>
class Create<T>
{
  public:
    Create(Random& random) : _value(T(random.interval(std::uint8_t(0), std::uint8_t(T::empty() - 1)))) {}
    operator T() const { return _value; }

  private:
    T _value;
};

template <>
class Create<char8_t>
{
  public:
    Create(Random& random) : _value(char8_t(random)) {}
    operator char8_t() const { return _value; }

  private:
    char8_t _value;
};

template <>
class Create<char16_t>
{
  public:
    Create(Random& random) : _value(char16_t(random)) {}
    operator char16_t() const { return _value; }

  private:
    char16_t _value;
};

template <>
class Create<char32_t>
{
  public:
    Create(Random& random) : _value(char32_t(random)) {}
    operator char32_t() const { return _value; }

  private:
    char32_t _value;
};

}  // namespace random
}  // namespace catta
