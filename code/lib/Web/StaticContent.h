//
// Created by Henning Tandberg on 31/05/2025.
//

#ifndef USB_RUBBER_DUCKY_STATICCONTENT_H
#define USB_RUBBER_DUCKY_STATICCONTENT_H

#if defined(ARDUINO)
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#else
#include <FakeWebServer.h>
#define FakeWebServer ESP8266WebServer
#endif

class StaticContent {
public:
    static void setup(fs::FS & fs, ESP8266WebServer & httpServer);
};

#endif //USB_RUBBER_DUCKY_STATICCONTENT_H
