#ifndef MY_WEBSERVER_H
#define MY_WEBSERVER_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ElegantOTA.h>

class MyWebServer {
public:
    MyWebServer(AsyncWebServer* server);
    void begin();
    void handleLoop();

private:
    AsyncWebServer* _server;
    void setupRoutes();
};

#endif
