#ifndef KRNLBASE
#define KRNLBASE

#include <float.h> //float stats
#include <iso646.h> //alterative logic (|| = or)
#include <limits.h> //int type limits
#include <stdalign.h> //alignment stuff - alignof alignas
#include <stdarg.h> //argument iterators
#include <stdbool.h> //bool type
#include <stddef.h> //size_t, wchar_t, ptrdiff_t, NULL
#include <stdint.h> //int types, uint64_t, int32_t
#include <stdnoreturn.h> //noreturn keyword if something goes terribly wrong

#include <cpuid.h> //gcc cpuid

typedef unsigned int uint;

namespace os {
	uint32_t pow(uint16_t aInt, uint16_t aPower);
	uint32_t log10(uint32_t aInt);
	uint32_t digitam(uint32_t aInt);
	uint32_t revnum(uint32_t aInt);
	bool isprime(uint32_t aInt);

	uint16_t strlen(const char* aString);

	bool streq(const char* aString1, const char* aString2);
	bool streq(const char* aString1, uint16_t aString1Size, const char* aString2, uint16_t aString2Size);

	//strcat
	//strerase

	void strcpy(const char* aSrc, char* aDest);
	void strcpy(const char* aSrc, uint16_t aSrcSize, char* aDest, uint16_t aDestSize);
	
	//Inprecise Micro Delay - 4x shorter than microdelay()
	void microdelay();
	//Inprecise Miniature Delay
	void minidelay();
	//Inprecise Small Delay - 4x longer than minidelay()
	void smalldelay();
}
#endif