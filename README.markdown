# MyWebServer

A simple Arduino library for creating a web server on ESP32/ESP8266 with HTML file upload via a web form and OTA (Over-The-Air) firmware update support.

## Features
- Web server with asynchronous HTTP handling using `ESPAsyncWebServer`.
- Upload HTML files via a web form and serve them dynamically.
- OTA firmware updates for remote code updates.
- SPIFFS file system support for storing and serving files.
- Compatible with ESP32 and ESP8266 boards.

## Prerequisites
- Arduino IDE or PlatformIO.
- ESP32 or ESP8266 board.
- Installed libraries:
  - `ESPAsyncWebServer`
  - `AsyncTCP` (for ESP32) or `ESPAsyncTCP` (for ESP8266)
  - `ArduinoOTA` (for OTA updates)
- SPIFFS upload tool (e.g., ESP32 Sketch Data Upload plugin for Arduino IDE).

## Installation

### Download the Library
- Clone or download this repository:
  ```bash
  git clone https://github.com/yourusername/MyWebServerLibrary.git
  ```
- Move the `MyWebServer` folder to your Arduino libraries directory (`~/Documents/Arduino/libraries/`).

### Install Dependencies
- **In Arduino IDE**:
  - Go to **Sketch > Include Library > Manage Libraries** and install:
    - `ESPAsyncWebServer`
    - `AsyncTCP` (for ESP32) or `ESPAsyncTCP` (for ESP8266)
    - `ArduinoOTA`
- **In PlatformIO**:
  - Add to `platformio.ini`:
    ```ini
    lib_deps = 
        ayushsharma82/AsyncTCP
        me-no-dev/ESP Async WebServer
        arduino-libraries/ArduinoOTA
    ```

### SPIFFS Setup
- Create a `data` folder in your sketch directory with `index.html` and `upload.html` files (see examples).
- Upload the files to SPIFFS using:
  - **Arduino IDE**: **Tools > ESP32 Sketch Data Upload** (or equivalent for ESP8266).
  - **PlatformIO**: `pio run -t uploadfs`.

## Usage
1. Include the library in your sketch:
   ```cpp
   #include <MyWebServer.h>
   ```
2. Initialize the web server:
   ```cpp
   AsyncWebServer server(80);
   MyWebServer myServer(&server);
   ```
3. Start the server in `setup()` (ensure WiFi is connected first):
   ```cpp
   void setup() {
     // Connect to WiFi (implement your WiFi connection logic here)
     myServer.begin();
   }
   ```
4. Handle OTA and other tasks in `loop()`:
   ```cpp
   void loop() {
     myServer.handleloop();
   }
   ```

## Troubleshooting
### WiFi Connection Issues
- Ensure the SSID and password are correct.
- Check that the ESP is within WiFi range.

### SPIFFS Errors
- If you see `Error mounting SPIFFS`, add `SPIFFS.format()` before `SPIFFS.begin(true)` and re-upload files.
- Verify that `index.html` and `upload.html` are in the `data` folder and uploaded correctly.

### OTA Issues
- Ensure the ESP and your computer are on the same WiFi network.
- Check firewall settings (ports 3232 for ESP32, 8266 for ESP8266).
- If using a password, ensure it matches in the OTA client.

## Contributing
Contributions are welcome! Please:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit (`git commit -m 'Add feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a pull request.

## License
This project is licensed under the [MIT License](LICENSE). See the `LICENSE` file for details.