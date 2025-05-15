// Arduino / ESP
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include <DuckySerial.h>
#include <CommandParser.h>
#include <string>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisnospoon"
#endif

const char* host = "esp8266-webupdate";
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
DuckySerial duckySerial = DuckySerial::create(Serial);

/*
 * TODO:
 * Set up current routs:
 * /
 *  - Display choises of:
 *      - Select pre built script
 *      - Creating custom script
 *      - Updating firmware and SPIFFS
 *      - Updating settings
 * /script/select
 *  - Display a page with all pre made scripts
 * /script/deploy?name=<SCRIPT_NAME>
 *  - Deploy given script
 * /script/custom
 *  - Allow user to write custom script and the deploy
 * /settings
 *  - Edit settings
 */

void handleRoot() {
    command_t *command = CommandParser::parse_command("KP LEFT_GUI+t");
    size_t sent_bytes = duckySerial.sendCommand((char *)command, sizeof(command_t) + command->len);

    String str =
            "Bytes sent: " + (String)(sent_bytes) + "\n" +
            "Command type: " + (String)(command->type) + "\nCommand len: " + (String)(command->len) + "\n";
    for (int i = 0; i < command->len; i++) {
        str += "\tCommand payload[" + (String)i + "]: " + String(command->payload[i], HEX) + "\n";
    }

    httpServer.send(200, "text/plain", str);   // Send HTTP status 200 (Ok) and send some text to the browser/client

    free(command);
}

void setup(void) {
    delay(1000);

    duckySerial.begin(115200);

    WiFi.softAP(ssid, password);

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);
    httpServer.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
}

void loop(void) {
    httpServer.handleClient();
    MDNS.update();
}
