#ifndef DATETIME
#define DATETIME

#include "../base/hardwareinfo.h"

namespace os {
    struct timepoint {
        uint8_t second, minute, hour, day, month;
        uint32_t year;
    };

    timepoint readcmostime();
}

#endif