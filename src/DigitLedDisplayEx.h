#ifndef DigitLedDisplayEx_h
#define DigitLedDisplayEx_h

#if (defined(__AVR__))
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

static const byte charTable[] PROGMEM =
{
	// ABCDEFG
	0b01111110, // "0"  offs=0         AAA
	0b00110000, // "1"  offs=1        F   B
	0b01101101, // "2"  offs=2        F   B
	0b01111001, // "3"  offs=3         GGG
	0b00110011, // "4"  offs=4        E   C
	0b01011011, // "5"  offs=5        E   C
	0b01011111, // "6"  offs=6         DDD
	0b01110000, // "7" offs=7
	0b01111111, // "8" offs=8
	0b01111011, // "9" offs=9
	0b01110111, // 'A' offs=10
	0b00011111, // 'b' offs=11
	0b01001110, // 'C' offs=12
	0b00111101, // 'd' offs=13
	0b01001111, // 'E' offs=14
	0b01000111, // 'F' offs=15
	0b01011110, // 'G' offs=16
	0b00110111, // 'H' offs=17
	0b00000110, // 'I' offs=18
	0b00111000, // 'J' offs=19
	0b00110111, // 'K'  offs=20
	0b00001110, // 'L' offs=21
	0b01010101, // 'M'  offs=22
	0b00010101, // 'n' offs=23
	0b01111110, // 'O' offs=24
	0b01100111, // 'P' offs=25
	0b01110011, // 'q' offs=26
	0b00000101, // 'r' offs=27
	0b01011011, // 'S' offs=28
	0b00001111, // 't' offs=29
	0b00111110, // 'U' offs=30
	0b00111110, // 'V'  offs=31
	0b00111111, // 'W'  offs=32
	0b00110111, // 'X'  offs=33
	0b00111011, // 'y' offs=34
	0b01101101, // 'Z'  offs=35
	0b00000000, // ' '  offs=36
	0b00000001, // '-'  offs=37
	0b10000000, // '.'  offs=38
	0b01100011, // '*'  offs=39
	0b00001000, // '_'  offs=40
	0b01111101, //'a' offs=41
	0b00001101, //'c' offs=42
	0b01111011, // "g" offs=43
	0b00010111, // "h" offs=44
	0b00011101, // "o" offs=45
	0b00011100, // "u" offs=46
	0b00001001, // "=" offs=47
	0b01101111, // "e" offs=48
	0b01100101, // "?" offs=49
	0b00011000, // "j" offs=50
	0b01000000, // "^" offs=51
	0b01111000, // ")" offs=52
	0b01001001, // "!" offs=53  (error symbol)
	0b01110101, // "@" offs=54
	0b00100101, // "/" offs=55
	0b00110110, // ":" offs=56
	0b00100010, // '"' offs=57
	0b00100000, // ''' offs=58
	// ABCDEFG

};

class DigitLedDisplay
{
	private:
		int DIN_PIN;
		int CS_PIN;
		int CLK_PIN;
		int _digitLimit;
		void tableChar(byte address, char c);
		void write(byte address, byte data);

	public:
		DigitLedDisplay(int dinPin, int csPin, int clkPin);
		void setBright(int brightness);
		void setDigitLimit(int limit);
		void printString(const char *string, byte startDigit = 0);
		void printMask(byte dgt, byte startDigit = 0);
		void clear();
		void on();
		void off();
};

#endif // DigitLedDisplay.h
