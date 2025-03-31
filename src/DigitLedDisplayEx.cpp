#include "DigitLedDisplayEx.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR 10
#define SCANLIMIT_ADDR 11
#define SHUTDOWN_ADDR 12
#define DISPLAYTEST_ADDR 15

DigitLedDisplay::DigitLedDisplay(int dinPin, int csPin, int clkPin)
{
	buildTable();
	_digitLimit = 4; // Default to 4 digits
	DIN_PIN = dinPin;
	CS_PIN = csPin;
	CLK_PIN = clkPin;

	pinMode(DIN_PIN, OUTPUT);
	pinMode(CS_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);
}

void DigitLedDisplay::setBright(int brightness)
{
	if(brightness >= 0 && brightness < 16)
		write(BRIGHTNESS_ADDR, brightness);
}

void DigitLedDisplay::setDigitLimit(int limit)
{
	_digitLimit = limit;

	write(DISPLAYTEST_ADDR, 0);
	write(SCANLIMIT_ADDR, limit - 1);

	// 0: Register Format
	// 255: Code B Font (0xff)
	write(DECODEMODE_ADDR, 0);
	clear();
	write(SHUTDOWN_ADDR, 1);
}

void DigitLedDisplay::on()
{
	write(SHUTDOWN_ADDR, 0x01);
}

void DigitLedDisplay::off()
{
	write(SHUTDOWN_ADDR, 0x00);
}

void DigitLedDisplay::clear()
{
	for(int i = 0; i < _digitLimit; i++)
		write(1+i, 0);
}

void DigitLedDisplay::write(volatile byte address, volatile byte data)
{
	digitalWrite(CS_PIN, LOW);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address);
	shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
	digitalWrite(CS_PIN, HIGH);
}

void DigitLedDisplay::printString(const char *string, byte startDigit)
{
	int slen = strlen(string);
	int addr = slen + startDigit;
	for(int i = 0; i < slen; i++)
		write(addr - i, pgm_read_word_near(charTable + string[i]));  //OCIO - BE CAREFUL to use only plain ascii chars, or add an '& 0x7f'
}

void DigitLedDisplay::printMask(byte dgt, byte startDigit)
{
	write(address, dgt);
}

void DigitLedDisplay::buildTable()
{
	const byte errorSymbol = 0b01001001; // error symbol
	memset(charTable, errorSymbol, sizeof(charTable));
	charTable['!'] = errorSymbol; //tanto per essere tassonomici  
	//                  ABCDEFG
	charTable[' '] = 0b00000000;  
	charTable['0'] = 0b01111110; 
	charTable['1'] = 0b00110000; 
	charTable['2'] = 0b01101101; 
	charTable['3'] = 0b01111001; 
	charTable['4'] = 0b00110011; 
	charTable['5'] = 0b01011011; 
	charTable['6'] = 0b01011111; 
	charTable['7'] = 0b01110000; 
	charTable['8'] = 0b01111111;  
	charTable['9'] = 0b01111011;  
	charTable['A'] = 0b01110111;  
	charTable['a'] = 0b01111101;  
	charTable['B'] = 0b00011111;  
	charTable['b'] = 0b00011111;  
	charTable['C'] = 0b01001110;  
	charTable['c'] = 0b00001101;  
	charTable['D'] = 0b00111101;  
	charTable['d'] = 0b00111101;  
	charTable['E'] = 0b01001111;  
	charTable['e'] = 0b01101111;  
	charTable['F'] = 0b01000111;  
	charTable['f'] = 0b01000111;  
	charTable['G'] = 0b01011110;  
	charTable['g'] = 0b01111011;  
	charTable['H'] = 0b00110111;  
	charTable['h'] = 0b00010111;  
	charTable['I'] = 0b00000110;  
	charTable['i'] = 0b00000110;  
	charTable['J'] = 0b00111000;  
	charTable['j'] = 0b00011000;  
	charTable['K'] = 0b00110111;  
	charTable['k'] = 0b00110111;  
	charTable['L'] = 0b00001110;  
	charTable['l'] = 0b00001110;  
	charTable['M'] = 0b01010101;  
	charTable['m'] = 0b01010101;  
	charTable['N'] = 0b00010101;  
	charTable['n'] = 0b00010101;  
	charTable['O'] = 0b01111110;  
	charTable['o'] = 0b00011101;  
	charTable['P'] = 0b01100111;  
	charTable['p'] = 0b01100111;  
	charTable['Q'] = 0b01110011;  
	charTable['q'] = 0b01110011;  
	charTable['R'] = 0b00000101;  
	charTable['r'] = 0b00000101;  
	charTable['S'] = 0b01011011;  
	charTable['s'] = 0b01011011;  
	charTable['T'] = 0b00001111;  
	charTable['t'] = 0b00001111;  
	charTable['U'] = 0b00111110;  
	charTable['u'] = 0b00011100;  
	charTable['V'] = 0b00111110;  
	charTable['v'] = 0b00111110;  
	charTable['W'] = 0b00111111;  
	charTable['w'] = 0b00111111;  
	charTable['X'] = 0b00110111;  
	charTable['x'] = 0b00110111;  
	charTable['Y'] = 0b00111011;  
	charTable['y'] = 0b00111011;  
	charTable['Z'] = 0b01101101;  
	charTable['z'] = 0b01101101;  
	charTable['('] = 0b01001110;  
	charTable['['] = 0b01001110;  
	charTable['-'] = 0b00000001;  
	charTable['.'] = 0b10000000;  // dot led on!
	charTable['*'] = 0b01100011;  
	charTable['_'] = 0b00001000;  
	charTable['='] = 0b00001001;  
	charTable['?'] = 0b01100101;  
	charTable['^'] = 0b01000000;  
	charTable[')'] = 0b01111000;  
	charTable[']'] = 0b01111000;  
	charTable['@'] = 0b01110101;  
	charTable['/'] = 0b00100101;  
	charTable['\\'] =0b00010011;  
	charTable[':'] = 0b00110110;  
	charTable['"'] = 0b00100010;  
	charTable['\''] =0b00100000; 
	//                  ABCDEFG
}
