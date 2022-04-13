
void TestFrame()
{
  MoveTo(0, 0);
  DrawTo(xsize - 1, 0);
  DrawTo(xsize - 1, ysize - 1);
  DrawTo(0, ysize - 1);
  DrawTo(0, 0);
}

void TestChar()
{
  scale = 8;
  MoveTo((xsize - 40) / 2, (ysize - 64) / 2);
  PlotChar('F');
}

void TestCircle()
{
  DrawCircle(xsize / 2, ysize / 2, min((xsize - 2) / 2, (ysize - 2) / 2));
}

void TestText()
{
  scale = 1;
  MoveTo(20, 20);
  PlotText(PSTR("Graphics Display"));
}

void TestChart2()
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
    debugln("Turning on display ...");
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
}

void stringToCharArray(String myString) {
  char buf[myString.length() + 1];

  myString.toCharArray(buf, myString.length() + 1);
}

void printTime(DateTime &now)
{
  yearNow = now.year();     //, DEC;
  monthNow = now.month();   //, DEC;
  dayNow = now.day();       //, DEC;
  hourNow = now.hour();     //, DEC;
  minuteNow = now.minute(); //, DEC;
  secondNow = now.second(); //, DEC;

  String time = padByte(hourNow) + ":" + padByte(minuteNow);
  //String time = "1553";
  debugln(time);
  
  char buf[time.length() + 1];
  time.toCharArray(buf, time.length() + 1);

  Serial.println(time);

  scale = 1;
  MoveTo(20, 20);
  PlotText(PSTR(time));

 debugln();
}

void updateScreenTime(DateTime &now)
{
  minuteNow = now.minute();

  if (minuteNow != oldMinuteNow)
  {
    debugln("Updating screen ...");
    printTime(now);
    oldMinuteNow = minuteNow;
  }
}