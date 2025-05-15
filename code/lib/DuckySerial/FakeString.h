//
// Created by Henning Tandberg on 15/05/2025.
//

#ifndef USB_RUBBER_DUCKY_FAKESTRING_H
#define USB_RUBBER_DUCKY_FAKESTRING_H

class String {
public:
    virtual char * c_str(void);
    virtual int length(void);
};

#endif //USB_RUBBER_DUCKY_FAKESTRING_H
