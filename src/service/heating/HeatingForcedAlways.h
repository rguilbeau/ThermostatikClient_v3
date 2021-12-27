#ifndef T_HEATING_ALWAYS_H
#define T_HEATING_ALWAYS_H

#include "Heating.h"

class HeatingForcedAlways: public Heating {

public:
    HeatingForcedAlways(Device *device, Programme *programme);
    ~HeatingForcedAlways();

    bool regulationStatus(float currentTemperature) override;
};

#endif