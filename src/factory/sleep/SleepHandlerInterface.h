#ifndef T_SLEEP_HANDLER_INTERFACE_H
#define T_SLEEP_HANDLER_INTERFACE_H

class SleepHandlerInterface {

public:
    virtual void goSleep() = 0;
    virtual void wakeUp() = 0;
};

#endif