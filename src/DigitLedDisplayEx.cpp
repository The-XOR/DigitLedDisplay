#include "DigitLedDisplayEx.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR 10
#define SCANLIMIT_ADDR 11
#define SHUTDOWN_ADDR 12
#define DISPLAYTEST_ADDR 15

DigitLedDisplay::DigitLedDisplay(int dinPin, int csPin, int clkPin)
{
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
	{
		write(1+i, 0);
	}
}

void DigitLedDisplay::tableChar(byte address, char c)
{
	int offs;
	switch (c)
	{
		case '0': 
			offs = 0;
			break;
		case '1':
			offs = 1;
			break;
		case '2':
			offs = 2;
			break;
		case '3':
			offs = 3;
			break;
		case '4':
			offs = 4;
			break;
		case '5':
			offs = 5;
			break;
		case '6':
			offs = 6;
			break;
		case '7':
			offs = 7;
			break;
		case '8':
			offs = 8;
			break;
		case '9':
			offs = 9;
			break;
		case 'A':
			offs = 10;
			break;
		case 'a':
			offs = 41;
			break;
		case 'B':
		case 'b':
			offs = 11;
			break;
		case 'c':
			offs = 42;
			break;
		case '(':
		case '[':
		case 'C':
			offs = 12;
			break;
		case 'D':
		case 'd':
			offs = 13;
			break;
		case 'e':
			offs = 48;
			break;
		case 'E':
			offs = 14;
			break;
		case 'f':
		case 'F':
			offs = 15;
			break;
		case 'g':
			offs = 43;
			break;
		case 'G':
			offs = 16;
			break;
		case 'h':
			offs = 44;
			break;
		case 'H':
			offs = 17;
			break;
		case 'i':
		case 'I':
			offs = 18;
			break;
		case 'j':
			offs = 50;
			break;
		case 'J':
			offs = 19;
			break;
		case 'k':
		case 'K':
			offs = 20;
			break;
		case 'l':
		case 'L':
			offs = 21;
			break;
		case 'm':
		case 'M':
			offs = 22;
			break;
		case 'N':
		case 'n':
			offs = 23;
			break;
		case 'o':
			offs = 45;
			break;
		case 'O':
			offs = 24;
			break;
		case 'p':
		case 'P':
			offs = 25;
			break;
		case 'Q':
		case 'q':
			offs = 26;
			break;
		case 'R':
		case 'r':
			offs = 27;
			break;
		case 's':
		case 'S':
			offs = 28;
			break;
		case 'T':
		case 't':
			offs = 29;
			break;
		case 'u':
			offs = 46;
			break;
		case 'U':
			offs = 30;
			break;
		case 'v':
		case 'V':
			offs = 31;
			break;
		case 'w':
		case 'W':
			offs = 32;
			break;
		case 'x':
		case 'X':
			offs = 33;
			break;
		case 'Y':
		case 'y':
			offs = 34;
			break;
		case 'z':
		case 'Z':
			offs = 45;
			break;
		case ' ':
			offs = 36;
			break;
		case '-':
			offs = 37;
			break;
		case '.':
			offs = 38;
			break;
		case '*':
			offs = 39;
			break;
		case '_':
			offs = 40;
			break;
		case '=':
			offs = 47;
			break;
		case '?':
			offs = 49;
			break;
		case '^':
			offs = 51;
			break;
		case ']':
		case ')':
			offs = 52;
			break;
		case '!':
			offs = 53;
			break; // error symbol
		case '@':
			offs = 54;
			break;
		case '/':
			offs = 55;
			break;
		case ':':
			offs = 56;
			break;
		case '"':
			offs = 57;
			break;
		case '\'':
			offs = 58;
			break;
		default:
			offs = 53;
			break;
	}
	write(address, pgm_read_word_near(charTable + offs));
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
	for (int i = 0; i < slen; i++)
		tableChar(slen - i + startDigit, string[i]);
}

void DigitLedDisplay::printMask(byte dgt, byte startDigit)
{
	write(address, dgt);
}
