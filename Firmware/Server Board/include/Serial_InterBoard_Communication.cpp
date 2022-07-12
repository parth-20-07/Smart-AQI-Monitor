#include <Arduino.h>
#include "HardwareSerial.h"
#include "ESP32 Pin Connection.h"
HardwareSerial &hSerial(Serial2);

bool send_message(String msg)
{
    Serial.println("Trying to send msg");
    hSerial.begin(9600);
    delay(500);
    digitalWrite(SERVER_BOARD_CONTROL_PIN, LOW);
    uint32_t last_millis = millis();
    bool reply_status = false;
    while ((millis() - last_millis) < 2000)
        if (digitalRead(SENSOR_BOARD_CONTROL_PIN) == LOW)
            reply_status = true;

    if (!reply_status)
    {
        Serial.println("Send Failure");
        digitalWrite(SERVER_BOARD_CONTROL_PIN, HIGH);
        hSerial.end();
        return false;
    }

    Serial.println("Server Replied");
    last_millis = millis();
    msg += "#";
    hSerial.write(msg.c_str());
    Serial.println("Writing Message: " + (String)msg);
    Serial.println("Sent");
    digitalWrite(SERVER_BOARD_CONTROL_PIN, HIGH);
    hSerial.end();
    return true;
}

String read_message(void)
{
    Serial.println("Trying to read msg");
    hSerial.begin(9600, SERIAL_8N1, HSERIAL_RX, HSERIAL_TX);
    digitalWrite(SENSOR_BOARD_CONTROL_PIN, LOW);
    delay(50);
    String msg = "";

    while (!hSerial.available())
        ;

    while (hSerial.available())
        msg = hSerial.readStringUntil('#');
    Serial.println("Recieved Message: " + msg);

    // while (digitalRead(SERVER_BOARD_CONTROL_PIN) == LOW)
    //     Serial.print(".");
    delay(10);
    digitalWrite(SENSOR_BOARD_CONTROL_PIN, HIGH);
    Serial.println("Read Complete");
    delay(10);
    hSerial.end();
    return msg;
}