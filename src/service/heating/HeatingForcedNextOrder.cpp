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
        Serial.print(F("Regulation : Forced next order"));
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
    _render.onlyTemperature = true;
    return true;
}

OrderRender HeatingForcedNextOrder::getRender()
{
    _render.icon = TftImage::IMAGE_ORDER_FORCED;
    _render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    _render.label = "Manuelle jusqu'a";
    _render.info = "la prochaine consigne";
    return _render;
}