// gui
#include <catta/gui/MiniSicc.hpp>

// linux
#include <catta/windows/Time.hpp>
#include <catta/windows/Uart.hpp>

int main()
{
    using MiniSicc = catta::gui::MiniSicc<catta::windows::Uart, catta::windows::Time>;
    MiniSicc* miniSicc = new MiniSicc("COM1");
    miniSicc->run();
    delete miniSicc;
    return 0;
}
