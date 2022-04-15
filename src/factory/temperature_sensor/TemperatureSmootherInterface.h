#ifndef T_TEMPERATURE_SMOOTHER_INTERFACE_H
#define T_TEMPERATURE_SMOOTHER_INTERFACE_H

class TemperatureSmootherInterface {

public:

    virtual float smooth(float temperature, float lastTemperature) = 0;

};

#endif