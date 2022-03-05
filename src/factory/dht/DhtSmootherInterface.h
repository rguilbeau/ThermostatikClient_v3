#ifndef T_DHT_SMOOTHER_INTERFACE_H
#define T_DHT_SMOOTHER_INTERFACE_H

class DhtSmootherInterface {

public:

    virtual float smooth(float temperature, float lastTemperature) = 0;

};

#endif