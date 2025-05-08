//
// Created by Henning Tandberg on 07/05/2025.
//

#include "unity.h"
#include <string.h>
#include <duckyp.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void keystrokPacketContainingLeftCtrl_duckyp_get_keystroke_LeftCtrlIsReturned(void) {
    struct duckyp_packet *packet = NULL;
    size_t packet_size = sizeof(struct duckyp_header) + sizeof(char);
    packet = (struct duckyp_packet *)malloc(packet_size);
    packet->header.type = DUCKYP_TYPE_KEYSTROKE;
    packet->header.len = 1;
    packet->payload[0] = (char)0x80;

    char keystroke = duckyp_get_keystroke(packet);

    TEST_ASSERT_EQUAL((char)0x80, keystroke);
    free(packet);
}

void LeftCtrl_duckyp_create_keystroke_PacketContainingLeftCtrlIsReturned(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_keystroke(packet, (char)0x80);

    TEST_ASSERT_EQUAL((char)0x80, packet->payload[0]);
    free(packet);
}

void LeftCtrl_duckyp_set_keystroke_HeaderIndicatesKeystrokePacket(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_keystroke(&packet, (char)0x80);

    TEST_ASSERT_EQUAL(DUCKYP_TYPE_KEYSTROKE, packet->header.type);
    free(packet);
}

void LeftCtrl_duckyp_set_keystroke_HeaderSizeIsCorrect(void) {
    struct duckyp_packet *packet = NULL;

    duckyp_create_keystroke(&packet, (char)0x80);

    TEST_ASSERT_EQUAL(1, packet->header.len);
    free(packet);
}

int runUnityTests(void) {
    UNITY_BEGIN();

    RUN_TEST(keystrokPacketContainingLeftCtrl_duckyp_get_keystroke_LeftCtrlIsReturned);
    RUN_TEST(LeftCtrl_duckyp_create_keystroke_PacketContainingLeftCtrlIsReturned);
    RUN_TEST(LeftCtrl_duckyp_set_keystroke_HeaderIndicatesKeystrokePacket);
    RUN_TEST(LeftCtrl_duckyp_set_keystroke_HeaderSizeIsCorrect);

    return UNITY_END();
}

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
}