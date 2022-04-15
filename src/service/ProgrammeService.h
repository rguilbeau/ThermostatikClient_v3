#ifndef T_PROGRAMME_SERVICE_H
#define T_PROGRAMME_SERVICE_H

#include <Arduino.h>

#include "factory/temperature_sensor/TemperatureSensorFactory.h"

#include "model/Device.h"
#include "model/Programme.h"
#include "model/Order.h"
#include "model/OrderTime.h"

#include "utils/Date.h"

class ProgrammeService {

public:
    ProgrammeService(
        Device *device,
        Programme *programme,
        TemperatureSensorFactory *temperatureSensorFactory
    );

    OrderTime *findOrderTimeAt(Date date);
    OrderTime *findNextOrderTimeAt(Date date);
    
    Order *findCurrentOrder();
    Order *findAnticipatingOrder();

private:
    Device *_device;
    Programme *_programme;

    TemperatureSensorFactory *_temperatureSensorFactory;
};

#endif