#include <Arduino.h>

#include "config.h"
#include "RTCf.h"

#if TFTSCREEN || OLEDSCREEN
#include "screenDrawf.h"

#endif

#if WEBSERVER
#include "webServer.h"

#endif

#if NTP
#include "NTPf.h"

#endif

// Setup##############################****************

void setup()
{
  // ############################## start serial
#if DEBUG || INFO
#if defined(ARDUINO_ESP8266_ESP01)
  Serial.begin(serialSpeed, SERIAL_8N1, SERIAL_TX_ONLY);

#else
  Serial.begin(serialSpeed); // start the serial port

#endif

  Serial.setTimeout(serialTimeout);

  debugMessln();
  debugMessln("mcuWatch");
  debugMessln();

#endif // DEBUG || INFO

  // ############################## start wire
  debugMessln("Starting wire ...");
#if defined(ARDUINO_ESP8266_ESP01)
  Wire.begin(i2cSDA, i2cSCK);

#else
  Wire.begin();

#endif // defined(ARDUINO_ESP8266_ESP01)
  debugMessln();

// ############################## start screen
#if TFTSCREEN
  debugMessln("Initializing display ...");

  myScreen.initR(INITR_BLACKTAB);

  debugMessln("Initialized");
  debugMess("Screen size: ");
  debugMess(myScreen.width());
  debugMess("x");
  debugMessln(myScreen.height());
  debugMessln();

  clearScreen();

#elif OLEDSCREEN
  debugMessln("Initializing display ...");

  if (!myScreen.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    debugMessln("SSD1306 allocation failed");
    for (;;)
      ; // Don't proceed, loop forever
  }

  debugMessln("Initialized");
  debugMess("Screen size: ");
  debugMess(myScreen.width());
  debugMess("x");
  debugMessln(myScreen.height());
  debugMessln();

  debugMessln("Splash screen ...");
  myScreen.display();

  debugMessln();

  delay(500);    // pause for 2 seconds
  clearScreen(); // clear the buffer

#endif // TFTSCREEN or OLEDSCREEN

  // ############################## start RTC
  debugMessln("Starting RTC ...");

#if TFTSCREEN || OLEDSCREEN
  printStartMess("RTC ...", 1);

#endif

  if (!rtc.begin())
  {
    debugMessln("Couldn't find RTC");
  }
  else
  {
    debugMessln("RTC found");
  }

  debugMessln();

#if TFTSCREEN || OLEDSCREEN
  clearScreen();

#endif

// ############################## start and connect wifi
#if WEBSERVER || RTC
  debugMessln("Starting and connecting wifi ...");

#if TFTSCREEN || OLEDSCREEN
  printStartMess("Connecting ...", 1);

#endif // TFTSCREEN || OLEDSCREEN

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
  debugMessln();

#if TFTSCREEN || OLEDSCREEN
  clearScreen();

#endif // TFTSCREEN || OLEDSCREEN

  if (WiFi.status() == WL_CONNECTED)
  {
    infoMess("Connected to ");
    infoMessln(ssid);
    infoMess("IP address: ");
    infoMessln(WiFi.localIP());
  }

#if TFTSCREEN || OLEDSCREEN
  printIP();
  delay(2000);
  clearScreen();

#endif // TFTSCREEN || OLEDSCREEN

#endif // WEBSERVER || RTC

// ############################## start web server
#if WEBSERVER
#if TFTSCREEN || OLEDSCREEN
  printStartMess("Web server ...", 1);

#endif // TFTSCREEN || OLEDSCREEN

  // debugMessln("Starting MDNS responder ...");
  if (MDNS.begin("esp8266"))
  {
    debugMessln("MDNS responder started");
  }

  debugMessln("Initializing web server ...");

  server.on("/", handleRoot);
  server.on("/temp", showTemps);
  server.on("/test.svg", drawGraph);
  server.on("/inline", []()
            { server.send(200, "text/plain", "this works as well"); });
  server.on("/gif", []()
            {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };

    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored)); });

  // Hook examples##############################************************
  server.addHook([](const String &method,
                    const String &url,
                    WiFiClient *client,
                    ESP8266WebServer::ContentTypeFunction contentType)
                 {
    (void)method;      // GET, PUT, ...
    (void)url;         // example: /root/myfile.html
    (void)client;      // the webserver tcp client connection
    (void)contentType; // contentType(".html") => "text/html"
    Serial.printf("A useless web hook has passed\n");
    Serial.printf("(this hook is in 0x%08x area (401x=IRAM 402x=FLASH))\n", esp_get_program_counter());
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });

  server.addHook([](const String &,
                    const String &url,
                    WiFiClient *,
                    ESP8266WebServer::ContentTypeFunction)
                 {

    if (url.startsWith("/fail")) {
      Serial.printf("An always failing web hook has been triggered\n");
      return ESP8266WebServer::CLIENT_MUST_STOP;
    }

    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });

  server.addHook([](const String &,
                    const String &url,
                    WiFiClient *client,
                    ESP8266WebServer::ContentTypeFunction)
                 {

      if (url.startsWith("/dump"))
      {
        Serial.printf("The dumper web hook is on the run\n");

      // Here the request is not interpreted, so we cannot for sure
      // swallow the exact amount matching the full request+content,
      // hence the tcp connection cannot be handled anymore by the
      // webserver.

#ifdef STREAMSEND_API
      // we are lucky
      client->sendAll(Serial, 500);

#else
      auto last = millis();
      while ((millis() - last) < 500) {
        char buf[32];
        size_t len = client->read((uint8_t*)buf, sizeof(buf));
        if (len > 0) {
          Serial.printf("(<%d> chars)", (int)len);
          Serial.write(buf, len);
          last = millis();
        }
      }

#endif

      // Two choices: return MUST STOP and webserver will close it
      //                       (we already have the example with '/fail' hook)
      // or                  IS GIVEN and webserver will forget it
      // trying with IS GIVEN and storing it on a dumb WiFiClient.
      // check the client connection: it should not immediately be closed
      // (make another '/dump' one to close the first)
      Serial.printf("\nTelling server to forget this connection\n");
      static WiFiClient forgetme = *client; // stop previous one if present and transfer client refcounter
      return ESP8266WebServer::CLIENT_IS_GIVEN;
  }

  return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE; });

  // Hook examples##############################************************
  server.onNotFound(handleNotFound);

  debugMessln("Starting web server ...");

  server.begin();

#if TFTSCREEN || OLEDSCREEN
  clearScreen();

#endif

  debugMessln();

#endif // WEBSERVER>

  currentMillis = millis();

// ############################## start NTP client
#if NTP
  debugMessln("Starting NTP client ...");

#if TFTSCREEN || OLEDSCREEN
  printStartMess("NTP ...", 1);

#endif

  timeClient.begin();                   // initialize a NTP client to get time
  timeClient.setTimeOffset(timeOffset); // set offset time

  getNetworkTime();

#if TFTSCREEN || OLEDSCREEN
  clearScreen();

#endif // NTP

  lastNTPCheckMillis = currentMillis;

  debugMessln();

#endif // NTP

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

#if TFTSCREEN || OLEDSCREEN
  debugMessln("Clearing screen ...");
  clearScreen();

  debugMessln();

#endif // TFTSCREEN || OLEDSCREEN

#if DEBUG && (TFTSCREEN || OLEDSCREEN)
  debugMessln("Drawing help lines ...");
  debugMessln();
  helpLines();

  debugMessln();

#endif // DEBUG && (TFTSCREEN || OLEDSCREEN)

  debugMessln("Getting time...");
  now = RTCTimeNow();

  debugMessln("Getting temperature...");
  temperature = RTCTempNow();

  prettyPrint(now, temperature);
  oldEpoch = now;

  lastRTCCheckMillis = currentMillis;

#if TFTSCREEN || OLEDSCREEN
  updateScreen(now, temperature);

#endif // TFTSCREEN || OLEDSCREEN

  debugMessln("Start finished!");
  debugMessln("Now entering main loop ...");
  debugMessln();
}

// ############################## Main

void updateOutput()
{
  RTCtest(now);

  prettyPrint(now, temperature);

#if TFTSCREEN || OLEDSCREEN
  updateScreen(now, temperature);

#endif
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

#if WEBSERVER
  server.handleClient();
  MDNS.update();

#endif

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
    getNetworkTime();

    lastNTPCheckMillis = currentMillis;
  }
}
