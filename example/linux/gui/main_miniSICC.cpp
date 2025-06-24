// gui
#include <catta/gui/MiniSicc.hpp>

// linux
#include <catta/linux/HostId.hpp>
#include <catta/linux/Time.hpp>
#include <catta/linux/Uart.hpp>

int main()
{
    using MiniSicc = catta::gui::MiniSicc<catta::linux::Uart, catta::linux::Time>;
    MiniSicc* miniSicc = new MiniSicc(catta::linux::HostId::get().value_or(0x0123456789abcdef), "/dev/ttyUSB0");
    miniSicc->run();
    delete miniSicc;
    return 0;
}
