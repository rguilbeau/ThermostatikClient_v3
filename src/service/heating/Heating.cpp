#include "Heating.h"

#include "HeatingForcedAlways.h"
#include "HeatingForcedNextOrder.h"
#include "HeatingForcedUntil.h"
#include "HeatingPowerOff.h"
#include "HeatingProgramme.h"
#include "HeatingAnticipating.h"

Heating *Heating::getMode(Device *device, Programme *programme) {
    if(device->isForcedAlways()) {
        return new HeatingForcedAlways(device, programme);
    } else if(device->isForcedNextOrder()) {
        return new HeatingForcedNextOrder(device, programme);
    } else if(device->isForcedUntilDate()) {
        return new HeatingForcedUntil(device, programme);
    } else if(device->isProgrammeMode() && programme->getAnticipatingOrder() == nullptr) {
        return new HeatingProgramme(device, programme);
    } else if(device->isProgrammeMode() && programme->getAnticipatingOrder() != nullptr) {
        return new HeatingAnticipating(device, programme);
    } else {
        return new HeatingPowerOff(device, programme);
    }
}

Heating::Heating(Device *device, Programme *programme)
{
    _device = device;
    _programme = programme;
    _isQuickRender = false;
}

Heating::~Heating()
{

}

bool Heating::_regulateByTemperature(float requestTemperature, float currentTemperature, bool currentStatus)
{
    bool regulationStatus = currentStatus;

    if(currentStatus && currentTemperature >= requestTemperature + 0.1) {
        regulationStatus = false;
    } else if(!currentStatus && currentTemperature <= requestTemperature -0.1) {
        regulationStatus = true;
    }

    #ifdef DEBUG
        Serial.print(F(" by temperature request:"));
        Serial.print(requestTemperature);
        Serial.print(F(", current:"));
        Serial.print(currentTemperature);
        Serial.print(F(", heating:"));
        Serial.println(regulationStatus);
    #endif

    return regulationStatus;
}

bool Heating::isQuickRender()
{
    return _isQuickRender;
}