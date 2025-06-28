//
// Created by Henning Tandberg on 28/06/2025.
//
#include <htmb.h>

#include "Api.h"

Api Api::create(ESP8266WebServer & httpServer) {
    return Api(httpServer);
}

void Api::mapControllers() {
    _httpServer.onNotFound([&](){ notFound(); });
}

void Api::notFound(void) {
    char *notFoundPage = Body(Header(
        H1("404 Not Found"),
        P("This page was not found..."),
        Hr()));

    _httpServer.send(404, "text/html", notFoundPage);
    free(notFoundPage);
}