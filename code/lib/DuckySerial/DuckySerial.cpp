//
// Created by Henning Tandberg on 14/05/2025.
//

#include <stdlib.h>
#include <string.h>
#include <DuckyPacket.h>

#include "DuckySerial.h"

DuckySerial DuckySerial::create(HardwareSerial &serial) {
    return DuckySerial(serial);
}

void DuckySerial::begin(unsigned long baud) {
    _serial.begin(baud);
}

int DuckySerial::available(void) {
    return _serial.available();
}

size_t DuckySerial::sendCommand(const char * buffer, size_t length) {
    DuckyPacket *packet = DuckyPacketFactory::create(DUCKY_PACKET_TYPE_COMMAND, length, buffer);

    size_t bytes_to_send = DUCKY_HEADER_SIZE + packet->header.len;
    _serial.write((char *)packet, bytes_to_send);
    _serial.write(EOT);
    _serial.flush();

    free(packet);
    return bytes_to_send;
}

size_t DuckySerial::sendPrintln(const char * buffer, size_t length) {
    DuckyPacket *packet = DuckyPacketFactory::create(DUCKY_PACKET_TYPE_PRINTLN, length, buffer);

    size_t bytes_to_send = DUCKY_HEADER_SIZE + packet->header.len;
    _serial.write((char *)packet, bytes_to_send);
    _serial.write(EOT);
    _serial.flush();

    free(packet);
    return bytes_to_send;
}

size_t DuckySerial::recv(char * buffer, size_t length) {
    if (_serial.available() <= 0) {
        return 0;
    }

    String str = _serial.readStringUntil(EOT);
    size_t bytes_received = str.length();

    if (bytes_received > length) {
        return 0; // We have a problem!
    }

    memcpy(buffer, str.c_str(), bytes_received);

    return bytes_received;
}
