#ifndef T_HEATING_PROGRAMME_H
#define T_HEATING_PROGRAMME_H

#include "Heating.h"

class HeatingProgramme : public Heating {

public:
    HeatingProgramme(Device *device, Programme *programme);
    ~HeatingProgramme();

    bool regulationStatus(float currentTemperature) override;
    bool nextMode() override;
    bool forceTemperature(float increment) override;
    OrderRender getRender() override;

private:

};

#endif