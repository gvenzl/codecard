#include <ESP8266WiFi.h>
#include <GxEPD2_BW.h>

#define BAUD_SPEED 115200

// Button pins
#define BUTTONA_PIN 10   // 10
#define BUTTONB_PIN 12   // 12

GxEPD2_BW<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ 2, /*DC=D3*/ 0, /*RST=D4*/ 4, /*BUSY=D2*/ 5)); // 2.7" b/w 264x176

void setup()
{
  Serial.begin(BAUD_SPEED);
  Serial.println("Setup...");

  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH); // immediately set wake pin to HIGH to keep the chip enabled, that way the loop will run endlessly.
  
  // Specify both buttons as input --> PULLUP effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
  pinMode(BUTTONA_PIN, INPUT_PULLUP);
  pinMode(BUTTONB_PIN, INPUT_PULLUP);
  delay(100);

  display.init(BAUD_SPEED);
  display.setRotation(3);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.powerOff();

  pinMode(BUTTONB_PIN, INPUT_PULLUP);
  
  Serial.println("Setup done");
}

void loop() {

  Serial.println("Mode: " + String(HIGH));
  for (int i=0; i<= 16; i++) {
     Serial.println("Pin " + String(i) + " - State: " + String(digitalRead(i)));
   }
   delay(100);

}
