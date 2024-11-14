#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace hardware
{
namespace uart
{
/**
 * @brief Bitrate represents the speed of the uart communication. The two uart devices have to have the same baudrate.
 * @author CattaTech - Maik Urbannek
 */
class Baudrate
{
  private:
    constexpr static std::uint8_t BAUDRATE_50 = 0;
    constexpr static std::uint8_t BAUDRATE_75 = 1;
    constexpr static std::uint8_t BAUDRATE_110 = 2;
    constexpr static std::uint8_t BAUDRATE_134 = 3;
    constexpr static std::uint8_t BAUDRATE_150 = 4;
    constexpr static std::uint8_t BAUDRATE_200 = 5;
    constexpr static std::uint8_t BAUDRATE_300 = 6;
    constexpr static std::uint8_t BAUDRATE_600 = 7;
    constexpr static std::uint8_t BAUDRATE_1200 = 8;
    constexpr static std::uint8_t BAUDRATE_1800 = 9;
    constexpr static std::uint8_t BAUDRATE_2400 = 10;
    constexpr static std::uint8_t BAUDRATE_4800 = 11;
    constexpr static std::uint8_t BAUDRATE_9600 = 12;
    constexpr static std::uint8_t BAUDRATE_19200 = 13;
    constexpr static std::uint8_t BAUDRATE_38400 = 14;
    constexpr static std::uint8_t BAUDRATE_57600 = 15;
    constexpr static std::uint8_t BAUDRATE_115200 = 16;
    constexpr static std::uint8_t BAUDRATE_230400 = 17;
    constexpr static std::uint8_t BAUDRATE_460800 = 18;
    constexpr static std::uint8_t BAUDRATE_500000 = 19;
    constexpr static std::uint8_t BAUDRATE_576000 = 20;
    constexpr static std::uint8_t BAUDRATE_921600 = 21;
    constexpr static std::uint8_t BAUDRATE_1000000 = 22;
    constexpr static std::uint8_t BAUDRATE_1152000 = 23;
    constexpr static std::uint8_t BAUDRATE_1500000 = 24;
    constexpr static std::uint8_t BAUDRATE_2000000 = 25;
    constexpr static std::uint8_t BAUDRATE_2500000 = 26;
    constexpr static std::uint8_t BAUDRATE_3000000 = 27;
    constexpr static std::uint8_t BAUDRATE_3500000 = 28;
    constexpr static std::uint8_t BAUDRATE_4000000 = 29;
    constexpr static std::uint8_t EMPTY = 30;

  public:
    /**
     * @param[in] value The enum value of the baudrate.
     * @warning This constructor should not be used. Use baudrate50(), baudrate75(), baudrate110(), baudrate134(), baudrate150(), baudrate200(),
     * baudrate300(), baudrate600(), baudrate1200(), baudrate1800(), baudrate2400(), baudrate4800(), baudrate9600(), baudrate19200(), baudrate38400(),
     * baudrate57600(), baudrate115200(), baudrate230400(), baudrate460800(), baudrate500000(), baudrate576000(), baudrate921600(), baudrate1000000(),
     * baudrate1152000(), baudrate1500000(), baudrate2000000(), baudrate2500000(), baudrate3000000(), baudrate3500000(), baudrate4000000() or empty().
     * Explicit constructor. Converts uint8 to baudrate.
     */
    [[nodiscard]] constexpr explicit Baudrate(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty baudrate.
     */
    [[nodiscard]] constexpr Baudrate() noexcept : Baudrate(EMPTY) {}
    /**
     * @return Returns the 50 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate50() noexcept { return Baudrate{BAUDRATE_50}; }
    /**
     * @return Returns the 75 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate75() noexcept { return Baudrate{BAUDRATE_75}; }
    /**
     * @return Returns the 110 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate110() noexcept { return Baudrate{BAUDRATE_110}; }
    /**
     * @return Returns the 134 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate134() noexcept { return Baudrate{BAUDRATE_134}; }
    /**
     * @return Returns the 150 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate150() noexcept { return Baudrate{BAUDRATE_150}; }
    /**
     * @return Returns the 200 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate200() noexcept { return Baudrate{BAUDRATE_200}; }
    /**
     * @return Returns the 300 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate300() noexcept { return Baudrate{BAUDRATE_300}; }
    /**
     * @return Returns the 600 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate600() noexcept { return Baudrate{BAUDRATE_600}; }
    /**
     * @return Returns the 1200 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate1200() noexcept { return Baudrate{BAUDRATE_1200}; }
    /**
     * @return Returns the 1800 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate1800() noexcept { return Baudrate{BAUDRATE_1800}; }
    /**
     * @return Returns the 2400 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate2400() noexcept { return Baudrate{BAUDRATE_2400}; }
    /**
     * @return Returns the 4800 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate4800() noexcept { return Baudrate{BAUDRATE_4800}; }
    /**
     * @return Returns the 9600 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate9600() noexcept { return Baudrate{BAUDRATE_9600}; }
    /**
     * @return Returns the 19200 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate19200() noexcept { return Baudrate{BAUDRATE_19200}; }
    /**
     * @return Returns the 38400 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate38400() noexcept { return Baudrate{BAUDRATE_38400}; }
    /**
     * @return Returns the 57600 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate57600() noexcept { return Baudrate{BAUDRATE_57600}; }
    /**
     * @return Returns the 115200 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate115200() noexcept { return Baudrate{BAUDRATE_115200}; }
    /**
     * @return Returns the 230400 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate230400() noexcept { return Baudrate{BAUDRATE_230400}; }
    /**
     * @return Returns the 460800 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate460800() noexcept { return Baudrate{BAUDRATE_460800}; }
    /**
     * @return Returns the 500000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate500000() noexcept { return Baudrate{BAUDRATE_500000}; }
    /**
     * @return Returns the 576000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate576000() noexcept { return Baudrate{BAUDRATE_576000}; }
    /**
     * @return Returns the 921600 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate921600() noexcept { return Baudrate{BAUDRATE_921600}; }
    /**
     * @return Returns the 1000000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate1000000() noexcept { return Baudrate{BAUDRATE_1000000}; }
    /**
     * @return Returns the 1152000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate1152000() noexcept { return Baudrate{BAUDRATE_1152000}; }
    /**
     * @return Returns the 1500000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate1500000() noexcept { return Baudrate{BAUDRATE_1500000}; }
    /**
     * @return Returns the 2000000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate2000000() noexcept { return Baudrate{BAUDRATE_2000000}; }
    /**
     * @return Returns the 2500000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate2500000() noexcept { return Baudrate{BAUDRATE_2500000}; }
    /**
     * @return Returns the 3000000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate3000000() noexcept { return Baudrate{BAUDRATE_3000000}; }
    /**
     * @return Returns the 3500000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate3500000() noexcept { return Baudrate{BAUDRATE_3500000}; }
    /**
     * @return Returns the 4000000 character baudrate.
     */
    [[nodiscard]] constexpr static Baudrate baudrate4000000() noexcept { return Baudrate{BAUDRATE_4000000}; }
    /**
     * @return Returns the empty baudrate.
     */
    [[nodiscard]] constexpr static Baudrate empty() noexcept { return Baudrate{EMPTY}; }
    /**
     * @param[in] other The other Baudrate.
     * @return Returns @b true if the two Baudrate objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Baudrate& other) const = default;
    /**
     * @return Returns baudrate as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if 50 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate50() const noexcept { return _value == BAUDRATE_50; }
    /**
     * @return Returns @b true if 75 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate75() const noexcept { return _value == BAUDRATE_75; }
    /**
     * @return Returns @b true if 110 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate110() const noexcept { return _value == BAUDRATE_110; }
    /**
     * @return Returns @b true if 134 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate134() const noexcept { return _value == BAUDRATE_134; }
    /**
     * @return Returns @b true if 150 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate150() const noexcept { return _value == BAUDRATE_150; }
    /**
     * @return Returns @b true if 200 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate200() const noexcept { return _value == BAUDRATE_200; }
    /**
     * @return Returns @b true if 300 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate300() const noexcept { return _value == BAUDRATE_300; }
    /**
     * @return Returns @b true if 600 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate600() const noexcept { return _value == BAUDRATE_600; }
    /**
     * @return Returns @b true if 1200 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate1200() const noexcept { return _value == BAUDRATE_1200; }
    /**
     * @return Returns @b true if 1800 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate1800() const noexcept { return _value == BAUDRATE_1800; }
    /**
     * @return Returns @b true if 2400 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate2400() const noexcept { return _value == BAUDRATE_2400; }
    /**
     * @return Returns @b true if 4800 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate4800() const noexcept { return _value == BAUDRATE_4800; }
    /**
     * @return Returns @b true if 9600 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate9600() const noexcept { return _value == BAUDRATE_9600; }
    /**
     * @return Returns @b true if 19200 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate19200() const noexcept { return _value == BAUDRATE_19200; }
    /**
     * @return Returns @b true if 38400 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate38400() const noexcept { return _value == BAUDRATE_38400; }
    /**
     * @return Returns @b true if 57600 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate57600() const noexcept { return _value == BAUDRATE_57600; }
    /**
     * @return Returns @b true if 115200 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate115200() const noexcept { return _value == BAUDRATE_115200; }
    /**
     * @return Returns @b true if 230400 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate230400() const noexcept { return _value == BAUDRATE_230400; }
    /**
     * @return Returns @b true if 460800 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate460800() const noexcept { return _value == BAUDRATE_460800; }
    /**
     * @return Returns @b true if 500000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate500000() const noexcept { return _value == BAUDRATE_500000; }
    /**
     * @return Returns @b true if 576000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate576000() const noexcept { return _value == BAUDRATE_576000; }
    /**
     * @return Returns @b true if 921600 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate921600() const noexcept { return _value == BAUDRATE_921600; }
    /**
     * @return Returns @b true if 1000000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate1000000() const noexcept { return _value == BAUDRATE_1000000; }
    /**
     * @return Returns @b true if 1152000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate1152000() const noexcept { return _value == BAUDRATE_1152000; }
    /**
     * @return Returns @b true if 1500000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate1500000() const noexcept { return _value == BAUDRATE_1500000; }
    /**
     * @return Returns @b true if 2000000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate2000000() const noexcept { return _value == BAUDRATE_2000000; }
    /**
     * @return Returns @b true if 2500000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate2500000() const noexcept { return _value == BAUDRATE_2500000; }
    /**
     * @return Returns @b true if 3000000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate3000000() const noexcept { return _value == BAUDRATE_3000000; }
    /**
     * @return Returns @b true if 3500000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate3500000() const noexcept { return _value == BAUDRATE_3500000; }
    /**
     * @return Returns @b true if 4000000 character baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isBaudrate4000000() const noexcept { return _value == BAUDRATE_4000000; }
    /**
     * @return Returns @b true if empty baudrate is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Baudrate in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {
        "BAUDRATE_50",      "BAUDRATE_75",      "BAUDRATE_110",     "BAUDRATE_134",     "BAUDRATE_150",     "BAUDRATE_200",
        "BAUDRATE_300",     "BAUDRATE_600",     "BAUDRATE_1200",    "BAUDRATE_1800",    "BAUDRATE_2400",    "BAUDRATE_4800",
        "BAUDRATE_9600",    "BAUDRATE_19200",   "BAUDRATE_38400",   "BAUDRATE_57600",   "BAUDRATE_115200",  "BAUDRATE_230400",
        "BAUDRATE_460800",  "BAUDRATE_500000",  "BAUDRATE_576000",  "BAUDRATE_921600",  "BAUDRATE_1000000", "BAUDRATE_1152000",
        "BAUDRATE_1500000", "BAUDRATE_2000000", "BAUDRATE_2500000", "BAUDRATE_3000000", "BAUDRATE_3500000", "BAUDRATE_4000000"};
    /**
     * @return Returns the BAUDRATE as integer value. Is needed for many uart implementations.
     */
    constexpr std::uint32_t asInteger() const noexcept
    {
        switch (_value)
        {
            case BAUDRATE_50:
                return 50;
            case BAUDRATE_75:
                return 75;
            case BAUDRATE_110:
                return 110;
            case BAUDRATE_134:
                return 134;
            case BAUDRATE_150:
                return 150;
            case BAUDRATE_200:
                return 200;
            case BAUDRATE_300:
                return 300;
            case BAUDRATE_600:
                return 600;
            case BAUDRATE_1200:
                return 1200;
            case BAUDRATE_1800:
                return 1800;
            case BAUDRATE_2400:
                return 2400;
            case BAUDRATE_4800:
                return 4800;
            case BAUDRATE_9600:
                return 9600;
            case BAUDRATE_19200:
                return 19200;
            case BAUDRATE_38400:
                return 38400;
            case BAUDRATE_57600:
                return 57600;
            case BAUDRATE_115200:
                return 115200;
            case BAUDRATE_230400:
                return 230400;
            case BAUDRATE_460800:
                return 460800;
            case BAUDRATE_500000:
                return 500000;
            case BAUDRATE_576000:
                return 576000;
            case BAUDRATE_921600:
                return 921600;
            case BAUDRATE_1000000:
                return 1000000;
            case BAUDRATE_1152000:
                return 1152000;
            case BAUDRATE_1500000:
                return 1500000;
            case BAUDRATE_2000000:
                return 2000000;
            case BAUDRATE_2500000:
                return 2500000;
            case BAUDRATE_3000000:
                return 3000000;
            case BAUDRATE_3500000:
                return 3500000;
            case BAUDRATE_4000000:
                return 4000000;
            default:
                return 0;
        }
    }

  private:
    std::uint8_t _value;
};
}  // namespace uart
}  // namespace hardware
}  // namespace catta
