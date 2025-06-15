//
// Created by Henning Tandberg on 14/05/2025.
//

#ifndef USB_RUBBER_DUCKY_DUCKYSERIAL_H
#define USB_RUBBER_DUCKY_DUCKYSERIAL_H

#include <stddef.h>

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <FakeHardwareSerial.h>
#endif

#define EOT 0x07 // ASCII End of Transmission

class DuckySerial {
private:
    HardwareSerial & _serial;
    DuckySerial(HardwareSerial & serial) : _serial(serial) { }
public:
    int available(void);
    void begin(unsigned long baud);
    size_t sendCommand(const char * buffer, size_t length);
    size_t sendPrintln(const char * buffer, size_t length);
    size_t recv(char * buffer, size_t length);

    static DuckySerial create(HardwareSerial & serial);
};


#endif //USB_RUBBER_DUCKY_DUCKYSERIAL_H
