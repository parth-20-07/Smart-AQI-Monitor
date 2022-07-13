#ifndef Variable_Declaration_h
#define Variable_Declaration_h
#include <Arduino.h>

/* --------------------------- Sensor Data Values --------------------------- */
// T => Temperature
// H => Humidity
// C => Carbondioxide
// M => Carbonmonoxide
// D => Dust PM AE 2.5
// L => Light Intensity
// V => VOC
uint16_t temperature, humidity, carbondioxide, carbonmonoxide, pm_ae_2_5, lux, voc;
uint8_t battery;
#define NUM_OF_PARAMS 7
uint16_t params_range[NUM_OF_PARAMS * 2];

/* ----------------------- WiFi Configuration Details ----------------------- */
#define SSID_CHAR_LENGTH 50
#define PASSWORD_CHAR_LENGTH 100
char ssid[SSID_CHAR_LENGTH], password[PASSWORD_CHAR_LENGTH];
bool aws_connect_flag = false;
bool backlog_file_available = false;
uint32_t last_aws_upload;
#define AWS_UPLOAD_TIME_IN_MINUTES 5 // TODO: AWS Update Time Interval
bool internet_connection_status = false, wifi_connection_status = false;

/* ------------------------- MICRO SD CONFIGURATION ------------------------- */
#define SSID_FILE "/ssid.txt"
#define PASSWORD_FILE "/pwd.txt"
#define BACKLOG_FILE "/backup.txt"

/* ------------------------- TIME CONFIGURATION DATA ------------------------ */
uint16_t year;
uint8_t month, date, hour, minutes, seconds;
String formatted_day, formatted_time;

#endif // Variable_Declaration_h
