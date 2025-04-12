#include "DigitLedDisplayEx.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR 10
#define SCANLIMIT_ADDR 11
#define SHUTDOWN_ADDR 12
#define DISPLAYTEST_ADDR 15

DigitLedDisplay::DigitLedDisplay(int dinPin, int csPin, int clkPin)
{
	_numDigits = 4; // Default to 4 digits
	DIN_PIN = dinPin;
	CS_PIN = csPin;
	CLK_PIN = clkPin;

	pinMode(DIN_PIN, OUTPUT);
	pinMode(CS_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);
}

DigitLedDisplay::DigitLedDisplay(int numDigits, int dinPin, int csPin, int clkPin) : 
	DigitLedDisplay(dinPin, csPin, clkPin)
{
	_numDigits = numDigits;
	setDigitLimit(numDigits);
}

void DigitLedDisplay::setBright(int brightness)
{
	if(brightness >= 0 && brightness < 16)
		write(BRIGHTNESS_ADDR, brightness);
}

void DigitLedDisplay::setDigitLimit(int limit)
{
	_numDigits = limit;

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
	for(int i = 0; i < _numDigits; i++)
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
	int slenCorr=slen;
	for(int i = 0; i < slen; i++)
		if(string[i] == '.') // OCIO - dot is not a char, so we need to skip it
			slenCorr--;
	

	int addr = slenCorr + startDigit;
	int corr=0;

	for(int i = 0; i < slen; i++)
	{
		if((i < slen - 1) && string[i+1]=='.') // OCIO - dot is not a char, so we need to skip it
		{
			write(addr - i+corr, 0x80|pgm_read_word_near(charTable + string[i]));  //OCIO - BE CAREFUL to use only plain ascii chars, or add an '& 0x7f'
			i++;
			corr++;
		} else
			write(addr - i+corr, pgm_read_word_near(charTable + string[i]));  //OCIO - BE CAREFUL to use only plain ascii chars, or add an '& 0x7f'
	}
}

void DigitLedDisplay::printMask(byte dgt, byte startDigit)
{
	write(startDigit, dgt);
}

void DigitLedDisplay::printDigit(long number, byte startDigit) 
{
	char s[50];
	sprintf(s, "%ld", number);
	printString(s, startDigit);
}
