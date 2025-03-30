DigitLedDisplayEx
==========
DigitLedDisplay is an [Arduino](http://arduino.cc) library for MAX7219 and MAX7221 8 bit 7-segment digital LED display module drivers.

Install
-------
Copy DigitLedDisplayEx library to -> arduino\libraries\

-------
*Start From Digit: Default Value Zero*\
`digitLedDisplay.printString("Try");`\

*Start From Digit 4*\
`digitLedDisplay.printString("Try", 4);`\

## Quickstart

```c
#include <DigitLedDisplayEx.h>

// initialize with pin numbers for data, cs, and clock
DigitLedDisplay ld = DigitLedDisplay(7, 6, 5);

void setup() {
  ld.setBright(15); // range is 0-15
  ld.setDigitLimit(8);
}

long i = 12345678;

void loop() {
  ld.printString("Hello");
  delay(10900);
  ld.clear();
  delay(1000);
}
```

For additional features see [Digit7SegmentExDemo.ino](examples/Digit7SegmentExDemo/Digit7SegmenExtDemo.ino)
