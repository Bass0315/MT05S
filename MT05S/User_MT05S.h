//
#ifndef USER_MT05S_H
#define USER_MT05S_H

/*
 * https://github.com/INFWIN/mt05s-demo
 * Attention:Define a 1-Wire signal pin (a 2.0K~5.1K pull-up resistor is necessary)
 */

#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <OneWire.h>

void MT05S_Init(void);
bool fnReadMT05S(OneWire ds);




#endif
