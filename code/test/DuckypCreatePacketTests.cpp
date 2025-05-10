//
// Created by Henning Tandberg on 07/05/2025.
//

#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include <duckyp.h>

void duckyp_create_packet_PacketContainsProvidedCommand(void) {
    duckyp_packet *packet = NULL;

    packet = duckyp_create_packet(DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(0, strcmp(packet->payload, "PLN echo hello!"));
    free(packet);
}

void duckyp_create_packet_HeaderIndicatesCommandPacket(void) {
    duckyp_packet *packet = NULL;

    packet = duckyp_create_packet(DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(DUCKYP_TYPE_COMMAND, packet->header.type);
    free(packet);
}

void duckyp_create_packet_HeaderHasCorrectCommandLen(void) {
    duckyp_packet *packet = NULL;

    packet = duckyp_create_packet(DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(16, packet->header.len);
    free(packet);
}