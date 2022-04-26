
void clearScreen()
{
  oled.clearDisplay();
}

void helpLines()
{
#if DEBUG
  debugMessln("Drawing horizontal lines ...");
  for (int i = oled.height() / 4; i < oled.height(); i += oled.height() / 4) // horizontal lines
  {
    Serial.print("0, ");
    Serial.print(i);
    Serial.print(" -> ");
    Serial.print(oled.width() - 1);
    Serial.print(", ");
    Serial.println(i);

    oled.drawLine(0, i, oled.width() - 1, i, textCol);
  }

  debugMessln("Drawing vertical lines ...");
  for (int i = oled.width() / 4; i < oled.width(); i += oled.width() / 4) // vertical lines
  {
    Serial.print(i);
    Serial.print(", 0 -> ");
    Serial.print(i);
    Serial.print(", ");
    Serial.println(oled.height() - 1);

    oled.drawLine(i, 0, i, oled.height() - 1, textCol);
  }

  oled.display(); // update screen with drawn lines
#endif
}

void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color)
{
  debugMess("Filling rectangle, x: ");
  debugMess(x);
  debugMess("\ty: ");
  debugMess(y);
  debugMess("\twidth: ");
  debugMess(width);
  debugMess("\theight: ");
  debugMess(height);
  debugMess("\tcolour: ");
  debugMessln(color);
  oled.fillRect(x, y, width, height, color);

  oled.display(); // update screen
}

void drawText(int16_t posX, int16_t posY, int16_t size, uint16_t color, String inText)
{
  debugMess("Drawing text, x: ");
  debugMess(posX);
  debugMess("\ty: ");
  debugMess(posY);
  debugMess("\tsize: ");
  debugMess(size);
  debugMess("\tcolour: ");
  debugMess(color);
  debugMess("\ttext: ");
  debugMessln(inText);

  oled.setCursor(posX, posY);
  oled.setTextSize(size);
  oled.setTextColor(color);
  oled.setTextWrap(true);
  oled.print(inText);

  oled.display(); // update screen
}

void printTime(DateTime &now)
{
  String myString;

  infoMess("+++++ Writing new time: ");

  myString = padByte((now.hour() + hourOffs)) + ":";
  myString.concat(padByte(now.minute()));

  infoMessln(myString);

  fillRectangle(oled.width() / XSplits * timeNowXPos - myString.length() / 2.0 * pixX * timeSize + timeXOffs, // x
                oled.height() / 8 * timeNowYPos,                                                              // y
                myString.length() * pixX * timeSize,                                                          // width
                pixY * timeSize,                                                                              // height
                bgCol);                                                                                       // colour

  drawText(oled.width() / XSplits * timeNowXPos - myString.length() / 2.0 * pixX * timeSize + timeXOffs, // x
           oled.height() / 8 * timeNowYPos,                                                              // y
           timeSize,                                                                                     // size
           textCol,                                                                                      // colour
           myString);                                                                                    // text

  oled.display(); // update screen
}

void printDate(DateTime &now)
{
  String myString;

  infoMess("+++++ Writing new date: ");

  myString = dayName[now.dayOfWeek() - 1];
  myString.concat(" ");
  myString.concat(monthName[now.month() - 1]);
  myString.concat(" ");
  myString.concat(now.date());
  myString.concat(prettyNumbering(now.date()));
  myString.concat(" ");
  myString.concat(now.year());

  infoMessln((myString));

  fillRectangle(oled.width() / XSplits * dateXPos - (myString.length() + 1) / 2.0 * pixX * dateSize, // x
                oled.height() / YSplits * dateYPos,                                                  // y
                (myString.length() + 1) * pixX * dateSize,                                           // width
                pixY * dateSize,                                                                     // height
                bgCol);                                                                              // colour

  drawText(oled.width() / XSplits * dateXPos - myString.length() / 2.0 * pixX * dateSize, // x
           oled.height() / YSplits * dateYPos,                                            // y
           dateSize,                                                                      // size
           textCol,                                                                       // colour
           myString);                                                                     // text

  oled.display(); // update screen
}

void printTemp(float temperature)
{
  char myString1[4];
  String myString2;

  infoMess("+++++ Writing new temperature: ");

  dtostrf(temperature, 4, 1, myString1);
  myString2 = String(myString1);

  infoMessln(myString2);

  fillRectangle(oled.width() / XSplits * tempNowXPos - (myString2.length() + 1) / 2.0 * pixX * tempNowSize, // x
                oled.height() / YSplits * tempNowYPos,                                                      // y
                (myString2.length() + 1) * pixX * tempNowSize,                                              // width
                pixY * tempNowSize,                                                                         // height
                bgCol);                                                                                     // colour

  drawText(oled.width() / XSplits * tempNowXPos - myString2.length() / 2.0 * pixX * tempNowSize, // x
           oled.height() / YSplits * tempNowYPos,                                                // y
           tempNowSize,                                                                          // size
           textCol,                                                                              // colour
           myString2);                                                                           // text

  if (temperature > maxTemp)
  {
    infoMessln("+++++ New max temperature");

    fillRectangle(oled.width() / XSplits * tempMaxXpos - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  oled.height() / YSplits * tempMaxYPos,                                                   // y
                  (myString2.length() + 1) * pixX * tempSize,                                              // width
                  pixY * tempSize,                                                                         // height
                  bgCol);                                                                                  // colour

    drawText(oled.width() / XSplits * tempMaxXpos - myString2.length() / 2.0 * pixX * tempSize, // x
             oled.height() / YSplits * tempMaxYPos,                                             // y
             tempSize,                                                                          // size
             textCol,                                                                           // colour
             myString2);                                                                        // text

    maxTemp = temperature;
    // maxTempNow = now;
  }

  if (temperature < minTemp)
  {
    infoMessln("+++++ New min temperature");

    fillRectangle(oled.width() / XSplits * tempMinXpos - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  oled.height() / YSplits * tempMinYPos,                                                   // y
                  (myString2.length() + 1) * pixX * tempSize,                                              // width
                  pixY * tempSize,                                                                         // height
                  bgCol);                                                                                  // colour

    drawText(oled.width() / XSplits * tempMinXpos - myString2.length() / 2.0 * pixX * tempSize, // x
             oled.height() / YSplits * tempMinYPos,                                             // y
             tempSize,                                                                          // size
             textCol,                                                                           // colour
             myString2);                                                                        // text

    minTemp = temperature;
    // minTempNow = now;
  }

  oled.display(); // update screen
}

void updateScreen(DateTime &now, float temperature)
{
  if (now.date() != oldNow.date())
  {
    debugMessln("----- Updating screen, date ...");
    printDate(now);
  }

  if (now.minute() != oldNow.minute())
  {
    debugMessln("----- Updating screen, time ...");
    printTime(now);
    oldNow = now;
  }

  if (temperature != oldTemp)
  {
    debugMessln("----- Updating screen, temperature ...");
    printTemp(temperature);

    oldTemp = temperature;
  }

  debugMessln();
}

void testdrawstyles(void)
{
  oled.clearDisplay();

  oled.setTextSize(1);              // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE); // Draw white text
  oled.setCursor(0, 0);             // Start at top-left corner
  oled.println(F("Hello, world!"));

  oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  oled.println(3.141592);

  oled.setTextSize(2); // Draw 2X-scale text
  oled.setTextColor(SSD1306_WHITE);
  oled.print(F("0x"));
  oled.println(0xDEADBEEF, HEX);

  oled.display();
  delay(2000);
}
