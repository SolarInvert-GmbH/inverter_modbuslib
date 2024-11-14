#pragma once

// std
#include <array>

namespace catta
{
namespace modbus
{
namespace sunspec
{
/**
 * @brief Class for represening strings with lenght 20.
 *
 * @author CattaTech - Maik Urbannek
 */
class String
{
  public:
    /**
     * Max lenght of string
     */
    static constexpr std::size_t size = 20;
    /**
     * The base type to hold character data.
     */
    using Raw = std::array<char, size + 1>;
    /**
     * Default constructor. Creates empty string.
     */
    constexpr String() noexcept : String(Raw{}) {}
    /**
     * @return Returns empty string.
     */
    constexpr static String empty() noexcept { return String{}; }
    /**
     *  @return Returns @b true if string is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _data[0] == '\0'; }
    /**
     * @param[in] factorExponent Represening the exponent of the scaling factor. Has to be beetween -10 and 10, otherwise empty is returned.
     */
    static constexpr String create(const char* string)
    {
        Raw raw = Raw{};
        for (std::size_t i = 0; i <= size; i++)
        {
            raw[i] = string[i];
            if (string[i] == '\0') return String(raw);
        }
        return empty();
    }
    /**
     * @return Returns the data. Is only valid if not empty.
     */
    const Raw& data() const noexcept { return _data; }
    /**
     * @param[in] other The other String.
     * @return Returns @b true if the two String objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const String& other) const noexcept = default;

  private:
    constexpr String(const Raw& data) : _data(data) {}
    std::array<char, size + 1> _data;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
