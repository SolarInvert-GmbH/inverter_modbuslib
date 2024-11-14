// catta
#include <catta/modbus/sunspec/String.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/Test.hpp>

int main()
{
    static constexpr auto string = catta::modbus::sunspec::String::create("Catta");
    std::cout << string.data().data() << ' ' << string.isEmpty() << '\n';
    return 0;
}
