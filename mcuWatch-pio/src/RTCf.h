
void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
    // Call this if you notice something coming in on
    // the serial port. The stuff coming in should be in
    // the order YYMMDDwHHMMSS, with an 'x' at the end.
    boolean gotString = false;
    char inChar;
    byte temp1, temp2;
    char inString[20];

    byte j = 0;
    while (!gotString)
    {
        if (Serial.available())
        {
            inChar = Serial.read();
            inString[j] = inChar;
            j += 1;
            if (inChar == 'x')
            {
                gotString = true;
            }
        }
    }

    Serial.println(inString);
    // Read year first
    temp1 = (byte)inString[0] - 48;
    temp2 = (byte)inString[1] - 48;
    year = temp1 * 10 + temp2;
    Serial.print("Year: ");
    Serial.println(year);
    // now month
    temp1 = (byte)inString[2] - 48;
    temp2 = (byte)inString[3] - 48;
    month = temp1 * 10 + temp2;
    Serial.print("Month: ");
    Serial.println(month);
    // now date
    temp1 = (byte)inString[4] - 48;
    temp2 = (byte)inString[5] - 48;
    date = temp1 * 10 + temp2;
    Serial.print("Date: ");
    Serial.println(date);
    // now Day of Week
    dOW = (byte)inString[6] - 48;
    Serial.print("Dow: ");
    Serial.println(dOW);
    // now hour
    temp1 = (byte)inString[7] - 48;
    temp2 = (byte)inString[8] - 48;
    hour = temp1 * 10 + temp2;
    Serial.print("Hour: ");
    Serial.println(hour);
    // now minute
    temp1 = (byte)inString[9] - 48;
    temp2 = (byte)inString[10] - 48;
    minute = temp1 * 10 + temp2;
    Serial.print("Minute: ");
    Serial.println(minute);
    // now second
    temp1 = (byte)inString[11] - 48;
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
        clockIsSet = false;

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
        clockIsSet = true;
    }

    if (clockIsSet)
    {
        Serial.println("RTC is set");
        clockIsSet = false;
        Serial.println("Clearing serial buffer...");
        while (Serial.available())
            Serial.read();
    }
}

void printTime()
{
    for (int i = 0; i < 1; i++)
    {
        // delay(1000);
        Serial.print(myRTC.getYear(), DEC);
        Serial.print("-");
        Serial.print(myRTC.getMonth(century), DEC);
        Serial.print("-");
        Serial.print(myRTC.getDate(), DEC);
        Serial.print(" ");
        Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
        Serial.print(":");
        Serial.print(myRTC.getMinute(), DEC);
        Serial.print(":");
        Serial.println(myRTC.getSecond(), DEC);
    }
}