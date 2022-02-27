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
        Serial.print(F("Regulation : Forced always"));
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
    _isQuickRender = true;
    return true;
}

OrderRender HeatingForcedAlways::getRender()
{
    OrderRender render;

    render.icon = TftImage::IMAGE_ORDER_FORCED;
    render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    render.label = "Manuelle";
    render.info = "Tout le temps";
    return render;
}