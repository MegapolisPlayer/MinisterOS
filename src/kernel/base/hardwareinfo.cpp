#include "hardwareinfo.h"

namespace os {
	void getcpustr(char* aResult) {
		uint leax = 0, lebx = 0, lecx = 0, ledx = 0;
		__get_cpuid(0, &leax, &lebx, &lecx, &ledx);

		union {
			struct { uint32_t I1, I2, I3; };
			char Out[12];
		} lCV;

		lCV.I1 = lebx;
		lCV.I2 = ledx;
		lCV.I3 = lecx;
		strcpy(lCV.Out, 12, aResult, 12);
		aResult[12] = '\0';
	}
	const char* getcpumanufacturer() {
		char lVStr[13];
		getcpustr(lVStr);

		if (streq(lVStr, "AuthenticAMD")) {
			return "AMD";
		}
		if (streq(lVStr, "CentaurHauls")) {
			return "Centaur";
		}
		if (streq(lVStr, "CyrixInstead")) {
			return "Cyrix";
		}
		if (streq(lVStr, "E2K MACHINE ")) {
			return "Elbrus";
		}
		if (streq(lVStr, "GenuineIntel")) {
			return "Intel";
		}
		if (streq(lVStr, "GenuineTMx86")) {
			return "Transmeta";
		}
		if (streq(lVStr, "HygonGenuine")) {
			return "Hygon";
		}
		if (streq(lVStr, "MiSTer AO486")) {
			return "AO486";
		}
		if (streq(lVStr, "NexGenDriven")) {
			return "NexGen";
		}
		if (streq(lVStr, "RiseRiseRise")) {
			return "Rise";
		}
		if (streq(lVStr, "  Shanghai  ")) {
			return "Zhaoxin";
		}
		if (streq(lVStr, "SiS SiS SiS ")) {
			return "SiS";
		}
		if (streq(lVStr, "UMC UMC UMC ")) {
			return "UMC";
		}
		if (streq(lVStr, "VIA VIA VIA ")) {
			return "VIA";
		}
		if (streq(lVStr, "Vortex86 SoC")) {
			return "Vortex";
		}
		else {
			return "Unknown";
		}
	}
	
	uint32_t getramamount() {
		union {
			struct { uint8_t Low, High; };
			uint16_t Total;
		} lMem;

		lMem.Low = getcmosreg(0x30);
		lMem.High = getcmosreg(0x31);

		return lMem.Total;
	}	
} 