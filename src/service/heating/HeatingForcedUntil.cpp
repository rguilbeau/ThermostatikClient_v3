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
        Serial.print(F("Regulation : Forced until"));
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
    _isQuickRender = true;
    return true;
}

OrderRender HeatingForcedUntil::getRender()
{
    Date until(_device->getForcedUntil());

    OrderRender render;
    render.icon = TftImage::IMAGE_ORDER_FORCED;
    render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    render.label = F("Manuelle jusqu'au");
    render.info = until.toShortFormat();
    return render;
}