
// https://werner.rothschopf.net/microcontroller/202112_arduino_esp_ntp_rtc_en.htm

/*
  NTP TZ DST - RTC fallback
  NetWork Time Protocol - Time Zone - Daylight Saving Time - Real Time Clock

  Target for this sketch is:
  - get the SNTP request running
  - set the timezone
  - (implicit) respect daylight saving time
  - how to "read" time to be printed to Serial.Monitor
  - get date/time from RTC until first NTP
  - Update date/time of RTC if NTP was successful

  This example is a stripped down version of the NTP-TZ-DST (v2) from the ESP8266
  based on the idea of https://forum.arduino.cc/t/set-ds3231-with-ntp-server/939845/9

  Hardware:
  NodeMCU / ESP8266 and DS3231 wiring
  D0 GPI16 (use for reset after deep sleep)
  D1 GPIO5 - I2C SCL
  D2 GPIO4 - I2C SDA

  Dependencies:
  ESP8266 Core 3.0.2 (we need at least 3.0.0 because of the parameter in the callback)

  by noiasca https://werner.rothschopf.net/microcontroller/202112_arduino_esp_ntp_rtc_en.htm
  2021-12-30 OK
*/

/*
// Sets the internal time epoch (seconds in GMT) microseconds
void setInternalTime(uint64_t epoch = 0, uint32_t us = 0)
{
    struct timeval tv;

    tv.tv_sec = epoch;
    tv.tv_usec = us;

    settimeofday(&tv, NULL);
}

void print10(int value) // prints an one digit integer with a leading 0
{
    if (value < 10)
        Serial.print("0");
    Serial.print(value);
}

// ESP8266 has no timegm, so we need to create our own...
// Take a broken-down time and convert it to calendar time (seconds since the Epoch 1970)
// Expects the input value to be Coordinated Universal Time (UTC)
// Parameters and values:
// - year  [1970..2038]
// - month [1..12]  ! - start with 1 for January
// - mday  [1..31]
// - hour  [0..23]
// - min   [0..59]
// - sec   [0..59]
// Code based on https://de.wikipedia.org/wiki/Unixzeit example "unixzeit"
int64_t getTimestamp(int year, int mon, int mday, int hour, int min, int sec)
{
    const uint16_t ytd[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};                //Anzahl der Tage seit Jahresanfang ohne Tage des aktuellen Monats und ohne Schalttag
int leapyears = ((year - 1) - 1968) / 4 - ((year - 1) - 1900) / 100 + ((year - 1) - 1600) / 400; // Anzahl der Schaltjahre seit 1970 (ohne das evtl. laufende Schaltjahr)
int64_t days_since_1970 = (year - 1970) * 365 + leapyears + ytd[mon - 1] + mday - 1;
if ((mon > 2) && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
    days_since_1970 += 1; // +Schalttag, wenn Jahr Schaltjahr ist
return sec + 60 * (min + 60 * (hour + 24 * days_since_1970));
}

void printRTC() // print time of RTC to Serial
{
    DateTime dtrtc = rtc.now(); // get date time from RTC i

    if (!dtrtc.isValid())
    {
        Serial.println(F("E103: RTC not valid"));
    }
    else
    {
        time_t newTime = getTimestamp(dtrtc.year(), dtrtc.month(), dtrtc.day(), dtrtc.hour(), dtrtc.minute(), dtrtc.second());
        Serial.print(F("RTC:"));
        Serial.print(newTime);
        Serial.print(" ");
        Serial.print(dtrtc.year());
        Serial.print("-");
        print10(dtrtc.month());
        Serial.print("-");
        print10(dtrtc.day());
        Serial.print(" ");
        print10(dtrtc.hour());
        Serial.print(":");
        print10(dtrtc.minute());
        Serial.print(":");
        print10(dtrtc.second());
        Serial.println(F(" UTC")); // remember: the RTC runs in UTC
    }
}

void getRTC() // get date/time from RTC and take over to internal clock
{
    Serial.println(F("getRTC --> update internal clock"));
    DateTime dtrtc = rtc.now(); // get date time from RTC i
    if (!dtrtc.isValid())
    {
        Serial.print(F("E127: RTC not valid"));
    }
    else
    {
        time_t newTime = getTimestamp(dtrtc.year(), dtrtc.month(), dtrtc.day(), dtrtc.hour(), dtrtc.minute(), dtrtc.second());
        setInternalTime(newTime);
        // Serial.print(F("UTC:")); Serial.println(newTime);
        printRTC();
    }
}

void setRTC() // set date/time of external RTC
{
    Serial.println(F("setRTC --> from internal time"));
    time_t now;          // this are the seconds since Epoch (1970) - seconds GMT
    tm tm;               // the structure tm holds time information in a more convenient way
    time(&now);          // read the current time and store to now
    gmtime_r(&now, &tm); // update the structure tm with the current GMT
    rtc.adjust(DateTime(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec));
}

void time_is_set(bool from_sntp)
{
    if (from_sntp) // needs Core 3.0.0 or higher!
    {
        Serial.println(F("The internal time is set from SNTP."));
        setRTC();
        printRTC();
    }
    else
    {
        Serial.println(F("The internal time is set."));
    }
}

// optional: by default, the NTP will be started after 60 secs
// lets start at a random time in 5 seconds
uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000()
{
    randomSeed(A0);
    return random(5000 + millis());
}

// optional: set SNTP interval

// uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
// {
// return 60 * 1000UL; // 12 hours
// }

void showTime() // print local time to serial
{
    time_t now; // this are the seconds since Epoch (1970) GMT
    tm tm;      // a readable structure

    time(&now);             // read the current time and store to now
    localtime_r(&now, &tm); // update the structure tm with the current time

    char buf[50];
    strftime(buf, sizeof(buf), " %F %T %Z wday=%w", &tm); // https://www.cplusplus.com/reference/ctime/strftime/

    Serial.print("now:");
    Serial.print(now); // in UTC!
    Serial.print(buf);

    if (tm.tm_isdst == 1)
    { // Daylight Saving Time flag
        Serial.print(" DST");
    }
    else
    {
        Serial.print(" standard");
    }
    Serial.println();
}

    void loop() {
      showTime();
      delay(1000);     // dirty delay
    }
    */

void getNetworkTime()
{
    debugMessln("Getting network time ...");

    timeClient.update();

#if DEBUG
    Serial.println("********** Network time **********");

    time_t epochTime = timeClient.getEpochTime();
    Serial.print("Epoch Time: ");
    Serial.println(epochTime);

    String formattedTime = timeClient.getFormattedTime();
    Serial.print("Formatted Time: ");
    Serial.println(formattedTime);

    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour);

    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute);

    int currentSecond = timeClient.getSeconds();
    Serial.print("Seconds: ");
    Serial.println(currentSecond);

    String weekDay = dayName[timeClient.getDay()];
    Serial.print("Week Day: ");
    Serial.println(weekDay);

    // Get a time structure
    struct tm *ptm = gmtime((time_t *)&epochTime);

    int monthDay = ptm->tm_mday;
    Serial.print("Month day: ");
    Serial.println(monthDay);

    int currentMonth = ptm->tm_mon + 1;
    Serial.print("Month: ");
    Serial.println(currentMonth);

    String currentMonthName = monthName[currentMonth - 1];
    Serial.print("Month name: ");
    Serial.println(currentMonthName);

    int currentYear = ptm->tm_year + 1900;
    Serial.print("Year: ");
    Serial.println(currentYear);

    // Print complete date:
    String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
    Serial.print("Current date: ");
    Serial.println(currentDate);

    Serial.println("********** Network time **********");
    Serial.println();

#endif
}
