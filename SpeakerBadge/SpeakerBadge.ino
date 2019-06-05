#include <ESP8266WiFi.h>               // ESP8266 Board support needed. Add https://arduino.esp8266.com/stable/package_esp8266com_index.json to Borad Manager Urls (Preferences)
#include <EEPROM.h>                    // EEPROM memory controller - https://www.arduino.cc/en/Reference/EEPROM
#include <GxEPD2_BW.h>                 // Arduino Display Library for SPI E-Paper Displays - https://github.com/ZinggJM/GxEPD2
#include <Fonts/FreeMonoBold18pt7b.h>  // Adafruit GFX graphics core library - https://github.com/adafruit/Adafruit-GFX-Library

#define WAKE_PIN 16
#define BAUD_SPEED 115200
#define PRINT_LANDSCAPE 3

// Button pins
#define BUTTON1_PIN 10   // 10
#define BUTTON2_PIN 12   // 12

int btn1State = LOW;
int btn2State = LOW;
unsigned long startTime;
unsigned long currentTime;

GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176

void setup()
{
  digitalWrite(WAKE_PIN, HIGH); // immediately set wake pin to HIGH to keep the chip enabled
  Serial.begin(BAUD_SPEED);
  Serial.println();
  Serial.println("Setup...");
  delay(100);
  display.init(BAUD_SPEED);
  
  writeText("Gerald Venzl Code Card", FreeMonoBold18pt7b);

  display.powerOff();
  
  Serial.println("Setup done");

}

void loop()
{
  // Add button watch
}

void writeText(String text, GFXfont font)
{  
  display.setRotation(PRINT_LANDSCAPE);
  display.setFont(&font);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  
  display.setFullWindow();
  
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.println(text);
  }
  while (display.nextPage());
}
