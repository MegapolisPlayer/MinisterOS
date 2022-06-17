#include "out.h"

namespace os {
	address::address() {
		this->chr = 0xb8000;
		this->clr = 0xb8001;
	}
	void address::reset() {
		this->chr = 0xb8000;
		this->clr = 0xb8001;
	}
	void address::operator++() { //prefix
		this->chr += 2;
		this->clr += 2;
	}
	void address::operator++(int) { //postfix
		this->chr += 2;
		this->clr += 2;
	}
	void address::operator--() {
		this->chr -= 2;
		this->clr -= 2;
	}
	void address::operator--(int) {
		this->chr -= 2;
		this->clr -= 2;
	}

	void address::operator+(uint32_t aChars) {
		this->chr += (aChars * 2);
		this->clr += (aChars * 2);
	}
	void address::operator-(uint32_t aChars) {
		this->chr -= (aChars * 2);
		this->clr -= (aChars * 2);
	}

	border::border() {
		this->StraightV = 0;
		this->StraightH = 0;
		this->ULCorner = 0;
		this->URCorner = 0;
		this->LRCorner = 0;
		this->LLCorner = 0;
	}
	border::border(uint8_t aAll) {
		this->StraightV = aAll;
		this->StraightH = aAll;
		this->ULCorner = aAll;
		this->URCorner = aAll;
		this->LRCorner = aAll;
		this->LLCorner = aAll;
	}
	border::border(uint8_t aStraightV, uint8_t aStraightH, uint8_t aULCorner, uint8_t aURCorner, uint8_t aLRCorner, uint8_t aLLCorner) {
		this->StraightV = aStraightV;
		this->StraightH = aStraightH;
		this->ULCorner = aULCorner;
		this->URCorner = aURCorner;
		this->LRCorner = aLRCorner;
		this->LLCorner = aLLCorner;
	}

	cursor::cursor() {
		this->enabled = false;
	}
	void cursor::enable(uint8_t aCharScanlineBegin, uint8_t aCharScanlineEnd) {
		if (aCharScanlineEnd > 16) aCharScanlineEnd = 16;
		outb(0x3D4, 0x0A);
		outb(0x3D5, (inb(0x3D5) & 0xC0) | aCharScanlineBegin);
		outb(0x3D4, 0x0B);
		outb(0x3D5, (inb(0x3D5) & 0xE0) | aCharScanlineEnd);
		this->enabled = true;
	}
	void cursor::position(uint8_t aRow, uint8_t aColumn) {
		uint16_t pos = aRow * 80 + aColumn;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t)(pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
	}
	void cursor::disable() {
		outb(0x3D4, 0x0A);
		outb(0x3D5, 0x20);
		this->enabled = false;
	}

	color getfg(uint8_t aCombined) {
		return color(aCombined % 16);
	}
	color getbg(uint8_t aCombined) {
		return color(aCombined / 16);
	}
	uint8_t combineclr(color aBg, color aFg) {
		return (uint8_t(aBg) * 16) + uint8_t(aFg);
	}

	terminalout::terminalout() {
		this->addr;
		this->crsr;
		this->activecolor = combineclr(color::WHITE, color::LIGHT_GREY);
		this->hasborder = false;
	}

	void terminalout::print(char aChar) {
		this->prtchar(aChar);
		this->crsr.position(this->row(), this->column());
	}
	void terminalout::print(const char* aString) {
		uint16_t lId = 0;
		while (aString[lId] != '\0') {
			if (this->hasborder and lId % (80 - 2) == 0 and lId > 0) {
				this->moveaddr(2);
			}
			this->prtchar(aString[lId]);
			lId++;
		}
		this->crsr.position(this->row(), this->column());
	}
	void terminalout::print(uint8_t aInt) {
		this->print(uint32_t(aInt));
	}
	void terminalout::print(uint16_t aInt) {
		this->print(uint32_t(aInt));
	}
	void terminalout::print(uint32_t aInt) {
		if (aInt == 0) {
			this->prtchar('0');
			return;
		}
		uint16_t lDigitsAm1 = digitam(aInt);
		uint32_t lInt = revnum(aInt);
		uint16_t lDigitsAm2 = digitam(lInt);
		while (lInt != 0) {
			this->prtchar((lInt % 10) + '0');
			lInt /= 10;
		}
		for (uint16_t i = 0; i < lDigitsAm1 - lDigitsAm2; i++) {
			this->prtchar('0');
		}
		this->crsr.position(this->row(), this->column());
	}
	void terminalout::print(const char* aDescription, uint32_t aValue, const char* aUnit) {
		this->print(aDescription);
		this->print(": ");
		this->print(aValue);
		this->print(' ');
		this->print(aUnit);
		this->crsr.position(this->row(), this->column());
	}
	void terminalout::print(const char* aDescription, const char* aValue, const char* aUnit) {
		this->print(aDescription);
		this->print(": ");
		this->print(aValue);
		this->print(' ');
		this->print(aUnit);
		this->crsr.position(this->row(), this->column());
	}
	void terminalout::print(timepoint aTime) {
		if (aTime.hour < 10) {
			this->print('0');
		}
		this->print(aTime.hour);
		this->print(':');

		if (aTime.minute < 10) {
			this->print('0');
		}
		this->print(aTime.minute);
		this->print(':');

		if (aTime.second < 10) {
			this->print('0');
		}
		this->print(aTime.second);
		this->print(", ");

		if (aTime.day < 10) {
			this->print('0');
		}
		this->print(aTime.day);
		this->print('.');

		if (aTime.month < 10) {
			this->print('0');
		}
		this->print(aTime.month);
		this->print('.');

		if (aTime.year < 10) {
			this->print('0');
		}
		this->print(aTime.year);
	}

	void terminalout::nl() {
		uint8_t lColumn = 80 - this->column();
		this->moveaddr(lColumn);
		this->moveaddr(this->hasborder);
	}

	void terminalout::printnl(char aChar) {
		this->print(aChar);
		this->nl();
	}
	void terminalout::printnl(const char* aString) {
		this->print(aString);
		this->nl();
	}
	void terminalout::printnl(uint8_t aInt) {
		this->printnl(uint32_t(aInt));
	}
	void terminalout::printnl(uint16_t aInt) {
		this->printnl(uint32_t(aInt));
	}
	void terminalout::printnl(uint32_t aInt) {
		this->print(aInt);
		this->nl();
	}
	void terminalout::printnl(const char* aDescription, uint32_t aValue, const char* aUnit) {
		this->print(aDescription, aValue, aUnit);
		this->nl();
	}
	void terminalout::printnl(const char* aDescription, const char* aValue, const char* aUnit) {
		this->print(aDescription, aValue, aUnit);
		this->nl();
	}
	void terminalout::printnl(timepoint aTime) {
		this->print(aTime);
		this->nl();
	}

	void terminalout::delchars(uint32_t aAmount) {
		this->addr - aAmount;
		for (uint16_t i = 0; i < aAmount; i++) {
			this->prtchar(ASCII_EMPTY);
		}
		this->addr - aAmount;
		this->crsr.position(this->row(), this->column());
	}

	void terminalout::clrscr() {
		for (uint16_t i = 0; i < 2000; i++) {
			this->prtchar(ASCII_EMPTY);
		}
		this->addr.reset();
	}

	void terminalout::drawborder(border aBorder) {
		this->prtchar(aBorder.ULCorner);

		for (uint8_t i = 0; i < 80 - 2; i++) {
			this->prtchar(aBorder.StraightH);
		}

		this->prtchar(aBorder.URCorner);

		for (uint8_t i = 0; i < 25 - 2; i++) {
			this->prtchar(aBorder.StraightV);
			for (uint8_t i = 0; i < 80 - 2; i++) {
				this->moveaddr(1);
			}
			this->prtchar(aBorder.StraightV);
		}

		this->prtchar(aBorder.LLCorner);

		for (uint8_t i = 0; i < 80 - 2; i++) {
			this->prtchar(aBorder.StraightH);
		}

		this->prtchar(aBorder.LRCorner);

		this->hasborder = true;
		this->addr.reset();
		this->moveaddr(80 + 1);
		this->crsr.position(this->row(), this->column());
	}

	void terminalout::drawpalette() {
		uint8_t lSaved = this->activecolor;
		for (uint8_t i = 0; i < 16; i++) {
			this->setbg(color(i));
			this->prtchar(ASCII_EMPTY);
		}
		this->activecolor = lSaved;
	}

	void terminalout::setfg(color aFg) {
		color lBg = getfg(this->activecolor);
		this->activecolor = combineclr(lBg, aFg);
	}
	void terminalout::setbg(color aBg) {
		color lFg = getfg(this->activecolor);
		this->activecolor = combineclr(aBg, lFg);
	}
	void terminalout::setclr(color aFg, color aBg) {
		this->activecolor = combineclr(aBg, aFg);
	}
	void terminalout::setclr(uint8_t aClr) {
		this->activecolor = aClr;
	}
	color terminalout::fg() {
		return color(this->activecolor % 16);
	}
	color terminalout::bg() {
		return color(this->activecolor / 16);
	}
	uint8_t terminalout::clr() {
		return this->activecolor;
	}

	uint8_t terminalout::row() {
		uint32_t lChAddr = this->addr.chr - 0xb8000;
		lChAddr /= 2;

		if (lChAddr < 80) return 0;

		uint32_t lRowCounter = 0;
		while (lChAddr > 80) {
			lChAddr -= 80;
			lRowCounter++;
		}
		return lRowCounter;
	}
	uint8_t terminalout::column() {
		uint32_t lChAddr = this->addr.chr - 0xb8000;
		lChAddr /= 2;

		if (lChAddr < 80) return lChAddr;

		while (lChAddr > 80) {
			lChAddr -= 80;
		}
		return lChAddr;
	}

	address terminalout::adr() {
		return this->addr;
	}


	inline void terminalout::prtchar(char aChar) {
		*(char*)this->addr.chr = aChar;
		*(char*)this->addr.clr = this->activecolor;
		this->addr++;
	}
	inline void terminalout::moveaddr(uint32_t aCharAmount) {
		this->addr + aCharAmount;
	}
}