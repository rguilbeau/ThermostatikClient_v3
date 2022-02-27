#ifndef T_SLEEP_FACTORY_H
#define T_SLEEP_FACTORY_H

#include <Arduino.h>
#include "SleepHandlerInterface.h"

class SleepFactory {

public:
    SleepFactory(int delay);

    void wakeUp();
    void setHandler(SleepHandlerInterface *handler);
    void invokeHandler();
    void loop();

private:
    SleepHandlerInterface *_handler;
    unsigned long _lastWakeUp;
    int _delay;
    bool _sleeping;
};

#endif