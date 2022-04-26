
#include <Wire.h>

/**********
 * Debug
 **********/
#define DEBUG 0 // debugMess is off when 0
#define INFO 0

#define WEBSERVER 1

#if DEBUG
#define debugMess(x) Serial.print(x)
#define debugMessln(x) Serial.println(x)
#else
#define debugMess(x)
#define debugMessln(x)
#endif

#if INFO || DEBUG
#define infoMess(x) Serial.print(x)
#define infoMessln(x) Serial.println(x)
#else
#define infoMess(x)
#define infoMessln(x)
#endif

#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) || defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#define TFTSCREEN 1
#define BUZZER 1
#elif defined(ARDUINO_ESP8266_ESP01)
#define OLEDSCREEN 1
#define BUZZER 0
#endif

/*
SPI (ST7735)
Function    Screen pin  Mini        Uno         Mega        ESP8266     ESP-01      Comment
-----       -----       -----       -----       -----       -----       -----       -----
SCK         3           D13*)       D13*)       D52*)       D5/GPIO14*)             SCL, HSCLK, SPI Clock, Hardware SPI clk
SDA         4           D11*)       D11*)       D51*)       D7/GPIO13*)             SPI Data, MOSI, HMOSI, data to screen
RES         5           D5          D5          D5          D6/GPIO12               RST, MISO, HMISO, screen reset
DC          6           D4          D4          D4          D4/GPIO2                Register Select, labelled as DC in Adafruit code
CS          7           D3          D3          D3          D3/GPIO0                Chip Select, defined as Slave Select in SPI

I2C (RTC and SSD1306)
Function    RTC         Screen      Uno, Mini   Mega        ESP8266     ESP-01
-----       -----       -----       -----       -----       -----       -----
Address     0x68        0x3C
SDA         2                       A4*)         20*)      D2/GPIO4*)  3/GPIO2
SCL         3                       A5*)         21*)      D1/GPIO5*)  5/GPIO0
  oldNow = now;

Rotary encoder
Function                Arduino 168 Arduino 328 ESP8266     ESP-01
-----                   -----       -----       -----       -----
CLK                                 D9
DT                                  D8
SW                                  D7

Buzzer
Function                Arduino 168 Arduino 328 ESP8266     ESP-01
-----                   -----       -----       -----       -----
+                                   D6          D8/GPIO15

*) Must be these pins as they are set in firmware/hardware

Find macro definitions:
$ grep board= `find ~/.platformio/ -name boards.txt` | cut -f2 -d= | sort -u
*/

/**********
 * Pins
 **********/

#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) // nodeMCU LoLin v3
//#define i2cSDA D2
//#define i2cSCK D1

#define tftSCK D5
#define tftSDA D7

#define tftRES D6
#define tftDC D4 // GPIO2, TFT display SPI chip select pin
#define tftCS D3 // GPIO0, TFT display data/command select pin

#define rotCLK SD3 // GPIO10
#define rotDT SD2  // GPIO9
#define rotSW D0   // GPIO16

#define buz D8 // GPIO2

#elif defined(ARDUINO_ESP32_DEV) // esp32
//#define i2cSDA D2
//#define i2cSCK D1

#define tftSCK D5
#define tftSDA D7

#define tftRES 0
#define tftDC 4 // GPIO2, TFT display SPI chip select pin
#define tftCS 3 // GPIO0, TFT display data/command select pin

#define rotCLK SD3 // GPIO10
#define rotDT SD2  // GPIO9
#define rotSW D0   // GPIO16

#define buz D8 // GPIO2

#elif defined(ARDUINO_AVR_PRO) // arduino Pro & Pro Mini
//#define i2cSDA A4
//#define i2cSCK A5

#define tftSCK 13
#define tftSDA 11

#define tftRES 5
#define tftDC 4
#define tftCS 3

#define rotCLK 9
#define rotDT 8
#define rotSW 7

#define buz 6

#elif defined(ARDUINO_AVR_UNO) // arduino Uno
//#define i2cSDA A4
//#define i2cSCK A5

#define tftSCK 13
#define tftSDA 11

#define tftRES 5
#define tftDC 4
#define tftCS 3

#define rotCLK 8
#define rotDT 7
#define rotSW 6

#define buz 9

#elif defined(ARDUINO_AVR_MEGA2560) // arduino Mega 2560
//#define i2cSDA 20
//#define i2cSCK 21

#define tftSCK 52
#define tftSDA 51

#define tftRES 5
#define tftDC 4
#define tftCS 3

#define rotCLK 8
#define rotDT 7
#define rotSW 6

#define buz 9

#elif defined(ARDUINO_ESP8266_ESP01)
#define i2cSDA 2
#define i2cSCK 0

#endif

/**********
 * TFT screen
 **********/
#if TFTSCREEN

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

Adafruit_ST7735 tft = Adafruit_ST7735(tftCS, tftDC, tftRES);

// colours
#define bgCol ST77XX_BLACK

#define timeCol ST77XX_GREEN
#define dateCol ST77XX_YELLOW

#define tempCol ST77XX_GREEN
#define maxTempCol ST77XX_RED
#define minTempCol ST77XX_BLUE

#define colBla ST77XX_BLACK
#define colWhi ST77XX_WHITE
#define colYel ST77XX_YELLOW
#define colRed ST77XX_RED
#define colGre ST77XX_GREEN
#define colBlu ST77XX_BLUE
#define colMag ST77XX_MAGENTA

// sizes
#define timeSize 4
#define dateSize 1

#define tempNowSize 3
#define tempSize 2

// positions
#define dateYPos 1
#define timeNowYPos 2
#define tempNowYPos 4
#define tempMinMaxYPos 6

// compensations
#define timeXOffs 2

// font
#define pixX 6
#define pixY 8

#elif OLEDSCREEN
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#endif

/**********
 * RTC
 **********/
/*
RTC module from above
------------
| 5 GND     |
| 4 NC      |
| 3 C SCL   |
| 2 D SDA   |
| 1 VCC     |
------------
*/

#include <Sodaq_DS3231.h>

const int hourOffs = 0;

DateTime now;
DateTime oldNow;
DateTime oldEpoch;

float temperature;
float oldTemp;

float maxTemp = -100.0;
float minTemp = 100.0;

DateTime maxTempNow;
DateTime minTempNow;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const char *dayName[7] = {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

long currentMillis;
long lastCheckMillis;
int checkInterval = 5000;

/**********
 * Web server
 **********/
#if WEBSERVER

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "secrets.h"

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

#endif

/**********
 * Rotary encoder
 **********/

/**********
 * Buzzer
 **********/

/**********
 * Misc
 **********/
const int serialTimeout = 10000;
