//
// Created by Henning Tandberg on 07/05/2025.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "DuckyPacket.h"

DuckyPacket * DuckyPacketFactory::create(uint8_t type, uint8_t len, const char * payload)
{
    DuckyPacket * packet;
    size_t packet_size = DUCKY_HEADER_SIZE + len;

    packet = (DuckyPacket *)malloc(packet_size);
    packet->header.type = type;
    packet->header.len = len;

    memcpy(packet->payload, payload, len);

    return packet;
}
