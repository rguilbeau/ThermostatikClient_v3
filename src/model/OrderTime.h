#ifndef T_ORDER_TIME_H
#define T_ORDER_TIME_H

#include <Arduino.h>

#include "Order.h"

class OrderTime {

public:
    OrderTime();
    
    void update(unsigned short dayIndex, unsigned short time, unsigned short orderId);
    void unused();

    unsigned short getDayIndex();
    unsigned short getTime();
    unsigned short getOrderId();
    bool isUsed();
    unsigned short findTimeSinceStartWeek();
    
private:
    bool _used;
    unsigned short _dayIndex;
    unsigned short _time;
    unsigned short _orderId;
};

#endif