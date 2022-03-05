#include "OrderTime.h"

OrderTime::OrderTime()
{
    _dayIndex = 0;
    _time = 0;
    _orderId = 0;
    _used = false;
}

void OrderTime::update(unsigned short dayIndex, unsigned short time, unsigned short orderId)
{
    _dayIndex = dayIndex;
    _time = time;
    _orderId = orderId;
    _used = true;
}

void OrderTime::unused()
{
    _used = false;
}

unsigned short OrderTime::getDayIndex()
{
    return _dayIndex;
}

unsigned short OrderTime::getTime() 
{
    return _time;
}

unsigned short OrderTime::getOrderId()
{
    return _orderId;
}

bool OrderTime::isUsed()
{
    return _used;
}

unsigned short OrderTime::findTimeSinceStartWeek()
{
    return _time + (_dayIndex * 1440);
}