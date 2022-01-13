#include "HeatingForcedAlways.h"

HeatingForcedAlways::HeatingForcedAlways(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingForcedAlways::~HeatingForcedAlways()
{

}

HeatingType HeatingForcedAlways::getType()
{
    return HeatingType::HEATING_FORCED_ALWAYS;
}

bool HeatingForcedAlways::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Forced always");
    #endif

    return _regulateByTemperature(_device->getForcedTemperature(), currentTemperature);
}

bool HeatingForcedAlways::nextMode()
{
    _device->setPowerOn(false);
    return true;
}

bool HeatingForcedAlways::forceTemperature(float increment)
{
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    return true;
}