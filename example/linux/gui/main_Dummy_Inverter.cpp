// gui
#include <catta/gui/DummyInverter.hpp>

// linux
#include <catta/linux/Uart.hpp>

int main()
{
    catta::gui::DummyInverter* dummyInverter = new catta::gui::DummyInverter();
    dummyInverter->run();
    delete dummyInverter;
    return 0;
}
