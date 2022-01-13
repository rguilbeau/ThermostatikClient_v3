#include "HeatingProgramme.h"

HeatingProgramme::HeatingProgramme(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingProgramme::~HeatingProgramme()
{

}

HeatingType HeatingProgramme::getType()
{
    return HeatingType::HEATING_PROGRAMME;
}

bool HeatingProgramme::regulationStatus(float currentTemperature)
{
    Order *order = _programme->getLastOrder();
    
    #ifdef DEBUG
        Serial.print("Regulation : Programme, Order:");
        Serial.print(order == nullptr ? "null" : order->getLabel());

        if(order == nullptr) {
            Serial.println();
        }
    #endif

    if(order != nullptr) {
        return _regulateByTemperature(order->getTemperature(), currentTemperature);
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