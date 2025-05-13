#include <Arduino.h>
#include <Keyboard.h>
#include <SPI.h>
#include <string.h>
#include <CommandParser.h>
#include <duckyp.h>

#define EspSerial Serial1

void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    Keyboard.begin();
    Serial.begin(115200);
    EspSerial.begin(115200);
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

void handle_command(command_t * command) {
    if (command->type != COMMAND_TYPE_KEYBOARD_KEYPRESS) {
        return;
    }

    for (int i = 0; i < command->len; i++) {
        Keyboard.press((uint8_t)command->payload[i]);
    }

    delay(100);
    Keyboard.releaseAll();
}

char buffer[256];
int i = 0;

void loop() {
    if (EspSerial.available() <= 0) {
        return;
    }

    while(EspSerial.available()) {
        if (i == 255) {
            Serial.println("GIBBERISH!");
            return;
        }

        char rcvChar = EspSerial.read();

        // Check for end symbol
        if (rcvChar == '\r') {
            break;  // Break the loop upon end symbol
        }

        buffer[i++] = rcvChar;
        Serial.print("Recv byte: ");
        Serial.println(buffer[i - 1], HEX);
    }

    duckyp_packet *packet = (duckyp_packet *)malloc(i);
    memcpy(packet, buffer, i);
    memset(buffer, 0, 255);
    i = 0;

    Serial.println("Packet: ");

    Serial.print("Header type: ");
    Serial.println(packet->header.type, DEC);
    Serial.print("Header len: ");
    Serial.println(packet->header.len, DEC);

    command_t *command = (command_t *)packet->payload;
    Serial.print("Command type: ");
    Serial.println(command->type, DEC);
    Serial.print("Command len: ");
    Serial.println(command->len, DEC);

    for (int j = 0; j < command->len; j++) {
        Serial.print("Byte: ");
        Serial.println(command->payload[j], HEX);
    }

    handle_command(command);

    free(packet);
}

