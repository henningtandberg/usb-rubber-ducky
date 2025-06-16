// STL
#include <string.h>

// Arduino
#include <Arduino.h>
#include <Keyboard.h>
#include <SPI.h>

// Custom
#include <CommandParser.h>
#include <DuckyPacket.h>
#include <DuckySerial.h>

const int debug = 1;
const int dryRun = 1;

DuckySerial duckySerial = DuckySerial::create(Serial1);

void inline esp_power_on() {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void setup() {
    esp_power_on();

    Keyboard.begin();
    Serial.begin(115200);
    duckySerial.begin(115200);
}

/*
 * TODO:
 * - Read packet and parse commands
 *      - Keypress          e.g. "KP ENTER" or "KP LEFT_CTRL+LEFT_SHIFT+d"
 *      - Print             e.g. "P echo hello world"
 *      - Println           e.g. "PLN echo hello world" Writes ENTER at the end
 *      - Mouse             e.g. "MM 10,23" Move mose to location x = 10, y = 23
 *      - Mouse Click       e.g. "MC LEFT" Press mouse left button
 *      - Execute Script    e.g. "EXEC win/deploy_keylogger.ducky"
 */

void handle_keypress_command(Command * command) {
    if (command->type != COMMAND_TYPE_KEYBOARD_KEYPRESS) {
        return;
    }

    for (int i = 0; i < command->len; i++) {
        Keyboard.press((uint8_t)command->payload[i]);
    }

    delay(100);
    Keyboard.releaseAll();
}

void print_command(Command * command) {
    Serial.println("\nCommand");
    Serial.print("\tType:   ");

    switch (command->type) {
        case COMMAND_TYPE_KEYBOARD_KEYPRESS:
            Serial.println("COMMAND_TYPE_KEYBOARD_KEYPRESS");
            break;
        case COMMAND_TYPE_KEYBOARD_PRINT:
            Serial.println("COMMAND_TYPE_KEYBOARD_PRINT");
            break;
        case COMMAND_TYPE_KEYBOARD_PRINTLN:
            Serial.println("COMMAND_TYPE_KEYBOARD_PRINTLN");
            break;
        case COMMAND_TYPE_MOUSE_MOVE:
            Serial.println("COMMAND_TYPE_MOUSE_MOVE");
            break;
        case COMMAND_TYPE_MOUSE_CLICK:
            Serial.println("COMMAND_TYPE_MOUSE_CLICK");
            break;
        case COMMAND_TYPE_EXECUTE_SCRIPT:
            Serial.println("COMMAND_TYPE_EXECUTE_SCRIPT");
            break;
        case COMMAND_TYPE_UNKNOWN:
        default:
            Serial.println("COMMAND_TYPE_UNKNOWN");
            break;
    }

    Serial.print("\tLength: ");
    Serial.println(command->len, DEC);

    Serial.print("\tData:   ");
    if (command->type == COMMAND_TYPE_UNKNOWN) {
        Serial.println("Unknown");
    } else if (command->type == COMMAND_TYPE_KEYBOARD_PRINT ||
        command->type == COMMAND_TYPE_KEYBOARD_PRINTLN ||
        command->type == COMMAND_TYPE_EXECUTE_SCRIPT) {
        Serial.println(command->payload);
    } else {
        for (int j = 0; j < command->len; j++) {
            Serial.print(command->payload[j], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

}

void handle_command(Command * command) {
    if (debug) {
        print_command(command);
    }

    if (dryRun) {
        return;
    }

    switch (command->type) {
        case COMMAND_TYPE_KEYBOARD_KEYPRESS:
            break;
        case COMMAND_TYPE_KEYBOARD_PRINT:
            break;
        case COMMAND_TYPE_KEYBOARD_PRINTLN:
            break;
        case COMMAND_TYPE_MOUSE_MOVE:
            break;
        case COMMAND_TYPE_MOUSE_CLICK:
            break;
        case COMMAND_TYPE_EXECUTE_SCRIPT:
            break;
        case COMMAND_TYPE_UNKNOWN:
        default:
            break;
    }
}

char buffer[DUCKY_PACKET_MAX_SIZE];

void print_packet_header(DuckyPacket * packet) {
    Serial.println("\nPacket Header");
    Serial.print("\tType:   ");
    Serial.println(packet->header.type, DEC);
    Serial.print("\tLength: ");
    Serial.println(packet->header.len, DEC);
}

void loop() {
    if (duckySerial.available() <= 0) {
        return;
    }

    size_t bytes_read = duckySerial.recv(buffer, DUCKY_PACKET_MAX_SIZE);

    if (bytes_read == 0) {
        memset(buffer, 0, DUCKY_PACKET_MAX_SIZE);
        return;
    }

    if (debug) {
        Serial.print("\nBytes read: ");
        Serial.println(bytes_read);
    }

    DuckyPacket *packet = (DuckyPacket *)buffer;

    if (debug) {
       print_packet_header(packet);
    }

    switch (packet->header.type) {
        case DUCKY_PACKET_TYPE_COMMAND:
            handle_command((Command *)packet->payload);
            break;
        case DUCKY_PACKET_TYPE_PRINTLN:
            Serial.println("[ESP8266] " + (String)(packet->payload));
            break;
        default:
            break;
    }

    memset(buffer, 0, DUCKY_PACKET_MAX_SIZE);
    Serial.println("---");
}

