#ifndef T_ORDER_HANDLER_INTERFACE_H
#define T_ORDER_HANDLER_INTERFACE_H

#include <Arduino.h>

#include "model/Order.h"

class OrderHandlerInterface {

public:

    virtual void orderUpdated(Order *order) = 0;

};

#endif