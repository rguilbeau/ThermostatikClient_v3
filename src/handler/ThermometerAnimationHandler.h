#ifndef T_THERMOMETER_ANIMATION_HANDLER_H
#define T_THERMOMETER_ANIMATION_HANDLER_H

#include <Arduino.h>
#include "factory/clock/ClockHandlerInterface.h"

#include "utils/Date.h"

class ThermometerAnimationHandler : public ClockHandlerInterface {

public:
    ThermometerAnimationHandler();

    void clockHandle() override;

private:
    long _lastTimeMin;

};

#endif