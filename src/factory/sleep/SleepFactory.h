#ifndef T_SLEEP_FACTORY_H
#define T_SLEEP_FACTORY_H

#include <Arduino.h>
#include "SleepHandlerInterface.h"

class SleepFactory {

public:
    SleepFactory(unsigned short delay);

    void wakeUp();
    bool isWakeUp();

    void setHandler(SleepHandlerInterface *handler);
    void invokeHandler();
    void loop();

private:
    SleepHandlerInterface *_handler;
    unsigned long _lastWakeUp;
    unsigned short _delay;
    bool _sleeping;
};

#endif