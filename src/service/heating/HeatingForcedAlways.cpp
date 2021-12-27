#include "HeatingForcedAlways.h"

HeatingForcedAlways::HeatingForcedAlways(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingForcedAlways::~HeatingForcedAlways()
{

}

bool HeatingForcedAlways::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Forced always");
    #endif

    return _regulateByTemperature(_device->getForcedTemperature(), currentTemperature);
}