#include <Arduino.h>

#include "config.h"
#include "RTCf.h"

#if TFTSCREEN
#include "tftScreen.h"
#endif

#if WEBSERVER
#include "webServer.h"
#endif

// Setup **********************************************

void setup()
{
#if DEBUG || INFO
  Serial.begin(9600); // start the serial port
  Serial.setTimeout(serialTimeout);

  Serial.println();
  Serial.println("mcuWatch");
  Serial.println();
#endif

  debugMessln("Starting wire ...");
#if defined(ARDUINO_ESP8266_ESP01)
  Wire.begin(i2cSDA, i2cSCK);
#else
  Wire.begin();
#endif
  debugMessln();

  debugMessln("Starting RTC ...");
  rtc.begin();
  debugMessln();

#if TFTSCREEN
  debugMessln("Initializing display ...");
  tft.initR(INITR_BLACKTAB);
  debugMessln("Initialized");
  debugMess("Screen size: ");
  debugMess(tft.width());
  debugMess("x");
  debugMessln(tft.height());
  debugMessln();
#elif OLEDSCREEN
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    debugMessln("SSD1306 allocation failed");
    for (;;)
      ; // Don't proceed, loop forever
  }
  debugMessln("Splash screen ...");
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
#endif

#if WEBSERVER
  debugMessln("Starting and connecting wifi ...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) // wait for connection
  {
    delay(500);
    debugMess(".");
  }
  debugMessln();

  infoMess("Connected to ");
  infoMessln(ssid);
  infoMess("IP address: ");
  infoMessln(WiFi.localIP());

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
  // Hook examples ******************************************************
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
    if (url.startsWith("/dump")) {
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
  // Hook examples ******************************************************
  server.onNotFound(handleNotFound);

  debugMessln("Starting web server ...");
  server.begin();
  Serial.println("HTTP server started");
  debugMessln();
#endif

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

#if TFTSCREEN
  debugMessln("Clearing screen ...");
  clearScreen();
  debugMessln();
#endif

#if DEBUG && TFTSCREEN
  Serial.println("Drawing help lines ...");
  Serial.println();
  helpLines();
  debugMessln();
#endif

  debugMessln("Getting time...");
  now = timeNow();

  debugMessln("Getting temperature...");
  temperature = tempNow();

  prettyPrint(now, temperature);
  oldEpoch = now;

#if TFTSCREEN
  updateScreen(now, temperature);
#endif
}

// Main **********************************************

void update()
{
  RTCtest(now);

  prettyPrint(now, temperature);

#if TFTSCREEN
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

#if WEBSERVER
  server.handleClient();
  MDNS.update();
#endif

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
