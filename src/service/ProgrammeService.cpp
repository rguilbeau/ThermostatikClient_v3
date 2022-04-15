#include "ProgrammeService.h"

ProgrammeService::ProgrammeService(
    Device *device,
    Programme *programme,
    TemperatureSensorFactory *temperatureSensorFactory
) {
    _device = device;
    _programme = programme;
    _temperatureSensorFactory = temperatureSensorFactory;
}

OrderTime *ProgrammeService::findOrderTimeAt(Date date)
{
    OrderTime *findedOrderTime = nullptr;

    short relativeTime = date.findTimeSinceStartWeek();
    short lastRelativeTime = -1;

    for(unsigned short i = 0; i < _programme->getOrderTimeSize(); i++) {
        OrderTime *orderTime = _programme->getOrderTime(i);

        if(orderTime != nullptr && orderTime->isUsed()) {
            short orderRelativeTime = orderTime->findTimeSinceStartWeek();

            if(orderRelativeTime <= relativeTime
                && (lastRelativeTime == -1 || orderRelativeTime > lastRelativeTime)
            ) {
                lastRelativeTime = orderRelativeTime;
                findedOrderTime = orderTime;
            }
        }
    }
    return findedOrderTime;
}

OrderTime *ProgrammeService::findNextOrderTimeAt(Date date)
{
    OrderTime *findedOrderTime = nullptr;
    OrderTime *currentOrderTime = findOrderTimeAt(date);
    short lastRelativeTime = -1;

    if(currentOrderTime != nullptr) {
        short currentRelativeTime = currentOrderTime->findTimeSinceStartWeek();

        for(unsigned short i = 0; i < _programme->getOrderTimeSize(); i++) {
            OrderTime *orderTime = _programme->getOrderTime(i);

            if(orderTime != nullptr && orderTime->isUsed()) {
                short orderRelativeTime = orderTime->findTimeSinceStartWeek();

                if(orderRelativeTime > currentRelativeTime
                    && (lastRelativeTime == -1 || orderRelativeTime < lastRelativeTime)
                ) {
                    lastRelativeTime = orderRelativeTime;
                    findedOrderTime = orderTime;
                }
            }
        }
    }

    return findedOrderTime;
}

Order *ProgrammeService::findCurrentOrder()
{
    Date now;
    OrderTime *orderTime = findOrderTimeAt(now);

    if(orderTime != nullptr) {
        return _programme->getOrderById(orderTime->getOrderId());
    } else {
        return nullptr;
    }
}

Order *ProgrammeService::findAnticipatingOrder()
{
    if(_device->getHeatingAnticipation() > 0 && !_temperatureSensorFactory->isNan()) {
        Date now;
        OrderTime *anticipatingOrderTime = findNextOrderTimeAt(now);
        Order *anticipatingOrder = anticipatingOrderTime != nullptr 
            ? _programme->getOrderById(anticipatingOrderTime->getOrderId()) 
            : nullptr;

        if(anticipatingOrder != nullptr) {
            long anticipatingTime = anticipatingOrderTime->findTimeSinceStartWeek();
            long currentTime = now.findTimeSinceStartWeek();
            long diffTime = anticipatingTime - currentTime;

            if(_temperatureSensorFactory->getTemperature() + (_device->getHeatingAnticipation() * diffTime) <= anticipatingOrder->getTemperature()) {
                return anticipatingOrder;
            }
        }
    }
    return nullptr;
}