#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisnospoon"
#endif

const char* host = "esp8266-webupdate";
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;


void handleRoot() {
    httpServer.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void setup(void) {
    delay(1000);

    Serial.begin(115200);
    Serial.println();
    Serial.println("Booting Sketch...");

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);
    httpServer.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
}

void loop(void) {
    httpServer.handleClient();
    MDNS.update();
}
