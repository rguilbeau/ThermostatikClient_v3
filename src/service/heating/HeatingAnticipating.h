#ifndef T_HEATING_ANTICIPATING_H
#define T_HEATING_ANTICIPATING_H

#include "Heating.h"

class HeatingAnticipating: public Heating {

public:
    HeatingAnticipating(Device *device, Programme *programme);
    ~HeatingAnticipating();

    bool regulationStatus(float currentTemperature) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;
};

#endif