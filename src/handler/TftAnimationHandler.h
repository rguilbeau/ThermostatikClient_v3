#ifndef T_THERMOMETER_ANIMATION_HANDLER_H
#define T_THERMOMETER_ANIMATION_HANDLER_H

#include <Arduino.h>

#include "factory/clock/ClockHandlerInterface.h"
#include "factory/tft/type/TftImage.h"

#include "service/TftService.h"

class TftAnimationHandler : public ClockHandlerInterface {

public:
    TftAnimationHandler(
        TftService *tftService
    );

    void animateThermometer(bool animate);
    void clockHandle() override;

private:
    TftService *_tftService;

    bool _thermometerAnimation;
    TftImage _lastThermometerImage;
};

#endif