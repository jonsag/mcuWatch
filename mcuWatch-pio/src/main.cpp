#include <Arduino.h>

#include "config.h"
#include "RTCf.h"

#include "screenDrawf.h"
#include "webServer.h"
#include "NTPf.h"
#include "EEPROMf.h"

// Setup##############################****************

void setup()
{
  // ############################## start serial
#if DEBUG || INFO
  Serial.begin(serialSpeed); // start the serial port

  Serial.setTimeout(serialTimeout);

  debugMessln();
  debugMessln("mcuWatch");
  debugMessln();

#endif // DEBUG || INFO

  // ############################## start wire
  debugMessln("Starting wire ...");
  Wire.begin();

  debugMessln();

  // ############################## start screen
  debugMessln("Initializing display ...");

  myScreen.initR(INITR_BLACKTAB);

  debugMessln("Initialized");
  debugMess("Screen size: ");
  debugMess(myScreen.width());
  debugMess("x");
  debugMessln(myScreen.height());
  debugMessln();

  clearScreen();

  // ############################## start RTC
  debugMessln("Starting RTC ...");

  printStartMess("RTC ...", 1);

  if (!rtc.begin())
  {
    debugMessln("Couldn't find RTC");
  }
  else
  {
    debugMessln("RTC found");
  }

  debugMessln();

  clearScreen();

  // ############################## start and connect wifi
  debugMessln("Starting and connecting wifi ...");

  printStartMess("Connecting ...", 1);

  startTime = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED && (millis() - startTime) <= wifiTimeout) // wait for connection
  {
    debugMess(".");
    delay(500);
    // static uint16_t counter = 0;
    // counter++;
    // if (counter % 30 == 0)
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  debugMessln();

  clearScreen();

  if (WiFi.status() != WL_CONNECTED)
  {
    infoMessln("ERROR: Could not connect");
  }
  else
  {
    infoMess("Connected to ");
    infoMessln(ssid);
    infoMess("IP address: ");
    infoMessln(WiFi.localIP());

    printIP();
    delay(2000);
    clearScreen();
  }
  infoMessln();

  // ############################## start web server
  startWebServer();

  currentMillis = millis();

  // ############################## start NTP client
  debugMessln("Starting NTP client ...");

  printStartMess("Starting NTP ...", 1);

  timeClient.begin();                   // initialize a NTP client to get time
  timeClient.setTimeOffset(timeOffset); // set offset time

  // getNetworkTime();

  clearScreen();

  lastNTPCheckMillis = currentMillis;

  debugMessln();

  getDtNTP();

  debugMessln();

  // ############################## show info
  infoMessln("Set time with YYMMDDwhhmmssx, ");
  infoMessln("where YY = Year (ex. 20 for 2020)");
  infoMessln("      MM = Month (ex. 04 for April)");
  infoMessln("      DD = Day of month (ex. 09 for 9th)");
  infoMessln("      w  = Day of week from 1 to 7, 1 = Monday (ex. 4 for Thursday)");
  infoMessln("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  infoMessln("      mm = minutes (ex. 02)");
  infoMessln("      ss = seconds (ex. 42)");
  infoMessln("End with 'x'");
  infoMessln("Example for input : 2004094090242x");
  infoMessln();

  // ############################## set up screen
  debugMessln("Clearing screen ...");
  clearScreen();

  debugMessln();

#if DEBUG
  debugMessln("Drawing help lines ...");
  debugMessln();
  helpLines();

  debugMessln();

#endif // DEBUG

  // ############################## get time and temp from RTC
  debugMessln("Getting time...");
  now = RTCTimeNow();

  debugMessln("Getting temperature...");
  temperature = RTCTempNow();

  prettyPrint(now, temperature);
  oldEpoch = now;

  lastRTCCheckMillis = currentMillis;

  updateScreen(now, temperature);

  // ############################## finished with setup
  debugMessln("Start finished!");
  debugMessln("Now entering main loop ...");
  debugMessln();
}

// ############################## Main

void updateOutput()
{
  RTCtest(now);

  prettyPrint(now, temperature);

  updateScreen(now, temperature);
}

void getRTCData()
{
  debugMessln("Getting time...");
  now = RTCTimeNow();

  debugMessln("Getting temperature...");
  temperature = RTCTempNow();
}

void loop()
{
  currentMillis = millis();

  setTime(); // check for keyboard input

  server.handleClient();
  MDNS.update();

// ############################## if in debug mode, only check every interval
#if DEBUG
  if (currentMillis - lastRTCCheckMillis >= RTCCheckInterval)
  {
    getRTCData();
    updateOutput();
    lastRTCCheckMillis = currentMillis;
  }

// ############################## otherwise check every time, then see if a second have passed
#else
  getRTCData();
  if (now.getEpoch() != oldEpoch.getEpoch())
  {
    updateOutput();
    oldEpoch = now;
  }

#endif

  // ############################## update from NTP
  if (currentMillis - lastNTPCheckMillis >= NTPCheckInterval)
  {
      if (WiFi.status() != WL_CONNECTED)
  {
    drawText(myScreen.width() / XSplits * wifiStatusXPos - wifiStatusString.length() / 2.0 * pixX * wifiStatusSize, // x
             myScreen.height() / YSplits * wifiStatusYPos,                                        // y
             wifiStatusSize,                                                                                 // size
             wifiStatusDownCol,                                                                              // colour
             wifiStatusString);
  }
  else
  {
    drawText(myScreen.width() / XSplits * wifiStatusXPos - wifiStatusString.length() / 2.0 * pixX * wifiStatusSize, // x
             myScreen.height() / YSplits * wifiStatusYPos,                                                   // y
             wifiStatusSize,                                                                                 // size
             wifiStatusOKCol,                                                                                // colour
             wifiStatusString);
  }
  
    if (WiFi.status() != WL_CONNECTED)
    {
      debugMessln("Not connected");
    }
    else
    {
      checkNetworkTime();
    }

    lastNTPCheckMillis = currentMillis;
  }
}
