// catta
#include <catta/modbus/sunspec/ScaledUValue.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/Test.hpp>

int main()
{
    static constexpr auto scaleFactor = catta::modbus::sunspec::ScaleFactor::create(0);
    static constexpr std::uint16_t value = 1;
    static constexpr auto scaledValue = catta::modbus::sunspec::ScaledUValue::create(scaleFactor, value);
    std::cout << int(scaledValue.scaleFactor().factorExponent()) << ' ' << scaledValue.value() << ' ' << scaledValue.isEmpty() << '\n';
    return 0;
}
