#ifndef T_HEATING_NEXTORDER_H
#define T_HEATING_NEXTORDER_H

#include "Heating.h"

class HeatingForcedNextOrder : public Heating {

public:
    HeatingForcedNextOrder(Device *device, Programme *programme);
    ~HeatingForcedNextOrder();

    bool regulationStatus(float currentTemperature, bool currentStatus) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;
    
private:

};

#endif