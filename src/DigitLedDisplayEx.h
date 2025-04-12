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

#include "charTable.h"

class DigitLedDisplay
{
	private:
		int DIN_PIN;
		int CS_PIN;
		int CLK_PIN;
		int _numDigits;
		void write(byte address, byte data);

	public:
		DigitLedDisplay(int numDigits, int dinPin, int csPin, int clkPin);
		DigitLedDisplay(int dinPin, int csPin, int clkPin);
		void setBright(int brightness);
		void setDigitLimit(int limit);
		void printString(const char *string, byte startDigit = 0);
		void printMask(byte dgt, byte startDigit = 0);
		void printDigit(long number, byte startDigit = 0);
		void clear();
		void on();
		void off();
};

#endif // DigitLedDisplay.h
