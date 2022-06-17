#ifndef ASMBLCOM
#define ASMBLCOM

#include "base.h"

namespace os {
	void outb(uint16_t port, uint8_t val);
	uint8_t inb(uint16_t port);

	uint8_t getcmosreg(uint16_t reg);
	uint16_t iscmostimeupdating();
}

#endif