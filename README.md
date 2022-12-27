# Smart AQI Monitor

<!-- TOC -->

- [Smart AQI Monitor](#smart-aqi-monitor)
- [What is Smart AQI Monitor?](#what-is-smart-aqi-monitor)
- [Features of AQI Monitor](#features-of-aqi-monitor)
- [Install Dependencies](#install-dependencies)
    - [Install Arduino](#install-arduino)
    - [Install Visual Studio Code](#install-visual-studio-code)
    - [Install PlatformIO IDE](#install-platformio-ide)
- [Editing the Project Files](#editing-the-project-files)
    - [Download the Project Files](#download-the-project-files)
    - [Upload Code to Board](#upload-code-to-board)
    - [Wire the Electronics](#wire-the-electronics)
- [Design Details](#design-details)
- [License](#license)

<!-- /TOC -->

# What is Smart AQI Monitor?

Smart Air Quality Index Monitor (Smart AQI Monitor) is a wall mounted unit which measures:
- Temperature
- Humidity
- Carbon Dioxide
- Carbon Monoxide
- Dust Particulate Level:
    - PM AE 1.0
    - PM AE 2.5
    - PM AE 10.0
- Light Intensity
- Volatile Organic Components:
    - Ozone
    - Methane

:spiral_notepad: _Note: This device is build for industrial application using EU accepted sensors._

Using these values, AQI can be calculated as follows:

$$
I_{p} = \frac{I_{Hi}-I_{Lo}}{BP_{Hi}-BP_{Lo}}(C_{P}-BP_{Lo}) + I_{Lo}
$$

where,\
$I_{p}$ = The Index of pollutant $p$ \
$C_{p}$ = The truncated concentration of pollutant $p$ \
$BP_{Hi}$ = The concentration breakpoint that is greater than or equal to $C_{p}$ \
$BP_{Lo}$ = The concentration breakpoint that is less than or equal to $C_{p}$ \
$I_{Hi}$ = The AQI Value corresponding to $BP_{Hi}$ \
$I_{Lo}$ = The AQI Value corresponding to $BP_{Lo}$

More Details on calculation AQI can be found [here](https://www.airnow.gov/sites/default/files/2020-05/aqi-technical-assistance-document-sept2018.pdf).

# Features of AQI Monitor
- Approximately 6 hours of Battery Backup when supply is disconnected.
- Type C charging support.
- Interactive Touch Screen Display.
- Sensor and AQI Calculation accurate to 1 decimal place.

<!-- # How to assemble the project
1. Download the latest version of firmware from the /Firmware folder
2. Edit the Firmware as per the requirement with the help of guide provided in /Firmware/README.md
3. Order the components from the Bill of Materials as per the requirement.
4. Make the Hardware circuit using the guide in /Hardware/README.md
5.  Upload the firmware on the the hardware -->

:spiral_notepad: _Note: This project was written in Windows 11. You can port it to any Operating Software you wish to. Though the basics of installing dependencies might change a bit !!_

# Install Dependencies

## Install Arduino
Download and Install Arduino for Windows using this [link](https://www.arduino.cc/en/software).

## Install Visual Studio Code
Yes, I know. You can use any other IDE that you may like but I love VS Code. _So deal with it!!_

1. Download VS Code by clicking the [link](https://code.visualstudio.com/).
2. Install VS Code. Once the Installation is complete, launch it.
3. Click the Extensions tab and install the following extensions by clicking these links

   1. [Better Comments](https://marketplace.visualstudio.com/items?itemName=aaron-bond.better-comments)
   2. [C#](https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csharp)
   3. [Prettier - Code formatter](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode)
   4. [VSC-Essentials](https://marketplace.visualstudio.com/items?itemName=Gydunhn.vsc-essentials)
   5. [Prettier ESLint](https://marketplace.visualstudio.com/items?itemName=rvest.vs-code-prettier-eslint)

   _(Note: This Extensions are not neccesary but will surely make your life a bit easier when you are on the verge of unaliving yourself for picking up a project like this!!! Believe me... you are reading this ReadMe just due to their help!!)_ 👼

## Install PlatformIO IDE

The complete project was setup and written using PlatformIO for the ease of portability across devices and make task of setting up of new computers a bit easier. Install PIO with the [link](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

_This installation is gonna take a lot of time. When I mean lot, I mean a really lot lot. Make a coffee meanwhile?_  ☕

# Editing the Project Files

## Download the Project Files

Open a new terminal and enter

```shell
git clone git@github.com:parth-20-07/Smart-AQI-Monitor.git
```

`cd` to the Project folder using 

```shell
cd Smart-AQI-Monitor/Firmware/Sensor\ Board/
```

Open the project folder in VS Code using

```shell
code .
```

In a New Terminal, Open the other firmware file using
```shell
cd Smart-AQI-Monitor/Firmware/Server\ Board/
```

Open the project folder in VS Code using

```shell
code .
```

Wait for probably a minute for PlatformIO to initialize completely.

## Upload Code to Board
- `Sensor Board` code to `nanoatmega328new`. Change the COM Port in `platformio.ini` to your system.
- `Server Board` code to `esp32doit-devkit-v1`. Change the COM Port in `platformio.ini` to your system.

## Wire the Electronics
- `nanoatmega328new`
    - MHZ16 NDIR CO2 Sensor: `(RX,TX) --> (GPIO2, GPIO3)`
    - ZE03 CO Sensor: `(RX,TX,VOUT) --> (GPIO5, GPIO4, AI0)`
    - ZH06 LASER Dust Sensor: `(RX,TX) --> (GPIO7, GPIO6)`
    - HTU21D T&H I2C Sensor: `(SDA,SCL) --> (AI4, AI5)`
    - BH1750 LUX I2C Sensor: `(SDA,SCL) --> (AI4, AI5)`
    - InterBoard Communication: `(RX,TX,CHIP_SELECT,INT) --> (GPIO9, GPIO8, GPIO10, AI3)`
- `esp32doit-devkit-v1`
    - Battery ADC In: `(IN) --> (GPIO34)`
    - RGB LED Control Pin: `(CTRL_PIN) --> (GPIO2)`
    - CONTROL BUTTON: `(BUT) --> (GPIO4)`
    - SD CARD: `(SCK,MISO,MOSI,CHIP_SELECT) --> (GPIO18, GPIO19, GPIO23, GPIO5)`
    - InterBoard Communication: `(RX,TX,CHIP_SELECT,INT) --> (GPIO16, GPIO17, GPIO25, GPIO26)`

# Design Details
- Designed for: Ecologic Pvt. Ltd.
- Designed by: [Parth Patel](mailto:parth.pmech@gmail.com)

🥳 _Ladies and Gentlemen!!_ \
🥳 _Hope you have a good day!!_\
🥳 _We are all done with the project here!!_

# License

This project is licensed under [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) (see [LICENSE.md](LICENSE.md)).

Copyright 2022 Parth Patel

Licensed under the GNU General Public License, Version 3.0 (the "License"); you may not use this file except in compliance with the License.

You may obtain a copy of the License at

_https://www.gnu.org/licenses/gpl-3.0.en.html_

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.