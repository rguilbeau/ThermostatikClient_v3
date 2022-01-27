#include "Programme.h"

Programme::Programme()
{
    _lastOrder = nullptr;
    _label = "";

    for(int i = 0; i < PROGRAMME_MAX_TIMES_ORDERS; i++) {
        _ordersTimes[i] = new OrderTime();
    }

    for(int i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
        _orders[i] = new Order();
    }
}

Order *Programme::getOrder(int index)
{
    if(index < PROGRAMME_MAX_ORDERS) {
        return _orders[index];
    } else {
        return nullptr;
    }
}

OrderTime *Programme::getOrderTime(int index)
{
    if(index < PROGRAMME_MAX_TIMES_ORDERS) {
        return _ordersTimes[index];
    } else {
        return nullptr;
    }
}

Order *Programme::getLastOrder()
{
    if(_lastOrder != nullptr && _lastOrder->isUsed()) {
        return _lastOrder;
    } else {
        return nullptr;
    }
}

Order *Programme::getAnticipatingOrder()
{
    if(_anticipatingOrder != nullptr && _anticipatingOrder->isUsed()) {
        return _anticipatingOrder;
    } else {
        return nullptr;
    }
}

void Programme::setLastOrder(Order *order)
{
    _lastOrder = order;
}

void Programme::setAnticipatingOrder(Order *order)
{
    _anticipatingOrder = order;
}

String Programme::getLabel() 
{
    return _label;
}

void Programme::setLabel(String label) 
{
    _label = label;
}

Order *Programme::findAnticipatingOrderAt(Order *currentOrder, Date date)
{
    Order *anticipatingOrder = findOrderAt(date);
    if(anticipatingOrder != nullptr && anticipatingOrder->isUsed() && currentOrder->getTemperature() < anticipatingOrder->getTemperature()) {
        return anticipatingOrder;
    } else {
        return nullptr;
    }
}

Order *Programme::findOrderAt(Date date)
{
    int dayIndex = date.findDayIndex();
    int timeFromMidnight = date.findTimeSinceMidnight();

    int orderId = 0;
    bool finded = false;
    int lastTime = 0;
    Order *order = nullptr;

    for(int i = 0; i < PROGRAMME_MAX_TIMES_ORDERS; i++) {
        OrderTime *orderTime = getOrderTime(i);

        if(orderTime != nullptr
            && orderTime->isUsed()
            && dayIndex == orderTime->getDayIndex()
            && timeFromMidnight >= orderTime->getTime()
            && orderTime->getTime() >= lastTime) 
        {
            orderId = orderTime->getOrderId();
            finded = true;
        }
    }

    if(finded) {
        for(int i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
            Order *orderCur = getOrder(i);
            if(orderCur != nullptr && orderCur->isUsed() && orderCur->getId() == orderId) {
                order = orderCur;
                break;
            }
        }
    }
    
    return order;
}
