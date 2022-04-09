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

  debugln();
  debugln("Set time with YYMMDDwhhmmssx, ");
  debugln("where YY = Year (ex. 20 for 2020)");
  debugln("      MM = Month (ex. 04 for April)");
  debugln("      DD = Day of month (ex. 09 for 9th)");
  debugln("      w  = Day of week from 1 to 7, 1 = Monday (ex. 4 for Thursday)");
  debugln("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  debugln("      mm = minutes (ex. 02)");
  debugln("      ss = seconds (ex. 42)");
  debugln("End with 'x'");
  debugln("Example for input : 2004094090242x");

  debugln("Delay...");
  debugln();
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

    debugln("UNIX time: ");
    printUNIXtime();

    printTemp();

    debugln();
    
    lastTickMillis = currentMillis;
  }
}
