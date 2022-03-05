#ifndef T_ORDER_H
#define T_ORDER_H

#include <Arduino.h>

class Order {

public:
    Order();
    
    void update(unsigned short id, String lable, float temperature);
    void unused();

    unsigned short getId();
    String getLabel();
    float getTemperature();
    bool isUsed();

private:
    bool _used;
    unsigned short _id;
    String _label;
    float _temperature;
};

#endif