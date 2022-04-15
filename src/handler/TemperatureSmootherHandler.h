#ifndef T_TEMPERATURE_SMOOTHER_HANDLER_H
#define T_TEMPERATURE_SMOOTHER_HANDLER_H

#include <Arduino.h>

#include "Debug.h"

#include "factory/temperature_sensor/TemperatureSmootherInterface.h"

class TemperatureSmootherHandler : public TemperatureSmootherInterface {

public:
    TemperatureSmootherHandler();

    float smooth(float temperature, float lastTemperature) override;

private:

    void sort(float a[], unsigned short size);
    float smooth(float temperature, float lastTemperature, float factor);
    float fixDecimal(float temperature);

    short _readsIndex;
    float _reads[3]{0,0,0};
    float _lastTemperature;
    bool _hasMuted;
};

#endif