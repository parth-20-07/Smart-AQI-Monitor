#include <Arduino.h>
#include <RGB_Led_Control.cpp>
#include <Variable_Declaration.h>
#include <Sensor_Data_Collection.cpp>

void setup()
{
  Serial.begin(115200);
  setup_sensors();
  // setup_leds();
}

void loop()
{
  collect_gps_values();
  delay(1000);
}