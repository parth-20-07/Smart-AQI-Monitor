#ifndef Sensor_Data_Collection_cpp
#define Sensor_Data_Collection_cpp

#include "Arduino.h"
#include "Arduino Nano Pin Connection.h"

#define HTU21D_TEMP_HUMIDITY_SENSOR // https://learn.sparkfun.com/tutorials/htu21d-humidity-sensor-hookup-guide
// #define BME280_TEMP_HUMIDITY_PRESSURE_SENSOR // https://randomnerdtutorials.com/bme280-sensor-arduino-pressure-temperature-humidity/
// #define MHZ19C_CO2_SENSOR                    // https://github.com/strange-v/MHZ19
#define MHZ16C_CO2_SENSOR // https://github.com/datphys/MHZ16-CO2-sensor
// #define TSL2561_LUX_SENSOR                   // https://learn.sparkfun.com/tutorials/tsl2561-luminosity-sensor-hookup-guide/all
#define PMS_DUST_SENSOR   // https://how2electronics.com/interfacing-pms5003-air-quality-sensor-arduino/
#define ZE03_CO_SENSOR    // https://github.com/fega/winsen-ze03-arduino-library
#define BH1750_LUX_SENSOR // https://randomnerdtutorials.com/arduino-bh1750-ambient-light-sensor/
#define NEO_6M_GPS_MODULE // https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/

/* ---------------------------- BASIC DEFINITION ---------------------------- */
#ifdef HTU21D_TEMP_HUMIDITY_SENSOR
#include <Wire.h>
#include "HTU21D.h"
HTU21D temperature_and_humidity_sensor; // Create an instance of the object
#endif                                  // HTU21D_TEMP_HUMIDITY_SENSOR

#ifdef BME280_TEMP_HUMIDITY_PRESSURE_SENSOR
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 temperature_humidity_and_pressure_sensor;
#endif // BME280_TEMP_HUMIDITY_PRESSURE_SENSOR

#ifdef MHZ19C_CO2_SENSOR
#include "MHZ19.h"
#include <SoftwareSerial.h>
SoftwareSerial mhz19_serial(MHZ19_CO2_SENSOR_RX, MHZ19_CO2_SENSOR_TX);
MHZ19 carbondioxide_sensor(mhz19_serial); // Constructor for library
#endif                                    // MHZ19C_CO2_SENSOR

#ifdef MHZ16C_CO2_SENSOR
#include <Mhz16.h>
Mhz16 carbondioxide_sensor(MHZ16_NDIR_CO2_SENSOR_RX, MHZ16_NDIR_CO2_SENSOR_TX);
#endif // MHZ16C_CO2_SENSOR

#ifdef TSL2561_LUX_SENSOR
#include <Wire.h>
#include <SparkFunTSL2561.h>
SFE_TSL2561 light_sensor; // Create an SFE_TSL2561 object
boolean gain;             // Gain setting, 0 = X1, 1 = X16;
unsigned int ms;          // Integration ("shutter") time in milliseconds
#endif                    // TSL2561_LUX_SENSOR

#ifdef PMS_DUST_SENSOR
#include <PMS.h>
#include <SoftwareSerial.h>
SoftwareSerial PMSerial(ZH06_LASER_DUST_SENSOR_RX, ZH06_LASER_DUST_SENSOR_TX);
PMS pms(PMSerial);
#endif // PMS_DUST_SENSOR

#ifdef ZE03_CO_SENSOR
#include <WinsenZE03.h>
#include <SoftwareSerial.h>
SoftwareSerial ze03_serial(ZE03_CO_SENSOR_RX, ZE03_CO_SENSOR_TX);
WinsenZE03 co_sensor;
#endif // ZE03_CO_SENSOR

#ifdef BH1750_LUX_SENSOR
#include <Wire.h>
#include <BH1750.h>
BH1750 lux_sensor;
#endif // BH1750_LUX_SENSOR

#ifdef NEO_6M_GPS_MODULE
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(NEO_6M_GPS_SENSOR_RX, NEO_6M_GPS_SENSOR_TX);
TinyGPSPlus gps; // The TinyGPS++ object
#endif           // NEO_6M_GPS_MODULE

/* -------------------------------------------------------------------------- */
/*                             FUNCTION DEFINITION                            */
/* -------------------------------------------------------------------------- */

/* ------------------------------ SENSOR SETUP ------------------------------ */
void setup_sensors(void)
{
    Serial.println("Setting up Sensors");

#ifdef HTU21D_TEMP_HUMIDITY_SENSOR
    Serial.println("Setting up Temperature and Humidity Sensor");
    temperature_and_humidity_sensor.begin();
#endif // HTU21D_TEMP_HUMIDITY_SENSOR

#ifdef BME280_TEMP_HUMIDITY_PRESSURE_SENSOR
    Serial.println("Setting up Temperature and Humidity Sensor");
    if (!temperature_humidity_and_pressure_sensor.begin(0x76))
        Serial.println("Cannot setup BME280 Temperature, Humidity and Pressure Sensor");
    else
        Serial.println("Setup BME280 Temperature, Humidity and Pressure Sensor");
#endif // BME280_TEMP_HUMIDITY_PRESSURE_SENSOR

#ifdef MHZ19C_CO2_SENSOR
    Serial.println("Setting up MHZ-19C CO2 Sensor");
    MHZ19CSerial.begin(9600);
    carbondioxide_sensor.begin(MHZ19CSerial);
    carbondioxide_sensor.autoCalibration();
#endif // MHZ19C_CO2_SENSOR

#ifdef MHZ16C_CO2_SENSOR
    Serial.println("Setting up MHZ-16C CO2 Sensor");
#endif // MHZ16C_CO2_SENSOR

#ifdef TSL2561_LUX_SENSOR
    Serial.println("Setting up Lux Sensor");
    light_sensor.begin();
    gain = 0;
    unsigned char time = 2;
    Serial.println("Set timing...");
    light_sensor.setTiming(gain, time, ms);
    Serial.println("Powerup..."); // To start taking measurements, power up the sensor
    light_sensor.setPowerUp();
#endif // TSL2561_LUX_SENSOR

#ifdef PMS_DUST_SENSOR
    Serial.println("Setting up PMS Dust Sensor");
#endif // PMS_DUST_SENSOR

#ifdef ZE03_CO_SENSOR
    Serial.println("Setting up Winsen ZE03 CO Sensor");
#endif // ZE03_CO_SENSOR

#ifdef BH1750_LUX_SENSOR
    Serial.println("Setting up BH1750 Lux Sensor");
    Wire.begin();
    lux_sensor.begin();
#endif // BH1750_LUX_SENSOR

#ifdef NEO_6M_GPS_MODULE
    Serial.println("Setting up Neo-6M GPS Sensor");
#endif // NEO_6M_GPS_MODULE
}

/* --------------------------- COLLECT SENSOR DATA -------------------------- */
#ifdef HTU21D_TEMP_HUMIDITY_SENSOR
String collect_temperature_humidity_and_pressure_values(void)
{
    Serial.println("Reading HTU21D");
    uint8_t humd = temperature_and_humidity_sensor.readHumidity();
    uint8_t temp = temperature_and_humidity_sensor.readTemperature();
    // Serial.println("Temperature: " + (String)temp + "C");
    // Serial.println("Humidity: " + (String)humd + "%");
    return ("T:" + (String)temp + ",H:" + (String)humd);
}
#endif // HTU21D_TEMP_HUMIDITY_SENSOR

#ifdef BME280_TEMP_HUMIDITY_PRESSURE_SENSOR
String collect_temperature_and_humidity_values(void)
{
    Serial.println("Reading BME280");
    uint8_t humd = temperature_humidity_and_pressure_sensor.readHumidity();
    uint8_t temp = temperature_humidity_and_pressure_sensor.readTemperature();
    uint8_t pressure = (temperature_humidity_and_pressure_sensor.readPressure() / 100.0F);
    Serial.println("Temperature: " + (String)temp + "C");
    Serial.println("Humidity: " + (String)humd + "%");
    Serial.println("Humidity: " + (String)pressure + "hPa");
    return (",T:" + (String)temp + ",H:" + (String)humd + ",P:" + (String)pressure);
}
#endif // BME280_TEMP_HUMIDITY_PRESSURE_SENSOR

#ifdef MHZ19C_CO2_SENSOR
String collect_co2_values(void)
{
    Serial.println("Reading MHZ19C");
    uint16_t CO2 = carbondioxide_sensor.getCO2();
    Serial.println("CO2: " + (String)CO2 + "ppm");
    return (",C:" + (String)CO2);
}
#endif // MHZ19C_CO2_SENSOR

#ifdef MHZ16C_CO2_SENSOR
String collect_co2_values(void)
{
    Serial.println("Reading MHZ16C NDIR");
    carbondioxide_sensor.begin(9600);
    delay(50);
    uint16_t CO2 = carbondioxide_sensor.readGasConcentration();
    // Serial.println("CO2: " + (String)CO2 + "ppm");
    carbondioxide_sensor.end();
    delay(50);
    return (",C:" + (String)CO2);
}
#endif // MHZ16C_CO2_SENSOR

#ifdef TSL2561_LUX_SENSOR
String collect_lux_values(void)
{
    Serial.println("Reading TSL2561");
    double lux;
    unsigned int data0, data1;
    if (light_sensor.getData(data0, data1)) // getData() returned true, communication was successful
    {
        Serial.print("data0: ");
        Serial.print(data0);
        Serial.print(" data1: ");
        Serial.println(data1);
        boolean good;                                            // True if neither sensor is saturated
        good = light_sensor.getLux(gain, ms, data0, data1, lux); // Perform lux calculation:
        Serial.print("Lux: " + (String)lux);                     // Print out the results:
        if (good)
            Serial.println(" | GOOD");
        else
            Serial.println(" | BAD");
    }
    return (",L:" + (String)lux);
}
#endif // TSL2561_LUX_SENSOR

#ifdef PMS_DUST_SENSOR
String collect_dust_sensor_values(void)
{
    Serial.print("Reading PMS Dust Sensor");
    PMSerial.begin(9600);
    delay(50);
    PMS::DATA data;
    uint16_t pm_ae_1_0, pm_ae_2_5, pm_ae_10;
    while (!pms.read(data))
    {
        Serial.print(".");
        delay(50);
    }
    Serial.println();
    pm_ae_1_0 = data.PM_AE_UG_1_0;
    pm_ae_2_5 = data.PM_AE_UG_2_5;
    pm_ae_10 = data.PM_AE_UG_10_0;
    // Serial.println("PM AE 1: " + (String)pm_ae_1_0);
    // Serial.println("PM AE 2.5: " + (String)pm_ae_2_5);
    // Serial.println("PM AE 10: " + (String)pm_ae_10);
    PMSerial.end();
    delay(50);
    return (",D:" + (String)pm_ae_2_5);
}
#endif // PMS_DUST_SENSOR

#ifdef ZE03_CO_SENSOR
String collect_co_sensor_values(void)
{
    Serial.println("Reading Winsen ZE03 CO Sensor");
    ze03_serial.begin(9600);
    co_sensor.begin(&ze03_serial, CO);
    co_sensor.setAs(QA); // use ACTIVE, for the active mode
    uint16_t co = co_sensor.readManual();
    ze03_serial.end();
    return (",M:" + (String)co);
}
#endif // ZE03_CO_SENSOR

#ifdef BH1750_LUX_SENSOR
String collect_lux_values(void)
{
    Serial.println("Reading BH1750");
    uint16_t lux = lux_sensor.readLightLevel();
    // Serial.println("Lux: " + (String)lux + " lx");
    return (",L:" + (String)lux);
}
#endif // BH1750_LUX_SENSOR

#ifdef NEO_6M_GPS_MODULE
String collect_gps_values(void)
{
    Serial.print("Reading Neo-6M GPS");
    gpsSerial.begin(9600);
    delay(1000);
    String return_msg = "";
    while (!gpsSerial.available())
    {
        delay(50);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("GPS Connected!");
    while (gpsSerial.available() > 0)
        if (gps.encode(gpsSerial.read()))
        {
            Serial.println("GPS Encode Successful");
            if (gps.location.isValid())
            {
                float latitude = gps.location.lat();
                float longitude = gps.location.lng();
                Serial.println("Latitude: " + (String)latitude);
                Serial.println("Longitude: " + (String)longitude);
                return_msg = ",X:" + (String)latitude + ",Y:" + (String)longitude;
            }
            else
                Serial.println("GPS Fetch Failure");
        }
        else
            Serial.println("GPS Encode Failed");
    gpsSerial.end();
    return return_msg;
}
#endif // NEO_6M_GPS_MODULE

#endif // Sensor_Data_Collection_cpp
