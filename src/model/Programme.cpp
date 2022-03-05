#include "Programme.h"

Programme::Programme()
{
    _lastOrder = nullptr;
    _anticipatingOrder = nullptr;

    _label = "";

    for(int i = 0; i < PROGRAMME_MAX_TIMES_ORDERS; i++) {
        _ordersTimes[i] = new OrderTime();
    }

    for(int i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
        _orders[i] = new Order();
    }
}

Order *Programme::getOrder(unsigned short index)
{
    if(index < PROGRAMME_MAX_ORDERS) {
        return _orders[index];
    } else {
        return nullptr;
    }
}

OrderTime *Programme::getOrderTime(unsigned short index)
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

unsigned short Programme::getOrderTimeSize()
{
    return PROGRAMME_MAX_TIMES_ORDERS;
}

unsigned short Programme::getOrderSize()
{
    return PROGRAMME_MAX_ORDERS;
}

Order *Programme::getOrderById(unsigned short orderId)
{
    for(int i = 0; i < PROGRAMME_MAX_ORDERS; i++) {
        Order *orderCur = getOrder(i);
        if(orderCur != nullptr && orderCur->isUsed() && orderCur->getId() == orderId) {
            return orderCur;
        }
    }
    return nullptr;
}