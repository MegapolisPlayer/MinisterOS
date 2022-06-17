#include "base.h"

namespace os {
	uint32_t pow(uint16_t aInt, uint16_t aPower) {
		uint32_t lInt = aInt;
		for (uint16_t i = 1; i < aPower; i++) {
			lInt *= aInt;
		}
		return lInt;
	}
	uint32_t log10(uint32_t aInt) {
		uint32_t lId = 0;
		while (aInt >= 10) {
			aInt /= 10;
			lId++;
		}
		return lId;
	}
	uint32_t digitam(uint32_t aInt) {
		return log10(aInt) + 1;
	}
	uint32_t revnum(uint32_t aInt) {
		uint32_t lRemnant = 0, lReverse = 0;
		while (aInt != 0) {
			lRemnant = aInt % 10;
			lReverse = lReverse * 10 + lRemnant;
			aInt /= 10;
		}
		return lReverse;
	}
	bool isprime(uint32_t aInt) {
		if (aInt == 2 || aInt == 3 || aInt == 5) return true;
		if (!(aInt % 2) || !(aInt % 3) || !(aInt % 5)) return false;

		for (uint32_t i = 7; i * i <= aInt; i += 6) {
			if (!(aInt % i) || !(aInt % (i + 4))) return false;
		}

		return true;
	}

	uint16_t strlen(const char* aString) {
		uint16_t lId = 0;
		while (aString[lId] != 0) {
			lId++;
		}
		return lId;
	}

	bool streq(const char* aString1, const char* aString2) {
		if (strlen(aString1) == strlen(aString2)) {
			for (uint16_t i = 0; i < strlen(aString1); i++) {
				if (aString1[i] != aString2[i]) return false;
				else continue;
			}
			return true;
		}
		else return false;
	}
	bool streq(const char* aString1, uint16_t aString1Size, const char* aString2, uint16_t aString2Size) {
		if (aString1Size == aString2Size) {
			for (uint16_t i = 0; i < strlen(aString1); i++) {
				if (aString1[i] != aString2[i]) return false;
				else continue;
			}
			return true;
		}
		else return false;
	}

	void strcpy(const char* aSrc, char* aDest) {
		if (strlen(aDest) >= strlen(aSrc)) {
			for (uint16_t i = 0; i < strlen(aSrc); i++) {
				aDest[i] = aSrc[i];
			}
		}
		else {
			for (uint16_t i = 0; i < strlen(aDest); i++) {
				aDest[i] = aSrc[i];
			}
		}
	}
	void strcpy(const char* aSrc, uint16_t aSrcSize, char* aDest, uint16_t aDestSize) {
		if (aDestSize >= aSrcSize) {
			for (uint16_t i = 0; i < aSrcSize; i++) {
				aDest[i] = aSrc[i];
			}
		}
		else {
			for (uint16_t i = 0; i < aDestSize; i++) {
				aDest[i] = aSrc[i];
			}
		}
	}

	//USE IRQ 8 later

	void microdelay() {
		const char* aText1 = "Minister Micro Imprecise Delay,  works.";
		char aText2[40] = {};
		for (uint32_t i = 0; i < 1024; i++) {
			strcpy(aText1, aText2);
		}
	}
	void minidelay() {
		const char* aText1 = "Minister Mini Imprecise Delay,  works for now.";
		char aText2[47] = {};
		for (uint32_t i = 0; i < 4096; i++) {
			strcpy(aText1, aText2);
		}
	}
	void smalldelay() {
		const char* aText1 = "Minister Small Imprecise Delay, works for now.";
		char aText2[47] = {};
		for (uint32_t i = 0; i < 16384; i++) {
			strcpy(aText1, aText2);
		}
	}
}