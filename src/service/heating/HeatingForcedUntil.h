#ifndef T_HEATING_UNTIL_H
#define T_HEATING_UNTIL_H

#include "Heating.h"

class HeatingForcedUntil : public Heating {

public:
    HeatingForcedUntil(Device *device, Programme *programme);
    ~HeatingForcedUntil();

    bool regulationStatus(float currentTemperature) override;

private:

};

#endif