#include <Arduino.h>

#include "config.h"
#include "RTCf.h"
#include "adaScreen.h"

// Setup **********************************************>

void setup()
{
  // Start the serial port
  Serial.begin(9600);
  Serial.setTimeout(serialTimeout);

  Wire.begin();

  debugln("Hello! ST77xx TFT Test");
  // debugln("Compact TFT Graphics library");
  debugln();

  debugln("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  debugln("Initialized");

  /*
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
  */

  // debugln("Drawing TestChart2 ...");
  // TestChart2();

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

debugln("Running screen test ...");
adaScreenTest();

}

void loop()
{
  currentMillis = millis();

  setTime();

  if (currentMillis - lastTickMillis >= tickInterval)
  {
    i++;
    debugln("Getting time...");
    now = timeNow();
    /*
        debug("RTCtest: ");
        RTCtest(now);

        debug("Padded RTCtest: ");
        paddedRTCtest(now);

        debug("UNIX time: ");
        printUNIXtime(now);

        debug("Temp: ");
        printTemp();

        debug("Day of the week: ");
        debugln(getDayName(now));

        debug("Month: ");
        debugln(getMonthName(now));
    */
    prettyPrint(now);
    debugln();

    updateScreenTime(now);

    lastTickMillis = currentMillis;
  }
}
