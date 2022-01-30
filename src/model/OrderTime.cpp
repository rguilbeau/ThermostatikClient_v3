#include "OrderTime.h"

OrderTime::OrderTime()
{
    _dayIndex = 0;
    _time = 0;
    _orderId = 0;
    _used = false;
}

void OrderTime::update(int dayIndex, int time, int orderId)
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

int OrderTime::getDayIndex()
{
    return _dayIndex;
}

int OrderTime::getTime() 
{
    return _time;
}

int OrderTime::getOrderId()
{
    return _orderId;
}

bool OrderTime::isUsed()
{
    return _used;
}

unsigned long OrderTime::findTimeSinceStartWeek()
{
    return _time + (_dayIndex * 1440);
}