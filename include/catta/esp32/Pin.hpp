#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace esp32
{
/**
 * @brief Represent pin of esp32.
 * @author CattaTech - Maik Urbannek
 */
class Pin
{
  private:
    constexpr static std::uint8_t GP00 = 0;
    constexpr static std::uint8_t GP01 = 1;
    constexpr static std::uint8_t GP02 = 2;
    constexpr static std::uint8_t GP03 = 3;
    constexpr static std::uint8_t GP04 = 4;
    constexpr static std::uint8_t GP05 = 5;
    constexpr static std::uint8_t GP06 = 6;
    constexpr static std::uint8_t GP07 = 7;
    constexpr static std::uint8_t GP08 = 8;
    constexpr static std::uint8_t GP09 = 9;
    constexpr static std::uint8_t GP10 = 10;
    constexpr static std::uint8_t GP11 = 11;
    constexpr static std::uint8_t GP12 = 12;
    constexpr static std::uint8_t GP13 = 13;
    constexpr static std::uint8_t GP14 = 14;
    constexpr static std::uint8_t GP15 = 15;
    constexpr static std::uint8_t GP16 = 16;
    constexpr static std::uint8_t GP17 = 17;
    constexpr static std::uint8_t GP18 = 18;
    constexpr static std::uint8_t GP19 = 19;
    constexpr static std::uint8_t GP20 = 20;
    constexpr static std::uint8_t GP21 = 21;
    constexpr static std::uint8_t GP22 = 22;
    constexpr static std::uint8_t GP23 = 23;
    constexpr static std::uint8_t GP24 = 24;
    constexpr static std::uint8_t GP25 = 25;
    constexpr static std::uint8_t GP26 = 26;
    constexpr static std::uint8_t GP27 = 27;
    constexpr static std::uint8_t GP28 = 28;
    constexpr static std::uint8_t GP29 = 29;
    constexpr static std::uint8_t GP30 = 30;
    constexpr static std::uint8_t GP31 = 31;
    constexpr static std::uint8_t GP32 = 32;
    constexpr static std::uint8_t GP33 = 33;
    constexpr static std::uint8_t GP34 = 34;
    constexpr static std::uint8_t GP35 = 35;
    constexpr static std::uint8_t GP36 = 36;
    constexpr static std::uint8_t GP37 = 37;
    constexpr static std::uint8_t GP38 = 38;
    constexpr static std::uint8_t GP39 = 39;
    constexpr static std::uint8_t EMPTY = 40;

  public:
    /**
     * @param[in] value The enum value of the pin.
     * @warning This constructor should not be used. Use gp00(), gp01(), gp02(), gp03(), gp04(), gp05(), gp06(), gp07(), gp08(), gp09(), gp10(),
     * gp11(), gp12(), gp13(), gp14(), gp15(), gp16(), gp17(), gp18(), gp19(), gp20(), gp21(), gp22(), gp23(), gp24(), gp25(), gp26(), gp27(), gp28(),
     * gp29(), gp30(), gp31(), gp32(), gp33(), gp34(), gp35(), gp36(), gp37(), gp38(), gp39() or empty(). Explicit constructor. Converts uint8 to pin.
     */
    [[nodiscard]] constexpr explicit Pin(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates empty pin.
     */
    [[nodiscard]] constexpr Pin() noexcept : Pin(EMPTY) {}
    /**
     * @return Returns the pin00.
     */
    [[nodiscard]] constexpr static Pin gp00() noexcept { return Pin{GP00}; }
    /**
     * @return Returns the pin01.
     */
    [[nodiscard]] constexpr static Pin gp01() noexcept { return Pin{GP01}; }
    /**
     * @return Returns the pin02.
     */
    [[nodiscard]] constexpr static Pin gp02() noexcept { return Pin{GP02}; }
    /**
     * @return Returns the pin03.
     */
    [[nodiscard]] constexpr static Pin gp03() noexcept { return Pin{GP03}; }
    /**
     * @return Returns the pin04.
     */
    [[nodiscard]] constexpr static Pin gp04() noexcept { return Pin{GP04}; }
    /**
     * @return Returns the pin05.
     */
    [[nodiscard]] constexpr static Pin gp05() noexcept { return Pin{GP05}; }
    /**
     * @return Returns the pin06.
     */
    [[nodiscard]] constexpr static Pin gp06() noexcept { return Pin{GP06}; }
    /**
     * @return Returns the pin07.
     */
    [[nodiscard]] constexpr static Pin gp07() noexcept { return Pin{GP07}; }
    /**
     * @return Returns the pin08.
     */
    [[nodiscard]] constexpr static Pin gp08() noexcept { return Pin{GP08}; }
    /**
     * @return Returns the pin09.
     */
    [[nodiscard]] constexpr static Pin gp09() noexcept { return Pin{GP09}; }
    /**
     * @return Returns the pin10.
     */
    [[nodiscard]] constexpr static Pin gp10() noexcept { return Pin{GP10}; }
    /**
     * @return Returns the pin11.
     */
    [[nodiscard]] constexpr static Pin gp11() noexcept { return Pin{GP11}; }
    /**
     * @return Returns the pin12.
     */
    [[nodiscard]] constexpr static Pin gp12() noexcept { return Pin{GP12}; }
    /**
     * @return Returns the pin13.
     */
    [[nodiscard]] constexpr static Pin gp13() noexcept { return Pin{GP13}; }
    /**
     * @return Returns the pin14.
     */
    [[nodiscard]] constexpr static Pin gp14() noexcept { return Pin{GP14}; }
    /**
     * @return Returns the pin15.
     */
    [[nodiscard]] constexpr static Pin gp15() noexcept { return Pin{GP15}; }
    /**
     * @return Returns the pin16.
     */
    [[nodiscard]] constexpr static Pin gp16() noexcept { return Pin{GP16}; }
    /**
     * @return Returns the pin17.
     */
    [[nodiscard]] constexpr static Pin gp17() noexcept { return Pin{GP17}; }
    /**
     * @return Returns the pin18.
     */
    [[nodiscard]] constexpr static Pin gp18() noexcept { return Pin{GP18}; }
    /**
     * @return Returns the pin19.
     */
    [[nodiscard]] constexpr static Pin gp19() noexcept { return Pin{GP19}; }
    /**
     * @return Returns the pin20.
     */
    [[nodiscard]] constexpr static Pin gp20() noexcept { return Pin{GP20}; }
    /**
     * @return Returns the pin21.
     */
    [[nodiscard]] constexpr static Pin gp21() noexcept { return Pin{GP21}; }
    /**
     * @return Returns the pin22.
     */
    [[nodiscard]] constexpr static Pin gp22() noexcept { return Pin{GP22}; }
    /**
     * @return Returns the pin23.
     */
    [[nodiscard]] constexpr static Pin gp23() noexcept { return Pin{GP23}; }
    /**
     * @return Returns the pin24.
     */
    [[nodiscard]] constexpr static Pin gp24() noexcept { return Pin{GP24}; }
    /**
     * @return Returns the pin25.
     */
    [[nodiscard]] constexpr static Pin gp25() noexcept { return Pin{GP25}; }
    /**
     * @return Returns the pin26.
     */
    [[nodiscard]] constexpr static Pin gp26() noexcept { return Pin{GP26}; }
    /**
     * @return Returns the pin27.
     */
    [[nodiscard]] constexpr static Pin gp27() noexcept { return Pin{GP27}; }
    /**
     * @return Returns the pin28.
     */
    [[nodiscard]] constexpr static Pin gp28() noexcept { return Pin{GP28}; }
    /**
     * @return Returns the pin29.
     */
    [[nodiscard]] constexpr static Pin gp29() noexcept { return Pin{GP29}; }
    /**
     * @return Returns the pin30.
     */
    [[nodiscard]] constexpr static Pin gp30() noexcept { return Pin{GP30}; }
    /**
     * @return Returns the pin31.
     */
    [[nodiscard]] constexpr static Pin gp31() noexcept { return Pin{GP31}; }
    /**
     * @return Returns the pin32.
     */
    [[nodiscard]] constexpr static Pin gp32() noexcept { return Pin{GP32}; }
    /**
     * @return Returns the pin33.
     */
    [[nodiscard]] constexpr static Pin gp33() noexcept { return Pin{GP33}; }
    /**
     * @return Returns the pin34.
     */
    [[nodiscard]] constexpr static Pin gp34() noexcept { return Pin{GP34}; }
    /**
     * @return Returns the pin35.
     */
    [[nodiscard]] constexpr static Pin gp35() noexcept { return Pin{GP35}; }
    /**
     * @return Returns the pin36.
     */
    [[nodiscard]] constexpr static Pin gp36() noexcept { return Pin{GP36}; }
    /**
     * @return Returns the pin37.
     */
    [[nodiscard]] constexpr static Pin gp37() noexcept { return Pin{GP37}; }
    /**
     * @return Returns the pin38.
     */
    [[nodiscard]] constexpr static Pin gp38() noexcept { return Pin{GP38}; }
    /**
     * @return Returns the pin39.
     */
    [[nodiscard]] constexpr static Pin gp39() noexcept { return Pin{GP39}; }
    /**
     * @return Returns the empty pin.
     */
    [[nodiscard]] constexpr static Pin empty() noexcept { return Pin{EMPTY}; }
    /**
     * @param[in] other The other Pin.
     * @return Returns @b true if the two Pin objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const Pin& other) const = default;
    /**
     * @return Returns pin as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if pin00 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp00() const noexcept { return _value == GP00; }
    /**
     * @return Returns @b true if pin01 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp01() const noexcept { return _value == GP01; }
    /**
     * @return Returns @b true if pin02 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp02() const noexcept { return _value == GP02; }
    /**
     * @return Returns @b true if pin03 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp03() const noexcept { return _value == GP03; }
    /**
     * @return Returns @b true if pin04 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp04() const noexcept { return _value == GP04; }
    /**
     * @return Returns @b true if pin05 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp05() const noexcept { return _value == GP05; }
    /**
     * @return Returns @b true if pin06 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp06() const noexcept { return _value == GP06; }
    /**
     * @return Returns @b true if pin07 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp07() const noexcept { return _value == GP07; }
    /**
     * @return Returns @b true if pin08 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp08() const noexcept { return _value == GP08; }
    /**
     * @return Returns @b true if pin09 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp09() const noexcept { return _value == GP09; }
    /**
     * @return Returns @b true if pin10 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp10() const noexcept { return _value == GP10; }
    /**
     * @return Returns @b true if pin11 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp11() const noexcept { return _value == GP11; }
    /**
     * @return Returns @b true if pin12 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp12() const noexcept { return _value == GP12; }
    /**
     * @return Returns @b true if pin13 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp13() const noexcept { return _value == GP13; }
    /**
     * @return Returns @b true if pin14 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp14() const noexcept { return _value == GP14; }
    /**
     * @return Returns @b true if pin15 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp15() const noexcept { return _value == GP15; }
    /**
     * @return Returns @b true if pin16 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp16() const noexcept { return _value == GP16; }
    /**
     * @return Returns @b true if pin17 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp17() const noexcept { return _value == GP17; }
    /**
     * @return Returns @b true if pin18 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp18() const noexcept { return _value == GP18; }
    /**
     * @return Returns @b true if pin19 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp19() const noexcept { return _value == GP19; }
    /**
     * @return Returns @b true if pin20 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp20() const noexcept { return _value == GP20; }
    /**
     * @return Returns @b true if pin21 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp21() const noexcept { return _value == GP21; }
    /**
     * @return Returns @b true if pin22 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp22() const noexcept { return _value == GP22; }
    /**
     * @return Returns @b true if pin23 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp23() const noexcept { return _value == GP23; }
    /**
     * @return Returns @b true if pin24 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp24() const noexcept { return _value == GP24; }
    /**
     * @return Returns @b true if pin25 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp25() const noexcept { return _value == GP25; }
    /**
     * @return Returns @b true if pin26 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp26() const noexcept { return _value == GP26; }
    /**
     * @return Returns @b true if pin27 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp27() const noexcept { return _value == GP27; }
    /**
     * @return Returns @b true if pin28 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp28() const noexcept { return _value == GP28; }
    /**
     * @return Returns @b true if pin29 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp29() const noexcept { return _value == GP29; }
    /**
     * @return Returns @b true if pin30 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp30() const noexcept { return _value == GP30; }
    /**
     * @return Returns @b true if pin31 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp31() const noexcept { return _value == GP31; }
    /**
     * @return Returns @b true if pin32 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp32() const noexcept { return _value == GP32; }
    /**
     * @return Returns @b true if pin33 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp33() const noexcept { return _value == GP33; }
    /**
     * @return Returns @b true if pin34 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp34() const noexcept { return _value == GP34; }
    /**
     * @return Returns @b true if pin35 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp35() const noexcept { return _value == GP35; }
    /**
     * @return Returns @b true if pin36 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp36() const noexcept { return _value == GP36; }
    /**
     * @return Returns @b true if pin37 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp37() const noexcept { return _value == GP37; }
    /**
     * @return Returns @b true if pin38 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp38() const noexcept { return _value == GP38; }
    /**
     * @return Returns @b true if pin39 is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp39() const noexcept { return _value == GP39; }
    /**
     * @return Returns @b true if empty pin is represented, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Pin in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"GP00", "GP01", "GP02", "GP03", "GP04", "GP05", "GP06", "GP07", "GP08", "GP09",
                                                                      "GP10", "GP11", "GP12", "GP13", "GP14", "GP15", "GP16", "GP17", "GP18", "GP19",
                                                                      "GP20", "GP21", "GP22", "GP23", "GP24", "GP25", "GP26", "GP27", "GP28", "GP29",
                                                                      "GP30", "GP31", "GP32", "GP33", "GP34", "GP35", "GP36", "GP37", "GP38", "GP39"};

  private:
    std::uint8_t _value;
};
}  // namespace esp32
}  // namespace catta
