#include <Arduino.h>
#include <RGB_Led_Control.cpp>
#include <Variable_Declaration.h>
#include <Sensor_Data_Collection.cpp>
#include <Serial_InterBoard_Communication.cpp>
#include <esp32_webserver.cpp>
#include <MicroSD_Control.cpp>
#include <WiFi_Setup.cpp>
#include <NTP_Configuration.cpp>
#include <MQTT_Connection.cpp>

/* --------------------------- Webserver Functions -------------------------- */
void fetch_new_values_from_server(void)
{
  launch_webserver();
  Serial.println("Saving Values");

  deleteFile(SD, SSID_FILE);
  writeFile(SD, SSID_FILE, (String)ssid);

  deleteFile(SD, PASSWORD_FILE);
  writeFile(SD, PASSWORD_FILE, (String)password);
  for (size_t i = 0; i < NUM_OF_PARAMS; i++)
  {
    String file_path = "/" + (String)i + ".txt";
    deleteFile(SD, file_path);
    writeFile(SD, file_path, (String)params_range[i]);
  }
  ESP.restart();
}

/* ------------------------ Data Processing Functions ----------------------- */
void deparse_message(String deparse_msg)
{
  Serial.println("Deparse Full String: " + deparse_msg);

  String msg = "";
  char token = ',';
  uint8_t count = 0;
  uint8_t last_index_pos = 0;
  for (size_t i = 0; i < deparse_msg.length(); i++)
  {
    if (deparse_msg[i] == token)
    {
      if (count == 0)
        formatted_day = deparse_msg.substring(0, i);
      else if (count == 1)
        formatted_time = deparse_msg.substring(last_index_pos, i);
      else if (count == 2)
        msg = deparse_msg.substring(last_index_pos);
      last_index_pos = i + 1;
      count++;
    }
  }

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

  msg += ",";
  Serial.println("Deparse Message String: " + msg);
  String data_params[6]; // T,H,C,M,D,L
  {
    char token = ',';
    uint8_t param_index = 0;
    uint8_t last_param_pos = 0;
    for (size_t i = 0; i < msg.length(); i++)
    {
      if (msg[i] == token)
      {
        data_params[param_index] = msg.substring(last_param_pos, i);
        last_param_pos = i + 1;
        param_index++;
      }
    }
    for (size_t i = 0; i < param_index; i++)
      Serial.println("Param " + (String)i + " = " + data_params[i]);
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

/* ---------------------------- MicroSD Function ---------------------------- */
void fetch_configuration_details(void)
{
  String str_ssid = read_single_line_data_from_sd_card(SSID_FILE);
  strcpy(ssid, str_ssid.c_str());
  Serial.println("Fetched SSID: " + (String)ssid);

  String str_pwd = read_single_line_data_from_sd_card(PASSWORD_FILE);
  strcpy(password, str_pwd.c_str());
  Serial.println("Fetched Password: " + (String)password);

  for (size_t i = 0; i < NUM_OF_PARAMS; i++)
  {
    String file_path = "/" + (String)i + ".txt";
    String value = read_single_line_data_from_sd_card(file_path);
    char char_value[value.length()];
    strcpy(char_value, value.c_str());
    params_range[i] = atoi(char_value);
  }

  for (size_t i = 0; i < NUM_OF_PARAMS; i++)
    Serial.println("Param " + (String)i + "=" + (String)params_range[i]);

  return;
}

void read_backlog_file(void)
{
  Serial.println("Reading Historical Data");
  File printFile = SD.open(BACKLOG_FILE);
  bool complete_send_success = true;
  if (!printFile)
  {
    Serial.print("The text file cannot be opened");
    return;
  }
  int lineIndex = 1;
  while (printFile.available())
  {
    String send_string = printFile.readStringUntil('\n');
    Serial.println((String)lineIndex + " : " + send_string);
    deparse_message(send_string);
    if (!sendData(formatted_day, formatted_time, temperature, humidity, carbondioxide, carbonmonoxide, pm_ae_2_5, lux))
    {
      Serial.println("Send Failure");
      complete_send_success = false;
      break;
    }
    Serial.println("------------------------------------");
    lineIndex++;
    delay(50);
  }
  printFile.close();
  if (complete_send_success)
  {
    deleteFile(SD, BACKLOG_FILE);
    backlog_file_available = false;
  }
}

/* --------------------------- LED Alert Function --------------------------- */
void set_led_alerts(void)
{
  Serial.println("Setting LED Alerts");
  if ((temperature < params_range[0]) || (temperature > params_range[1]))
    set_specific_led(1, RED);
  else
    set_specific_led(1, GREEN);

  if ((humidity < params_range[2]) || (humidity > params_range[3]))
    set_specific_led(2, RED);
  else
    set_specific_led(2, GREEN);

  if ((carbondioxide < params_range[4]) || (carbondioxide > params_range[5]))
    set_specific_led(3, RED);
  else
    set_specific_led(3, GREEN);

  if ((carbonmonoxide < params_range[6]) || (carbonmonoxide > params_range[7]))
    set_specific_led(4, RED);
  else
    set_specific_led(4, GREEN);

  if ((pm_ae_2_5 < params_range[8]) || (pm_ae_2_5 > params_range[9]))
    set_specific_led(5, RED);
  else
    set_specific_led(5, GREEN);

  if ((lux < params_range[10]) || (lux > params_range[11]))
    set_specific_led(6, RED);
  else
    set_specific_led(6, GREEN);
}

/* -------------------------------------------------------------------------- */
/*                                  Main Code                                 */
/* -------------------------------------------------------------------------- */
void setup()
{
  Serial.begin(9600);
  setup_board_pins();
  setup_leds();
  setup_sensors();
  setup_microsd();
  fetch_configuration_details();
  if ((((String)ssid).length() == 0) || (((String)password).length() == 0))
    fetch_new_values_from_server();
  if (connect_to_wifi())
    if (connect_to_ntp())
      if (aws_setup())
        aws_connect_flag = true;
  last_aws_upload = millis();
  Serial.println("============================= Device Setup Complete =============================");
}

void loop()
{
  if (digitalRead(SERVER_BOARD_CONTROL_PIN) == LOW) // Deparse Incoming message from sensor board
  {
    Serial.println("\n\n=======================================");
    String recieved_msg = read_message();
    if (recieved_msg != "")
    {
      Serial.println("Incoming Msg: " + recieved_msg);
      printLocalTime();
      formatted_day = (String)year + "-" + (String)month + "-" + (String)date;
      formatted_time = (String)hour + "-" + (String)minutes + "-" + (String)seconds;
      String backup_msg = formatted_day + "," + formatted_time + "," + recieved_msg;
      appendFile(SD, BACKLOG_FILE, backup_msg);
      backlog_file_available = true;
      deparse_message(backup_msg);
      set_led_alerts();
    }
  }

  if (digitalRead(CONFIGURATION_BUTTON) == HIGH) // Launch Webserver to update Limits
    fetch_new_values_from_server();

  if (backlog_file_available) // To check the backlog and upload any data which is not uploaded
    if ((millis() - last_aws_upload) > (AWS_UPLOAD_TIME_IN_MINUTES * 60000))
    {
      if (!aws_connect_flag) // Connect to AWS if not connected
        aws_setup();
      if (aws_connect_flag)
        read_backlog_file();
      last_aws_upload = millis();
    }
}