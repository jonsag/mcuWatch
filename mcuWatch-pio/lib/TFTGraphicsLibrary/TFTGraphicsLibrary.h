/* Compact TFT Graphics Library v3 - see http://www.technoblogy.com/show?2LMJ

  Sources: https://github.com/technoblogy/compact-tft-graphics-library

   David Johnson-Davies - www.technoblogy.com - 24th July 2021

   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license:
   http://creativecommons.org/licenses/by/4.0/
*/

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

void lcd_circle(uint8_t xc, uint8_t yc, uint8_t r)
{
  int16_t x = 0;
  int16_t y = r;
  int16_t d = r - 1;

  while (y >= x)
  {
    PlotPoint(xc + x, yc + y);
    PlotPoint(xc + y, yc + x);
    PlotPoint(xc - x, yc + y);
    PlotPoint(xc - y, yc + x);
    PlotPoint(xc + x, yc - y);
    PlotPoint(xc + y, yc - x);
    PlotPoint(xc - x, yc - y);
    PlotPoint(xc - y, yc - x);

    if (d >= 2 * x)
    {
      d -= 2 * x + 1;
      x++;
    }
    else if (d < 2 * (r - y))
    {
      d += 2 * y - 1;
      y--;
    }
    else
    {
      d += 2 * (y - x - 1);
      y--;
      x++;
    }
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
