#ifndef T_HEATING_POWER_OFF_H
#define T_HEATING_POWER_OFF_H

#include "Heating.h"

class HeatingPowerOff : public Heating {

public:
    HeatingPowerOff(Device *device, Programme *programme);
    ~HeatingPowerOff();

    bool regulationStatus(float currentTemperature, bool currentStatus) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;
    
private:

};

#endif