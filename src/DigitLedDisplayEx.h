	#ifndef DigitLedDisplay_h
#define DigitLedDisplay_h

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

static const byte charTable [] PROGMEM = {
	// ABCDEFG		
	0b01111110, // "0"          AAA
	0b00110000, // "1"         F   B
	0b01101101, // "2"         F   B
	0b01111001, // "3"          GGG
	0b00110011, // "4"         E   C
	0b01011011, // "5"         E   C
	0b01011111, // "6"          DDD
	0b01110000, // "7"
	0b01111111, // "8"
	0b01111011, // "9"
	0b01110111, // 'A'
	0b00011111, // 'b'
	0b01001110, // 'C'
	0b00111101, // 'd'
	0b01001111, // 'E'
	0b01000111, // 'F'
	0b01011110, // 'G'
	0b00110111, // 'H'
	0b00000110, // 'I'
	0b00111000, // 'J'
	0b00110111, // 'K'  
	0b00001110, // 'L'
	0b01010101, // 'M'  
	0b00010101, // 'n'
	0b01111110, // 'O'
	0b01100111, // 'P'
	0b01110011, // 'q'
	0b00000101, // 'r'
	0b01011011, // 'S'
	0b00001111, // 't'
	0b00111110, // 'U'
	0b00111110, // 'V'  
	0b00111110, // 'W'  
	0b00110111, // 'X'  
	0b00111011, // 'y'
	0b01101101, // 'Z'  
	0b00000000, // ' '  
	0b00000001, // '-'  
	0b10000000, // '.'  
	0b01100011, // '*'  
	0b00001000 // '_'  

}; 

class DigitLedDisplay
{
	private:
		int DIN_PIN;
		int CS_PIN;
		int CLK_PIN;
		int _digitLimit;
		void tableChar(byte address, char c);	
	public:
		DigitLedDisplay(int dinPin, int csPin, int clkPin);
		void setBright(int brightness);
		void setDigitLimit(int limit);
		void printString(const char *string, byte startDigit = 0);
		void write(byte address, byte data);
		void clear();
		void on();
		void off();		
};

#endif	//DigitLedDisplay.h
