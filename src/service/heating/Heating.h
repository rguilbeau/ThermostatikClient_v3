#ifndef T_HEATING_H
#define T_HEATING_H

#include <Arduino.h>

#include "model/Device.h"
#include "model/Programme.h"

class Heating {
public:

    static Heating *getMode(Device *device, Programme *programme);

    virtual ~Heating() = 0;

    virtual bool regulationStatus(float currentTemperature) = 0;


protected:
    Device *_device;
    Programme *_programme;

    Heating(Device *device, Programme *programme);
    bool _regulateByTemperature(float requestTemperature, float currentTemperature);

};

#endif