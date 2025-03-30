
/* Include DigitLedDisplay Library */
#include "DigitLedDisplayEx.h"

/* Arduino Pin to Display Pin
   7 to DIN,
   6 to CS,
   5 to CLK */
DigitLedDisplay ld = DigitLedDisplay(7, 6, 5);

void setup() {

  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);

}

void loop() 
{

  ld.printString("01234567");
  delay(2500);
  ld.clear();

  ld.printString("89 .23");
  delay(2500);
  ld.clear();
  ld.printString("AaBbCcDd");
  delay(2500);
  ld.clear();
  ld.printString("EeFfGgHh");
  delay(2500);
  ld.clear();
  ld.printString("IiJjKkLl");
  delay(2500);
  ld.clear();
  ld.printString("MmNnOoPp");
  delay(2500);
  ld.clear();
  ld.printString("QqRrSsTt");
  delay(2500);
  ld.clear();
  ld.printString("UuVvXxYy");
  delay(2500);
  ld.clear();
  ld.printString("Zz -.*_");
  delay(2500);
  ld.clear();

  ld.printString("The XOR");
  delay(1500);
  ld.clear();

  ld.printString(".23");
  delay(1500);
  ld.clear();

}