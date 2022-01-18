#ifndef T_HEATING_NEXTORDER_H
#define T_HEATING_NEXTORDER_H

#include "Heating.h"

class HeatingForcedNextOrder : public Heating {

public:
    HeatingForcedNextOrder(Device *device, Programme *programme);
    ~HeatingForcedNextOrder();

    HeatingType getType() override;
    bool regulationStatus(float currentTemperature) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;
    
private:

};

#endif