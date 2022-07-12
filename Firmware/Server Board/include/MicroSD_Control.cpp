#ifndef MicroSD_Control_cpp
#define MicroSD_Control_cpp
// Reference (SD Card Module): https://randomnerdtutorials.com/esp32-microsd-card-arduino/
// Reference: (ReadLines Library): https://github.com/mykeels/ReadLines/blob/master/examples/print-line-and-index/print-line-only.ino
#include "FS.h"
#include "SD.h"
#include "ESP32 Pin Connection.h"
#include "Variable_Declaration.h"

/* -------------------------- FUNCTION DECLARATION -------------------------- */
void setup_microsd(void)
{
    if (!SD.begin(SD_CHIP_SELECT))
    {
        Serial.println("MicroSd Card Mount Failed");
        while (1)
            ;
    }
    else
        Serial.println("MicroSD Card Mount Successful");
}

/**
 * @brief List All the Available Directories
 *
 * @param fs
 * @param dirname
 * @param levels
 */
void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\n", dirname);
    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
                listDir(fs, file.name(), levels - 1);
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

/**
 * @brief Create a Directory on SD Card
 *
 * @param fs SD Object
 * @param path The Location Path of the folder
 */
void createDir(fs::FS &fs, const char *path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path))
        Serial.println("Dir created");
    else
        Serial.println("Mkdir failed");
    return;
}

/**
 * @brief Delete the File
 *
 * @param fs SD Object
 * @param path
 */
void deleteFile(fs::FS &fs, String str_path)
{
    char path[str_path.length()];
    strcpy(path, str_path.c_str());

    Serial.printf("Deleting file: %s\n", path);
    if (fs.remove(path))
        Serial.println("File deleted");
    else
        Serial.println("Delete failed");
}

/**
 * @brief Read a file on SD Card
 *
 * @param fs SD Object
 * @param path The Location path of the file
 * @return int Exit Status
 */
String readFile(fs::FS &fs, const char *path)
{
    String read_line = "";
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file)
        Serial.println("Failed to open file for reading");
    Serial.print("Read from file: ");
    while (file.available())
        read_line = file.read();
    file.close();
    return read_line;
}

/**
 * @brief Write to a file on SD Card
 *
 * @param fs SD Object
 * @param path Path of the file
 * @param message Message to be written in the file
 */
void writeFile(fs::FS &fs, String str_path, String msg)
{
    Serial.println("Writing file: " + (String)str_path);
    Serial.println("Write Message: " + (String)msg);

    char path[str_path.length()];
    strcpy(path, str_path.c_str());

    msg += "\n";
    char message[msg.length()];
    strcpy(message, msg.c_str());

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
        Serial.println("File written");
    else
        Serial.println("Write failed");
    file.close();
    return;
}

/**
 * @brief Append the message to the file
 * -> If file doesn't exist, then a new file is created and then written to it.
 * @param fs SD Object
 * @param path Path of the file
 * @param message Message to be written to the file
 */
void appendFile(fs::FS &fs, String str_path, String msg)
{
    Serial.println("Writing file: " + (String)str_path);
    Serial.println("Write Message: " + (String)msg);
    char path[str_path.length()];
    strcpy(path, str_path.c_str());

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        writeFile(SD, path, msg);
        return;
    }

    msg += "\n";
    char message[msg.length()];
    strcpy(message, msg.c_str());

    if (file.print(message))
        Serial.println("Message appended");
    else
        Serial.println("Append failed");
    file.close();
    return;
}

/**
 * @brief Read the file data containing only single line of data
 *
 * @param file_path
 * @return String
 */
String read_single_line_data_from_sd_card(String file_path)
{
    Serial.println("Reading Data");
    String send_string;
    File printFile = SD.open(file_path);
    if (!printFile)
        Serial.print("The text file cannot be opened");
    while (printFile.available())
        send_string = printFile.readStringUntil('\n');
    printFile.close();

    Serial.println("Read Line: " + send_string);
    return send_string;
}

// void read_data_from_sd_card(void)
// {
//     Serial.println("Reading Historical Data");
//     File printFile = SD.open(file_path);
//     if (!printFile)
//         Serial.print("The text file cannot be opened");
//     int lineIndex = 1;
//     while (printFile.available())
//     {
//         String send_string = printFile.readStringUntil('\n');
//         Serial.println((String)lineIndex + " : " + send_string);
//         lineIndex++;
//     }
//     printFile.close();
// }

#endif