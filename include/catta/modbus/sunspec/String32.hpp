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
 * @brief Class for representing strings with lenght 32.
 *
 * @author CattaTech - Maik Urbannek
 */
class String32
{
  public:
    /**
     * Max lenght of string
     */
    static constexpr std::size_t size = 32;
    /**
     * The base type to hold character data.
     */
    using Raw = std::array<char, size + 1>;
    /**
     * Default constructor. Creates empty string.
     */
    constexpr String32() noexcept : String32(Raw{}) {}
    /**
     * @return Returns empty string.
     */
    constexpr static String32 empty() noexcept { return String32{}; }
    /**
     *  @return Returns @b true if string is empty, otherwise @b false.
     */
    constexpr bool isEmpty() const noexcept { return _data[0] == '\0'; }
    /**
     * @param[in] string Representing the string. Has not longer than 32 character, otherwise empty is returned.
     * @return Returns string if input is valid, otherwise empty.
     */
    static constexpr String32 create(const char* string)
    {
        Raw raw = Raw{};
        for (std::size_t i = 0; i <= size; i++)
        {
            raw[i] = string[i];
            if (string[i] == '\0') return String32(raw);
        }
        return empty();
    }
    /**
     * @return Returns the data. Is only valid if not empty.
     */
    constexpr const Raw& data() const noexcept { return _data; }
    /**
     * @param[in] other The other String32.
     * @return Returns @b true if the two String32 objects are the same, otherwise @b false.
     */
    constexpr bool operator==(const String32& other) const noexcept = default;

  private:
    constexpr String32(const Raw& data) : _data(data) {}
    std::array<char, size + 1> _data;
};
}  // namespace sunspec
}  // namespace modbus
}  // namespace catta
