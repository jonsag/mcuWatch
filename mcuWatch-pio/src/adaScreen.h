
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
  debugMess("Filling rectangle, x: ");
  debugMess(x);
  debugMess("\t y: ");
  debugMess(y);
  debugMess("\t width: ");
  debugMess(width);
  debugMess("\t height: ");
  debugMess(height);
  debugMess("\t colour: ");
  debugMessln(color);
  tft.fillRect(x, y, width, height, color);
}

void drawText(int16_t posX, int16_t posY, int16_t size, uint16_t color, String inText)
{
  debugMess("Drawing text, x: ");
  debugMess(posX);
  debugMess("\t y: ");
  debugMess(posY);
  debugMess("\t size: ");
  debugMess(size);
  debugMess("\t colour: ");
  debugMess(color);
  debugMess("\ttext: ");
  debugMessln(inText);

  tft.setCursor(posX, posY);
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(inText);
}

void printTime(DateTime &now)
{
  String myString1, myString2;

  infoMess("+++++ Writing new time: ");

  myString1 = now.hour() + hourOffs;
  myString2 = padByte(myString1);
  myString2 += ":";
  myString1 = now.minute();
  myString2 += padByte(myString1);

  infoMessln(myString2);

  fillRectangle(tft.width() / 2 - myString2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
                tft.height() / 8 * timeNowYPos,                                       // y
                myString2.length() * pixX * timeSize,                                     // width
                pixY * timeSize,                                                      // height
                bgCol);                                                               // colour

  drawText(tft.width() / 2 - myString2.length() / 2.0 * pixX * timeSize + timeXOffs, // x
           tft.height() / 8 * timeNowYPos,                                       // y
           timeSize,                                                             // size
           timeCol,                                                              // colour
           myString2);                                                               // text
}

void printDate(DateTime &now)
{
  String myString1, myString2;

  infoMess("+++++ Writing new date: ");

  myString2 = dayName[now.dayOfWeek() - 1];
  myString2 += " ";
  myString2 += monthName[now.month() - 1];
  myString2 += " ";
  myString1 = now.date();
  myString2 += prettyNumbering(myString1);
  myString2 += " ";
  myString1 = now.year();
  myString2 += padByte(myString1);

  infoMessln((myString2));

  fillRectangle(tft.width() / 2 - (myString2.length() + 1) / 2.0 * pixX * dateSize, // x
                tft.height() / 8 * dateYPos,                                    // y
                (myString2.length() + 1) * pixX * dateSize,                         // width
                pixY * dateSize,                                                // height
                bgCol);                                                         // colour

  drawText(tft.width() / 2 - myString2.length() / 2.0 * pixX * dateSize, // x
           tft.height() / 8 * dateYPos,                              // y
           dateSize,                                                 // size
           dateCol,                                                  // colour
           myString2);                                                   // text
}

void printTemp(float temperature)
{
  char myString1[4];
  String myString2;

  infoMess("+++++ Writing new temperature: ");

  // myString2 = String(temperature, 1);
  dtostrf(temperature, 4, 1, myString1);
  myString2 = String(myString1);

  infoMess(myString2);

  fillRectangle(tft.width() / 2 - (myString2.length() + 1) / 2.0 * pixX * tempNowSize, // x
                tft.height() / 8 * tempNowYPos,                                    // y
                (myString2.length() + 1) * pixX * tempNowSize,                         // width
                pixY * tempNowSize,                                                // height
                bgCol);                                                            // colour

  drawText(tft.width() / 2 - myString2.length() / 2.0 * pixX * tempNowSize, // x
           tft.height() / 8 * tempNowYPos,                              // y
           tempNowSize,                                                 // size
           tempCol,                                                     // colour
           myString2);                                                      // text

  if (temperature > maxTemp)
  {
    infoMessln("+++++ New max temperature");

    fillRectangle(tft.width() / 4 * 3 - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * tempMinMaxYPos,                                  // y
                  (myString2.length() + 1) * pixX * tempSize,                             // width
                  pixY * tempSize,                                                    // height
                  bgCol);                                                             // colour

    drawText(tft.width() / 4 * 3 - myString2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * tempMinMaxYPos,                            // y
             tempSize,                                                     // size
             maxTempCol,                                                   // colour
             myString2);                                                       // text

    maxTemp = temperature;
    // maxTempNow = now;
  }

  if (temperature < minTemp)
  {
    infoMessln("+++++ New min temperature");

    fillRectangle(tft.width() / 4 - (myString2.length() + 1) / 2.0 * pixX * tempSize, // x
                  tft.height() / 8 * tempMinMaxYPos,                              // y
                  (myString2.length() + 1) * pixX * tempSize,                         // width
                  pixY * tempSize,                                                // height
                  bgCol);                                                         // colour

    drawText(tft.width() / 4 - myString2.length() / 2.0 * pixX * tempSize, // x
             tft.height() / 8 * tempMinMaxYPos,                        // y
             tempSize,                                                 // size
             minTempCol,                                               // colour
             myString2);                                                   // text

    minTemp = temperature;
    // minTempNow = now;
  }
}

void updateScreen(DateTime &now, float temperature)
{
  String myString1, myString2;

  myString1 = now.date();
  myString2 = oldNow.date();
  if (myString1 != myString2)
  {
    debugMessln("----- Updating screen, date ...");
    printDate(now);
  }

  myString1 = now.minute();
  myString2 = oldNow.minute();
  if (myString1 != myString2)
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