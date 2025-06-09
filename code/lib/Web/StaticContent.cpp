//
// Created by Henning Tandberg on 27/05/2025.
//

#include "Pages.h"

Pages Pages::create(ESP8266WebServer & httpServer) {
    return Pages(httpServer);
}

void Pages::mapEndpoints() {
    _httpServer.on("/", HTTP_GET, [this](){ this->indexPageGet(); });
    //_httpServer.on("/script/select", HTTP_GET, script_select_get);
    //httpServer.on("/script/select", HTTP_POST, script_select_post);
    //httpServer.on("/script/custom", HTTP_GET, script_custom_get);
    //httpServer.on("/script/custom", HTTP_POST, script_custom_post);
    //httpServer.on("/settings", HTTP_GET, settings_get);
    //httpServer.on("/settings", HTTP_POST, settings_post);
}

static const char *indexPage PROGMEM = "<!doctypehtml><html lang=en><link href=./css/navbar.css rel=stylesheet><link href=./css/normalize.css rel=stylesheet><link href=./css/skeleton.css rel=stylesheet><link href=./css/raleway.css rel=stylesheet><title>Your Site</title><div class=container><div class=navbar><a href=/ >Home</a> <a href=./script/select>Pre-built Scripts</a> <a href=./script/custom>Custom Script</a> <a href=./settings>Settings</a> <a href=./update>Firmware</a></div><br><section class=header><h1 class=title>USB Rubber Ducky</h1></section><div class=docs-section><p>Welcome!</div><hr><a href=/script/select class=button>Pre-Built Scripts</a> <a href=/script/custom class=button>Build Your Own Script</a> <a href=/settings class=button>Update Settings</a> <a href=/update class=button>Update Firmware</a></div>";
void Pages::indexPageGet() {
    _httpServer.send(200, "text/html", indexPage);
}

