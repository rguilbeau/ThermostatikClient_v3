#ifndef T_HEATING_H
#define T_HEATING_H

#include <Arduino.h>

#include "model/Device.h"
#include "model/Programme.h"

#include "factory/tft/TftFactory.h"
#include "factory/tft/type/TftImage.h"

#include "render/OrderRender.h"

class Heating {
public:

    static Heating *getMode(Device *device, Programme *programme);

    virtual ~Heating() = 0;

    virtual bool regulationStatus(float currentTemperature, bool currentStatus) = 0;

    virtual bool nextMode() = 0;
    virtual bool forceTemperature(float increment) = 0;

    virtual OrderRender getRender() = 0;

    bool isQuickRender();

protected:
    Device *_device;
    Programme *_programme;

    Heating(Device *device, Programme *programme);
    bool _regulateByTemperature(float requestTemperature, float currentTemperature, bool currentStatus);

    bool _isQuickRender;

};

#endif