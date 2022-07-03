#ifndef RGB_Led_Control_cpp
#define RGB_Led_Control_cpp
#include <FastLED.h> //Reference: https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
#include "ESP32 Pin Connection.h"
#include "Variable_Declaration.h"

/* ---------------------------- Basic Definition ---------------------------- */
#define NUM_OF_LEDS 6
CRGB leds[NUM_OF_LEDS];

/* -------------------------- FUNCTION DECLARATION -------------------------- */
void setup_leds(void);
void set_specific_led(uint8_t led_number, uint8_t red_color, uint8_t green_color, uint8_t blue_color);

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

    for (size_t i = 1; i <= NUM_OF_LEDS; i++) // Turning All Leds Black
        leds[i - 1] = CRGB(BLACK);
    FastLED.show();

    for (size_t i = 1; i <= NUM_OF_LEDS; i++)
    {
        set_specific_led(i, RED);
        delay(250);
        set_specific_led(i, GREEN);
        delay(250);
        set_specific_led(i, BLUE);
        delay(250);
    }

    for (size_t i = 1; i <= NUM_OF_LEDS; i++) // Turning All Leds Black
        leds[i - 1] = CRGB(BLACK);
    FastLED.show();

    for (size_t i = 1; i <= NUM_OF_LEDS; i++) // Turning individual LEDs White
    {
        set_specific_led(i, DIM_WHITE);
        delay(250);
    }
    Serial.println("LED Setup Complete");
}

void set_specific_led(uint8_t led_number, uint8_t red_color, uint8_t green_color, uint8_t blue_color)
{
    leds[led_number - 1] = CRGB(red_color, green_color, blue_color);
    FastLED.show();
}
#endif // RGB_Led_Control_cpp