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
    _isQuickRender = true;
    return true;
}

OrderRender HeatingForcedNextOrder::getRender()
{
    OrderRender render;

    render.icon = TftImage::IMAGE_ORDER_FORCED;
    render.temperature = TftFactory::formatTemperature(_device->getForcedTemperature());
    render.label = F("Manuelle jusqu'a");
    render.info = F("la prochaine consigne");
    return render;
}