#include "HeatingAnticipating.h"

HeatingAnticipating::HeatingAnticipating(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingAnticipating::~HeatingAnticipating()
{

}

bool HeatingAnticipating::regulationStatus(float currentTemperature)
{
    Order *order = _programme->getAnticipatingOrder();
    #ifdef DEBUG
        Serial.print("Regulation : anticipating, Order:");
        Serial.print(order == nullptr ? "null" : order->getLabel());

        if(order == nullptr) {
            Serial.println();
        }
    #endif

    return _regulateByTemperature(order->getTemperature(), currentTemperature);
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
    render.icon = TftImage::IMAGE_ORDER_ANTICIPATING;
    render.temperature = TftFactory::formatTemperature(order->getTemperature());
    render.label = order->getLabel() + " (anticipation)";
    render.info = _programme->getLabel();
    return render;
}