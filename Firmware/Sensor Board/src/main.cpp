#include <Arduino.h>
#include <Sensor_Data_Collection.cpp>
#include "Variable_Declaration.h"
#include "Serial_InterBoard_Communication.cpp"

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\n/* ----------------------------- Starting Device ---------------------------- */");
  setup_sensors();
  setup_board_pins();
  Serial.println("/* -------------------------- Device Setup Complete ------------------------- */\n");
}

void loop()
{
  Serial.println("\n\n/* -------------------------- Reading Sensor Values ------------------------- */");
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
  delay(500);
  msg += collect_co2_values();
  delay(500);
  msg += collect_co_sensor_values();
  delay(500);
  // msg += collect_o3_sensor_values();
  delay(500);
  msg += collect_dust_sensor_values();
  delay(500);
  msg += collect_lux_values();
  delay(500);
  msg += collect_gps_values();
  delay(500);
  msg += ",#";
  Serial.println(msg);
  Serial.println();
  send_message(msg);
  delay(SENSOR_DATA_REFRESH_TIME_IN_SECONDS * 1000);
}