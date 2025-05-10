//
// Created by Henning Tandberg on 07/05/2025.
//

#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include <duckyp.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void duckyp_create_packet_PacketContainsProvidedCommand(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_packet(&packet, DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(0, strcmp(packet->payload, "PLN echo hello!"));
    free(packet);
}

void duckyp_create_packet_HeaderIndicatesCommandPacket(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_packet(&packet, DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(DUCKYP_TYPE_COMMAND, packet->header.type);
    free(packet);
}

void duckyp_create_packet_HeaderHasCorrectCommandLen(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_packet(&packet, DUCKYP_TYPE_COMMAND, 16, "PLN echo hello!");

    TEST_ASSERT_EQUAL(16, packet->header.len);
    free(packet);
}

int runUnityTests(void) {
    UNITY_BEGIN();

    RUN_TEST(duckyp_create_packet_PacketContainsProvidedCommand);
    RUN_TEST(duckyp_create_packet_HeaderIndicatesCommandPacket);
    RUN_TEST(duckyp_create_packet_HeaderHasCorrectCommandLen);

    return UNITY_END();
}

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
}