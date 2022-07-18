#ifndef HTML_PAGE_H
#define HTML_PAGE_H
// HTML web page to handle input fields
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>Smart AQI Configuration Page</title>
    <meta name="viewport" http-equiv="Content-Type"
        content="width=device-width, initial-scale=1 text/html; charset=utf-8">
    <style>
        body {
            background-color: #0000008c;
            font-family: Georgia, "Times New Roman", Times, serif;
            color: rgb(255, 255, 255);
        }

        input[type="text"] {
            width: 100px;
            height: 20px;
            border: 1px solid rgba(0, 0, 0, 0.349);
            background: #ffffff;
        }

        input[type="number"] {
            width: 100px;
            height: 20px;
            border: 1px solid rgba(0, 0, 0, 0.349);
            background: #ffffff;
        }
    </style>
</head>

<body>
    <center>
        <form action="/get">
            <h2 align="center">Smart AQI Configuration Form</h2>

            <h3>Enter Wi-Fi Details

            </h3>
            <table>
                <tr>
                    <td align="right">SSID:</td>
                    <td><input type="text" name="ssid" placeholder="Enter SSID" /></td>
                </tr>

                <tr>
                    <td align="right">Password:</td>
                    <td>
                        <input type="text" name="password" placeholder="Enter Password" />
                    </td>
                </tr>
            </table>

            <h3>Enter Sensor Range</h3>
            <table>
                <tr>
                    <td align="right">Range</td>
                    <td> Minimum</td>
                    <td> Maximum</td>
                </tr>

                <tr>
                    <td align="right">Temperature (°C):</td>
                    <td>
                        <input type="number" name="min_temp" placeholder="0" min="0" max="125" />
                    </td>
                    <td>
                        <input type="number" name="max_temp" placeholder="125" min="0" max="125" />
                    </td>
                </tr>

                <tr>
                    <td align="right">Humidity (%):</td>
                    <td>
                        <input type="number" name="min_humi" placeholder="0" min="0" max="100" />
                    </td>
                    <td>
                        <input type="number" name="max_humi" placeholder="100" min="0" max="100" />
                    </td>
                </tr>
                <tr>
                    <td align="right">Carbondioxide (ppm):</td>
                    <td>
                        <input type="number" name="min_co2" placeholder="0" min="0" max="2000" />
                    </td>
                    <td>
                        <input type="number" name="max_co2" placeholder="2000" min="0" max="2000" />
                    </td>
                </tr>

                <tr>
                    <td align="right">Carbonmonoxide (ppm):</td>
                    <td>
                        <input type="number" name="min_co" placeholder="0" min="0" max="1000" />
                    </td>
                    <td>
                        <input type="number" name="max_co" placeholder="1000" min="1000" max="1000" />
                    </td>
                </tr>

                <tr>
                    <td align="right">PM AE 2.5 (ug/m3):</td>
                    <td>
                        <input type="number" name="min_pm_ae_2.5" placeholder="0" min="0" max="0" />
                    </td>
                    <td>
                        <input type="number" name="max_pm_ae_2.5" placeholder="1000" min="0" max="1000" />
                    </td>
                </tr>
                <tr>
                    <td align="right">Light Intensity (lx):</td>
                    <td>
                        <input type="number" name="min_lux" placeholder="1" min="1" max="65535" />
                    </td>
                    <td>
                        <input type="number" name="max_lux" placeholder="65535" min="1" max="65535" />
                    </td>
                </tr>

                <tr>
                    <td align="right">Volatile Organic Component (ppm):</td>
                    <td>
                        <input type="number" name="min_voc" placeholder="1" min="1" max="30" />
                    </td>
                    <td>
                        <input type="number" name="max_voc" placeholder="30" min="1" max="30" />
                    </td>
                </tr>
            </table>
            <br />
            <input type="submit" value="Submit" />
        </form>
    </center>
</body>

</html>
)rawliteral";
#endif