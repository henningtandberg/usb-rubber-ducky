//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_COMMAND_H
#define USB_RUBBER_DUCKY_COMMAND_H

#include <stdint.h>

#define COMMAND_TYPE_UNKNOWN            0x00
#define COMMAND_TYPE_KEYBOARD_KEYPRESS  0x01
#define COMMAND_TYPE_KEYBOARD_PRINT     0x02
#define COMMAND_TYPE_KEYBOARD_PRINTLN   0x03
#define COMMAND_TYPE_MOUSE_MOVE         0x04
#define COMMAND_TYPE_MOUSE_CLICK        0x05
#define COMMAND_TYPE_EXECUTE_SCRIPT     0x06

typedef struct Command {
    uint8_t type;
    uint8_t len;
    char payload[];
} __attribute__((packed)) Command;

#endif //USB_RUBBER_DUCKY_COMMAND_H
