#ifndef T_SLEEP_HANDLER_H
#define T_SLEEP_HANDLER_H

#include <Arduino.h>
#include "Debug.h"

#include "factory/sleep/SleepHandlerInterface.h"
#include "factory/tft/TftFactory.h"

#include "model/Device.h"

class SleepHandler : public SleepHandlerInterface {

public:
    SleepHandler(
        Device *device,
        TftFactory *tftFactory
    );

    void goSleep() override;
    void wakeUp() override;

private:
    Device *_device;
    TftFactory *_tftFactory;
};

#endif