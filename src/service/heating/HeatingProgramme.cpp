#include "HeatingProgramme.h"

HeatingProgramme::HeatingProgramme(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingProgramme::~HeatingProgramme()
{

}

bool HeatingProgramme::regulationStatus(float currentTemperature, bool currentStatus)
{
    Order *order = _programme->getLastOrder();
    
    #ifdef DEBUG
        Serial.print(F("Regulation : Programme, Order:"));
        
        if(order == nullptr) {
            Serial.println(F("null"));
        } else {
            Serial.print(order->getLabel());
        }
    #endif

    if(order != nullptr) {
        return _regulateByTemperature(order->getTemperature(), currentTemperature, currentStatus);
    } else {
        return false;
    }
}

bool HeatingProgramme::nextMode()
{
    _device->setPowerOn(true);
    _device->setForced(true);
    
    Order *order = _programme->getLastOrder();

    if(order != nullptr) {
        _device->setForcedUntil(0);
        _device->setForcedTemperature(order->getTemperature());
    } else {
        _device->setForcedUntil(-1);
        _device->setForcedTemperature(20.5);
    }

    return true;
}

bool HeatingProgramme::forceTemperature(float increment)
{
    nextMode();
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    return true;
}

OrderRender HeatingProgramme::getRender()
{
    Order *order = _programme->getLastOrder();
    
    OrderRender render;

    render.icon = TftImage::IMAGE_ORDER_PROGRAMME;

    if(order != nullptr) {
        render.temperature = TftFactory::formatTemperature(order->getTemperature());
        render.label = order->getLabel();
        render.info = _programme->getLabel();
    } else {
        render.temperature = F("N/A");
    }
    return render;
}