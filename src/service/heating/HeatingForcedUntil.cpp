#include "HeatingForcedUntil.h"

HeatingForcedUntil::HeatingForcedUntil(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingForcedUntil::~HeatingForcedUntil()
{

}

bool HeatingForcedUntil::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Forced until");
    #endif

    return _regulateByTemperature(_device->getForcedTemperature(), currentTemperature);
}

bool HeatingForcedUntil::nextMode()
{
    _device->setPowerOn(false);
    return true;
}

bool HeatingForcedUntil::forceTemperature(float increment)
{
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    return true;
}