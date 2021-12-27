#ifndef T_ORDER_TIME_H
#define T_ORDER_TIME_H

#include <Arduino.h>

#include "Order.h"

class OrderTime {

public:
    OrderTime();
    
    void update(int dayIndex, int time, int orderId);
    void unused();

    int getDayIndex();
    int getTime();
    int getOrderId();
    bool isUsed();
    
private:
    bool _used;
    int _dayIndex;
    int _time;
    int _orderId;
};

#endif