// gui
#include <catta/gui/MiniSicc.hpp>

// linux
#include <catta/windows/HostId.hpp>
#include <catta/windows/Time.hpp>
#include <catta/windows/Uart.hpp>

int main()
{
    using MiniSicc = catta::gui::MiniSicc<catta::windows::Uart, catta::windows::Time>;
    MiniSicc* miniSicc = new MiniSicc(catta::windows::HostId::get().value_or(0x0123456789abcdef), "COM1");
    miniSicc->run();
    delete miniSicc;
    return 0;
}
