#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include "Variable_Declaration.h"
#include "WiFi.h"

/* -------------------------------------------------------------------------- */
/*                              BASIC DEFINITION                              */
/* -------------------------------------------------------------------------- */
const char *ntpServer = "asia.pool.ntp.org";
const long gmtOffset_sec = 19800; // +5:30 = (5*60*60) + (30*60) = 19800
const int daylightOffset_sec = 0; // India doesn't observe DayLight Saving

/* --------------------------- FUNCTION DEFINITION -------------------------- */
void connect_to_ntp(void);
bool printLocalTime(void);

/* -------------------------- FUNCTION DECLARATION -------------------------- */
void connect_to_ntp(void)
{
    Serial.println("Connecting to NTP");
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Setting up NTP Server");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Configure NTP
        printLocalTime();                                         // Fetching time from NTP
    }
    else
        Serial.println("WiFi Not Connected");
    return;
}

/**
 * @brief Tries to get local time from NTP:
 * -> If it's successful, The year, month, date, hour, minutes, seconds is updated to global variables with time from NTP,
 * and the time is saved to RTC.
 * -> If it fails, the fuction is called rtc_get_time()
 */
bool printLocalTime(void)
{
    Serial.println("Updating Time from NTP");
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("NTP Failed to Update");
        return false;
    }
    Serial.println("NTP Connect Success");
    year = timeinfo.tm_year - 100 + 2000;
    month = timeinfo.tm_mon + 1;
    date = timeinfo.tm_mday;
    hour = timeinfo.tm_hour;
    minutes = timeinfo.tm_min;
    seconds = timeinfo.tm_sec;
    Serial.println("NTP Update Successful");
    String day = (String)year + "/" + (String)month + "/" + (String)date;
    String time = (String)hour + ":" + (String)minutes + ":" + (String)seconds;
    Serial.println("Time from NTP: " + day + ' ' + time);
    delay(10);
    return true;
}
