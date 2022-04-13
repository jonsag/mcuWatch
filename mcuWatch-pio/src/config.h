
/**********
 * Debug
 **********/
#define DEBUG 0 // debug is off when 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

/**********
 * Pins
 **********/
/*
SPI (ST7735)
Function    Screen pin  Arduino 168 Arduino 328 ESP8266     ESP-01      Comment
-----       -----       -----       -----       -----       -----       -----
SCK         3           D13*)       D13*)       D5/GPIO14*)             SCL, HSCLK, SPI Clock, Hardware SPI clk
SDA         4           D11*)       D11*)       D7/GPIO13*)             SPI Data, MOSI, HMOSI, data to screen
RES         pulled high                                                 RST, HMISO, screen reset
DC          6           D4          D4          D4/GPIO2                Register Select, labelled as DC in Adafruit code
CS          7           D3          D3          D3/GPIO0                Chip Select, defined as Slave Select in SPI
*) Must be these pins as they are set in firmware/hardware

I2C (RTC and SSD1306)
Function    RTC         Screen      Arduino     ESP8266     ESP-01
-----       -----       -----       -----       -----       -----
Address     0x68        0x3C
SDA         2                       A4          D2/GPIO4    3/GPIO2
SCL         3                       A5          D1/GPIO5    5/GPIO0

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

Find macro definitions:
$ grep board= `find ~/.platformio/ -name boards.txt` | cut -f2 -d= | sort -u
*/

#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E)
#define tftRES 0
#define tftDC D4 // GPIO2, TFT display SPI chip select pin
#define tftCS D3 // GPIO0, TFT display data/command select pin
#define rotCLK SD3 // GPIO10
#define rotDT SD2 // GPIO9
#define rotSW D0 // GPIO16
#define buz D8 // GPIO2

#elif defined(ARDUINO_AVR_PRO)
#define tftRES 5
#define tftDC 4
#define tftCS 3
#define rotCLK 9
#define rotDT 8
#define rotSW 7
#define buz 6

#elif defined(ARDUINO_AVR_UNO)

#define tftRES 5
#define tftDC 4
#define tftCS 3
#define rotCLK 8
#define rotDT 7
#define rotSW 6
#define buz 9
#endif

/**********
 * TFT screen
 **********/
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(tftCS, tftDC, tftRES);

// colours
#define colBla ST77XX_BLACK
#define colWhi ST77XX_WHITE
#define colYel ST77XX_YELLOW
#define colRed ST77XX_RED
#define colGre ST77XX_GREEN
#define colBlu ST77XX_BLUE
#define colMag ST77XX_MAGENTA

/*
rotate:
0: no rotation
3: 90 degrees CW
6: 180 degrees
5: 90 degrees CCW
*/

/*
#if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) || defined(ARDUINO_AVR_PRO)
int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0; // Adafruit 1.8" 160x128 display

#elif defined(ARDUINO_AVR_UNO)
int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 6; // Adafruit 1.8" 160x128 display

#endif

#include <TFTGraphicsLibrary.h>
*/

/**********
 * RTC
 **********/
/*
RTC from above
------------
| 5 GND     |
| 4 NC      |
| 3 C SCL   |
| 2 D SDA   |
| 1 VCC     |
------------
*/

#include <DS3231.h>
#include <Wire.h> // also included by the SPI-include above

DS3231 myDS3231;
RTClib myRTClib;

DateTime now;

byte year;
byte month;
byte date;
byte dOW;
byte hour;
byte minute;
byte second;

String yearNow;
String monthNow;
String dayNow;
String dOWNow;
String hourNow;
String minuteNow;
String secondNow;

//String oldYearNow;
//String oldMonthNow;
String oldDayNow;
//String olddOWNow;
//String oldHourNow;
String oldMinuteNow;;

//String oldTime;

const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const char *dayName[7] = {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

const int BUFFER_SIZE = 12;
char buf[BUFFER_SIZE];
char inString[BUFFER_SIZE];
byte temp1, temp2;
int rlen;
int rxlen;

bool century = false;
bool h12Flag;
bool pmFlag;

long currentMillis;
long lastTickMillis;
int tickInterval = 5000;

/**********
 * Rotary encoder
 **********/

/**********
 * Buzzer
 **********/

/**********
 * Misc
 **********/
int i = 0;

const int serialTimeout = 10000;

float pi = 3.1415926;