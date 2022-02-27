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
    _render.onlyTemperature = true;
    return true;
}

OrderRender HeatingForcedUntil::getRender()
{
    Date until(_device->getForcedUntil());

    _render.icon = TftImage::IMAGE_ORDER_FORCED;
    _render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    _render.label = "Manuelle jusqu'au";
    _render.info = until.toShortFormat();
    return _render;
}