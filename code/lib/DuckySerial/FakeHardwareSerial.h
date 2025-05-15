//
// Created by Henning Tandberg on 15/05/2025.
//

#ifndef USB_RUBBER_DUCKY_FAKEHARDWARESERIAL_H
#define USB_RUBBER_DUCKY_FAKEHARDWARESERIAL_H

#include <stddef.h>

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <FakeString.h>
#endif

#define FakeHardwareSerial HardwareSerial

class HardwareSerial
{
public:
    virtual void begin(unsigned long baud);
    virtual int available(void);
    virtual size_t write(const char * buf, size_t len);
    virtual size_t write(int n);
    virtual int read(void);
    virtual String readStringUntil(char chr);
};

#endif //USB_RUBBER_DUCKY_FAKEHARDWARESERIAL_H
