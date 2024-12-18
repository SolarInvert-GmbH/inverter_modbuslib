#pragma once

// std
#include <array>
#include <cstdint>
#include <string_view>

namespace catta
{
namespace rp2040
{
/**
 * @brief Represent pin of the pi pico.
 * @author CattaTech - Maik Urbannek
 */
class Pin
{
  private:
    static constexpr std::uint8_t GP00 = 0;
    static constexpr std::uint8_t GP01 = 1;
    static constexpr std::uint8_t GP02 = 2;
    static constexpr std::uint8_t GP03 = 3;
    static constexpr std::uint8_t GP04 = 4;
    static constexpr std::uint8_t GP05 = 5;
    static constexpr std::uint8_t GP06 = 6;
    static constexpr std::uint8_t GP07 = 7;
    static constexpr std::uint8_t GP08 = 8;
    static constexpr std::uint8_t GP09 = 9;
    static constexpr std::uint8_t GP10 = 10;
    static constexpr std::uint8_t GP11 = 11;
    static constexpr std::uint8_t GP12 = 12;
    static constexpr std::uint8_t GP13 = 13;
    static constexpr std::uint8_t GP14 = 14;
    static constexpr std::uint8_t GP15 = 15;
    static constexpr std::uint8_t GP16 = 16;
    static constexpr std::uint8_t GP17 = 17;
    static constexpr std::uint8_t GP18 = 18;
    static constexpr std::uint8_t GP19 = 19;
    static constexpr std::uint8_t GP20 = 20;
    static constexpr std::uint8_t GP21 = 21;
    static constexpr std::uint8_t GP22 = 22;
    static constexpr std::uint8_t GP23 = 23;
    static constexpr std::uint8_t GP24 = 24;
    static constexpr std::uint8_t GP25 = 25;
    static constexpr std::uint8_t GP26 = 26;
    static constexpr std::uint8_t GP27 = 27;
    static constexpr std::uint8_t GP28 = 28;
    static constexpr std::uint8_t GP29 = 29;
    static constexpr std::uint8_t EMPTY = 30;

  public:
    /**
     * @param[in] value The enum value of the pin.
     * @warning This constructor should not be used. Use gp00(), gp01(), gp02(),
     * gp03(), gp04(), gp05(), gp06(), gp07(), gp08(), gp09(), gp10(), gp11(),
     * gp12(), gp13(), gp14(), gp15(), gp16(), gp17(), gp18(), gp19(), gp20(),
     * gp21(), gp22(), gp23(), gp24(), gp25(), gp26(), gp27(), gp28(), adc0(),
     * adc1(), adc2(), adc3(), led() or empty(). Explicit constructor. Converts
     * uint8 to data type.
     */
    [[nodiscard]] constexpr explicit Pin(const std::uint8_t value) noexcept : _value(value) {}
    /**
     * Default constructor. Creates invalid pin.
     */
    [[nodiscard]] constexpr Pin() noexcept : Pin(EMPTY) {}
    /**
     * @return Returns the pin00 representation.
     */
    [[nodiscard]] constexpr static Pin gp00() noexcept { return Pin{GP00}; }
    /**
     * @return Returns the pin01 representation.
     */
    [[nodiscard]] constexpr static Pin gp01() noexcept { return Pin{GP01}; }
    /**
     * @return Returns the pin02 representation.
     */
    [[nodiscard]] constexpr static Pin gp02() noexcept { return Pin{GP02}; }
    /**
     * @return Returns the pin03 representation.
     */
    [[nodiscard]] constexpr static Pin gp03() noexcept { return Pin{GP03}; }
    /**
     * @return Returns the pin04 representation.
     */
    [[nodiscard]] constexpr static Pin gp04() noexcept { return Pin{GP04}; }
    /**
     * @return Returns the pin05 representation.
     */
    [[nodiscard]] constexpr static Pin gp05() noexcept { return Pin{GP05}; }
    /**
     * @return Returns the pin06 representation.
     */
    [[nodiscard]] constexpr static Pin gp06() noexcept { return Pin{GP06}; }
    /**
     * @return Returns the pin07 representation.
     */
    [[nodiscard]] constexpr static Pin gp07() noexcept { return Pin{GP07}; }
    /**
     * @return Returns the pin08 representation.
     */
    [[nodiscard]] constexpr static Pin gp08() noexcept { return Pin{GP08}; }
    /**
     * @return Returns the pin09 representation.
     */
    [[nodiscard]] constexpr static Pin gp09() noexcept { return Pin{GP09}; }
    /**
     * @return Returns the pin10 representation.
     */
    [[nodiscard]] constexpr static Pin gp10() noexcept { return Pin{GP10}; }
    /**
     * @return Returns the pin11 representation.
     */
    [[nodiscard]] constexpr static Pin gp11() noexcept { return Pin{GP11}; }
    /**
     * @return Returns the pin12 representation.
     */
    [[nodiscard]] constexpr static Pin gp12() noexcept { return Pin{GP12}; }
    /**
     * @return Returns the pin13 representation.
     */
    [[nodiscard]] constexpr static Pin gp13() noexcept { return Pin{GP13}; }
    /**
     * @return Returns the pin14 representation.
     */
    [[nodiscard]] constexpr static Pin gp14() noexcept { return Pin{GP14}; }
    /**
     * @return Returns the pin15 representation.
     */
    [[nodiscard]] constexpr static Pin gp15() noexcept { return Pin{GP15}; }
    /**
     * @return Returns the pin16 representation.
     */
    [[nodiscard]] constexpr static Pin gp16() noexcept { return Pin{GP16}; }
    /**
     * @return Returns the pin17 representation.
     */
    [[nodiscard]] constexpr static Pin gp17() noexcept { return Pin{GP17}; }
    /**
     * @return Returns the pin18 representation.
     */
    [[nodiscard]] constexpr static Pin gp18() noexcept { return Pin{GP18}; }
    /**
     * @return Returns the pin19 representation.
     */
    [[nodiscard]] constexpr static Pin gp19() noexcept { return Pin{GP19}; }
    /**
     * @return Returns the pin20 representation.
     */
    [[nodiscard]] constexpr static Pin gp20() noexcept { return Pin{GP20}; }
    /**
     * @return Returns the pin21 representation.
     */
    [[nodiscard]] constexpr static Pin gp21() noexcept { return Pin{GP21}; }
    /**
     * @return Returns the pin22 representation.
     */
    [[nodiscard]] constexpr static Pin gp22() noexcept { return Pin{GP22}; }
    /**
     * @return Returns the pin23 representation. Hardware is not accessable. Gpio
     * out for buck-boost to create 3.3 Volts. Do not use.
     */
    [[nodiscard]] constexpr static Pin gp23() noexcept { return Pin{GP23}; }
    /**
     * @return Returns the pin24 representation. Hardware is not accessable. Gpio
     * in. High if VBUS is present, else LOW.
     */
    [[nodiscard]] constexpr static Pin gp24() noexcept { return Pin{GP24}; }
    /**
     * @return Returns the pin25 representation. Hardware is not accessable. Led
     * can glow via gpio out.
     */
    [[nodiscard]] constexpr static Pin gp25() noexcept { return Pin{GP25}; }
    /**
     * @return Returns the pin26 representation.
     */
    [[nodiscard]] constexpr static Pin gp26() noexcept { return Pin{GP26}; }
    /**
     * @return Returns the pin27 representation.
     */
    [[nodiscard]] constexpr static Pin gp27() noexcept { return Pin{GP27}; }
    /**
     * @return Returns the pin28 representation.
     */
    [[nodiscard]] constexpr static Pin gp28() noexcept { return Pin{GP28}; }
    /**
     * @return Returns the pin29 representation. Hardware is not accessable. Can
     * be used to messure VSYS.
     */
    [[nodiscard]] constexpr static Pin gp29() noexcept { return Pin{GP29}; }
    /**
     * @return Returns the adc0 (pin26) representation.
     */
    [[nodiscard]] constexpr static Pin adc0() noexcept { return gp26(); }
    /**
     * @return Returns the adc1 (pin27)  representation.
     */
    [[nodiscard]] constexpr static Pin adc1() noexcept { return gp27(); }
    /**
     * @return Returns the adc2 (pin28)  representation.
     */
    [[nodiscard]] constexpr static Pin adc2() noexcept { return gp28(); }
    /**
     * @return Returns the adc3 (pin29)  representation.
     */
    [[nodiscard]] constexpr static Pin adc3() noexcept { return gp29(); }
    /**
     * @return Returns the led (pin25) representation.
     */
    [[nodiscard]] constexpr static Pin led() noexcept { return gp25(); }
    /**
     * @return Returns invalid pin representation.
     */
    [[nodiscard]] constexpr static Pin empty() noexcept { return Pin{EMPTY}; }
    /**
     * @param[in] other The other Pin.
     * @return Returns @b true if the two Pin objects are the same, otherwise @b
     * false.
     */
    [[nodiscard]] constexpr bool operator==(const Pin &other) const noexcept { return this->_value == other._value; }
    /**
     * @param[in] other The other Pin.
     * @return Returns @b true if the two Pin objects are not the same, otherwise
     * @b false.
     */
    [[nodiscard]] constexpr bool operator!=(const Pin &other) const noexcept { return !(*this == other); }
    /**
     * @return Returns the pin as uint8.
     */
    [[nodiscard]] constexpr operator std::uint8_t() const noexcept { return _value; }
    /**
     * @return Returns @b true if the pin is gp00, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp00() const noexcept { return _value == GP00; }
    /**
     * @return Returns @b true if the pin is gp01, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp01() const noexcept { return _value == GP01; }
    /**
     * @return Returns @b true if the pin is gp02, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp02() const noexcept { return _value == GP02; }
    /**
     * @return Returns @b true if the pin is gp03, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp03() const noexcept { return _value == GP03; }
    /**
     * @return Returns @b true if the pin is gp04, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp04() const noexcept { return _value == GP04; }
    /**
     * @return Returns @b true if the pin is gp05, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp05() const noexcept { return _value == GP05; }
    /**
     * @return Returns @b true if the pin is gp06, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp06() const noexcept { return _value == GP06; }
    /**
     * @return Returns @b true if the pin is gp07, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp07() const noexcept { return _value == GP07; }
    /**
     * @return Returns @b true if the pin is gp08, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp08() const noexcept { return _value == GP08; }
    /**
     * @return Returns @b true if the pin is gp09, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp09() const noexcept { return _value == GP09; }
    /**
     * @return Returns @b true if the pin is gp10, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp10() const noexcept { return _value == GP10; }
    /**
     * @return Returns @b true if the pin is gp11, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp11() const noexcept { return _value == GP11; }
    /**
     * @return Returns @b true if the pin is gp12, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp12() const noexcept { return _value == GP12; }
    /**
     * @return Returns @b true if the pin is gp13, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp13() const noexcept { return _value == GP13; }
    /**
     * @return Returns @b true if the pin is gp14, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp14() const noexcept { return _value == GP14; }
    /**
     * @return Returns @b true if the pin is gp15, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp15() const noexcept { return _value == GP15; }
    /**
     * @return Returns @b true if the pin is gp16, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp16() const noexcept { return _value == GP16; }
    /**
     * @return Returns @b true if the pin is gp17, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp17() const noexcept { return _value == GP17; }
    /**
     * @return Returns @b true if the pin is gp18, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp18() const noexcept { return _value == GP18; }
    /**
     * @return Returns @b true if the pin is gp19, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp19() const noexcept { return _value == GP19; }
    /**
     * @return Returns @b true if the pin is gp20, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp20() const noexcept { return _value == GP20; }
    /**
     * @return Returns @b true if the pin is gp21, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp21() const noexcept { return _value == GP21; }
    /**
     * @return Returns @b true if the pin is gp22, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp22() const noexcept { return _value == GP22; }
    /**
     * @return Returns @b true if the pin is gp23, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp23() const noexcept { return _value == GP23; }
    /**
     * @return Returns @b true if the pin is gp24, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp24() const noexcept { return _value == GP24; }
    /**
     * @return Returns @b true if the pin is gp25, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp25() const noexcept { return _value == GP25; }
    /**
     * @return Returns @b true if the pin is gp26, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp26() const noexcept { return _value == GP26; }
    /**
     * @return Returns @b true if the pin is gp27, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp27() const noexcept { return _value == GP27; }
    /**
     * @return Returns @b true if the pin is gp28, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp28() const noexcept { return _value == GP28; }
    /**
     * @return Returns @b true if the pin is gp29, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isGp29() const noexcept { return _value == GP29; }
    /**
     * @return Returns @b true if the pin is invalid, otherwise @b false.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return _value >= EMPTY; }
    /**
     * Pins in text form.
     */
    constexpr static std::array<std::string_view, EMPTY> enumNames = {"GP00", "GP01", "GP02", "GP03", "GP04", "GP05", "GP06", "GP07", "GP08", "GP09",
                                                                      "GP10", "GP11", "GP12", "GP13", "GP14", "GP15", "GP16", "GP17", "GP18", "GP19",
                                                                      "GP20", "GP21", "GP22", "GP23", "GP24", "GP25", "GP26", "GP27", "GP28", "GP29"};

  private:
    std::uint8_t _value;
};
}  // namespace rp2040
}  // namespace catta
