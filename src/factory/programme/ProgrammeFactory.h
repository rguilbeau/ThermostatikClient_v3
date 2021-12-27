#ifndef T_PROGRAMME_FACTORY_H
#define T_PROGRAMME_FACTORY_H

#include <Arduino.h>

#include "model/Programme.h"
#include "model/Device.h"
#include "model/Order.h"

#include "UntilDateHandlerInterface.h"
#include "OrderHandlerInterface.h"

#include "utils/Date.h"

class ProgrammeFactory {

public:
    ProgrammeFactory(
        Programme *programme,
        Device *device
    );

    void setOrderHandler(OrderHandlerInterface *orderHandlerInterface);
    void setUntilDateHandler(UntilDateHandlerInterface *untilDateHandlerInterface);

    void loop();

private:
    OrderHandlerInterface * _orderHandlerInterface;
    UntilDateHandlerInterface *_untilDateHandlerInterface;

    Programme *_programme;
    Device *_device;

    long _lastCheckMin;
};

#endif