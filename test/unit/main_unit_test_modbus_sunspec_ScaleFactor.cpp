// catta
#include <catta/modbus/sunspec/ScaleFactor.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/Test.hpp>

int main()
{
    static constexpr auto scaleFactor = catta::modbus::sunspec::ScaleFactor::create(0);
    std::cout << int(scaleFactor.factorExponent()) << ' ' << scaleFactor.isEmpty() << '\n';
    return 0;
}
