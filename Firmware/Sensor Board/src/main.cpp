#include <Arduino.h>
#include <Sensor_Data_Collection.cpp>
#include "Variable_Declaration.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n\n/* ----------------------------- Starting Device ---------------------------- */");
  setup_sensors();
  Serial.println("/* -------------------------- Device Setup Complete ------------------------- */\n");
}

void loop()
{
  if ((millis() - sensor_data_collection_millis) > SENSOR_DATA_REFRESH_TIME)
  {
    String msg;
    /**
     * T => Temperature
     * H => Humidity
     * C => Carbondioxide
     * M => Carbonmonoxide
     * D => Dust PM AE 2.5
     * L => Light Intensity
     * O => Ozone
     */
    msg += collect_temperature_humidity_and_pressure_values();
    msg += collect_co2_values();
    msg += collect_co_sensor_values();
    // msg += collect_o3_sensor_values();
    msg += collect_dust_sensor_values();
    msg += collect_lux_values();
    msg += ",#";
    Serial.println(msg);
    Serial.println();
    sensor_data_collection_millis = millis();
  }
}