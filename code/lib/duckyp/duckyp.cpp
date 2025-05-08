//
// Created by Henning Tandberg on 07/05/2025.
//

#include <stddef.h>
#include <stdlib.h>

#include "duckyp.h"

char duckyp_get_keystroke(struct duckyp_packet *packet)
{
    if (packet->header.type != DUCKYP_TYPE_KEYSTROKE)
    {
        return -1;
    }

    if (packet->header.len != 1)
    {
        return -1;
    }

    return packet->payload[0];
}

int duckyp_create_keystroke(struct duckyp_packet **packet, char keystroke)
{
    size_t packet_size = sizeof(struct duckyp_header) + sizeof(char);
    (*packet) = (struct duckyp_packet *)malloc(packet_size);

    (*packet)->header.type = DUCKYP_TYPE_KEYSTROKE;
    (*packet)->header.len = 1;
    (*packet)->payload[0] = keystroke;

    return 0;
}