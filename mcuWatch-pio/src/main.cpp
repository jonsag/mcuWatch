#include <Arduino.h>

#include "config.h"
#include "RTCf.h"
#include "adaScreen.h"

// Setup **********************************************>

void setup()
{
  Serial.begin(9600); // start the serial port
  Serial.setTimeout(serialTimeout);

  Wire.begin();

  Serial.println("mcuWatch");
  Serial.println();

  Serial.println("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  Serial.println("Initialized");
  Serial.println();

  Serial.println("Set time with YYMMDDwhhmmssx, ");
  Serial.println("where YY = Year (ex. 20 for 2020)");
  Serial.println("      MM = Month (ex. 04 for April)");
  Serial.println("      DD = Day of month (ex. 09 for 9th)");
  Serial.println("      w  = Day of week from 1 to 7, 1 = Monday (ex. 4 for Thursday)");
  Serial.println("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  Serial.println("      mm = minutes (ex. 02)");
  Serial.println("      ss = seconds (ex. 42)");
  Serial.println("End with 'x'");
  Serial.println("Example for input : 2004094090242x");
  Serial.println();

  // Serial.println("Running screen test ...");
  // adaScreenTest();
  // Serial.println();

  Serial.println("Clearing screen ...");
  clearScreen();
  Serial.println();

  #if DEBUG
  Serial.println("Drawing help lines ...");
  helpLines();
  Serial.println();
  #endif

  Serial.println("Getting time...");
  now = timeNow();
  prettyPrint(now);
  updateScreen(now);
}

void loop()
{
  currentMillis = millis();

  setTime();

  if (currentMillis - lastCheckMillis >= checkInterval)
  {
    debugln("Getting time...");
    now = timeNow();
    prettyPrint(now);

    updateScreen(now);

    lastCheckMillis = currentMillis;
  }
}
