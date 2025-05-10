//
// Created by Henning Tandberg on 07/05/2025.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "duckyp.h"

int duckyp_create_packet(struct duckyp_packet **packet, uint8_t type, uint8_t len, const char *payload)
{
    size_t packet_size = sizeof(struct duckyp_header) + len;
    (*packet) = (struct duckyp_packet *)malloc(packet_size);

    (*packet)->header.type = type;
    (*packet)->header.len = len;
    memcpy((*packet)->payload, payload, sizeof(char) * len);

    return 0;
}