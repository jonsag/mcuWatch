// ------------------------------------------------------------------------------------
// Simple clock based on a DS3231 RTC and simple 16x2 LCD
// Setup includes 3 push buttons for up, down, and enter
// 15th July 2015, Andrew W. - arwhitus.weebly.com
// Visit arwhitus.weebly.com for more info or to contact author for any reason
// ------------------------------------------------------------------------------------

// include LCD and Wire library
#include <LiquidCrystal.h>
#include <Wire.h>

// define button pins
#define enterButtPin A2
#define upButtPin A1
#define downButtPin A0

// define RTC address
#define DS3231_I2C_ADDRESS 0x68

// define LCD pins and initialize LCD library
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// variables for button states
int enterState = 0;
int enterStateLast = 0;
int upState = 0;
int upStateLast = 0;
int downState = 0;
int downStateLast = 0;

// variables for ui
boolean blinkOn = true;     // visibility of ':' between hour and minutes
boolean setVisible = false; // visibility of the set time ui

// variables for new time
int setM = 0; // users new minute value
int setH = 0; // users new hour value

byte decToBcd(byte val) // convert normal decimal numbers to binary coded decimals
{
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) // convert binary coded decimal to normal decimal numbers
{
  return ((val / 16 * 10) + (val % 16));
}

void setup() // code that runs once at setup
{
  // start wire and lcd
  Wire.begin();
  lcd.begin(16, 2); //(col, rows)

  // intialize buttons as inputs
  pinMode(enterButtPin, INPUT);
  pinMode(upButtPin, INPUT);
  pinMode(downButtPin, INPUT);

  // Use below code to set time and date once from code
  // it will run at every reset and you will lose the time on the RTC
  // format is (sec, min, hr, day of week, day of month, month, year)
  // setRTCTime(0, 3, 23, 4, 15, 7, 15);
}

// code that runs on a constant loop
void loop()
{
  checkButtons();
  printTime();
}

// easy and dirty way to clear the LCD
void clearLCD()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
}

// set the time and date to the RTC
void setRTCTime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);                    // set next input to start at the seconds register
  Wire.write(decToBcd(second));     // set seconds
  Wire.write(decToBcd(minute));     // set minutes
  Wire.write(decToBcd(hour));       // set hours
  Wire.write(decToBcd(dayOfWeek));  // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month));      // set month
  Wire.write(decToBcd(year));       // set year (0 to 99)
  Wire.endTransmission();
}

// read the time and date from the RTC
void readRTCTime(byte *second, byte *minute, byte *hour, byte *dayOfWeek,
                 byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

// reads the RTC time and prints it to the top of the LCD
void printTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

  // retrieve time
  readRTCTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  // print to lcd top
  lcd.setCursor(0, 0);
  lcd.print(" Current: ");
  if (hour < 10)
  {
    lcd.print("0");
  }
  lcd.print(hour, DEC);
  if (blinkOn == true)
  {
    lcd.print(" ");
    blinkOn = false;
  }
  else if (blinkOn == false)
  {
    lcd.print(":");
    blinkOn = true;
  }
  if (minute < 10)
  {
    lcd.print("0");
  }
  lcd.print(minute, DEC);

  delay(100);
}

// checks if buttons are pressed and responds accordingly
void checkButtons()
{
  // check enter
  enterState = digitalRead(enterButtPin);
  if (enterState != enterStateLast)
  {
    if (enterState == HIGH)
    {
      if (setVisible == true)
      {
        byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
        readRTCTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

        setRTCTime(0, setM, setH, dayOfWeek, dayOfMonth, month, year);
        hideSet();
      }
      else if (setVisible == false)
      {
        showSet();
      }
    }
  }
  enterStateLast = enterState;

  // check up
  upState = digitalRead(upButtPin);
  if (upState != upStateLast)
  {
    if (upState == HIGH)
    {
      if (setVisible == true)
      {
        addMin();
        printSetTime();
      }
      else if (setVisible == false)
      {
        showSet();
      }
    }
  }
  upStateLast = upState;

  // check down
  downState = digitalRead(downButtPin);
  if (downState != downStateLast)
  {
    if (downState == HIGH)
    {
      if (setVisible == true)
      {
        subMin();
        printSetTime();
      }
      else if (setVisible == false)
      {
        showSet();
      }
    }
  }
  downStateLast = downState;
}

// displays the new time interface in the bottom of the LCD
void showSet()
{
  // update new time variables to current RTC values
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readRTCTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  setH = hour, DEC;
  setM = minute, DEC;

  // pints to the LCD
  lcd.setCursor(0, 1);
  lcd.print("   New: ");
  printSetTime();
  setVisible = true;
}

// hides the new time interface
void hideSet()
{
  clearLCD();
  setVisible = false;
}

// adds a minute to new time
void addMin()
{
  if (setM < 59)
  {
    setM++;
  }
  else if (setM == 59)
  {
    setM = 0;
    addHr();
  }
}

// subtracts a minute from new time
void subMin()
{
  if (setM > 0)
  {
    setM--;
  }
  else if (setM == 0)
  {
    setM = 59;
    subHr();
  }
}

// adds an hour to new time
void addHr()
{
  if (setH < 23)
  {
    setH++;
  }
  else if (setH == 23)
  {
    setH = 0;
  }
}

// subtracts an hour from new time
void subHr()
{
  if (setH > 0)
  {
    setH--;
  }
  else if (setH == 0)
  {
    setH = 23;
  }
}

// prints the new time values on the bottom of the LCD
void printSetTime()
{
  lcd.setCursor(8, 1);
  if (setH < 10)
  {
    lcd.print("0");
  }
  lcd.print(setH);
  lcd.print(":");
  if (setM < 10)
  {
    lcd.print("0");
  }
  lcd.print(setM);
}
