#include "main.h"

extern "C" void _start() {
    os::terminalout tout;
    tout.setclr(os::color::WHITE, os::color::BLUE);
    tout.clrscr();
    tout.drawborder(BORDER_SINGLELINE);

    tout.drawpalette();
    tout.nl();

    tout.print("Minister Kernel");
    tout.nl();


    tout.printnl("CPU", os::getcpumanufacturer());
    tout.printnl("RAM", os::getramamount(), "KB");

    tout.print("BOOTUP TIME: ");
    tout.printnl(os::readcmostime());

    tout.print("CURRENT TIME: ");

    uint32_t lId = 0;
    while (true) {
        tout.print(os::readcmostime());
        lId++;
    
        if (lId % 1000 == 0 and lId > 0) { //300 cycles = ~1 second
    
            uint8_t lClr = uint8_t(tout.bg()) + 1;
    
            if (lClr > 15) { lClr = 0; } //wraparound
    
            if (lClr == 0) {
                tout.setfg(os::color::WHITE);
            }
            if (lClr == 10) {
                tout.setfg(os::color::BLACK);
            }
    
            tout.setbg(os::color(lClr));
        }
    
        os::minidelay();
        tout.delchars(20);
    }
    
    return;
}