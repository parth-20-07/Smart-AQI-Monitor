#ifndef Battery_Configuration_cpp
#define Battery_Configuration_cpp
#include <Arduino.h>
#include "ESP32 Pin Connection.h"

#define BATTERY_INPUT_ADC BATT_ADC_IN
#define MIN_BATTERY_ADC 1
#define MAX_BATTERY_ADC 4000

void battery_setup(void)
{
    analogReadResolution(12);
    adcAttachPin(BATTERY_INPUT_ADC);
    Serial.println("Battery Setup Complete");
}

String battery_level_percentage(void)
{
    Serial.println("Reading Battery");
    uint16_t battery_adc_value = analogRead(BATTERY_INPUT_ADC);
    float float_battery_level = ((battery_adc_value - MIN_BATTERY_ADC) * 100) / (MAX_BATTERY_ADC - MIN_BATTERY_ADC);
    uint8_t battery_level = (uint8_t)float_battery_level;
    Serial.println("Battery Level: " + (String)battery_level + "%");
    return (",B:" + (String)battery_level);
}

void run_battery_calibration(void)
{
    while (1)
        Serial.println("Battery ADC: " + (String)analogRead(BATTERY_INPUT_ADC));
}
#endif