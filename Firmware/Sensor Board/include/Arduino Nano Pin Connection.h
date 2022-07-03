#ifndef PIN_CONNECTION_H
#define PIN_CONNECTION_H

// GPIO PINS
#define NANO_GPIO_2 2 // MHZ-16 NDIR CO2 SENSOR TX
#define NANO_GPIO_3 3 // MHZ-16 NDIR CO2 SENSOR RX
#define NANO_GPIO_4 4 // ZE03 CO SENSOR RX
#define NANO_GPIO_5 5 // ZE03 CO SENSOR TX
#define NANO_GPIO_6 6 // ZH06 LASER DUST SENSOR TX
#define NANO_GPIO_7 7 // ZH06 LASER DUST SENSOR RX
#define NANO_GPIO_8 8 // hSerial RX
#define NANO_GPIO_9 9 // hSerial TX
#define NANO_GPIO_10 10
#define NANO_AI_0 A0 // ZE03 CO SENSOR VOUT
#define NANO_AI_1 A1 // SERVER BOARD CONTROL PIN
#define NANO_AI_2 A2 // SENSOR BOARD CONTROL PIN
#define NANO_AI_3 A3
#define NANO_AI_6 A6
#define NANO_AI_7 A7

// COMMUNICATION PINS
#define SERIAL_TX 0
#define SERIAL_RX 1
#define SPI_MOSI 11
#define SPI_MISO 12
#define SPI_SCK 13
#define I2C_SDA A4
#define I2C_SCL A5

/* -------------------------------------------------------------------------- */
/*                               PIN CONNECTION                               */
/* -------------------------------------------------------------------------- */

/* ------------------------ MHZ - 16 NDIR CO2 SENSOR ------------------------ */
#define MHZ16_NDIR_CO2_SENSOR_RX NANO_GPIO_2
#define MHZ16_NDIR_CO2_SENSOR_TX NANO_GPIO_3

/* ----------------------------- ZE03 CO SENSOR ----------------------------- */
#define ZE03_CO_SENSOR_TX NANO_GPIO_5
#define ZE03_CO_SENSOR_RX NANO_GPIO_4
#define ZE03_CO_SENSOR_VOUT NANO_AI_0

/* ------------------------- ZH06 LASER DUST SENSOR ------------------------- */
#define ZH06_LASER_DUST_SENSOR_RX NANO_GPIO_7
#define ZH06_LASER_DUST_SENSOR_TX NANO_GPIO_6

/* ----------------- HTU21D TEMPERATURE AND HUMIDITY SENSOR ----------------- */
// I2C Connection

/* ---------------------------- BH1750 LUX SENSOR --------------------------- */
// I2C Connection

/* -------------------- UART COMMUNICATION BETWEEN BOARDS ------------------- */
#define HSERIAL_RX NANO_GPIO_8
#define HSERIAL_TX NANO_GPIO_9
#define SERVER_BOARD_CONTROL_PIN NANO_AI_1
#define SENSOR_BOARD_CONTROL_PIN NANO_AI_2

void setup_board_pins(void)
{
    Serial.println("Setting up Board Pins");
    pinMode(SENSOR_BOARD_CONTROL_PIN, INPUT);
    pinMode(SERVER_BOARD_CONTROL_PIN, OUTPUT);
    digitalWrite(SERVER_BOARD_CONTROL_PIN, HIGH);
}
#endif