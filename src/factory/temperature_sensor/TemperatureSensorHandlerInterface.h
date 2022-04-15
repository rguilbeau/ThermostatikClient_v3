#ifndef T_TEMPERATURE_SENSOR_HANDLER_INTERFACE_H
#define T_TEMPERATURE_SENSOR_HANDLER_INTERFACE_H

#include <Arduino.h>

class TemperatureSensorHandlerInterface {

public:

    virtual void temperatureChanged(float temperature) = 0;

    virtual void temperatureIsNan() = 0;

};

#endif