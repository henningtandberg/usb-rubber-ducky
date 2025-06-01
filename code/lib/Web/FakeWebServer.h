//
// Created by Henning Tandberg on 31/05/2025.
//

#ifndef USB_RUBBER_DUCKY_FAKEWEBSERVER_H
#define USB_RUBBER_DUCKY_FAKEWEBSERVER_H

class FakeWebServer {
public:
    typedef std::function<void(void)> THandlerFunction;
    void on(const char* uri, HTTPMethod method, THandlerFunction fn);
    void send(int code, const char* content_type = NULL, String content = String(""));
};

#endif //USB_RUBBER_DUCKY_FAKEWEBSERVER_H
