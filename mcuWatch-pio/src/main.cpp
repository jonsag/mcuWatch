#include <Arduino.h>

#include "config.h"
#include "drawScreen.h"
#include "RTCf.h"

// Setup **********************************************>

void setup()
{
  // Start the serial port
  Serial.begin(9600);
  Serial.setTimeout(serialTimeout);
  
  debugln("Hello! ST77xx TFT Test");
  debugln("Compact TFT Graphics library");
  debugln();

  debugln("Initializing display ...");
  InitDisplay();
  debugln("Clearing display ...");
  ClearDisplay();
  debugln("Turning on display ...");
  DisplayOn();
  MoveTo(0, 0);

  debugln("Drawing frame...");
  TestFrame();
  debugln("Drawing large char...");
  TestChar();
  debugln("Drawing circle...");
  TestCircle();
  debugln("Drawing text...");
  TestText();

  debugln("Set time with YYMMDDwHHMMSS, with an 'x' at the end!");
  debugln("Delay...");
  delay(2000);
}

void loop()
{
  currentMillis = millis();

  setTime();

  if (currentMillis - lastTickMillis >= tickInterval)
  {
    i++;

    debugln("Getting time...");
    getTime();

    debug("Raw time: ");
    printRawTime(yearNow, monthNow, dateNow, dOWNow, hourNow, minuteNow, secondNow);

    debug("Formatted time: ");
    printFormattedTime(yearNow, monthNow, dateNow, dOWNow, hourNow, minuteNow, secondNow);

    lastTickMillis = currentMillis;
  }
}
