#include <Arduino.h>
#include <Sensor_Data_Collection.cpp>
#include "Arduino Nano Pin Connection.h"
#include "Variable_Declaration.h"
#include "Serial_InterBoard_Communication.cpp"

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n\n/* ----------------------------- Starting Device ---------------------------- */");
  setup_board_pins();
  setup_sensors();
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
   * V => Volatile Organic Components
   */
  msg += collect_temperature_humidity_and_pressure_values();
  delay(500);
  msg += collect_co2_values();
  delay(500);
  msg += collect_co_sensor_values();
  delay(500);
  msg += collect_dust_sensor_values();
  delay(500);
  msg += collect_lux_values();
  delay(500);
  // msg += collect_voc_values();
  delay(500);
  Serial.println(msg);
  send_message(msg);
  Serial.println();
  delay(SENSOR_DATA_REFRESH_TIME_IN_MINUTES * 60000);
}