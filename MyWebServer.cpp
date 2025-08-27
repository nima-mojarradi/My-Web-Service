#include "MyWebServer.h"
#include <WiFi.h>

MyWebServer::MyWebServer(AsyncWebServer* server) {
    _server = server;
}

void MyWebServer::begin() {
    if (!SPIFFS.begin(true)) {
        Serial.println("Error mounting SPIFFS");
        return;
    }

    _server->begin();
    ElegantOTA.begin(_server);
    setupRoutes();
}

void MyWebServer::handleLoop() {
    ElegantOTA.loop();
}

// تعریف مسیرها
void MyWebServer::setupRoutes() {
    _server->on("/upload", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/upload.html", "text/html");
    });

    _server->on("/upload", HTTP_POST, 
        [](AsyncWebServerRequest *request) {
            request->send(200, "text/plain", "File Uploaded! Refresh /");
        },
        [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
            File file;
            if (!index) {
                Serial.printf("UploadStart: %s\n", filename.c_str());
                file = SPIFFS.open("/" + filename, "w");
                if (!file) {
                    Serial.println("Failed to open file for writing");
                    return;
                }
                request->_tempFile = file;
            }
            if (len) request->_tempFile.write(data, len);
            if (final) {
                request->_tempFile.close();
                Serial.printf("UploadEnd: %s (%u)\n", filename.c_str(), index + len);
            }
        }
    );

    _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        if (SPIFFS.exists("/index.html")) {
            request->send(SPIFFS, "/index.html", "text/html");
        } else {
            request->send(200, "text/plain", "No index.html uploaded yet!");
        }
    });

    _server->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not found");
    });
}
