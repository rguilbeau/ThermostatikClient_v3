#include "HeatingAnticipating.h"

HeatingAnticipating::HeatingAnticipating(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingAnticipating::~HeatingAnticipating()
{

}

bool HeatingAnticipating::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Anticipating");
    #endif

    return _regulateByTemperature(_programme->getAnticipatingOrder()->getTemperature(), currentTemperature);
}

bool HeatingAnticipating::nextMode()
{
    _device->setPowerOn(true);
    _device->setForced(true);
    
    Order *order = _programme->getAnticipatingOrder();

    if(order != nullptr) {
        _device->setForcedUntil(0);
        _device->setForcedTemperature(order->getTemperature());
    } else {
        _device->setForcedUntil(-1);
        _device->setForcedTemperature(20.5);
    }

    return true;
}

bool HeatingAnticipating::forceTemperature(float increment)
{
    nextMode();
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    return true;
}

OrderRender HeatingAnticipating::getRender()
{
    Order *order = _programme->getAnticipatingOrder();

    OrderRender render;
    render.icon = TftImage::IMAGE_ORDER_PROGRAMME;
    render.temperature = TftFactory::formatTemperature(order->getTemperature());
    render.label = order->getLabel() + " (anticipation)";
    render.info = _programme->getLabel();
    return render;
}