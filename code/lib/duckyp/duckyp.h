//
// Created by Henning Tandberg on 07/05/2025.
//

#ifndef USB_RUBBER_DUCKY_DUCKYP_H
#define USB_RUBBER_DUCKY_DUCKYP_H

#include <stdint.h>

#define UART_BUFFER_SIZE_BYTES  64

#define DUCKYP_HEADER_SIZE      (sizeof(struct duckyp_header))
#define DUCKYP_PAYLOAD_MAX_SIZE (UART_BUFFER_SIZE_BYTES - DUCKYP_HEADR_SIZE)
#define DUCKYP_PACKET_MAX_SIZE  (DUCKYP_HEADDR_SIZE + DUCKYP_PAYLOAD_MAX_SIZE)

#define DUCKYP_TYPE_KEYSTROKE   0x00

typedef struct duckyp_header {
    uint8_t type;
    uint8_t len;
} __attribute__((packed)) duckyp_header;

typedef struct duckyp_packet {
    struct duckyp_header header;
    char payload[];
} __attribute__((packed)) duckyp_packet;

char duckyp_get_keystroke(struct duckyp_packet *packet);
int duckyp_create_keystroke(struct duckyp_packet **packet, char keystroke);

#endif //USB_RUBBER_DUCKY_DUCKYP_H
