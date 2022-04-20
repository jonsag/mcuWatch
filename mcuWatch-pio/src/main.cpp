#include <Arduino.h>

#include "config.h"
#include "RTCf.h"

#if SCREENON
#include "adaScreen.h"
#endif

// Setup **********************************************

void setup()
{
  Serial.begin(9600); // start the serial port
  Serial.setTimeout(serialTimeout);

  Serial.println();
  Serial.println("mcuWatch");
  Serial.println();

  debugMessln("Starting wire ...");
#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E)
  Wire.begin(rtcSDA, rtcSCL);
#else
  Wire.begin();
#endif

  debugMessln("Starting RTC ...");
  rtc.begin();

#if SCREENON
  debugMessln("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  debugMessln("Initialized");
  debugMess("Screen size: ");
  debugMess(tft.width());
  debugMess("x");
  debugMessln(tft.height());
  debugMessln();
#endif

  debugMessln("Set time with YYMMDDwhhmmssx, ");
  debugMessln("where YY = Year (ex. 20 for 2020)");
  debugMessln("      MM = Month (ex. 04 for April)");
  debugMessln("      DD = Day of month (ex. 09 for 9th)");
  debugMessln("      w  = Day of week from 1 to 7, 1 = Monday (ex. 4 for Thursday)");
  debugMessln("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  debugMessln("      mm = minutes (ex. 02)");
  debugMessln("      ss = seconds (ex. 42)");
  debugMessln("End with 'x'");
  debugMessln("Example for input : 2004094090242x");
  debugMessln();

#if SCREENON
  debugMessln("Clearing screen ...");
  clearScreen();
  debugMessln();
#endif

#if DEBUG && SCREENON
  Serial.println("Drawing help lines ...");
  Serial.println();
  helpLines();
#endif

  debugMessln("Getting time...");
  now = timeNow();

  debugMessln("Getting temperature...");
  temperature = tempNow();

  prettyPrint(now, temperature);
  oldEpoch = now;

#if SCREENON
  updateScreen(now, temperature);
#endif
}

// Main **********************************************

void update()
{
  RTCtest(now);

  prettyPrint(now, temperature);

#if SCREENON
  updateScreen(now, temperature);
#endif
}

void getData()
{
  debugMessln("Getting time...");
  now = timeNow();
  debugMessln("Getting temperature...");
  temperature = tempNow();
}

void loop()
{
  currentMillis = millis();

  setTime();

#if DEBUG
  if (currentMillis - lastCheckMillis >= checkInterval)
  {
    getData();
    update();
    lastCheckMillis = currentMillis;
  }
#else
  getData();
  if (now.getEpoch() != oldEpoch.getEpoch())
  {
    update();
    oldEpoch = now;
  }
#endif
}
