#ifndef T_DHT_FACTORY_H
#define T_DHT_FACTORY_H

#include <Arduino.h>

#include "Debug.h"

#include "DhtHandlerInterface.h"

class DhtFactory {

public:   
    DhtFactory(unsigned short pin, unsigned short delay);

    void setHandler(DhtHandlerInterface *dhtHandler);

    float getTemperature();

    bool isNan();

    void loop();

    void setTare(float tare);

private:

    unsigned short _pin;
    unsigned short _delay;
    float _lastTemperature;
    unsigned long _lastCheck;
    bool _isNan;

    float _tare;

    bool _readTemperature();

    DhtHandlerInterface *_dhtHandler;
};

#endif