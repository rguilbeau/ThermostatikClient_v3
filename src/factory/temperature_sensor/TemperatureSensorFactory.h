#ifndef T_TEMPERATURE_SENSOR_FACTORY_H
#define T_TEMPERATURE_SENSOR_FACTORY_H

#include <Arduino.h>
#include <SHT31.h>
#include "Debug.h"

#include "service/TftService.h"
#include "TemperatureSensorHandlerInterface.h"
#include "TemperatureSmootherInterface.h"
#include "TemperatureSensorBrutHandlerInterface.h"

class TemperatureSensorFactory {

public:   
    TemperatureSensorFactory(SHT31 *sht, uint8_t pin, unsigned short delay);

    void setHandler(TemperatureSensorHandlerInterface *temperatureSensorHandler);
    void setSmoother(TemperatureSmootherInterface *temperatureSmoother);
    void setTemperatureBrutHandler(TemperatureSensorBrutHandlerInterface *temperatureBrutHandler);

    float getTemperature();

    bool isNan();

    void loop();

    void setTare(float tare);

private:
    SHT31 *_sht;

    unsigned short _pin;
    unsigned short _delay;
    float _lastTemperature;
    unsigned long _lastCheck;
    unsigned short _isNanCnt;
    bool _isNan;
    bool _nanNotified;
    float _tare;

    bool _readTemperature();

    TemperatureSensorHandlerInterface *_temperatureSensorHandler;
    TemperatureSmootherInterface *_temperatureSmoother;
    TemperatureSensorBrutHandlerInterface *_temperatureBrutHandler;
};

#endif