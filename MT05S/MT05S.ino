#include "User_MT05S.h"
#include "User_OLED96x96.h"


uint8_t OneWirePin[] = {2, 3, 4, 5, 6, 7, 8};

void setup(void)
{
  char strBuffer[20];
  Serial.begin(9600);
  OLED96x96_Init();
  while (!Serial);
  for (uint8_t i = 0; i < 7; i++)
  {
    Serial.print(String(i));
    OneWire MT05S(OneWirePin[i]);
    if (fnReadMT05S(MT05S))
    {
      sprintf(strBuffer, "Ch: %d OK.", i+1);
      OLED_Write(0, i * 2, strBuffer);
    }
    else
    {
      sprintf(strBuffer, "Ch: %d ER.", i+1);
      OLED_Write(0, i * 2, strBuffer);
    }
    Serial.print("\n");
  }
}


void loop(void)
{
  delay(5000);
}
