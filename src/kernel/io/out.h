#include "../time/datetime.h"

namespace os {
	#define ASCII_EMPTY          32
	#define ASCII_TRANSPARENT_1 176
	#define ASCII_TRANSPARENT_2 177
	#define ASCII_TRANSPARENT_3 178
	#define ASCII_SOLID         219

	struct address {
		address();
		void reset();

		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);

		void operator+(uint32_t aChars);
		void operator-(uint32_t aChars);

		uint32_t chr;
		uint32_t clr;
	};

	struct border {
		border();
		border(uint8_t aAll);
		border(uint8_t aStraightV, uint8_t aStraightH, uint8_t aULCorner, uint8_t aURCorner, uint8_t aLRCorner, uint8_t aLLCorner);

		uint8_t StraightV, StraightH;
		uint8_t ULCorner, URCorner, LRCorner, LLCorner;
	};

	#define BORDER_SINGLELINE { 179, 196, 218, 191, 217, 192 }
	#define BORDER_DOUBLELINE { 186, 205, 201, 187, 188, 200 }
	#define BORDER_TRANSPARENT_1 { ASCII_TRANSPARENT_1 }
	#define BORDER_TRANSPARENT_2 { ASCII_TRANSPARENT_2 }
	#define BORDER_TRANSPARENT_3 { ASCII_TRANSPARENT_3 }
	#define BORDER_SOLID { ASCII_SOLID }

	class cursor {
	public:
		cursor();
		void enable(uint8_t aCharScanlineBegin, uint8_t aCharScanlineEnd);
		void position(uint8_t aRow, uint8_t aColumn);
		void disable();
	protected:
	private:
		bool enabled;
	};

	enum class color {
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		PURPLE = 5,
		BROWN = 6,
		LIGHT_GREY = 7,
		DARK_GREY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		PINK = 13,
		YELLOW = 14,
		WHITE = 15
	};

	color getfg(uint8_t aCombined);
	color getbg(uint8_t aCombined);
	uint8_t combineclr(color aBg, color aFg);

	class terminalout {
	public:
		terminalout();

		void print(char aChar);
		void print(const char* aString);
		void print(uint8_t aInt);
		void print(uint16_t aInt);
		void print(uint32_t aInt);
		void print(const char* aDescription, uint32_t aValue, const char* aUnit = "");
		void print(const char* aDescription, const char* aValue, const char* aUnit = "");
		//20 chars
		void print(timepoint aTime);

		void nl();

		void printnl(char aChar);
		void printnl(const char* aString);
		void printnl(uint8_t aInt);
		void printnl(uint16_t aInt);
		void printnl(uint32_t aInt);
		void printnl(const char* aDescription, uint32_t aValue, const char* aUnit = "");
		void printnl(const char* aDescription, const char* aValue, const char* aUnit = "");
		//20 chars
		void printnl(timepoint aTime);

		void delchars(uint32_t aAmount);

		void clrscr();

		void drawborder(border aBorder);

		void drawpalette();

		void setfg(color aFg);
		void setbg(color aBg);
		void setclr(color aFg, color aBg);
		void setclr(uint8_t aClr);
		color fg();
		color bg();
		uint8_t clr();

		uint8_t row();
		uint8_t column();

		address adr();
	protected:
	private:
		address addr;
		cursor crsr;
		uint8_t activecolor;
		bool hasborder;

		inline void prtchar(char aChar);
		inline void moveaddr(uint32_t aCharAmount);
	};
}