// gui
#include <catta/gui/DummyInverter.hpp>

// linux
#include <catta/linux/Time.hpp>
#include <catta/linux/Uart.hpp>

int main()
{
    using DummyInverter = catta::gui::DummyInverter<catta::linux::Uart, catta::linux::Time>;
    DummyInverter* dummyInverter = new DummyInverter("/dev/ttyUSB0");
    dummyInverter->run();
    delete dummyInverter;
    return 0;
}
