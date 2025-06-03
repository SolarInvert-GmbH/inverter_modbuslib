// gui
#include <catta/gui/MiniSicc.hpp>

// linux
#include <catta/linux/Time.hpp>
#include <catta/linux/Uart.hpp>

int main()
{
    using MiniSicc = catta::gui::MiniSicc<catta::linux::Uart, catta::linux::Time>;
    MiniSicc* miniSicc = new MiniSicc("/dev/ttyUSB0");
    miniSicc->run();
    delete miniSicc;
    return 0;
}
