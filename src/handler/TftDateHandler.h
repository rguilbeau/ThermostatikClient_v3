#ifndef T_TFT_DATE_HANDLER_H
#define T_TFT_DATE_HANDLER_H

#include <Arduino.h>

#include "factory/clock/ClockHandlerInterface.h"

#include "service/TftService.h"

#include "utils/Date.h"

class TftDateHandler : public ClockHandlerInterface {

public:
    TftDateHandler(TftService *tftService);
    void clockHandle() override;

private:
    TftService *_tftService;
    
    long _lastTimeMin;
    bool _dateUpdateEnabled;
};

#endif