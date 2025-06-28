//
// Created by Henning Tandberg on 28/06/2025.
//

#ifndef USB_RUBBER_DUCKY_API_H
#define USB_RUBBER_DUCKY_API_H

#if defined(ARDUINO)
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#else
#include <FakeWebServer.h>
#define FakeWebServer ESP8266WebServer
#endif

class Api {
private:
    ESP8266WebServer & _httpServer;
    Api(ESP8266WebServer & httpServer) : _httpServer(httpServer) { }

    void notFound(void);
public:
    static Api create(ESP8266WebServer & httpServer);
    void mapControllers();
};


#endif //USB_RUBBER_DUCKY_API_H
