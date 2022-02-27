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

bool HeatingForcedAlways::nextMode()
{
    _device->setPowerOn(false);
    return true;
}

bool HeatingForcedAlways::forceTemperature(float increment)
{
    _device->setForcedTemperature(_device->getForcedTemperature() + increment);
    _render.onlyTemperature = true;
    return true;
}

OrderRender HeatingForcedAlways::getRender()
{
    _render.icon = TftImage::IMAGE_ORDER_FORCED;
    _render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    _render.label = "Manuelle";
    _render.info = "Tout le temps";
    return _render;
}