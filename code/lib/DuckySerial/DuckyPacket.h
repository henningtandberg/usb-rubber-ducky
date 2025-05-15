//
// Created by Henning Tandberg on 07/05/2025.
//

#ifndef USB_RUBBER_DUCKY_DUCKY_PACKET_H
#define USB_RUBBER_DUCKY_DUCKY_PACKET_H

#include <stdint.h>

#define UART_BUFFER_SIZE_BYTES          64

#define DUCKY_HEADER_SIZE               sizeof(struct DuckyHeader)
#define DUCKY_PACKET_MAX_SIZE           (4 * UART_BUFFER_SIZE_BYTES)
#define DUCKY_PACKET_PAYLOAD_MAX_SIZE   (DUCKY_PACKET_MAX_SIZE - DUCKY_HEADER_SIZE)

#define DUCKY_PACKET_TYPE_COMMAND       0x00

typedef struct DuckyHeader {
    uint8_t type;
    uint8_t len;
} __attribute__((packed)) DuckyHeader;

typedef struct DuckyPacket {
    struct DuckyHeader header;
    char payload[];
} __attribute__((packed)) DuckyPacket;

class DuckyPacketFactory {
public:
    static DuckyPacket * create(uint8_t type, uint8_t len, const char * payload);
};


#endif //USB_RUBBER_DUCKY_DUCKY_PACKET_H
