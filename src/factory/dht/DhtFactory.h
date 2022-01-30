#ifndef T_DHT_FACTORY_H
#define T_DHT_FACTORY_H

#include <Arduino.h>
#include <DHTesp.h>

#include "Debug.h"

#include "DhtHandlerInterface.h"

class DhtFactory {

public:   
    DhtFactory(DHTesp *dht, unsigned short pin, unsigned short delay);

    void setHandler(DhtHandlerInterface *dhtHandler);

    float getTemperature();

    bool isNan();

    void loop();

    void setTare(float tare);

private:

    DHTesp *_dht;

    unsigned short _pin;
    unsigned short _delay;
    float _lastTemperature;
    unsigned long _lastCheck;
    int _isNanCnt;
    bool _nanNotified;
    float _tare;

    bool _readTemperature();
    float fixDecimal(float temperature);
    float smooth(float temperature, float lastSmoothTemperature, float factor);

    DhtHandlerInterface *_dhtHandler;
};

#endif