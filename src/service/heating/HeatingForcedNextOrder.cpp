#include "HeatingForcedNextOrder.h"

HeatingForcedNextOrder::HeatingForcedNextOrder(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingForcedNextOrder::~HeatingForcedNextOrder()
{

}

bool HeatingForcedNextOrder::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Forced next order");
    #endif

    return _regulateByTemperature(_device->getForcedTemperature(), currentTemperature);
}