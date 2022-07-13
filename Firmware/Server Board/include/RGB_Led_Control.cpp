#ifndef RGB_Led_Control_cpp
#define RGB_Led_Control_cpp
#include <FastLED.h> //Reference: https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
#include "ESP32 Pin Connection.h"
#include "Variable_Declaration.h"

/* ----------------------------- RGB LED Colors ----------------------------- */
#define RED 255, 0, 0
#define ORANGE 255, 165, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define WHITE 255, 255, 255
#define DIM_WHITE 10, 10, 10
#define BLACK 0, 0, 0

/* ---------------------------- Basic Definition ---------------------------- */
#define NUM_OF_LEDS (NUM_OF_PARAMS + 1)
CRGB leds[NUM_OF_LEDS];

/* -------------------------- FUNCTION DECLARATION -------------------------- */
void setup_leds(void);
void set_specific_led(uint8_t led_number, uint8_t red_color, uint8_t green_color, uint8_t blue_color);
void set_all_leds(uint8_t red_color, uint8_t green_color, uint8_t blue_color);
/* --------------------------- FUNCTION DEFINITION -------------------------- */
void setup_leds(void)
{
    Serial.println("Setting Up LEDs");
    FastLED.addLeds<WS2812, RGB_LED_CTRL_PIN, GRB>(leds, NUM_OF_LEDS);
    for (size_t i = 1; i <= NUM_OF_LEDS; i++) // Turning individual LEDs White
    {
        set_specific_led(i, WHITE);
        delay(250);
    }

    set_all_leds(BLACK);     // Turning All Leds Black
    set_all_leds(RED);       // Turning All Leds Red
    set_all_leds(GREEN);     // Turning All Leds Green
    set_all_leds(BLUE);      // Turning All Leds Blue
    set_all_leds(BLACK);     // Turning All Leds Black
    set_all_leds(DIM_WHITE); // Turning individual LEDs White
    Serial.println("LED Setup Complete");
}

void set_specific_led(uint8_t led_number, uint8_t red_color, uint8_t green_color, uint8_t blue_color)
{
    leds[led_number - 1] = CRGB(red_color, green_color, blue_color);
    FastLED.show();
}

void set_all_leds(uint8_t red_color, uint8_t green_color, uint8_t blue_color)
{
    for (size_t i = 0; i < NUM_OF_LEDS; i++)
        leds[i] = CRGB(red_color, green_color, blue_color);
    FastLED.show();
}
#endif // RGB_Led_Control_cpp