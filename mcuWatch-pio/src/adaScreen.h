
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

  // Serial.println("Test 2/12: print function ..."); // tft print function!
  tftPrintTest();
  delay(4000);

  // Serial.println("Test 3/12: single pixel ..."); // a single pixel
  tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
  delay(500);

  // Serial.println("Test 4/12: line draw ..."); // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // Serial.println("Test 5/12: optimized lines ..."); // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  // Serial.println("Test 6/12: draw rectangles ...");
  testdrawrects(ST77XX_GREEN);
  delay(500);

  // Serial.println("Test 7/12: fill rectangles ...");
  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);

  // Serial.println("Test 8/12: fill circles ...");
  testfillcircles(10, ST77XX_BLUE);

  // Serial.println("Test 9/12: draw circles ...");
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  // Serial.println("Test 10/12: round rextangles ...");
  testroundrects();
  delay(500);

  // Serial.println("Test 11/12: triangles ...");
  testtriangles();
  delay(500);

  // Serial.println("Test 12/12: media buttons ...");
  mediabuttons();
  delay(500);

  // Serial.println("Done\nWaiting ...");
  delay(500);
  // Serial.println("Continuing");
}

// ****************************** end of test ******************************

void clearScreen()
{
  tft.fillScreen(bgCol);
}

void helpLines()
{
#if DEBUG
  for (int i = tft.height() / 4; i < tft.height(); i += tft.height() / 4)
  {
    Serial.print("0, ");
    Serial.print(i);
    Serial.print(" -> ");
    Serial.print(tft.width() - 1);
    Serial.print(", ");
    Serial.println(i);

    tft.drawLine(0, i, tft.width() - 1, i, colGre);
  }

  for (int i = tft.width() / 4; i < tft.width(); i += tft.width() / 4)
  {
    Serial.print(i);
    Serial.print(", 0 -> ");
    Serial.print(i);
    Serial.print(", ");
    Serial.println(tft.height() - 1);

    tft.drawLine(i, 0, i, tft.height() - 1, colGre);
  }
#endif
}

void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
  debug("Filling rectangle, x: ");
  debug(x);
  debug("\t y: ");
  debug(y);
  debug("\t width: ");
  debug(width);
  debug("\t height: ");
  debug(height);
  debug("\t colour: ");
  debugln(color);
  tft.fillRect(x, y, width, height, color);
}

void drawText(int16_t posX, int16_t posY, int16_t size, uint16_t color, String inText)
{
  debug("Drawing text, x: ");
  debug(posX);
  debug("\t y: ");
  debug(posY);
  debug("\t size: ");
  debug(size);
  debug("\t colour: ");
  debug(color);
  debug("\ttext: ");
  debugln(inText);

  tft.setCursor(posX, posY);
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(inText);
}

void printTime(DateTime &now)
{
  String temp1, temp2;

  debug("Writing new time: ");
  temp1 = now.hour() + hourOffs;
  temp2 = padByte(temp1);
  temp2 += ":";
  temp1 = now.minute();
  temp2 += padByte(temp1);
  debugln(temp2);

  fillRectangle(tft.width() / 2 - temp2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
                tft.height() / 4,                                                     // y
                temp2.length() * pixX * timeSize,                                     // width
                pixY * timeSize,                                                      // height
                bgCol);                                                               // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
           tft.height() / 4,                                                     // y
           timeSize,                                                             // size
           timeCol,                                                              // colour
           temp2);                                                               // text
}

void printDate(DateTime &now)
{
  String temp1, temp2;

  debug("Writing new date: ");
  temp2 = dayName[now.dayOfWeek() - 1];
  temp2 += " ";
  temp2 += monthName[now.month() - 1];
  temp2 += " ";
  temp1 = now.date();
  temp2 += prettyNumbering(temp1);
  temp2 += " ";
  temp1 = now.year();
  temp2 += padByte(temp1);
  debugln((temp2));

  fillRectangle(tft.width() / 2 - (temp2.length() + 1) / 2.0 * pixX * dateSize, // x
                tft.height() / 8,                                               // y
                (temp2.length() + 1) * pixX * dateSize,                         // width
                pixY * dateSize,                                                // height
                bgCol);                                                         // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * dateSize, // x
           tft.height() / 8,                                         // y
           dateSize,                                                 // size
           dateCol,                                                  // colour
           temp2);                                                   // text
}

void printTemp(float temperature)
{
  String temp2;

  temp2 = String(temperature, 1);

  fillRectangle(tft.width() / 2 - (temp2.length() + 1) / 2.0 * pixX * tempSize, // x
                tft.height() / 8 * 5,                                           // y
                (temp2.length() + 1) * pixX * tempSize,                         // width
                pixY * dateSize,                                                // height
                bgCol);                                                         // colour

  drawText(tft.width() / 2 - temp2.length() / 2.0 * pixX * tempSize, // x
           tft.height() / 8 * 5,                                     // y
           tempSize,                                                 // size
           tempCol,                                                  // colour
           temp2);                                                   // text

  if (temperature > maxTemp)
  {
    debugln("New max temp");

    fillRectangle(tft.width() / 4 - (temp2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * 7,                                           // y
                  (temp2.length() + 1) * pixX * tempSize,                         // width
                  pixY * dateSize,                                                // height
                  bgCol);                                                         // colour

    drawText(tft.width() / 4 - temp2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * 7,                                     // y
             tempSize,                                                 // size
             maxTempCol,                                               // colour
             temp2);                                                   // text

    maxTemp = temperature;
  }

  if (temperature < minTemp)
  {
    debugln("New min temp");

    fillRectangle(tft.width() / 4 * 3 - (temp2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * 7,                                               // y
                  (temp2.length() + 1) * pixX * tempSize,                             // width
                  pixY * dateSize,                                                    // height
                  bgCol);                                                             // colour

    drawText(tft.width() / 4 * 3 - temp2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * 7,                                         // y
             tempSize,                                                     // size
             minTempCol,                                                   // colour
             temp2);                                                       // text

    minTemp = temperature;
  }
}

void updateScreen(DateTime &now, float temperature)
{
  String temp1, temp2;

  temp1 = now.minute();
  temp2 = oldNow.minute();
  if (temp1 != temp2)
  {
    debugln("Updating screen, time ...");
    printTime(now);

    oldNow = now;
  }

  temp1 = now.date();
  temp2 = oldNow.date();
  if (temp1 != temp2)
  {
    debugln("Updating screen, date ...");
    printDate(now);
  }

  if (temperature != oldTemp)
  {
    debugln("Updating screen, temperature ...");
    printTemp(temperature);

    oldTemp = temperature;
  }

  debugln();
}