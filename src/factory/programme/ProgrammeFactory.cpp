#include "ProgrammeFactory.h"

ProgrammeFactory::ProgrammeFactory(
    Programme *programme,
    Device *device
) {
    _programme = programme;
    _device = device;
    _untilDateHandlerInterface = nullptr;
    _orderHandlerInterface = nullptr;
    _lastCheckMin = 0;
}

void ProgrammeFactory::setOrderHandler(OrderHandlerInterface *orderHandlerInterface)
{
    _orderHandlerInterface = orderHandlerInterface;
}

void ProgrammeFactory::setUntilDateHandler(UntilDateHandlerInterface *untilDateHandlerInterface)
{
    _untilDateHandlerInterface = untilDateHandlerInterface;
}

void ProgrammeFactory::loop()
{
    Date now;
    if(_lastCheckMin != now.getTimeMin()) {
        _lastCheckMin = now.getTimeMin();

        Order *currentOrder = _programme->findOrderAt(now);
        Order *lastOrder = _programme->getLastOrder();

        if(lastOrder == nullptr || lastOrder->getId() != currentOrder->getId()) {            
            if(_orderHandlerInterface != nullptr) {
                _orderHandlerInterface->orderUpdated(currentOrder);
            }
        }

        if(_untilDateHandlerInterface != nullptr && _device->isForcedUntilDate()) {
            Date untilDate(_device->getForcedUntil());
            
            if(untilDate.before(now)) {
                _untilDateHandlerInterface->untilDateHit();
            }
        }
    }
}