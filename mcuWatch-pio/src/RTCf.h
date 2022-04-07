
void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    // boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    char inString[20];
    byte j = 0;

    // while (!gotString)
    while (true)
    {
        if (Serial.available())
        {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x')
            {
                // gotString = true;
                break;
            }
        }
    }

    Serial.println(inString);

    temp1 = (byte)inString[0] - 48; // Read year first
    temp2 = (byte)inString[1] - 48;
    year = temp1 * 10 + temp2;
    Serial.print("Year: ");
    Serial.println(year);

    temp1 = (byte)inString[2] - 48; // now month
    temp2 = (byte)inString[3] - 48;
    month = temp1 * 10 + temp2;
    Serial.print("Month: ");
    Serial.println(month);

    temp1 = (byte)inString[4] - 48; // now date
    temp2 = (byte)inString[5] - 48;
    date = temp1 * 10 + temp2;
    Serial.print("Date: ");
    Serial.println(date);

    dOW = (byte)inString[6] - 48; // now Day of Week
    Serial.print("Dow: ");
    Serial.println(dOW);

    temp1 = (byte)inString[7] - 48; // now hour
    temp2 = (byte)inString[8] - 48;
    hour = temp1 * 10 + temp2;
    Serial.print("Hour: ");
    Serial.println(hour);

    temp1 = (byte)inString[9] - 48; // now minute
    temp2 = (byte)inString[10] - 48;
    minute = temp1 * 10 + temp2;
    Serial.print("Minute: ");
    Serial.println(minute);

    temp1 = (byte)inString[11] - 48; // now second
    temp2 = (byte)inString[12] - 48;
    second = temp1 * 10 + temp2;
    Serial.print("Second: ");
    Serial.println(second);
}

void setTime()
{

    // If something is coming in on the serial line, it's
    // a time correction so set the clock accordingly.
    if (Serial.available())
    {
        // clockIsSet = false;

        Serial.println("Preparing to set RTC...");

        getDateStuff(year, month, date, dOW, hour, minute, second);

        myRTC.setClockMode(false); // set to 24h
        // setClockMode(true); // set to 12h

        myRTC.setYear(year);
        myRTC.setMonth(month);
        myRTC.setDate(date);
        myRTC.setDoW(dOW);
        myRTC.setHour(hour);
        myRTC.setMinute(minute);
        myRTC.setSecond(second);

        /*
        // Test of alarm functions
        // set A1 to one minute past the time we just set the clock
        // on current day of week.
        myRTC.setA1Time(dOW, hour, minute + 1, second, 0x0, true,
                        false, false);
        // set A2 to two minutes past, on current day of month.
        myRTC.setA2Time(date, hour, minute + 2, 0x0, false, false,
                        false);
        // Turn on both alarms, with external interrupt
        myRTC.turnOnAlarm(1);
        myRTC.turnOnAlarm(2);
        */

        Serial.println();
        Serial.println("Finished!");
        // clockIsSet = true;
    }

    /*
        if (clockIsSet)
        {
            Serial.println("RTC is set");
            clockIsSet = false;
            Serial.println("Clearing serial buffer...");
            while (Serial.available())
                Serial.read();
        }
        */
}

String padByte(byte &k)
{
    String myString = String(k);
    if (myString.length() < 2)
    {
        myString = "0" + myString;
    }

    return myString;
}

void getTime()
{
    yearNow = (myRTC.getYear(), DEC);
    monthNow = (myRTC.getMonth(century), DEC);
    dateNow = (myRTC.getDate(), DEC);
    hourNow = (myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
    minuteNow = (myRTC.getMinute(), DEC);
    secondNow = (myRTC.getSecond(), DEC);
}

void printRawTime(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    Serial.print(year);
    Serial.print("-");
    Serial.print(month);
    Serial.print("-");
    Serial.print(date);
    Serial.print(" ");
    Serial.print(hour); // 24-hr
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);
}

void printFormattedTime(byte &year, byte &month, byte &date, byte &dOW,
                        byte &hour, byte &minute, byte &second)
{
    Serial.print(padByte(year));
    Serial.print("-");
    Serial.print(padByte(month));
    Serial.print("-");
    Serial.print(padByte(date));
    Serial.print(" ");
    Serial.print(padByte(hour)); // 24-hr
    Serial.print(":");
    Serial.print(padByte(minute));
    Serial.print(":");
    Serial.println(padByte(second));
}