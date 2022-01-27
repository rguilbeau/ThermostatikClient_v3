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
}

Heating::~Heating()
{

}

bool Heating::_regulateByTemperature(float requestTemperature, float currentTemperature)
{
    bool regulationStatus;

    if(requestTemperature > currentTemperature) {
        regulationStatus = true;
    } else {
        regulationStatus = false;
    }

    #ifdef DEBUG
        Serial.print(" by temperature request:");
        Serial.print(requestTemperature);
        Serial.print(", current:");
        Serial.print(currentTemperature);
        Serial.print(", heating:");
        Serial.println(regulationStatus);
    #endif

    return regulationStatus;
}