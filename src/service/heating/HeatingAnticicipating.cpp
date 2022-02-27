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
        Serial.print(F("Regulation : anticipating, Order:"));
        
        if(order == nullptr) {
            Serial.println(F("null"));
        } else {
            Serial.print(order->getLabel());
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

    _render.icon = TftImage::IMAGE_ORDER_ANTICIPATING;
    _render.temperature = TftFactory::formatTemperature(order->getTemperature());
    _render.label = order->getLabel() + " (anticipation)";
    _render.info = _programme->getLabel();
    return _render;
}