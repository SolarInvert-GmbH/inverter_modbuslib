// gui
#include <catta/gui/DummyInverter.hpp>

// linux
#include <catta/windows/Time.hpp>
#include <catta/windows/Uart.hpp>

int main()
{
    using DummyInverter = catta::gui::DummyInverter<catta::windows::Uart, catta::windows::Time>;
    DummyInverter* dummyInverter = new DummyInverter("COM1");
    dummyInverter->run();
    delete dummyInverter;
    return 0;
}
