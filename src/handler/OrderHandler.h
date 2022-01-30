#ifndef T_ORDER_HANDLER_H
#define T_ORDER_HANDLER_H

#include <Arduino.h>

#include "factory/clock/ClockHandlerInterface.h"
#include "handler/interface/UntilDateHandlerInterface.h"
#include "handler/interface/OrderUpdatedHandlerInterface.h"
#include "model/Device.h"
#include "model/Programme.h"

#include "service/ProgrammeService.h"

#include "utils/Date.h"

class OrderHandler : public ClockHandlerInterface {

public:
    OrderHandler(
        Device *device,
        Programme *programme,
        DhtFactory *dhtFactory,
        ProgrammeService *programmeService
    );

    void setOrderUpdatedHandler(OrderUpdatedHandlerInterface *orderUpdatedHandlerInterface);
    void setUntilDateHandler(UntilDateHandlerInterface *untilDateHandlerInterface);
    
    void clockHandle() override;

private:
    Device *_device;
    Programme *_programme;
    
    DhtFactory *_dhtFactory;

    ProgrammeService *_programmeService;

    OrderUpdatedHandlerInterface *_orderUpdatedHandlerInterface;
    UntilDateHandlerInterface *_untilDateHandlerInterface;

    long _lastCheckMin;
};

#endif