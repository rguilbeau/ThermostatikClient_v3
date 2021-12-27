#ifndef T_DHT_HANDLER_INTERFACE_H
#define T_DHT_HANDLER_INTERFACE_H

#include <Arduino.h>

class DhtHandlerInterface {

public:

    virtual void temperatureChanged(float temperature) = 0;

    virtual void temperatureIsNan() = 0;

};

#endif