#include "User_MT05S.h"
#include "User_OLED96x96.h"


bool fnReadMT05S(OneWire ds)
{
  uint8_t scratchpad[9];
  uint8_t timeout = 0;
  Serial.print("Convert T [0x44]: ");
  ds.reset();//Send RESET
  ds.skip();//Send ROM Command-Skip ROM
  ds.write(0x44);//Send Function command- convert T

  //Wait conversion done (Whether to pull down the DQ line during operation can be configured in scratchpad CONFIG0-Bit3- SensorPowerMode)
  while (ds.read_bit() == 0)
  {
    delay(10);
    Serial.print(".");
    timeout++;
    if (timeout > 50)
    {
      return false;
    }
  }
  Serial.print("Conversion Done\n");

  Serial.print("Read Scratchpad [0xBE]: ");
  ds.reset();//Send RESET
  ds.skip();//Send ROM Command-Skip ROM
  ds.write(0xBE);//Send Function command- Read Scratchpad
  for (int i = 0; i < 9; i++) // we need 9 bytes
  {
    scratchpad[i] = ds.read();
  }
  for (int i = 0; i < 9; i++)// we need 9 bytes
  {
    Serial.print(scratchpad[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CrcCalculated=");
  Serial.print(OneWire::crc8(scratchpad, 8), HEX);
  Serial.println();

  if (OneWire::crc8(scratchpad, 8) == scratchpad[8])
  {
    int16_t temperature = makeWord(scratchpad[0], scratchpad[1]);
    int16_t moisture = makeWord(scratchpad[2], scratchpad[3]);
    int16_t conductivity = makeWord(scratchpad[4], scratchpad[5]);
    Serial.print("  TEMP(C) = "); Serial.print(temperature / 100.00);
    Serial.print("  MOISTURE(%) = "); Serial.print(moisture / 100.00);
    Serial.print("  CONDUCTIVITY(ms/cm) = "); Serial.print(conductivity / 1000.00);
    //if ((temperature / 100.00 > 0) && (moisture / 100.00 > 0) && (conductivity / 1000.00 > 0))
    if ((temperature / 100.00 > 0) && (moisture / 100.00 > 0))
    {
      return true;
    }
  }
  else
  {
    Serial.print("CRC ERROR!");
    return false;
  }
}
