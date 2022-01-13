#ifndef T_HEATING_POWER_OFF_H
#define T_HEATING_POWER_OFF_H

#include "Heating.h"

class HeatingPowerOff : public Heating {

public:
    HeatingPowerOff(Device *device, Programme *programme);
    ~HeatingPowerOff();

    HeatingType getType() override;
    bool regulationStatus(float currentTemperature) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;

private:

};

#endif