#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "MyWebServer.h"

const char* ssid = "Dina";
const char* password = "Dd78134003Segco";

AsyncWebServer server(80);
MyWebServer myServer(&server);

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());

    myServer.begin(); // شروع وب‌سرور + OTA + آپلود فایل
}

void loop() {
    myServer.handleLoop(); // OTA loop
}
