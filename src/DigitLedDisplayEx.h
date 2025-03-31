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

class DigitLedDisplay
{
	private:
		int DIN_PIN;
		int CS_PIN;
		int CLK_PIN;
		int _digitLimit;
		void write(byte address, byte data);
		static const byte charTable[127] PROGMEM;
		void buildTable()

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
