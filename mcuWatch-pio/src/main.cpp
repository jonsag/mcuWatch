/* Compact TFT Graphics Library v3 - see http://www.technoblogy.com/show?2LMJ

   David Johnson-Davies - www.technoblogy.com - 24th July 2021

   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license:
   http://creativecommons.org/licenses/by/4.0/
*/

/*
SPI (ST7735)
Function    Screen pin  Arduino 168 Arduino 328 ESP8266     ESP-01      Comment
-----       -----       -----       -----       -----       -----       -----
SCK         3           D9          D13*)       D5/GPIO14*)             SCL, HSCLK, SPI Clock, Hardware SPI clk
SDA         4           D8          D11*)       D7/GPIO13*)             SPI Data, MOSI, HMOSI, data to screen
RES         5           D7          pulled high D6/GPIO12*)             RST, HMISO, screen reset
DC          6           D6          D7          D4/GPIO2                Register Select, labelled as DC in Adafruit code
CS          7           D5          D6          D3/GPIO0                Chip Select, defined as Slave Select in SPI
*) Must be these pins as they are set in firmware/hardware
*/

#include <SPI.h>

int const cs = 6; // TFT display SPI chip select pin
int const dc = 7; // TFT display data/command select pin

// Display parameters - uncomment the line for the one you want to use

// Adafruit 1.44" 128x128 display
// int const ysize = 128, xsize = 128, yoff = 3, xoff = 2, invert = 0, rotate = 5;

// Adafruit 0.96" 160x80 display
// int const ysize = 80, xsize = 160, yoff = 24, xoff = 0, invert = 0, rotate = 0;

// AliExpress 0.96" 160x80 display
// int const ysize = 80, xsize = 160, yoff = 26, xoff = 1, invert = 1, rotate = 0;

// Adafruit 1.8" 160x128 display
 int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0;

// AliExpress 1.8" 160x128 display
//int const ysize = 128, xsize = 160, yoff = 0, xoff = 0, invert = 0, rotate = 0;

// Adafruit 1.14" 240x135 display
// int const ysize = 135, xsize = 240, yoff = 53, xoff = 40, invert = 1, rotate = 6;

// AliExpress 1.14" 240x135 display
// int const ysize = 135, xsize = 240, yoff = 52, xoff = 40, invert = 1, rotate = 0;

// Adafruit 1.54" 240x240 display and Adafruit 1.3" 240x240 display
// int const ysize = 240, xsize = 240, yoff = 0, xoff = 0, invert = 1, rotate = 3;

// AliExpress 1.54" 240x240 display
// int const ysize = 240, xsize = 240, yoff = 80, xoff = 0, invert = 1, rotate = 5;

// Adafruit 2.0" 320x240 display
// int const ysize = 240, xsize = 320, yoff = 0, xoff = 0, invert = 1, rotate = 6;

// Character set for text - stored in program memory
const uint8_t CharMap[96][6] PROGMEM = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00},
    {0x00, 0x07, 0x00, 0x07, 0x00, 0x00},
    {0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00},
    {0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00},
    {0x23, 0x13, 0x08, 0x64, 0x62, 0x00},
    {0x36, 0x49, 0x56, 0x20, 0x50, 0x00},
    {0x00, 0x08, 0x07, 0x03, 0x00, 0x00},
    {0x00, 0x1C, 0x22, 0x41, 0x00, 0x00},
    {0x00, 0x41, 0x22, 0x1C, 0x00, 0x00},
    {0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x00},
    {0x08, 0x08, 0x3E, 0x08, 0x08, 0x00},
    {0x00, 0x80, 0x70, 0x30, 0x00, 0x00},
    {0x08, 0x08, 0x08, 0x08, 0x08, 0x00},
    {0x00, 0x00, 0x60, 0x60, 0x00, 0x00},
    {0x20, 0x10, 0x08, 0x04, 0x02, 0x00},
    {0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00},
    {0x00, 0x42, 0x7F, 0x40, 0x00, 0x00},
    {0x72, 0x49, 0x49, 0x49, 0x46, 0x00},
    {0x21, 0x41, 0x49, 0x4D, 0x33, 0x00},
    {0x18, 0x14, 0x12, 0x7F, 0x10, 0x00},
    {0x27, 0x45, 0x45, 0x45, 0x39, 0x00},
    {0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00},
    {0x41, 0x21, 0x11, 0x09, 0x07, 0x00},
    {0x36, 0x49, 0x49, 0x49, 0x36, 0x00},
    {0x46, 0x49, 0x49, 0x29, 0x1E, 0x00},
    {0x00, 0x00, 0x14, 0x00, 0x00, 0x00},
    {0x00, 0x40, 0x34, 0x00, 0x00, 0x00},
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00},
    {0x14, 0x14, 0x14, 0x14, 0x14, 0x00},
    {0x00, 0x41, 0x22, 0x14, 0x08, 0x00},
    {0x02, 0x01, 0x59, 0x09, 0x06, 0x00},
    {0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x00},
    {0x7C, 0x12, 0x11, 0x12, 0x7C, 0x00},
    {0x7F, 0x49, 0x49, 0x49, 0x36, 0x00},
    {0x3E, 0x41, 0x41, 0x41, 0x22, 0x00},
    {0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00},
    {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00},
    {0x7F, 0x09, 0x09, 0x09, 0x01, 0x00},
    {0x3E, 0x41, 0x41, 0x51, 0x73, 0x00},
    {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00},
    {0x00, 0x41, 0x7F, 0x41, 0x00, 0x00},
    {0x20, 0x40, 0x41, 0x3F, 0x01, 0x00},
    {0x7F, 0x08, 0x14, 0x22, 0x41, 0x00},
    {0x7F, 0x40, 0x40, 0x40, 0x40, 0x00},
    {0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x00},
    {0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00},
    {0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00},
    {0x7F, 0x09, 0x09, 0x09, 0x06, 0x00},
    {0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00},
    {0x7F, 0x09, 0x19, 0x29, 0x46, 0x00},
    {0x26, 0x49, 0x49, 0x49, 0x32, 0x00},
    {0x03, 0x01, 0x7F, 0x01, 0x03, 0x00},
    {0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00},
    {0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00},
    {0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00},
    {0x63, 0x14, 0x08, 0x14, 0x63, 0x00},
    {0x03, 0x04, 0x78, 0x04, 0x03, 0x00},
    {0x61, 0x59, 0x49, 0x4D, 0x43, 0x00},
    {0x00, 0x7F, 0x41, 0x41, 0x41, 0x00},
    {0x02, 0x04, 0x08, 0x10, 0x20, 0x00},
    {0x00, 0x41, 0x41, 0x41, 0x7F, 0x00},
    {0x04, 0x02, 0x01, 0x02, 0x04, 0x00},
    {0x40, 0x40, 0x40, 0x40, 0x40, 0x00},
    {0x00, 0x03, 0x07, 0x08, 0x00, 0x00},
    {0x20, 0x54, 0x54, 0x78, 0x40, 0x00},
    {0x7F, 0x28, 0x44, 0x44, 0x38, 0x00},
    {0x38, 0x44, 0x44, 0x44, 0x28, 0x00},
    {0x38, 0x44, 0x44, 0x28, 0x7F, 0x00},
    {0x38, 0x54, 0x54, 0x54, 0x18, 0x00},
    {0x00, 0x08, 0x7E, 0x09, 0x02, 0x00},
    {0x18, 0xA4, 0xA4, 0x9C, 0x78, 0x00},
    {0x7F, 0x08, 0x04, 0x04, 0x78, 0x00},
    {0x00, 0x44, 0x7D, 0x40, 0x00, 0x00},
    {0x20, 0x40, 0x40, 0x3D, 0x00, 0x00},
    {0x7F, 0x10, 0x28, 0x44, 0x00, 0x00},
    {0x00, 0x41, 0x7F, 0x40, 0x00, 0x00},
    {0x7C, 0x04, 0x78, 0x04, 0x78, 0x00},
    {0x7C, 0x08, 0x04, 0x04, 0x78, 0x00},
    {0x38, 0x44, 0x44, 0x44, 0x38, 0x00},
    {0xFC, 0x18, 0x24, 0x24, 0x18, 0x00},
    {0x18, 0x24, 0x24, 0x18, 0xFC, 0x00},
    {0x7C, 0x08, 0x04, 0x04, 0x08, 0x00},
    {0x48, 0x54, 0x54, 0x54, 0x24, 0x00},
    {0x04, 0x04, 0x3F, 0x44, 0x24, 0x00},
    {0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00},
    {0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00},
    {0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00},
    {0x44, 0x28, 0x10, 0x28, 0x44, 0x00},
    {0x4C, 0x90, 0x90, 0x90, 0x7C, 0x00},
    {0x44, 0x64, 0x54, 0x4C, 0x44, 0x00},
    {0x00, 0x08, 0x36, 0x41, 0x00, 0x00},
    {0x00, 0x00, 0x77, 0x00, 0x00, 0x00},
    {0x00, 0x41, 0x36, 0x08, 0x00, 0x00},
    {0x00, 0x06, 0x09, 0x06, 0x00, 0x00}, // degree symbol = '~'
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00}};

// TFT colour display **********************************************

int const CASET = 0x2A; // Define column address
int const RASET = 0x2B; // Define row address
int const RAMWR = 0x2C; // Write to display RAM

// Globals - current plot position and colours
int xorigin, yorigin;
int fore = 0xFFFF; // White
int back = 0;      // Black
int scale = 1;     // Text scale

// Send a byte to the display
void Data(uint8_t d)
{
  digitalWrite(cs, LOW);
  SPI.transfer(d);
  digitalWrite(cs, HIGH);
}

// Send a command to the display
void Command(uint8_t c)
{
  digitalWrite(dc, LOW);
  Data(c);
  digitalWrite(dc, HIGH);
}

// Send a command followed by two data words
void Command2(uint8_t c, uint16_t d1, uint16_t d2)
{
  digitalWrite(dc, LOW);
  Data(c);
  digitalWrite(dc, HIGH);
  Data(d1 >> 8);
  Data(d1);
  Data(d2 >> 8);
  Data(d2);
}

void InitDisplay()
{
  pinMode(dc, OUTPUT);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  digitalWrite(dc, HIGH); // Data
  SPI.begin();
  Command(0x01); // Software reset
  delay(150);    // delay 150 ms
  Command(0x11); // Out of sleep mode
  delay(500);    // delay 500 ms
  Command(0x3A);
  Data(0x55);             // Set color mode - 16-bit color
  Command(0x20 + invert); // Invert
  Command(0x36);
  Data(rotate << 5); // Set orientation
}

void DisplayOn()
{
  Command(0x29); // Display on
  delay(10);
}

void ClearDisplay()
{
  Command2(CASET, yoff, yoff + ysize - 1);
  Command2(RASET, xoff, xoff + xsize - 1);
  Command(0x3A);
  Data(0x03); // 12-bit colour
  Command(RAMWR);
  for (int i = 0; i < xsize / 2; i++)
  {
    for (int j = 0; j < ysize * 3; j++)
    {
      Data(0);
    }
  }
  Command(0x3A);
  Data(0x05); // Back to 16-bit colour
}

unsigned int Colour(int r, int g, int b)
{
  return (r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3;
}

// Move current plot position to x,y
void MoveTo(int x, int y)
{
  xorigin = x;
  yorigin = y;
}

// Plot point at x,y
void PlotPoint(int x, int y)
{
  Command2(CASET, yoff + y, yoff + y);
  Command2(RASET, xoff + x, xoff + x);
  Command(RAMWR);
  Data(fore >> 8);
  Data(fore & 0xff);
}

// Draw a line to x,y
void DrawTo(int x, int y)
{
  int sx, sy, e2, err;
  int dx = abs(x - xorigin);
  int dy = abs(y - yorigin);
  if (xorigin < x)
    sx = 1;
  else
    sx = -1;
  if (yorigin < y)
    sy = 1;
  else
    sy = -1;
  err = dx - dy;
  for (;;)
  {
    PlotPoint(xorigin, yorigin);
    if (xorigin == x && yorigin == y)
      return;
    e2 = err << 1;
    if (e2 > -dy)
    {
      err = err - dy;
      xorigin = xorigin + sx;
    }
    if (e2 < dx)
    {
      err = err + dx;
      yorigin = yorigin + sy;
    }
  }
}

void FillRect(int w, int h)
{
  Command2(CASET, yorigin + yoff, yorigin + yoff + h - 1);
  Command2(RASET, xorigin + xoff, xorigin + xoff + w - 1);
  Command(RAMWR);
  for (int p = 0; p < w * h * 2; p++)
  {
    Data(fore >> 8);
    Data(fore & 0xff);
  }
}

// Plot an ASCII character with bottom left corner at x,y
void PlotChar(char c)
{
  int colour;
  Command2(CASET, yoff + yorigin, yoff + yorigin + 8 * scale - 1);
  Command2(RASET, xoff + xorigin, xoff + xorigin + 6 * scale - 1);
  Command(RAMWR);
  for (int xx = 0; xx < 6; xx++)
  {
    int bits = pgm_read_byte(&CharMap[c - 32][xx]);
    for (int xr = 0; xr < scale; xr++)
    {
      for (int yy = 0; yy < 8; yy++)
      {
        if (bits >> (7 - yy) & 1)
          colour = fore;
        else
          colour = back;
        for (int yr = 0; yr < scale; yr++)
        {
          Data(colour >> 8);
          Data(colour & 0xFF);
        }
      }
    }
  }
  xorigin = xorigin + 6 * scale;
}

// Plot text starting at the current plot position
void PlotText(PGM_P p)
{
  while (1)
  {
    char c = pgm_read_byte(p++);
    if (c == 0)
      return;
    PlotChar(c);
  }
}

void TestChart()
{
  MoveTo(0, 0);
  DrawTo(xsize - 1, 0);
  DrawTo(xsize - 1, ysize - 1);
  DrawTo(0, ysize - 1);
  DrawTo(0, 0);
  scale = 8;
  MoveTo((xsize - 40) / 2, (ysize - 64) / 2);
  PlotChar('F');
}

// Setup **********************************************

void setup()
{
  // Start the serial port
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  Serial.println("Compact TFT Graphics library");
  Serial.println();

  Serial.println("Initializing display ...");
  InitDisplay();
  Serial.println("Clearing display ...");
  ClearDisplay();
  Serial.println("Turning on display ...");
  DisplayOn();
  MoveTo(0, 0);
}

void loop()
{
  // Plot bar chart
  int x1 = 15, y1 = 11; // Origin
  MoveTo((xsize - x1 - 90) / 2 + x1, ysize - 8);
  PlotText(PSTR("Sensor Readings"));
  // Horizontal axis
  int xinc = (xsize - x1) / 20;
  MoveTo(x1, y1);
  DrawTo(xsize - 1, y1);
  for (int i = 0; i <= 20; i = i + 4)
  {
    int mark = x1 + i * xinc;
    MoveTo(mark, y1);
    DrawTo(mark, y1 - 2);
    // Draw histogram
    if (i != 20)
    {
      int bar = xinc * 4 / 3;
      fore = Colour(0, 0, 255);
      MoveTo(mark + bar * 2 - 1, y1 + 1);
      FillRect(bar, 5 + random(ysize - y1 - 20));
      fore = Colour(0, 255, 0);
      MoveTo(mark + bar, y1 + 1);
      FillRect(bar, 5 + random(ysize - y1 - 20));
      fore = Colour(255, 0, 0);
      MoveTo(mark + 1, y1 + 1);
      FillRect(bar, 5 + random(ysize - y1 - 20));
      fore = 0xFFFF;
    }
    int tens = i / 10;
    if (tens != 0)
    {
      MoveTo(mark - 7, y1 - 11);
      PlotChar(tens + '0');
      MoveTo(mark - 1, y1 - 11);
      PlotChar(i % 10 + '0');
    }
    else
    {
      MoveTo(mark - 3, y1 - 11);
      PlotChar(i % 10 + '0');
    }
  }
  // Vertical axis
  int yinc = (ysize - y1) / 20;
  MoveTo(x1, y1);
  DrawTo(x1, ysize - 1);
  for (int i = 0; i <= 20; i = i + 5)
  {
    int mark = y1 + i * yinc;
    MoveTo(x1, mark);
    DrawTo(x1 - 2, mark);
    int tens = i / 10;
    if (tens != 0)
    {
      MoveTo(x1 - 15, mark - 4);
      PlotChar(tens + '0');
    }
    MoveTo(x1 - 9, mark - 4);
    PlotChar(i % 10 + '0');
  }
  for (;;)
    ;
}
