#ifndef GETHINFO
#define GETHINFO

#include "hardwarecom.h"

namespace os {
	void getcpustr(char* aResult);
	const char* getcpumanufacturer();
	uint32_t getramamount();
}

#endif