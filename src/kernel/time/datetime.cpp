#include "datetime.h"

namespace os {
    timepoint readcmostime() {
        timepoint lCt, lLCt;
        uint8_t CMOSReg11;

        //reading until two same values
        //from osdev wiki, changed almost everything

        //get the first values
        lCt.second = getcmosreg(0x00);
        lCt.minute = getcmosreg(0x02);
        lCt.hour   = getcmosreg(0x04);
        lCt.day    = getcmosreg(0x07);
        lCt.month  = getcmosreg(0x08);
        lCt.year   = getcmosreg(0x09);

        microdelay(); //micro delay so request isnt on same tick

        lLCt.second = getcmosreg(0x00);
        lLCt.minute = getcmosreg(0x02);
        lLCt.hour   = getcmosreg(0x04);
        lLCt.day    = getcmosreg(0x07);
        lLCt.month  = getcmosreg(0x08);
        lLCt.year   = getcmosreg(0x09);

        while ((
            (lLCt.second != lCt.second) or
            (lLCt.minute != lCt.minute) or
            (lLCt.hour   != lCt.hour  ) or
            (lLCt.day    != lCt.day   ) or
            (lLCt.month  != lCt.month ) or
            (lLCt.year   != lCt.year  )
            ) and iscmostimeupdating()) { //if all values are equal (ret false) and cmos is not updating (ret false) exit
                lCt.second = lLCt.second; //saving last values to currents
                lCt.minute = lLCt.minute;
                lCt.hour   = lLCt.hour;
                lCt.day    = lLCt.day;
                lCt.month  = lLCt.month;
                lCt.year   = lLCt.year;

                microdelay(); //micro delay so request isnt on same tick

                while (iscmostimeupdating()) { //reading new "last" values
                    lLCt.second = getcmosreg(0x00);
                    lLCt.minute = getcmosreg(0x02);
                    lLCt.hour   = getcmosreg(0x04);
                    lLCt.day    = getcmosreg(0x07);
                    lLCt.month  = getcmosreg(0x08);
                    lLCt.year   = getcmosreg(0x09);
                }
            }

            CMOSReg11 = getcmosreg(0x0B);

            // Convert BCD to binary values if necessary

            if (!(CMOSReg11 & 0x04)) {
                lCt.second = (lCt.second & 0x0F) + (( lCt.second / 16) * 10);
                lCt.minute = (lCt.minute & 0x0F) + (( lCt.minute / 16) * 10);
                lCt.hour   = (lCt.hour   & 0x0F) + (((lCt.hour   & 0x70) / 16) * 10) | (lCt.hour & 0x80);
                lCt.day    = (lCt.day    & 0x0F) + (( lCt.day    / 16) * 10);
                lCt.month  = (lCt.month  & 0x0F) + (( lCt.month  / 16) * 10);
                lCt.year   = (lCt.year   & 0x0F) + (( lCt.year   / 16) * 10);
            }

            // Convert 12 hour clock to 24 hour clock if necessary

            if (!(CMOSReg11 & 0x02) and (lCt.hour & 0x80)) {
                lCt.hour = ((lCt.hour & 0x7F) + 12) % 24;
            }

            // Calculate the full (4-digit) year

            lCt.year += (2022 / 100) * 100;
            if (lCt.year < 2022) lCt.year += 100;

            return lCt;
        }
}