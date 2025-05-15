//
// Created by Henning Tandberg on 07/05/2025.
//

#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include <DuckyPacket.h>

void CommandPacket_Create_PacketContainsProvidedCommand(void) {
    DuckyPacket * packet = NULL;

    packet = DuckyPacketFactory::create(DUCKY_PACKET_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(0, strcmp(packet->payload, "PLN echo hello!"));
    free(packet);
}

void CommandPacket_Create_HeaderIndicatesCommandPacket(void) {
    DuckyPacket * packet = NULL;

    packet = DuckyPacketFactory::create(DUCKY_PACKET_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(DUCKY_PACKET_TYPE_COMMAND, packet->header.type);
    free(packet);
}

void CommandPacket_Create_HeaderHasCorrectCommandLen(void) {
    DuckyPacket * packet = NULL;

    packet = DuckyPacketFactory::create(DUCKY_PACKET_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(16, packet->header.len);
    free(packet);
}