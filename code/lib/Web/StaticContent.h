//
// Created by Henning Tandberg on 31/05/2025.
//

#ifndef USB_RUBBER_DUCKY_PAGES_H
#define USB_RUBBER_DUCKY_PAGES_H

#if defined(ARDUINO)
#include <ESP8266WebServer.h>
#else
#include <FakeWebServer.h>
#define FakeWebServer ESP8266WebServer
#endif

class StaticContent {
private:
    ESP8266WebServer & _httpServer;
    Pages(ESP8266WebServer & httpServer) : _httpServer(httpServer) { }
    void indexPageGet();

public:
    static Pages create(ESP8266WebServer & httpServer);
    void mapEndpoints();
/**
 *  - Display choices of:
 *      - Select pre built script
 *      - Creating custom script
 *      - Updating firmware and SPIFFS
 *      - Updating settings
 */

/**
 * GET  /script/select
 *  - Display a page with all pre made scripts
 * POST /script/select
 *  - Deploy given script
 */

/**
 * GET  /script/custom
 *  - Allow user to write custom script and the deploy
 * POST /script/custom
 *  - Handle input from form
 */

/**
 * GET  /settings
 *  - Edit settings
 * POST /settings
 */
};

#endif //USB_RUBBER_DUCKY_PAGES_H
