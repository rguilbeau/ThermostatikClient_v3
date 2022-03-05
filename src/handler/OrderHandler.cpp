#include "OrderHandler.h"

OrderHandler::OrderHandler(
    Device *device,
    Programme *programme,
    DhtFactory *dhtFactory,
    ProgrammeService *programmeService
) {
    _device = device;
    _programme = programme;
    _dhtFactory = dhtFactory;
    _programmeService = programmeService;
    _lastCheckMin = -1;
}

void OrderHandler::setOrderUpdatedHandler(OrderUpdatedHandlerInterface *orderUpdatedHandlerInterface)
{
    _orderUpdatedHandlerInterface = orderUpdatedHandlerInterface;
}

void OrderHandler::setUntilDateHandler(UntilDateHandlerInterface *untilDateHandlerInterface)
{
    _untilDateHandlerInterface = untilDateHandlerInterface;
}

void OrderHandler::clockHandle() {
    Date now;
    if(_lastCheckMin != now.getTimeMin()) {
        _lastCheckMin = now.getTimeMin();

        // check if order updated
        Order *lastOrder = _programme->getLastOrder();
        Order *currentOrder = _programmeService->findCurrentOrder();
        if(
            currentOrder != nullptr && 
            (lastOrder == nullptr || lastOrder->getId() != currentOrder->getId())
        ) {
            _programme->setLastOrder(currentOrder);
            _programme->setAnticipatingOrder(nullptr);

            if(_orderUpdatedHandlerInterface != nullptr) {
                _orderUpdatedHandlerInterface->orderUpdated();
            }
        }
        
        // check if anticipating
        Order *lastAnticipating = _programme->getAnticipatingOrder();
        if(lastAnticipating == nullptr) {
            Order *anticipatingOrder = _programmeService->findAnticipatingOrder();

            _programme->setAnticipatingOrder(anticipatingOrder);

            if(anticipatingOrder != nullptr) {
                if(_orderUpdatedHandlerInterface != nullptr) {
                    _orderUpdatedHandlerInterface->orderAnticipating();
                }
            }
        }

        // check if forced date hint
        if(_untilDateHandlerInterface != nullptr && _device->isForcedUntilDate()) {
            Date untilDate(_device->getForcedUntil());
            
            if(untilDate.before(now)) {
                _untilDateHandlerInterface->untilDateHit();
            }
        }
    }
}