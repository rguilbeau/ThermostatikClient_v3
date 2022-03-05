#ifndef T_CLOCK_FACTORY_H
#define T_CLOCK_FACTORY_H

#include <Arduino.h>
#include "Debug.h"

#include "ClockHandlerInterface.h"
#include "NtpHandlerInterface.h"

class ClockFactory {

public:
    ClockFactory();

    void setNtpHandler(NtpHandlerInterface *ntpHandler);
    void setHandlerSize(unsigned short size);
    void setHandler(unsigned short index, unsigned short delay, ClockHandlerInterface *handler);

    void initNtp();

    void loop();

private:
    bool _ntpInitialized; 
    unsigned short _handlerSize;
    unsigned short *_handlersDelays;
    unsigned long *_lastCheck;
    ClockHandlerInterface **_handlers;
    NtpHandlerInterface *_ntpHandler;

};

#endif