#include <Arduino.h>
#include <RGB_Led_Control.cpp>
#include <Variable_Declaration.h>
#include <Sensor_Data_Collection.cpp>
#include <Serial_InterBoard_Communication.cpp>
#include <esp32_webserver.cpp>

void deparse_message(String data_msg)
{
  // Expected Data String: T:29,H:71,C:410,M:597,D:4,L:40,#
  // T => Temperature
  // H => Humidity
  // C => Carbondioxide
  // M => Carbonmonoxide
  // D => Dust PM AE 2.5
  // L => Light Intensity
  temperature = 0;
  humidity = 0;
  carbondioxide = 0;
  carbonmonoxide = 0;
  pm_ae_2_5 = 0;
  lux = 0;

  Serial.println("Deparse String: " + data_msg);
  String data_params[6]; // T,H,C,M,D,L
  {
    char token = ',';
    uint8_t param_index = 0;
    uint8_t last_param_pos = 0;
    for (size_t i = 0; i < data_msg.length(); i++)
    {
      if (data_msg[i] == token)
      {
        data_params[param_index] = data_msg.substring(last_param_pos, i);
        last_param_pos = i + 1;
        param_index++;
      }
    }
  }

  char param_values[6][10]; // T,H,C,M,D,L
  {
    char token = ':';
    for (size_t j = 0; j < 6; j++)
      for (size_t i = 0; i < data_params[j].length(); i++)
        if (data_params[j][i] == token)
        {
          String values = data_params[j].substring(i + 1);
          strcpy(param_values[j], values.c_str());
        }
  }
  temperature = atoi(param_values[0]);
  humidity = atoi(param_values[1]);
  carbondioxide = atoi(param_values[2]);
  carbonmonoxide = atoi(param_values[3]);
  pm_ae_2_5 = atoi(param_values[4]);
  lux = atoi(param_values[5]);
}

void setup()
{
  Serial.begin(115200);
  setup_leds();
  setup_sensors();
}

void loop()
{
  if (digitalRead(SERVER_BOARD_CONTROL_PIN) == LOW) // Deparse Incoming message from sensor board
  {
    String recieved_msg = read_message();
    deparse_message(recieved_msg);
  }

  if (digitalRead(CONFIGURATION_BUTTON) == HIGH)
    launch_webserver();
}