#ifndef T_TEMPERATURE_SENSOR_BRUT_HANDLER_INTERFACE_H
#define T_TEMPERATURE_SENSOR_BRUT_HANDLER_INTERFACE_H

#include <Arduino.h>

class TemperatureSensorBrutHandlerInterface {

public:

    virtual void temperatureBrutChanged(float temperature) = 0;

};

#endif