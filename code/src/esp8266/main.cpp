// Arduino / ESP
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include <DuckySerial.h>
#include <CommandParser.h>
#include <Pages.h>

const char * host = "ducky";
const char * ssid = "ESPap";
const char * password = "quackquack";

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
DuckySerial duckySerial = DuckySerial::create(Serial);
Pages pages = Pages::create(httpServer);

void setup(void) {
    duckySerial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_IP, gateway,subnet);

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);

    pages.mapEndpoints();

    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
}

void loop(void) {
    httpServer.handleClient();
    MDNS.update();
}
