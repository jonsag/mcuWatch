#include <Arduino.h>

#include "config.h"
#include "RTCf.h"
#include "adaScreen.h"

// Setup **********************************************>

void setup()
{
  Serial.begin(57600); // start the serial port
  Serial.setTimeout(serialTimeout);

  debugln();
  Serial.println("mcuWatch");
  debugln();

  debugln("Starting wire ...");
#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E)
  Wire.begin(rtcSDA, rtcSCL);
#else
  Wire.begin();
#endif

  debugln("Starting RTC ...");
  rtc.begin();

  debugln("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  debugln("Initialized");
  debug("Screen size: ");
  debug(tft.width());
  debug("x");
  debugln(tft.height());
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
  debugln();

  debugln("Clearing screen ...");
  clearScreen();
  debugln();

#if DEBUG
  Serial.println("Drawing help lines ...");
  Serial.println();
#endif

  helpLines();

  debugln("Getting time...");
  now = timeNow();
  debugln("Getting temp...");
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
    debugln("Getting temp...");
    temperature = tempNow();

    prettyPrint(now, temperature);

    updateScreen(now, temperature);

    lastCheckMillis = currentMillis;
  }
}
