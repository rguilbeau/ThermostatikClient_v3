#ifndef T_HEATING_UNTIL_H
#define T_HEATING_UNTIL_H

#include "Heating.h"

class HeatingForcedUntil : public Heating {

public:
    HeatingForcedUntil(Device *device, Programme *programme);
    ~HeatingForcedUntil();

    bool regulationStatus(float currentTemperature, bool currentStatus) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;
    
private:

};

#endif