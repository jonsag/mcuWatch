DateTime readEEPROMdatetime(int EEPROMaddress)
{
    //    #if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) || defined(ARDUINO_ESP8266_ESP01) || defined(ARDUINO_ESP32_DEV)
    debugMessln("Initializing EEPROM ...");
    EEPROM.begin(EEPROM_SIZE); // initialize EEPROM

    debugMessln("Reading EEPROM ...");
    EEPROM.get(EEPROMaddress, dtAnswer);

    debugMessln("Closing EEPROM ...");
    EEPROM.end();

    debugMessln();

    return dtAnswer;
    //#endif // esp8266
}

byte readEEPROMbyte(int EEPROMaddress)
{
    //    #if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) || defined(ARDUINO_ESP8266_ESP01) || defined(ARDUINO_ESP32_DEV)
    debugMessln("Initializing EEPROM ...");
    EEPROM.begin(EEPROM_SIZE); // initialize EEPROM

    debugMessln("Reading EEPROM ...");
    EEPROM.get(dtNtpAddress, byteAnswer);

    debugMessln("Closing EEPROM ...");
    EEPROM.end();

    debugMessln();

    return byteAnswer;
    //#endif // esp8266
}

void getDtNTP()
{

    //dtNTP = readEEPROMdatetime(dtNtpAddress);

    debugMessln("Time when RTC was synced with an ntp server: ");
    //prettyPrintDateTime(dtNTP);
    Serial.print(readEEPROMbyte(dtNtpAddress));
    debugMessln();
}