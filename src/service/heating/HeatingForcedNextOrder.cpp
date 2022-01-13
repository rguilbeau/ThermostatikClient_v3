#include "HeatingForcedNextOrder.h"

HeatingForcedNextOrder::HeatingForcedNextOrder(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingForcedNextOrder::~HeatingForcedNextOrder()
{

}

HeatingType HeatingForcedNextOrder::getType()
{
    return HeatingType::HEATING_FORCED_NEXT_ORDER;
}

bool HeatingForcedNextOrder::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.print("Regulation : Forced next order");
    #endif

    return _regulateByTemperature(_device->getForcedTemperature(), currentTemperature);
}

bool HeatingForcedNextOrder::nextMode()
{
    _device->setPowerOn(true);
    _device->setForced(true);
    _device->setForcedUntil(-1);
    return true;
}

bool HeatingForcedNextOrder::forceTemperature(float increment)
{
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    return true;
}