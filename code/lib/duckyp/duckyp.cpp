//
// Created by Henning Tandberg on 07/05/2025.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "duckyp.h"

duckyp_packet * duckyp_create_packet(uint8_t type, uint8_t len, const char *payload)
{
    duckyp_packet *packet;

    size_t packet_size = sizeof(duckyp_header) + len;
    packet = (duckyp_packet *)malloc(packet_size);

    packet->header.type = type;
    packet->header.len = len;
    memcpy(packet->payload, payload, sizeof(char) * len);

    return packet;
}
