// Reference (AWS IoT Core): https://aws.amazon.com/blogs/compute/building-an-aws-iot-core-device-using-aws-serverless-and-an-esp32/
#ifndef MQTT_Connection_cpp
#define MQTT_Connection_cpp

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "AWS_Configuration.h"
#include "WiFi_Setup.cpp"
#include "Variable_Declaration.h"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

/* --------------------------- FUNCTION DEFINITION -------------------------- */
bool aws_setup(void);
void messageReceived(String &topic, String &payload);
void handleEachAWSBacklogLine(char line[], int lineIndex);
void lwMQTTErr(lwmqtt_err_t reason);
void lwMQTTErrConnection(lwmqtt_return_code_t reason);
void connectToMqtt(bool nonBlocking);
void checkWiFiThenMQTT(void);
void checkWiFiThenMQTTNonBlocking(void);
void checkWiFiThenReboot(void);
bool sendData(String date, String time, uint8_t temp, uint8_t humiditiy, uint16_t co2, uint16_t co, uint16_t pm_ae_2_5, uint16_t lux, uint16_t voc, uint8_t battery);

/* -------------------------- FUNCTION DECLARATION -------------------------- */
/**
 * @brief Setup AWS
 *
 */
bool aws_setup(void)
{
    Serial.println("Setting up AWS");

    // Configure WiFiClientSecure to use the AWS IoT device credentials
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);
    // Connect to the MQTT broker on the AWS endpoint we defined earlier
    client.begin(AWS_IOT_ENDPOINT, 8883, net);
    // Create a message handler
    client.onMessage(messageReceived);
    Serial.print("Connecting to AWS IOT");
    while (!client.connect(THINGNAME))
    {
        Serial.print(".");
        delay(100);
    }
    if (!client.connected())
    {
        Serial.println("AWS IoT Timeout!");
        return false;
    }
    client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC); // Subscribe to a topic
    Serial.println("AWS IoT Connected!");
    Serial.println("AWS Thingname: " + (String)THINGNAME);
    Serial.println("AWS Publish Topic: " + (String)AWS_IOT_PUBLISH_TOPIC);
    delay(10);
    return true;
}

/**
 * @brief This function is activated when the message is recieved from AWS
 *
 * @param topic
 * @param payload
 */
void messageReceived(String &topic, String &payload)
{ // Reference (JSON to String Converter): https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonParserExample/JsonParserExample.ino
    Serial.println("Recieved:\n" + payload);
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
        Serial.println("deserializeJson() failed: " + (String)error.f_str());
        return;
    }

    String cmd = doc["cmd"];
    delay(1000);
    // Perform action as per the command from AWS
}

void lwMQTTErr(lwmqtt_err_t reason)
{
    if (reason == lwmqtt_err_t::LWMQTT_SUCCESS)
        Serial.print("Success");
    else if (reason == lwmqtt_err_t::LWMQTT_BUFFER_TOO_SHORT)
        Serial.print("Buffer too short");
    else if (reason == lwmqtt_err_t::LWMQTT_VARNUM_OVERFLOW)
        Serial.print("Varnum overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_CONNECT)
        Serial.print("Network failed connect");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_TIMEOUT)
        Serial.print("Network timeout");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_READ)
        Serial.print("Network failed read");
    else if (reason == lwmqtt_err_t::LWMQTT_NETWORK_FAILED_WRITE)
        Serial.print("Network failed write");
    else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_OVERFLOW)
        Serial.print("Remaining length overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_REMAINING_LENGTH_MISMATCH)
        Serial.print("Remaining length mismatch");
    else if (reason == lwmqtt_err_t::LWMQTT_MISSING_OR_WRONG_PACKET)
        Serial.print("Missing or wrong packet");
    else if (reason == lwmqtt_err_t::LWMQTT_CONNECTION_DENIED)
        Serial.print("Connection denied");
    else if (reason == lwmqtt_err_t::LWMQTT_FAILED_SUBSCRIPTION)
        Serial.print("Failed subscription");
    else if (reason == lwmqtt_err_t::LWMQTT_SUBACK_ARRAY_OVERFLOW)
        Serial.print("Suback array overflow");
    else if (reason == lwmqtt_err_t::LWMQTT_PONG_TIMEOUT)
        Serial.print("Pong timeout");
}

void lwMQTTErrConnection(lwmqtt_return_code_t reason)
{
    if (reason == lwmqtt_return_code_t::LWMQTT_CONNECTION_ACCEPTED)
        Serial.print("Connection Accepted");
    else if (reason == lwmqtt_return_code_t::LWMQTT_UNACCEPTABLE_PROTOCOL)
        Serial.print("Unacceptable Protocol");
    else if (reason == lwmqtt_return_code_t::LWMQTT_IDENTIFIER_REJECTED)
        Serial.print("Identifier Rejected");
    else if (reason == lwmqtt_return_code_t::LWMQTT_SERVER_UNAVAILABLE)
        Serial.print("Server Unavailable");
    else if (reason == lwmqtt_return_code_t::LWMQTT_BAD_USERNAME_OR_PASSWORD)
        Serial.print("Bad UserName/Password");
    else if (reason == lwmqtt_return_code_t::LWMQTT_NOT_AUTHORIZED)
        Serial.print("Not Authorized");
    else if (reason == lwmqtt_return_code_t::LWMQTT_UNKNOWN_RETURN_CODE)
        Serial.print("Unknown Return Code");
}

void connectToMqtt(bool nonBlocking)
{
    Serial.print("MQTT connecting ");
    int tries = 0;
    int max_tries = 50;
    while ((!client.connected()) && (tries < max_tries))
    {
        tries++;
        if (client.connect(THINGNAME))
        {
            Serial.println("connected!");
            if (!client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC))
                lwMQTTErr(client.lastError());
        }
        else
        {
            Serial.println("failed, reason -> ");
            lwMQTTErrConnection(client.returnCode());
            if (!nonBlocking)
            {
                Serial.println(" < try again in 5 seconds");
                delay(5000);
            }
            else
            {
                Serial.println(" <");
            }
        }
        if (nonBlocking)
            break;
    }
}

void checkWiFiThenMQTT(void)
{
    if (WiFi.status() != WL_CONNECTED)
        connect_to_wifi();
    if (WiFi.status() == WL_CONNECTED)
        connectToMqtt(false);
}

unsigned long previousMillis = 0;
const long interval = 5000;

void checkWiFiThenMQTTNonBlocking(void)
{
    connect_to_wifi();
    if (millis() - previousMillis >= interval && !client.connected())
    {
        previousMillis = millis();
        connectToMqtt(true);
    }
}

void checkWiFiThenReboot(void)
{
    connect_to_wifi();
    Serial.print("Rebooting");
    ESP.restart();
}

/**
 * @brief
 *
 * @param cmd
 * @param date
 * @param time
 * @param temp
 * @param humiditiy
 * @param co2
 * @param co
 * @param pm_ae_2_5
 * @param lux
 * @param voc
 * @param battery
 * @return true
 * @return false
 */
bool sendData(String date, String time, uint8_t temp, uint8_t humiditiy, uint16_t co2, uint16_t co, uint16_t pm_ae_2_5, uint16_t pm_ae_10, uint16_t lux, uint16_t voc, uint8_t battery)
{

    bool send_success = false;
    // Update to AWS
    if (!client.connected())
        checkWiFiThenMQTT();
    if (client.connected())
    {
        client.loop();
        // Reference:https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonGeneratorExample/JsonGeneratorExample.ino
        Serial.println("Sending to AWS");
        StaticJsonDocument<500> doc;
        doc["date"] = date;
        doc["time"] = time;
        doc["temp"] = temp;
        doc["humiditiy"] = humiditiy;
        doc["co2"] = co2;
        doc["co"] = co;
        doc["pm_ae_2_5"] = pm_ae_2_5;
        doc["pm_ae_10"] = pm_ae_10;
        doc["lux"] = lux;
        doc["voc"] = voc;
        doc["batt"] = battery;

        serializeJsonPretty(doc, Serial);
        char shadow[measureJson(doc) + 1];
        serializeJson(doc, shadow, sizeof(shadow));
        Serial.println();
        int tries = 0;
        int max_tries = 30;
        while (tries < max_tries)
        {
            if (client.publish(AWS_IOT_PUBLISH_TOPIC, shadow, false, 0))
            {
                send_success = true;
                Serial.println("Send Success");
                break;
            }
            else
            {
                lwMQTTErr(client.lastError());
                delay(50);
                tries++;
            }
        }
    }
    return send_success;
}

void sendData2(void)
{
    if (!client.connected())
        checkWiFiThenMQTT();
    if (client.connected())
    {
        client.loop();
        // Reference:https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonGeneratorExample/JsonGeneratorExample.ino
        StaticJsonDocument<500> doc;
        Serial.println("Ping");
        doc["msg"] = "Hello";
        serializeJsonPretty(doc, Serial);
        char shadow[measureJson(doc) + 1];
        serializeJson(doc, shadow, sizeof(shadow));
        Serial.println();
        if (client.publish(AWS_IOT_PUBLISH_TOPIC, shadow, false, 0))
            Serial.println("Send Success");
    }
}
#endif