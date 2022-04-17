#include <Arduino.h>

#include "config.h"
#include "RTCf.h"
#include "adaScreen.h"

// Setup **********************************************>

void setup()
{
  Serial.begin(57600); // start the serial port
  Serial.setTimeout(serialTimeout);

  Serial.println();
  Serial.println("mcuWatch");
  Serial.println();

  Serial.println("Starting wire ...");
  Wire.begin();

  Serial.println("Starting RTC ...");
  rtc.begin();

  Serial.println("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  Serial.println("Initialized");
  Serial.print("Screen size: ");
  Serial.print(tft.width());
  Serial.print("x");
  Serial.println(tft.height());
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
  Serial.println();
#endif

  helpLines();

  Serial.println("Getting time...");
  now = timeNow();
  Serial.println("Getting temp...");
  temperature = tempNow();
  prettyPrint(now, temperature);
  updateScreen(now, temperature);
}

void loop()
{
  currentMillis = millis();

  setTime();

  if (currentMillis - lastCheckMillis >= checkInterval)
  {
    debugln("Getting time...");
    now = timeNow();
    Serial.println("Getting temp...");
    temperature = tempNow();

    prettyPrint(now, temperature);

    updateScreen(now, temperature);

    lastCheckMillis = currentMillis;
  }
}
