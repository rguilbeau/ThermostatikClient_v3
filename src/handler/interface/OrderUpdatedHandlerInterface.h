#ifndef T_ORDER_UPDATED_HANDLER_INTERFACE_H
#define T_ORDER_UPDATED_HANDLER_INTERFACE_H

#include <Arduino.h>

#include "model/Order.h"

class OrderUpdatedHandlerInterface {

public:

    virtual void orderUpdated() = 0;
    virtual void orderAnticipating() = 0;
};

#endif