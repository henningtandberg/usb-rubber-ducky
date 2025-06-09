//
// Created by Henning Tandberg on 27/05/2025.
//

#include "StaticContent.h"

void StaticContent::setup(fs::FS & fs, ESP8266WebServer & httpServer) {
    /**
     * HTML
     */
    httpServer.serveStatic("/", fs, "/html/index.html");
    httpServer.serveStatic("/script/select", fs, "/html/select.html");
    httpServer.serveStatic("/script/custom", fs, "/html/custom.html");
    /**
     * CSS
     */
    httpServer.serveStatic("/css/navbar.css", fs, "/css/navbar.css");
    httpServer.serveStatic("/css/normalize.css", fs, "/css/normalize.css");
    httpServer.serveStatic("/css/skeleton.css", fs, "/css/skeleton.css");
}

