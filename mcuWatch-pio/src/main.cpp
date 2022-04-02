#include <Arduino.h>

#include "config.h"
#include "drawScreen.h"

// Setup **********************************************

void setup()
{
  // Start the serial port
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  Serial.println("Compact TFT Graphics library");
  Serial.println();

  Serial.println("Initializing display ...");
  InitDisplay();
  Serial.println("Clearing display ...");
  ClearDisplay();
  Serial.println("Turning on display ...");
  DisplayOn();
  MoveTo(0, 0);

  TestFrame();
  TestChar();
  TestCircle();
  TestText();
}

void loop()
{

}
