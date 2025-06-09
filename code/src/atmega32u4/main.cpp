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

char buffer[DUCKY_PACKET_MAX_SIZE];

void loop() {
    if (duckySerial.available() <= 0) {
        return;
    }

    size_t bytes_read = duckySerial.recv(buffer, DUCKY_PACKET_MAX_SIZE);

    if (bytes_read == 0) {
        memset(buffer, 0, DUCKY_PACKET_MAX_SIZE);
        return;
    }

    Serial.print("Bytes read: ");
    Serial.println(bytes_read);

    DuckyPacket *packet = (DuckyPacket *)buffer;

    Serial.println("Packet: ");

    Serial.print("Header type: ");
    Serial.println(packet->header.type, DEC);
    Serial.print("Header len: ");
    Serial.println(packet->header.len, DEC);

    Command *command = (Command *)packet->payload;
    Serial.print("Command type: ");
    Serial.println(command->type, DEC);
    Serial.print("Command len: ");
    Serial.println(command->len, DEC);

    for (int j = 0; j < command->len; j++) {
        Serial.print("Byte: ");
        Serial.println(command->payload[j], HEX);
    }

    //handle_keypress_command(command);
    memset(buffer, 0, DUCKY_PACKET_MAX_SIZE);
}

