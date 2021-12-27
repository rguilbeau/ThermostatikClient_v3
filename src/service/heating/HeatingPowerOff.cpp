#include "HeatingPowerOff.h"

HeatingPowerOff::HeatingPowerOff(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingPowerOff::~HeatingPowerOff()
{

}

bool HeatingPowerOff::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.println("Regulation : power off. Heating:0");
    #endif

    return false;
}