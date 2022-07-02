#ifndef Variable_Declaration_h
#define Variable_Declaration_h
#include <Arduino.h>

/* ----------------------------- RGB LED Colors ----------------------------- */
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0

/* --------------------------- Sensor Data Values --------------------------- */
// T => Temperature
// H => Humidity
// C => Carbondioxide
// M => Carbonmonoxide
// D => Dust PM AE 2.5
// L => Light Intensity
uint16_t temperature, humidity, carbondioxide, carbonmonoxide, pm_ae_2_5, lux;

#endif // Variable_Declaration_h
