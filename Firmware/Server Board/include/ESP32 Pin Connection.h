#ifndef Pin_Connection_h
#define Pin_Connection_h

// GPIO Pins
#define ESP32_GPIO_2 2 // RGB_LED_CTRL_PIN
#define ESP32_GPIO_4 4 // CONFIGURATION BUTTON
#define ESP32_GPIO_5 5 // SD CHIP SELECT
#define ESP32_GPIO_12 12
#define ESP32_GPIO_13 13
#define ESP32_GPIO_14 14
#define ESP32_GPIO_15 15
#define ESP32_GPIO_16 16 // HSERIAL_RX
#define ESP32_GPIO_17 17 // HSERIAL_TX
#define ESP32_GPIO_25 25 // SERVER_BOARD_CONTROL_PIN
#define ESP32_GPIO_26 26 // SENSOR_BOARD_CONTROL_PIN
#define ESP32_GPIO_27 27
#define ESP32_GPIO_32 32
#define ESP32_GPIO_33 33
#define ESP32_GPIO_34 34 // BATTERY VOLTAGE INPUT
#define ESP32_GPIO_35 35
#define ESP32_GPIO_39 39
#define ESP32_GPIO_36 36

// Communication Pins
#define ESP_SPI_SCK 18  // SPI Clock
#define ESP_SPI_MISO 19 // SPI Master In Slave Out
#define ESP_SPI_MOSI 23 // SPI Master Out Slave In
#define ESP_I2C_SDA 21  // I2C Serial Data
#define ESP_I2C_SCL 22  // T2C Serial Clock

/* -------------------------------------------------------------------------- */
/*                               PIN CONNECTIONS                              */
/* -------------------------------------------------------------------------- */

/* ----------------------------- WS2812B RGB LED ---------------------------- */
#define RGB_LED_CTRL_PIN ESP32_GPIO_2

/* ---------------------- UART INTERBOARD COMMUNICATION --------------------- */
#define HSERIAL_RX ESP32_GPIO_16
#define HSERIAL_TX ESP32_GPIO_17
#define SERVER_BOARD_CONTROL_PIN ESP32_GPIO_25
#define SENSOR_BOARD_CONTROL_PIN ESP32_GPIO_26

/* ------------------------- WEBSERVER CONFIGURATION ------------------------ */
#define CONFIGURATION_BUTTON ESP32_GPIO_4

/* --------------------------- MICROSD CONNECTION --------------------------- */
#define SD_CHIP_SELECT ESP32_GPIO_5

/* --------------------------- BATTERY CONNECTION --------------------------- */
#define BATT_ADC_IN ESP32_GPIO_34

void setup_board_pins(void)
{
    Serial.println("Setting up Board Pins");
    pinMode(SENSOR_BOARD_CONTROL_PIN, OUTPUT);
    pinMode(SERVER_BOARD_CONTROL_PIN, INPUT);
    pinMode(CONFIGURATION_BUTTON, INPUT);
    digitalWrite(SENSOR_BOARD_CONTROL_PIN, HIGH);
}
#endif // Pin_Connection_h