#include "HeatingPowerOff.h"

HeatingPowerOff::HeatingPowerOff(Device *device, Programme *programme) : Heating(device, programme)
{

}

HeatingPowerOff::~HeatingPowerOff()
{

}

HeatingType HeatingPowerOff::getType()
{
    return HeatingType::HEATING_POWER_OFF;
}

bool HeatingPowerOff::regulationStatus(float currentTemperature)
{
    #ifdef DEBUG
        Serial.println("Regulation : power off. Heating:0");
    #endif

    return false;
}

bool HeatingPowerOff::nextMode()
{
    Order *order = _programme->getLastOrder();
    if(order != nullptr) {
        _device->setPowerOn(true);
        _device->setForced(false);
    } else {
        _device->setPowerOn(true);
        _device->setForced(true);
        _device->setForcedUntil(-1);
        _device->setForcedTemperature(20.5);
    }
    return true;
}

bool HeatingPowerOff::forceTemperature(float increment)
{
    return false;
}

OrderRender HeatingPowerOff::getRender()
{
    OrderRender render;
    render.icon = TftImage::IMAGE_ORDER_POWER_OFF;
    render.temperature = "Eteint";
    render.label = "Aucune consigne";
    render.info = "";
    return render;
}