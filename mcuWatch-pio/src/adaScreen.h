
void testlines(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color)
{
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5)
  {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5)
  {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6)
  {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = radius; x < tft.width(); x += radius * 2)
  {
    for (int16_t y = radius; y < tft.height(); y += radius * 2)
    {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
    {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles()
{
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++)
  {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects()
{
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1)
  {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1)
    {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(pi, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons()
{
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

void adaScreenTest()
{
  // Serial.println("Clearing screen ...");
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  // Serial.print("Time: ");
  Serial.println(time, DEC);
  delay(500);

  // Serial.println("Test 1/12: large block of text ..."); // large block of text
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  delay(1000);
  /*
    //Serial.println("Test 2/12: print function ..."); // tft print function!
    tftPrintTest();
    delay(4000);

    //Serial.println("Test 3/12: single pixel ..."); // a single pixel
    tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
    delay(500);

    //Serial.println("Test 4/12: line draw ..."); // line draw test
    testlines(ST77XX_YELLOW);
    delay(500);

    //Serial.println("Test 5/12: optimized lines ..."); // optimized lines
    testfastlines(ST77XX_RED, ST77XX_BLUE);
    delay(500);

    //Serial.println("Test 6/12: draw rectangles ...");
    testdrawrects(ST77XX_GREEN);
    delay(500);

    //Serial.println("Test 7/12: fill rectangles ...");
    testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(500);

    tft.fillScreen(ST77XX_BLACK);

    //Serial.println("Test 8/12: fill circles ...");
    testfillcircles(10, ST77XX_BLUE);

    //Serial.println("Test 9/12: draw circles ...");
    testdrawcircles(10, ST77XX_WHITE);
    delay(500);

    //Serial.println("Test 10/12: round rextangles ...");
    testroundrects();
    delay(500);

    //Serial.println("Test 11/12: triangles ...");
    testtriangles();
    delay(500);

    //Serial.println("Test 12/12: media buttons ...");
    mediabuttons();
    delay(500);

    //Serial.println("Done\nWaiting ...");
    delay(500);
    //Serial.println("Continuing");
    */
}

// ****************************** end of test ******************************

void clearScreen()
{
  tft.fillScreen(ST77XX_BLACK);
}

/*
char strToCharArr(String &myString)
{
  char buf[myString.length() + 1];
  myString.toCharArray(buf, myString.length() + 1);
  return *buf;
}

void eraseCenter(int posX, int posY, String &oldText)
{
  int16_t x1, y1;
  uint16_t width, height;

  debug("Erasing old text: ");
  debug(oldText);
  debugln(" ...");

  tft.getTextBounds(oldText, posX, posY, &x1, &y1, &width, &height);

  debug("posX: ");
  debugln(posX);
  debug("posY: ");
  debugln(posY);
  debug("x1: ");
  debugln(x1);
  debug("y1: ");
  debugln(y1);
  debug("width: ");
  debugln(width);
  debug("height: ");
  debugln(height);
  debugln();

  tft.fillRect(tft.width() / 2 - posX / 2, tft.height() / 2 - posX / 2, posX, posX, colBla);
}

void drawCenter(int posX, int posY, String &oldText, String &newText)
{
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  eraseCenter(posX, posY, oldText);

  debug("Drawing new text: ");
  debug(newText);
  debugln(" ...");

  tft.getTextBounds(newText, 0, 0, &x1, &y1, &width, &height);

  // display on horizontal and vertical center
  tft.setCursor((tft.width() - width) / 2, (tft.height() - height) / 2);
  tft.print(newText); // text to display
}
*/

void drawText(int16_t posX, int16_t posY, String myString, uint16_t color)
{
  char text[myString.length() + 1];
  myString.toCharArray(text, myString.length() + 1);

  Serial.print("x: ");
  Serial.print(posX);
  Serial.print("\ty: ");
  Serial.print(posY);
  Serial.print("\tColour: ");
  Serial.print(color);
  Serial.print("\tText: ");
  Serial.println(text);

  tft.setCursor(posX, posY);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(myString);
}

void printTime()
{
  String time = padByte(hourNow) + ":" + padByte(minuteNow);
  Serial.println(time);

  drawText(20, 30, time, colRed);
  // drawCenter(20, 30, oldTime, time);

  if (dayNow != oldDayNow)
  {
    String dateLine = getDayName(now) + " " + getMonthName(now) + " " + prettyNumbering(dayNow) + " " + padByte(yearNow);
    Serial.println(dateLine);

    drawText(20, 20, dateLine, colBlu);

    oldDayNow = dayNow;
  }
}

void updateScreen()
{
  minuteNow = now.minute();

  if (minuteNow != oldMinuteNow)
  {
    debugln("Updating screen ...");
    printTime();

    oldMinuteNow = minuteNow;
  }
}