#ifndef T_HEATING_NEXTORDER_H
#define T_HEATING_NEXTORDER_H

#include "Heating.h"

class HeatingForcedNextOrder : public Heating {

public:
    HeatingForcedNextOrder(Device *device, Programme *programme);
    ~HeatingForcedNextOrder();

    bool regulationStatus(float currentTemperature) override;

private:

};

#endif