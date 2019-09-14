#include <EEPROM.h>

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(4096);
  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
    EEPROM.commit();
    Serial.println("Written " + String(i));
  }
  EEPROM.end();
  Serial.println("Done");
}

void loop()
{
}
