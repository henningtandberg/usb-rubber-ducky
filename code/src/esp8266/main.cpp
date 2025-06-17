// Arduino / ESP
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <LittleFS.h>

#include <DuckySerial.h>
#include <CommandParser.h>
#include <StaticContent.h>

const char * host = "ducky";
const char * ssid = "ESPap";
const char * password = "quackquack";

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
DuckySerial duckySerial = DuckySerial::create(Serial);

static void handleCustomScript(void);

void setup(void) {
    duckySerial.begin(115200);

    LittleFS.begin();

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_IP, gateway,subnet);

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);
    StaticContent::setup(LittleFS, httpServer);
    //Api.setup(); -> runs .on for API endpoints
    httpServer.on("/script/custom", HTTP_POST, handleCustomScript);

    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

void handleCustomScript(void) {
    const char * textAreaName = "customScript";

    if (!httpServer.hasArg(textAreaName)) {
        return;
    }

    String customScript = httpServer.arg(textAreaName);
    int lines_len = customScript.length() + 1;
    char lines[lines_len];
    customScript.toCharArray(lines, lines_len);
    duckySerial.sendPrintln(lines, lines_len);

    char *line;
    char *rest = lines;
    char *context;
    int count = 0;

    while ((line = strtok_r(rest, ";", &context)) != NULL) {
        line = trim(line);
        duckySerial.sendPrintln(line, strlen(line));
        Command * command = CommandParser::parse_command(line);
        duckySerial.sendCommand((char *)command, sizeof(Command) + command->len);
        free(command);
        rest = NULL; // Important for subsequent calls to strtok_r
        count++;
        delay(100);
    }

    //delay(1000);
    httpServer.send(200, "text/html", "Lines: " + (String)count);
    // Add IFrame to show progress
}

void loop(void) {
    httpServer.handleClient();
    MDNS.update();
}

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
