#ifndef T_HEATING_PROGRAMME_H
#define T_HEATING_PROGRAMME_H

#include "Heating.h"

class HeatingProgramme : public Heating {

public:
    HeatingProgramme(Device *device, Programme *programme);
    ~HeatingProgramme();

    bool regulationStatus(float currentTemperature) override;

private:

};

#endif