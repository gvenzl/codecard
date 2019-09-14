#include <EEPROM.h>

int value;

void setup()
{
  Serial.begin(115200);

  EEPROM.begin(4096);
  Serial.println("EEPROM length: " + String(EEPROM.length()));
  
  for (int i = 0; i < EEPROM.length(); i++)
  {
    value = EEPROM.read(i);

    Serial.print(i);
    Serial.print("\t");
    Serial.print(value);
    Serial.println();
  }
}

void loop()
{
  
}
